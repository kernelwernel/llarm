#include "../id.hpp"
#include "opcodes/opcodes.hpp"
#include "instruction_set.hpp"
#include "instructions/instructions.hpp"
#include "core/registers.hpp"
#include "memory/memory.hpp"



INSTRUCTION_SET::INSTRUCTION_SET(INSTRUCTIONS& instructions) : instructions(instructions) {
    arm_table = {
        { id::arm_instruction::ADC, { opcodes::arm::ADC, [this](const arm_code_t& code) { this->instructions.arm.math.ADC(code); } } },
        { id::arm_instruction::ADD, { opcodes::arm::ADD, [this](const arm_code_t& code) { this->instructions.arm.math.ADD(code); } } },
        { id::arm_instruction::RSB, { opcodes::arm::RSB, [this](const arm_code_t& code) { this->instructions.arm.math.RSB(code); } } },
        { id::arm_instruction::RSC, { opcodes::arm::RSC, [this](const arm_code_t& code) { this->instructions.arm.math.RSC(code); } } },
        { id::arm_instruction::SBC, { opcodes::arm::SBC, [this](const arm_code_t& code) { this->instructions.arm.math.SBC(code); } } },
        { id::arm_instruction::SUB, { opcodes::arm::SUB, [this](const arm_code_t& code) { this->instructions.arm.math.SUB(code); } } },

        { id::arm_instruction::CMN, { opcodes::arm::CMN, [this](const arm_code_t& code) { this->instructions.arm.logic.CMN(code); } } },
        { id::arm_instruction::AND, { opcodes::arm::AND, [this](const arm_code_t& code) { this->instructions.arm.logic.AND(code); } } },
        { id::arm_instruction::CMP, { opcodes::arm::CMP, [this](const arm_code_t& code) { this->instructions.arm.logic.CMP(code); } } },
        { id::arm_instruction::CLZ, { opcodes::arm::CLZ, [this](const arm_code_t& code) { this->instructions.arm.logic.CLZ(code); } } },
        { id::arm_instruction::EOR, { opcodes::arm::EOR, [this](const arm_code_t& code) { this->instructions.arm.logic.EOR(code); } } },
        { id::arm_instruction::ORR, { opcodes::arm::ORR, [this](const arm_code_t& code) { this->instructions.arm.logic.ORR(code); } } },
        { id::arm_instruction::TEQ, { opcodes::arm::TEQ, [this](const arm_code_t& code) { this->instructions.arm.logic.TEQ(code); } } },
        { id::arm_instruction::TST, { opcodes::arm::TST, [this](const arm_code_t& code) { this->instructions.arm.logic.TST(code); } } },

        { id::arm_instruction::MOV, { opcodes::arm::MOV, [this](const arm_code_t& code) { this->instructions.arm.movement.MOV(code); } } },
        { id::arm_instruction::MVN, { opcodes::arm::MVN, [this](const arm_code_t& code) { this->instructions.arm.movement.MVN(code); } } },
        { id::arm_instruction::MRS, { opcodes::arm::MRS, [this](const arm_code_t& code) { this->instructions.arm.movement.MRS(code); } } },
        { id::arm_instruction::MSR_IMM, { opcodes::arm::MSR_IMM, [this](const arm_code_t& code) { this->instructions.arm.movement.MSR_IMM(code); } } }, 
        { id::arm_instruction::MSR_REG, { opcodes::arm::MSR_REG, [this](const arm_code_t& code) { this->instructions.arm.movement.MSR_REG(code); } } }, 

        { id::arm_instruction::MLA, { opcodes::arm::MLA, [this](const arm_code_t& code) { this->instructions.arm.multiply.MLA(code); } } },
        { id::arm_instruction::MUL, { opcodes::arm::MUL, [this](const arm_code_t& code) { this->instructions.arm.multiply.MUL(code); } } },
        { id::arm_instruction::SMLAL, { opcodes::arm::SMLAL, [this](const arm_code_t& code) { this->instructions.arm.multiply.SMLAL(code); } } },
        { id::arm_instruction::SMULL, { opcodes::arm::SMULL, [this](const arm_code_t& code) { this->instructions.arm.multiply.SMULL(code); } } },
        { id::arm_instruction::UMLAL, { opcodes::arm::UMLAL, [this](const arm_code_t& code) { this->instructions.arm.multiply.UMLAL(code); } } },
        { id::arm_instruction::UMULL, { opcodes::arm::UMULL, [this](const arm_code_t& code) { this->instructions.arm.multiply.UMULL(code); } } },

        { id::arm_instruction::B, { opcodes::arm::B, [this](const arm_code_t& code) { this->instructions.arm.branching.B(code); } } },
        { id::arm_instruction::BL, { opcodes::arm::BL, [this](const arm_code_t& code) { this->instructions.arm.branching.BL(code); } } },
        { id::arm_instruction::BX, { opcodes::arm::BX, [this](const arm_code_t& code) { this->instructions.arm.branching.BX(code); } } },


        { id::arm_instruction::CDP, { opcodes::arm::CDP, [this](const arm_code_t& code) { this->instructions.arm.coprocessor_inst.CDP(code); } } },
        { id::arm_instruction::LDC, { opcodes::arm::LDC, [this](const arm_code_t& code) { this->instructions.arm.coprocessor_inst.LDC(code); } } },
        { id::arm_instruction::MCR, { opcodes::arm::MCR, [this](const arm_code_t& code) { this->instructions.arm.coprocessor_inst.MCR(code); } } },
        { id::arm_instruction::MRC, { opcodes::arm::MRC, [this](const arm_code_t& code) { this->instructions.arm.coprocessor_inst.MRC(code); } } },
        { id::arm_instruction::STC, { opcodes::arm::STC, [this](const arm_code_t& code) { this->instructions.arm.coprocessor_inst.STC(code); } } },


        { id::arm_instruction::NOP, { opcodes::arm::NOP, [this](const arm_code_t& code) { this->instructions.arm.misc.NOP(code); } } },
        { id::arm_instruction::PSR, { opcodes::arm::PSR, [this](const arm_code_t& code) { this->instructions.arm.misc.PSR(code); } } },
        { id::arm_instruction::SWI, { opcodes::arm::SWI, [this](const arm_code_t& code) { this->instructions.arm.misc.SWI(code); } } },

        { id::arm_instruction::LDM1, { opcodes::arm::LDM1, [this](const arm_code_t& code) { this->instructions.arm.load.LDM1(code); } } },
        { id::arm_instruction::LDM2, { opcodes::arm::LDM2, [this](const arm_code_t& code) { this->instructions.arm.load.LDM2(code); } } },
        { id::arm_instruction::LDM3, { opcodes::arm::LDM3, [this](const arm_code_t& code) { this->instructions.arm.load.LDM3(code); } } },
        { id::arm_instruction::LDR, { opcodes::arm::LDR, [this](const arm_code_t& code) { this->instructions.arm.load.LDR(code); } } },
        { id::arm_instruction::LDRB, { opcodes::arm::LDRB, [this](const arm_code_t& code) { this->instructions.arm.load.LDRB(code); } } },
        { id::arm_instruction::LDRBT, { opcodes::arm::LDRBT, [this](const arm_code_t& code) { this->instructions.arm.load.LDRBT(code); } } },
        { id::arm_instruction::LDRH, { opcodes::arm::LDRH, [this](const arm_code_t& code) { this->instructions.arm.load.LDRH(code); } } },
        { id::arm_instruction::LDRSB, { opcodes::arm::LDRSB, [this](const arm_code_t& code) { this->instructions.arm.load.LDRSB(code); } } },
        { id::arm_instruction::LDRSH, { opcodes::arm::LDRSH, [this](const arm_code_t& code) { this->instructions.arm.load.LDRSH(code); } } },
        { id::arm_instruction::LDRT, { opcodes::arm::LDRT, [this](const arm_code_t& code) { this->instructions.arm.load.LDRT(code); } } },


        { id::arm_instruction::STM1, { opcodes::arm::STM1, [this](const arm_code_t& code) { this->instructions.arm.store.STM1(code); } } }, 
        { id::arm_instruction::STM2, { opcodes::arm::STM2, [this](const arm_code_t& code) { this->instructions.arm.store.STM2(code); } } }, 
        { id::arm_instruction::STR, { opcodes::arm::STR, [this](const arm_code_t& code) { this->instructions.arm.store.STR(code); } } }, 
        { id::arm_instruction::STRB, { opcodes::arm::STRB, [this](const arm_code_t& code) { this->instructions.arm.store.STRB(code); } } }, 
        { id::arm_instruction::STRBT, { opcodes::arm::STRBT, [this](const arm_code_t& code) { this->instructions.arm.store.STRBT(code); } } }, 
        { id::arm_instruction::STRH, { opcodes::arm::STRH, [this](const arm_code_t& code) { this->instructions.arm.store.STRH(code); } } }, 
        { id::arm_instruction::STRT, { opcodes::arm::STRT, [this](const arm_code_t& code) { this->instructions.arm.store.STRT(code); } } }, 
        { id::arm_instruction::SWP, { opcodes::arm::SWP, [this](const arm_code_t& code) { this->instructions.arm.store.SWP(code); } } }, 
        { id::arm_instruction::SWPB, { opcodes::arm::SWPB, [this](const arm_code_t& code) { this->instructions.arm.store.SWPB(code); } } }, 
        { id::arm_instruction::LDRD, { opcodes::arm::LDRD, [this](const arm_code_t& code) { this->instructions.arm.dsp.LDRD(code); } } }, 
        { id::arm_instruction::MCRR, { opcodes::arm::MCRR, [this](const arm_code_t& code) { this->instructions.arm.dsp.MCRR(code); } } }, 
        { id::arm_instruction::MRRC, { opcodes::arm::MRRC, [this](const arm_code_t& code) { this->instructions.arm.dsp.MRRC(code); } } }, 
        { id::arm_instruction::PLD, { opcodes::arm::PLD, [this](const arm_code_t& code) { this->instructions.arm.dsp.PLD(code); } } }, 
        { id::arm_instruction::QADD, { opcodes::arm::QADD, [this](const arm_code_t& code) { this->instructions.arm.dsp.QADD(code); } } }, 
        { id::arm_instruction::QDADD, { opcodes::arm::QDADD, [this](const arm_code_t& code) { this->instructions.arm.dsp.QDADD(code); } } }, 
        { id::arm_instruction::QDSUB, { opcodes::arm::QDSUB, [this](const arm_code_t& code) { this->instructions.arm.dsp.QDSUB(code); } } }, 
        { id::arm_instruction::QSUB, { opcodes::arm::QSUB, [this](const arm_code_t& code) { this->instructions.arm.dsp.QSUB(code); } } }, 
        { id::arm_instruction::SMLA, { opcodes::arm::SMLA, [this](const arm_code_t& code) { this->instructions.arm.dsp.SMLA(code); } } }, 
        { id::arm_instruction::SMLAL, { opcodes::arm::SMLAL, [this](const arm_code_t& code) { this->instructions.arm.dsp.SMLAL(code); } } }, 
        { id::arm_instruction::SMLAW, { opcodes::arm::SMLAW, [this](const arm_code_t& code) { this->instructions.arm.dsp.SMLAW(code); } } }, 
        { id::arm_instruction::SMUL, { opcodes::arm::SMUL, [this](const arm_code_t& code) { this->instructions.arm.dsp.SMUL(code); } } }, 
        { id::arm_instruction::SMULW, { opcodes::arm::SMULW, [this](const arm_code_t& code) { this->instructions.arm.dsp.SMULW(code); } } }, 
        { id::arm_instruction::STRD, { opcodes::arm::STRD, [this](const arm_code_t& code) { this->instructions.arm.dsp.STRD(code); } } }, 
        { id::arm_instruction::FABSD, { opcodes::arm::FABSD, [this](const arm_code_t& code) { this->instructions.arm.vfp.FABSD(code); } } }, 
        { id::arm_instruction::FABSS, { opcodes::arm::FABSS, [this](const arm_code_t& code) { this->instructions.arm.vfp.FABSS(code); } } }, 
        { id::arm_instruction::FADDD, { opcodes::arm::FADDD, [this](const arm_code_t& code) { this->instructions.arm.vfp.FADDD(code); } } }, 
        { id::arm_instruction::FADDS, { opcodes::arm::FADDS, [this](const arm_code_t& code) { this->instructions.arm.vfp.FADDS(code); } } }, 
        { id::arm_instruction::FCMPD, { opcodes::arm::FCMPD, [this](const arm_code_t& code) { this->instructions.arm.vfp.FCMPD(code); } } }, 
        { id::arm_instruction::FCMPED, { opcodes::arm::FCMPED, [this](const arm_code_t& code) { this->instructions.arm.vfp.FCMPED(code); } } }, 
        { id::arm_instruction::FCMPES, { opcodes::arm::FCMPES, [this](const arm_code_t& code) { this->instructions.arm.vfp.FCMPES(code); } } }, 
        { id::arm_instruction::FCMPEZD, { opcodes::arm::FCMPEZD, [this](const arm_code_t& code) { this->instructions.arm.vfp.FCMPEZD(code); } } }, 
        { id::arm_instruction::FCMPEZS, { opcodes::arm::FCMPEZS, [this](const arm_code_t& code) { this->instructions.arm.vfp.FCMPEZS(code); } } }, 
        { id::arm_instruction::FCMPS, { opcodes::arm::FCMPS, [this](const arm_code_t& code) { this->instructions.arm.vfp.FCMPS(code); } } }, 
        { id::arm_instruction::FCMPZD, { opcodes::arm::FCMPZD, [this](const arm_code_t& code) { this->instructions.arm.vfp.FCMPZD(code); } } }, 
        { id::arm_instruction::FCMPZS, { opcodes::arm::FCMPZS, [this](const arm_code_t& code) { this->instructions.arm.vfp.FCMPZS(code); } } }, 
        { id::arm_instruction::FCPYD, { opcodes::arm::FCPYD, [this](const arm_code_t& code) { this->instructions.arm.vfp.FCPYD(code); } } }, 
        { id::arm_instruction::FCPYS, { opcodes::arm::FCPYS, [this](const arm_code_t& code) { this->instructions.arm.vfp.FCPYS(code); } } }, 
        { id::arm_instruction::FCVTDS, { opcodes::arm::FCVTDS, [this](const arm_code_t& code) { this->instructions.arm.vfp.FCVTDS(code); } } }, 
        { id::arm_instruction::FCVTSD, { opcodes::arm::FCVTSD, [this](const arm_code_t& code) { this->instructions.arm.vfp.FCVTSD(code); } } }, 
        { id::arm_instruction::FDIVD, { opcodes::arm::FDIVD, [this](const arm_code_t& code) { this->instructions.arm.vfp.FDIVD(code); } } }, 
        { id::arm_instruction::FDIVS, { opcodes::arm::FDIVS, [this](const arm_code_t& code) { this->instructions.arm.vfp.FDIVS(code); } } }, 
        { id::arm_instruction::FLDD, { opcodes::arm::FLDD, [this](const arm_code_t& code) { this->instructions.arm.vfp.FLDD(code); } } }, 
        { id::arm_instruction::FLDMD, { opcodes::arm::FLDMD, [this](const arm_code_t& code) { this->instructions.arm.vfp.FLDMD(code); } } }, 
        { id::arm_instruction::FLDMS, { opcodes::arm::FLDMS, [this](const arm_code_t& code) { this->instructions.arm.vfp.FLDMS(code); } } }, 
        { id::arm_instruction::FLDMX, { opcodes::arm::FLDMX, [this](const arm_code_t& code) { this->instructions.arm.vfp.FLDMX(code); } } }, 
        { id::arm_instruction::FLDS, { opcodes::arm::FLDS, [this](const arm_code_t& code) { this->instructions.arm.vfp.FLDS(code); } } }, 
        { id::arm_instruction::FMACD, { opcodes::arm::FMACD, [this](const arm_code_t& code) { this->instructions.arm.vfp.FMACD(code); } } }, 
        { id::arm_instruction::FMACS, { opcodes::arm::FMACS, [this](const arm_code_t& code) { this->instructions.arm.vfp.FMACS(code); } } }, 
        { id::arm_instruction::FMDHR, { opcodes::arm::FMDHR, [this](const arm_code_t& code) { this->instructions.arm.vfp.FMDHR(code); } } }, 
        { id::arm_instruction::FMDLR, { opcodes::arm::FMDLR, [this](const arm_code_t& code) { this->instructions.arm.vfp.FMDLR(code); } } }, 
        { id::arm_instruction::FMRDH, { opcodes::arm::FMRDH, [this](const arm_code_t& code) { this->instructions.arm.vfp.FMRDH(code); } } }, 
        { id::arm_instruction::FMRDL, { opcodes::arm::FMRDL, [this](const arm_code_t& code) { this->instructions.arm.vfp.FMRDL(code); } } }, 
        { id::arm_instruction::FMRS, { opcodes::arm::FMRS, [this](const arm_code_t& code) { this->instructions.arm.vfp.FMRS(code); } } }, 
        { id::arm_instruction::FMRX, { opcodes::arm::FMRX, [this](const arm_code_t& code) { this->instructions.arm.vfp.FMRX(code); } } }, 
        { id::arm_instruction::FMSCD, { opcodes::arm::FMSCD, [this](const arm_code_t& code) { this->instructions.arm.vfp.FMSCD(code); } } }, 
        { id::arm_instruction::FMSCS, { opcodes::arm::FMSCS, [this](const arm_code_t& code) { this->instructions.arm.vfp.FMSCS(code); } } }, 
        { id::arm_instruction::FMSR, { opcodes::arm::FMSR, [this](const arm_code_t& code) { this->instructions.arm.vfp.FMSR(code); } } }, 
        { id::arm_instruction::FMSTAT, { opcodes::arm::FMSTAT, [this](const arm_code_t& code) { this->instructions.arm.vfp.FMSTAT(code); } } }, 
        { id::arm_instruction::FMULD, { opcodes::arm::FMULD, [this](const arm_code_t& code) { this->instructions.arm.vfp.FMULD(code); } } }, 
        { id::arm_instruction::FMULS, { opcodes::arm::FMULS, [this](const arm_code_t& code) { this->instructions.arm.vfp.FMULS(code); } } }, 
        { id::arm_instruction::FMXR, { opcodes::arm::FMXR, [this](const arm_code_t& code) { this->instructions.arm.vfp.FMXR(code); } } }, 
        { id::arm_instruction::FNEGD, { opcodes::arm::FNEGD, [this](const arm_code_t& code) { this->instructions.arm.vfp.FNEGD(code); } } }, 
        { id::arm_instruction::FNEGS, { opcodes::arm::FNEGS, [this](const arm_code_t& code) { this->instructions.arm.vfp.FNEGS(code); } } }, 
        { id::arm_instruction::FNMACD, { opcodes::arm::FNMACD, [this](const arm_code_t& code) { this->instructions.arm.vfp.FNMACD(code); } } }, 
        { id::arm_instruction::FNMACS, { opcodes::arm::FNMACS, [this](const arm_code_t& code) { this->instructions.arm.vfp.FNMACS(code); } } }, 
        { id::arm_instruction::FNMSCD, { opcodes::arm::FNMSCD, [this](const arm_code_t& code) { this->instructions.arm.vfp.FNMSCD(code); } } }, 
        { id::arm_instruction::FNMSCS, { opcodes::arm::FNMSCS, [this](const arm_code_t& code) { this->instructions.arm.vfp.FNMSCS(code); } } }, 
        { id::arm_instruction::FNMULD, { opcodes::arm::FNMULD, [this](const arm_code_t& code) { this->instructions.arm.vfp.FNMULD(code); } } }, 
        { id::arm_instruction::FNMULS, { opcodes::arm::FNMULS, [this](const arm_code_t& code) { this->instructions.arm.vfp.FNMULS(code); } } }, 
        { id::arm_instruction::FSITOD, { opcodes::arm::FSITOD, [this](const arm_code_t& code) { this->instructions.arm.vfp.FSITOD(code); } } }, 
        { id::arm_instruction::FSITOS, { opcodes::arm::FSITOS, [this](const arm_code_t& code) { this->instructions.arm.vfp.FSITOS(code); } } }, 
        { id::arm_instruction::FSQRTD, { opcodes::arm::FSQRTD, [this](const arm_code_t& code) { this->instructions.arm.vfp.FSQRTD(code); } } }, 
        { id::arm_instruction::FSQRTS, { opcodes::arm::FSQRTS, [this](const arm_code_t& code) { this->instructions.arm.vfp.FSQRTS(code); } } }, 
        { id::arm_instruction::FSTD, { opcodes::arm::FSTD, [this](const arm_code_t& code) { this->instructions.arm.vfp.FSTD(code); } } }, 
        { id::arm_instruction::FSTMD, { opcodes::arm::FSTMD, [this](const arm_code_t& code) { this->instructions.arm.vfp.FSTMD(code); } } }, 
        { id::arm_instruction::FSTMS, { opcodes::arm::FSTMS, [this](const arm_code_t& code) { this->instructions.arm.vfp.FSTMS(code); } } }, 
        { id::arm_instruction::FSTMX, { opcodes::arm::FSTMX, [this](const arm_code_t& code) { this->instructions.arm.vfp.FSTMX(code); } } }, 
        { id::arm_instruction::FSTS, { opcodes::arm::FSTS, [this](const arm_code_t& code) { this->instructions.arm.vfp.FSTS(code); } } }, 
        { id::arm_instruction::FSUBD, { opcodes::arm::FSUBD, [this](const arm_code_t& code) { this->instructions.arm.vfp.FSUBD(code); } } }, 
        { id::arm_instruction::FSUBS, { opcodes::arm::FSUBS, [this](const arm_code_t& code) { this->instructions.arm.vfp.FSUBS(code); } } }, 
        { id::arm_instruction::FTOSID, { opcodes::arm::FTOSID, [this](const arm_code_t& code) { this->instructions.arm.vfp.FTOSID(code); } } }, 
        { id::arm_instruction::FTOSIS, { opcodes::arm::FTOSIS, [this](const arm_code_t& code) { this->instructions.arm.vfp.FTOSIS(code); } } }, 
        { id::arm_instruction::FTOUID, { opcodes::arm::FTOUID, [this](const arm_code_t& code) { this->instructions.arm.vfp.FTOUID(code); } } }, 
        { id::arm_instruction::FTOUIS, { opcodes::arm::FTOUIS, [this](const arm_code_t& code) { this->instructions.arm.vfp.FTOUIS(code); } } }, 
        { id::arm_instruction::FUITOD, { opcodes::arm::FUITOD, [this](const arm_code_t& code) { this->instructions.arm.vfp.FUITOD(code); } } }, 
        { id::arm_instruction::FUITOS, { opcodes::arm::FUITOS, [this](const arm_code_t& code) { this->instructions.arm.vfp.FUITOS(code); } } }, 
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    };
    

    /*
    if (settings.is_enhanced_DSP_enabled) {
        arm_table.emplace(id::arm_instruction::LDRD, { opcodes::arm::LDRD, INSTRUCTIONS::arm::dsp::LDRD });
        arm_table.emplace(id::arm_instruction::MCRR, { opcodes::arm::MCRR, INSTRUCTIONS::arm::dsp::MCRR });
        arm_table.emplace(id::arm_instruction::MRRC, { opcodes::arm::MRRC, INSTRUCTIONS::arm::dsp::MRRC });
        arm_table.emplace(id::arm_instruction::PLD, { opcodes::arm::PLD, INSTRUCTIONS::arm::dsp::PLD });
        arm_table.emplace(id::arm_instruction::QADD, { opcodes::arm::QADD, INSTRUCTIONS::arm::dsp::QADD });
        arm_table.emplace(id::arm_instruction::QDADD, { opcodes::arm::QDADD, INSTRUCTIONS::arm::dsp::QDADD });
        arm_table.emplace(id::arm_instruction::QDSUB, { opcodes::arm::QDSUB, INSTRUCTIONS::arm::dsp::QDSUB });
        arm_table.emplace(id::arm_instruction::QSUB, { opcodes::arm::QSUB, INSTRUCTIONS::arm::dsp::QSUB });
        arm_table.emplace(id::arm_instruction::SMLA, { opcodes::arm::SMLA, INSTRUCTIONS::arm::dsp::SMLA });
        arm_table.emplace(id::arm_instruction::SMLAL, { opcodes::arm::SMLAL, INSTRUCTIONS::arm::dsp::SMLAL });
        arm_table.emplace(id::arm_instruction::SMLAW, { opcodes::arm::SMLAW, INSTRUCTIONS::arm::dsp::SMLAW });
        arm_table.emplace(id::arm_instruction::SMUL, { opcodes::arm::SMUL, INSTRUCTIONS::arm::dsp::SMUL });
        arm_table.emplace(id::arm_instruction::SMULW, { opcodes::arm::SMULW, INSTRUCTIONS::arm::dsp::SMULW });
        arm_table.emplace(id::arm_instruction::STRD, { opcodes::arm::STRD, INSTRUCTIONS::arm::dsp::STRD });
    }


    if (settings.is_vfp_enabled) {
        arm_table.emplace(id::arm_instruction::FABSS, { opcodes::arm::FABSS, instruction::arm::vfp::FABSS });
        arm_table.emplace(id::arm_instruction::FADDS, { opcodes::arm::FADDS, instruction::arm::vfp::FADDS });
        arm_table.emplace(id::arm_instruction::FCMPES, { opcodes::arm::FCMPES, instruction::arm::vfp::FCMPES });
        arm_table.emplace(id::arm_instruction::FCMPEZS, { opcodes::arm::FCMPEZS, instruction::arm::vfp::FCMPEZS });
        arm_table.emplace(id::arm_instruction::FCMPS, { opcodes::arm::FCMPS, instruction::arm::vfp::FCMPS });
        arm_table.emplace(id::arm_instruction::FCMPZS, { opcodes::arm::FCMPZS, instruction::arm::vfp::FCMPZS });
        arm_table.emplace(id::arm_instruction::FCPYS, { opcodes::arm::FCPYS, instruction::arm::vfp::FCPYS });
        arm_table.emplace(id::arm_instruction::FDIVS, { opcodes::arm::FDIVS, instruction::arm::vfp::FDIVS });
        arm_table.emplace(id::arm_instruction::FLDMS, { opcodes::arm::FLDMS, instruction::arm::vfp::FLDMS });
        arm_table.emplace(id::arm_instruction::FLDMX, { opcodes::arm::FLDMX, instruction::arm::vfp::FLDMX });
        arm_table.emplace(id::arm_instruction::FLDS, { opcodes::arm::FLDS, instruction::arm::vfp::FLDS });
        arm_table.emplace(id::arm_instruction::FMACS, { opcodes::arm::FMACS, instruction::arm::vfp::FMACS });
        arm_table.emplace(id::arm_instruction::FMRS, { opcodes::arm::FMRS, instruction::arm::vfp::FMRS });
        arm_table.emplace(id::arm_instruction::FMRX, { opcodes::arm::FMRX, instruction::arm::vfp::FMRX });
        arm_table.emplace(id::arm_instruction::FMSCS, { opcodes::arm::FMSCS, instruction::arm::vfp::FMSCS });
        arm_table.emplace(id::arm_instruction::FMSR, { opcodes::arm::FMSR, instruction::arm::vfp::FMSR });
        arm_table.emplace(id::arm_instruction::FMSTAT, { opcodes::arm::FMSTAT, instruction::arm::vfp::FMSTAT });
        arm_table.emplace(id::arm_instruction::FMULS, { opcodes::arm::FMULS, instruction::arm::vfp::FMULS });
        arm_table.emplace(id::arm_instruction::FMXR, { opcodes::arm::FMXR, instruction::arm::vfp::FMXR });
        arm_table.emplace(id::arm_instruction::FNEGS, { opcodes::arm::FNEGS, instruction::arm::vfp::FNEGS });
        arm_table.emplace(id::arm_instruction::FNMACS, { opcodes::arm::FNMACS, instruction::arm::vfp::FNMACS });
        arm_table.emplace(id::arm_instruction::FNMSCS, { opcodes::arm::FNMSCS, instruction::arm::vfp::FNMSCS });
        arm_table.emplace(id::arm_instruction::FNMULS, { opcodes::arm::FNMULS, instruction::arm::vfp::FNMULS });
        arm_table.emplace(id::arm_instruction::FSITOS, { opcodes::arm::FSITOS, instruction::arm::vfp::FSITOS });
        arm_table.emplace(id::arm_instruction::FSQRTS, { opcodes::arm::FSQRTS, instruction::arm::vfp::FSQRTS });
        arm_table.emplace(id::arm_instruction::FSTMS, { opcodes::arm::FSTMS, instruction::arm::vfp::FSTMS });
        arm_table.emplace(id::arm_instruction::FSTMX, { opcodes::arm::FSTMX, instruction::arm::vfp::FSTMX });
        arm_table.emplace(id::arm_instruction::FSTS, { opcodes::arm::FSTS, instruction::arm::vfp::FSTS });
        arm_table.emplace(id::arm_instruction::FSUBS, { opcodes::arm::FSUBS, instruction::arm::vfp::FSUBS });
        arm_table.emplace(id::arm_instruction::FTOSIS, { opcodes::arm::FTOSIS, instruction::arm::vfp::FTOSIS });
        arm_table.emplace(id::arm_instruction::FTOUIS, { opcodes::arm::FTOUIS, instruction::arm::vfp::FTOUIS });
        arm_table.emplace(id::arm_instruction::FUITOS, { opcodes::arm::FUITOS, instruction::arm::vfp::FUITOS });
        
        if (settings.is_vfp_double_precision_enabled) {
            arm_table.emplace(id::arm_instruction::FADDD, { opcodes::arm::FADDD, instruction::arm::vfp::FADDD });
            arm_table.emplace(id::arm_instruction::FABSD, { opcodes::arm::FABSD, instruction::arm::vfp::FABSD });
            arm_table.emplace(id::arm_instruction::FCMPD, { opcodes::arm::FCMPD, instruction::arm::vfp::FCMPD });
            arm_table.emplace(id::arm_instruction::FCMPED, { opcodes::arm::FCMPED, instruction::arm::vfp::FCMPED });
            arm_table.emplace(id::arm_instruction::FCMPEZD, { opcodes::arm::FCMPEZD, instruction::arm::vfp::FCMPEZD });
            arm_table.emplace(id::arm_instruction::FCMPZD, { opcodes::arm::FCMPZD, instruction::arm::vfp::FCMPZD });
            arm_table.emplace(id::arm_instruction::FCPYD, { opcodes::arm::FCPYD, instruction::arm::vfp::FCPYD });
            arm_table.emplace(id::arm_instruction::FCVTDS, { opcodes::arm::FCVTDS, instruction::arm::vfp::FCVTDS });
            arm_table.emplace(id::arm_instruction::FCVTSD, { opcodes::arm::FCVTSD, instruction::arm::vfp::FCVTSD });
            arm_table.emplace(id::arm_instruction::FDIVD, { opcodes::arm::FDIVD, instruction::arm::vfp::FDIVD });
            arm_table.emplace(id::arm_instruction::FLDD, { opcodes::arm::FLDD, instruction::arm::vfp::FLDD });
            arm_table.emplace(id::arm_instruction::FLDMD, { opcodes::arm::FLDMD, instruction::arm::vfp::FLDMD });
            arm_table.emplace(id::arm_instruction::FMACD, { opcodes::arm::FMACD, instruction::arm::vfp::FMACD });
            arm_table.emplace(id::arm_instruction::FMDHR, { opcodes::arm::FMDHR, instruction::arm::vfp::FMDHR });
            arm_table.emplace(id::arm_instruction::FMDLR, { opcodes::arm::FMDLR, instruction::arm::vfp::FMDLR });
            arm_table.emplace(id::arm_instruction::FMRDH, { opcodes::arm::FMRDH, instruction::arm::vfp::FMRDH });
            arm_table.emplace(id::arm_instruction::FMRDL, { opcodes::arm::FMRDL, instruction::arm::vfp::FMRDL });
            arm_table.emplace(id::arm_instruction::FMSCD, { opcodes::arm::FMSCD, instruction::arm::vfp::FMSCD });
            arm_table.emplace(id::arm_instruction::FMULD, { opcodes::arm::FMULD, instruction::arm::vfp::FMULD });
            arm_table.emplace(id::arm_instruction::FNEGD, { opcodes::arm::FNEGD, instruction::arm::vfp::FNEGD });
            arm_table.emplace(id::arm_instruction::FNMACD, { opcodes::arm::FNMACD, instruction::arm::vfp::FNMACD });
            arm_table.emplace(id::arm_instruction::FNMSCD, { opcodes::arm::FNMSCD, instruction::arm::vfp::FNMSCD });
            arm_table.emplace(id::arm_instruction::FNMULD, { opcodes::arm::FNMULD, instruction::arm::vfp::FNMULD });
            arm_table.emplace(id::arm_instruction::FSITOD, { opcodes::arm::FSITOD, instruction::arm::vfp::FSITOD });
            arm_table.emplace(id::arm_instruction::FSQRTD, { opcodes::arm::FSQRTD, instruction::arm::vfp::FSQRTD });
            arm_table.emplace(id::arm_instruction::FSTD, { opcodes::arm::FSTD, instruction::arm::vfp::FSTD });
            arm_table.emplace(id::arm_instruction::FSTMD, { opcodes::arm::FSTMD, instruction::arm::vfp::FSTMD });
            arm_table.emplace(id::arm_instruction::FSUBD, { opcodes::arm::FSUBD, instruction::arm::vfp::FSUBD });
            arm_table.emplace(id::arm_instruction::FTOSID, { opcodes::arm::FTOSID, instruction::arm::vfp::FTOSID });
            arm_table.emplace(id::arm_instruction::FTOUID, { opcodes::arm::FTOUID, instruction::arm::vfp::FTOUID });
            arm_table.emplace(id::arm_instruction::FUITOD, { opcodes::arm::FUITOD, instruction::arm::vfp::FUITOD });
        }
    }
    */

    thumb_table = {
        // math
        { id::thumb_instruction::ADC,   { opcodes::thumb::ADC,   [this](const thumb_code_t& code) { this->instructions.thumb.math.ADC(code); } } },
        { id::thumb_instruction::ADD1,  { opcodes::thumb::ADD1,  [this](const thumb_code_t& code) { this->instructions.thumb.math.ADD1(code); } } },
        { id::thumb_instruction::ADD2,  { opcodes::thumb::ADD2,  [this](const thumb_code_t& code) { this->instructions.thumb.math.ADD2(code); } } },
        { id::thumb_instruction::ADD3,  { opcodes::thumb::ADD3,  [this](const thumb_code_t& code) { this->instructions.thumb.math.ADD3(code); } } },
        { id::thumb_instruction::ADD4,  { opcodes::thumb::ADD4,  [this](const thumb_code_t& code) { this->instructions.thumb.math.ADD4(code); } } },
        { id::thumb_instruction::ADD5,  { opcodes::thumb::ADD5,  [this](const thumb_code_t& code) { this->instructions.thumb.math.ADD5(code); } } },
        { id::thumb_instruction::ADD6,  { opcodes::thumb::ADD6,  [this](const thumb_code_t& code) { this->instructions.thumb.math.ADD6(code); } } },
        { id::thumb_instruction::ADD7,  { opcodes::thumb::ADD7,  [this](const thumb_code_t& code) { this->instructions.thumb.math.ADD7(code); } } },
        { id::thumb_instruction::SBC,   { opcodes::thumb::SBC,   [this](const thumb_code_t& code) { this->instructions.thumb.math.SBC(code); } } },
        { id::thumb_instruction::SUB1,  { opcodes::thumb::SUB1,  [this](const thumb_code_t& code) { this->instructions.thumb.math.SUB1(code); } } },
        { id::thumb_instruction::SUB2,  { opcodes::thumb::SUB2,  [this](const thumb_code_t& code) { this->instructions.thumb.math.SUB2(code); } } },
        { id::thumb_instruction::SUB3,  { opcodes::thumb::SUB3,  [this](const thumb_code_t& code) { this->instructions.thumb.math.SUB3(code); } } },
        { id::thumb_instruction::SUB4,  { opcodes::thumb::SUB4,  [this](const thumb_code_t& code) { this->instructions.thumb.math.SUB4(code); } } },
        { id::thumb_instruction::MUL,   { opcodes::thumb::MUL,   [this](const thumb_code_t& code) { this->instructions.thumb.math.MUL(code); } } },

        // logic
        { id::thumb_instruction::AND,   { opcodes::thumb::AND,   [this](const thumb_code_t& code) { this->instructions.thumb.logic.AND(code); } } },
        { id::thumb_instruction::ASR1,  { opcodes::thumb::ASR1,  [this](const thumb_code_t& code) { this->instructions.thumb.logic.ASR1(code); } } },
        { id::thumb_instruction::ASR2,  { opcodes::thumb::ASR2,  [this](const thumb_code_t& code) { this->instructions.thumb.logic.ASR2(code); } } },
        { id::thumb_instruction::BIC,   { opcodes::thumb::BIC,   [this](const thumb_code_t& code) { this->instructions.thumb.logic.BIC(code); } } },
        { id::thumb_instruction::EOR,   { opcodes::thumb::EOR,   [this](const thumb_code_t& code) { this->instructions.thumb.logic.EOR(code); } } },
        { id::thumb_instruction::LSL1,  { opcodes::thumb::LSL1,  [this](const thumb_code_t& code) { this->instructions.thumb.logic.LSL1(code); } } },
        { id::thumb_instruction::LSL2,  { opcodes::thumb::LSL2,  [this](const thumb_code_t& code) { this->instructions.thumb.logic.LSL2(code); } } },
        { id::thumb_instruction::LSR1,  { opcodes::thumb::LSR1,  [this](const thumb_code_t& code) { this->instructions.thumb.logic.LSR1(code); } } },
        { id::thumb_instruction::LSR2,  { opcodes::thumb::LSR2,  [this](const thumb_code_t& code) { this->instructions.thumb.logic.LSR2(code); } } },
        { id::thumb_instruction::NEG,   { opcodes::thumb::NEG,   [this](const thumb_code_t& code) { this->instructions.thumb.logic.NEG(code); } } },
        { id::thumb_instruction::ORR,   { opcodes::thumb::ORR,   [this](const thumb_code_t& code) { this->instructions.thumb.logic.ORR(code); } } },
        { id::thumb_instruction::ROR,   { opcodes::thumb::ROR,   [this](const thumb_code_t& code) { this->instructions.thumb.logic.ROR(code); } } },
        { id::thumb_instruction::TST,   { opcodes::thumb::TST,   [this](const thumb_code_t& code) { this->instructions.thumb.logic.TST(code); } } },

        // comparison
        { id::thumb_instruction::CMN,   { opcodes::thumb::CMN,   [this](const thumb_code_t& code) { this->instructions.thumb.compare.CMN(code); } } },
        { id::thumb_instruction::CMP1,  { opcodes::thumb::CMP1,  [this](const thumb_code_t& code) { this->instructions.thumb.compare.CMP1(code); } } },
        { id::thumb_instruction::CMP2,  { opcodes::thumb::CMP2,  [this](const thumb_code_t& code) { this->instructions.thumb.compare.CMP2(code); } } },
        { id::thumb_instruction::CMP3,  { opcodes::thumb::CMP3,  [this](const thumb_code_t& code) { this->instructions.thumb.compare.CMP3(code); }} },

        // movement
        { id::thumb_instruction::MOV1,  { opcodes::thumb::MOV1,  [this](const thumb_code_t& code) { this->instructions.thumb.movement.MOV1(code); } } },
        { id::thumb_instruction::MOV2,  { opcodes::thumb::MOV2,  [this](const thumb_code_t& code) { this->instructions.thumb.movement.MOV2(code); } } },
        { id::thumb_instruction::MOV3,  { opcodes::thumb::MOV3,  [this](const thumb_code_t& code) { this->instructions.thumb.movement.MOV3(code); } } },
        { id::thumb_instruction::MVN,   { opcodes::thumb::MVN,   [this](const thumb_code_t& code) { this->instructions.thumb.movement.MVN(code); } } },

        // branching
        { id::thumb_instruction::B1,    { opcodes::thumb::B1,    [this](const thumb_code_t& code) { this->instructions.thumb.branching.B1(code); } } },
        { id::thumb_instruction::B2,    { opcodes::thumb::B2,    [this](const thumb_code_t& code) { this->instructions.thumb.branching.B2(code); } } },
        { id::thumb_instruction::BL,    { opcodes::thumb::BL,    [this](const thumb_code_t& code) { this->instructions.thumb.branching.BL(code); } } },
        { id::thumb_instruction::BX,    { opcodes::thumb::BX,    [this](const thumb_code_t& code) { this->instructions.thumb.branching.BX(code); } } },

        // misc
        { id::thumb_instruction::NOP,   { opcodes::thumb::NOP,   [this](const thumb_code_t& code) { this->instructions.thumb.misc.NOP(code); } } },
        { id::thumb_instruction::SWI,   { opcodes::thumb::SWI,   [this](const thumb_code_t& code) { this->instructions.thumb.misc.SWI(code); } } },

        // load
        { id::thumb_instruction::LDMIA, { opcodes::thumb::LDMIA, [this](const thumb_code_t& code) { this->instructions.thumb.load.LDMIA(code); } } },
        { id::thumb_instruction::LDR1,  { opcodes::thumb::LDR1,  [this](const thumb_code_t& code) { this->instructions.thumb.load.LDR1(code); } } },
        { id::thumb_instruction::LDR2,  { opcodes::thumb::LDR2,  [this](const thumb_code_t& code) { this->instructions.thumb.load.LDR2(code); } } },
        { id::thumb_instruction::LDR3,  { opcodes::thumb::LDR3,  [this](const thumb_code_t& code) { this->instructions.thumb.load.LDR3(code); } } },
        { id::thumb_instruction::LDR4,  { opcodes::thumb::LDR4,  [this](const thumb_code_t& code) { this->instructions.thumb.load.LDR4(code); } } },
        { id::thumb_instruction::LDRB1, { opcodes::thumb::LDRB1, [this](const thumb_code_t& code) { this->instructions.thumb.load.LDRB1(code); } } },
        { id::thumb_instruction::LDRB2, { opcodes::thumb::LDRB2, [this](const thumb_code_t& code) { this->instructions.thumb.load.LDRB2(code); } } },
        { id::thumb_instruction::LDRH1, { opcodes::thumb::LDRH1, [this](const thumb_code_t& code) { this->instructions.thumb.load.LDRH1(code); } } },
        { id::thumb_instruction::LDRH2, { opcodes::thumb::LDRH2, [this](const thumb_code_t& code) { this->instructions.thumb.load.LDRH2(code); } } },
        { id::thumb_instruction::LDRSB, { opcodes::thumb::LDRSB, [this](const thumb_code_t& code) { this->instructions.thumb.load.LDRSB(code); } } },
        { id::thumb_instruction::LDRSH, { opcodes::thumb::LDRSH, [this](const thumb_code_t& code) { this->instructions.thumb.load.LDRSH(code); } } },
        { id::thumb_instruction::POP,   { opcodes::thumb::POP,   [this](const thumb_code_t& code) { this->instructions.thumb.load.POP(code); } } },
    
        // store
        { id::thumb_instruction::STMIA, { opcodes::thumb::STMIA, [this](const thumb_code_t& code) { this->instructions.thumb.store.STMIA(code); } } },
        { id::thumb_instruction::STR1,  { opcodes::thumb::STR1,  [this](const thumb_code_t& code) { this->instructions.thumb.store.STR1(code); } } },
        { id::thumb_instruction::STR2,  { opcodes::thumb::STR2,  [this](const thumb_code_t& code) { this->instructions.thumb.store.STR2(code); } } },
        { id::thumb_instruction::STR3,  { opcodes::thumb::STR3,  [this](const thumb_code_t& code) { this->instructions.thumb.store.STR3(code); } } },
        { id::thumb_instruction::STRB1, { opcodes::thumb::STRB1, [this](const thumb_code_t& code) { this->instructions.thumb.store.STRB1(code); } } },
        { id::thumb_instruction::STRH1, { opcodes::thumb::STRH1, [this](const thumb_code_t& code) { this->instructions.thumb.store.STRH1(code); } } },
        { id::thumb_instruction::STRH2, { opcodes::thumb::STRH2, [this](const thumb_code_t& code) { this->instructions.thumb.store.STRH2(code); } } },
        { id::thumb_instruction::PUSH,  { opcodes::thumb::PUSH,  [this](const thumb_code_t& code) { this->instructions.thumb.store.PUSH(code); } } }

        // { id::thumb_instruction::BKPT,    { opcodes::thumb::, INSTRUCTIONS::thumb:: } },
        // { id::thumb_instruction::BLX1,    { opcodes::thumb::BLX1, INSTRUCTIONS::thumb:: } },
        // { id::thumb_instruction::BLX2,    { opcodes::thumb::, INSTRUCTIONS::thumb:: } }
    };


/*
    jazelle_table = {
        { id::jazelle_instruction::UNKNOWN,         { opcodes::jazelle::UNKNOWN, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::AALOAD,          { opcodes::jazelle::AALOAD, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::AASTORE,         { opcodes::jazelle::AASTORE, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ACONST_NULL,     { opcodes::jazelle::ACONST_NULL, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ALOAD,           { opcodes::jazelle::ALOAD, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ALOAD_0,         { opcodes::jazelle::ALOAD_0, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ALOAD_1,         { opcodes::jazelle::ALOAD_1, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ALOAD_2,         { opcodes::jazelle::ALOAD_2, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ALOAD_3,         { opcodes::jazelle::ALOAD_3, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ANEWARRAY,       { opcodes::jazelle::ANEWARRAY, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ARETURN,         { opcodes::jazelle::ARETURN, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ARRAYLENGTH,     { opcodes::jazelle::ARRAYLENGTH, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ASTORE,          { opcodes::jazelle::ASTORE, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ASTORE_0,        { opcodes::jazelle::ASTORE_0, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ASTORE_1,        { opcodes::jazelle::ASTORE_1, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ASTORE_2,        { opcodes::jazelle::ASTORE_2, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ASTORE_3,        { opcodes::jazelle::ASTORE_3, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ATHROW,          { opcodes::jazelle::ATHROW, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::BALOAD,          { opcodes::jazelle::BALOAD, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::BASTORE,         { opcodes::jazelle::BASTORE, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::BIPUSH,          { opcodes::jazelle::BIPUSH, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::BREAKPOINT,      { opcodes::jazelle::BREAKPOINT, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::CALOAD,          { opcodes::jazelle::CALOAD, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::CASTORE,         { opcodes::jazelle::CASTORE, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::CHECKCAST,       { opcodes::jazelle::CHECKCAST, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::D2F,             { opcodes::jazelle::D2F, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::D2I,             { opcodes::jazelle::D2I, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::D2L,             { opcodes::jazelle::D2L, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::DADD,            { opcodes::jazelle::DADD, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::DALOAD,          { opcodes::jazelle::DALOAD, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::DASTORE,         { opcodes::jazelle::DASTORE, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::DCMPG,           { opcodes::jazelle::DCMPG, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::DCMPL,           { opcodes::jazelle::DCMPL, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::DCONST_0,        { opcodes::jazelle::DCONST_0, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::DCONST_1,        { opcodes::jazelle::DCONST_1, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::DDIV,            { opcodes::jazelle::DDIV, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::DLOAD,           { opcodes::jazelle::DLOAD, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::DLOAD_0,         { opcodes::jazelle::DLOAD_0, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::DLOAD_1,         { opcodes::jazelle::DLOAD_1, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::DLOAD_2,         { opcodes::jazelle::DLOAD_2, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::DLOAD_3,         { opcodes::jazelle::DLOAD_3, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::DMUL,            { opcodes::jazelle::DMUL, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::DNEG,            { opcodes::jazelle::DNEG, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::DREM,            { opcodes::jazelle::DREM, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::DRETURN,         { opcodes::jazelle::DRETURN, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::DSTORE,          { opcodes::jazelle::DSTORE, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::DSTORE_0,        { opcodes::jazelle::DSTORE_0, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::DSTORE_1,        { opcodes::jazelle::DSTORE_1, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::DSTORE_2,        { opcodes::jazelle::DSTORE_2, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::DSTORE_3,        { opcodes::jazelle::DSTORE_3, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::DSUB,            { opcodes::jazelle::DSUB, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::DUP,             { opcodes::jazelle::DUP, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::DUP_X1,          { opcodes::jazelle::DUP_X1, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::DUP_X2,          { opcodes::jazelle::DUP_X2, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::DUP2,            { opcodes::jazelle::DUP2, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::DUP2_X1,         { opcodes::jazelle::DUP2_X1, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::DUP2_X2,         { opcodes::jazelle::DUP2_X2, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::F2D,             { opcodes::jazelle::F2D, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::F2I,             { opcodes::jazelle::F2I, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::F2L,             { opcodes::jazelle::F2L, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::FADD,            { opcodes::jazelle::FADD, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::FALOAD,          { opcodes::jazelle::FALOAD, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::FASTORE,         { opcodes::jazelle::FASTORE, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::FCMPG,           { opcodes::jazelle::FCMPG, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::FCMPL,           { opcodes::jazelle::FCMPL, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::FCONST_0,        { opcodes::jazelle::FCONST_0, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::FCONST_1,        { opcodes::jazelle::FCONST_1, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::FCONST_2,        { opcodes::jazelle::FCONST_2, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::FDIV,            { opcodes::jazelle::FDIV, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::FLOAD,           { opcodes::jazelle::FLOAD, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::FLOAD_0,         { opcodes::jazelle::FLOAD_0, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::FLOAD_1,         { opcodes::jazelle::FLOAD_1, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::FLOAD_2,         { opcodes::jazelle::FLOAD_2, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::FLOAD_3,         { opcodes::jazelle::FLOAD_3, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::FMUL,            { opcodes::jazelle::FMUL, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::FNEG,            { opcodes::jazelle::FNEG, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::FREM,            { opcodes::jazelle::FREM, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::FRETURN,         { opcodes::jazelle::FRETURN, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::FSTORE,          { opcodes::jazelle::FSTORE, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::FSTORE_0,        { opcodes::jazelle::FSTORE_0, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::FSTORE_1,        { opcodes::jazelle::FSTORE_1, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::FSTORE_2,        { opcodes::jazelle::FSTORE_2, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::FSTORE_3,        { opcodes::jazelle::FSTORE_3, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::FSUB,            { opcodes::jazelle::FSUB, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::GETFIELD,        { opcodes::jazelle::GETFIELD, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::GETSTATIC,       { opcodes::jazelle::GETSTATIC, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::GOTO,            { opcodes::jazelle::GOTO, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::GOTO_W,          { opcodes::jazelle::GOTO_W, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::I2B,             { opcodes::jazelle::I2B, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::I2C,             { opcodes::jazelle::I2C, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::I2D,             { opcodes::jazelle::I2D, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::I2F,             { opcodes::jazelle::I2F, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::I2L,             { opcodes::jazelle::I2L, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::I2S,             { opcodes::jazelle::I2S, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IADD,            { opcodes::jazelle::IADD, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IALOAD,          { opcodes::jazelle::IALOAD, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IAND,            { opcodes::jazelle::IAND, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IASTORE,         { opcodes::jazelle::IASTORE, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ICONST_M1,       { opcodes::jazelle::ICONST_M1, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ICONST_0,        { opcodes::jazelle::ICONST_0, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ICONST_1,        { opcodes::jazelle::ICONST_1, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ICONST_2,        { opcodes::jazelle::ICONST_2, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ICONST_3,        { opcodes::jazelle::ICONST_3, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ICONST_4,        { opcodes::jazelle::ICONST_4, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ICONST_5,        { opcodes::jazelle::ICONST_5, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IDIV,            { opcodes::jazelle::IDIV, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IF_ACMPEQ,       { opcodes::jazelle::IF_ACMPEQ, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IF_ACMPNE,       { opcodes::jazelle::IF_ACMPNE, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IF_ICMPEQ,       { opcodes::jazelle::IF_ICMPEQ, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IF_ICMPGE,       { opcodes::jazelle::IF_ICMPGE, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IF_ICMPGT,       { opcodes::jazelle::IF_ICMPGT, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IF_ICMPLE,       { opcodes::jazelle::IF_ICMPLE, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IF_ICMPLT,       { opcodes::jazelle::IF_ICMPLT, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IF_ICMPNE,       { opcodes::jazelle::IF_ICMPNE, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IFEQ,            { opcodes::jazelle::IFEQ, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IFGE,            { opcodes::jazelle::IFGE, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IFGT,            { opcodes::jazelle::IFGT, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IFLE,            { opcodes::jazelle::IFLE, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IFLT,            { opcodes::jazelle::IFLT, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IFNE,            { opcodes::jazelle::IFNE, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IFNONNULL,       { opcodes::jazelle::IFNONNULL, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IFNULL,          { opcodes::jazelle::IFNULL, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IINC,            { opcodes::jazelle::IINC, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ILOAD,           { opcodes::jazelle::ILOAD, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ILOAD_0,         { opcodes::jazelle::ILOAD_0, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ILOAD_1,         { opcodes::jazelle::ILOAD_1, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ILOAD_2,         { opcodes::jazelle::ILOAD_2, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ILOAD_3,         { opcodes::jazelle::ILOAD_3, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IMPDEP1,         { opcodes::jazelle::IMPDEP1, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IMPDEP2,         { opcodes::jazelle::IMPDEP2, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IMUL,            { opcodes::jazelle::IMUL, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::INEG,            { opcodes::jazelle::INEG, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::INSTANCEOF,      { opcodes::jazelle::INSTANCEOF, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::INVOKEDYNAMIC,   { opcodes::jazelle::INVOKEDYNAMIC, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::INVOKEINTERFACE, { opcodes::jazelle::INVOKEINTERFACE, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::INVOKESPECIAL,   { opcodes::jazelle::INVOKESPECIAL, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::INVOKESTATIC,    { opcodes::jazelle::INVOKESTATIC, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::INVOKEVIRTUAL,   { opcodes::jazelle::INVOKEVIRTUAL, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IOR,             { opcodes::jazelle::IOR, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IREM,            { opcodes::jazelle::IREM, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IRETURN,         { opcodes::jazelle::IRETURN, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ISHL,            { opcodes::jazelle::ISHL, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ISHR,            { opcodes::jazelle::ISHR, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ISTORE,          { opcodes::jazelle::ISTORE, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ISTORE_0,        { opcodes::jazelle::ISTORE_0, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ISTORE_1,        { opcodes::jazelle::ISTORE_1, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ISTORE_2,        { opcodes::jazelle::ISTORE_2, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ISTORE_3,        { opcodes::jazelle::ISTORE_3, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::ISUB,            { opcodes::jazelle::ISUB, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IUSHR,           { opcodes::jazelle::IUSHR, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::IXOR,            { opcodes::jazelle::IXOR, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::JSR,             { opcodes::jazelle::JSR, INSTRUCTIONS::jazelle:: } }, // DEPRECATED
        { id::jazelle_instruction::JSR_W,           { opcodes::jazelle::JSR_W, INSTRUCTIONS::jazelle:: } }, // DEPRECATED
        { id::jazelle_instruction::L2D,             { opcodes::jazelle::L2D, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::L2F,             { opcodes::jazelle::L2F, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::L2I,             { opcodes::jazelle::L2I, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LADD,            { opcodes::jazelle::LADD, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LALOAD,          { opcodes::jazelle::LALOAD, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LAND,            { opcodes::jazelle::LAND, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LASTORE,         { opcodes::jazelle::LASTORE, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LCMP,            { opcodes::jazelle::LCMP, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LCONST_0,        { opcodes::jazelle::LCONST_0, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LCONST_1,        { opcodes::jazelle::LCONST_1, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LDC,             { opcodes::jazelle::LDC, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LDC_W,           { opcodes::jazelle::LDC_W, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LDC2_W,          { opcodes::jazelle::LDC2_W, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LDIV,            { opcodes::jazelle::LDIV, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LLOAD,           { opcodes::jazelle::LLOAD, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LLOAD_0,         { opcodes::jazelle::LLOAD_0, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LLOAD_1,         { opcodes::jazelle::LLOAD_1, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LLOAD_2,         { opcodes::jazelle::LLOAD_2, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LLOAD_3,         { opcodes::jazelle::LLOAD_3, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LMUL,            { opcodes::jazelle::LMUL, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LNEG,            { opcodes::jazelle::LNEG, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LOOKUPSWITCH,    { opcodes::jazelle::LOOKUPSWITCH, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LOR,             { opcodes::jazelle::LOR, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LREM,            { opcodes::jazelle::LREM, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LRETURN,         { opcodes::jazelle::LRETURN, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LSHL,            { opcodes::jazelle::LSHL, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LSHR,            { opcodes::jazelle::LSHR, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LSTORE,          { opcodes::jazelle::LSTORE, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LSTORE_0,        { opcodes::jazelle::LSTORE_0, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LSTORE_1,        { opcodes::jazelle::LSTORE_1, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LSTORE_2,        { opcodes::jazelle::LSTORE_2, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LSTORE_3,        { opcodes::jazelle::LSTORE_3, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LSUB,            { opcodes::jazelle::LSUB, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LUSHR,           { opcodes::jazelle::LUSHR, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::LXOR,            { opcodes::jazelle::LXOR, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::MONITORENTER,    { opcodes::jazelle::MONITORENTER, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::MONITOREXIT,     { opcodes::jazelle::MONITOREXIT, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::MULTIANEWARRAY,  { opcodes::jazelle::MULTIANEWARRAY, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::NEW,             { opcodes::jazelle::NEW, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::NEWARRAY,        { opcodes::jazelle::NEWARRAY, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::NOP,             { opcodes::jazelle::NOP, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::POP,             { opcodes::jazelle::POP, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::POP2,            { opcodes::jazelle::POP2, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::PUTFIELD,        { opcodes::jazelle::PUTFIELD, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::PUTSTATIC,       { opcodes::jazelle::PUTSTATIC, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::RET,             { opcodes::jazelle::RET, INSTRUCTIONS::jazelle:: } }, // DEPRECATED
        { id::jazelle_instruction::RETURN,          { opcodes::jazelle::RETURN, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::SALOAD,          { opcodes::jazelle::SALOAD, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::SASTORE,         { opcodes::jazelle::SASTORE, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::SIPUSH,          { opcodes::jazelle::SIPUSH, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::SWAP,            { opcodes::jazelle::SWAP, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::TABLESWITCH,     { opcodes::jazelle::TABLESWITCH, INSTRUCTIONS::jazelle:: } },
        { id::jazelle_instruction::WIDE,            { opcodes::jazelle::WIDE, INSTRUCTIONS::jazelle::}
    }; 
*/
}