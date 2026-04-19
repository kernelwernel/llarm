#include "../../../id.hpp"

#include "decode.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/out.hpp>

#include <llarm/llarm-asm.hpp>


bool DECODE::has_condition_failed(const id::cond cond) const {
    return (reg.is_cond_valid(cond) == false);
}


bool DECODE::is_arm_instruction_unsupported(const llarm::as::arm_id id) const {
    using namespace llarm::as;

    if (settings.is_arch_version_inst_check_enabled == false) {
        return false;
    }

    const id::specific_arch instruction_arch_support = [=]() -> id::specific_arch {
        switch (id) {
            case arm_id::UNKNOWN: 
                llarm::out::warning("Unknown instruction check for ARM arch version support lookup");
                [[fallthrough]];
    
            case arm_id::UNDEFINED:
            case arm_id::ADC:
            case arm_id::ADD:
            case arm_id::RSB:
            case arm_id::BIC:
            case arm_id::RSC:
            case arm_id::SBC:
            case arm_id::SUB:
            case arm_id::CMN:
            case arm_id::AND:
            case arm_id::CMP:
            case arm_id::EOR:
            case arm_id::ORR:
            case arm_id::TEQ:
            case arm_id::TST:
            case arm_id::MOV:
            case arm_id::MVN:
            case arm_id::B:
            case arm_id::BL:
            case arm_id::NOP:
            case arm_id::CMNP:
            case arm_id::CMPP:
            case arm_id::TEQP:
            case arm_id::TSTP:
            case arm_id::SWI:
            case arm_id::LDM1:
            case arm_id::LDM2:
            case arm_id::LDM3:
            case arm_id::LDR:
            case arm_id::LDRB:
            case arm_id::LDRBT:
            case arm_id::LDRT:
            case arm_id::STM1: 
            case arm_id::STM2: 
            case arm_id::STR: 
            case arm_id::STRB: 
            case arm_id::STRBT:
            case arm_id::STRT: return id::specific_arch::ARMv1;
            
            // ARMv2
            case arm_id::CDP:
            case arm_id::LDC:
            case arm_id::MCR:
            case arm_id::MRC:
            case arm_id::STC:
            case arm_id::MLA:
            case arm_id::MUL:
            case arm_id::SWP: return id::specific_arch::ARMv2;
            case arm_id::SWPB: return id::specific_arch::ARMv2a;
            
            // ARMv3
            case arm_id::MRS:
            case arm_id::MSR_IMM:
            case arm_id::MSR_REG: return id::specific_arch::ARMv3;
            
            // ARMv4
            case arm_id::LDRH:
            case arm_id::LDRSB:
            case arm_id::LDRSH:
            case arm_id::STRH: return id::specific_arch::ARMv4;
            case arm_id::BX: return id::specific_arch::ARMv4T;
            
            // ARMv5
            case arm_id::BKPT:
            case arm_id::BLX1:
            case arm_id::BLX2:
            case arm_id::CLZ:
            case arm_id::CDP2:
            case arm_id::LDC2:
            case arm_id::MCR2:
            case arm_id::MRC2:
            case arm_id::STC2: return id::specific_arch::ARMv5;

            // ARMv5TE: 
            case arm_id::MCRR:
            case arm_id::MRRC:
            case arm_id::PLD:
            case arm_id::STRD:
            case arm_id::LDRD: return id::specific_arch::ARMv5TE;

            // ARMv5TExP:
            case arm_id::QADD:
            case arm_id::QDADD:
            case arm_id::QDSUB:
            case arm_id::QSUB:
            case arm_id::SMLAXY:
            case arm_id::SMLALXY:
            case arm_id::SMLAWY:
            case arm_id::SMULXY:
            case arm_id::SMULWY: return id::specific_arch::ARMv5TExP;
            default: return id::specific_arch::UNKNOWN;
        }
    }();
    
    if (instruction_arch_support == id::specific_arch::UNKNOWN) {
        switch (id) {
            // long multiplications
            case arm_id::SMLAL: 
            case arm_id::SMULL: 
            case arm_id::UMLAL: 
            case arm_id::UMULL:
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
            case arm_id::FABSS:
            case arm_id::FADDS:
            case arm_id::FCMPES:
            case arm_id::FCMPEZS:
            case arm_id::FCMPS:
            case arm_id::FCMPZS:
            case arm_id::FCPYS:
            case arm_id::FDIVS:
            case arm_id::FLDMS:
            case arm_id::FLDMX:
            case arm_id::FLDS:
            case arm_id::FMACS:
            case arm_id::FMRS:
            case arm_id::FMRX:
            case arm_id::FMSCS:
            case arm_id::FMSR:
            case arm_id::FMSTAT:
            case arm_id::FMULS:
            case arm_id::FMXR:
            case arm_id::FNEGS:
            case arm_id::FNMACS:
            case arm_id::FNMSCS:
            case arm_id::FNMULS:
            case arm_id::FSITOS:
            case arm_id::FSQRTS:
            case arm_id::FSTMS:
            case arm_id::FSTMX:
            case arm_id::FSTS:
            case arm_id::FSUBS:
            case arm_id::FTOSIS:
            case arm_id::FTOUIS:
            case arm_id::FUITOS:
                if (settings.is_vfp_single_precision_enabled == false) {
                    return true;
                }
                [[fallthrough]];

            // double precision VFP
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
            case arm_id::FLDMD:
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
            case arm_id::FSTMD:
            case arm_id::FSUBD:
            case arm_id::FTOSID:
            case arm_id::FTOUID:
            case arm_id::FUITOD: 
                // ARMv5
                if (settings.is_vfp_double_precision_enabled == false || settings.is_vfp_enabled == false) {
                    return true;
                }
                
                // double precision was introduced in VFPv2
                if (settings.vfp_version < id::vfp_version::VFPv2) {
                    return true;
                }

                // TODO (ARMv6): more conditions should be added
                return (settings.product_family != id::product_family::ARM10E);
                
            default: llarm::out::dev_error("Unknown instruction encountered during instruction support lookup");
        }
    }

    return (settings.specific_arch < instruction_arch_support);
}


bool DECODE::is_thumb_instruction_unsupported(const llarm::as::thumb_id id) const {
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
            case as::thumb_id::BKPT: 
            case as::thumb_id::BLX1: 
            case as::thumb_id::BLX2: return true;
            default: return false;
        }
    }

    return false;
}


arm_decode_struct DECODE::arm_decode(const u32 code) const {
    using namespace llarm; // for llarm::as

    const id::cond cond = reg.fetch_cond_id(code);

    if (has_condition_failed(cond)) {
        return arm_decode_struct {
            arm_id::NOP, // id
            code // code
        };
    }

    const arm_id id = as::identify_arm(code);

    if (is_arm_instruction_unsupported(id)) {
        return arm_decode_struct {
            arm_id::UNDEFINED, // id
            code // code
        };
    }

    return arm_decode_struct {
        id, // id
        code // code
    };
}


thumb_decode_struct DECODE::thumb_decode(const u16 raw_code) const {
    using namespace llarm; // for llarm::ass
    const as::thumb_id id = as::identify_thumb(raw_code);

    if (is_thumb_instruction_unsupported(id)) {
        return thumb_decode_struct {
            as::thumb_id::UNDEFINED, // id
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