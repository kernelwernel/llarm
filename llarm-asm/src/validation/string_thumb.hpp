#pragma once

#include "../interpreter/IR_struct.hpp"
#include <string>

namespace internal::validation::string_thumb {
    bool is_thumb_instruction_valid(const std::string &code);
    bool is_thumb_instruction_valid(const IR_thumb_struct &IR);
}