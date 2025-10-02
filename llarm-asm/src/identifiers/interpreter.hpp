#pragma once

#include <vector>

#include "shared/types.hpp"

namespace interpreter {
    enum tokens : u8 {
        UNKNOWN,
        REG, // R0~R15
        REG_THUMB, // R0~R7
        REG_LIST,
        REG_LIST_NO_PC,

        // these are only meant for pattern matching, not used as an actual token for analysis
        REG_LIST_WITH_PC,
        REG_PC, // R15
        REG_SP, // R14

        IMMED_3,
        IMMED_5,
        IMMED_7,
        IMMED_8,
        IMMED,
        OP,
        MUL_OP, // "*"
        INTEGER,
        INTEGER_4,
        INTEGER_2,
        CPSR_FIELD,
        SPSR_FIELD,
        MEM_START, // "{"
        MEM_END, // "}"
        LSL,
        LSR,
        ASR,
        ROR,
        RRX,
        PRE_INDEX, // '!'
        CARET, // '^'
        MNEMONIC
    };
    
    struct lexeme_struct {
        tokens token_type;
        u8 immed;
        u8 integer;
        u8 reg;
        unsigned char op;
        u16 reg_list;
        bool pre_index;
    };

    constexpr u8 error = 255;

    constexpr u16 EQ = ('E' << 8) | 'Q';
    constexpr u16 NE = ('N' << 8) | 'E';
    constexpr u16 CS = ('C' << 8) | 'S';
    constexpr u16 HS = ('H' << 8) | 'S';
    constexpr u16 CC = ('C' << 8) | 'C';
    constexpr u16 LO = ('L' << 8) | 'O';
    constexpr u16 MI = ('M' << 8) | 'I';
    constexpr u16 PL = ('P' << 8) | 'L';
    constexpr u16 VS = ('V' << 8) | 'S';
    constexpr u16 VC = ('V' << 8) | 'C';
    constexpr u16 HI = ('H' << 8) | 'I';
    constexpr u16 LS = ('L' << 8) | 'S';
    constexpr u16 GE = ('G' << 8) | 'E';
    constexpr u16 LT = ('L' << 8) | 'T';
    constexpr u16 GT = ('G' << 8) | 'T';
    constexpr u16 LE = ('L' << 8) | 'E';
    constexpr u16 AL = ('A' << 8) | 'L';

    using tokens_t = std::vector<std::string_view>;
    using lexemes_t = std::vector<lexeme_struct>;

    // argument prefix analysis
    void asterisk(lexeme_struct &lexeme);
    void hashtag(const std::string_view token, lexeme_struct &lexeme);

    // tokenization/lexing management 
    tokens_t tokenize(const std::string &code);
    lexemes_t lexer(const tokens_t &code);
    bool has_matching_pattern(const std::vector<tokens> &tokens, const lexemes_t &lexemes);

    // instruction string manipulation 
    std::string fetch_instruction(const std::string &code);
    std::string strip(std::string str);

    // argument analysis
    u8 identify_reg(const std::string_view code);
    bool is_integer(const std::string_view str);
    bool is_hex(const std::string_view str);
    i32 fetch_integer(const std::string_view str);
    i32 fetch_hex(const std::string_view str);
    tokens is_cpsr_spsr_field(const std::string_view str);

    // condition matching
    bool cond_match(const std::string_view key);
    bool cond_match(const u16 key);

    // basic wrapper for tokenize and lexer
    lexemes_t analyze(const std::string &str);
}