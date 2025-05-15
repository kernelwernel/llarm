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
        case id::arm::ADC: return generators::arm::math::ADC(code);
        case id::arm::ADD: return generators::arm::math::ADD(code);
        case id::arm::AND: return generators::arm::logic::AND(code);
        case id::arm::B: return generators::arm::branching::B(code, PC); 
        case id::arm::BL: return generators::arm::branching::BL(code, PC); 
        case id::arm::BIC: return generators::arm::logic::BIC(code); 
        case id::arm::CDP: return generators::arm::coprocessor::CDP(code);
        case id::arm::CMN: return generators::arm::logic::CMN(code);
        case id::arm::CMP: return generators::arm::logic::CMP(code);
        case id::arm::EOR: return generators::arm::logic::EOR(code);
        case id::arm::LDC: return generators::arm::coprocessor::LDC(code);
        case id::arm::LDM1: return generators::arm::load::LDM1(code);
        case id::arm::LDM2: return generators::arm::load::LDM2(code);
        case id::arm::LDM3: return generators::arm::load::LDM3(code);
        case id::arm::LDR: return generators::arm::load::LDR(code);
        case id::arm::LDRB: return generators::arm::load::LDRB(code);
        case id::arm::LDRBT: return generators::arm::load::LDRBT(code);
        case id::arm::LDRT: return generators::arm::load::LDRT(code);
        case id::arm::MCR: return generators::arm::coprocessor::MCR(code);
        case id::arm::MLA: return generators::arm::multiply::MLA(code);
        case id::arm::MOV: return generators::arm::movement::MOV(code);
        case id::arm::MRC: return generators::arm::coprocessor::MRC(code);
        case id::arm::MRS: return generators::arm::movement::MRS(code);
        case id::arm::MSR_IMM: return generators::arm::movement::MSR_IMM(code);
        case id::arm::MSR_REG: return generators::arm::movement::MSR_REG(code);
        case id::arm::MUL: return generators::arm::multiply::MUL(code);
        case id::arm::MVN: return generators::arm::movement::MVN(code);
        case id::arm::ORR: return generators::arm::logic::ORR(code);
        case id::arm::RSB: return generators::arm::math::RSB(code);
        case id::arm::RSC: return generators::arm::math::RSC(code);
        case id::arm::SBC: return generators::arm::math::SBC(code);
        case id::arm::STC: return generators::arm::coprocessor::STC(code);
        case id::arm::STM1: return generators::arm::store::STM1(code);
        case id::arm::STM2: return generators::arm::store::STM2(code);
        case id::arm::STR: return generators::arm::store::STR(code);
        case id::arm::STRB: return generators::arm::store::STRB(code);
        case id::arm::STRBT: return generators::arm::store::STRBT(code);
        case id::arm::STRT: return generators::arm::store::STRT(code);
        case id::arm::SUB: return generators::arm::math::SUB(code);
        case id::arm::SWI: return generators::arm::misc::SWI(code);
        case id::arm::NOP: return generators::arm::misc::NOP();
        case id::arm::SWP: return generators::arm::store::SWP(code);
        case id::arm::SWPB: return generators::arm::store::SWPB(code);
        case id::arm::TEQ: return generators::arm::logic::TEQ(code);
        case id::arm::TST: return generators::arm::logic::TST(code);
        case id::arm::PSR: return generators::arm::misc::PSR(code);
        case id::arm::STRH: return generators::arm::store::STRH(code);
        case id::arm::LDRH: return generators::arm::load::LDRH(code);
        case id::arm::LDRSB: return generators::arm::load::LDRSB(code);
        case id::arm::LDRSH: return generators::arm::load::LDRSH(code);
        case id::arm::BKPT: return generators::arm::misc::BKPT(code);
        case id::arm::BLX1: return generators::arm::branching::BLX1(code, PC);
        case id::arm::BLX2: return generators::arm::branching::BLX2(code);
        case id::arm::CLZ: return generators::arm::logic::CLZ(code);
        case id::arm::BX: return generators::arm::branching::BX(code); 
        case id::arm::SMLAL: return generators::arm::multiply::SMLAL(code);
        case id::arm::SMULL: return generators::arm::multiply::SMULL(code);
        case id::arm::UMLAL: return generators::arm::multiply::UMLAL(code);
        case id::arm::UMULL: return generators::arm::multiply::UMULL(code);
        case id::arm::LDRD: return generators::arm::dsp::LDRD(code);
        case id::arm::MCRR: return generators::arm::dsp::MCRR(code);
        case id::arm::MRRC: return generators::arm::dsp::MRRC(code);
        case id::arm::PLD: return generators::arm::dsp::PLD(code);
        case id::arm::QADD: return generators::arm::dsp::QADD(code);
        case id::arm::QDADD: return generators::arm::dsp::QDADD(code);
        case id::arm::QDSUB: return generators::arm::dsp::QDSUB(code);
        case id::arm::QSUB: return generators::arm::dsp::QSUB(code);
        case id::arm::SMLA: return generators::arm::dsp::SMLA(code);
        case id::arm::SMLAW: return generators::arm::dsp::SMLAW(code);
        case id::arm::SMUL: return generators::arm::dsp::SMUL(code);
        case id::arm::SMULW: return generators::arm::dsp::SMULW(code);
        case id::arm::STRD: return generators::arm::dsp::STRD(code);
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
        case id::arm::FLDD: return generators::arm::vfp::FLDD(code);
        case id::arm::FLDMD: return generators::arm::vfp::FLDMD(code);
        case id::arm::FLDMS: return generators::arm::vfp::FLDMS(code);
        case id::arm::FLDMX: return generators::arm::vfp::FLDMX(code);
        case id::arm::FLDS: return generators::arm::vfp::FLDS(code);
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
        case id::arm::FSTD: return generators::arm::vfp::FSTD(code);
        case id::arm::FSTMD: return generators::arm::vfp::FSTMD(code);
        case id::arm::FSTMS: return generators::arm::vfp::FSTMS(code);
        case id::arm::FSTMX: return generators::arm::vfp::FSTMX(code);
        case id::arm::FSTS: return generators::arm::vfp::FSTS(code);
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



std::string disassemble::thumb(const u16 code, const u32 PC) {
    const id::thumb id = identifiers::thumb(code);

    switch (id) {
        case id::thumb::ADC: return generators::thumb::math::ADC(code);
        case id::thumb::ADD1: return generators::thumb::math::ADD1(code);
        case id::thumb::ADD2: return generators::thumb::math::ADD2(code);
        case id::thumb::ADD3: return generators::thumb::math::ADD3(code);
        case id::thumb::ADD4: return generators::thumb::math::ADD4(code);
        case id::thumb::ADD5: return generators::thumb::math::ADD5(code);
        case id::thumb::ADD6: return generators::thumb::math::ADD6(code);
        case id::thumb::ADD7: return generators::thumb::math::ADD7(code);
        case id::thumb::SBC: return generators::thumb::math::SBC(code);
        case id::thumb::SUB1: return generators::thumb::math::SUB1(code);
        case id::thumb::SUB2: return generators::thumb::math::SUB2(code);
        case id::thumb::SUB3: return generators::thumb::math::SUB3(code);
        case id::thumb::SUB4: return generators::thumb::math::SUB4(code);
        case id::thumb::MUL: return generators::thumb::math::MUL(code);
        case id::thumb::AND: return generators::thumb::logic::AND(code);
        case id::thumb::ASR1: return generators::thumb::logic::ASR1(code);
        case id::thumb::ASR2: return generators::thumb::logic::ASR2(code);
        case id::thumb::BIC: return generators::thumb::logic::BIC(code);
        case id::thumb::EOR: return generators::thumb::logic::EOR(code);
        case id::thumb::LSL1: return generators::thumb::logic::LSL1(code);
        case id::thumb::LSL2: return generators::thumb::logic::LSL2(code);
        case id::thumb::LSR1: return generators::thumb::logic::LSR1(code);
        case id::thumb::LSR2: return generators::thumb::logic::LSR2(code);
        case id::thumb::NEG: return generators::thumb::logic::NEG(code);
        case id::thumb::ORR: return generators::thumb::logic::ORR(code);
        case id::thumb::ROR: return generators::thumb::logic::ROR(code);
        case id::thumb::TST: return generators::thumb::logic::TST(code);
        case id::thumb::CMN: return generators::thumb::comparison::CMN(code);
        case id::thumb::CMP1: return generators::thumb::comparison::CMP1(code);
        case id::thumb::CMP2: return generators::thumb::comparison::CMP2(code);
        case id::thumb::CMP3: return generators::thumb::comparison::CMP3(code);
        case id::thumb::MOV1: return generators::thumb::movement::MOV1(code);
        case id::thumb::MOV2: return generators::thumb::movement::MOV2(code);
        case id::thumb::MOV3: return generators::thumb::movement::MOV3(code);
        case id::thumb::MVN: return generators::thumb::movement::MVN(code);
        case id::thumb::B1: return generators::thumb::branching::B1(code, PC);
        case id::thumb::B2: return generators::thumb::branching::B2(code, PC);
        case id::thumb::BL:
        case id::thumb::BLX1:
        case id::thumb::BLX2: return generators::thumb::branching::BLX2(code);
        case id::thumb::BX: return generators::thumb::branching::BX(code);
        case id::thumb::BKPT: return generators::thumb::misc::BKPT(code);
        case id::thumb::SWI: return generators::thumb::misc::SWI(code);
        case id::thumb::LDMIA: return generators::thumb::load::LDMIA(code);
        case id::thumb::LDR1: return generators::thumb::load::LDR1(code);
        case id::thumb::LDR2: return generators::thumb::load::LDR2(code);
        case id::thumb::LDR3: return generators::thumb::load::LDR3(code);
        case id::thumb::LDR4: return generators::thumb::load::LDR4(code);
        case id::thumb::LDRB1: return generators::thumb::load::LDRB1(code);
        case id::thumb::LDRB2: return generators::thumb::load::LDRB2(code);
        case id::thumb::LDRH1: return generators::thumb::load::LDRH1(code);
        case id::thumb::LDRH2: return generators::thumb::load::LDRH2(code);
        case id::thumb::LDRSB: return generators::thumb::load::LDRSB(code);
        case id::thumb::LDRSH: return generators::thumb::load::LDRSH(code);
        case id::thumb::POP: return generators::thumb::load::POP(code);
        case id::thumb::PUSH: return generators::thumb::store::PUSH(code);
        case id::thumb::STMIA: return generators::thumb::store::STMIA(code);
        case id::thumb::STR1: return generators::thumb::store::STR1(code);
        case id::thumb::STR2: return generators::thumb::store::STR2(code);
        case id::thumb::STR3: return generators::thumb::store::STR3(code);
        case id::thumb::STRB1: return generators::thumb::store::STRB1(code);
        case id::thumb::STRB2: return generators::thumb::store::STRB2(code);
        case id::thumb::STRH1: return generators::thumb::store::STRH1(code);
        case id::thumb::STRH2: return generators::thumb::store::STRH2(code);
        default: return "idk, todo";
    }
}