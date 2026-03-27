
#include "constants.hpp"
#include "src/id/shifter_id.hpp"
#include <llarm/llarm-asm.hpp>
#include <llarm/shared/types.hpp>

#include <capstone/capstone.h>

#include <cstring>
#include <format>
#include <fstream>

static constexpr bool ARM = true;
static constexpr bool THUMB = false;

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


inline std::string remove_mnemonic_s(const std::string& inst) {
    const size_t space = inst.find(' ');
    const size_t mnemonic_end = (space == std::string::npos) ? inst.size() : space;
    if (mnemonic_end > 0 && inst[mnemonic_end - 1] == 's')
        return inst.substr(0, mnemonic_end - 1) + inst.substr(mnemonic_end);
    return inst;
}


inline bool does_checkpoint_file_exist(const bool is_arm) {
    std::ifstream f(is_arm ? "checkpoint.txt" : "checkpoint_thumb.txt");
    return f.good();
}

llarm::as::settings setup(u32& binary, int argc, char* argv[], const bool is_arm) {
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

    if (argc == 2) {
        if (std::strcmp(argv[1], "--reset") == 0) {
            binary = 0;
        }
    } else {
        if (does_checkpoint_file_exist(is_arm)) {
            std::ifstream f((is_arm ? "checkpoint.txt" : "checkpoint_thumb.txt"));
    
            if (!f.is_open()) {
                std::cerr << "Error opening the file!";
                std::exit(1);
            }
            std::string s;
    
            getline(f, s);
            binary = static_cast<u32>(std::stoi(s));
        }
    }


    std::cout << "current checkpoint: " << 0 << "\n" << std::flush;
    
    return settings;
}