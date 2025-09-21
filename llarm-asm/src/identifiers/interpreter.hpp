#pragma once

#include <vector>

#include "shared/types.hpp"
#include "shared/out.hpp"
#include "shared/util.hpp"


namespace interpreter {
    enum tokens : u8 {
        UNKNOWN,
        REG,
        REG_PC,
        REG_SP,
        REG_THUMB,
        REG_LIST,
        IMMED_3,
        IMMED_5,
        IMMED_7,
        IMMED_8,
        OP,
        MUL_OP,
        INTEGER,
        INTEGER_4,
        INTEGER_2,
        MEM_START,
        MEM_END
    };
    
    struct lexeme_struct {
        tokens token_type;
        u8 immed;
        u8 integer;
        u8 reg;
        unsigned char op;
        std::vector<u8> reg_list;
    };
    
    constexpr u8 error = 255;

    using tokens_t = std::vector<std::string>;
    using lexemes_t = std::vector<lexeme_struct>;

    tokens_t tokenize(const std::string &code);
    lexemes_t lexer(const tokens_t &code);
    std::string fetch_instruction(const std::string &code);
    std::string strip(std::string str);
    u8 identify_reg(const std::string_view code);
    bool is_integer(const std::string_view str);
    u32 fetch_integer(std::string_view str);
    bool has_matching_pattern(const std::vector<tokens> &tokens, const lexemes_t &lexemes);
    //lexemes_t fetch_lexemes(const std::string& code);
}