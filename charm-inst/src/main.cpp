#include <iostream>
#include 

#include "shared/types.hpp"
#include "shared/tools/metadata.hpp"

#include <charm-asm/charm-asm.hpp>


enum arg_enum : u8 {
    NULL_ARG,
    HELP,
    VERSION,
    ARM,
    THUMB,
    THUMB2,
    JAZELLE,
    END
};



[[noreturn]] void help() {
    std::cout << 
R"(Usage: 
 charm-inst [option(s)] [args] [extra]

Options:
 -h  | --help          prints this help menu
 -v  | --version       print CLI version and other details
 -a  | --arm           ARM mode (default)
 -t  | --thumb         Thumb mode
 -t2 | --thumb2        Thumb2 mode
 -j  | --jazelle       Jazelle mode

Examples:
 charm-inst --thumb ""

)";
    std::exit(0);
}



[[noreturn]] void version(void) {
    std::cout << 
        "charm-inst " << "v" << CHARM_INST_VER << " (" << CHARM_INST_DATE << ")\n\n" <<
        "Sub-project of the CHARM framework at https://github.com/kernelwernel/CHARM\n" <<
        "License MIT: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>.\n" <<  // TODO
        "This is free software: you are free to change and redistribute it.\n" <<
        "There is NO WARRANTY, to the extent permitted by law.\n" <<
        "Developed and maintained by kernelwernel, see https://github.com/kernelwernel\n";

    std::exit(0);
}



int main(int argc, char* argv[]) {
    const std::vector<std::string> args(argv + 1, argv + argc); // easier to handle args this way
    const u32 arg_count = static_cast<u32>(argc - 1);

    constexpr u8 arg_bits = static_cast<u8>(END) + 1;
    std::bitset<arg_bits> arg_bitset;

    if (arg_count == 0) {
        help();
        return 0;
    }

    
}