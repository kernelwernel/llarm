
#include "constants.hpp"
#include "disassembler.hpp"
#include <llarm/llarm-asm.hpp>
#include <llarm/shared/types.hpp>

#include <capstone/capstone.h>

#include <cstring>
#include <format>
#include <fstream>


std::string highlight_mismatch(const std::string& a, const std::string& b) {
    std::string result;
    const size_t len = std::max(a.size(), b.size());

    for (size_t i = 0; i < len; i++) {
        const char ca = i < a.size() ? a[i] : '?';
        const char cb = i < b.size() ? b[i] : '?';

        if (ca != cb) {
            result += red;
            result += bold;
            result += ca;
            result += ansi_exit;
        } else {
            result += ca;
        }
    }

    return result;
}


unsigned int reverse_bits32(unsigned int v) {
    v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1);
    v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2);
    v = ((v >> 4) & 0x0F0F0F0F) | ((v & 0x0F0F0F0F) << 4);
    v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8);
    v = (v >> 16) | (v << 16);
    return v;
}



inline bool does_checkpoint_file_exist() {
    std::ifstream f("checkpoint.txt");
    return f.good();
}


std::string fetch_shifter(const u32 code) {
    switch (llarm::as::identify_shifter(code)) {
        case shifter_id::UNKNOWN: return "UNKNOWN";
        case shifter_id::NONE: return "NONE";
        case shifter_id::DATA_IMM: return "DATA_IMM";
        case shifter_id::DATA_RRX: return "DATA_RRX";
        case shifter_id::DATA_REG: return "DATA_REG";
        case shifter_id::DATA_IMM_LSL: return "DATA_IMM_LSL";
        case shifter_id::DATA_IMM_LSR: return "DATA_IMM_LSR";
        case shifter_id::DATA_IMM_ASR: return "DATA_IMM_ASR";
        case shifter_id::DATA_IMM_ROR: return "DATA_IMM_ROR";
        case shifter_id::DATA_REG_LSL: return "DATA_REG_LSL";
        case shifter_id::DATA_REG_LSR: return "DATA_REG_LSR";
        case shifter_id::DATA_REG_ASR: return "DATA_REG_ASR";
        case shifter_id::DATA_REG_ROR: return "DATA_REG_ROR";
        case shifter_id::LS_IMM: return "LS_IMM";
        case shifter_id::LS_IMM_PRE: return "LS_IMM_PRE";
        case shifter_id::LS_IMM_POST: return "LS_IMM_POST";
        case shifter_id::LS_REG: return "LS_REG";
        case shifter_id::LS_REG_PRE: return "LS_REG_PRE";
        case shifter_id::LS_REG_POST: return "LS_REG_POST";
        case shifter_id::LS_SCALED_LSL: return "LS_SCALED_LSL";
        case shifter_id::LS_SCALED_LSR: return "LS_SCALED_LSR";
        case shifter_id::LS_SCALED_ASR: return "LS_SCALED_ASR";
        case shifter_id::LS_SCALED_ROR: return "LS_SCALED_ROR";
        case shifter_id::LS_SCALED_RRX: return "LS_SCALED_RRX";
        case shifter_id::LS_SCALED_PRE_LSL: return "LS_SCALED_PRE_LSL";
        case shifter_id::LS_SCALED_PRE_LSR: return "LS_SCALED_PRE_LSR";
        case shifter_id::LS_SCALED_PRE_ASR: return "LS_SCALED_PRE_ASR";
        case shifter_id::LS_SCALED_PRE_ROR: return "LS_SCALED_PRE_ROR";
        case shifter_id::LS_SCALED_PRE_RRX: return "LS_SCALED_PRE_RRX";
        case shifter_id::LS_SCALED_POST_LSL: return "LS_SCALED_POST_LSL";
        case shifter_id::LS_SCALED_POST_LSR: return "LS_SCALED_POST_LSR";
        case shifter_id::LS_SCALED_POST_ASR: return "LS_SCALED_POST_ASR";
        case shifter_id::LS_SCALED_POST_ROR: return "LS_SCALED_POST_ROR";
        case shifter_id::LS_SCALED_POST_RRX: return "LS_SCALED_POST_RRX";
        case shifter_id::LS_MISC_IMM: return "LS_MISC_IMM";
        case shifter_id::LS_MISC_IMM_PRE: return "LS_MISC_IMM_PRE";
        case shifter_id::LS_MISC_IMM_POST: return "LS_MISC_IMM_POST";
        case shifter_id::LS_MISC_REG: return "LS_MISC_REG";
        case shifter_id::LS_MISC_REG_PRE: return "LS_MISC_REG_PRE";
        case shifter_id::LS_MISC_REG_POST: return "LS_MISC_REG_POST";
        case shifter_id::LS_MUL_INC_AFTER: return "LS_MUL_INC_AFTER";
        case shifter_id::LS_MUL_INC_BEFORE: return "LS_MUL_INC_BEFORE";
        case shifter_id::LS_MUL_DEC_AFTER: return "LS_MUL_DEC_AFTER";
        case shifter_id::LS_MUL_DEC_BEFORE: return "LS_MUL_DEC_BEFORE";
        case shifter_id::LS_COPROC_IMM: return "LS_COPROC_IMM";
        case shifter_id::LS_COPROC_IMM_PRE: return "LS_COPROC_IMM_PRE";
        case shifter_id::LS_COPROC_IMM_POST: return "LS_COPROC_IMM_POST";
        case shifter_id::LS_COPROC_UNINDEXED: return "LS_COPROC_UNINDEXED";
        case shifter_id::VFP_SINGLE: return "VFP_SINGLE";
        case shifter_id::VFP_SINGLE_SCALAR: return "VFP_SINGLE_SCALAR";
        case shifter_id::VFP_SINGLE_MIXED: return "VFP_SINGLE_MIXED";
        case shifter_id::VFP_SINGLE_VECTOR: return "VFP_SINGLE_VECTOR";
        case shifter_id::VFP_SINGLE_MONADIC: return "VFP_SINGLE_MONADIC";
        case shifter_id::VFP_SINGLE_MONADIC_SCALAR_TO_SCALAR: return "VFP_SINGLE_MONADIC_SCALAR_TO_SCALAR";
        case shifter_id::VFP_SINGLE_MONADIC_SCALAR_TO_VECTOR: return "VFP_SINGLE_MONADIC_SCALAR_TO_VECTOR";
        case shifter_id::VFP_SINGLE_MONADIC_VECTOR_TO_VECTOR: return "VFP_SINGLE_MONADIC_VECTOR_TO_VECTOR";
        case shifter_id::VFP_DOUBLE: return "VFP_DOUBLE";
        case shifter_id::VFP_DOUBLE_SCALAR: return "VFP_DOUBLE_SCALAR";
        case shifter_id::VFP_DOUBLE_MIXED: return "VFP_DOUBLE_MIXED";
        case shifter_id::VFP_DOUBLE_VECTOR: return "VFP_DOUBLE_VECTOR";
        case shifter_id::VFP_DOUBLE_MONADIC: return "VFP_DOUBLE_MONADIC";
        case shifter_id::VFP_DOUBLE_MONADIC_SCALAR_TO_SCALAR: return "VFP_DOUBLE_MONADIC_SCALAR_TO_SCALAR";
        case shifter_id::VFP_DOUBLE_MONADIC_SCALAR_TO_VECTOR: return "VFP_DOUBLE_MONADIC_SCALAR_TO_VECTOR";
        case shifter_id::VFP_DOUBLE_MONADIC_VECTOR_TO_VECTOR: return "VFP_DOUBLE_MONADIC_VECTOR_TO_VECTOR";
        case shifter_id::VFP_LS_MUL: return "VFP_LS_MUL";
        case shifter_id::VFP_LS_MUL_UNINDEXED: return "VFP_LS_MUL_UNINDEXED";
        case shifter_id::VFP_LS_MUL_INC: return "VFP_LS_MUL_INC";
        case shifter_id::VFP_LS_MUL_DEC: return "VFP_LS_MUL_DEC";
        case shifter_id::VFP_LS_MUL_SPECIAL: return "VFP_LS_MUL_SPECIAL";
    }
}



int main(int argc, char* argv[]) {
    u32 binary = 0;

    llarm::as::settings settings = {};
    settings.capitals = false;
    settings.register_alias = true;
    settings.register_alias = true;
    settings.cond_always_suffix = true;
    settings.explicit_operands = true;
    settings.strict_compliance = false;
    settings.hex = true;
    settings.equivalent_alias = true;
    settings.remove_nulls = true;
    settings.explicit_rotation = true;

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

    if (argc == 2) {
        if (std::strcmp(argv[1], "--reset") == 0) {
            binary = 0;
        }
    } else {
        if (does_checkpoint_file_exist()) {
            std::ifstream f("checkpoint.txt");
    
            if (!f.is_open()) {
                std::cerr << "Error opening the file!";
                return 1;
            }
            std::string s;
    
            getline(f, s);
            binary = static_cast<u32>(std::stoi(s));
        }
    }


    std::cout << "current checkpoint: " << 0 << "\n" << std::flush;

    for (u32 i = 0; i < 0xFF'FF'FF'FF; i++) {
        //const u32 tmp_binary = reverse_bits32(binary);
        const std::string& llarm_disassembly = llarm::as::disassemble_arm(binary, PC, settings);
        const std::string& capstone_disassembly = capstone_arm_disassembler(binary);

        const size_t cap_size = capstone_disassembly.size();
        const size_t llarm_size = llarm_disassembly.size();

        const bool is_size_exact = (cap_size == llarm_size);

        if (binary % (1 << 16) == 0) {
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
        std::cout << "shifter: " << fetch_shifter(binary) << "\n\n";

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