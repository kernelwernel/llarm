#pragma once

#include "tokens.hpp"
#include "lexer.hpp"
#include "../id/cond_id.hpp"

#include <llarm/shared/string_view.hpp>
#include <array>


namespace interpreter {
    template<typename... Ts>
    LLARM_CONSTEVAL std::array<lexeme, sizeof...(Ts)> make_lexemes(Ts... args) {
        return { args... };
    }

    template<typename... Ts>
    LLARM_CONSTEVAL std::array<token_enum, sizeof...(Ts)> make_tokens(Ts... args) {
        return { args... };
    }

    // specifically for validation
    template<std::size_t N>
    bool verify_lexemes(const std::array<lexeme, N>& raw_pattern, const lexemes_t& match_pattern) {
        if (raw_pattern.size() != match_pattern.size()) {
            return false;
        }

        for (size_t i = 0; i < raw_pattern.size(); i++) {
            const lexeme& raw = raw_pattern.at(i);
            const lexeme& match = match_pattern.at(i);

            if (raw.token_type != match.token_type) {
                return false;
            }

            bool is_equivalent = false;

            switch (raw.token_type) {
                case token_enum::REG: is_equivalent = (raw.data.reg == match.data.reg); break;
                case token_enum::REG_THUMB: is_equivalent = (raw.data.reg == match.data.reg); break;
                case token_enum::PSR: is_equivalent = (raw.data.psr == match.data.psr); break;
                case token_enum::OPTION: is_equivalent = (raw.data.option == match.data.option); break;
                case token_enum::REG_LIST: is_equivalent = (raw.data.reg_list == match.data.reg_list); break;
                case token_enum::IMMED: is_equivalent = (raw.data.imm == match.data.imm); break;
                case token_enum::REG_LIST_START:
                case token_enum::REG_LIST_END:
                case token_enum::HASHTAG:
                case token_enum::MUL_OP:
                case token_enum::MIN_OP:
                case token_enum::MEM_START:
                case token_enum::MEM_END:
                case token_enum::LSL:
                case token_enum::LSR:
                case token_enum::ASR:
                case token_enum::ROR:
                case token_enum::RRX:
                case token_enum::SHIFT:
                case token_enum::PRE_INDEX:
                case token_enum::CARET:
                case token_enum::COMMENT: return true; // these tokens don't have complex components to check if they're valid or not
                case token_enum::UNKNOWN: return false;
            }
    
            if (is_equivalent == false) {
                return false;
            }
        }

        return true;
    }

    // specifically for identification, it's basically a cheaper version of verify_lexemes() 
    // but for token placements instead of a thorough analysis of lexemes
    template <std::size_t N>
    bool verify_tokens(const std::array<token_enum, N>& raw_tokens, const lexemes_t& match_pattern) {
        using enum token_enum;

        if (raw_tokens.size() != match_pattern.size()) {
            return false;
        }

        for (size_t i = 0; i < raw_tokens.size(); i++) {
            const token_enum match = match_pattern.at(i).token_type;
            const token_enum raw = raw_tokens.at(i);

            // REG_THUMB is supported under REG since it's a substitute, 
            // but REG to REG_THUMB is incompatible. 
            if (raw == REG_THUMB && match == REG) {
                continue;
            }

            if (match == SHIFT) {
                switch (raw) {
                    case LSL:
                    case LSR:
                    case ASR:
                    case ROR:
                    case RRX: continue;
                    default: return false;
                }
            }

            if (raw != match) {
                return false;
            }
        }

        return true;
    }

    lexemes_t analyze(const sv instruction);
    sv fetch_instruction(const sv instruction);
    u16 fetch_last_2_chars(const sv str);
    bool cond_match(const sv cond);
    bool cond_match(const u16 cond);
    cond_id fetch_cond_id(const u16 cond);
    cond_id fetch_cond_id(const sv cond);

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

        constexpr immed_settings() : divisor(1), msb(0), is_msb_rangable(false) {}
    };

    struct reg_list_settings {
        reg_type reg_list_type = reg_type::REGULAR;
        bool is_r15_excluded = false;
        bool must_include_r15 = false;
        bool is_reg_list_thumb = false;
        bool is_PC_optional = false;
        bool is_LR_optional = false;
    };

    enum class special_reg : u8 {
        PC,
        LR,
        SP,
        IP,
        FP
    };

    LLARM_CONSTEVAL lexeme reg(const reg_type reg_type = reg_type::REGULAR, const u8 reg_num = WILDCARD) {
        REG r{};
        
        r.type = reg_type;
        r.number = reg_num;
        r.is_thumb_supported = false;
        r.is_malformed = false;
        r.is_invalid = false;

        return { token_enum::REG, r };
    }

    LLARM_CONSTEVAL lexeme reg(const special_reg special_reg) {
        u8 reg_num = 0;

        switch (special_reg) {
            case special_reg::PC: reg_num = 15; break;
            case special_reg::LR: reg_num = 14; break;
            case special_reg::SP: reg_num = 13; break;
            case special_reg::IP: reg_num = 12; break;
            case special_reg::FP: reg_num = 11; break;
        }

        REG r{};
        
        r.type = reg_type::REGULAR;
        r.number = reg_num;
        r.is_thumb_supported = false;
        r.is_malformed = false;
        r.is_invalid = false;

        return { token_enum::REG, r };
    }

    LLARM_CONSTEVAL lexeme reg_thumb(const u8 reg_num = WILDCARD) {
        REG r{};
        
        r.type = reg_type::REGULAR;
        r.number = reg_num;
        r.is_thumb_supported = true;
        r.is_malformed = false;
        r.is_invalid = false;

        return { token_enum::REG, r };
    }

    LLARM_CONSTEVAL lexeme psr(const bool psr_type, const bool has_fields = false) {
        PSR psr{};

        psr.flags = 0;

        if (psr_type == CPSR) {
            psr.set_cpsr();
        } else {
            psr.set_spsr();
        }

        if (has_fields == HAS_FIELDS) {
            psr.set_C();
        }

        return { token_enum::PSR, psr };
    }

    LLARM_CONSTEVAL lexeme option(const u8 number = 0) {
        OPTION option{};
        
        option.number = number;
        option.is_malformed = false;
        option.is_invalid = false;

        return { token_enum::OPTION, option };
    }

    LLARM_CONSTEVAL lexeme immed(const immed_settings& settings = {}) {
        IMM imm{};

        imm.number = 0;
        imm.msb = settings.msb;
        imm.divisor_constraint = settings.divisor;
        imm.start_value = 0;
        imm.end_value = 0;
        imm.has_msb_comparison = settings.is_msb_rangable;
        imm.is_rotateable = false;
        imm.is_negative = false;
        imm.is_malformed = false;
        imm.is_invalid = false;

        return { token_enum::IMMED, imm };
    }

    LLARM_CONSTEVAL lexeme immed(const u8 msb) {
        IMM imm{};
        imm.msb = msb;
        imm.has_msb_comparison = true;
        return { token_enum::IMMED, imm };
    }

    LLARM_CONSTEVAL lexeme immed(const u8 msb, const u8 multiplier) {
        IMM imm{};
        imm.msb = msb;
        imm.divisor_constraint = multiplier;
        imm.has_msb_comparison = true;
        return { token_enum::IMMED, imm };
    }

    LLARM_CONSTEVAL lexeme immed_range(const u8 start_val, const u8 end_val) {
        IMM imm{};
        imm.start_value = start_val;
        imm.end_value = end_val;
        return { token_enum::IMMED, imm };
    }

    LLARM_CONSTEVAL lexeme immed_rotate() {
        IMM imm{};
        imm.is_rotateable = true;
        return { token_enum::IMMED, imm };
    }

    LLARM_CONSTEVAL lexeme reg_list(const reg_list_settings& settings = {}) {
        REG_LIST reg_list{};

        reg_list.type = settings.reg_list_type;
        reg_list.reg_count = 0;
        reg_list.is_r15_excluded = settings.is_r15_excluded; 
        reg_list.must_have_r15 = settings.must_include_r15;
        reg_list.is_thumb_supported = settings.is_reg_list_thumb;
        reg_list.is_thumb_optional_pc = settings.is_PC_optional;
        reg_list.is_thumb_optional_lr = settings.is_LR_optional;
        reg_list.is_malformed = false;
        reg_list.is_invalid = false;
        reg_list.is_empty = false;
        reg_list.list = 0;

        return { token_enum::REG_LIST, reg_list };
    }

    LLARM_CONSTEVAL lexeme reg_list_double() {
        reg_list_settings s{};
        s.reg_list_type = reg_type::DOUBLE;
        return reg_list(s);
    }

    LLARM_CONSTEVAL lexeme reg_list_single() {
        reg_list_settings s{};
        s.reg_list_type = reg_type::SINGLE;
        return reg_list(s);
    }

    LLARM_CONSTEVAL lexeme reg_list_thumb() {
        reg_list_settings s{};
        s.is_reg_list_thumb = true;
        return reg_list(s);
    }

    LLARM_CONSTEVAL lexeme reg_list_thumb_optional_PC() {
        reg_list_settings s{};
        s.is_reg_list_thumb = true;
        s.is_PC_optional = true;
        return reg_list(s);
    }

    LLARM_CONSTEVAL lexeme reg_list_thumb_optional_LR() {
        reg_list_settings s{};
        s.is_reg_list_thumb = true;
        s.is_LR_optional = true;
        return reg_list(s);
    }

    LLARM_CONSTEVAL lexeme reg_list_must_include_PC() {
        reg_list_settings s{};
        s.must_include_r15 = true;
        return reg_list(s);
    }

    LLARM_CONSTEVAL lexeme reg_list_must_exclude_PC() {
        reg_list_settings s{};
        s.is_r15_excluded = true;
        return reg_list(s);
    }

    LLARM_CONSTEVAL lexeme token(const token_enum t) {
        return { t };
    }
}