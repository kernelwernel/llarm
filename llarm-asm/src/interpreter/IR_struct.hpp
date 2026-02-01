#pragma once

#include "lexer.hpp"
#include "mnemonic.hpp"
#include "operand_struct.hpp"

using namespace internal;

struct IR_arm_struct {
    lexemes_t lexemes;
    mnemonic_struct mnemonic;
    operand_struct operands;
    u32 PC;
};