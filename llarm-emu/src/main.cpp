#include <cstring>
#include <iostream>
#include <array>
#include <string>
#include <span>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cinttypes>
#include <chrono>
#include <thread>

#include <llarm/shared/types.hpp>
#include <llarm/shared/out.hpp>
#include <llarm/shared/metadata.hpp>

#include <llarm/llarm-emu.hpp>
#include <llarm/llarm-asm.hpp>


// NOLINTBEGIN(cppcoreguidelines-use-enum-class)
enum arg_enum : u8 {
    NULL_ARG,
    HELP,
    VERSION,
    RUN,
    STEP,
    ARM,
    THUMB,
    REGS,
    REG,
    MEM,
    END
};
// NOLINTEND(cppcoreguidelines-use-enum-class)


[[noreturn]] void help() {
    std::cout <<
R"(Usage:
 llarm-emu [option(s)] <binary>

Options:
 -h | --help          print this help menu
 -v | --version       print CLI version and other details
 -r | --run           run binary headlessly (default)
 -s | --step          interactive step-by-step execution
 -a | --arm           start in ARM mode (default)
 -t | --thumb         start in Thumb mode
    | --regs          print all registers at each step or after run
    | --reg <name>    print a specific register (e.g. R0, SP, PC, CPSR)
    | --mem <addr>    read physical memory (e.g. 0x1000 or 0x1000:u8)

 (no mode flag)         defaults to --run

Examples:
 llarm-emu program.bin
 llarm-emu --run program.bin
 llarm-emu --step --thumb program.bin
 llarm-emu --step --regs program.bin
 llarm-emu --reg PC --mem 0x1000:u32 program.bin

)";
    std::exit(0);
}

using namespace llarm::emu;

static constexpr std::array<std::pair<const char*, llarm::emu::reg>, 30> reg_table {{
    { "R0",       reg_R0 },
    { "R1",       reg_R1 },
    { "R2",       reg_R2 },
    { "R3",       reg_R3 },
    { "R4",       reg_R4 },
    { "R5",       reg_R5 },
    { "R6",       reg_R6 },
    { "R7",       reg_R7 },
    { "R8",       reg_R8 },
    { "R9",       reg_R9 },
    { "R10",      reg_R10 },
    { "R11",      reg_R11 },
    { "R12",      reg_R12 },
    { "R13",      reg_R13 },
    { "R14",      reg_R14 },
    { "R15",      reg_R15 },
    { "SP",       reg_SP },
    { "LR",       reg_LR },
    { "PC",       reg_PC },
    { "IP",       reg_IP },
    { "CPSR",     reg_CPSR },
    { "SPSR",     reg_SPSR },
    { "SPSR_svc", reg_SPSR_svc },
    { "SPSR_abt", reg_SPSR_abt },
    { "SPSR_und", reg_SPSR_und },
    { "SPSR_irq", reg_SPSR_irq },
    { "SPSR_fiq", reg_SPSR_fiq },
    { "R8_fiq",   reg_R8_fiq },
    { "R9_fiq",   reg_R9_fiq },
    { "R10_fiq",  reg_R10_fiq },
}};


static void print_all_regs(llarm::emu::cpu_blockstep &cpu) {
    static constexpr std::array<std::pair<const char*, llarm::emu::reg>, 20> display_regs {{
        { "R0",   reg_R0   },
        { "R1",   reg_R1   },
        { "R2",   reg_R2   },
        { "R3",   reg_R3   },
        { "R4",   reg_R4   },
        { "R5",   reg_R5   },
        { "R6",   reg_R6   },
        { "R7",   reg_R7   },
        { "R8",   reg_R8   },
        { "R9",   reg_R9   },
        { "R10",  reg_R10  },
        { "R11",  reg_R11  },
        { "R12",  reg_R12  },
        { "SP",   reg_SP   },
        { "LR",   reg_LR   },
        { "PC",   reg_PC   },
        { "CPSR", reg_CPSR },
        { "SPSR", reg_SPSR },
    }};

    for (std::size_t i = 0; i < display_regs.size(); i += 4) {
        for (std::size_t j = i; j < std::min(i + 4, display_regs.size()); ++j) {
            const auto &[name, id] = display_regs.at(j);
            std::printf("  %-5s=0x%08X", name, cpu.read_reg(id));
        }
        std::printf("\n");
    }
}


static void print_one_reg(llarm::emu::cpu_blockstep &cpu, const std::string &name) {
    const std::string upper = [&] {
        std::string s = name;
        std::transform(s.begin(), s.end(), s.begin(), ::toupper);
        return s;
    }();

    auto it = std::find_if(reg_table.cbegin(), reg_table.cend(), [&](const auto &p) {
        return upper == p.first;
    });

    if (it == reg_table.cend()) {
        llarm::out::error("llarm-emu: unknown register \"", name, "\"");
    }

    std::printf("  %s=0x%08X\n", it->first, cpu.read_reg(it->second));
}


struct mem_request {
    u32 address = 0;
    u8  width   = 4; // bytes: 1, 2, 4, 8
    bool valid  = false;
};


static mem_request parse_mem_arg(const std::string &arg) {
    mem_request req;

    // format: ADDRESS or ADDRESS:uN  (u8, u16, u32, u64)
    const std::size_t colon = arg.find(':');
    const std::string addr_part = arg.substr(0, colon);

    char *end = nullptr;
    req.address = static_cast<u32>(std::strtoul(addr_part.c_str(), &end, 0));

    if (end == addr_part.c_str() || *end != '\0') {
        return req; // invalid address
    }

    if (colon != std::string::npos) {
        const std::string type_part = arg.substr(colon + 1);
        if      (type_part == "u8")  { req.width = 1; }
        else if (type_part == "u16") { req.width = 2; }
        else if (type_part == "u32") { req.width = 4; }
        else if (type_part == "u64") { req.width = 8; }
        else {
            return req; // invalid type
        }
    }

    req.valid = true;
    return req;
}


static void print_mem(llarm::emu::cpu_blockstep &cpu, const mem_request &req) {
    switch (req.width) {
        case 1: std::printf("  [0x%08X] = 0x%02X\n",   req.address, cpu.read_physical_mem<u8>(req.address));  break;
        case 2: std::printf("  [0x%08X] = 0x%04X\n",   req.address, cpu.read_physical_mem<u16>(req.address)); break;
        case 4: std::printf("  [0x%08X] = 0x%08X\n",   req.address, cpu.read_physical_mem<u32>(req.address)); break;
        case 8: std::printf("  [0x%08X] = 0x%016" PRIx64 "\n", req.address, cpu.read_physical_mem<u64>(req.address)); break;
    }
}


static void run_step_mode(
    llarm::emu::cpu_blockstep &cpu,
    const bool show_regs,
    const std::string &reg_arg,
    const mem_request &mem_req
) {
    cpu.run();

    // give the CPU thread time to execute the first instruction and reach the spin-wait
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    u64 step = 0;

    while (true) {
        const bool is_thumb = cpu.is_thumb_mode();
        const u32  pc       = cpu.read_reg(reg_PC);

        if (is_thumb) {
            const u16 code = cpu.current_thumb_code();
            const llarm::as::settings cfg = llarm::as::default_settings();
            const std::string mnemonic = llarm::as::disassemble_thumb(code, pc, cfg);
            std::printf("[%4" PRIu64 "] PC=0x%08X  THUMB: %s (0x%04X)\n", step, pc, mnemonic.c_str(), code);
        } else {
            const u32 code = cpu.current_arm_code();
            const llarm::as::settings cfg = llarm::as::default_settings();
            const std::string mnemonic = llarm::as::disassemble_arm(code, pc, cfg);
            std::printf("[%4" PRIu64 "] PC=0x%08X  ARM: %s (0x%08X)\n", step, pc, mnemonic.c_str(), code);
        }

        if (show_regs) {
            print_all_regs(cpu);
        }

        if (!reg_arg.empty()) {
            print_one_reg(cpu, reg_arg);
        }

        if (mem_req.valid) {
            print_mem(cpu, mem_req);
        }

        std::printf("> [Enter]=step  [q]=quit\n");

        const int ch = std::getchar();

        if (ch == 'q' || ch == 'Q') {
            break;
        }

        // consume any remaining characters on the line
        if (ch != '\n') {
            while (std::getchar() != '\n') {}
        }

        cpu.next_instruction();
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        ++step;
    }
}


int main(int argc, char* argv[]) {
    const std::span<char*> args(argv + 1, static_cast<std::size_t>(argc - 1));
    const u32 arg_count = static_cast<u32>(argc - 1);

    constexpr u8 arg_bits = static_cast<u8>(END) + 1;
    std::bitset<arg_bits> arg_bitset;

    if (arg_count == 0) {
        help();
        return 0;
    }

    static constexpr std::array<std::pair<const char*, arg_enum>, 15> table {{
        { "-h",      HELP    },
        { "--help",  HELP    },
        { "-v",      VERSION },
        { "--version", VERSION },
        { "-r",      RUN     },
        { "--run",   RUN     },
        { "-s",      STEP    },
        { "--step",  STEP    },
        { "-a",      ARM     },
        { "--arm",   ARM     },
        { "-t",      THUMB   },
        { "--thumb", THUMB   },
        { "--regs",  REGS    },
        { "--reg",   REG     },
        { "--mem",   MEM     },
    }};

    std::string binary_path;
    std::string reg_arg;
    std::string mem_arg;
    std::string potential_null_arg;

    for (auto arg_it = args.begin(); arg_it != args.end(); ++arg_it) {
        auto it = std::find_if(table.cbegin(), table.cend(), [&](const auto &p) {
            return (std::strcmp(*arg_it, p.first) == 0);
        });

        const auto next = std::next(arg_it);

        if (it == table.cend()) {
            if (!binary_path.empty()) {
                arg_bitset.set(NULL_ARG);
                potential_null_arg = *arg_it;
            } else {
                binary_path = *arg_it;
            }
        } else {
            arg_bitset.set(it->second);

            if (it->second == REG) {
                if (next != args.end() && (*next)[0] != '-') {
                    reg_arg = *++arg_it;
                } else {
                    llarm::out::error("llarm-emu: --reg requires a register name");
                }
            } else if (it->second == MEM) {
                if (next != args.end() && (*next)[0] != '-') {
                    mem_arg = *++arg_it;
                } else {
                    llarm::out::error("llarm-emu: --mem requires an address (e.g. 0x1000 or 0x1000:u32)");
                }
            }
        }
    }

    if (arg_bitset.test(NULL_ARG)) {
        llarm::out::error("llarm-emu: unknown argument \"", potential_null_arg, "\"");
    }

    if (arg_bitset.test(HELP)) {
        help();
    }

    if (arg_bitset.test(VERSION)) {
        llarm::metadata::version(
            "llarm-emu",
            llarm::metadata::LLARM_EMU_VER,
            llarm::metadata::LLARM_EMU_DATE
        );
    }

    if (arg_bitset.test(RUN) && arg_bitset.test(STEP)) {
        llarm::out::error("llarm-emu: --run and --step are mutually exclusive");
    }

    if (arg_bitset.test(ARM) && arg_bitset.test(THUMB)) {
        llarm::out::error("llarm-emu: --arm and --thumb are mutually exclusive");
    }

    if (arg_bitset.test(REGS) && !arg_bitset.test(STEP)) {
        llarm::out::error("llarm-emu: --regs requires --step mode");
    }

    if (arg_bitset.test(REG) && !arg_bitset.test(STEP)) {
        llarm::out::error("llarm-emu: --reg requires --step mode");
    }

    if (arg_bitset.test(MEM) && !arg_bitset.test(STEP)) {
        llarm::out::error("llarm-emu: --mem requires --step mode");
    }

    if (binary_path.empty()) {
        llarm::out::error("llarm-emu: no binary file provided");
    }

    if (!std::filesystem::exists(binary_path)) {
        llarm::out::error("llarm-emu: file not found: \"", binary_path, "\"");
    }

    mem_request mem_req;
    if (arg_bitset.test(MEM)) {
        mem_req = parse_mem_arg(mem_arg);
        if (!mem_req.valid) {
            llarm::out::error("llarm-emu: invalid --mem argument \"", mem_arg, "\" (expected e.g. 0x1000 or 0x1000:u32)");
        }
    }

    const std::size_t binary_size = std::filesystem::file_size(binary_path);
    std::printf("llarm-emu: loaded \"%s\" (%zu bytes)\n", binary_path.c_str(), binary_size);

    // step mode
    if (arg_bitset.test(STEP)) {
        llarm::emu::cpu_blockstep cpu(binary_path);
        run_step_mode(cpu, arg_bitset.test(REGS), reg_arg, mem_req);
        return 0;
    }

    // headless run (default)
    llarm::emu::cpu_headless cpu(binary_path);
    cpu.run();

    return 0;
}