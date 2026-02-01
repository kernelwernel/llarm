#include "interpreter.hpp"
#include "lexer.hpp"
#include "tokens.hpp"
#include "../id/cond_id.hpp"

bool interpreter::verify_lexemes(const lexemes_t&& raw_pattern, const lexemes_t &match_pattern) {
    if (raw_pattern.size() != match_pattern.size()) {
        return false;
    }

    for (u8 i = 0; i < raw_pattern.size(); i++) {
        const lexeme raw = raw_pattern.at(i);
        const lexeme match = match_pattern.at(i);

        if (raw.token_type != match.token_type) {
            return false;
        }

        bool is_equivalent = false;

        switch (raw.token_type) {
            case token_enum::REG: is_equivalent = (raw.data.reg == match.data.reg); break;
            case token_enum::PSR: is_equivalent = (raw.data.psr == match.data.psr); break;
            case token_enum::OPTION: is_equivalent = (raw.data.option == match.data.option); break;
            case token_enum::REG_LIST: is_equivalent = (raw.data.reg_list == match.data.reg_list); break;
            case token_enum::IMMED: is_equivalent = (raw.data.imm == match.data.imm); break;

            // this is because anything other than the above are just simple tokens that don't have 
            // any important attributes associated. For example the "LSL" or "{" tokens are self explanatory.
            default: return true;
        }
 
        if (is_equivalent == false) {
            return false;
        }
    }

    return true;
}


bool interpreter::verify_tokens(const std::vector<token_enum>&& raw_tokens, const lexemes_t &match_pattern) {
    using enum token_enum;

    if (raw_tokens.size() != match_pattern.size()) {
        return false;
    }

    for (u8 i = 0; i < raw_tokens.size(); i++) {
        const token_enum match = match_pattern.at(i).token_type;
        const token_enum raw = raw_tokens.at(i);

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


lexemes_t interpreter::analyze(const sv instruction) {
    const raw_tokens_t tokens = tokens::tokenize(instruction);
    return lexer::lex(tokens);
}


sv interpreter::fetch_instruction(const sv code) {
    const std::size_t pos = code.find(' ');

    if (pos == std::string::npos) {
        return code;
    }

    return code.substr(0, pos);
}


u16 interpreter::fetch_last_2_chars(const sv str) {
    const sv sub = (str.substr(str.size() - 2));
    return (sub.at(0) << 8) | sub.at(1);
};


bool interpreter::cond_match(const sv cond) {
    return fetch_cond_id(cond) != cond_id::UNKNOWN;
}


bool interpreter::cond_match(const u16 cond) {
    return fetch_cond_id(cond) != cond_id::UNKNOWN;
}


cond_id interpreter::fetch_cond_id(const u16 cond) {
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

    switch (cond) {
        case EQ: return cond_id::EQ; 
        case NE: return cond_id::NE; 
        case CS: return cond_id::CS; 
        case HS: return cond_id::HS; 
        case CC: return cond_id::CC; 
        case LO: return cond_id::LO; 
        case MI: return cond_id::MI; 
        case PL: return cond_id::PL; 
        case VS: return cond_id::VS; 
        case VC: return cond_id::VC; 
        case HI: return cond_id::HI; 
        case LS: return cond_id::LS; 
        case GE: return cond_id::GE; 
        case LT: return cond_id::LT; 
        case GT: return cond_id::GT; 
        case LE: return cond_id::LE; 
        case AL: return cond_id::AL; 
        default: return cond_id::UNKNOWN;
    }
}

cond_id interpreter::fetch_cond_id(const sv cond) {
    if (cond.size() == 0) {
        return cond_id::NONE;
    }

    return fetch_cond_id((cond.at(0) << 8) | (cond.at(1)));
}


lexeme interpreter::reg(const reg_type reg_type, const u8 reg_num) {
    REG reg = {
        reg_type::REGULAR, // type
        reg_num, // number
        false, // is_thumb_supported
        false, // is_malformed
        false // is_invalid
    };

    lexeme lexeme = {
        token_enum::REG, // token_type
        reg // data
    };

    return lexeme;
}


lexeme interpreter::reg(const interpreter::special_reg special_reg) {
    const u8 reg_num = [=]() -> u8 {
        switch (special_reg) {
            case special_reg::PC: return 15;
            case special_reg::LR: return 14;
            case special_reg::SP: return 13;
            case special_reg::IP: return 12;
            case special_reg::FP: return 11;
        }
    }();

    REG reg = {
        reg_type::REGULAR, // type
        reg_num, // number
        false, // is_thumb_supported
        false, // is_malformed
        false // is_invalid
    };

    lexeme lexeme = {
        token_enum::REG, // token_type
        reg // data
    };

    return lexeme;
}


lexeme interpreter::reg_thumb(const u8 reg_num) {
    REG reg = {
        reg_type::REGULAR, // type
        reg_num, // number
        true, // is_thumb_supported
        false, // is_malformed
        false // is_invalid
    };

    lexeme lexeme = {
        token_enum::REG, // token_type
        reg // data
    };

    return lexeme;
}

lexeme interpreter::psr(const bool psr_type, const bool has_fields) {
    PSR psr = {
        0 // flags
    };

    if (psr_type == CPSR) {
        psr.set_cpsr();
    } else if (psr_type == SPSR) {
        psr.set_spsr();
    }

    if (has_fields == HAS_FIELDS) {
        // it doesn't matter which field is set, what's important is if at least one is set for the upcoming comparison
        psr.set_C();
    }

    lexeme lexeme = {
        token_enum::PSR, // token_type
        psr // data
    };

    return lexeme;
}


lexeme interpreter::option(const u8 number) {
    OPTION option = {
        number, // number
        false, // is_malformed
        false // is_invalid
    };

    lexeme lexeme = {
        token_enum::OPTION, // token_type
        option // data
    };

    return lexeme;
}


lexeme interpreter::immed(const immed_settings &settings) {
    IMM imm = {
        0, // number
        settings.msb, // msb
        settings.divisor, // divisor_constraint
        settings.is_msb_rangable, // has_msb_comparison
        false, // bool is_rotateable
        false, // is_negative
        false, // is_malformed
        false // is_invalid
    };

    lexeme lexeme = {
        token_enum::IMMED, // token_type
        imm // data
    };

    return lexeme;
}


lexeme interpreter::immed(const u8 msb) {
    IMM imm = {
        0, // number
        msb, // msb
        1, // divisor_constraint
        true, // has_msb_comparison
        false, // is_rotateable
        false, // is_negative
        false, // is_malformed
        false // is_invalid
    };

    lexeme lexeme = {
        token_enum::IMMED, // token_type
        imm // data
    };

    return lexeme;
}


lexeme interpreter::immed(const u8 msb, const u8 multiplier) {
    IMM imm = {
        0, // number
        msb, // msb
        multiplier, // divisor_constraint
        true, // has_msb_comparison
        false, // is_rotateable
        false, // is_negative
        false, // is_malformed
        false // is_invalid
    };

    lexeme lexeme = {
        token_enum::IMMED, // token_type
        imm // data
    };

    return lexeme;
}


lexeme interpreter::reg_list(const reg_list_settings &settings) {
    REG_LIST reg_list = {
        settings.reg_list_type, // type
        0, // reg_count
        settings.is_r15_excluded, // is_r15_excluded
        settings.must_include_r15, // must_have_r15
        settings.is_reg_list_thumb, // is_thumb_supported
        false, // is_malformed
        false, // is_invalid
        false, // is_empty
        0 // list
    };

    lexeme lexeme = {
        token_enum::IMMED, // token_type
        reg_list // data
    };

    return lexeme;
}


lexeme interpreter::token(const token_enum t) {
    lexeme lexeme = {
        t, // token_type
    };

    return lexeme;
}