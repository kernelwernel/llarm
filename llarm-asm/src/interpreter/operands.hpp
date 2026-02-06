#pragma once

#include "operand_struct.hpp"
#include "mnemonic.hpp"
#include "lexer.hpp"

#include <llarm/shared/types.hpp>

using enum token_enum;


namespace operands {
    operand_struct lex_to_operands(const lexemes_t &lexemes, const mnemonic_struct &mnemonic);

    void reg(u8 &reg_count, u8 &CR_reg_count, operand_struct &op, const lexeme &lexeme);
    void imm(u8 &int_count, operand_struct &op, const lexeme &lexeme);
    void psr(operand_struct &op, const lexeme &lexeme);
    void reg_list(operand_struct &op, const lexeme &lexeme);


    //operands thumb_IR_to_ops(const IR_thumb_struct &IR) {
    //    
    //}
}