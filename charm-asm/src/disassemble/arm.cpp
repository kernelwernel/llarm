#include "disassemble.hpp"
#include "../identifiers/identifiers.hpp"
#include "../instruction_id.hpp"
#include "generators/generators.hpp"

#include "shared/types.hpp"

#include <string>

using namespace internal;

std::string disassemble::arm(const u32 code, const u32 PC) {
    const id::arm id = identifiers::arm(code);

    switch (id) {
        case id::arm::ADC:
        case id::arm::ADD:
        case id::arm::AND:
        case id::arm::UNDEFINED:
        case id::arm::NOP:
        case id::arm::B:
        case id::arm::BL:
        case id::arm::BIC:
        case id::arm::CDP:
        case id::arm::CMN:
        case id::arm::CMP:
        case id::arm::EOR:
        case id::arm::LDC:
        case id::arm::LDM1:
        case id::arm::LDM2:
        case id::arm::LDM3:
        case id::arm::LDR:
        case id::arm::LDRB:
        case id::arm::LDRBT:
        case id::arm::LDRT:
        case id::arm::MCR:
        case id::arm::MLA:
        case id::arm::MOV:
        case id::arm::MRC:
        case id::arm::MRS:
        case id::arm::MSR_IMM:
        case id::arm::MSR_REG:
        case id::arm::MUL:
        case id::arm::MVN:
        case id::arm::ORR:
        case id::arm::RSB:
        case id::arm::RSC:
        case id::arm::SBC:
        case id::arm::STC:
        case id::arm::STM1:
        case id::arm::STM2:
        case id::arm::STR:
        case id::arm::STRB:
        case id::arm::STRBT:
        case id::arm::STRT:
        case id::arm::SUB:
        case id::arm::SWI:
        case id::arm::SWP:
        case id::arm::SWPB:
        case id::arm::TEQ:
        case id::arm::TST:
        case id::arm::PSR:
        case id::arm::STRH:
        case id::arm::LDRH:
        case id::arm::LDRSB:
        case id::arm::LDRSH:
        case id::arm::BKPT:
        case id::arm::BLX1:
        case id::arm::BLX2:
        case id::arm::CLZ:
        case id::arm::BX:
        case id::arm::SMLAL:
        case id::arm::SMULL:
        case id::arm::UMLAL:
        case id::arm::UMULL:
        case id::arm::LDRD:
        case id::arm::MCRR:
        case id::arm::MRRC:
        case id::arm::PLD:
        case id::arm::QADD:
        case id::arm::QDADD:
        case id::arm::QDSUB:
        case id::arm::QSUB:
        case id::arm::SMLA:
        case id::arm::SMLAW:
        case id::arm::SMUL:
        case id::arm::SMULW:
        case id::arm::STRD:
        case id::arm::FABSD: return generators::arm::vfp::FABSD(code);
        case id::arm::FABSS: return generators::arm::vfp::FABSS(code);
        case id::arm::FADDD: return generators::arm::vfp::FADDD(code);
        case id::arm::FADDS: return generators::arm::vfp::FADDS(code);
        case id::arm::FCMPD: return generators::arm::vfp::FCMPD(code);
        case id::arm::FCMPED: return generators::arm::vfp::FCMPED(code);
        case id::arm::FCMPES: return generators::arm::vfp::FCMPES(code);
        case id::arm::FCMPEZD: return generators::arm::vfp::FCMPEZD(code);
        case id::arm::FCMPEZS: return generators::arm::vfp::FCMPEZS(code);
        case id::arm::FCMPS: return generators::arm::vfp::FCMPS(code);
        case id::arm::FCMPZD: return generators::arm::vfp::FCMPZD(code);
        case id::arm::FCMPZS: return generators::arm::vfp::FCMPZS(code);
        case id::arm::FCPYD: return generators::arm::vfp::FCPYD(code);
        case id::arm::FCPYS: return generators::arm::vfp::FCPYS(code);
        case id::arm::FCVTDS: return generators::arm::vfp::FCVTDS(code);
        case id::arm::FCVTSD: return generators::arm::vfp::FCVTSD(code);
        case id::arm::FDIVD: return generators::arm::vfp::FDIVD(code);
        case id::arm::FDIVS: return generators::arm::vfp::FDIVS(code);
        case id::arm::FLDD: // TODO
        case id::arm::FLDMD: // TODO
        case id::arm::FLDMS: // TODO
        case id::arm::FLDMX: // TODO
        case id::arm::FLDS: // TODO
        case id::arm::FMACD: return generators::arm::vfp::FMACD(code);
        case id::arm::FMACS: return generators::arm::vfp::FMACS(code);
        case id::arm::FMDHR: return generators::arm::vfp::FMDHR(code);
        case id::arm::FMDLR: return generators::arm::vfp::FMDLR(code);
        case id::arm::FMRDH: return generators::arm::vfp::FMRDH(code);
        case id::arm::FMRDL: return generators::arm::vfp::FMRDL(code);
        case id::arm::FMRS: return generators::arm::vfp::FMRS(code);
        case id::arm::FMRX: return generators::arm::vfp::FMRX(code);
        case id::arm::FMSCD: return generators::arm::vfp::FMSCD(code);
        case id::arm::FMSCS: return generators::arm::vfp::FMSCS(code);
        case id::arm::FMSR: return generators::arm::vfp::FMSR(code);
        case id::arm::FMSTAT: return generators::arm::vfp::FMSTAT(code);
        case id::arm::FMULD: return generators::arm::vfp::FMULD(code);
        case id::arm::FMULS: return generators::arm::vfp::FMULS(code);
        case id::arm::FMXR: return generators::arm::vfp::FMXR(code);
        case id::arm::FNEGD: return generators::arm::vfp::FNEGD(code);
        case id::arm::FNEGS: return generators::arm::vfp::FNEGS(code);
        case id::arm::FNMACD: return generators::arm::vfp::FNMACD(code);
        case id::arm::FNMACS: return generators::arm::vfp::FNMACS(code);
        case id::arm::FNMSCD: return generators::arm::vfp::FNMSCD(code);
        case id::arm::FNMSCS: return generators::arm::vfp::FNMSCS(code);
        case id::arm::FNMULD: return generators::arm::vfp::FNMULD(code);
        case id::arm::FNMULS: return generators::arm::vfp::FNMULS(code);
        case id::arm::FSITOD: return generators::arm::vfp::FSITOD(code);
        case id::arm::FSITOS: return generators::arm::vfp::FSITOS(code);
        case id::arm::FSQRTD: return generators::arm::vfp::FSQRTD(code);
        case id::arm::FSQRTS: return generators::arm::vfp::FSQRTS(code);
        case id::arm::FSTD: // TODO
        case id::arm::FSTMD: // TODO
        case id::arm::FSTMS: // TODO
        case id::arm::FSTMX: // TODO
        case id::arm::FSTS: // TODO
        case id::arm::FSUBD: return generators::arm::vfp::FSUBD(code);
        case id::arm::FSUBS: return generators::arm::vfp::FSUBS(code);
        case id::arm::FTOSID: return generators::arm::vfp::FTOSID(code);
        case id::arm::FTOSIS: return generators::arm::vfp::FTOSIS(code);
        case id::arm::FTOUID: return generators::arm::vfp::FTOUID(code);
        case id::arm::FTOUIS: return generators::arm::vfp::FTOUIS(code);
        case id::arm::FUITOD: return generators::arm::vfp::FUITOD(code);
        case id::arm::FUITOS: return generators::arm::vfp::FUITOS(code); 
        default: return "idk, todo";
    }
}