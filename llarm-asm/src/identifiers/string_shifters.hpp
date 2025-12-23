#pragma once

#include "../shifter_id.hpp"

#include "../interpreter/lexer.hpp"
#include "../interpreter/IR.hpp"

namespace internal::ident::string_shifters {
    shifter_enum data_instruction(const lexemes_t &lexemes);
    shifter_enum ls_instruction(const lexemes_t &lexemes);
    shifter_enum ls_misc_instruction(const lexemes_t &lexemes);
    shifter_enum ls_mul_instruction(const sv mnemonic);
    shifter_enum ls_coproc_instruction(const lexemes_t &lexemes);
    shifter_enum vfp_mul_instruction(const lexemes_t &lexemes, const sv mnemonic);

    // PLD has an exception to its addressing mode format
    shifter_enum ls_instruction_PLD(const lexemes_t &lexemes);

    shifter_enum identify_shifter(const IR_arm_struct &IR);
    shifter_enum identify_shifter(const std::string &code);
}