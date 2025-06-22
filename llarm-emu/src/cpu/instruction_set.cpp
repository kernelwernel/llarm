#include "instruction_set.hpp"
#include "instructions/instructions.hpp"

#include <llarm-asm/llarm-asm.hpp>

void INSTRUCTION_SET::armv2_setup() {
    if ((settings.arch >= id::arch::ARMv2) == false) {
        return;
    }

    // coprocessors didn't exist in ARMv1
    arm_table.emplace(llarm::as::id::arm::CDP, [this](const arm_code_t& code) { this->instructions.arm.coprocessor_inst.CDP(code); });
    arm_table.emplace(llarm::as::id::arm::LDC, [this](const arm_code_t& code) { this->instructions.arm.coprocessor_inst.LDC(code); });
    arm_table.emplace(llarm::as::id::arm::MCR, [this](const arm_code_t& code) { this->instructions.arm.coprocessor_inst.MCR(code); });
    arm_table.emplace(llarm::as::id::arm::MRC, [this](const arm_code_t& code) { this->instructions.arm.coprocessor_inst.MRC(code); });
    arm_table.emplace(llarm::as::id::arm::STC, [this](const arm_code_t& code) { this->instructions.arm.coprocessor_inst.STC(code); });

    arm_table.emplace(llarm::as::id::arm::SWP,   [this](const arm_code_t& code) { this->instructions.arm.store.SWP(code); });

    if (settings.specific_arch >= id::specific_arch::ARMv2a) {
        arm_table.emplace(llarm::as::id::arm::SWPB,  [this](const arm_code_t& code) { this->instructions.arm.store.SWPB(code); });
    }

    // multiplications were added in ARMv2, but extensions were added later
    if (settings.is_multiply_enabled) {
        arm_table.emplace(llarm::as::id::arm::MLA,   [this](const arm_code_t& code) { this->instructions.arm.multiply.MLA(code); });
        arm_table.emplace(llarm::as::id::arm::MUL,   [this](const arm_code_t& code) { this->instructions.arm.multiply.MUL(code); });
        
        if (
            (settings.specific_arch == id::specific_arch::ARMv3M) ||
            (settings.specific_arch == id::specific_arch::ARMv4) ||
            (settings.specific_arch == id::specific_arch::ARMv4T) ||
            (settings.specific_arch == id::specific_arch::ARMv5) ||
            (settings.specific_arch == id::specific_arch::ARMv5T) ||
            (settings.specific_arch == id::specific_arch::ARMv5TE) ||
            (settings.specific_arch == id::specific_arch::ARMv5TExP) ||
            (settings.specific_arch >= id::specific_arch::ARMv6)
        ) {
            arm_table.emplace(llarm::as::id::arm::SMLAL, [this](const arm_code_t& code) { this->instructions.arm.multiply.SMLAL(code); });
            arm_table.emplace(llarm::as::id::arm::SMULL, [this](const arm_code_t& code) { this->instructions.arm.multiply.SMULL(code); });   
            arm_table.emplace(llarm::as::id::arm::UMLAL, [this](const arm_code_t& code) { this->instructions.arm.multiply.UMLAL(code); });
            arm_table.emplace(llarm::as::id::arm::UMULL, [this](const arm_code_t& code) { this->instructions.arm.multiply.UMULL(code); });
        }
    }
}


void INSTRUCTION_SET::armv3_setup() {
    if ((settings.arch >= id::arch::ARMv3) == false) {
        return;
    }

    arm_table.emplace(llarm::as::id::arm::MRS,     [this](const arm_code_t& code) { this->instructions.arm.movement.MRS(code); });
    arm_table.emplace(llarm::as::id::arm::MSR_IMM, [this](const arm_code_t& code) { this->instructions.arm.movement.MSR_IMM(code); });
    arm_table.emplace(llarm::as::id::arm::MSR_REG, [this](const arm_code_t& code) { this->instructions.arm.movement.MSR_REG(code); });
}


void INSTRUCTION_SET::armv4_setup() {
    if ((settings.arch >= id::arch::ARMv4) == false) {
        return;
    }

    arm_table.emplace(llarm::as::id::arm::LDRH,  [this](const arm_code_t& code) { this->instructions.arm.load.LDRH(code); });
    arm_table.emplace(llarm::as::id::arm::LDRSB, [this](const arm_code_t& code) { this->instructions.arm.load.LDRSB(code); });
    arm_table.emplace(llarm::as::id::arm::LDRSH, [this](const arm_code_t& code) { this->instructions.arm.load.LDRSH(code); });

    arm_table.emplace(llarm::as::id::arm::STRH, [this](const arm_code_t& code) { this->instructions.arm.store.STRH(code); });
    
    if (
        (settings.specific_arch == id::specific_arch::ARMv4T) ||
        (settings.specific_arch == id::specific_arch::ARMv4TxM)
    ) {
        arm_table.emplace(llarm::as::id::arm::BX, [this](const arm_code_t& code) { this->instructions.arm.branching.BX(code); });
    }
}


void INSTRUCTION_SET::armv5_setup() {
    if ((settings.arch >= id::arch::ARMv5) == false) {
        return;
    }

    arm_table.emplace(llarm::as::id::arm::BKPT, [this](const arm_code_t& code) { this->instructions.arm.misc.BKPT(code); });
    arm_table.emplace(llarm::as::id::arm::BLX1, [this](const arm_code_t& code) { this->instructions.arm.branching.BLX1(code); });
    arm_table.emplace(llarm::as::id::arm::BLX2, [this](const arm_code_t& code) { this->instructions.arm.branching.BLX2(code); });
    arm_table.emplace(llarm::as::id::arm::CLZ,  [this](const arm_code_t& code) { this->instructions.arm.branching.CLZ(code); });

    arm_table.emplace(llarm::as::id::arm::CDP2, [this](const arm_code_t& code) { this->instructions.arm.coprocessor_inst.CDP(code); });
    arm_table.emplace(llarm::as::id::arm::LDC2, [this](const arm_code_t& code) { this->instructions.arm.coprocessor_inst.LDC(code); });
    arm_table.emplace(llarm::as::id::arm::MCR2, [this](const arm_code_t& code) { this->instructions.arm.coprocessor_inst.MCR(code); });
    arm_table.emplace(llarm::as::id::arm::MRC2, [this](const arm_code_t& code) { this->instructions.arm.coprocessor_inst.MRC(code); });
    arm_table.emplace(llarm::as::id::arm::STC2, [this](const arm_code_t& code) { this->instructions.arm.coprocessor_inst.STC(code); });
    
    if (settings.is_enhanced_DSP_enabled) {
        switch (settings.specific_arch) {
            case id::specific::arch::ARMv5TE: 
                arm_table.emplace(llarm::as::id::arm::MCRR, [this](const arm_code_t& code) { this->instructions.arm.dsp.MCRR(code); });
                arm_table.emplace(llarm::as::id::arm::MRRC, [this](const arm_code_t& code) { this->instructions.arm.dsp.MRRC(code); });
                arm_table.emplace(llarm::as::id::arm::PLD,  [this](const arm_code_t& code) { this->instructions.arm.dsp.PLD(code); });
                arm_table.emplace(llarm::as::id::arm::STRD, [this](const arm_code_t& code) { this->instructions.arm.dsp.STRD(code); });
                arm_table.emplace(llarm::as::id::arm::LDRD, [this](const arm_code_t& code) { this->instructions.arm.dsp.LDRD(code); });
                // no break on purpose

            case id::specific_arch::ARMv5TExP:
                arm_table.emplace(llarm::as::id::arm::QADD,    [this](const arm_code_t& code) { this->instructions.arm.dsp.QADD(code); });
                arm_table.emplace(llarm::as::id::arm::QDADD,   [this](const arm_code_t& code) { this->instructions.arm.dsp.QDADD(code); });
                arm_table.emplace(llarm::as::id::arm::QDSUB,   [this](const arm_code_t& code) { this->instructions.arm.dsp.QDSUB(code); });
                arm_table.emplace(llarm::as::id::arm::QSUB,    [this](const arm_code_t& code) { this->instructions.arm.dsp.QSUB(code); });
                arm_table.emplace(llarm::as::id::arm::SMLAXY,  [this](const arm_code_t& code) { this->instructions.arm.dsp.SMLAXY(code); });
                arm_table.emplace(llarm::as::id::arm::SMLALXY, [this](const arm_code_t& code) { this->instructions.arm.dsp.SMLALXY(code); });
                arm_table.emplace(llarm::as::id::arm::SMLAWY,  [this](const arm_code_t& code) { this->instructions.arm.dsp.SMLAWY(code); });
                arm_table.emplace(llarm::as::id::arm::SMULXY,  [this](const arm_code_t& code) { this->instructions.arm.dsp.SMULXY(code); });
                arm_table.emplace(llarm::as::id::arm::SMULWY,  [this](const arm_code_t& code) { this->instructions.arm.dsp.SMULWY(code); });

            default: shared::out::error("Invalid Enhanced DSP configuration");
        }
    }
}


INSTRUCTION_SET::INSTRUCTION_SET(SETTINGS& settings, INSTRUCTIONS& instructions) : settings(settings), instructions(instructions) {
    arm_table = {
        { llarm::as::id::arm::ADC, [this](const arm_code_t& code) { this->instructions.arm.math.ADC(code); } },
        { llarm::as::id::arm::ADD, [this](const arm_code_t& code) { this->instructions.arm.math.ADD(code); } },
        { llarm::as::id::arm::RSB, [this](const arm_code_t& code) { this->instructions.arm.math.RSB(code); } },
        { llarm::as::id::arm::RSC, [this](const arm_code_t& code) { this->instructions.arm.math.RSC(code); } },
        { llarm::as::id::arm::SBC, [this](const arm_code_t& code) { this->instructions.arm.math.SBC(code); } },
        { llarm::as::id::arm::SUB, [this](const arm_code_t& code) { this->instructions.arm.math.SUB(code); } },

        { llarm::as::id::arm::CMN, [this](const arm_code_t& code) { this->instructions.arm.logic.CMN(code); } },
        { llarm::as::id::arm::AND, [this](const arm_code_t& code) { this->instructions.arm.logic.AND(code); } },
        { llarm::as::id::arm::CMP, [this](const arm_code_t& code) { this->instructions.arm.logic.CMP(code); } },
        { llarm::as::id::arm::EOR, [this](const arm_code_t& code) { this->instructions.arm.logic.EOR(code); } },
        { llarm::as::id::arm::ORR, [this](const arm_code_t& code) { this->instructions.arm.logic.ORR(code); } },
        { llarm::as::id::arm::TEQ, [this](const arm_code_t& code) { this->instructions.arm.logic.TEQ(code); } },
        { llarm::as::id::arm::TST, [this](const arm_code_t& code) { this->instructions.arm.logic.TST(code); } },

        { llarm::as::id::arm::MOV, [this](const arm_code_t& code) { this->instructions.arm.movement.MOV(code); } },
        { llarm::as::id::arm::MVN, [this](const arm_code_t& code) { this->instructions.arm.movement.MVN(code); } },
        
        { llarm::as::id::arm::B,  [this](const arm_code_t& code) { this->instructions.arm.branching.B(code); } },
        { llarm::as::id::arm::BL, [this](const arm_code_t& code) { this->instructions.arm.branching.BL(code); } },
        
        { llarm::as::id::arm::NOP, [this](const arm_code_t& code) { this->instructions.arm.misc.NOP(code); } },
        { llarm::as::id::arm::PSR, [this](const arm_code_t& code) { this->instructions.arm.misc.PSR(code); } },
        { llarm::as::id::arm::SWI, [this](const arm_code_t& code) { this->instructions.arm.misc.SWI(code); } },

        { llarm::as::id::arm::LDM1,  [this](const arm_code_t& code) { this->instructions.arm.load.LDM1(code); } },
        { llarm::as::id::arm::LDM2,  [this](const arm_code_t& code) { this->instructions.arm.load.LDM2(code); } },
        { llarm::as::id::arm::LDM3,  [this](const arm_code_t& code) { this->instructions.arm.load.LDM3(code); } },
        { llarm::as::id::arm::LDR,   [this](const arm_code_t& code) { this->instructions.arm.load.LDR(code); } },
        { llarm::as::id::arm::LDRB,  [this](const arm_code_t& code) { this->instructions.arm.load.LDRB(code); } },
        { llarm::as::id::arm::LDRBT, [this](const arm_code_t& code) { this->instructions.arm.load.LDRBT(code); } },
        { llarm::as::id::arm::LDRT,  [this](const arm_code_t& code) { this->instructions.arm.load.LDRT(code); } },

        { llarm::as::id::arm::STM1,  [this](const arm_code_t& code) { this->instructions.arm.store.STM1(code); } }, 
        { llarm::as::id::arm::STM2,  [this](const arm_code_t& code) { this->instructions.arm.store.STM2(code); } }, 
        { llarm::as::id::arm::STR,   [this](const arm_code_t& code) { this->instructions.arm.store.STR(code); } }, 
        { llarm::as::id::arm::STRB,  [this](const arm_code_t& code) { this->instructions.arm.store.STRB(code); } }, 
        { llarm::as::id::arm::STRBT, [this](const arm_code_t& code) { this->instructions.arm.store.STRBT(code); } }, 
        { llarm::as::id::arm::STRT,  [this](const arm_code_t& code) { this->instructions.arm.store.STRT(code); } }, 
    };


    // table for all instruction support: A4-115 
    armv2_setup();
    armv3_setup();
    armv4_setup();
    armv5_setup();


    if (settings.is_vfp_enabled) {
        arm_table.emplace(llarm::as::id::arm::FABSS,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FABSS(code); }); 
        arm_table.emplace(llarm::as::id::arm::FADDS,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FADDS(code); }); 
        arm_table.emplace(llarm::as::id::arm::FCMPES,  [this](const arm_code_t& code) { this->instructions.arm.vfp.FCMPES(code); }); 
        arm_table.emplace(llarm::as::id::arm::FCMPEZS, [this](const arm_code_t& code) { this->instructions.arm.vfp.FCMPEZS(code); }); 
        arm_table.emplace(llarm::as::id::arm::FCMPS,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FCMPS(code); }); 
        arm_table.emplace(llarm::as::id::arm::FCMPZS,  [this](const arm_code_t& code) { this->instructions.arm.vfp.FCMPZS(code); }); 
        arm_table.emplace(llarm::as::id::arm::FCPYS,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FCPYS(code); }); 
        arm_table.emplace(llarm::as::id::arm::FDIVS,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FDIVS(code); }); 
        arm_table.emplace(llarm::as::id::arm::FLDMS,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FLDMS(code); }); 
        arm_table.emplace(llarm::as::id::arm::FLDMX,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FLDMX(code); }); 
        arm_table.emplace(llarm::as::id::arm::FLDS,    [this](const arm_code_t& code) { this->instructions.arm.vfp.FLDS(code); }); 
        arm_table.emplace(llarm::as::id::arm::FMACS,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FMACS(code); }); 
        arm_table.emplace(llarm::as::id::arm::FMRS,    [this](const arm_code_t& code) { this->instructions.arm.vfp.FMRS(code); }); 
        arm_table.emplace(llarm::as::id::arm::FMRX,    [this](const arm_code_t& code) { this->instructions.arm.vfp.FMRX(code); }); 
        arm_table.emplace(llarm::as::id::arm::FMSCS,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FMSCS(code); }); 
        arm_table.emplace(llarm::as::id::arm::FMSR,    [this](const arm_code_t& code) { this->instructions.arm.vfp.FMSR(code); }); 
        arm_table.emplace(llarm::as::id::arm::FMSTAT,  [this](const arm_code_t& code) { this->instructions.arm.vfp.FMSTAT(code); }); 
        arm_table.emplace(llarm::as::id::arm::FMULS,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FMULS(code); }); 
        arm_table.emplace(llarm::as::id::arm::FMXR,    [this](const arm_code_t& code) { this->instructions.arm.vfp.FMXR(code); }); 
        arm_table.emplace(llarm::as::id::arm::FNEGS,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FNEGS(code); }); 
        arm_table.emplace(llarm::as::id::arm::FNMACS,  [this](const arm_code_t& code) { this->instructions.arm.vfp.FNMACS(code); }); 
        arm_table.emplace(llarm::as::id::arm::FNMSCS,  [this](const arm_code_t& code) { this->instructions.arm.vfp.FNMSCS(code); }); 
        arm_table.emplace(llarm::as::id::arm::FNMULS,  [this](const arm_code_t& code) { this->instructions.arm.vfp.FNMULS(code); }); 
        arm_table.emplace(llarm::as::id::arm::FSITOS,  [this](const arm_code_t& code) { this->instructions.arm.vfp.FSITOS(code); }); 
        arm_table.emplace(llarm::as::id::arm::FSQRTS,  [this](const arm_code_t& code) { this->instructions.arm.vfp.FSQRTS(code); }); 
        arm_table.emplace(llarm::as::id::arm::FSTMS,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FSTMS(code); }); 
        arm_table.emplace(llarm::as::id::arm::FSTMX,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FSTMX(code); }); 
        arm_table.emplace(llarm::as::id::arm::FSTS,    [this](const arm_code_t& code) { this->instructions.arm.vfp.FSTS(code); }); 
        arm_table.emplace(llarm::as::id::arm::FSUBS,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FSUBS(code); }); 
        arm_table.emplace(llarm::as::id::arm::FTOSIS,  [this](const arm_code_t& code) { this->instructions.arm.vfp.FTOSIS(code); }); 
        arm_table.emplace(llarm::as::id::arm::FTOUIS,  [this](const arm_code_t& code) { this->instructions.arm.vfp.FTOUIS(code); }); 
        arm_table.emplace(llarm::as::id::arm::FUITOS,  [this](const arm_code_t& code) { this->instructions.arm.vfp.FUITOS(code); }); 
        
        if (settings.is_vfp_double_precision_enabled) {
            arm_table.emplace(llarm::as::id::arm::FABSD,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FABSD(code); }); 
            arm_table.emplace(llarm::as::id::arm::FADDD,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FADDD(code); }); 
            arm_table.emplace(llarm::as::id::arm::FCMPD,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FCMPD(code); }); 
            arm_table.emplace(llarm::as::id::arm::FCMPED,  [this](const arm_code_t& code) { this->instructions.arm.vfp.FCMPED(code); }); 
            arm_table.emplace(llarm::as::id::arm::FCMPEZD, [this](const arm_code_t& code) { this->instructions.arm.vfp.FCMPEZD(code); }); 
            arm_table.emplace(llarm::as::id::arm::FCMPZD,  [this](const arm_code_t& code) { this->instructions.arm.vfp.FCMPZD(code); }); 
            arm_table.emplace(llarm::as::id::arm::FCPYD,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FCPYD(code); }); 
            arm_table.emplace(llarm::as::id::arm::FCVTDS,  [this](const arm_code_t& code) { this->instructions.arm.vfp.FCVTDS(code); }); 
            arm_table.emplace(llarm::as::id::arm::FCVTSD,  [this](const arm_code_t& code) { this->instructions.arm.vfp.FCVTSD(code); }); 
            arm_table.emplace(llarm::as::id::arm::FDIVD,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FDIVD(code); }); 
            arm_table.emplace(llarm::as::id::arm::FLDD,    [this](const arm_code_t& code) { this->instructions.arm.vfp.FLDD(code); }); 
            arm_table.emplace(llarm::as::id::arm::FLDMD,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FLDMD(code); }); 
            arm_table.emplace(llarm::as::id::arm::FMACD,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FMACD(code); }); 
            arm_table.emplace(llarm::as::id::arm::FMDHR,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FMDHR(code); }); 
            arm_table.emplace(llarm::as::id::arm::FMDLR,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FMDLR(code); }); 
            arm_table.emplace(llarm::as::id::arm::FMRDL,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FMRDL(code); }); 
            arm_table.emplace(llarm::as::id::arm::FMRDH,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FMRDH(code); }); 
            arm_table.emplace(llarm::as::id::arm::FMSCD,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FMSCD(code); }); 
            arm_table.emplace(llarm::as::id::arm::FMULD,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FMULD(code); }); 
            arm_table.emplace(llarm::as::id::arm::FNEGD,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FNEGD(code); }); 
            arm_table.emplace(llarm::as::id::arm::FNMACD,  [this](const arm_code_t& code) { this->instructions.arm.vfp.FNMACD(code); }); 
            arm_table.emplace(llarm::as::id::arm::FNMSCD,  [this](const arm_code_t& code) { this->instructions.arm.vfp.FNMSCD(code); }); 
            arm_table.emplace(llarm::as::id::arm::FNMULD,  [this](const arm_code_t& code) { this->instructions.arm.vfp.FNMULD(code); }); 
            arm_table.emplace(llarm::as::id::arm::FSITOD,  [this](const arm_code_t& code) { this->instructions.arm.vfp.FSITOD(code); }); 
            arm_table.emplace(llarm::as::id::arm::FSQRTD,  [this](const arm_code_t& code) { this->instructions.arm.vfp.FSQRTD(code); }); 
            arm_table.emplace(llarm::as::id::arm::FSTD,    [this](const arm_code_t& code) { this->instructions.arm.vfp.FSTD(code); }); 
            arm_table.emplace(llarm::as::id::arm::FSTMD,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FSTMD(code); }); 
            arm_table.emplace(llarm::as::id::arm::FSUBD,   [this](const arm_code_t& code) { this->instructions.arm.vfp.FSUBD(code); }); 
            arm_table.emplace(llarm::as::id::arm::FTOSID,  [this](const arm_code_t& code) { this->instructions.arm.vfp.FTOSID(code); }); 
            arm_table.emplace(llarm::as::id::arm::FTOUID,  [this](const arm_code_t& code) { this->instructions.arm.vfp.FTOUID(code); }); 
            arm_table.emplace(llarm::as::id::arm::FUITOD,  [this](const arm_code_t& code) { this->instructions.arm.vfp.FUITOD(code); });    
        }
    }

    thumb_table = {
    
        // math
        { llarm::as::id::thumb::ADC,   { [this](const thumb_code_t& code) { this->instructions.thumb.math.ADC(code); } } },
        { llarm::as::id::thumb::ADD1,  { [this](const thumb_code_t& code) { this->instructions.thumb.math.ADD1(code); } } },
        { llarm::as::id::thumb::ADD2,  { [this](const thumb_code_t& code) { this->instructions.thumb.math.ADD2(code); } } },
        { llarm::as::id::thumb::ADD3,  { [this](const thumb_code_t& code) { this->instructions.thumb.math.ADD3(code); } } },
        { llarm::as::id::thumb::ADD4,  { [this](const thumb_code_t& code) { this->instructions.thumb.math.ADD4(code); } } },
        { llarm::as::id::thumb::ADD5,  { [this](const thumb_code_t& code) { this->instructions.thumb.math.ADD5(code); } } },
        { llarm::as::id::thumb::ADD6,  { [this](const thumb_code_t& code) { this->instructions.thumb.math.ADD6(code); } } },
        { llarm::as::id::thumb::ADD7,  { [this](const thumb_code_t& code) { this->instructions.thumb.math.ADD7(code); } } },
        { llarm::as::id::thumb::SBC,   { [this](const thumb_code_t& code) { this->instructions.thumb.math.SBC(code); } } },
        { llarm::as::id::thumb::SUB1,  { [this](const thumb_code_t& code) { this->instructions.thumb.math.SUB1(code); } } },
        { llarm::as::id::thumb::SUB2,  { [this](const thumb_code_t& code) { this->instructions.thumb.math.SUB2(code); } } },
        { llarm::as::id::thumb::SUB3,  { [this](const thumb_code_t& code) { this->instructions.thumb.math.SUB3(code); } } },
        { llarm::as::id::thumb::SUB4,  { [this](const thumb_code_t& code) { this->instructions.thumb.math.SUB4(code); } } },
        { llarm::as::id::thumb::MUL,   { [this](const thumb_code_t& code) { this->instructions.thumb.math.MUL(code); } } },

        // logic
        { llarm::as::id::thumb::AND,   { [this](const thumb_code_t& code) { this->instructions.thumb.logic.AND(code); } } },
        { llarm::as::id::thumb::ASR1,  { [this](const thumb_code_t& code) { this->instructions.thumb.logic.ASR1(code); } } },
        { llarm::as::id::thumb::ASR2,  { [this](const thumb_code_t& code) { this->instructions.thumb.logic.ASR2(code); } } },
        { llarm::as::id::thumb::BIC,   { [this](const thumb_code_t& code) { this->instructions.thumb.logic.BIC(code); } } },
        { llarm::as::id::thumb::EOR,   { [this](const thumb_code_t& code) { this->instructions.thumb.logic.EOR(code); } } },
        { llarm::as::id::thumb::LSL1,  { [this](const thumb_code_t& code) { this->instructions.thumb.logic.LSL1(code); } } },
        { llarm::as::id::thumb::LSL2,  { [this](const thumb_code_t& code) { this->instructions.thumb.logic.LSL2(code); } } },
        { llarm::as::id::thumb::LSR1,  { [this](const thumb_code_t& code) { this->instructions.thumb.logic.LSR1(code); } } },
        { llarm::as::id::thumb::LSR2,  { [this](const thumb_code_t& code) { this->instructions.thumb.logic.LSR2(code); } } },
        { llarm::as::id::thumb::NEG,   { [this](const thumb_code_t& code) { this->instructions.thumb.logic.NEG(code); } } },
        { llarm::as::id::thumb::ORR,   { [this](const thumb_code_t& code) { this->instructions.thumb.logic.ORR(code); } } },
        { llarm::as::id::thumb::ROR,   { [this](const thumb_code_t& code) { this->instructions.thumb.logic.ROR(code); } } },
        { llarm::as::id::thumb::TST,   { [this](const thumb_code_t& code) { this->instructions.thumb.logic.TST(code); } } },

        // comparison
        { llarm::as::id::thumb::CMN,   { [this](const thumb_code_t& code) { this->instructions.thumb.compare.CMN(code); } } },
        { llarm::as::id::thumb::CMP1,  { [this](const thumb_code_t& code) { this->instructions.thumb.compare.CMP1(code); } } },
        { llarm::as::id::thumb::CMP2,  { [this](const thumb_code_t& code) { this->instructions.thumb.compare.CMP2(code); } } },
        { llarm::as::id::thumb::CMP3,  { [this](const thumb_code_t& code) { this->instructions.thumb.compare.CMP3(code); }} },

        // movement
        { llarm::as::id::thumb::MOV1,  { [this](const thumb_code_t& code) { this->instructions.thumb.movement.MOV1(code); } } },
        { llarm::as::id::thumb::MOV2,  { [this](const thumb_code_t& code) { this->instructions.thumb.movement.MOV2(code); } } },
        { llarm::as::id::thumb::MOV3,  { [this](const thumb_code_t& code) { this->instructions.thumb.movement.MOV3(code); } } },
        { llarm::as::id::thumb::MVN,   { [this](const thumb_code_t& code) { this->instructions.thumb.movement.MVN(code); } } },

        // branching
        { llarm::as::id::thumb::B1,    { [this](const thumb_code_t& code) { this->instructions.thumb.branching.B1(code); } } },
        { llarm::as::id::thumb::B2,    { [this](const thumb_code_t& code) { this->instructions.thumb.branching.B2(code); } } },
        { llarm::as::id::thumb::BL,    { [this](const thumb_code_t& code) { this->instructions.thumb.branching.BL(code); } } },
        { llarm::as::id::thumb::BX,    { [this](const thumb_code_t& code) { this->instructions.thumb.branching.BX(code); } } },
        { llarm::as::id::thumb::BLX1,  { [this](const thumb_code_t& code) { this->instructions.thumb.branching.BLX1(code); } } },
        { llarm::as::id::thumb::BLX2,  { [this](const thumb_code_t& code) { this->instructions.thumb.branching.BLX2(code); } } },

        // misc
        { llarm::as::id::thumb::NOP,   { [this](const thumb_code_t& code) { this->instructions.thumb.misc.NOP(code); } } },
        { llarm::as::id::thumb::SWI,   { [this](const thumb_code_t& code) { this->instructions.thumb.misc.SWI(code); } } },
        { llarm::as::id::thumb::BKPT,  { [this](const thumb_code_t& code) { this->instructions.thumb.misc.BKPT(code); } } },

        // load
        { llarm::as::id::thumb::LDMIA, { [this](const thumb_code_t& code) { this->instructions.thumb.load.LDMIA(code); } } },
        { llarm::as::id::thumb::LDR1,  { [this](const thumb_code_t& code) { this->instructions.thumb.load.LDR1(code); } } },
        { llarm::as::id::thumb::LDR2,  { [this](const thumb_code_t& code) { this->instructions.thumb.load.LDR2(code); } } },
        { llarm::as::id::thumb::LDR3,  { [this](const thumb_code_t& code) { this->instructions.thumb.load.LDR3(code); } } },
        { llarm::as::id::thumb::LDR4,  { [this](const thumb_code_t& code) { this->instructions.thumb.load.LDR4(code); } } },
        { llarm::as::id::thumb::LDRB1, { [this](const thumb_code_t& code) { this->instructions.thumb.load.LDRB1(code); } } },
        { llarm::as::id::thumb::LDRB2, { [this](const thumb_code_t& code) { this->instructions.thumb.load.LDRB2(code); } } },
        { llarm::as::id::thumb::LDRH1, { [this](const thumb_code_t& code) { this->instructions.thumb.load.LDRH1(code); } } },
        { llarm::as::id::thumb::LDRH2, { [this](const thumb_code_t& code) { this->instructions.thumb.load.LDRH2(code); } } },
        { llarm::as::id::thumb::LDRSB, { [this](const thumb_code_t& code) { this->instructions.thumb.load.LDRSB(code); } } },
        { llarm::as::id::thumb::LDRSH, { [this](const thumb_code_t& code) { this->instructions.thumb.load.LDRSH(code); } } },
        { llarm::as::id::thumb::POP,   { [this](const thumb_code_t& code) { this->instructions.thumb.load.POP(code); } } },

        // store
        { llarm::as::id::thumb::STMIA, { [this](const thumb_code_t& code) { this->instructions.thumb.store.STMIA(code); } } },
        { llarm::as::id::thumb::STR1,  { [this](const thumb_code_t& code) { this->instructions.thumb.store.STR1(code); } } },
        { llarm::as::id::thumb::STR2,  { [this](const thumb_code_t& code) { this->instructions.thumb.store.STR2(code); } } },
        { llarm::as::id::thumb::STR3,  { [this](const thumb_code_t& code) { this->instructions.thumb.store.STR3(code); } } },
        { llarm::as::id::thumb::STRB1, { [this](const thumb_code_t& code) { this->instructions.thumb.store.STRB1(code); } } },
        { llarm::as::id::thumb::STRH1, { [this](const thumb_code_t& code) { this->instructions.thumb.store.STRH1(code); } } },
        { llarm::as::id::thumb::STRH2, { [this](const thumb_code_t& code) { this->instructions.thumb.store.STRH2(code); } } },
        { llarm::as::id::thumb::PUSH,  { [this](const thumb_code_t& code) { this->instructions.thumb.store.PUSH(code); } } }
    };
}