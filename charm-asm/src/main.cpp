#include <bitset>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <array>
#include <string>

#include "../../shared/types.hpp"
#include "../../shared/out.hpp"
#include "../../shared/tools/metadata.hpp"

//#include <charm/charm-asm.hpp>


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
    END
};


[[noreturn]] void help() {
    std::cout << 
R"(Usage: 
 charm-asm [option(s)] [args] [extra]

Options:
 -h   | --help          prints this help menu
 -v   | --version       print CLI version and other details
 -as  | --assemble      assemble 
 -dis | --disassemble   disassemble
 -a   | --arm           ARM mode (default)
 -t   | --thumb         Thumb mode
 -t2  | --thumb2        Thumb2 mode
 -j   | --jazelle       Jazelle mode

Examples:
 charm-asm --assemble --thumb ""

)";
    std::exit(0);
}


[[noreturn]] void version(void) {
    std::cout << 
        "charm-asm " << "v" << CHARM_ASM_VER << " (" << CHARM_ASM_DATE << ")\n\n" <<
        "Sub-project of the CHARM framework at https://github.com/kernelwernel/CHARM\n" <<
        "License MIT: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>.\n" <<  // TODO
        "This is free software: you are free to change and redistribute it.\n" <<
        "There is NO WARRANTY, to the extent permitted by law.\n" <<
        "Developed and maintained by kernelwernel, see https://github.com/kernelwernel\n";

    std::exit(0);
}


int main(int argc, char* argv[]) {

// TMP



// TMP




    const std::vector<std::string> args(argv + 1, argv + argc); // easier to handle args this way
    const u32 arg_count = static_cast<u32>(argc - 1);


    constexpr u8 arg_bits = static_cast<u8>(END) + 1;
    std::bitset<arg_bits> arg_bitset;

    if (arg_count == 0) {
        help();
        return 0;
    }

    static constexpr std::array<std::pair<const char*, arg_enum>, 16> table {{
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
        { "-j", JAZELLE }
    }};

    std::string potential_null_arg = "";

    for (const auto arg_string : args) {
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
        out::error("charm-asm: unknown argument \"", potential_null_arg, "\"");
    }



    // basic arguments, these are directly returnable very easily
    if (arg_bitset.test(HELP)) {
        help();
        return 0;
    }

    if (arg_bitset.test(VERSION)) {
        version();
        return 0;
    }



    // complex arguments, multiple arguments can be combined for a result to take shape at this point




        // b5b0 = thumb PUSH
}