#include <llarm/llarm-emu.hpp>
#include <llarm/llarm-asm.hpp>
#include "src/device-tree/dtb.hpp"
#include "src/settings.hpp"

#include <unicorn/unicorn.h>

#include <array>
#include <cstdio>
#include <cstdlib>

static constexpr u32 CPSR_MASK = 0xF80F03FFU; // flags + mode + I/F/T

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
    // Phase 1: wait for execution_done to reset (CPU started new cycle)
    while (emu.cpu.core.execution_done.load(std::memory_order_acquire)) {}
    // Phase 2: wait for execution_done to set (CPU finished executing)
    while (!emu.cpu.core.execution_done.load(std::memory_order_acquire)) {}
}

static void halt_and_exit(llarm::emu::cpu_blockstep& emu, int code) {
    emu.cpu.core.is_halted = true;
    emu.next_instruction();
    exit(code);
}

static uc_engine* setup_unicorn(const SETTINGS& s, const std::vector<u8>& binary) {
    uc_engine* uc = nullptr;
    uc_must(uc_open(UC_ARCH_ARM, UC_MODE_ARM, &uc), "uc_open");
    uc_must(uc_ctl_set_cpu_model(uc, UC_CPU_ARM_926), "set cpu ARM926");
    // Map the full 32-bit address space so all reads return 0 for unmapped areas,
    // matching LLARM's RAM model which silently returns 0 for out-of-range accesses.
    uc_must(uc_mem_map(uc, 0, 0x100000000ULL, UC_PROT_ALL), "uc_mem_map");

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

    const SETTINGS settings = linux_settings();

    llarm::emu::cpu_blockstep emu(binary_path, settings);
    emu.run();

    // Wait for the first instruction to finish executing
    while (!emu.cpu.core.execution_done.load(std::memory_order_acquire)) {}

    // QEMU's boot stub initialises SP to the top of RAM before jumping to the kernel.
    // The Linux decompressor computes its relocation target as (sp - image_size), so
    // without this the subtraction underflows and the copy loop accesses ~0xFFFFFFE0.
    // We patch SP here (after run() has finished its own register init) while the CPU is paused.
    emu.write_reg(llarm::emu::reg_CPSR, 0xD3U); // ensure valid SVC mode for the SP dispatch
    emu.write_reg(llarm::emu::reg_SP, static_cast<u32>(settings.memsize));

    uc_engine* uc = setup_unicorn(settings, emu.binary);

    for (u32 step = 0; ; step++) {
        const u32 pc = emu.current_pc();

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

        const uc_err err = uc_emu_start(uc, pc, 0, 0, 1);

        if (err != UC_ERR_OK) {
            fprintf(stderr, "[%u] 0x%08X  op=0x%08X  id=%-30s  %s\n",
                step, pc, opcode, id_str.c_str(), disasm.c_str());
            fprintf(stderr, "\033[31m[%u] unicorn fault at PC=0x%08X: %s\033[0m\n", step, pc, uc_strerror(err));
            fprintf(stderr, "  register state at fault:\n");

            for (const auto& r : REG_MAP) {
                fprintf(stderr, "  %-4s  llarm=0x%08X\n", r.name, emu.read_reg(r.reg_id));
            }

            halt_and_exit(emu, 1);
        }

        bool diverged = false;

        for (const auto& r : REG_MAP) {
            u32 llarm_val = emu.read_reg(r.reg_id);
            u32 uc_val    = 0;
            uc_reg_read(uc, r.uc_reg_id, &uc_val);

            if (r.reg_id == llarm::emu::reg_CPSR) {
                llarm_val &= CPSR_MASK;
                uc_val    &= CPSR_MASK;
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

        if (diverged) {
            halt_and_exit(emu, 1);
        }

        if (step % 1000 == 0) {
            printf("[%u] PC=0x%08X  OK\n", step, pc);
            fflush(stdout);
        }

        emu.next_instruction();
        wait_for_execution(emu);
    }
}