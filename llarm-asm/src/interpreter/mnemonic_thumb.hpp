#pragma once

#include "../id/instruction_id.hpp"
#include "../id/cond_id.hpp"
#include "../interpreter/lexer.hpp"

#include <string>
#include <array>

using namespace internal;

struct mnemonic_struct_thumb {
    sv instruction = "";
    enum thumb_id id = thumb_id::UNKNOWN;
    enum cond_id cond_id = cond_id::UNKNOWN; // specifically for B1 instruction
};


namespace internal::mnemonic_thumb {
    using namespace internal;

    struct thumb_inst {
        sv str;
        thumb_id id;
    };

    constexpr std::array<thumb_inst, 23> pure_thumb_instructions = {{
        { "ADC", thumb_id::ADC },
        { "SBC", thumb_id::SBC },
        { "MUL", thumb_id::MUL },
        { "AND", thumb_id::AND },
        { "BIC", thumb_id::BIC },
        { "BL", thumb_id::BL },
        { "EOR", thumb_id::EOR },
        { "NEG", thumb_id::NEG },
        { "ORR", thumb_id::ORR },
        { "ROR", thumb_id::ROR },
        { "TST", thumb_id::TST },
        { "CMN", thumb_id::CMN },
        { "MVN", thumb_id::MVN },
        { "B", thumb_id::B2 },
        { "BX", thumb_id::BX },
        { "SWI", thumb_id::SWI },
        { "BKPT", thumb_id::BKPT },
        { "LDMIA", thumb_id::LDMIA },
        { "LDRSB", thumb_id::LDRSB },
        { "LDRSH", thumb_id::LDRSH },
        { "POP", thumb_id::POP },
        { "STMIA", thumb_id::STMIA },
        { "PUSH", thumb_id::PUSH }
    }};

    enum class sub_inst : u8 {
        ADD,
        SUB,
        ASR, 
        LSL, 
        LSR,
        CMP,
        MOV,
        BLX,
        LDR,
        LDRB,
        LDRH,
        STR,
        STRB,
        STRH
    };

    struct subinst_struct {
        sv str;
        sub_inst id;
    };

    constexpr std::array<subinst_struct, 14> thumb_subinstructions = {{
        { "ADD", sub_inst::ADD },
        { "SUB", sub_inst::SUB },
        { "ASR", sub_inst::ASR },
        { "LSL", sub_inst::LSL },
        { "LSR", sub_inst::LSR },
        { "CMP", sub_inst::CMP },
        { "MOV", sub_inst::MOV },
        { "BLX", sub_inst::BLX },
        { "LDR", sub_inst::LDR },
        { "LDRB", sub_inst::LDRB },
        { "LDRH", sub_inst::LDRH },
        { "STR", sub_inst::STR },
        { "STRB", sub_inst::STRB },
        { "STRH", sub_inst::STRH }
    }};

    thumb_id fetch_thumb_id(const sv code, const sv mnemonic);
    cond_id fetch_B1_cond_id(sv mnemonic);

    mnemonic_struct_thumb thumb(const std::string& code);

    thumb_id ADD(const lexemes_t& lexemes);
    thumb_id SUB(const lexemes_t& lexemes);
    thumb_id ASR(const lexemes_t& lexemes);
    thumb_id LSL(const lexemes_t& lexemes);
    thumb_id LSR(const lexemes_t& lexemes);
    thumb_id CMP(const lexemes_t& lexemes);
    thumb_id MOV(const lexemes_t& lexemes);
    thumb_id BLX(const lexemes_t& lexemes);
    thumb_id LDR(const lexemes_t& lexemes);
    thumb_id LDRB(const lexemes_t& lexemes);
    thumb_id LDRH(const lexemes_t& lexemes);
    thumb_id STR(const lexemes_t& lexemes);
    thumb_id STRB(const lexemes_t& lexemes);
    thumb_id STRH(const lexemes_t& lexemes);
}