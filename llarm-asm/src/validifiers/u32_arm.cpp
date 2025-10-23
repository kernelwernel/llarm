#include "llarm-asm/src/shifter_id.hpp"
#include "validifier.hpp"

#include "../identifiers/u32_arm.hpp"
#include "../identifiers/u32_shifters.hpp"

#include "shared/types.hpp"

using namespace internal;

bool validifier::is_arm_instruction_valid(const u32 code) {
    const id::arm id = u32_arm::arm(code);

    auto check_shifter = [=](const shifter_category category) -> bool {
        const shifter_enum shifter = u32_shifters::identify_shifter(category, code);

        return (shifter != shifter_enum::UNKNOWN);
    };

    switch (id) {
        case id::arm::UNKNOWN: return false;
        case id::arm::UNDEFINED: return false;
        case id::arm::NOP: return false;
        case id::arm::ADC: return check_shifter(shifter_category::DATA);
        case id::arm::ADD: return check_shifter(shifter_category::DATA);
        case id::arm::RSB: return check_shifter(shifter_category::DATA);
        case id::arm::BIC: return check_shifter(shifter_category::DATA);
        case id::arm::RSC: return check_shifter(shifter_category::DATA);
        case id::arm::SBC: return check_shifter(shifter_category::DATA);
        case id::arm::SUB: return check_shifter(shifter_category::DATA);
        case id::arm::CMN: return check_shifter(shifter_category::DATA);
        case id::arm::AND: return check_shifter(shifter_category::DATA);
        case id::arm::CMP: return check_shifter(shifter_category::DATA);
        case id::arm::EOR: return check_shifter(shifter_category::DATA);
        case id::arm::ORR: return check_shifter(shifter_category::DATA);
        case id::arm::TEQ: return check_shifter(shifter_category::DATA);
        case id::arm::TST: return check_shifter(shifter_category::DATA);
        case id::arm::MOV: return check_shifter(shifter_category::DATA);
        case id::arm::MVN: return check_shifter(shifter_category::DATA);
        case id::arm::CMNP: return check_shifter(shifter_category::DATA);
        case id::arm::CMPP: return check_shifter(shifter_category::DATA);
        case id::arm::TEQP: return check_shifter(shifter_category::DATA);
        case id::arm::TSTP: return check_shifter(shifter_category::DATA);
        case id::arm::LDR: return check_shifter(shifter_category::LS);
        case id::arm::LDRB: return check_shifter(shifter_category::LS);
        case id::arm::LDRBT: return check_shifter(shifter_category::LS);
        case id::arm::LDRT: return check_shifter(shifter_category::LS);
        case id::arm::STR: return check_shifter(shifter_category::LS);
        case id::arm::STRB: return check_shifter(shifter_category::LS);
        case id::arm::STRBT: return check_shifter(shifter_category::LS);
        case id::arm::STRT: return check_shifter(shifter_category::LS);
        case id::arm::LDRH: return check_shifter(shifter_category::LS_MISC);
        case id::arm::LDRSB: return check_shifter(shifter_category::LS_MISC);
        case id::arm::LDRSH: return check_shifter(shifter_category::LS_MISC);
        case id::arm::STRH: return check_shifter(shifter_category::LS_MISC);
        case id::arm::LDM1: return check_shifter(shifter_category::LS_MUL);
        case id::arm::LDM2: return check_shifter(shifter_category::LS_MUL);
        case id::arm::LDM3: return check_shifter(shifter_category::LS_MUL);
        case id::arm::STM1: return check_shifter(shifter_category::LS_MUL);
        case id::arm::STM2: return check_shifter(shifter_category::LS_MUL);
        case id::arm::LDC: return check_shifter(shifter_category::LS_COPROC);
        case id::arm::STC: return check_shifter(shifter_category::LS_COPROC);
        case id::arm::LDC2: return check_shifter(shifter_category::LS_COPROC);
        case id::arm::STC2: return check_shifter(shifter_category::LS_COPROC);
        case id::arm::B: return true;
        case id::arm::BL: return true;
        case id::arm::SWI: return true;
        case id::arm::CDP: return true;
        case id::arm::MCR: return true;
        case id::arm::MRC: return true;
        case id::arm::SWP: return true;
        case id::arm::SWPB: return true;
        case id::arm::MLA: return true;
        case id::arm::MUL: return true;
        case id::arm::SMLAL: return true; 
        case id::arm::SMULL: return true;
        case id::arm::UMLAL: return true;
        case id::arm::UMULL: return true;
        case id::arm::MRS: return true;
        case id::arm::MSR_IMM: return true;
        case id::arm::MSR_REG: return true;
        case id::arm::BX: return true;
        case id::arm::BKPT: return true;
        case id::arm::BLX1: return true;
        case id::arm::BLX2: return true;
        case id::arm::CLZ: return true;
        case id::arm::CDP2: return true;
        case id::arm::MCR2: return true;
        case id::arm::MRC2: return true;
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
        case id::arm::FUITOD:
    }
}