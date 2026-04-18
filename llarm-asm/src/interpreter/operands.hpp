#pragma once

#include "operand_struct.hpp"
#include "mnemonic_arm.hpp"
#include "mnemonic_thumb.hpp"
#include "lexer.hpp"

#include <llarm/shared/types.hpp>

using enum token_enum;


namespace operands {
    operand_struct lex_to_operands_arm(const lexemes_t& lexemes, const mnemonic_struct_arm& mnemonic);
    operand_struct lex_to_operands_thumb(const lexemes_t& lexemes, const mnemonic_struct_thumb& mnemonic);
    operand_struct lex_to_operands(const lexemes_t& lexemes, const cond_id cond_id);

    void reg(u8& reg_count, u8& CR_reg_count, operand_struct& op, const lexeme& lexeme);
    void imm(u8& int_count, operand_struct& op, const lexeme& lexeme);
    void psr(operand_struct& op, const lexeme& lexeme);
    void reg_list(operand_struct& op, const lexeme& lexeme);
}