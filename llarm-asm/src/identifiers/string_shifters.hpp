#pragma once

#include "../shifter_id.hpp"
#include "../instruction_id.hpp"

#include "../interpreter/interpreter.hpp"

namespace internal::ident::string_shifters {
    shifter_enum data_instruction(const interpreter::lexemes_t &lexemes);
    shifter_enum ls_instruction(const interpreter::lexemes_t &lexemes);
    shifter_enum ls_misc_instruction(const interpreter::lexemes_t &lexemes);
    shifter_enum ls_mul_instruction(const interpreter::lexemes_t &lexemes);
    shifter_enum ls_coproc_instruction(const interpreter::lexemes_t &lexemes);
    shifter_enum vfp_mul_instruction(const interpreter::lexemes_t &lexemes);

    // PLD has an exception to its addressing mode format
    shifter_enum ls_instruction_PLD(const interpreter::lexemes_t &lexemes);

    shifter_enum identify_shifter(const id::arm id, const interpreter::lexemes_t &lexemes);    
    shifter_enum identify_shifter(const std::string &code);
}