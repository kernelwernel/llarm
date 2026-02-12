#pragma once

#include "lexer.hpp"
#include "../id/shifter_id.hpp"
#include "mnemonic.hpp"
#include "operand_struct.hpp"

using namespace internal;

struct IR_arm_struct {
    lexemes_t lexemes;
    mnemonic_struct mnemonic;
    operand_struct operands;
    u32 PC;
    shifter_id shifter_id;
};


struct IR_thumb_struct {
    thumb_id id;
    lexemes_t lexemes;
    sv mnemonic;
};