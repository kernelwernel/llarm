#pragma once

#include "../interpreter/IR_struct.hpp"
#include <string>

namespace internal::validation::string_thumb {
    bool is_B1_valid(const u32 PC, const lexemes_t& lexemes);
    bool is_B2_valid(const u32 PC, const lexemes_t& lexemes);
 
    bool is_thumb_instruction_valid(const std::string& code);
    bool is_thumb_instruction_valid(const IR_thumb_struct& IR);

    bool is_bl_blx_target_valid(const u32 PC, const lexemes_t& lexemes, const bool is_blx);
}