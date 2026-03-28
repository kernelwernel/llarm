#include <bitset>
#include <cstring>
#include <iostream>
#include <array>
#include <string>
#include <span>
#include <algorithm>
#include <cstdio>

#include <llarm/shared/types.hpp>
#include <llarm/shared/out.hpp>
#include <llarm/shared/metadata.hpp>

#include <llarm/llarm-cpu.hpp>


enum arg_enum : u8 {
    NULL_ARG,
    HELP,
    VERSION,
    END
};


[[noreturn]] void help() {
    std::cout <<
R"(Usage:
 llarm-cpu [option(s)]

Options:
 -h   | --help          print this help menu
 -v   | --version       print CLI version and other details

 (no arguments)         print CPU identification info

)";
    std::exit(0);
}


static void print_cpu_info() {
    const uint32_t midr       = llarm_cpu_fetch_midr();
    const enum product prod   = llarm_cpu_fetch_product();
    const enum arch a         = llarm_cpu_fetch_arch();
    const uint32_t variant    = llarm_cpu_fetch_variant();
    const uint32_t revision   = llarm_cpu_fetch_revision();
    const uint32_t ppn        = llarm_cpu_fetch_ppn();

    std::printf("MIDR        : 0x%08X\n", midr);
    std::printf("Implementor : %s\n",     llarm_cpu_fetch_implementor_string());
    std::printf("Product     : %s\n",     llarm_cpu_fetch_product_string(prod));
    std::printf("Architecture: %s\n",     llarm_cpu_fetch_arch_string(a));
    std::printf("PPN         : 0x%03X\n", ppn);
    std::printf("Variant     : %u\n",     variant);
    std::printf("Revision    : %u\n",     revision);

    if (llarm_cpu_is_pre_arm7()) {
        std::printf("Generation  : pre-ARM7\n");
    } else if (llarm_cpu_is_arm7()) {
        std::printf("Generation  : ARM7\n");
    } else if (llarm_cpu_is_post_arm7()) {
        std::printf("Generation  : post-ARM7\n");
    } else {
        std::printf("Generation  : Unknown\n");
    }
}


int main(int argc, char* argv[]) {
    const std::span<char*> args(argv, static_cast<std::size_t>(argc));
    const u32 arg_count = static_cast<u32>(argc - 1);

    constexpr u8 arg_bits = static_cast<u8>(END) + 1;
    std::bitset<arg_bits> arg_bitset;

    if (arg_count == 0) {
        print_cpu_info();
        return 0;
    }

    static constexpr std::array<std::pair<const char*, arg_enum>, 20> table {{
        { "-h", HELP },
        { "--help", HELP },
        { "-v", VERSION },
        { "--version", VERSION },
    }};

    std::string potential_null_arg;

    for (const auto &arg_string : args) {
        auto it = std::find_if(table.cbegin(), table.cend(), [&](const auto &p) {
            return (arg_string == p.first);
        });

        if (it == table.end()) {
            arg_bitset.set(NULL_ARG);
            potential_null_arg = arg_string;
        } else {
            arg_bitset.set(it->second);
        }
    }

    if (arg_bitset.test(NULL_ARG)) {
        llarm::out::error("llarm-cpu: unknown argument \"", potential_null_arg, "\"");
    }

    if (arg_bitset.test(HELP)) {
        help();
        return 0;
    }

    if (arg_bitset.test(VERSION)) {
        llarm::metadata::version(
            "llarm-cpu",
            llarm::metadata::LLARM_CPU_VER,
            llarm::metadata::LLARM_CPU_DATE
        );
        return 0;
    }
}
