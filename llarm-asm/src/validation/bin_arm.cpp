
#include "bin_arm.hpp"
#include "../id/shifter_id.hpp"
#include "../identifiers/bin_arm.hpp"
#include "../identifiers/bin_shifters.hpp"

#include <llarm/shared/util.hpp>
#include <llarm/shared/types.hpp>

using namespace internal;



bool validation::bin_arm::check_shifter(const u32 code, const shifter_category category) {
    const shifter_id shifter = ident::bin_shifters::identify_shifter(category, code);

    return (shifter != shifter_id::UNKNOWN);
};


// PLD instruction only has 3 LS shifters supported
bool validation::bin_arm::check_PLD(const u32 code) {
    const shifter_id shifter = ident::bin_shifters::identify_shifter(shifter_category::LS, code);

    switch (shifter) {
        case shifter_id::LS_IMM: 
        case shifter_id::LS_REG:
        case shifter_id::LS_SCALED_ASR:
        case shifter_id::LS_SCALED_LSL:
        case shifter_id::LS_SCALED_LSR:
        case shifter_id::LS_SCALED_ROR:
        case shifter_id::LS_SCALED_RRX: return true;
        default: return false;
    }
};


// offset must be at least 0 and be an even number, and must have a valid reglist config
bool validation::bin_arm::check_vfp_reglist(const u32 code, const arm_id id) {
    const u8 offset = llarm::util::bit_range<u8>(code, 0, 7);

    if (offset == 0 || offset & 1) {
        return false;
    }

    const u8 Dd = llarm::util::bit_range<u8>(code, 12, 15);

    switch (id) {
        case arm_id::FLDMD: 
        case arm_id::FSTMD: {
            if (((offset >> 1) + Dd) > 15) {
                return false;
            }
            break;
        }

        case arm_id::FLDMX:
        case arm_id::FSTMX: {
            if ((((offset >> 1) - 1) + Dd) > 15) {
                return false;
            }
            break;
        }
            
        case arm_id::FLDMS:
        case arm_id::FSTMS: {
            const bool D = (Dd & 1);
            const u8 Fd = llarm::util::bit_range<u8>(Dd, 1, 4);
            const u8 Sd = static_cast<u8>((Fd << 1) | D);

            if ((offset + Sd) > 31) {
                return false;
            }
            break;
        }

        default: return false;
    }

    return true;
};


bool validation::bin_arm::check_move_system_reg(const u32 code) {
    const u8 reg = llarm::util::bit_range<u8>(code, 16, 19);

    switch (reg) {
        case 0b0000: // FPSID
        case 0b0001: // FPSCR
        case 0b1000: // FPEXC
            return true;
        default: return false; 
    } 
};


bool validation::bin_arm::is_arm_instruction_valid(const u32 code) {
    const arm_id id = ident::bin_arm::arm(code);

    switch (id) {
        case arm_id::UNKNOWN: return false;
        case arm_id::UNDEFINED: return false;
        case arm_id::NOP: return false;
        case arm_id::ADC: return check_shifter(code, shifter_category::DATA);
        case arm_id::ADD: return check_shifter(code, shifter_category::DATA);
        case arm_id::RSB: return check_shifter(code, shifter_category::DATA);
        case arm_id::BIC: return check_shifter(code, shifter_category::DATA);
        case arm_id::RSC: return check_shifter(code, shifter_category::DATA);
        case arm_id::SBC: return check_shifter(code, shifter_category::DATA);
        case arm_id::SUB: return check_shifter(code, shifter_category::DATA);
        case arm_id::CMN: return check_shifter(code, shifter_category::DATA);
        case arm_id::AND: return check_shifter(code, shifter_category::DATA);
        case arm_id::CMP: return check_shifter(code, shifter_category::DATA);
        case arm_id::EOR: return check_shifter(code, shifter_category::DATA);
        case arm_id::ORR: return check_shifter(code, shifter_category::DATA);
        case arm_id::TEQ: return check_shifter(code, shifter_category::DATA);
        case arm_id::TST: return check_shifter(code, shifter_category::DATA);
        case arm_id::MOV: return check_shifter(code, shifter_category::DATA);
        case arm_id::MVN: return check_shifter(code, shifter_category::DATA);
        case arm_id::CMNP: return check_shifter(code, shifter_category::DATA);
        case arm_id::CMPP: return check_shifter(code, shifter_category::DATA);
        case arm_id::TEQP: return check_shifter(code, shifter_category::DATA);
        case arm_id::TSTP: return check_shifter(code, shifter_category::DATA);
        case arm_id::LDR: return check_shifter(code, shifter_category::LS);
        case arm_id::LDRB: return check_shifter(code, shifter_category::LS);
        case arm_id::LDRBT: return check_shifter(code, shifter_category::LS);
        case arm_id::LDRT: return check_shifter(code, shifter_category::LS);
        case arm_id::STR: return check_shifter(code, shifter_category::LS);
        case arm_id::STRB: return check_shifter(code, shifter_category::LS);
        case arm_id::STRBT: return check_shifter(code, shifter_category::LS);
        case arm_id::STRT: return check_shifter(code, shifter_category::LS);
        case arm_id::LDRH: return check_shifter(code, shifter_category::LS_MISC);
        case arm_id::LDRSB: return check_shifter(code, shifter_category::LS_MISC);
        case arm_id::LDRSH: return check_shifter(code, shifter_category::LS_MISC);
        case arm_id::STRH: return check_shifter(code, shifter_category::LS_MISC);
        case arm_id::LDM1: return check_shifter(code, shifter_category::LS_MUL);
        case arm_id::LDM2: return check_shifter(code, shifter_category::LS_MUL);
        case arm_id::LDM3: return check_shifter(code, shifter_category::LS_MUL);
        case arm_id::STM1: return check_shifter(code, shifter_category::LS_MUL);
        case arm_id::STM2: return check_shifter(code, shifter_category::LS_MUL);
        case arm_id::LDC: return check_shifter(code, shifter_category::LS_COPROC);
        case arm_id::STC: return check_shifter(code, shifter_category::LS_COPROC);
        case arm_id::LDC2: return check_shifter(code, shifter_category::LS_COPROC);
        case arm_id::STC2: return check_shifter(code, shifter_category::LS_COPROC);
        case arm_id::PLD: return check_PLD(code);
        case arm_id::FLDMS: return check_vfp_reglist(code, id);
        case arm_id::FLDMX: return check_vfp_reglist(code, id);
        case arm_id::FMRX: return check_move_system_reg(code);
        case arm_id::FMXR: return check_move_system_reg(code);
        case arm_id::FSTMS: return check_vfp_reglist(code, id);
        case arm_id::FSTMX: return check_vfp_reglist(code, id);
        case arm_id::FLDMD: return check_vfp_reglist(code, id);
        case arm_id::FSTMD: return check_vfp_reglist(code, id);
        case arm_id::B:
        case arm_id::BL:
        case arm_id::SWI:
        case arm_id::CDP:
        case arm_id::MCR:
        case arm_id::MRC:
        case arm_id::SWP:
        case arm_id::SWPB:
        case arm_id::MLA:
        case arm_id::MUL:
        case arm_id::SMLAL:
        case arm_id::SMULL:
        case arm_id::UMLAL:
        case arm_id::UMULL:
        case arm_id::MRS:
        case arm_id::MSR_IMM:
        case arm_id::MSR_REG:
        case arm_id::BX:
        case arm_id::BKPT:
        case arm_id::BLX1:
        case arm_id::BLX2:
        case arm_id::CLZ:
        case arm_id::CDP2:
        case arm_id::MCR2:
        case arm_id::MRC2:
        case arm_id::MCRR:
        case arm_id::MRRC:
        case arm_id::STRD:
        case arm_id::LDRD:
        case arm_id::QADD:
        case arm_id::QDADD:
        case arm_id::QDSUB:
        case arm_id::QSUB:
        case arm_id::SMLAXY:
        case arm_id::SMLALXY:
        case arm_id::SMLAWY:
        case arm_id::SMULXY:
        case arm_id::SMULWY:
        case arm_id::FABSS:
        case arm_id::FADDS:
        case arm_id::FCMPES:
        case arm_id::FCMPEZS:
        case arm_id::FCMPS:
        case arm_id::FCMPZS:
        case arm_id::FCPYS:
        case arm_id::FDIVS:
        case arm_id::FLDS:
        case arm_id::FMACS:
        case arm_id::FMRS:
        case arm_id::FMSCS:
        case arm_id::FMSR:
        case arm_id::FMSTAT:
        case arm_id::FMULS:
        case arm_id::FNEGS:
        case arm_id::FNMACS:
        case arm_id::FNMSCS:
        case arm_id::FNMULS:
        case arm_id::FSITOS:
        case arm_id::FSQRTS:
        case arm_id::FSTS:
        case arm_id::FSUBS:
        case arm_id::FTOSIS:
        case arm_id::FTOUIS:
        case arm_id::FUITOS:
        case arm_id::FABSD:
        case arm_id::FADDD:
        case arm_id::FCMPD:
        case arm_id::FCMPED:
        case arm_id::FCMPEZD:
        case arm_id::FCMPZD:
        case arm_id::FCPYD:
        case arm_id::FCVTDS:
        case arm_id::FCVTSD:
        case arm_id::FDIVD:
        case arm_id::FLDD:
        case arm_id::FMACD:
        case arm_id::FMDHR:
        case arm_id::FMDLR:
        case arm_id::FMRDL:
        case arm_id::FMRDH:
        case arm_id::FMSCD:
        case arm_id::FMULD:
        case arm_id::FNEGD:
        case arm_id::FNMACD:
        case arm_id::FNMSCD:
        case arm_id::FNMULD:
        case arm_id::FSITOD:
        case arm_id::FSQRTD:
        case arm_id::FSTD:
        case arm_id::FSUBD:
        case arm_id::FTOSID:
        case arm_id::FTOUID:
        case arm_id::FUITOD: return true;
        case arm_id::CPS: // TODO
        case arm_id::CPY: // TODO
        case arm_id::LDREX: // TODO
        case arm_id::MCRR2: // TODO
        case arm_id::MRRC2: // TODO
        case arm_id::PKHBT: // TODO
        case arm_id::PKHTB: // TODO
        case arm_id::QADD16: // TODO
        case arm_id::QADD8: // TODO
        case arm_id::QADDSUBX: // TODO
        case arm_id::QSUB16: // TODO
        case arm_id::QSUB8: // TODO
        case arm_id::QSUBADDX: // TODO
        case arm_id::REV: // TODO
        case arm_id::REV16: // TODO
        case arm_id::REVSH: // TODO
        case arm_id::RFE: // TODO
        case arm_id::SADD16: // TODO
        case arm_id::SADD8: // TODO
        case arm_id::SADDSUBX: // TODO
        case arm_id::SEL: // TODO
        case arm_id::SETEND: // TODO
        case arm_id::SHADD16: // TODO
        case arm_id::SHADD8: // TODO
        case arm_id::SHADDSUBX: // TODO
        case arm_id::SHSUB16: // TODO
        case arm_id::SHSUB8: // TODO
        case arm_id::SHSUBADDX: // TODO
        case arm_id::SMLAD: // TODO
        case arm_id::SMLALD: // TODO
        case arm_id::SMLSD: // TODO
        case arm_id::SMLSLD: // TODO
        case arm_id::SMMLA: // TODO
        case arm_id::SMMLS: // TODO
        case arm_id::SMMUL: // TODO
        case arm_id::SMUAD: // TODO
        case arm_id::SMUSD: // TODO
        case arm_id::SRS: // TODO
        case arm_id::SSAT: // TODO
        case arm_id::SSAT16: // TODO
        case arm_id::SSUB16: // TODO
        case arm_id::SSUB8: // TODO
        case arm_id::SSUBADDX: // TODO
        case arm_id::STREX: // TODO
        case arm_id::SXTAB: // TODO
        case arm_id::SXTAB16: // TODO
        case arm_id::SXTAH: // TODO
        case arm_id::SXTB: // TODO
        case arm_id::SXTB16: // TODO
        case arm_id::SXTH: // TODO
        case arm_id::UADD16: // TODO
        case arm_id::UADD8: // TODO
        case arm_id::UADDSUBX: // TODO
        case arm_id::UHADD16: // TODO
        case arm_id::UHADD8: // TODO
        case arm_id::UHADDSUBX: // TODO
        case arm_id::UHSUB16: // TODO
        case arm_id::UHSUB8: // TODO
        case arm_id::UHSUBADDX: // TODO
        case arm_id::UMAAL: // TODO
        case arm_id::UQADD16: // TODO
        case arm_id::UQADD8: // TODO
        case arm_id::UQADDSUBX: // TODO
        case arm_id::UQSUB16: // TODO
        case arm_id::UQSUB8: // TODO
        case arm_id::UQSUBADDX: // TODO
        case arm_id::USAD8: // TODO
        case arm_id::USADA8: // TODO
        case arm_id::USAT: // TODO
        case arm_id::USAT16: // TODO
        case arm_id::USUB16: // TODO
        case arm_id::USUB8: // TODO
        case arm_id::USUBADDX: // TODO
        case arm_id::UXTAB: // TODO
        case arm_id::UXTAB16: // TODO
        case arm_id::UXTAH: // TODO
        case arm_id::UXTB: // TODO
        case arm_id::UXTB16: // TODO
        case arm_id::UXTH: // TODO
            return true;
    }
}