#pragma once

#include "../instruction_id.hpp"
#include "../identifiers/interpreter.hpp"

#include "shared/types.hpp"

using namespace internal;

namespace internal::generators {
    enum class shifters : u8 {
        NONE,
        REG_SHIFT,
        IMM_SHIFT,
        IMM_32,
        LS_IMM,
        LS_REG,
        LS_SCALED,
    };

    struct arguments {
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

    u32 S_R_R_1(const id::arm instruction, const arguments &arg) {
        switch (instruction) {
            case id::arm::ORR:
            case id::arm::RSB:
            case id::arm::RSC:
            case id::arm::SBC:
            case id::arm::BIC:
            case id::arm::EOR:
            case id::arm::ADC:
            case id::arm::ADD:
            case id::arm::AND: 
            default: shared::out::dev_error("Invalid configuration to S_R_R_1 pattern of instruction generation")
        }

        return 
    }


    u32 arm(const id::arm instruction, const arguments &arg) {
        switch (instruction) {
            case id::arm::UNKNOWN: 
            case id::arm::UNDEFINED:  
            case id::arm::ADC: S R R 1
            case id::arm::ADD: S R R 1
            case id::arm::AND: S R R 1
            case id::arm::NOP:  
            case id::arm::B:
            case id::arm::BL:
            case id::arm::BIC: S R R 1
            case id::arm::CDP: coproc
            case id::arm::CMN: R 1
            case id::arm::CMP: R 1
            case id::arm::EOR: S R R 1
            case id::arm::LDC: coproc
            case id::arm::LDM1:  
            case id::arm::LDM2:  
            case id::arm::LDM3:  
            case id::arm::LDR: R 2
            case id::arm::LDRB: R 2
            case id::arm::LDRBT: R 2 
            case id::arm::LDRT: R 2
            case id::arm::MCR: coproc 
            case id::arm::MLA: S R R R R
            case id::arm::MOV: S R 1
            case id::arm::MRC: coproc
            case id::arm::MRS: R PSR
            case id::arm::MSR_IMM:  TODO
            case id::arm::MSR_REG:  TODO
            case id::arm::MUL: S R R R 
            case id::arm::MVN: S R 1
            case id::arm::ORR: S R R 1
            case id::arm::RSB: S R R 1
            case id::arm::RSC: S R R 1
            case id::arm::SBC: S R R 1
            case id::arm::STC:  
            case id::arm::STM1:  
            case id::arm::STM2:  
            case id::arm::STR: R 2
            case id::arm::STRB: R 2
            case id::arm::STRBT: R 2
            case id::arm::STRT: R 2
            case id::arm::SUB: S R R 1
            case id::arm::SWI:  
            case id::arm::SWP: R R M R M
            case id::arm::SWPB: R R M R M
            case id::arm::TEQ: R 1
            case id::arm::TST: R 1
            case id::arm::PSR:  
            case id::arm::STRH: R 3
            case id::arm::LDRH: R 3
            case id::arm::LDRSB: R 3
            case id::arm::LDRSH: R 3
            case id::arm::BKPT:  
            case id::arm::BLX1:  
            case id::arm::BLX2: R
            case id::arm::CLZ: R R
            case id::arm::BX: R
            case id::arm::SMLAL:  
            case id::arm::SMULL:  
            case id::arm::UMLAL:  
            case id::arm::UMULL:  
            case id::arm::LDRD: R 3
            case id::arm::MCRR: 
            case id::arm::MRRC:  
            case id::arm::PLD: 2
            case id::arm::QADD: R R R
            case id::arm::QDADD: R R R
            case id::arm::QDSUB: R R R
            case id::arm::QSUB: R R R
            case id::arm::SMLAXY: XY R R R R
            case id::arm::SMLALXY:
            case id::arm::SMLAWY: Y R R R R
            case id::arm::SMULXY: XY R R R
            case id::arm::SMULWY: Y R R R
            case id::arm::STRD: R 3
            case id::arm::FABSD: D D
            case id::arm::FABSS: S S
            case id::arm::FADDD: D D D
            case id::arm::FADDS: S S S
            case id::arm::FCMPD: D D
            case id::arm::FCMPED: D D
            case id::arm::FCMPES: S S
            case id::arm::FCMPEZD: D
            case id::arm::FCMPEZS: S
            case id::arm::FCMPS: S S
            case id::arm::FCMPZD: D
            case id::arm::FCMPZS: S
            case id::arm::FCPYD: D D
            case id::arm::FCPYS: S S
            case id::arm::FCVTDS: D S
            case id::arm::FCVTSD: S D
            case id::arm::FDIVD: D D D
            case id::arm::FDIVS: S S S 
            case id::arm::FLDD:  
            case id::arm::FLDMD:  
            case id::arm::FLDMS:  
            case id::arm::FLDMX:  
            case id::arm::FLDS:  
            case id::arm::FMACD:  
            case id::arm::FMACS:  
            case id::arm::FMDHR:  
            case id::arm::FMDLR:  
            case id::arm::FMRDH:  
            case id::arm::FMRDL:  
            case id::arm::FMRS:  
            case id::arm::FMRX:  
            case id::arm::FMSCD:  
            case id::arm::FMSCS:  
            case id::arm::FMSR:  
            case id::arm::FMSTAT:  
            case id::arm::FMULD:  
            case id::arm::FMULS:  
            case id::arm::FMXR:  
            case id::arm::FNEGD:  
            case id::arm::FNEGS:  
            case id::arm::FNMACD:  
            case id::arm::FNMACS:  
            case id::arm::FNMSCD:  
            case id::arm::FNMSCS:  
            case id::arm::FNMULD:  
            case id::arm::FNMULS:  
            case id::arm::FSITOD:  
            case id::arm::FSITOS:  
            case id::arm::FSQRTD:  
            case id::arm::FSQRTS:  
            case id::arm::FSTD:  
            case id::arm::FSTMD:  
            case id::arm::FSTMS:  
            case id::arm::FSTMX:  
            case id::arm::FSTS:  
            case id::arm::FSUBD:  
            case id::arm::FSUBS:  
            case id::arm::FTOSID:  
            case id::arm::FTOSIS:  
            case id::arm::FTOUID:  
            case id::arm::FTOUIS:  
            case id::arm::FUITOD:  
            case id::arm::FUITOS: 
            case id::arm::CDP2: 
            case id::arm::LDC2: 
            case id::arm::MCR2: 
            case id::arm::MRC2: 
            case id::arm::STC2: 
        }
    }
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