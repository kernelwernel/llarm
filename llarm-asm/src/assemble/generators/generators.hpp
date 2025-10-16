#pragma once

#include "../../instruction_id.hpp"

#include "shared/types.hpp"

using namespace internal;

namespace internal::generators {
    /*
    enum class shifters : u8 {
        NONE,
        REG_SHIFT,
        IMM_SHIFT,
        IMM_32,
        LS_IMM,
        LS_REG,
        LS_SCALED,
        LS_IMM_PRE,
        LS_REG_PRE,
        LS_SCALED_PRE,
        LS_IMM_POST,
        LS_REG_POST,
        LS_SCALED_POST,
    };
    */

    struct arguments {
        bool has_S;
        u8 cond;
        u8 first_reg;
        u8 second_reg;
        u8 third_reg;
        u8 fourth_reg;
        u16 reg_list;
        u32 first_int;
        u32 second_int;
        u32 third_int;
    };

    struct shift {
        bool I;
        bool S;
        u16 shifter_code;
    };

    u32 data_instruction(const id::arm instruction, const arguments &arg);
    u32 ls_instruction(const id::arm instruction, const arguments &arg);

    u32 arm(const id::arm id, const arguments &args);
}








    /*
            switch (id) {
                case id::thumb::UNDEFINED: return "UNDEFINED";
                case id::thumb::ADC: return "ADC";
                case id::thumb::ADD1: return "ADD1";
                case id::thumb::ADD2: return "ADD2";
                case id::thumb::ADD3: return "ADD3";
                case id::thumb::ADD4: return "ADD4";
                case id::thumb::ADD5: return "ADD5";
                case id::thumb::ADD6: return "ADD6";
                case id::thumb::ADD7: return "ADD7";
                case id::thumb::SBC: return "SBC";
                case id::thumb::SUB1: return "SUB1";
                case id::thumb::SUB2: return "SUB2";
                case id::thumb::SUB3: return "SUB3";
                case id::thumb::SUB4: return "SUB4";
                case id::thumb::MUL: return "MUL";
                case id::thumb::AND: return "AND";
                case id::thumb::ASR1: return "ASR1";
                case id::thumb::ASR2: return "ASR2";
                case id::thumb::BIC: return "BIC";
                case id::thumb::EOR: return "EOR";
                case id::thumb::LSL1: return "LSL1";
                case id::thumb::LSL2: return "LSL2";
                case id::thumb::LSR1: return "LSR1";
                case id::thumb::LSR2: return "LSR2";
                case id::thumb::NEG: return "NEG";
                case id::thumb::ORR: return "ORR";
                case id::thumb::ROR: return "ROR";
                case id::thumb::TST: return "TST";
                case id::thumb::CMN: return "CMN";
                case id::thumb::CMP1: return "CMP1";
                case id::thumb::CMP2: return "CMP2";
                case id::thumb::CMP3: return "CMP3";
                case id::thumb::MOV1: return "MOV1";
                case id::thumb::MOV2: return "MOV2";
                case id::thumb::MOV3: return "MOV3";
                case id::thumb::MVN: return "MVN";
                case id::thumb::B1: return "B1";
                case id::thumb::B2: return "B2";
                case id::thumb::BL: return "BL";
                case id::thumb::BLX1: return "BLX1";
                case id::thumb::BLX2: return "BLX2";
                case id::thumb::BX: return "BX";
                case id::thumb::NOP: return "NOP";
                case id::thumb::BKPT: return "BKPT";
                case id::thumb::SWI: return "SWI";
                case id::thumb::LDMIA: return "LDMIA";
                case id::thumb::LDR1: return "LDR1";
                case id::thumb::LDR2: return "LDR2";
                case id::thumb::LDR3: return "LDR3";
                case id::thumb::LDR4: return "LDR4";
                case id::thumb::LDRB1: return "LDRB1";
                case id::thumb::LDRB2: return "LDRB2";
                case id::thumb::LDRH1: return "LDRH1";
                case id::thumb::LDRH2: return "LDRH2";
                case id::thumb::LDRSB: return "LDRSB";
                case id::thumb::LDRSH: return "LDRSH";
                case id::thumb::POP: return "POP";
                case id::thumb::PUSH: return "PUSH";
                case id::thumb::STMIA: return "STMIA";
                case id::thumb::STR1: return "STR1";
                case id::thumb::STR2: return "STR2";
                case id::thumb::STR3: return "STR3";
                case id::thumb::STRB1: return "STRB1";
                case id::thumb::STRB2: return "STRB2";
                case id::thumb::STRH1: return "STRH1";
                case id::thumb::STRH2: return "STRH2";
            }
        }
            */