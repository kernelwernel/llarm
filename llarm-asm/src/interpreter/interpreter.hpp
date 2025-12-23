#pragma once

#include "tokens.hpp"
#include "lexer.hpp"

#include "shared/string_view.hpp"


namespace interpreter {
    // specifically for validation
    bool verify_lexemes(const lexemes_t&& raw_pattern, const lexemes_t &match_pattern);

    // specifically for identification, it's basically a cheaper version of verify_lexemes() 
    // but for token placements instead of a thorough analysis of lexemes
    bool verify_tokens(const tokens_t&& tokens, const lexemes_t &match_pattern);

    lexemes_t analyze(const sv instruction);
    sv fetch_instruction(const sv instruction);
    u16 fetch_last_2_chars(const sv str);
    bool cond_match(const sv cond);
    bool cond_match(const u16 cond);

    // these functions are meant to be wrappers for the sake of not cluttering the argument list
    // when trying to make a comparison between the raw lexemes that were gathered from string analysis,
    // and the pre-set lexemes for comparison and checking

    // PSR specific argument aliases
    constexpr bool CPSR = true;
    constexpr bool SPSR = false;
    constexpr bool HAS_FIELDS = true;
    constexpr bool NO_FIELDS = false;

    // IMM specific
    constexpr bool HAS_NEGATIVE = true;


    struct immed_settings {
        u8 divisor;
        u8 msb;
        bool is_msb_rangable;

        immed_settings() : divisor(1), msb(0), is_msb_rangable(false) {

        }
    };

    struct reg_list_settings {
        reg_type reg_list_type;
        bool is_r15_excluded;
        bool must_include_r15;
        bool is_reg_list_thumb;

        reg_list_settings() :
            reg_list_type(reg_type::REGULAR), 
            is_r15_excluded(false),
            must_include_r15(false),
            is_reg_list_thumb(false)
        {

        }
    };

    // this may be useful: https://stackoverflow.com/questions/30632442/c14-constexpr-union-conditional-initialization-in-constructor

    lexeme reg(const reg_type reg_type = reg_type::REGULAR, const u8 reg_num = WILDCARD, const bool is_thumb = false);
    lexeme psr(const bool psr_type, const bool has_fields);
    lexeme option(const u8 number);
    lexeme immed(const immed_settings &imm_settings = {});
    lexeme immed(const u8 msb);
    lexeme reg_list(const reg_list_settings &reg_list_settings = {});
    //constexpr lexeme token(const token_enum t);

    constexpr lexeme token(const token_enum t) {
        constexpr lexeme lexeme = {
            token_enum::IMMED, // token_type
        };

        return lexeme;
    }
}