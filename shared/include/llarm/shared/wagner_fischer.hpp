#pragma once

#include <string>
#include <vector>

#include "types.hpp"

namespace shared::spellcheck {
    // https://en.wikipedia.org/wiki/Wagner%E2%80%93Fischer_algorithm
    static u8 wagner_fischer(
        sv a, 
        sv b
    );

    static std::vector<std::string> suggest(
        const sv misspelled_word, 
        const std::vector<std::string> &dictionary
    );

    static void manage_output(const std::vector<std::string> &tmp);
};