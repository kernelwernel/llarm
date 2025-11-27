#pragma once

#include "tokens.hpp"

#include <vector>

#include "shared/types.hpp"

namespace interpreter {    
    struct lexeme_struct {
        std::string_view mnemonic;
        tokens token_type;
        u8 immed;
        u8 integer;
        u8 reg;
        u8 coproc;
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
    
    // tokenization/lexing management 
    tokens_t tokenize(const std::string &code);
    lexemes_t lexer(const tokens_t &code);
    bool has_matching_pattern(const std::vector<tokens> &tokens, const lexemes_t &lexemes);
    
    // instruction string manipulation 
    std::string fetch_instruction(const std::string &code);
    std::string strip(std::string str);
    u16 fetch_last_2_chars(const std::string_view str);
    
    // argument analysis
    u8 identify_reg(const std::string_view code);
    bool is_reg(const std::string_view str);
    bool is_integer(const std::string_view str);
    bool is_hex(const std::string_view str);
    bool is_immed(const std::string_view str);
    i32 fetch_integer(const std::string_view str);
    i32 fetch_hex(const std::string_view str);
    tokens fetch_immed(const std::string_view token);
    tokens is_cpsr_spsr_field(const std::string_view str);

    // condition matching
    bool cond_match(const std::string_view key);
    bool cond_match(const u16 key);

    // basic wrapper for tokenize and lexer
    lexemes_t analyze(const std::string &str);
}