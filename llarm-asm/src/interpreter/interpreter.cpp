#include "interpreter.hpp"
#include "lexer.hpp"
#include "tokens.hpp"
#include "../id/cond_id.hpp"

lexemes_t interpreter::analyze(const sv instruction) {
    const raw_tokens_t tokens = tokens::tokenize(instruction);
    return lexer::lex(tokens);
}


sv interpreter::fetch_instruction(const sv instruction) {
    const std::size_t pos = instruction.find(' ');

    if (pos == std::string::npos) {
        return instruction;
    }

    return instruction.substr(0, pos);
}


u16 interpreter::fetch_last_2_chars(const sv str) {
    if (str.size() < 2) {
        return 0;
    }

    const sv sub = str.substr(str.size() - 2);
    return static_cast<u16>((sub.at(0) << 8) | sub.at(1));
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
    if (cond.empty()) {
        return cond_id::NONE;
    }

    return fetch_cond_id(static_cast<u16>((cond.at(0) << 8) | cond.at(1)));
}