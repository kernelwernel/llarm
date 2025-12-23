#include "interpreter.hpp"
#include "llarm-asm/src/interpreter/lexer.hpp"
#include "llarm-asm/src/interpreter/tokens.hpp"

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
    if (raw_tokens.size() != match_pattern.size()) {
        return false;
    }

    for (u8 i = 0; i < raw_tokens.size(); i++) {
        if (raw_tokens.at(i) != match_pattern.at(i).token_type) {
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
    return cond_match((cond.at(0) << 8) | (cond.at(1)));
}


bool interpreter::cond_match(const u16 cond) {
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
        case EQ: 
        case NE: 
        case CS: 
        case HS: 
        case CC: 
        case LO: 
        case MI: 
        case PL: 
        case VS: 
        case VC: 
        case HI: 
        case LS: 
        case GE: 
        case LT: 
        case GT: 
        case LE: 
        case AL: return true;
    }

    return false;
}


lexeme interpreter::reg(const reg_type reg_type, const u8 reg_num, const bool is_thumb) {
    REG reg = {
        reg_type::REGULAR, // type
        reg_num, // number
        is_thumb, // is_thumb_supported
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
        0, // msb
        0, // divisor_constraint
        false, // has_msb_range
        false, // is_negative
        false, // is_malformed
        false // is_invalid
    };

    imm.msb = settings.msb;
    imm.divisor_constraint = settings.divisor;
    imm.has_msb_range = settings.is_msb_rangable;

    lexeme lexeme = {
        token_enum::IMMED, // token_type
        imm // data
    };

    return lexeme;
}


lexeme interpreter::immed(const u8 msb) {
    IMM imm = {
        0, // number
        0, // msb
        0, // divisor_constraint
        false, // has_msb_range
        false, // is_negative
        false, // is_malformed
        false // is_invalid
    };

    imm.msb = msb;
    imm.divisor_constraint = 1;
    imm.has_msb_range = true;

    lexeme lexeme = {
        token_enum::IMMED, // token_type
        imm // data
    };

    return lexeme;
}


lexeme interpreter::reg_list(const reg_list_settings &settings) {
    REG_LIST reg_list = {
        reg_type::UNKNOWN, // type
        0, // reg_count
        false, // is_r15_excluded
        false, // must_have_r15
        false, // is_malformed
        false, // is_invalid
        false, // is_empty
        0 // list
    };

    reg_list.type = settings.reg_list_type;
    reg_list.is_r15_excluded = settings.is_r15_excluded;
    reg_list.must_have_r15 = settings.must_include_r15;
    reg_list.is_thumb_supported = settings.is_reg_list_thumb;

    lexeme lexeme = {
        token_enum::IMMED, // token_type
        reg_list // data
    };

    return lexeme;
}


//constexpr lexeme interpreter::token(const token_enum t) {
//    constexpr lexeme lexeme = {
//        token_enum::IMMED, // token_type
//    };
//
//    return lexeme;
//}