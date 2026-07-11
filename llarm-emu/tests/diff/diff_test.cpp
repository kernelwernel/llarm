#include <llarm/llarm-emu.hpp>
#include <llarm/llarm-asm.hpp>
#include "src/device-tree/dtb.hpp"
#include "src/settings.hpp"
#include "src/vic/vic.hpp"
#include "src/peripherals/uart/uart.hpp"

#include <unicorn/unicorn.h>

#include <array>
#include <cstdio>
#include <cstdlib>
#include <vector>

static constexpr u32 CPSR_MASK = 0xF80F03FFU; // flags + mode + I/F/T

struct mem_write {
    u32 address;
    u32 size;
    u64 value;
};

static void on_mem_write(uc_engine* /*uc*/, uc_mem_type /*type*/, u64 address, int size, i64 value, void* user_data) {
    auto* writes = static_cast<std::vector<mem_write>*>(user_data);
    writes->push_back({ static_cast<u32>(address), static_cast<u32>(size), static_cast<u64>(value) });
}

struct reg_entry {
    llarm::emu::reg reg_id;
    uc_arm_reg uc_reg_id;
    const char* name;
};

// PC is excluded: llarm-emu returns the pipelined value (PC+8), Unicorn returns the raw PC
static constexpr std::array<reg_entry, 16> REG_MAP = {{
    { llarm::emu::reg_R0, UC_ARM_REG_R0, "R0" },
    { llarm::emu::reg_R1, UC_ARM_REG_R1, "R1" },
    { llarm::emu::reg_R2, UC_ARM_REG_R2, "R2" },
    { llarm::emu::reg_R3, UC_ARM_REG_R3, "R3" },
    { llarm::emu::reg_R4, UC_ARM_REG_R4, "R4" },
    { llarm::emu::reg_R5, UC_ARM_REG_R5, "R5" },
    { llarm::emu::reg_R6, UC_ARM_REG_R6, "R6" },
    { llarm::emu::reg_R7, UC_ARM_REG_R7, "R7" },
    { llarm::emu::reg_R8, UC_ARM_REG_R8, "R8" },
    { llarm::emu::reg_R9, UC_ARM_REG_R9, "R9" },
    { llarm::emu::reg_R10, UC_ARM_REG_R10, "R10" },
    { llarm::emu::reg_R11, UC_ARM_REG_R11, "R11" },
    { llarm::emu::reg_R12, UC_ARM_REG_R12, "IP" },
    { llarm::emu::reg_R13, UC_ARM_REG_R13, "SP" },
    { llarm::emu::reg_R14, UC_ARM_REG_R14, "LR" },
    { llarm::emu::reg_CPSR, UC_ARM_REG_CPSR, "CPSR" },
}};

static void uc_must(uc_err err, const char* op) {
    if (err != UC_ERR_OK) {
        fprintf(stderr, "unicorn error in %s: %s\n", op, uc_strerror(err));
        exit(1);
    }
}

static void wait_for_execution(llarm::emu::cpu_blockstep& emu) {
    emu.wait_for_execution();
}

static void halt_and_exit(llarm::emu::cpu_blockstep& emu, int code) {
    emu.cpu.core.is_halted = true;
    emu.next_instruction();
    exit(code);
}

// PrimeCell PeriphID0-3 / PCellID0-3 are fixed, read-only identification registers
// (DDI0181/DDI0183, offsets 0xFE0-0xFFC). Unicorn has no VIC/UART device model, so
// without this it reads back 0 there while LLARM's peripheral model reads the real
// constant, producing a false-positive divergence. Seeding these known constants
// into Unicorn's flat memory lets the two models agree on this narrow, static slice
// of MMIO; stateful peripheral registers are out of scope for this diff test.
static void seed_primecell_ids(uc_engine* uc, u32 base, const std::array<u32, 8>& ids) {
    constexpr std::array<u16, 8> OFFSETS = {{ 0xFE0, 0xFE4, 0xFE8, 0xFEC, 0xFF0, 0xFF4, 0xFF8, 0xFFC }};

    for (u8 i = 0; i < OFFSETS.size(); i++) {
        uc_must(uc_mem_write(uc, base + OFFSETS.at(i), &ids.at(i), sizeof(u32)), "seed PrimeCell ID register");
    }
}

static uc_engine* setup_unicorn(const SETTINGS& s, const std::vector<u8>& binary) {
    uc_engine* uc = nullptr;
    uc_must(uc_open(UC_ARCH_ARM, UC_MODE_ARM, &uc), "uc_open");
    uc_must(uc_ctl_set_cpu_model(uc, UC_CPU_ARM_926), "set cpu ARM926");
    // Map the full 32-bit address space so all reads return 0 for unmapped areas,
    // matching LLARM's RAM model which silently returns 0 for out-of-range accesses.
    uc_must(uc_mem_map(uc, 0, 0x100000000ULL, UC_PROT_ALL), "uc_mem_map");

    seed_primecell_ids(uc, s.vic_base, {{ PERIPH_ID0, PERIPH_ID1, PERIPH_ID2, PERIPH_ID3, PCELL_ID0, PCELL_ID1, PCELL_ID2, PCELL_ID3 }});
    seed_primecell_ids(uc, s.uart_base, {{ UART_PERIPHID0, UART_PERIPHID1, UART_PERIPHID2, UART_PERIPHID3, UART_PCELLID0, UART_PCELLID1, UART_PCELLID2, UART_PCELLID3 }});

    uc_must(uc_mem_write(uc, s.binary_load_address, binary.data(), binary.size()), "write binary");
    uc_must(uc_mem_write(uc, s.dtb_load_address, DTB::data.data(), DTB::data.size()), "write dtb");

    const u32 cpsr = 0xD3U; // SVC mode, I=1, F=1, T=0
    const u32 r0 = 0;
    const u32 r1 = s.machine_type;
    const u32 r2 = s.dtb_load_address;
    const u32 sp = static_cast<u32>(s.memsize); // top of RAM, matching QEMU's boot stub
    const u32 pc = s.binary_load_address;

    uc_must(uc_reg_write(uc, UC_ARM_REG_CPSR, &cpsr), "write CPSR");
    uc_must(uc_reg_write(uc, UC_ARM_REG_R0, &r0), "write R0");
    uc_must(uc_reg_write(uc, UC_ARM_REG_R1, &r1), "write R1");
    uc_must(uc_reg_write(uc, UC_ARM_REG_R2, &r2), "write R2");
    uc_must(uc_reg_write(uc, UC_ARM_REG_SP, &sp), "write SP");
    uc_must(uc_reg_write(uc, UC_ARM_REG_PC, &pc), "write PC");

    return uc;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: llarm-difftest [-v] <binary>\n");
        return 1;
    }

    bool verbose = false;
    const char* binary_path = nullptr;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == 'v') {
                verbose = true;
            } else {
                fprintf(stderr, "unknown flag: %s\n", argv[i]);
                return 1;
            }
        } else {
            binary_path = argv[i];
        }
    }

    if (!binary_path) {
        fprintf(stderr, "usage: llarm-difftest [-v] <binary>\n");
        return 1;
    }

    const SETTINGS settings = image_settings();

    llarm::emu::cpu_blockstep emu(binary_path, settings);
    emu.run();

    // Wait for the first instruction to finish executing
    while (!emu.cpu.core.execution_done.load(std::memory_order_acquire)) {}

    uc_engine* uc = setup_unicorn(settings, emu.binary);

    std::vector<mem_write> mem_writes;
    uc_hook mem_hook = 0;
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    uc_must(uc_hook_add(uc, &mem_hook, UC_HOOK_MEM_WRITE, reinterpret_cast<void*>(on_mem_write), &mem_writes, 1, 0), "add mem write hook");

    u32 zero_run = 0;

    bool has_expected_next_pc = false;
    u32 expected_next_pc = 0;
    u32 prev_step_num = 0;
    u32 prev_step_pc = 0;
    u32 prev_step_opcode = 0;
    std::string prev_step_id_str;
    std::string prev_step_disasm;

    for (u32 step = 0; ; step++) {
        const u32 pc = emu.current_pc();

        if (has_expected_next_pc && pc != expected_next_pc) {
            fprintf(stderr, "[%u] 0x%08X  op=0x%08X  id=%-30s  %s\n",
                prev_step_num, prev_step_pc, prev_step_opcode,
                prev_step_id_str.c_str(), prev_step_disasm.c_str());
            fprintf(stderr, "\033[31mDIVERGENCE\033[0m\n");
            fprintf(stderr, "  \033[31mPC  llarm=0x%08X  unicorn=0x%08X\033[0m\n", pc, expected_next_pc);
            halt_and_exit(emu, 1);
        }

        const bool thumb = emu.is_thumb_mode();
        const u32 opcode = thumb ? emu.current_thumb_code() : emu.current_arm_code();
        const std::string id_str = thumb
            ? llarm::as::identify_thumb_string(opcode)
            : llarm::as::identify_arm_string(opcode);
        const std::string disasm = thumb
            ? llarm::as::disassemble_thumb(static_cast<u16>(opcode), pc)
            : llarm::as::disassemble_arm(opcode, pc);

        if (verbose) {
            fprintf(stderr, "[%u] 0x%08X  op=0x%08X  id=%-30s  R5=0x%08X R6=0x%08X R9=0x%08X SP=0x%08X  %s\n",
                step, pc, opcode,
                id_str.c_str(),
                emu.read_reg(llarm::emu::reg_R5),
                emu.read_reg(llarm::emu::reg_R6),
                emu.read_reg(llarm::emu::reg_R9),
                emu.read_reg(llarm::emu::reg_SP),
                disasm.c_str());
        }

        if (opcode == 0) {
            zero_run++;
            if (zero_run >= 8) {
                fprintf(stderr, "[%u] 0x%08X  8 consecutive zero opcodes, CPU fell into zeroed memory\n", step, pc);
                halt_and_exit(emu, 1);
            }
        } else {
            zero_run = 0;
        }

        const uc_err err = uc_emu_start(uc, pc, 0, 0, 1);

        if (err == UC_ERR_INSN_INVALID) {
            // Architecturally UNPREDICTABLE instructions (e.g. SBO violations) may be rejected
            // by Unicorn as invalid. Advance Unicorn's PC past the instruction so comparison
            // can continue; any divergence in checked registers will surface naturally.
            fprintf(stderr, "[%u] 0x%08X  op=0x%08X  unicorn INSN_INVALID, skipping\n", step, pc, opcode);
            const u32 next_pc = pc + (thumb ? 2U : 4U);
            uc_reg_write(uc, UC_ARM_REG_PC, &next_pc);
        } else if (err != UC_ERR_OK) {
            fprintf(stderr, "[%u] 0x%08X  op=0x%08X  id=%-30s  %s\n", step, pc, opcode, id_str.c_str(), disasm.c_str());
            fprintf(stderr, "\033[31m[%u] unicorn fault at PC=0x%08X: %s\033[0m\n", step, pc, uc_strerror(err));
            fprintf(stderr, "  register state at fault:\n");

            for (const auto& r : REG_MAP) {
                fprintf(stderr, "  %-4s  llarm=0x%08X\n", r.name, emu.read_reg(r.reg_id));
            }

            halt_and_exit(emu, 1);
        }

        uc_reg_read(uc, UC_ARM_REG_PC, &expected_next_pc);
        has_expected_next_pc = true;

        bool diverged = false;

        for (const auto& r : REG_MAP) {
            u32 llarm_val = emu.read_reg(r.reg_id);
            u32 uc_val = 0;
            uc_reg_read(uc, r.uc_reg_id, &uc_val);

            if (r.reg_id == llarm::emu::reg_CPSR) {
                llarm_val &= CPSR_MASK;
                uc_val &= CPSR_MASK;
            }

            if (llarm_val != uc_val) {
                if (!diverged) {
                    fprintf(stderr, "[%u] 0x%08X  op=0x%08X  id=%-30s  %s\n", step, pc, opcode, id_str.c_str(), disasm.c_str());
                    fprintf(stderr, "\033[31mDIVERGENCE\033[0m\n");
                    diverged = true;
                }
                fprintf(stderr, "  \033[31m%-4s  llarm=0x%08X  unicorn=0x%08X\033[0m\n", r.name, llarm_val, uc_val);
            }
        }

        for (const auto& w : mem_writes) {
            // Skip MMIO addresses, they're above RAM and handled by LLARM peripherals,
            // not stored in physical memory, so read_physical_mem would return 0.
            if (w.address >= static_cast<u32>(settings.memsize)) {
                continue;
            }

            u64 llarm_val = 0;
            switch (w.size) {
                case 1: llarm_val = emu.read_physical_mem<u8>(w.address);  break;
                case 2: llarm_val = emu.read_physical_mem<u16>(w.address); break;
                case 4: llarm_val = emu.read_physical_mem<u32>(w.address); break;
                case 8: llarm_val = emu.read_physical_mem<u64>(w.address); break;
                default: break;
            }

            const u64 mask    = (w.size < 8) ? ((1ULL << (w.size * 8)) - 1ULL) : ~0ULL;
            const u64 uc_val  = static_cast<u64>(w.value) & mask;
            llarm_val        &= mask;

            if (llarm_val != uc_val) {
                if (!diverged) {
                    fprintf(stderr, "[%u] 0x%08X  op=0x%08X  id=%-30s  %s\n", step, pc, opcode, id_str.c_str(), disasm.c_str());
                    fprintf(stderr, "\033[31mDIVERGENCE\033[0m\n");
                    diverged = true;
                }
                fprintf(stderr, "  \033[31mMEM[0x%08X] size=%u  llarm=0x%llX  unicorn=0x%llX\033[0m\n",
                    w.address, w.size, (unsigned long long)llarm_val, (unsigned long long)uc_val);
            }
        }

        mem_writes.clear();

        if (diverged) {
            halt_and_exit(emu, 1);
        }

        if (step % 10000 == 0) {
            printf("[%u] PC=0x%08X  OK\n", step, pc);
            fflush(stdout);
        }

        prev_step_num = step;
        prev_step_pc = pc;
        prev_step_opcode = opcode;
        prev_step_id_str = id_str;
        prev_step_disasm = disasm;

        emu.next_instruction();
        wait_for_execution(emu);
    }
}