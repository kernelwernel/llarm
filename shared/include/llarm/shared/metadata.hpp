#pragma once

#include "types.hpp"

#include <iostream>

namespace llarm::metadata {
    // versions
    static constinit const char* LLARM_ASM_VER = "0.1";
    static constinit const char* LLARM_CPU_VER = "0.1";
    static constinit const char* LLARM_EMU_VER = "0.1";
    static constinit const char* LLARM_INST_VER = "0.1";
    static constinit const char* LLARM_RAND_VER = "0.1";

    // release dates
    static constinit const char* LLARM_ASM_DATE = "00/00/00"; // TODO
    static constinit const char* LLARM_CPU_DATE = "00/00/00"; // TODO
    static constinit const char* LLARM_EMU_DATE = "00/00/00"; // TODO
    static constinit const char* LLARM_INST_DATE = "00/00/00"; // TODO
    static constinit const char* LLARM_RAND_DATE = "00/00/00"; // TODO

    // overall LLARM framework details
    static constinit const char* LLARM_VER = "0.1";
    static constinit const char* LLARM_DATE = "00/00/00"; // TODO

    [[noreturn]] inline void version(const sv project, const sv ver, const sv date) {
        std::cout << 
            project << " v" << ver << " (" << date << ")\n\n" <<
            "Sub-project of the LLARM framework at https://github.com/kernelwernel/LLARM\n" <<
            "License: Apache 2.0 <https://opensource.org/license/apache-2.0>\n" <<
            "This is free software: you are free to change and redistribute it.\n" <<
            "There is NO WARRANTY, to the extent permitted by law.\n" <<
            "Developed and maintained by kernelwernel (https://github.com/kernelwernel)\n";

        std::exit(0);
    }
}