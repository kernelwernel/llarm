#include "lexer.hpp"
#include "tokens.hpp"
#include "matchers.hpp"

#include <llarm/shared/out.hpp>


lexemes_t lexer::lex(const raw_tokens_t& tokens) {
    lexemes_t lexeme_list{};
    lexeme_list.reserve(tokens.size());

    for (const auto token : tokens) {
        lexeme lexeme{};

        // this might look repetitive but lexeme is taken as a reference in all these functions, 
        // so there's a bit of dependency stuff going on here. While only one of the functions
        // can possible return true, technically speaking it could have multiple either due to
        // a bug or something else going on that shouldn't happen. This method is easier to debug,
        // on top of guaranteeing the lexeme variable NOT being overwritten in case of a bug.

        // Additionally, the reg list and option check is not included here due to their multi-token nature.
        // That is identified in the refining process at the later stage of this function.

        if (reg_check(lexeme, token)) {
            lexeme_list.push_back(lexeme);
            continue;
        }

        if (psr_check(lexeme, token)) {
            lexeme_list.push_back(lexeme);
            continue;
        }

        if (imm_check(lexeme, token)) {
            lexeme_list.push_back(lexeme);
            continue;
        }

        if (character_check(lexeme, token)) {
            lexeme_list.push_back(lexeme);
            continue;
        }

        if (address_check(lexeme, token)) {
            lexeme_list.push_back(lexeme);
            continue;
        }

        // end of instruction arguments, return earlier if a comment was found
        if (comment_check(lexeme, token)) {
            return lexeme_list;
        }

        llarm::out::error("Unidentifiable or invalid token \"", token, "\" in assembly string argument");
    }

    // check for whether it could contain an option or reg list through brackets
    u8 start_pos = 0; // "{"
    u8 end_pos = 0; // "}"

    u8 pos = 0;

    for (const lexeme& lexeme : lexeme_list) {
        if (lexeme.token_type == token_enum::REG_LIST_START) {
            start_pos = pos;
            continue;
        }

        if (lexeme.token_type == token_enum::REG_LIST_END) {
            end_pos = pos;
            break;
        }

        pos++;
    }
    
    // early return if there's no "{" and "}" tokens for a reg list or option
    if (start_pos == 0 && end_pos == 0) {
        return lexeme_list;
    }

    if (end_pos >= start_pos) {
        llarm::out::error("Invalid register list argument to instruction, malformed \"{\" and \"}\" positions");
    }

    const u8 arg_count = static_cast<u8>(end_pos - start_pos) - 1;

    if (arg_count == 1) {
        option_check(lexeme_list, start_pos, end_pos);
    } else {
        const u8 pre_size = static_cast<u8>(lexeme_list.size());
    
        reg_list_check(lexeme_list, start_pos, end_pos);
    
        const bool is_reg_list = (pre_size != lexeme_list.size()); 
    
        if (is_reg_list == false) {
            llarm::out::error("Invalid arguments in brackets, only register lists and options are supported");   
        }
    }

    return lexeme_list;
}


void lexer::option_check(lexemes_t& lexemes, const u8 start_pos, const u8 end_pos) {
    const lexeme arg = lexemes.at(start_pos + 1);
    
    if (arg.token_type != token_enum::IMMED) {
        return;
    }
    
    // options can only be u8

    OPTION option = {
        0, // number
        false, // is_malformed
        false // is_invalid
    };

    const IMM imm = arg.data.imm;

    if (imm.is_malformed) {
        option.is_malformed = true;
    }

    if (imm.is_invalid) {
        option.is_invalid = true;
    }

    if (imm.number > 255) {
        option.is_malformed = true;
    }

    lexeme lex = {
        token_enum::OPTION, // token_type
        option
    };

    lexemes.erase(lexemes.begin() + start_pos, lexemes.begin() + end_pos);
    lexemes.insert(lexemes.begin() + start_pos, lex);
}


void lexer::reg_list_check(lexemes_t& lexemes, const u8 start_pos, const u8 end_pos) {
    REG_LIST reg_list = {
        reg_type::UNKNOWN_REG, // type
        0, // reg_count
        false, // is_r15_excluded
        false, // must_have_r15
        false, // is_thumb_supported
        false, // is_thumb_optional_pc;
        false, // is_thumb_optional_lr;
        false, // is_malformed
        true, // is_invalid
        false, // is_empty
        0 // list
    };

    const u8 arg_count = static_cast<u8>(end_pos - start_pos) - 1;

    // check the difference between the start and end indexes to see if it's empty
    if (arg_count == 0) {
        reg_list.is_empty = true;
        reg_list.is_malformed = true;

        reg_list_categorize(lexemes, reg_list, start_pos, end_pos);
        return;
    } else if (arg_count == 3) { // this could be a range based reglist, so for example "{ R0-R3 }"
        const u8 middle_index = start_pos + 2; // exact same as end_pos - 2

        if (lexemes.at(middle_index).token_type == token_enum::MIN_OP) {
            reg_list_range(lexemes, start_pos, end_pos);
            return;
        }
    }

    const u8 first_reg_index = start_pos + 1;
    const u8 last_reg_index = end_pos + 1;

    for (u8 i = first_reg_index; i < last_reg_index; i++) {
        if (lexemes.at(i).data.reg.is_invalid) {
            llarm::out::error("Invalid element in register list argument, make sure to add registers only to the list");
        }

        if (lexemes.at(i).data.reg.is_malformed) {
            llarm::out::error("Malformed register element in register list argument, make sure they are valid");
        }
    }

    const REG first_reg = lexemes.at(first_reg_index).data.reg;
    const reg_type reg_list_type = first_reg.type;

    switch (reg_list_type) {
        // valid
        case reg_type::REGULAR:
        case reg_type::SINGLE:
        case reg_type::DOUBLE:
        case reg_type::COPROC:
        case reg_type::CR: 
            break;

        // invalid/malformed, these shouldn't be in the list
        case reg_type::UNKNOWN_REG:
        case reg_type::FPSID:
        case reg_type::FPSCR:
        case reg_type::FPEXC: 
        case reg_type::FP_WILDCARD:
            llarm::out::error("Invalid register list argument for first element, make sure it's valid");
    }

    u8 reg_minimum = first_reg.number;

    for (u8 i = first_reg_index; i < last_reg_index; i++) {
        const REG reg_entry = lexemes.at(i).data.reg;

        if (
            (reg_entry.number != ++reg_minimum) || // order MUST be consecutive (1, 2, 3 etc)
            (reg_entry.type != reg_list_type) ||
            (reg_entry.is_malformed)
        ) {
            reg_list.is_malformed = true;
            reg_list_categorize(lexemes, reg_list, start_pos, end_pos);
            return;
        }

        reg_list.reg_count++;
        llarm::util::modify_bit(reg_list.list, reg_entry.number, true);
    }

    reg_list.is_thumb_supported = (reg_minimum <= 7);

    reg_list_categorize(lexemes, reg_list, start_pos, end_pos);
    return;
}


void lexer::reg_list_range(lexemes_t& lexemes, const u8 start_pos, const u8 end_pos) { 
    const REG first_reg  = lexemes.at(start_pos + 1).data.reg;
    const REG second_reg = lexemes.at(start_pos + 3).data.reg;

    const reg_type first_reg_type  = first_reg.type;
    const reg_type second_reg_type = second_reg.type;

    const bool reg_type_mismatch = (first_reg_type != second_reg_type); 

    const bool reg_type_unrecognised = (
        (first_reg_type == reg_type::UNKNOWN_REG) || 
        (second_reg_type == reg_type::UNKNOWN_REG)
    );

    const bool reg_num_malformed = (first_reg.number >= second_reg.number);

    REG_LIST reg_list;

    if (reg_type_mismatch || reg_type_unrecognised || reg_num_malformed) {

        reg_list.is_malformed = true;

        reg_list_categorize(lexemes, reg_list, start_pos, end_pos);
        return;
    }

    reg_list.type = first_reg.type;
    reg_list.is_malformed = false;
    reg_list.is_invalid = false;
    reg_list.is_empty = false;

    for (u8 i = first_reg.number; i <= second_reg.number; i++) {
        llarm::util::modify_bit(reg_list.list, i, true);
        reg_list.reg_count++;
    }

    reg_list_categorize(lexemes, reg_list, start_pos, end_pos);
    return;
}

void lexer::reg_list_categorize(lexemes_t& lexemes, REG_LIST& reg_list, const u8 start_pos, const u8 end_pos) {
    lexemes.erase(lexemes.begin() + start_pos, lexemes.begin() + end_pos);

    lexeme reg_list_lexeme = {
        token_enum::REG_LIST,
        reg_list
    };

    lexemes.insert(lexemes.begin() + start_pos, reg_list_lexeme);
}


bool lexer::reg_check(lexeme& lexeme, const sv token) {
    const REG reg = matchers::reg(token);
    
    if (reg.is_invalid) {
        return false;
    }

    if (reg.type != reg_type::UNKNOWN_REG) {
        lexeme.token_type = token_enum::REG;
    }

    lexeme.data.reg = reg;
    return true;
}


bool lexer::psr_check(lexeme& lexeme, const sv token) {
    PSR psr = matchers::cpsr_spsr(token);

    if (psr.is_invalid()) {
        return false;
    }

    lexeme.token_type = token_enum::PSR;
    lexeme.data.psr = psr;
    return true;
}


bool lexer::imm_check(lexeme& lexeme, const sv token) {
    const IMM imm = matchers::immediate(token);

    if (imm.is_invalid) {
        return false;
    }

    lexeme.token_type = token_enum::IMMED;
    lexeme.data.imm = imm;
    return true;
}


bool lexer::character_check(lexeme& lexeme, const sv token) {
    const token_enum token_candidate = matchers::character(token);

    if (token_candidate == token_enum::UNKNOWN) {
        return false;
    }

    lexeme.token_type = token_candidate;
    return true;
}


bool lexer::address_check(lexeme& lexeme, const sv token) {
    const token_enum address_candidate = matchers::address_mode(token);

    if (address_candidate == token_enum::UNKNOWN) {
        return false;
    }

    lexeme.token_type = address_candidate;
    return true;
}


bool lexer::comment_check(lexeme& lexeme, const sv token) {
    const bool is_comment = matchers::comment(token);

    if (is_comment) {
        lexeme.token_type = token_enum::COMMENT;
        return true;
    }

    return false;
}