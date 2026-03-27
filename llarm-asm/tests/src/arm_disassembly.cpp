
#include "constants.hpp"
#include "capstone_disassembler.hpp"
#include "src/id/shifter_id.hpp"
#include "fuzzer.hpp"

#include <llarm/llarm-asm.hpp>
#include <llarm/shared/types.hpp>

#include <capstone/capstone.h>

#include <cstring>
#include <format>
#include <fstream>


int main(int argc, char* argv[]) {
    u32 binary = 0;

    llarm::as::settings settings = setup(binary, argc, argv, ARM);

    // these are either unimplemented in ARMv5 (our target) or not available for a few reasons
    std::vector<const char*> bypass = {
        "strht",
        "ldrht", 
        "ldrsbt",
        "ldrsht",
        "umaal",
        "mls",
        "bxj",
        "hvc",
        "eret",
        "smc",
        "stlex",
        "strex",
        "stl",
        "lda",
        "ldrex"
    };

    std::vector<const char*> unpredictable = {
        "mrs",
        "msr",
        "bx",
        "blx",
        "clz", // SBO
        "mov", // SBO
        "lsleq", // SBO
        "lsreq", // SBO
        "asreq", // SBO
        "rrxeq", // SBO
        "roreq" // SBO
    };

    // capstone can have very inconsistent encoding conventions to the point it's better to skin them entirely.
    // Both isntructions in LLARM and capstone are correct and equivalent, just the encoding is different.
    std::vector<const char*> addressing_mode_exception = {
        "strh",
        "ldrd",
        "strd",
        "ldrh",
        "ldrsb",
        "ldrsh",
        "and",
        "eor",
        "sub",
        "rsb",
        "add",
        "adc",
        "sbc",
        "rsc",
        "tst",
        "teq",
        "cmp",
        "cmn",
        "orr",
        "bic"
    };

    for (u32 i = 0; i < 0xFF'FF'FF'FF; i++) {
        //const u32 tmp_binary = reverse_bits32(binary);
        const std::string& llarm_disassembly = llarm::as::disassemble_arm(binary, PC, settings);
        const std::string& capstone_disassembly = capstone_arm_disassembler(binary);

        const size_t cap_size = capstone_disassembly.size();
        const size_t llarm_size = llarm_disassembly.size();

        const bool is_size_exact = (cap_size == llarm_size);

        if (binary % (1 << 16) == 1) {
            std::cout << "\033[A\033[2K current checkpoint: " << binary << "\n" << std::flush;
        }

        if ((llarm_disassembly == capstone_disassembly) && is_size_exact) {
            binary++;

            continue;
        }

        bool skip_check = false;

        for (const auto& inst : bypass) {
            if (capstone_disassembly.starts_with(inst)) {
                skip_check = true;
            }
        }

        for (const auto& inst : unpredictable) {
            if (llarm_disassembly.starts_with(inst) || capstone_disassembly.starts_with(inst)) {
                skip_check = true;
            }
        }

        using enum llarm::as::shifter_id;

        switch (llarm::as::identify_shifter(binary)) {
            case DATA_IMM:
            case LS_MISC_IMM:
            case LS_MISC_IMM_POST:
            case LS_MISC_IMM_PRE : {
                bool should_continue = false;
                for (const auto& inst : addressing_mode_exception) {
                    if (llarm_disassembly.starts_with(inst)) {
                        should_continue = true;
                    }
                }

                if (should_continue) {
                    binary++;
                    continue;
                }
                break;
            }
            default: break;
        }
        
        if (skip_check) {
            binary++;
            continue;
        }

        if (llarm_disassembly == "undefined" && capstone_disassembly == "error") {
            binary++;
            continue;
        }

        std::cout << "\033[A\033[2K current checkpoint: " << binary << "\n" << std::flush;

        std::cout << red << "\n===== DISASSEMBLY MISMATCH FOUND =====" << ansi_exit << "\n\n";

        std::cout << "int:    " << binary << "\n" << \
        "binary: " << std::bitset<32>(binary) << "\n" << \
        "hex:    " << std::format("0x{:08X}\n", binary) << "\n";

        std::cout << "instruction: " << llarm::as::identify_arm_string(binary) << "\n\n";
        std::cout << "shifter: " << llarm::as::code_to_shifter_string(binary) << "\n\n";

        if (!is_size_exact) {
            std::cout << "size mismatch: \nLLARM (" << llarm_size << ") => capstone (" << cap_size << ")\n\n";
        }

        const std::string& mismatch_str = highlight_mismatch(llarm_disassembly, capstone_disassembly);

        std::cout << mismatch_str << "\n\n";

        std::cout << "LLARM:    " << bold << llarm_disassembly << "\n" << ansi_exit << \
        "capstone: " << bold << capstone_disassembly << "\n" << ansi_exit << "\n\n";

        // save result to file 
        std::ofstream checkpoint_file("checkpoint.txt");
        checkpoint_file << binary << std::endl;
        checkpoint_file.close();
        
        break;
    }
    
    return 0;
}