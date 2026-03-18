#pragma once

#include "lexer.hpp"
#include "../id/shifter_id.hpp"
#include "mnemonic_arm.hpp"
#include "mnemonic_thumb.hpp"
#include "operand_struct.hpp"

using namespace internal;

struct IR_arm_struct {
    lexemes_t lexemes;
    mnemonic_struct_arm mnemonic;
    operand_struct operands;
    u32 PC;
    enum shifter_id shifter_id;
};


struct IR_thumb_struct {
    lexemes_t lexemes;
    mnemonic_struct_thumb mnemonic;
    operand_struct operands;
    u32 PC;
};