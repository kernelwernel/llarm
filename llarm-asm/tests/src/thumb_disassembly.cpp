
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

    llarm::as::settings settings = setup(binary, argc, argv, THUMB);

    using namespace llarm::as;

    // these are bypassed because capstone would convert these instructions
    // to the equivalent ARM instructions instead, it doesn't have an option
    // to ACTUALLY disassemble into the raw thumb instruction itself
    // these are bypassed because capstone decodes them as newer-ISA instructions
    // that LLARM's target architecture doesn't support (e.g. ARMv6T2+)
    std::vector<const char*> capstone_bypass_list = {
        "cbz",
        "sxth",
        "sxtb",
        "uxth",
        "uxtb",
        "setend",
        "cpsie",
        "cpsid",
        "cbnz",
        "rev",
        "it",
        "yield",
        "wfe",
        "wfi",
        "sev",
        "hint"
    };


    std::vector<thumb_id> bypass_list = {
        thumb_id::LSL1,
        thumb_id::NEG,
        thumb_id::MUL,
        thumb_id::ADD4,
        thumb_id::LSR1,
        thumb_id::ASR1,
        thumb_id::BX,
        thumb_id::BLX2,
        thumb_id::STR1,
        thumb_id::LDR1,
        thumb_id::STRB1,
        thumb_id::LDRB1,
        thumb_id::STRH1,
        thumb_id::LDRH1,
        thumb_id::STR3,
        thumb_id::LDR4,
        thumb_id::ADD5,
        thumb_id::STMIA,
        thumb_id::LDMIA
    };
    // ^ remove once arm equivalent conversion feature is implemented TODO


    for (u32 i = 0; i < 0xFF'FF'FF'FF; i++) {
        //const u32 tmp_binary = reverse_bits32(binary);
        const std::string& llarm_disassembly = llarm::as::disassemble_thumb(binary, PC, settings);
        const std::string& capstone_disassembly = capstone_thumb_disassembler(binary);

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

        if (remove_mnemonic_s(capstone_disassembly) == llarm_disassembly) {
            binary++;
            continue;
        }

        if (llarm_disassembly == "undefined" && capstone_disassembly == "error") {
            binary++;
            continue;
        }

        // this is a nop, introduced in armv6
        if (binary == 0x0000BF00) {
            binary++;
            continue;
        }

        const thumb_id id = llarm::as::identify_thumb(binary);

        bool bypassed = false;
        for (const auto inst : bypass_list) {
            if (id == inst) { bypassed = true; break; }
        }
        if (bypassed) { binary++; continue; }

        if (!bypassed) {
            for (const auto mnemonic : capstone_bypass_list) {
                if (capstone_disassembly.starts_with(mnemonic)) { bypassed = true; break; }
            }
        }
        if (bypassed) { binary++; continue; }


        std::cout << "\033[A\033[2K current checkpoint: " << binary << "\n" << std::flush;

        std::cout << red << "\n===== DISASSEMBLY MISMATCH FOUND =====" << ansi_exit << "\n\n";

        std::cout << "int:    " << binary << "\n" << \
        "binary: " << std::bitset<32>(binary) << "\n" << \
        "hex:    " << std::format("0x{:08X}\n", binary) << "\n";

        std::cout << "instruction: " << llarm::as::thumb_id_to_string(id) << "\n\n";

        if (!is_size_exact) {
            std::cout << "size mismatch: \nLLARM (" << llarm_size << ") => capstone (" << cap_size << ")\n\n";
        }

        const std::string& mismatch_str = highlight_mismatch(llarm_disassembly, capstone_disassembly);

        std::cout << mismatch_str << "\n\n";

        std::cout << "LLARM:    " << bold << llarm_disassembly << "\n" << ansi_exit << \
        "capstone: " << bold << capstone_disassembly << "\n" << ansi_exit << "\n\n";

        // save result to file 
        std::ofstream checkpoint_file("checkpoint_thumb.txt");
        checkpoint_file << binary << std::endl;
        checkpoint_file.close();
        
        break;
    }
    
    return 0;
}