#pragma once

//#include "id.hpp"
//
//#include <tuple>
//
//#include <llarm/shared/types.hpp>


namespace sanitize {
    //using input_args_t = std::tuple<fs::

    /*
    bool sanitize::is_binary_valid() { 

        // 1: check for elf magic
        // 2: check for arm machine value

        // 0xB7 	Arm 64-bits 
        // 0x28 	Arm (up to Armv7/AArch32) 
    }
    */

/*
    void handler(const int argc, const char* argv[]) {
        const std::vector<const char*> args(argv + 1, argv + argc); // easier this way
        const std::uint32_t arg_count = argc - 1;

        constexpr std::array<std::pair<sv, id::arguments>, 6> table {{
            { "-h",          id::arguments::HELP },
            { "--help",      id::arguments::HELP },
            { "-v",          id::arguments::VERBOSE },
            { "--verbose",   id::arguments::VERBOSE },
            { "-t",          id::arguments::THUMB_ARG },
            { "--thumb",     id::arguments::THUMB_ARG },
        }};

        for (const char* arg : args) {
            auto it = std::find_if(table.cbegin(), table.cend(), [&](const auto &p) { 
                return p.first == arg; 
            });

            if (it != table.end()) {
                return it->second;
            }

            return id::arguments::NULL_ARG;
        }
    }
*/
}
