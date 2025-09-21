#include "interpreter.hpp"
#include "shared/util.hpp"
#include <cctype>
#include <algorithm>


std::vector<std::string> interpreter::tokenize(const std::string &code) {
    if (code.empty()) {
        shared::out::error("Empty instruction string for tokenization is invalid");
    }

    std::vector<std::string> raw_tokens;
    std::size_t start = 0;

    const std::string instruction = strip(code);

    // characters that count as delimiters
    const std::string_view delimiters = " ,";

    while (start < instruction.size()) {
        // skip leading delimiters
        start = instruction.find_first_not_of(delimiters, start);

        if (start == std::string::npos) {
            break;
        }

        // find end of token
        const std::size_t end = instruction.find_first_of(delimiters, start);

        raw_tokens.emplace_back(instruction.substr(start, end - start));

        if (end == std::string::npos) {
            break;
        }

        start = end + 1;
    }

    return raw_tokens;
}


std::vector<interpreter::lexeme_struct> interpreter::lexer(const std::vector<std::string> &tokens) {
    std::vector<lexeme_struct> lexeme_vec = {};

    bool reg_list_continuation = false;
    std::vector<u8> reg_list = {};

    for (const auto &raw_token : tokens) {
        const std::string_view token = raw_token;

        // default values, will be modified later
        lexeme_struct lexeme {
            tokens::UNKNOWN, // token_type
            0, // immed
            0, // integer
            0, // reg
            '\0', // op
            {} // reg_list
        };

        const u8 reg = identify_reg(token);
        const bool is_register = (reg != error);

        if (is_register) {
            lexeme.token_type = REG;
            lexeme.reg = reg;

            lexeme_vec.emplace_back(lexeme);
            continue;
        }
        
        if (reg_list_continuation) {
            if (token.back() == '}') {
                reg_list_continuation = false;

                lexeme.token_type = REG_LIST;
                lexeme.reg_list = reg_list;

                lexeme_vec.emplace_back(lexeme);
                continue;
            }

            const u8 reg = identify_reg(token);

            reg_list.push_back(reg);
            continue;
        }

        if (token.front() == '#') {
            if (is_integer(token.substr(1)) == false) {
                shared::out::error("Invalid immediate value argument in thumb instruction interpretation");
            }

            const u32 num = fetch_integer(token.substr(1));

            if (num <= 0b111) {
                lexeme.token_type = tokens::IMMED_3;
            } else if (num <= 0b1'1111) {
                lexeme.token_type = tokens::IMMED_5;
            } else if (num <= 0b111'1111) {
                lexeme.token_type = tokens::IMMED_7;
            } else if (num <= 0b1111'1111) {
                lexeme.token_type = tokens::IMMED_8;
            } else {
                shared::out::error("Invalid immediate value argument in thumb instruction, maybe try reducing the MSB index");
            }

            lexeme.immed = num;

            lexeme_vec.emplace_back(lexeme);
            continue;
        }

        // might change this in the future
        if (token.front() == '*') {
            lexeme.token_type = tokens::MUL_OP;
            lexeme.op = '*';

            lexeme_vec.emplace_back(lexeme);
            continue;            
        }

        if (token.front() == '{') {
            reg_list_continuation = true;
            continue;
        }

        if (token.front() == '[') {
            lexeme.token_type = tokens::MEM_START;
            lexeme_vec.emplace_back(lexeme);
            continue;
        }

        if (token.front() == ']') {
            lexeme.token_type = tokens::MEM_END;
            lexeme_vec.emplace_back(lexeme);
            continue;
        }


        if (is_integer(token)) {
            const u32 num = fetch_integer(token);
            
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

    return str;
}


u8 interpreter::identify_reg(std::string_view reg) {
    if (reg.size() < 2) {
        return error;
    }

    if (reg.front() == 'R') {
        reg.remove_prefix(1);

        if (is_integer(reg) == false) {
            return error;
        }

        const u32 num = fetch_integer(reg);

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


u32 interpreter::fetch_integer(std::string_view str) {
    u32 value = 0;

    for (char c : str) {
        value = value * 10 + (c - '0');
    }

    return value;
}


bool interpreter::has_matching_pattern(const std::vector<interpreter::tokens> &token_pattern, const lexemes_t &lexemes) {
    if (lexemes.size() != token_pattern.size()) {
        return false;
    }

    for (std::size_t i = 0; i < lexemes.size(); i++) {
        const enum tokens pattern_token = token_pattern.at(i);
        const enum tokens string_token = lexemes.at(i).token_type;

        if (string_token == pattern_token) {
            continue;
        }

        if ((
            (pattern_token == tokens::IMMED_3) ||
            (pattern_token == tokens::IMMED_5) ||
            (pattern_token == tokens::IMMED_7) ||
            (pattern_token == tokens::IMMED_8)
        ) && (
            (string_token == tokens::IMMED_3) ||
            (string_token == tokens::IMMED_5) ||
            (string_token == tokens::IMMED_7) ||
            (string_token == tokens::IMMED_8)
        )) {
            // an immed_3 can be represented within an immed_7, 
            // that's what this part is checking for 
            if (string_token <= pattern_token) {
                continue;
            }
        }

        if (pattern_token == REG_THUMB && string_token == REG) {
            if (lexemes.at(i).reg <= 7) {
                continue;
            }
        }

        return false;
    }

    return true;
}

