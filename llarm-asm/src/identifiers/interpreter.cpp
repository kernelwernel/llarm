#include "interpreter.hpp"
#include "shared/util.hpp"
#include "shared/out.hpp"

#include <string>
#include <cctype>
#include <algorithm>

#include <algorithm>
#include <vector>
#include <string>
#include <string_view>

interpreter::tokens_t interpreter::tokenize(const std::string &code) {
    if (code.empty()) {
        shared::out::error("Empty instruction string for tokenization is invalid");
    }

    std::vector<std::string_view> raw_tokens;
    std::size_t start = 0;

    const std::string instruction = strip(code);

    const std::string_view special_delims = "[]^!-#";
    const std::string_view whitespace_delims = " ,";

    while (start < instruction.size()) {
        const char c = instruction[start];

        if (whitespace_delims.find(c) != std::string_view::npos) {
            ++start;
            continue;
        }

        if (special_delims.find(c) != std::string_view::npos) {
            raw_tokens.emplace_back(&instruction[start], 1);
            ++start;
            continue;
        }

        std::size_t end = start;

        while (
            (end < instruction.size()) &&
            whitespace_delims.find(instruction[end]) == std::string_view::npos &&
            special_delims.find(instruction[end]) == std::string_view::npos
        ) {
            ++end;
        }

        raw_tokens.emplace_back(instruction.substr(start, end - start));
        start = end;
    }

    return raw_tokens;
}


void interpreter::asterisk(interpreter::lexeme_struct &lexeme) {
    lexeme.token_type = tokens::MUL_OP;
    lexeme.op = '*';
}


std::vector<interpreter::lexeme_struct> interpreter::lexer(const std::vector<std::string_view> &tokens) {
    std::vector<lexeme_struct> lexeme_vec = {};
    
    bool bracket_continuation = false;
    u16 reg_list = 0;
    u16 index = 0;
    bool is_r15_present_in_reg_list = false;
    bool is_option_bracket = false;
    
    for (const auto &raw_token : tokens) {
        const std::string_view token = raw_token;
        index++;

        // default values, will be modified later
        lexeme_struct lexeme {
            "", // mnemonic
            tokens::UNKNOWN, // token_type
            0, // immed
            0, // integer
            0, // reg
            0,
            '\0', // op
            0, // reg_list
        };

        // first mnemonic of the instruction
        if (index == 1) {
            lexeme.token_type = tokens::MNEMONIC;
            lexeme.mnemonic = raw_token;
            lexeme_vec.emplace_back(lexeme);
            continue;
        }

        if (bracket_continuation) {
            // bracket end
            if (token.back() == '}') {
                bracket_continuation = false;

                if (is_option_bracket) {
                    lexeme_vec.emplace_back(lexeme);
                    continue;
                }

                lexeme.reg_list = reg_list;

                // this distinction is important in some instructions like LDM2
                if (shared::util::bit_fetch(reg_list, 15)) {
                    lexeme.token_type = REG_LIST;
                } else {
                    lexeme.token_type = REG_LIST_NO_PC;
                }

                lexeme_vec.emplace_back(lexeme);
                continue;
            }

            if (is_integer(token)) {
                const i32 integer = fetch_integer(token);

                if (integer <= 255) {
                    lexeme.token_type = tokens::OPTION;
                    lexeme.integer = integer;
                    is_option_bracket = true;
                }
            } else if (is_reg(token)) {
                const u8 reg = identify_reg(token);
                shared::util::modify_bit<u16>(reg_list, reg, true);
            }
    
            continue;
        }

        const unsigned char first_char = token.front();

        switch (first_char) {
            case '{': bracket_continuation = true; continue;
            case '[': lexeme.token_type = tokens::MEM_START; break;
            case ']': lexeme.token_type = tokens::MEM_END; break;
            case '*': asterisk(lexeme); break;
            case '#': lexeme.token_type = tokens::HASHTAG; break;
            case '^': lexeme.token_type = tokens::CARET; break;

            // both are basically comments, so everything afterwards is ignored
            case '@': return lexeme_vec;
            case '<': return lexeme_vec; 
        }

        // check if a token has been identified from the switch above
        if (lexeme.token_type != tokens::UNKNOWN) {
            lexeme_vec.emplace_back(lexeme);
            continue;
        }

        // pre-index symbol
        if (token.size() == 1 && token.front() == '!') {
            lexeme.pre_index = true;
            lexeme.token_type = tokens::PRE_INDEX;
            lexeme_vec.emplace_back(lexeme);
            continue;
        }

        // all registers, coprocessors, and CR registers 
        // have the format of R0~R15 for regs, P0~P15
        // for coproc, and C0~C15 for CR regs. Since they
        // are similar in syntax, they're bundled up into 
        // this mechanism to analyse the token thoroughly

        const u8 num = identify_reg(token);
        const bool is_valid_range = (num != error);

        if (is_valid_range) {
            switch (token.front()) {
                case 'S':
                    lexeme.token_type = REG_SINGLE;
                    lexeme.reg = num;
                    break;

                case 'D':
                    lexeme.token_type = REG_DOUBLE;
                    lexeme.reg = num;
                    break;

                case 'R':
                    lexeme.token_type = REG;
                    lexeme.reg = num;
                    break;
                
                case 'P': 
                    lexeme.token_type = COPROCESSOR;
                    lexeme.coproc = num;
                    break;
                
                case 'C': 
                    lexeme.token_type = CR_REG;
                    lexeme.reg = num;
                    break;

                default: 
                    shared::out::dev_error("How the fuck did this happen?");
            }

            lexeme_vec.emplace_back(lexeme);
            continue;
        }

        if (token.size() == 3) {
            constexpr u32 LSL = ('L' << 16) | ('S' << 8) | 'L';
            constexpr u32 LSR = ('L' << 16) | ('S' << 8) | 'R';
            constexpr u32 ASR = ('A' << 16) | ('S' << 8) | 'R';
            constexpr u32 ROR = ('R' << 16) | ('O' << 8) | 'R';
            constexpr u32 RRX = ('R' << 16) | ('R' << 8) | 'X';

            const u32 key = (token.at(0) << 16) | (token.at(1) << 8) | token.at(2);

            switch (key) {
                case LSL: lexeme.token_type = tokens::LSL; break;
                case LSR: lexeme.token_type = tokens::LSR; break;
                case ASR: lexeme.token_type = tokens::ASR; break;
                case ROR: lexeme.token_type = tokens::ROR; break;
                case RRX: lexeme.token_type = tokens::RRX; break;
            }

            if (lexeme.token_type != tokens::UNKNOWN) {
                lexeme_vec.emplace_back(lexeme);
                continue;
            }
        }

        if (is_integer(token)) {
            const u32 num = fetch_integer(token);

            if (num <= 0b111) {
                lexeme.token_type = tokens::IMMED_3;
            } else if (num <= 0b1'1111) {
                lexeme.token_type = tokens::IMMED_5;
            } else if (num <= 0b111'1111) {
                lexeme.token_type = tokens::IMMED_7;
            } else if (num <= 0b1111'1111) {
                lexeme.token_type = tokens::IMMED_8;
            } else if (num <= 0b1111'1111'1111) {
                lexeme.token_type = tokens::IMMED_12;
            } else {
                lexeme.token_type = tokens::IMMED;
            }

            if (num == 4) {
                lexeme.token_type = INTEGER_4;
            } else if (num == 2) {
                lexeme.token_type = INTEGER_2;
            } else {
                lexeme.token_type = tokens::INTEGER;
            }

            lexeme.integer = num;

            lexeme_vec.emplace_back(lexeme);
            continue;
        }

        if (is_hex(token)) {
            const u32 num = fetch_hex(token);

            lexeme.token_type = tokens::INTEGER;
            lexeme.integer = num;

            lexeme_vec.emplace_back(lexeme);
            continue;            
        }

        const enum tokens token_type = is_cpsr_spsr_field(token);

        if (token_type != UNKNOWN) {
            lexeme.token_type = token_type; // either CPSR_FIELD or SPSR_FIELD

            lexeme_vec.emplace_back(lexeme);
            continue;
        }

        if (
            (token == "FPSID") ||
            (token == "FPSCR") ||
            (token == "FPEXC")
        ) {
            lexeme.token_type = VFP_REG_SPECIAL;
            lexeme_vec.emplace_back(lexeme);
        }

        // unidentifiable token, would be handled 
        // in different ways outside of this function
        lexeme.token_type = tokens::UNKNOWN;
        lexeme_vec.emplace_back(lexeme);

    }

    return lexeme_vec;
};


std::string interpreter::fetch_instruction(const std::string &code) {
    const std::size_t pos = code.find(' ');

    if (pos == std::string::npos) {
        return code;
    }

    return code.substr(0, pos);
}


std::string interpreter::strip(std::string str) {
    // erase leading
    str.erase(
        str.begin(), 
        std::find_if(str.begin(), str.end(), [](unsigned char ch) { 
            return !std::isspace(ch); 
        })
    );

    // erase trailing
    str.erase(
        std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) { 
            return !std::isspace(ch); 
        }).base(), str.end()
    );

    // remove all instances of '+', redundant to showcase positive integers
    str.erase(std::remove(str.begin(), str.end(), '+'), str.end());

    return str;
}


u16 interpreter::fetch_last_2_chars(const std::string_view str) {
    const std::string_view sub = (str.substr(str.size() - 2));
    return (sub.at(0) << 8) | sub.at(1);
};


bool interpreter::is_reg(const std::string_view str) {
    if (
        (str.front() != 'R') &&
        (str.front() != 'D') &&
        (str.front() != 'S')
    ) {
        return false;
    }

    const u8 reg = identify_reg(str);

    return (reg != error);
}

u8 interpreter::identify_reg(std::string_view reg) {
    if (reg.size() < 2 || reg.size() > 3) {
        return error;
    }

    if (
        (reg.front() == 'R') || // regular register
        (reg.front() == 'D') || // VFP double register
        (reg.front() == 'S') || // VFP single register
        (reg.front() == 'P') || // coprocessor num
        (reg.front() == 'C')    // CRn/CRm register
    ) {
        reg.remove_prefix(1);

        if (is_integer(reg) == false) {
            return error;
        }

        const u32 num = fetch_integer(reg);

        if (num > 31) {
            return error;
        }

        return static_cast<u8>(num);
    }
    
    // reg must be 2 characters long at this point
    if (reg.size() != 2) {
        return error;
    }

    const u16 key = (static_cast<u8>(reg[0]) << 8) | static_cast<u8>(reg[1]);

    constexpr u16 PC = ('P' << 8) | 'C';
    constexpr u16 LR = ('L' << 8) | 'R';
    constexpr u16 SP = ('S' << 8) | 'P';

    // not sure if these 2 are even officially used, but i'll add them anyway
    constexpr u16 IP = ('I' << 8) | 'P';
    constexpr u16 FP = ('F' << 8) | 'P';

    switch (key) {
        case PC: return 15;
        case LR: return 14;
        case SP: return 13;
        case IP: return 12;
        case FP: return 11;
    }

    return error;
}


bool interpreter::is_integer(const std::string_view str) {
    if (str.empty())  {
        return false;
    }

    std::size_t start = 0;

    if (str[0] == '+' || str[0] == '-') {
        start = 1;
    }

    if (start == str.size()) {
        return false;
    }

    for (std::size_t i = start; i < str.size(); ++i) {
        if (!std::isdigit(static_cast<unsigned char>(str[i]))) {
            return false;
        }
    }

    return true;
}


bool interpreter::is_hex(const std::string_view str) {
    if (str.empty()) {
        return false;
    }

    std::size_t start = 0;
    
    if (str.size() > 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        start = 2;
    }
    
    // for malformed hexes like "0x"
    if (start == str.size()) {
        return false;
    }

    for (std::size_t i = start; i < str.size(); ++i) {
        if (!std::isxdigit(static_cast<unsigned char>(str[i]))) {
            return false;
        }
    }
    
    return true;
}


interpreter::tokens interpreter::is_cpsr_spsr_field(const std::string_view token) {
    constexpr std::string_view valid_fields = "cxsf";

    if (token.size() < 6) {
        return UNKNOWN; 
    }
    
    tokens token_type;

    if (token.rfind("CPSR_", 0) == 0) {
        token_type = CPSR_FIELD;
    } else if (token.rfind("SPSR_", 0) == 0) {
        token_type = SPSR_FIELD;
    } else {
        return UNKNOWN;
    }

    const std::string_view fields = token.substr(5);

    if (fields.empty()) {
        return UNKNOWN;
    }

    if (fields.find_first_not_of(valid_fields) == std::string::npos) {
        return token_type;
    }

    return UNKNOWN;
}


i32 interpreter::fetch_integer(const std::string_view str) {
    u32 value = 0;

    for (char c : str) {
        value = value * 10 + (c - '0');
    }

    return value;
}


i32 interpreter::fetch_hex(const std::string_view str) {
    return std::stoi(std::string(str), nullptr, 16); 
}


bool interpreter::has_matching_pattern(const std::vector<interpreter::tokens> &token_pattern, const lexemes_t &lexemes) {
    u16 token_index = 0;
    u16 lexeme_index = 0;

    // if mnemonic is included, skip. Only the arguments are important
    if (lexemes.at(0).token_type == tokens::MNEMONIC) {
        token_index += 1;
    }

    // pattern mismatch is guaranteed if they're unequal in size
    if (lexemes.size() != token_pattern.size() - token_index) {
        return false;
    }

    for (std::size_t i = 0; i < lexemes.size(); i++) {
        const enum tokens pattern_token = token_pattern.at(token_index);
        const enum tokens string_token = lexemes.at(lexeme_index).token_type;

        if (string_token == pattern_token) {
            continue;
        }

        const bool is_string_token_immed = (
            (string_token == tokens::IMMED_3) ||
            (string_token == tokens::IMMED_5) ||
            (string_token == tokens::IMMED_7) ||
            (string_token == tokens::IMMED_8) ||
            (string_token == tokens::IMMED_12)  
        );

        const bool is_pattern_token_immed = (
            (pattern_token == tokens::IMMED_3) ||
            (pattern_token == tokens::IMMED_5) ||
            (pattern_token == tokens::IMMED_7) ||
            (pattern_token == tokens::IMMED_8) ||
            (pattern_token == tokens::IMMED_12)
        );

        const bool is_string_token_integer = (
            (string_token == tokens::INTEGER_4) ||
            (string_token == tokens::INTEGER_2)
        );

        const bool is_pattern_token_integer = (
            (pattern_token == tokens::INTEGER_4) ||
            (pattern_token == tokens::INTEGER_2)
        );

        if (is_pattern_token_integer && is_string_token_immed) {
            if (
                (string_token == tokens::IMMED_3) &&
                (
                    (pattern_token == tokens::INTEGER_4) ||
                    (pattern_token == tokens::INTEGER_2) 
                )
            ) {
                continue;
            }
        }

        if (is_pattern_token_immed && is_string_token_immed) {
            // an immed_3 can be represented within an immed_7, 
            // that's what this part is checking for 
            if (string_token <= pattern_token) {
                continue;
            }

            return false;
        }

        if (pattern_token == tokens::IMMED && is_string_token_immed) {
            continue;
        }

        if (pattern_token == REG_THUMB && string_token == REG) {
            if (lexemes.at(lexeme_index).reg <= 7) {
                continue;
            }

            return false;
        }

        if (pattern_token == REG_LIST_WITH_PC) {
            const u16 list = lexemes.at(lexeme_index).reg_list;

            // has R15?
            if (shared::util::bit_fetch(list, 15)) {
                continue;
            }

            return false;
        }

        if (pattern_token == REG_LIST_NO_PC) {
            const u16 list = lexemes.at(lexeme_index).reg_list;

            // does not have R15?
            if (shared::util::bit_fetch(list, 15) == false) {
                continue;
            }
            
            return false;
        }

        if (pattern_token == REG_LIST_THUMB_OPTIONAL_PC) {
            const u16 list = lexemes.at(lexeme_index).reg_list;
            
            // does not have R8~R14?
            if (shared::util::bit_range(list, 8, 14) == 0) {
                continue;
            }

            return false;
        }

        if (pattern_token == REG_LIST_THUMB_OPTIONAL_LR) {
            const u16 list = lexemes.at(lexeme_index).reg_list;
            
            // does not have R8~R13 and R15 is 0?
            if (
                (shared::util::bit_range(list, 8, 13) == 0) &&
                (shared::util::bit_fetch(list, 15) == false)
            ) {
                continue;
            }

            return false;
        }

        if (pattern_token == REG_LIST_THUMB) {
            const u16 list = lexemes.at(lexeme_index).reg_list;

            // does not have R8~R15?
            if (shared::util::bit_range(list, 8, 15) == 0) {
                continue;
            }

            return false;
        }

        if (pattern_token == REG_LIST) {
            if (
                (string_token == REG_LIST_WITH_PC) ||
                (string_token == REG_LIST_NO_PC)
            ) {
                continue;
            }

            return false;
        }

        if (pattern_token == SHIFT) {
            switch (string_token) {
                case LSL: 
                case LSR:
                case ASR:
                case ROR:
                case RRX: continue;
                default: return false;
            }
        }

        return false;
    }

    return true;
}


bool interpreter::cond_match(const std::string_view cond) {
    return cond_match((cond.at(0) << 8) | (cond.at(1)));
}


bool interpreter::cond_match(const u16 cond) {
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


interpreter::lexemes_t interpreter::analyze(const std::string &str) {
    const tokens_t tokens = tokenize(str);
    return lexer(tokens);
}