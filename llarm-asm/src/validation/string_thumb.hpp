#pragma once

#include "../interpreter/IR.hpp"
#include <string>

using namespace internal;

namespace validation::string_thumb {
    bool is_thumb_instruction_valid(const std::string &code);
    bool is_thumb_instruction_valid(const IR_thumb_struct &IR);
}