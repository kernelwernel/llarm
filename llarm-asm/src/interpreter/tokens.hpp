#pragma once

#include "shared/types.hpp"

enum tokens : u8 {
    UNKNOWN,
    REG, // R0~R15
    REG_THUMB, // R0~R7
    REG_SINGLE, // S0~S31
    REG_DOUBLE, // D0~D15
    REG_LIST,
    REG_LIST_NO_PC,
    REG_LIST_DOUBLE,
    REG_LIST_SINGLE,
    VFP_REG_SPECIAL, // FPSID, FPSCR, or FPEXC

    // these are only meant for pattern matching, not used as an actual token for analysis
    REG_LIST_WITH_PC,
    REG_LIST_THUMB,
    REG_LIST_THUMB_OPTIONAL_PC,
    REG_LIST_THUMB_OPTIONAL_LR,
    REG_PC, // R15
    REG_SP, // R14
    //DATA_PROCESSING_ADDRESS_MODE,
    //LS_ADDRESS_MODE,
    //LS_MISC_ADDRESS_MODE,
    //LS_MUL_ADDRESS_MODE,
    //LS_COPROC_ADDRESS_MODE,

    COPROCESSOR, // P0~P15
    CR_REG, // C0~C15

    HASHTAG,
    IMMED_3,
    IMMED_5,
    IMMED_7,
    IMMED_8,
    IMMED_12,
    IMMED_16,
    IMMED_24,
    IMMED,
    OP,
    MUL_OP, // "*"
    CONST,
    CONST_4,
    CONST_2,
    CONST_MUL_4,
    CPSR_FIELD,
    SPSR_FIELD,
    CPSR,
    SPSR,
    MEM_START, // "{"
    MEM_END, // "}"
    LSL,
    LSR,
    ASR,
    ROR,
    RRX,
    SHIFT,
    PRE_INDEX, // '!'
    CARET, // '^'
    OPTION, // specific to address mode 5
    MNEMONIC
};