#include "generate.hpp"
#include "../params.hpp"
#include "../settings.hpp"

#include "generate.hpp"
#include "llarm/shared/util.hpp"
#include "patterns.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/random.hpp>

#include <llarm/llarm-asm.hpp>

param_struct generate::make_params(const settings_struct settings, llarm::random& rand) {
    const u8 cond = [&]() -> u8 {
        if (settings.no_cond_limitation) {
            return 0;
        } else if (settings.occasional_cond_switch) {
            if (cond_switch_count < settings.cond_switch_frequency) {
                cond_switch_count++;
                return current_cond;
            } else {
                current_cond = static_cast<u8>(rand.generate_index_range(28, 31));
                return current_cond;
            }
        } else if (settings.random_conds) {
            return static_cast<u8>(rand.generate_index_range(28, 31));
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

    llarm::random rand;

    if (settings.randomised_bin) {
        return llarm::util::bit_range(rand.generate(), 0, 31);
    }

    const u8 begin = static_cast<u8>(arm_id::ADC);
    const u8 end = static_cast<u8>(arm_id::FUITOD);

    const u8 random_id = static_cast<u8>(rand.generate_range(begin, end));

    const arm_id id = static_cast<arm_id>(random_id);

    const param_struct params = make_params(settings, rand);

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
        case arm_id::UNKNOWN: return 0;
        case arm_id::UNDEFINED: return 0;
        case arm_id::ADC: return patterns::logic_arithmetic(params);
        case arm_id::ADD: return patterns::logic_arithmetic(params);
        case arm_id::RSB: return patterns::logic_arithmetic(params);
        case arm_id::BIC: return patterns::logic_arithmetic(params);
        case arm_id::RSC: return patterns::logic_arithmetic(params);
        case arm_id::SBC: return patterns::logic_arithmetic(params);
        case arm_id::SUB: return patterns::logic_arithmetic(params);
        case arm_id::CMN:
        case arm_id::AND: return patterns::logic_arithmetic(params);
        case arm_id::CMP: 
        case arm_id::EOR: return patterns::logic_arithmetic(params);
        case arm_id::ORR: return patterns::logic_arithmetic(params);
        case arm_id::TEQ:
        case arm_id::TST:
        case arm_id::MOV:
        case arm_id::MVN:
        case arm_id::CMNP:
        case arm_id::CMPP:
        case arm_id::TEQP:
        case arm_id::TSTP:
        case arm_id::B:
        case arm_id::BL:
        case arm_id::NOP:
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
        case arm_id::STRT: 
        case arm_id::CDP:
        case arm_id::LDC:
        case arm_id::MCR:
        case arm_id::MRC:
        case arm_id::STC:
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
        case arm_id::LDRH:
        case arm_id::LDRSB:
        case arm_id::LDRSH:
        case arm_id::STRH:
        case arm_id::BX:
        case arm_id::BKPT:
        case arm_id::BLX1:
        case arm_id::BLX2:
        case arm_id::CLZ:
        case arm_id::CDP2:
        case arm_id::LDC2:
        case arm_id::MCR2:
        case arm_id::MRC2:
        case arm_id::STC2:
        case arm_id::MCRR:
        case arm_id::MRRC:
        case arm_id::PLD:
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
        case arm_id::FUITOD: return 0; // tmp
                break;
        }
}


std::vector<u32> generate::make_blueprint() {
    std::vector<u32> tmp = {};

    //for (settings.binary_size) {
//
    //}

    return tmp;
}