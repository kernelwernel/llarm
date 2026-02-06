#include "generate.hpp"
#include "../params.hpp"
#include "../settings.hpp"
#include "../random.hpp"

#include "generate.hpp"
#include "patterns.hpp"

#include <llarm/shared/types.hpp>

#include <llarm-asm/llarm-asm.hpp>

param_struct generate::make_params(const settings_struct settings) {
    const u8 cond = [&]() -> u8 {
        if (settings.no_cond_limitation) {
            return 0;
        } else if (settings.occasional_cond_switch) {
            if (cond_switch_count < settings.cond_switch_frequency) {
                cond_switch_count++;
                return current_cond;
            } else {
                current_cond = random::generate<u8>(28, 31);
                return current_cond;
            }
        } else if (settings.random_conds) {
            return random::generate<u8>(28, 31);
        }

        return 0;
    }();

    return param_struct {
        cond,
        settings.random_register_choice
    };
}


u32 generate::make_instruction(const settings_struct settings) {
    using namespace llarm::as; // for llarm::as

    const u8 begin = static_cast<u8>(id::arm::ADC);
    const u8 end = static_cast<u8>(id::arm::FUITOD);

    const u8 random_num = random::generate<u8>(begin, end);

    const id::arm id = static_cast<id::arm>(random_num);

    const param_struct params = make_params(settings);

   // B
   // BL
//
   // BKPT
//
   // BLX1
//
   // BLX2
//
   // BX
//
   // CDP
//
   // CLZ
//
   // CMN


    switch (id) {
        case id::arm::UNKNOWN: return 0;
        case id::arm::UNDEFINED: return 0;
        case id::arm::ADC: return patterns::logic_arithmetic(params);
        case id::arm::ADD: return patterns::logic_arithmetic(params);
        case id::arm::RSB: return patterns::logic_arithmetic(params);
        case id::arm::BIC: return patterns::logic_arithmetic(params);
        case id::arm::RSC: return patterns::logic_arithmetic(params);
        case id::arm::SBC: return patterns::logic_arithmetic(params);
        case id::arm::SUB: return patterns::logic_arithmetic(params);
        case id::arm::CMN:
        case id::arm::AND: return patterns::logic_arithmetic(params);
        case id::arm::CMP: 
        case id::arm::EOR: return patterns::logic_arithmetic(params);
        case id::arm::ORR: return patterns::logic_arithmetic(params);
        case id::arm::TEQ:
        case id::arm::TST:
        case id::arm::MOV:
        case id::arm::MVN:
        case id::arm::B:
        case id::arm::BL:
        case id::arm::NOP:
        case id::arm::PSR:
        case id::arm::SWI:
        case id::arm::LDM1:
        case id::arm::LDM2:
        case id::arm::LDM3:
        case id::arm::LDR:
        case id::arm::LDRB:
        case id::arm::LDRBT:
        case id::arm::LDRT:
        case id::arm::STM1: 
        case id::arm::STM2: 
        case id::arm::STR: 
        case id::arm::STRB: 
        case id::arm::STRBT:
        case id::arm::STRT: 
        case id::arm::CDP:
        case id::arm::LDC:
        case id::arm::MCR:
        case id::arm::MRC:
        case id::arm::STC:
        case id::arm::SWP:
        case id::arm::SWPB:
        case id::arm::MLA:
        case id::arm::MUL:
        case id::arm::SMLAL:
        case id::arm::SMULL:
        case id::arm::UMLAL:
        case id::arm::UMULL:
        case id::arm::MRS:
        case id::arm::MSR_IMM:
        case id::arm::MSR_REG:
        case id::arm::LDRH:
        case id::arm::LDRSB:
        case id::arm::LDRSH:
        case id::arm::STRH:
        case id::arm::BX:
        case id::arm::BKPT:
        case id::arm::BLX1:
        case id::arm::BLX2:
        case id::arm::CLZ:
        case id::arm::CDP2:
        case id::arm::LDC2:
        case id::arm::MCR2:
        case id::arm::MRC2:
        case id::arm::STC2:
        case id::arm::MCRR:
        case id::arm::MRRC:
        case id::arm::PLD:
        case id::arm::STRD:
        case id::arm::LDRD:
        case id::arm::QADD:
        case id::arm::QDADD:
        case id::arm::QDSUB:
        case id::arm::QSUB:
        case id::arm::SMLAXY:
        case id::arm::SMLALXY:
        case id::arm::SMLAWY:
        case id::arm::SMULXY:
        case id::arm::SMULWY:
        case id::arm::FABSS:
        case id::arm::FADDS:
        case id::arm::FCMPES:
        case id::arm::FCMPEZS:
        case id::arm::FCMPS:
        case id::arm::FCMPZS:
        case id::arm::FCPYS:
        case id::arm::FDIVS:
        case id::arm::FLDMS:
        case id::arm::FLDMX:
        case id::arm::FLDS:
        case id::arm::FMACS:
        case id::arm::FMRS:
        case id::arm::FMRX:
        case id::arm::FMSCS:
        case id::arm::FMSR:
        case id::arm::FMSTAT:
        case id::arm::FMULS:
        case id::arm::FMXR:
        case id::arm::FNEGS:
        case id::arm::FNMACS:
        case id::arm::FNMSCS:
        case id::arm::FNMULS:
        case id::arm::FSITOS:
        case id::arm::FSQRTS:
        case id::arm::FSTMS:
        case id::arm::FSTMX:
        case id::arm::FSTS:
        case id::arm::FSUBS:
        case id::arm::FTOSIS:
        case id::arm::FTOUIS:
        case id::arm::FUITOS:
        case id::arm::FABSD:
        case id::arm::FADDD:
        case id::arm::FCMPD:
        case id::arm::FCMPED:
        case id::arm::FCMPEZD:
        case id::arm::FCMPZD:
        case id::arm::FCPYD:
        case id::arm::FCVTDS:
        case id::arm::FCVTSD:
        case id::arm::FDIVD:
        case id::arm::FLDD:
        case id::arm::FLDMD:
        case id::arm::FMACD:
        case id::arm::FMDHR:
        case id::arm::FMDLR:
        case id::arm::FMRDL:
        case id::arm::FMRDH:
        case id::arm::FMSCD:
        case id::arm::FMULD:
        case id::arm::FNEGD:
        case id::arm::FNMACD:
        case id::arm::FNMSCD:
        case id::arm::FNMULD:
        case id::arm::FSITOD:
        case id::arm::FSQRTD:
        case id::arm::FSTD:
        case id::arm::FSTMD:
        case id::arm::FSUBD:
        case id::arm::FTOSID:
        case id::arm::FTOUID:
        case id::arm::FUITOD: return 0; // tmp
    }
}


std::vector<u32> generate::make_blueprint() {
    std::vector<u32> tmp = {};

    //for (settings.binary_size) {
//
    //}

    return tmp;
}