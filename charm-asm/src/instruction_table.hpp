#pragma once

#include "opcodes/opcodes.hpp"
#include "identifiers/identifiers.hpp"
#include "instruction_id.hpp"

#include "../../shared/types.hpp"

#include <functional>

namespace internal::instructions {
    struct arm_opcode {
        id::arm instruction_id;
        std::function<bool(const arm_code_t&)> test;
    };

    struct thumb_opcode {
        id::thumb instruction_id;
        std::function<bool(const thumb_code_t&)> test;
    };



    static std::vector<arm_opcode> arm_table = {};
    static std::vector<thumb_opcode> thumb_table = {};



    static void arm_load() { // possibly add arguments here for which instructions should be loaded
        arm_table.push_back({ id::arm::ADC, opcodes::arm::ADC }); 
        arm_table.push_back({ id::arm::ADD, opcodes::arm::ADD }); 
        arm_table.push_back({ id::arm::AND, opcodes::arm::AND }); 
        arm_table.push_back({ id::arm::UNDEFINED, opcodes::arm::UNDEFINED }); 
        arm_table.push_back({ id::arm::NOP, opcodes::arm::NOP }); 
        arm_table.push_back({ id::arm::B, opcodes::arm::B }); 
        arm_table.push_back({ id::arm::BL, opcodes::arm::BL }); 
        arm_table.push_back({ id::arm::BIC, opcodes::arm::BIC }); 
        arm_table.push_back({ id::arm::CDP, opcodes::arm::CDP }); 
        arm_table.push_back({ id::arm::CMN, opcodes::arm::CMN }); 
        arm_table.push_back({ id::arm::CMP, opcodes::arm::CMP }); 
        arm_table.push_back({ id::arm::EOR, opcodes::arm::EOR }); 
        arm_table.push_back({ id::arm::LDC, opcodes::arm::LDC }); 
        arm_table.push_back({ id::arm::LDM1, opcodes::arm::LDM1 }); 
        arm_table.push_back({ id::arm::LDM2, opcodes::arm::LDM2 }); 
        arm_table.push_back({ id::arm::LDM3, opcodes::arm::LDM3 }); 
        arm_table.push_back({ id::arm::LDR, opcodes::arm::LDR }); 
        arm_table.push_back({ id::arm::LDRB, opcodes::arm::LDRB }); 
        arm_table.push_back({ id::arm::LDRBT, opcodes::arm::LDRBT }); 
        arm_table.push_back({ id::arm::LDRT, opcodes::arm::LDRT }); 
        arm_table.push_back({ id::arm::MCR, opcodes::arm::MCR }); 
        arm_table.push_back({ id::arm::MLA, opcodes::arm::MLA }); 
        arm_table.push_back({ id::arm::MOV, opcodes::arm::MOV }); 
        arm_table.push_back({ id::arm::MRC, opcodes::arm::MRC }); 
        arm_table.push_back({ id::arm::MRS, opcodes::arm::MRS }); 
        arm_table.push_back({ id::arm::MSR_IMM, opcodes::arm::MSR_IMM }); 
        arm_table.push_back({ id::arm::MSR_REG, opcodes::arm::MSR_REG }); 
        arm_table.push_back({ id::arm::MUL, opcodes::arm::MUL }); 
        arm_table.push_back({ id::arm::MVN, opcodes::arm::MVN }); 
        arm_table.push_back({ id::arm::ORR, opcodes::arm::ORR }); 
        arm_table.push_back({ id::arm::RSB, opcodes::arm::RSB }); 
        arm_table.push_back({ id::arm::RSC, opcodes::arm::RSC }); 
        arm_table.push_back({ id::arm::SBC, opcodes::arm::SBC }); 
        arm_table.push_back({ id::arm::STC, opcodes::arm::STC }); 
        arm_table.push_back({ id::arm::STM1, opcodes::arm::STM1 }); 
        arm_table.push_back({ id::arm::STM2, opcodes::arm::STM2 }); 
        arm_table.push_back({ id::arm::STR, opcodes::arm::STR }); 
        arm_table.push_back({ id::arm::STRB, opcodes::arm::STRB }); 
        arm_table.push_back({ id::arm::STRBT, opcodes::arm::STRBT }); 
        arm_table.push_back({ id::arm::STRT, opcodes::arm::STRT }); 
        arm_table.push_back({ id::arm::SUB, opcodes::arm::SUB }); 
        arm_table.push_back({ id::arm::SWI, opcodes::arm::SWI }); 
        arm_table.push_back({ id::arm::SWP, opcodes::arm::SWP }); 
        arm_table.push_back({ id::arm::SWPB, opcodes::arm::SWPB }); 
        arm_table.push_back({ id::arm::TEQ, opcodes::arm::TEQ }); 
        arm_table.push_back({ id::arm::TST, opcodes::arm::TST }); 
        arm_table.push_back({ id::arm::PSR, opcodes::arm::PSR }); 
        arm_table.push_back({ id::arm::STRH, opcodes::arm::STRH }); 
        arm_table.push_back({ id::arm::LDRH, opcodes::arm::LDRH }); 
        arm_table.push_back({ id::arm::LDRSB, opcodes::arm::LDRSB }); 
        arm_table.push_back({ id::arm::LDRSH, opcodes::arm::LDRSH }); 
        arm_table.push_back({ id::arm::BKPT, opcodes::arm::BKPT }); 
        arm_table.push_back({ id::arm::BLX1, opcodes::arm::BLX1 }); 
        arm_table.push_back({ id::arm::BLX2, opcodes::arm::BLX2 }); 
        arm_table.push_back({ id::arm::CLZ, opcodes::arm::CLZ }); 
        arm_table.push_back({ id::arm::BX, opcodes::arm::BX }); 
        arm_table.push_back({ id::arm::SMLAL, opcodes::arm::SMLAL }); 
        arm_table.push_back({ id::arm::SMULL, opcodes::arm::SMULL }); 
        arm_table.push_back({ id::arm::UMLAL, opcodes::arm::UMLAL }); 
        arm_table.push_back({ id::arm::UMULL, opcodes::arm::UMULL }); 
        arm_table.push_back({ id::arm::LDRD, opcodes::arm::LDRD }); 
        arm_table.push_back({ id::arm::MCRR, opcodes::arm::MCRR }); 
        arm_table.push_back({ id::arm::MRRC, opcodes::arm::MRRC }); 
        arm_table.push_back({ id::arm::PLD, opcodes::arm::PLD }); 
        arm_table.push_back({ id::arm::QADD, opcodes::arm::QADD }); 
        arm_table.push_back({ id::arm::QDADD, opcodes::arm::QDADD }); 
        arm_table.push_back({ id::arm::QDSUB, opcodes::arm::QDSUB }); 
        arm_table.push_back({ id::arm::QSUB, opcodes::arm::QSUB }); 
        arm_table.push_back({ id::arm::SMLA, opcodes::arm::SMLA }); 
        arm_table.push_back({ id::arm::SMLAW, opcodes::arm::SMLAW }); 
        arm_table.push_back({ id::arm::SMUL, opcodes::arm::SMUL }); 
        arm_table.push_back({ id::arm::SMULW, opcodes::arm::SMULW }); 
        arm_table.push_back({ id::arm::STRD, opcodes::arm::STRD }); 
        arm_table.push_back({ id::arm::FABSD, opcodes::arm::FABSD }); 
        arm_table.push_back({ id::arm::FABSS, opcodes::arm::FABSS }); 
        arm_table.push_back({ id::arm::FADDD, opcodes::arm::FADDD }); 
        arm_table.push_back({ id::arm::FADDS, opcodes::arm::FADDS }); 
        arm_table.push_back({ id::arm::FCMPD, opcodes::arm::FCMPD }); 
        arm_table.push_back({ id::arm::FCMPED, opcodes::arm::FCMPED }); 
        arm_table.push_back({ id::arm::FCMPES, opcodes::arm::FCMPES }); 
        arm_table.push_back({ id::arm::FCMPEZD, opcodes::arm::FCMPEZD }); 
        arm_table.push_back({ id::arm::FCMPEZS, opcodes::arm::FCMPEZS }); 
        arm_table.push_back({ id::arm::FCMPS, opcodes::arm::FCMPS }); 
        arm_table.push_back({ id::arm::FCMPZD, opcodes::arm::FCMPZD }); 
        arm_table.push_back({ id::arm::FCMPZS, opcodes::arm::FCMPZS }); 
        arm_table.push_back({ id::arm::FCPYD, opcodes::arm::FCPYD }); 
        arm_table.push_back({ id::arm::FCPYS, opcodes::arm::FCPYS }); 
        arm_table.push_back({ id::arm::FCVTDS, opcodes::arm::FCVTDS }); 
        arm_table.push_back({ id::arm::FCVTSD, opcodes::arm::FCVTSD }); 
        arm_table.push_back({ id::arm::FDIVD, opcodes::arm::FDIVD }); 
        arm_table.push_back({ id::arm::FDIVS, opcodes::arm::FDIVS }); 
        arm_table.push_back({ id::arm::FLDD, opcodes::arm::FLDD }); 
        arm_table.push_back({ id::arm::FLDMD, opcodes::arm::FLDMD }); 
        arm_table.push_back({ id::arm::FLDMS, opcodes::arm::FLDMS }); 
        arm_table.push_back({ id::arm::FLDMX, opcodes::arm::FLDMX }); 
        arm_table.push_back({ id::arm::FLDS, opcodes::arm::FLDS }); 
        arm_table.push_back({ id::arm::FMACD, opcodes::arm::FMACD }); 
        arm_table.push_back({ id::arm::FMACS, opcodes::arm::FMACS }); 
        arm_table.push_back({ id::arm::FMDHR, opcodes::arm::FMDHR }); 
        arm_table.push_back({ id::arm::FMDLR, opcodes::arm::FMDLR }); 
        arm_table.push_back({ id::arm::FMRDH, opcodes::arm::FMRDH }); 
        arm_table.push_back({ id::arm::FMRDL, opcodes::arm::FMRDL }); 
        arm_table.push_back({ id::arm::FMRS, opcodes::arm::FMRS }); 
        arm_table.push_back({ id::arm::FMRX, opcodes::arm::FMRX }); 
        arm_table.push_back({ id::arm::FMSCD, opcodes::arm::FMSCD }); 
        arm_table.push_back({ id::arm::FMSCS, opcodes::arm::FMSCS }); 
        arm_table.push_back({ id::arm::FMSR, opcodes::arm::FMSR }); 
        arm_table.push_back({ id::arm::FMSTAT, opcodes::arm::FMSTAT }); 
        arm_table.push_back({ id::arm::FMULD, opcodes::arm::FMULD }); 
        arm_table.push_back({ id::arm::FMULS, opcodes::arm::FMULS }); 
        arm_table.push_back({ id::arm::FMXR, opcodes::arm::FMXR }); 
        arm_table.push_back({ id::arm::FNEGD, opcodes::arm::FNEGD }); 
        arm_table.push_back({ id::arm::FNEGS, opcodes::arm::FNEGS }); 
        arm_table.push_back({ id::arm::FNMACD, opcodes::arm::FNMACD }); 
        arm_table.push_back({ id::arm::FNMACS, opcodes::arm::FNMACS }); 
        arm_table.push_back({ id::arm::FNMSCD, opcodes::arm::FNMSCD }); 
        arm_table.push_back({ id::arm::FNMSCS, opcodes::arm::FNMSCS }); 
        arm_table.push_back({ id::arm::FNMULD, opcodes::arm::FNMULD }); 
        arm_table.push_back({ id::arm::FNMULS, opcodes::arm::FNMULS }); 
        arm_table.push_back({ id::arm::FSITOD, opcodes::arm::FSITOD }); 
        arm_table.push_back({ id::arm::FSITOS, opcodes::arm::FSITOS }); 
        arm_table.push_back({ id::arm::FSQRTD, opcodes::arm::FSQRTD }); 
        arm_table.push_back({ id::arm::FSQRTS, opcodes::arm::FSQRTS }); 
        arm_table.push_back({ id::arm::FSTD, opcodes::arm::FSTD }); 
        arm_table.push_back({ id::arm::FSTMD, opcodes::arm::FSTMD }); 
        arm_table.push_back({ id::arm::FSTMS, opcodes::arm::FSTMS }); 
        arm_table.push_back({ id::arm::FSTMX, opcodes::arm::FSTMX }); 
        arm_table.push_back({ id::arm::FSTS, opcodes::arm::FSTS }); 
        arm_table.push_back({ id::arm::FSUBD, opcodes::arm::FSUBD }); 
        arm_table.push_back({ id::arm::FSUBS, opcodes::arm::FSUBS }); 
        arm_table.push_back({ id::arm::FTOSID, opcodes::arm::FTOSID }); 
        arm_table.push_back({ id::arm::FTOSIS, opcodes::arm::FTOSIS }); 
        arm_table.push_back({ id::arm::FTOUID, opcodes::arm::FTOUID }); 
        arm_table.push_back({ id::arm::FTOUIS, opcodes::arm::FTOUIS }); 
        arm_table.push_back({ id::arm::FUITOD, opcodes::arm::FUITOD }); 
        arm_table.push_back({ id::arm::FUITOS, opcodes::arm::FUITOS });
    };

    static void thumb_load() {
        thumb_table.push_back({ id::thumb::ADC, opcodes::thumb::ADC });
        thumb_table.push_back({ id::thumb::ADD1, opcodes::thumb::ADD1 });
        thumb_table.push_back({ id::thumb::ADD2, opcodes::thumb::ADD2 });
        thumb_table.push_back({ id::thumb::ADD3, opcodes::thumb::ADD3 });
        thumb_table.push_back({ id::thumb::ADD4, opcodes::thumb::ADD4 });
        thumb_table.push_back({ id::thumb::ADD5, opcodes::thumb::ADD5 });
        thumb_table.push_back({ id::thumb::ADD6, opcodes::thumb::ADD6 });
        thumb_table.push_back({ id::thumb::ADD7, opcodes::thumb::ADD7 });
        thumb_table.push_back({ id::thumb::SBC, opcodes::thumb::SBC });
        thumb_table.push_back({ id::thumb::SUB1, opcodes::thumb::SUB1 });
        thumb_table.push_back({ id::thumb::SUB2, opcodes::thumb::SUB2 });
        thumb_table.push_back({ id::thumb::SUB3, opcodes::thumb::SUB3 });
        thumb_table.push_back({ id::thumb::SUB4, opcodes::thumb::SUB4 });
        thumb_table.push_back({ id::thumb::MUL, opcodes::thumb::MUL });
        thumb_table.push_back({ id::thumb::AND, opcodes::thumb::AND });
        thumb_table.push_back({ id::thumb::ASR1, opcodes::thumb::ASR1 });
        thumb_table.push_back({ id::thumb::ASR2, opcodes::thumb::ASR2 });
        thumb_table.push_back({ id::thumb::BIC, opcodes::thumb::BIC });
        thumb_table.push_back({ id::thumb::EOR, opcodes::thumb::EOR });
        thumb_table.push_back({ id::thumb::LSL1, opcodes::thumb::LSL1 });
        thumb_table.push_back({ id::thumb::LSL2, opcodes::thumb::LSL2 });
        thumb_table.push_back({ id::thumb::LSR1, opcodes::thumb::LSR1 });
        thumb_table.push_back({ id::thumb::LSR2, opcodes::thumb::LSR2 });
        thumb_table.push_back({ id::thumb::NEG, opcodes::thumb::NEG });
        thumb_table.push_back({ id::thumb::ORR, opcodes::thumb::ORR });
        thumb_table.push_back({ id::thumb::ROR, opcodes::thumb::ROR });
        thumb_table.push_back({ id::thumb::TST, opcodes::thumb::TST });
        thumb_table.push_back({ id::thumb::CMN, opcodes::thumb::CMN });
        thumb_table.push_back({ id::thumb::CMP1, opcodes::thumb::CMP1 });
        thumb_table.push_back({ id::thumb::CMP2, opcodes::thumb::CMP2 });
        thumb_table.push_back({ id::thumb::CMP3, opcodes::thumb::CMP3 });
        thumb_table.push_back({ id::thumb::MOV1, opcodes::thumb::MOV1 });
        thumb_table.push_back({ id::thumb::MOV2, opcodes::thumb::MOV2 });
        thumb_table.push_back({ id::thumb::MOV3, opcodes::thumb::MOV3 });
        thumb_table.push_back({ id::thumb::MVN, opcodes::thumb::MVN });
        thumb_table.push_back({ id::thumb::B1, opcodes::thumb::B1 });
        thumb_table.push_back({ id::thumb::B2, opcodes::thumb::B2 });
        thumb_table.push_back({ id::thumb::BL, opcodes::thumb::BL });
        thumb_table.push_back({ id::thumb::BLX1, opcodes::thumb::BLX1 });
        thumb_table.push_back({ id::thumb::BLX2, opcodes::thumb::BLX2 });
        thumb_table.push_back({ id::thumb::BX, opcodes::thumb::BX });
        thumb_table.push_back({ id::thumb::NOP, opcodes::thumb::NOP });
        thumb_table.push_back({ id::thumb::BKPT, opcodes::thumb::BKPT });
        thumb_table.push_back({ id::thumb::SWI, opcodes::thumb::SWI });
        thumb_table.push_back({ id::thumb::LDMIA, opcodes::thumb::LDMIA });
        thumb_table.push_back({ id::thumb::LDR1, opcodes::thumb::LDR1 });
        thumb_table.push_back({ id::thumb::LDR2, opcodes::thumb::LDR2 });
        thumb_table.push_back({ id::thumb::LDR3, opcodes::thumb::LDR3 });
        thumb_table.push_back({ id::thumb::LDR4, opcodes::thumb::LDR4 });
        thumb_table.push_back({ id::thumb::LDRB1, opcodes::thumb::LDRB1 });
        thumb_table.push_back({ id::thumb::LDRB2, opcodes::thumb::LDRB2 });
        thumb_table.push_back({ id::thumb::LDRH1, opcodes::thumb::LDRH1 });
        thumb_table.push_back({ id::thumb::LDRH2, opcodes::thumb::LDRH2 });
        thumb_table.push_back({ id::thumb::LDRSB, opcodes::thumb::LDRSB });
        thumb_table.push_back({ id::thumb::LDRSH, opcodes::thumb::LDRSH });
        thumb_table.push_back({ id::thumb::POP, opcodes::thumb::POP });
        thumb_table.push_back({ id::thumb::PUSH, opcodes::thumb::PUSH });
        thumb_table.push_back({ id::thumb::STMIA, opcodes::thumb::STMIA });
        thumb_table.push_back({ id::thumb::STR1, opcodes::thumb::STR1 });
        thumb_table.push_back({ id::thumb::STR2, opcodes::thumb::STR2 });
        thumb_table.push_back({ id::thumb::STR3, opcodes::thumb::STR3 });
        thumb_table.push_back({ id::thumb::STRB1, opcodes::thumb::STRB1 });
        thumb_table.push_back({ id::thumb::STRH1, opcodes::thumb::STRH1 });
        thumb_table.push_back({ id::thumb::STRH2, opcodes::thumb::STRH2 });
    }
}