#pragma once

#include "tokens.hpp"
#include <llarm/shared/out.hpp>

#include <vector>


union lexeme_data {
    REG reg;
    PSR psr;
    IMM imm;
    REG_LIST reg_list;
    OPTION option;

    constexpr lexeme_data() : reg{} {}
    constexpr lexeme_data(REG r) : reg(r) {}
    constexpr lexeme_data(PSR p) : psr(p) {}
    constexpr lexeme_data(IMM i) : imm(i) {}
    constexpr lexeme_data(REG_LIST r) : reg_list(r) {}
    constexpr lexeme_data(OPTION o) : option(o) {}
};

struct lexeme {
    token_enum token_type;

    // marking it as a union goes from 72 bytes to 40 bytes
    lexeme_data data;

    constexpr lexeme(token_enum t, REG r) : token_type(t), data(r) {}
    constexpr lexeme(token_enum t, PSR p) : token_type(t), data(p) {}
    constexpr lexeme(token_enum t, IMM i) : token_type(t), data(i) {}
    constexpr lexeme(token_enum t, REG_LIST r) : token_type(t), data(r) {}
    constexpr lexeme(token_enum t, OPTION o) : token_type(t), data(o) {}
    constexpr lexeme(token_enum t) : token_type(t), data()  {}
    constexpr lexeme() : token_type(token_enum::UNKNOWN), data() {}
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