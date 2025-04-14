#pragma once

#include "../../instruction_id.hpp"

#include <charm/internal/shared/types.hpp>

#include <functional>
#include <string>
#include <map>

// the generation mechanism was benchmarked here:
// https://quick-bench.com/q/No_nYrHbcGwK5JTFl-qJtJ0ncc0

namespace internal::generators {
    namespace thumb {
        namespace math {
            std::string ADC(const u16 code); 
            std::string ADD1(const u16);
            std::string ADD2(const u16);
            std::string ADD3(const u16);
            std::string ADD4(const u16);
            std::string ADD5(const u16);
            std::string ADD6(const u16);
            std::string ADD7(const u16);
            std::string SBC(const u16);
            std::string SUB1(const u16);
            std::string SUB2(const u16);
            std::string SUB3(const u16);
            std::string SUB4(const u16);
            std::string MUL(const u16);
        }
    }
}
/*
        // logic
        { id::thumb::AND,
        { id::thumb::ASR1,
        { id::thumb::ASR2,
        { id::thumb::BIC,
        { id::thumb::EOR,
        { id::thumb::LSL1,
        { id::thumb::LSL2,
        { id::thumb::LSR1,
        { id::thumb::LSR2,
        { id::thumb::NEG,
        { id::thumb::ORR,
        { id::thumb::ROR,
        { id::thumb::TST,

        // comparison
        { id::thumb::CMN,
        { id::thumb::CMP1,
        { id::thumb::CMP2,
        { id::thumb::CMP3,

        // movement
        { id::thumb::MOV1,
        { id::thumb::MOV2,
        { id::thumb::MOV3,
        { id::thumb::MVN,

        // branching
        { id::thumb::B1,
        { id::thumb::B2,
        { id::thumb::BL,
        { id::thumb::BX,
        { id::thumb::BLX1,
        { id::thumb::BLX2,

        // misc
        { id::thumb::NOP,
        { id::thumb::SWI,
        { id::thumb::BKPT,

        // load
        { id::thumb::LDMIA,
        { id::thumb::LDR1,
        { id::thumb::LDR2,
        { id::thumb::LDR3,
        { id::thumb::LDR4,
        { id::thumb::LDRB1,
        { id::thumb::LDRB2,
        { id::thumb::LDRH1,
        { id::thumb::LDRH2,
        { id::thumb::LDRSB,
        { id::thumb::LDRSH,
        { id::thumb::POP,

        // store
        { id::thumb::STMIA,
        { id::thumb::STR1,
        { id::thumb::STR2,
        { id::thumb::STR3,
        { id::thumb::STRB1,
        { id::thumb::STRH1,
        { id::thumb::STRH2,
        { id::thumb::PUSH,
    };
    */