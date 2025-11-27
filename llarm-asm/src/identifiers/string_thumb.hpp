#pragma once

#include "../instruction_id.hpp"
#include "../interpreter/interpreter.hpp"

#include <string>
#include <array>


namespace internal::ident::string_thumb {
    using namespace internal;

    using interpreter::tokens_t;
    using interpreter::lexeme_struct;
    using interpreter::lexemes_t;

    struct thumb_inst {
        std::string_view str;
        id::thumb id;
    };

    constexpr std::array<thumb_inst, 23> pure_thumb_instructions = {{
        { "ADC", id::thumb::ADC },
        { "SBC", id::thumb::SBC },
        { "MUL", id::thumb::MUL },
        { "AND", id::thumb::AND },
        { "BIC", id::thumb::BIC },
        { "BL", id::thumb::BL },
        { "EOR", id::thumb::EOR },
        { "NEG", id::thumb::NEG },
        { "ORR", id::thumb::ORR },
        { "ROR", id::thumb::ROR },
        { "TST", id::thumb::TST },
        { "CMN", id::thumb::CMN },
        { "MVN", id::thumb::MVN },
        { "B", id::thumb::B2 },
        { "BX", id::thumb::BX },
        { "SWI", id::thumb::SWI },
        { "BKPT", id::thumb::BKPT },
        { "LDMIA", id::thumb::LDMIA },
        { "LDRSB", id::thumb::LDRSB },
        { "LDRSH", id::thumb::LDRSH },
        { "POP", id::thumb::POP },
        { "STMIA", id::thumb::STMIA },
        { "PUSH", id::thumb::PUSH }
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
        std::string_view str;
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

    id::thumb thumb(const std::string &code);

    id::thumb ADD(const lexemes_t &lexemes);
    id::thumb SUB(const lexemes_t &lexemes);
    id::thumb ASR(const lexemes_t &lexemes);
    id::thumb LSL(const lexemes_t &lexemes);
    id::thumb LSR(const lexemes_t &lexemes);
    id::thumb CMP(const lexemes_t &lexemes);
    id::thumb MOV(const lexemes_t &lexemes);
    id::thumb BLX(const lexemes_t &lexemes);
    id::thumb LDR(const lexemes_t &lexemes);
    id::thumb LDRB(const lexemes_t &lexemes);
    id::thumb LDRH(const lexemes_t &lexemes);
    id::thumb STR(const lexemes_t &lexemes);
    id::thumb STRB(const lexemes_t &lexemes);
    id::thumb STRH(const lexemes_t &lexemes);
}