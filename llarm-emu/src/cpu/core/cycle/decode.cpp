#include "../../../id.hpp"

#include "decode.hpp"

#include "shared/types.hpp"
#include "shared/out.hpp"

#include <llarm-asm/llarm-asm.hpp>


bool DECODE::has_condition_failed(const id::cond cond) {
    return (reg.check_cond(cond));
}


bool DECODE::is_arm_instruction_unsupported(const llarm::as::id::arm id) {
    using namespace llarm;

    if (settings.is_arch_version_inst_check_enabled == false) {
        return false;
    }

    const id::specific_arch instruction_arch_support = [=]() -> id::specific_arch {
        switch (id) {
            case as::id::arm::UNKNOWN: shared::out::warning("Unknown instruction check for ARM arch version support lookup");
            case as::id::arm::UNDEFINED:
            case as::id::arm::ADC:
            case as::id::arm::ADD:
            case as::id::arm::RSB:
            case as::id::arm::BIC:
            case as::id::arm::RSC:
            case as::id::arm::SBC:
            case as::id::arm::SUB:
            case as::id::arm::CMN:
            case as::id::arm::AND:
            case as::id::arm::CMP:
            case as::id::arm::EOR:
            case as::id::arm::ORR:
            case as::id::arm::TEQ:
            case as::id::arm::TST:
            case as::id::arm::MOV:
            case as::id::arm::MVN:
            case as::id::arm::B:
            case as::id::arm::BL:
            case as::id::arm::NOP:
            case as::id::arm::PSR:
            case as::id::arm::SWI:
            case as::id::arm::LDM1:
            case as::id::arm::LDM2:
            case as::id::arm::LDM3:
            case as::id::arm::LDR:
            case as::id::arm::LDRB:
            case as::id::arm::LDRBT:
            case as::id::arm::LDRT:
            case as::id::arm::STM1: 
            case as::id::arm::STM2: 
            case as::id::arm::STR: 
            case as::id::arm::STRB: 
            case as::id::arm::STRBT:
            case as::id::arm::STRT: return id::specific_arch::ARMv1;
            
            // ARMv2
            case as::id::arm::CDP:
            case as::id::arm::LDC:
            case as::id::arm::MCR:
            case as::id::arm::MRC:
            case as::id::arm::STC:
            case as::id::arm::MLA:
            case as::id::arm::MUL:
            case as::id::arm::SWP: return id::specific_arch::ARMv2;
            case as::id::arm::SWPB: return id::specific_arch::ARMv2a;
            
            // ARMv3
            case as::id::arm::MRS:
            case as::id::arm::MSR_IMM:
            case as::id::arm::MSR_REG: return id::specific_arch::ARMv3;
            
            // ARMv4
            case as::id::arm::LDRH:
            case as::id::arm::LDRSB:
            case as::id::arm::LDRSH:
            case as::id::arm::STRH: return id::specific_arch::ARMv4;
            case as::id::arm::BX: return id::specific_arch::ARMv4T;
            
            // ARMv5
            case as::id::arm::BKPT:
            case as::id::arm::BLX1:
            case as::id::arm::BLX2:
            case as::id::arm::CLZ:
            case as::id::arm::CDP2:
            case as::id::arm::LDC2:
            case as::id::arm::MCR2:
            case as::id::arm::MRC2:
            case as::id::arm::STC2: return id::specific_arch::ARMv5;

            // ARMv5TE: 
            case as::id::arm::MCRR:
            case as::id::arm::MRRC:
            case as::id::arm::PLD:
            case as::id::arm::STRD:
            case as::id::arm::LDRD: return id::specific_arch::ARMv5TE;

            // ARMv5TExP:
            case as::id::arm::QADD:
            case as::id::arm::QDADD:
            case as::id::arm::QDSUB:
            case as::id::arm::QSUB:
            case as::id::arm::SMLAXY:
            case as::id::arm::SMLALXY:
            case as::id::arm::SMLAWY:
            case as::id::arm::SMULXY:
            case as::id::arm::SMULWY: return id::specific_arch::ARMv5TExP;
            default: return id::specific_arch::UNKNOWN;
        }
    }();
    
    if (instruction_arch_support == id::specific_arch::UNKNOWN) {
        switch (id) {
            // long multiplications
            case as::id::arm::SMLAL: 
            case as::id::arm::SMULL: 
            case as::id::arm::UMLAL: 
            case as::id::arm::UMULL:
                return (
                    (settings.specific_arch != id::specific_arch::ARMv3M) &&
                    (settings.specific_arch != id::specific_arch::ARMv4) &&
                    (settings.specific_arch != id::specific_arch::ARMv4T) &&
                    (settings.specific_arch != id::specific_arch::ARMv5) &&
                    (settings.specific_arch != id::specific_arch::ARMv5T) &&
                    (settings.specific_arch != id::specific_arch::ARMv5TE) &&
                    (settings.specific_arch != id::specific_arch::ARMv5TExP) &&
                    (settings.specific_arch < id::specific_arch::ARMv6)
                );

            // single precision VFP
            case as::id::arm::FABSS:
            case as::id::arm::FADDS:
            case as::id::arm::FCMPES:
            case as::id::arm::FCMPEZS:
            case as::id::arm::FCMPS:
            case as::id::arm::FCMPZS:
            case as::id::arm::FCPYS:
            case as::id::arm::FDIVS:
            case as::id::arm::FLDMS:
            case as::id::arm::FLDMX:
            case as::id::arm::FLDS:
            case as::id::arm::FMACS:
            case as::id::arm::FMRS:
            case as::id::arm::FMRX:
            case as::id::arm::FMSCS:
            case as::id::arm::FMSR:
            case as::id::arm::FMSTAT:
            case as::id::arm::FMULS:
            case as::id::arm::FMXR:
            case as::id::arm::FNEGS:
            case as::id::arm::FNMACS:
            case as::id::arm::FNMSCS:
            case as::id::arm::FNMULS:
            case as::id::arm::FSITOS:
            case as::id::arm::FSQRTS:
            case as::id::arm::FSTMS:
            case as::id::arm::FSTMX:
            case as::id::arm::FSTS:
            case as::id::arm::FSUBS:
            case as::id::arm::FTOSIS:
            case as::id::arm::FTOUIS:
            case as::id::arm::FUITOS:
                if (settings.is_vfp_single_precision_enabled == false) {
                    return true;
                }

            // double precision VFP
            case as::id::arm::FABSD:
            case as::id::arm::FADDD:
            case as::id::arm::FCMPD:
            case as::id::arm::FCMPED:
            case as::id::arm::FCMPEZD:
            case as::id::arm::FCMPZD:
            case as::id::arm::FCPYD:
            case as::id::arm::FCVTDS:
            case as::id::arm::FCVTSD:
            case as::id::arm::FDIVD:
            case as::id::arm::FLDD:
            case as::id::arm::FLDMD:
            case as::id::arm::FMACD:
            case as::id::arm::FMDHR:
            case as::id::arm::FMDLR:
            case as::id::arm::FMRDL:
            case as::id::arm::FMRDH:
            case as::id::arm::FMSCD:
            case as::id::arm::FMULD:
            case as::id::arm::FNEGD:
            case as::id::arm::FNMACD:
            case as::id::arm::FNMSCD:
            case as::id::arm::FNMULD:
            case as::id::arm::FSITOD:
            case as::id::arm::FSQRTD:
            case as::id::arm::FSTD:
            case as::id::arm::FSTMD:
            case as::id::arm::FSUBD:
            case as::id::arm::FTOSID:
            case as::id::arm::FTOUID:
            case as::id::arm::FUITOD: 
                // ARMv5
                if (settings.is_vfp_double_precision_enabled == false || settings.is_vfp_enabled == false) {
                    return true;
                }
                
                // double precision was introduced in VFPv2
                if (settings.vfp_version < 2) {
                    return true;
                }

                // TODO (ARMv6): more conditions should be added
                return (settings.product_family != id::product_family::ARM10E);
                
            default: shared::out::dev_error("Unknown instruction encountered during instruction support lookup");
        }
    }

    return (settings.specific_arch < instruction_arch_support);
}


bool DECODE::is_thumb_instruction_unsupported(const llarm::as::id::thumb id) {
    using namespace llarm; // for llarm::as

    if (settings.is_arch_version_inst_check_enabled == false) {
        return false;
    }

    if (settings.thumb_version == id::thumb_version::NO_THUMB) {
        return true;
    }

    if (settings.thumb_version == id::thumb_version::THUMB1) {
        // these are all thumb-2 instructions
        switch (id) {
            case as::id::thumb::BKPT: 
            case as::id::thumb::BLX1: 
            case as::id::thumb::BLX2: return true;
            default: return false;
        }
    }

    return false;
}


arm_decode_struct DECODE::arm_decode(const arm_code_t &raw_code) {
    using namespace llarm; // for llarm::assembly

    const id::cond cond = reg.fetch_cond_id(raw_code);

    if (has_condition_failed(cond)) {
        return arm_decode_struct {
            assembly::id::arm::NOP, // id
            arm_code_t(0) // code
        };
    }

    const assembly::id::arm id = assembly::identify::arm(raw_code);

    if (is_arm_instruction_unsupported(id)) {
        return arm_decode_struct {
            assembly::id::arm::UNDEFINED, // id
            raw_code // code
        };
    }

    return arm_decode_struct {
        id, // id
        raw_code // code
    };
}


thumb_decode_struct DECODE::thumb_decode(const thumb_code_t &raw_code) {
    using namespace llarm; // for llarm::assembly

    const assembly::id::thumb id = assembly::identify::thumb(raw_code);

    if (is_thumb_instruction_unsupported(id)) {
        return thumb_decode_struct {
            assembly::id::thumb::UNDEFINED, // id
            raw_code // code
        };
    }

    return thumb_decode_struct {
        id, // id
        raw_code // code
    };
}


DECODE::DECODE(
    REGISTERS& reg,
    SETTINGS& settings
) : reg(reg), settings(settings) {

}