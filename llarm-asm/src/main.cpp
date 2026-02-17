#include <bitset>
#include <cstring>
#include <iostream>
#include <array>
#include <string>
#include <span>
#include <algorithm>

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

    const u16 inst = 0b1110'0000'0000'0001;
    std::cout << llarm::as::disassemble_thumb(inst, 0x500) << "\n";
    //std::cout << internal::thumb_id_to_string(llarm::as::identify::thumb(inst)) << "\n";
    return 0;


    const std::span<char*> args(argv, static_cast<std::size_t>(argc));
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

    std::string potential_null_arg;

    for (const auto &arg_string : args) {
        auto it = std::find_if(table.cbegin(), table.cend(), [&](const auto &p) {
            return (arg_string == p.first);
        });

        if (it == table.end()) {
            //if (arg_string.at(0) == "\"" && arg_string.at(sizeof(arg_string)) == "\"") {
            //    // this is a string argument, treat it differently
            //}

            arg_bitset.set(NULL_ARG);
            potential_null_arg = arg_string;
        } else {
            arg_bitset.set(it->second);
        }
    }

    if (arg_bitset.test(NULL_ARG)) {
        llarm::out::error("llarm-asm: unknown argument \"", potential_null_arg, "\"");
    }



    // basic arguments, these are directly returnable very simply
    if (arg_bitset.test(HELP)) {
        help();
        return 0;
    }

    if (arg_bitset.test(VERSION)) {
        llarm::metadata::version(
            "llarm-asm", 
            llarm::metadata::LLARM_ASM_VER, 
            llarm::metadata::LLARM_ASM_DATE
        );
        return 0;
    }



    // complex arguments, multiple arguments can be combined for a result to take shape at this point




        // b5b0 = thumb PUSH
}