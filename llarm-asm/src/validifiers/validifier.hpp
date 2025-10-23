#pragma once

#include "../instruction_id.hpp"
#include "../identifiers/interpreter.hpp"

#include "shared/types.hpp"

namespace internal::validifier {
    bool is_thumb_instruction_valid(const u16 code); // defined in u16_thumb.cpp
    bool is_thumb_instruction_valid(const id::thumb id); // defined in u16_thumb.cpp
    bool is_thumb_instruction_valid(const std::string &code); // defined in string_thumb.cpp
    bool is_thumb_instruction_valid(const id::thumb id, const interpreter::lexemes_t &lexemes); // defined in string_thumb.cpp

    bool is_arm_instruction_valid(const u32 code);
    bool is_arm_instruction_valid(const std::string &code);
    bool is_arm_instruction_valid(const id::arm id, const interpreter::lexemes_t &lexemes); // defined in string_arm.cpp
}