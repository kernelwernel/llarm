#include <bitset>
#include <cstring>
#include <iostream>
#include <array>
#include <string>
#include <span>
#include <algorithm>
#include <cstdlib>

#include <llarm/shared/types.hpp>
#include <llarm/shared/out.hpp>
#include <llarm/shared/metadata.hpp>

#include <llarm/llarm-asm.hpp>


enum arg_enum : u8 {
    NULL_ARG,
    HELP,
    VERSION,
    ASSEMBLE,
    DISASSEMBLE,
    ARM,
    THUMB,
    THUMB2,
    JAZELLE,
    RAW_ALIAS,
    LOWERCASE,
    END
};


[[noreturn]] void help() {
    std::cout <<
R"(Usage:
 llarm-asm [option(s)] [args] [extra]

Options:
 -h   | --help          prints this help menu
 -v   | --version       print CLI version and other details
 -as  | --assemble      assemble
 -dis | --disassemble   disassemble
 -a   | --arm           ARM mode (default)
 -t   | --thumb         Thumb mode
 -t2  | --thumb2        Thumb2 mode
 -j   | --jazelle       Jazelle mode
 -r   | --raw-alias     Show raw register aliases (i.e. PC => R15)
 -l   | --lowercase     Show the instructions as lowercase

Examples:
 llarm-asm --assemble --thumb "ADC R1, R0"

)";
    std::exit(0);
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

    static constexpr std::array<std::pair<const char*, arg_enum>, 20> table {{
        { "-h", HELP },
        { "--help", HELP },
        { "-v", VERSION },
        { "--version", VERSION },
        { "-as", ASSEMBLE },
        { "--assemble", ASSEMBLE },
        { "-dis", DISASSEMBLE },
        { "--disassemble", DISASSEMBLE },
        { "--arm", ARM },
        { "-a", ARM },
        { "--thumb", THUMB },
        { "-t", THUMB },
        { "--thumb2", THUMB2 },
        { "-t2", THUMB2 },
        { "--jazelle", JAZELLE },
        { "-j", JAZELLE },
        { "--raw-alias", RAW_ALIAS },
        { "-r", RAW_ALIAS },
        { "--lowercase", LOWERCASE },
        { "-l", LOWERCASE }
    }};

    std::string payload;

    for (const auto arg_string : args) {
        auto it = std::find_if(table.cbegin(), table.cend(), [&](const auto& p) {
            return (std::strcmp(arg_string, p.first) == 0);
        });

        if (it == table.end()) {
            if (!payload.empty()) {
                llarm::out::error("llarm-asm: unexpected argument \"", arg_string, "\"");
            }
            payload = arg_string;
        } else {
            arg_bitset.set(it->second);
        }
    }

    if (arg_bitset.test(HELP)) {
        help();
    }

    if (arg_bitset.test(VERSION)) {
        llarm::metadata::version(
            "llarm-asm",
            llarm::metadata::LLARM_ASM_VER,
            llarm::metadata::LLARM_ASM_DATE
        );
    }

    if (arg_bitset.test(THUMB2)) {
        llarm::out::error("llarm-asm: Thumb2 mode is not yet supported");
    }

    if (arg_bitset.test(JAZELLE)) {
        llarm::out::error("llarm-asm: Jazelle mode is not yet supported");
    }

    if (arg_bitset.test(ASSEMBLE) && arg_bitset.test(DISASSEMBLE)) {
        llarm::out::error("llarm-asm: --assemble and --disassemble are mutually exclusive");
    }

    if (!arg_bitset.test(ASSEMBLE) && !arg_bitset.test(DISASSEMBLE)) {
        llarm::out::error("llarm-asm: must specify --assemble or --disassemble");
    }

    if (payload.empty()) {
        llarm::out::error("llarm-asm: no instruction provided");
    }

    const bool is_thumb = arg_bitset.test(THUMB);

    llarm::as::settings config = llarm::as::default_settings();
    if (arg_bitset.test(RAW_ALIAS)) { config.register_alias = false; }
    if (arg_bitset.test(LOWERCASE)) { config.capitals = false; }

    if (arg_bitset.test(ASSEMBLE)) {
        const u32 code = is_thumb
            ? llarm::as::assemble_thumb(payload)
            : llarm::as::assemble_arm(payload);

        std::printf("0x%08X\n", code);
        return 0;
    }

    if (arg_bitset.test(DISASSEMBLE)) {
        char* end = nullptr;
        const u32 code = static_cast<u32>(std::strtoul(payload.c_str(), &end, 0));

        if (end == payload.c_str() || *end != '\0') {
            llarm::out::error("llarm-asm: invalid instruction value \"", payload, "\"");
        }

        const std::string& result = is_thumb
            ? llarm::as::disassemble_thumb(code, 0, config)
            : llarm::as::disassemble_arm(code, 0, config);

        std::cout << result << "\n";
        return 0;
    }

    return 0;
}