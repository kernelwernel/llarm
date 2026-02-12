#pragma once

#include "tokens.hpp"
#include <llarm/shared/out.hpp>

#include <vector>


struct lexeme {
    token_enum token_type;
    
    // marking it as a union goes from 72 bytes to 40 bytes
    union {
        REG reg;
        PSR psr;
        IMM imm;
        REG_LIST reg_list; 
        OPTION option;
    } data;

    constexpr lexeme(token_enum t, REG &reg) : token_type(t) {
        data.reg = reg;
    }

    constexpr lexeme(token_enum t, PSR &psr) : token_type(t) {
        data.psr = psr;
    }

    constexpr lexeme(token_enum t, IMM &imm) : token_type(t) {
        data.imm = imm;
    }

    constexpr lexeme(token_enum t, REG_LIST &reg_list) : token_type(t) {
        data.reg_list = reg_list;
    }

    constexpr lexeme(token_enum t, OPTION &option) : token_type(t) {
        data.option = option;
    }

    constexpr lexeme(token_enum t) : token_type(t) {

    }

    constexpr lexeme() : token_type(token_enum::UNKNOWN) {
        data.reg = REG{};  // Zero-initialize first member
    }
    
};

using lexemes_t = std::vector<lexeme>;

namespace lexer {
    lexemes_t lex(const raw_tokens_t &tokens);
    
    bool reg_check(lexeme &lexeme, const sv token);
    bool psr_check(lexeme &lexeme, const sv token);
    bool imm_check(lexeme &lexeme, const sv token);
    bool reg_list_check(lexeme &lexeme, const raw_tokens_t &list);
    bool character_check(lexeme &lexeme, const sv token);
    bool address_check(lexeme &lexeme, const sv token);
    bool comment_check(lexeme &lexeme, const sv token);
    
    void option_check(lexemes_t &lexemes, const u8 start_pos, const u8 end_pos);

    void reg_list_check(lexemes_t &lexemes, const u8 start_pos, const u8 end_pos);
    void reg_list_range(lexemes_t &rl_lexemes, const u8 start_pos, const u8 end_pos);
    void reg_list_categorize(lexemes_t &rl_lexemes, REG_LIST &reg_list, const u8 start_pos, const u8 end_pos);
}