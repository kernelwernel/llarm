#pragma once

#include "../types.hpp"

#include <iostream>

namespace shared::metadata {
    // versions
    static constinit const char* LLARM_EMU_VER = "0.1";
    static constinit const char* LLARM_ASM_VER = "0.1";
    static constinit const char* LLARM_INST_VER = "0.1";

    // release dates
    static constinit const char* LLARM_EMU_DATE = "00/00/00"; // TODO
    static constinit const char* LLARM_ASM_DATE = "00/00/00"; // TODO
    static constinit const char* LLARM_INST_DATE = "00/00/00"; // TODO

    // overall CHARM framework details
    static constinit const char* LLARM_VER = "0.1";
    static constinit const char* LLARM_DATE = "00/00/00"; // TODO

    [[noreturn]] void version(const sv project, const sv ver, const sv date) {
        std::cout << 
            project << " " << "v" << ver << " (" << date << ")\n\n" <<
            "Sub-project of the CHARM framework at https://github.com/kernelwernel/CHARM\n" <<
            "License MIT: <https://opensource.org/license/mit>.\n" <<
            "This is free software: you are free to change and redistribute it.\n" <<
            "There is NO WARRANTY, to the extent permitted by law.\n" <<
            "Developed and maintained by kernelwernel (https://github.com/kernelwernel)\n";

        std::exit(0);
    }
}