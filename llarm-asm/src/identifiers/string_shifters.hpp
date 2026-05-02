#pragma once

#include "../id/shifter_id.hpp"
#include "../interpreter/lexer.hpp"
#include "../interpreter/IR_struct.hpp"
#include "../interpreter/mnemonic_arm.hpp"

namespace internal::ident::string_shifters {
    shifter_id data_instruction(const lexemes_t& lexemes);
    shifter_id ls_instruction(const lexemes_t& lexemes);
    shifter_id ls_misc_instruction(const lexemes_t& lexemes);
    shifter_id ls_mul_instruction(const sv mnemonic);
    shifter_id ls_coproc_instruction(const lexemes_t& lexemes);
    shifter_id vfp_mul_instruction(const lexemes_t& lexemes, const sv mnemonic);
    shifter_id usat_instruction(const lexemes_t& lexemes);

    // PLD has an exception to its addressing mode format
    shifter_id ls_instruction_PLD(const lexemes_t& lexemes);

    shifter_id identify_shifter(const lexemes_t& lexemes, const mnemonic_struct_arm& mnemonic);
    shifter_id identify_shifter(const IR_arm_struct &&IR);
    shifter_id identify_shifter(const std::string& code);
}