#include "generators.hpp"
#include "shared/util.hpp"

using namespace internal;

bool generators::is_imm_encodable(const u32 imm) {
    // 1 byte immeds are always encodable
    if ((imm & 0xFFFFFF00) == 0) {
        return true;
    }

    // try every possible rotation
    for (u8 rot = 0; rot < 32; rot += 2) {
        const u32 rotated = std::rotr(imm, rot);

        if ((rotated & 0xFFFFFF00) == 0) {
            return true;
        }
    }

    return false;
}


void encode_imm(u32 &binary, const u32 immed) {
    for (u32 rot = 0; rot < 16; ++rot) {
        u32 rotated = std::rotr(immed, rot * 2);
        if ((rotated & 0xFFFFFF00) == 0) {
            llarm::util::swap_bits(binary, 8, 11, static_cast<u8>(rotated));
            llarm::util::swap_bits(binary, 0, 7, static_cast<u8>(immed));
        }
    }
}


u32 generators::arm(const id::arm id, const arguments &args) {
    switch (id) {
        case id::arm::UNKNOWN: return 0;
        case id::arm::UNDEFINED:  return 0;
        case id::arm::NOP: return 0;
        case id::arm::ADC: return data_instruction(id, args);
        case id::arm::ADD: return data_instruction(id, args);
        case id::arm::AND: return data_instruction(id, args);
        case id::arm::BIC: return data_instruction(id, args);
        case id::arm::CMN: return data_instruction(id, args);
        case id::arm::CMP: return data_instruction(id, args);
        case id::arm::EOR: return data_instruction(id, args);
        case id::arm::MOV: return data_instruction(id, args);
        case id::arm::MVN: return data_instruction(id, args);
        case id::arm::ORR: return data_instruction(id, args);
        case id::arm::RSB: return data_instruction(id, args);
        case id::arm::RSC: return data_instruction(id, args);
        case id::arm::SBC: return data_instruction(id, args);
        case id::arm::SUB: return data_instruction(id, args);
        case id::arm::TEQ: return data_instruction(id, args);
        case id::arm::TST: return data_instruction(id, args);
        case id::arm::CMNP: return data_instruction(id, args);
        case id::arm::CMPP: return data_instruction(id, args);
        case id::arm::TEQP: return data_instruction(id, args);
        case id::arm::TSTP: return data_instruction(id, args);
        case id::arm::LDR: return ls_instruction(id, args);
        case id::arm::STR: return ls_instruction(id, args);
        case id::arm::LDRB: return ls_instruction(id, args);
        case id::arm::LDRT: return ls_instruction(id, args);
        case id::arm::STRB: return ls_instruction(id, args);
        case id::arm::STRT: return ls_instruction(id, args);
        case id::arm::LDRBT: return ls_instruction(id, args);
        case id::arm::STRBT: return ls_instruction(id, args);
        case id::arm::PLD: return ls_instruction(id, args);
        case id::arm::STRH: return ls_misc_instruction(id, args);
        case id::arm::LDRH: return ls_misc_instruction(id, args);
        case id::arm::LDRSB: return ls_misc_instruction(id, args);
        case id::arm::LDRSH: return ls_misc_instruction(id, args);
        case id::arm::LDRD: return ls_misc_instruction(id, args);
        case id::arm::STRD: return ls_misc_instruction(id, args);
        case id::arm::LDM1: return ls_mul_instruction(id, args);
        case id::arm::LDM2: return ls_mul_instruction(id, args);
        case id::arm::LDM3: return ls_mul_instruction(id, args);
        case id::arm::STM1: return ls_mul_instruction(id, args);
        case id::arm::STM2: return ls_mul_instruction(id, args);
        case id::arm::LDC2: return ls_coproc_instruction(id, args);
        case id::arm::LDC: return ls_coproc_instruction(id, args);
        case id::arm::STC2: return ls_coproc_instruction(id, args);
        case id::arm::STC: return ls_coproc_instruction(id, args);
        case id::arm::B: return b(args);
        case id::arm::BL: return bl(args);
        case id::arm::CDP: return cdp(args);
        case id::arm::CDP2: return cdp(args);
        case id::arm::MCR: return mcr(args);
        case id::arm::MCR2: return mcr(args);
        case id::arm::MLA: return mla(args);
        case id::arm::MRC: return mrc(args);
        case id::arm::MRC2: return mrc(args);
        case id::arm::MRS: return mrs(args);
        case id::arm::MSR_IMM: return msr_imm(args);
        case id::arm::MSR_REG: return msr_reg(args);
        case id::arm::MUL: return mul(args);
        case id::arm::SWI: return swi(args);
        case id::arm::SWP: return swp(args); 
        case id::arm::SWPB: return swpb(args);
        case id::arm::BKPT: return bkpt(args);
        case id::arm::BLX1: return blx1(args);
        case id::arm::BLX2: return blx2(args);
        case id::arm::CLZ: return clz(args);
        case id::arm::BX: return bx(args);
        case id::arm::SMLAL: return mul_instructions(id, args);
        case id::arm::SMULL: return mul_instructions(id, args);
        case id::arm::UMLAL: return mul_instructions(id, args);
        case id::arm::UMULL: return mul_instructions(id, args);
        case id::arm::MCRR: return mcrr(args);
        case id::arm::MRRC: return mrrc(args);
        case id::arm::QADD: return q_instructions(id, args);
        case id::arm::QDADD: return q_instructions(id, args);
        case id::arm::QDSUB: return q_instructions(id, args);
        case id::arm::QSUB: return q_instructions(id, args);
        case id::arm::SMLAXY: return dsp_mul_instructions(id, args);
        case id::arm::SMLALXY: return dsp_mul_instructions(id, args);
        case id::arm::SMLAWY: return dsp_mul_instructions(id, args);
        case id::arm::SMULXY: return dsp_mul_instructions(id, args);
        case id::arm::SMULWY: return dsp_mul_instructions(id, args);
        case id::arm::FADDD: return vfp_Dd_Dn_Dm_instructions(id, args);
        case id::arm::FDIVD: return vfp_Dd_Dn_Dm_instructions(id, args);
        case id::arm::FMACD: return vfp_Dd_Dn_Dm_instructions(id, args);
        case id::arm::FMSCD: return vfp_Dd_Dn_Dm_instructions(id, args);
        case id::arm::FMULD: return vfp_Dd_Dn_Dm_instructions(id, args);
        case id::arm::FNMACD: return vfp_Dd_Dn_Dm_instructions(id, args);
        case id::arm::FNMSCD: return vfp_Dd_Dn_Dm_instructions(id, args);
        case id::arm::FNMULD: return vfp_Dd_Dn_Dm_instructions(id, args);
        case id::arm::FSUBD: return vfp_Dd_Dn_Dm_instructions(id, args);
        case id::arm::FADDS: return vfp_Sd_Sn_Sm_instructions(id, args);
        case id::arm::FDIVS: return vfp_Sd_Sn_Sm_instructions(id, args);
        case id::arm::FMACS: return vfp_Sd_Sn_Sm_instructions(id, args);
        case id::arm::FMSCS: return vfp_Sd_Sn_Sm_instructions(id, args);
        case id::arm::FMULS: return vfp_Sd_Sn_Sm_instructions(id, args);
        case id::arm::FNMACS: return vfp_Sd_Sn_Sm_instructions(id, args);
        case id::arm::FNMSCS: return vfp_Sd_Sn_Sm_instructions(id, args);
        case id::arm::FNMULS: return vfp_Sd_Sn_Sm_instructions(id, args);
        case id::arm::FSUBS: return vfp_Sd_Sn_Sm_instructions(id, args);
        case id::arm::FABSD:  return vfp_Dd_Dm_instructions(id, args);
        case id::arm::FCMPD:  return vfp_Dd_Dm_instructions(id, args);
        case id::arm::FCMPED: return vfp_Dd_Dm_instructions(id, args);
        case id::arm::FCPYD:  return vfp_Dd_Dm_instructions(id, args);
        case id::arm::FSQRTD: return vfp_Dd_Dm_instructions(id, args);
        case id::arm::FNEGD:  return vfp_Dd_Dm_instructions(id, args);
        case id::arm::FABSS: return vfp_Sd_Sm_instructions(id, args);
        case id::arm::FCMPES: return vfp_Sd_Sm_instructions(id, args);
        case id::arm::FCMPS: return vfp_Sd_Sm_instructions(id, args);
        case id::arm::FCPYS: return vfp_Sd_Sm_instructions(id, args);
        case id::arm::FNEGS: return vfp_Sd_Sm_instructions(id, args);
        case id::arm::FSITOS: return vfp_Sd_Sm_instructions(id, args); 
        case id::arm::FSQRTS: return vfp_Sd_Sm_instructions(id, args);
        case id::arm::FTOSIS: return vfp_Sd_Sm_instructions(id, args);
        case id::arm::FTOUIS: return vfp_Sd_Sm_instructions(id, args);
        case id::arm::FUITOS: return vfp_Sd_Sm_instructions(id, args);
        case id::arm::FCVTDS: return vfp_Dd_Sm_instructions(id, args);
        case id::arm::FSITOD: return vfp_Dd_Sm_instructions(id, args);
        case id::arm::FUITOD: return vfp_Dd_Sm_instructions(id, args);
        case id::arm::FCVTSD: return vfp_Sd_Dm_instructions(id, args);
        case id::arm::FTOSID: return vfp_Sd_Dm_instructions(id, args);
        case id::arm::FTOUID: return vfp_Sd_Dm_instructions(id, args);
        case id::arm::FLDMD: return vfp_mul_instructions(id, args);
        case id::arm::FLDMS: return vfp_mul_instructions(id, args);
        case id::arm::FLDMX: return vfp_mul_instructions(id, args);
        case id::arm::FLDD: return vfp_mul_instructions(id, args); 
        case id::arm::FLDS: return vfp_mul_instructions(id, args); 
        case id::arm::FSTD: return vfp_mul_instructions(id, args); 
        case id::arm::FSTMD: return vfp_mul_instructions(id, args); 
        case id::arm::FSTMS: return vfp_mul_instructions(id, args); 
        case id::arm::FSTMX: return vfp_mul_instructions(id, args); 
        case id::arm::FSTS: return vfp_mul_instructions(id, args); 
        case id::arm::FCMPEZD: return fcmpezd(args);
        case id::arm::FCMPZD: return fcmpzd(args);
        case id::arm::FCMPEZS: return fcmpezs(args);
        case id::arm::FCMPZS: return fcmpzs(args);
        case id::arm::FMDHR: return fmdhr(args);
        case id::arm::FMDLR: return fmdlr(args);
        case id::arm::FMRDH: return fmrdh(args);
        case id::arm::FMRDL: return fmrdl(args);
        case id::arm::FMRS: return fmrs(args);
        case id::arm::FMRX: return fmrx(args);
        case id::arm::FMSR: return fmsr(args);
        case id::arm::FMSTAT: return fmstat(args);
        case id::arm::FMXR: return fmxr(args);
    }
}
