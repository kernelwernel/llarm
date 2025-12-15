#include "lexer.hpp"
#include "llarm-asm/src/interpreter/tokens.hpp"
#include "matchers.hpp"

#include "shared/out.hpp"


lexemes_t lexer::analyze(const tokens_t &tokens) {
    lexemes_t lexeme_list{};
    lexeme_list.reserve(tokens.size());

    for (const auto token : tokens) {
        lexeme lexeme{};

        // this might look repetitive but lexeme is taken as a reference in all these functions, 
        // so there's a bit of dependency stuff going on here. While only one of the functions
        // can possible return true, technically speaking it could have multiple either due to
        // a bug or something else going on that shouldn't happen. This method is easier to debug,
        // on top of guaranteeing the lexeme variable NOT being overwritten in case of a bug.

        // Additionally, the reg list check is not included here due to the multi-token nature of it.
        // That is identified in the refining process at the end of this function.

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

        llarm::out::error("Unidentifiable or invalid token \"", token, "\" in assembly string argument");
    }

    reg_list_check(lexeme_list);

    return lexeme_list;
}


void lexer::reg_list_check(lexemes_t &lexemes) {
    u8 start_pos = 0;
    u8 end_pos = 0;

    u8 pos = 0;

    for (const lexeme &lexeme : lexemes) {
        if (lexeme.token_type == token::REG_LIST_START) {
            start_pos = pos;
        }

        if (lexeme.token_type == token::REG_LIST_END) {
            end_pos = pos;
            break;
        }

        pos++;
    }

    // early return if there's no "{" and "}" tokens for a reg list 
    if (start_pos == 0 && end_pos == 0) {
        return;
    }

    if (end_pos >= start_pos) {
        llarm::out::error("Invalid register list argument to instruction, malformed \"{\" and \"}\" positions");
    }

    // after this point, it's assumed this is a reg list. This is where the verification stage starts.

    REG_LIST reg_list = {
        reg_type::UNKNOWN, // type
        0, // reg_count
        false, // is_malformed
        true, // is_invalid
        false, // is_empty
        0 // list
    };

    const u8 arg_count = (end_pos - start_pos) - 1;

    // check the difference between the start and end indexes to see if it's empty
    if (arg_count == 0) {
        reg_list.is_empty = true;
        reg_list.is_malformed = true;

        reg_list_categorize(lexemes, reg_list, start_pos, end_pos);
        return;
    } else if (arg_count == 3) { // this could be a range based reglist, so for example "{ R0-R3 }"
        const u8 middle_index = start_pos + 2; // exact same as end_pos - 2

        if (lexemes.at(middle_index).token_type == token::MIN_OP) {
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
        case reg_type::UNKNOWN:
        case reg_type::FPSID:
        case reg_type::FPSCR:
        case reg_type::FPEXC: 
            llarm::out::error("Invalid register list argument for first element, make sure it's valid");
    }

    u8 reg_minimum = first_reg.number;

    for (u8 i = first_reg_index; i < last_reg_index; i++) {
        const REG reg_entry = lexemes.at(i).data.reg;

        if (
            (reg_entry.number != ++reg_minimum) || // order MUST be consecutive (1, 2, 3 etc)
            (reg_entry.type != reg_list_type) ||
            (reg_entry.is_malformed) ||
            (reg_entry.is_reg_vfp_special)
        ) {
            reg_list.is_malformed = true;
            reg_list_categorize(lexemes, reg_list, start_pos, end_pos);
            return;
        }

        reg_list.reg_count++;
        llarm::util::modify_bit(reg_list.list, reg_entry.number, true);
    }

    reg_list_categorize(lexemes, reg_list, start_pos, end_pos);
    return;
}


void lexer::reg_list_range(lexemes_t &lexemes, const u8 start_pos, const u8 end_pos) { 
    const REG first_reg  = lexemes.at(start_pos + 1).data.reg;
    const REG second_reg = lexemes.at(start_pos + 3).data.reg;

    const reg_type first_reg_type  = first_reg.type;
    const reg_type second_reg_type = second_reg.type;

    const bool reg_type_mismatch = (first_reg_type != second_reg_type); 

    const bool reg_type_unrecognised = (
        (first_reg_type == reg_type::UNKNOWN) || 
        (second_reg_type == reg_type::UNKNOWN)
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


void reg_list_categorize(lexemes_t &lexemes, REG_LIST &reg_list, const u8 start_pos, const u8 end_pos) {
    lexemes.erase(lexemes.begin() + start_pos, lexemes.begin() + end_pos);

    lexeme reg_list_lexeme = {
        token::REG_LIST,
        reg_list
    };

    lexemes.insert(lexemes.begin() + start_pos, reg_list_lexeme);
}


bool lexer::reg_check(lexeme &lexeme, const llarm::string_view token) {
    const REG reg = matchers::reg(token);
    
    if (reg.is_invalid) {
        return false;
    }

    switch (reg.type) {
        case reg_type::REGULAR: lexeme.token_type = token::REG; break;
        case reg_type::SINGLE: lexeme.token_type = token::REG_SINGLE; break;
        case reg_type::DOUBLE: lexeme.token_type = token::REG_DOUBLE; break;
        case reg_type::COPROC: lexeme.token_type = token::REG_COPROC; break;
        case reg_type::CR: lexeme.token_type = token::REG_CR; break;
        default: lexeme.token_type = token::UNKNOWN; // this part shouldn't be reachable
    }

    lexeme.data.reg = reg;
    return true;
}


bool lexer::psr_check(lexeme &lexeme, const llarm::string_view token) {
    const PSR psr = matchers::cpsr_spsr(token);

    if (psr.is_invalid()) {
        return false;
    }

    const bool has_fields = (psr.has_C() + psr.has_F() + psr.has_S() + psr.has_X() != 0);

    if (has_fields) {
        if (psr.is_cpsr()) {
            lexeme.token_type = token::CPSR;
        } else if (psr.is_spsr()) {
            lexeme.token_type = token::SPSR;
        } else {
            llarm::out::dev_error("Invalid PSR found for assembly interpreter (PSR fields)");
        }
    } else {
        if (psr.is_cpsr()) {
            lexeme.token_type = token::CPSR;
        } else if (psr.is_spsr()) {
            lexeme.token_type = token::SPSR;
        } else {
            llarm::out::dev_error("Invalid PSR found for assembly interpreter");
        }
    }

    lexeme.data.psr = psr;
    return true;
}


bool lexer::imm_check(lexeme &lexeme, const llarm::string_view token) {
    const IMM imm = matchers::immediate(token);

    if (imm.is_invalid) {
        return false;
    }

    lexeme.token_type = token::IMMED;
    return true;
}


bool lexer::character_check(lexeme &lexeme, const llarm::string_view token) {
    const enum token token_candidate = matchers::character(token);

    if (token_candidate == token::UNKNOWN) {
        return false;
    }

    lexeme.token_type = token_candidate;
    return true;
}


bool lexer::address_check(lexeme &lexeme, const llarm::string_view token) {
    const enum token address_candidate = matchers::address_mode(token);

    if (address_candidate == token::UNKNOWN) {
        return false;
    }

    lexeme.token_type = address_candidate;
    return true;
}