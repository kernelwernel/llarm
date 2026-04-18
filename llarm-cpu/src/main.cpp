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
    MIDR,
    IMPL,
    PROD,
    ARCH,
    PPN,
    VARIANT,
    REVISION,
    IS_ARM,
    END
};


[[noreturn]] void help() {
    std::cout <<
R"(Usage:
 llarm-cpu [option(s)]

Options:
 -h   | --help          print this help menu
 -v   | --version       print CLI version and other details
 -m   | --midr          print raw MIDR field
 -i   | --implementor   print the CPU's implementor
 -p   | --product       print the CPU's product name/brand
 -a   | --arch          print the CPU's architecture model
 -r   | --revision      print the CPU's revision number
 -P   | --ppn           print the CPU's Primary Part Number (PPN)
 -V   | --variant       print the CPU's variant number
 -A   | --is-arm        print 0 or 1 if it's an ARM CPU

 (no arguments)         print CPU identification info

)";
    std::exit(0);
}


static void print_cpu_info() {
    const unsigned int midr     = llarm::cpu::fetch_midr();
    const enum product prod     = llarm::cpu::fetch_product();
    const enum arch a           = llarm::cpu::fetch_arch();
    const unsigned int variant  = llarm::cpu::fetch_variant();
    const unsigned int revision = llarm::cpu::fetch_revision();
    const unsigned int ppn      = llarm::cpu::fetch_ppn();

    std::printf("MIDR        : 0x%08X\n", midr);
    std::printf("Implementor : %s\n",     llarm::cpu::fetch_implementor_string());
    std::printf("Product     : %s\n",     llarm::cpu::fetch_product_string(prod));
    std::printf("Architecture: %s\n",     llarm::cpu::fetch_arch_string(a));
    std::printf("PPN         : 0x%03X\n", ppn);
    std::printf("Variant     : %u\n",     variant);
    std::printf("Revision    : %u\n",     revision);

    if (llarm::cpu::is_pre_arm7()) {
        std::printf("Generation  : pre-ARM7\n");
    } else if (llarm::cpu::is_arm7()) {
        std::printf("Generation  : ARM7\n");
    } else if (llarm::cpu::is_post_arm7()) {
        std::printf("Generation  : post-ARM7\n");
    } else {
        std::printf("Generation  : Unknown\n");
    }
}


int main(int argc, char* argv[]) {
    const std::span<char*> args(argv + 1, static_cast<std::size_t>(argc - 1));
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
        { "-m", MIDR },
        { "--midr", MIDR },
        { "-i", IMPL },
        { "--implementor", IMPL },
        { "-p", PROD },
        { "--product", PROD },
        { "-a", ARCH },
        { "--arch", ARCH },
        { "-P", PPN},
        { "--ppn", PPN },
        { "-V", VARIANT },
        { "--variant", VARIANT },
        { "-r", REVISION },
        { "--revision", REVISION },
        { "-A", IS_ARM },
        { "--is-arm", IS_ARM }
    }};

    std::string potential_null_arg;

    for (const auto &arg_string : args) {
        auto it = std::find_if(table.cbegin(), table.cend(), [&](const auto &p) {
            return (std::strcmp(arg_string, p.first) == 0);
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

    if (arg_bitset.test(MIDR)) {
        std::printf("0x%08X\n", llarm::cpu::fetch_midr());
    }

    if (arg_bitset.test(IMPL)) {
        std::printf("%s\n", llarm::cpu::fetch_implementor_string());
    }

    if (arg_bitset.test(PROD)) {
        std::printf("%s\n", llarm::cpu::fetch_product_string(llarm::cpu::fetch_product()));
    }

    if (arg_bitset.test(ARCH)) {
        std::printf("%s\n", llarm::cpu::fetch_arch_string(llarm::cpu::fetch_arch()));
    }

    if (arg_bitset.test(PPN)) {
        std::printf("0x%03X\n", llarm::cpu::fetch_ppn());
    }

    if (arg_bitset.test(VARIANT)) {
        std::printf("%u\n", llarm::cpu::fetch_variant());
    }

    if (arg_bitset.test(REVISION)) {
        std::printf("%u\n", llarm::cpu::fetch_revision());
    }

    if (arg_bitset.test(IS_ARM)) {
        std::printf("%d\n", llarm::cpu::fetch_midr() != 0 ? 1 : 0);
    }

    return 0;
}
