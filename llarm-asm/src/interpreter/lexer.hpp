#pragma once

#include "tokens.hpp"

#include <vector>

enum class lexeme_category : u8 {
    REG,
    PSR,
    IMM,
    REG_LIST,

};

// marking it as a union goes from 72 bytes to 40 bytes
struct lexeme {
    token token_type;

    union {
        REG reg;
        PSR psr;
        IMM imm;
        REG_LIST reg_list; 
    } data;

    lexeme(token t, REG &reg) : token_type(t) {
        data.reg = reg;
    }

    lexeme(token t, PSR &psr) : token_type(t) {
        data.psr = psr;
    }

    lexeme(token t, IMM &imm) : token_type(t) {
        data.imm = imm;
    }

    lexeme(token t, REG_LIST &reg_list) : token_type(t) {
        data.reg_list = reg_list;
    }

    lexeme() {
        
    }
};

using lexemes_t = std::vector<lexeme>;

namespace lexer {
    lexemes_t analyze(const tokens_t &tokens);
    
    bool reg_check(lexeme &lexeme, const llarm::string_view token);
    bool psr_check(lexeme &lexeme, const llarm::string_view token);
    bool imm_check(lexeme &lexeme, const llarm::string_view token);
    bool reg_list_check(lexeme &lexeme, const tokens_t &list);
    bool character_check(lexeme &lexeme, const llarm::string_view token);
    bool address_check(lexeme &lexeme, const llarm::string_view token);

    void reg_list_check(lexemes_t &lexemes);
    void reg_list_range(lexemes_t &rl_lexemes, const u8 start_pos, const u8 end_pos);
    void reg_list_categorize(lexemes_t &rl_lexemes, REG_LIST &reg_list, const u8 start_pos, const u8 end_pos);
}