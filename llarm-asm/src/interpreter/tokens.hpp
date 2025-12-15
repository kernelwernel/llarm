#pragma once

#include <vector>

#include "shared/string_view.hpp"
#include "shared/types.hpp"
#include "shared/util.hpp"

enum class token : u8 {
    UNKNOWN,

    REG, // R0~R15
    REG_SINGLE, // S0~S31
    REG_DOUBLE, // D0~D15
    REG_COPROC, // P0~P15
    REG_CR, // C0~C15

    REG_LIST,
    REG_LIST_NO_PC,
    REG_LIST_DOUBLE,
    REG_LIST_SINGLE,
    REG_LIST_START,
    REG_LIST_END,
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

    HASHTAG,
    IMMED,
    OP,
    MUL_OP, // "*"
    MIN_OP, // "-"
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
    COMMENT, // '@' and '<'
    OPTION, // specific to address mode 5
    MNEMONIC
};

enum class reg_type : u8 {
    UNKNOWN,
    REGULAR,
    SINGLE,
    DOUBLE,
    COPROC,
    CR,
    FPSID,
    FPSCR,
    FPEXC
};

struct REG {
    reg_type type;
    u8 number; // 0~31
    bool is_reg_vfp_special;
    bool is_malformed;
    bool is_invalid;
};

struct IMM {
    i64 number;
    u8 msb; // most significant bit index, this is useful since there's a limit in some cases
    bool is_negative;
    bool is_hex;
    bool is_multiple_of_4; // important distinction in some instructions like FSTS
    bool is_malformed;
    bool is_invalid;
};

struct PSR {
    enum psr_bitset : u8 {
        IS_CPSR,
        IS_SPSR,
        C,
        X,
        S,
        F,
        MALFORMED,
        INVALID
    };

    u8 flags; // this will save memory space instead of having bool variables for each element, 
              // the whole struct is now 1 byte instead of 8

    bool has_C() const { return llarm::util::bit_fetch(flags, C); }
    bool has_X() const { return llarm::util::bit_fetch(flags, X); }
    bool has_S() const { return llarm::util::bit_fetch(flags, S); }
    bool has_F() const { return llarm::util::bit_fetch(flags, F); }
    bool is_cpsr() const { return llarm::util::bit_fetch(flags, IS_CPSR); }
    bool is_spsr() const { return llarm::util::bit_fetch(flags, IS_SPSR); }
    bool is_malformed() const { return llarm::util::bit_fetch(flags, MALFORMED); }
    bool is_invalid() const { return llarm::util::bit_fetch(flags, INVALID); }

    void set_C(const bool value = true) { llarm::util::modify_bit(flags, C, value); }
    void set_X(const bool value = true) { llarm::util::modify_bit(flags, X, value); }
    void set_S(const bool value = true) { llarm::util::modify_bit(flags, S, value); }
    void set_F(const bool value = true) { llarm::util::modify_bit(flags, F, value); }
    void set_cpsr(const bool value = true) { llarm::util::modify_bit(flags, IS_CPSR, value); }
    void set_spsr(const bool value = true) { llarm::util::modify_bit(flags, IS_SPSR, value); }
    void set_malformed(const bool value = true) { llarm::util::modify_bit(flags, MALFORMED, value); }
    void set_invalid(const bool value = true) { llarm::util::modify_bit(flags, INVALID, value); }
};

struct REG_LIST {
    reg_type type;
    u8 reg_count;
    bool is_malformed;
    bool is_invalid;
    bool is_empty;
    u32 list;
};

using tokens_t = std::vector<llarm::string_view>;

namespace tokens {
    // tokenization/lexing management 
    tokens_t tokenize(const std::string &code);
    std::string strip(std::string str);
}