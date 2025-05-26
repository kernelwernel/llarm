#include "disassemble.hpp"
#include "../identifiers/identifiers.hpp"
#include "../instruction_id.hpp"
#include "generators/generators.hpp"
#include "generators/util.hpp"
#include "../settings.hpp"

#include "shared/types.hpp"

#include <string>

using namespace internal;

std::string disassemble::thumb_generate(const u16 code, const u32 PC, const settings settings) {
    const id::thumb id = identifiers::thumb(code);

    switch (id) {
        case id::thumb::ADC: return generators::thumb::math::ADC(code, settings);
        case id::thumb::ADD1: return generators::thumb::math::ADD1(code, settings);
        case id::thumb::ADD2: return generators::thumb::math::ADD2(code, settings);
        case id::thumb::ADD3: return generators::thumb::math::ADD3(code, settings);
        case id::thumb::ADD4: return generators::thumb::math::ADD4(code, settings);
        case id::thumb::ADD5: return generators::thumb::math::ADD5(code, settings);
        case id::thumb::ADD6: return generators::thumb::math::ADD6(code, settings);
        case id::thumb::ADD7: return generators::thumb::math::ADD7(code, settings);
        case id::thumb::SBC: return generators::thumb::math::SBC(code, settings);
        case id::thumb::SUB1: return generators::thumb::math::SUB1(code, settings);
        case id::thumb::SUB2: return generators::thumb::math::SUB2(code, settings);
        case id::thumb::SUB3: return generators::thumb::math::SUB3(code, settings);
        case id::thumb::SUB4: return generators::thumb::math::SUB4(code, settings);
        case id::thumb::MUL: return generators::thumb::math::MUL(code, settings);
        case id::thumb::AND: return generators::thumb::logic::AND(code, settings);
        case id::thumb::ASR1: return generators::thumb::logic::ASR1(code, settings);
        case id::thumb::ASR2: return generators::thumb::logic::ASR2(code, settings);
        case id::thumb::BIC: return generators::thumb::logic::BIC(code, settings);
        case id::thumb::EOR: return generators::thumb::logic::EOR(code, settings);
        case id::thumb::LSL1: return generators::thumb::logic::LSL1(code, settings);
        case id::thumb::LSL2: return generators::thumb::logic::LSL2(code, settings);
        case id::thumb::LSR1: return generators::thumb::logic::LSR1(code, settings);
        case id::thumb::LSR2: return generators::thumb::logic::LSR2(code, settings);
        case id::thumb::NEG: return generators::thumb::logic::NEG(code, settings);
        case id::thumb::ORR: return generators::thumb::logic::ORR(code, settings);
        case id::thumb::ROR: return generators::thumb::logic::ROR(code, settings);
        case id::thumb::TST: return generators::thumb::logic::TST(code, settings);
        case id::thumb::CMN: return generators::thumb::comparison::CMN(code, settings);
        case id::thumb::CMP1: return generators::thumb::comparison::CMP1(code, settings);
        case id::thumb::CMP2: return generators::thumb::comparison::CMP2(code, settings);
        case id::thumb::CMP3: return generators::thumb::comparison::CMP3(code, settings);
        case id::thumb::MOV1: return generators::thumb::movement::MOV1(code, settings);
        case id::thumb::MOV2: return generators::thumb::movement::MOV2(code, settings);
        case id::thumb::MOV3: return generators::thumb::movement::MOV3(code, settings);
        case id::thumb::MVN: return generators::thumb::movement::MVN(code, settings);
        case id::thumb::B1: return generators::thumb::branching::B1(code, PC, settings);
        case id::thumb::B2: return generators::thumb::branching::B2(code, PC, settings);
        case id::thumb::BL:
        case id::thumb::BLX1:
        case id::thumb::BLX2: return generators::thumb::branching::BLX2(code, settings);
        case id::thumb::BX: return generators::thumb::branching::BX(code, settings);
        case id::thumb::BKPT: return generators::thumb::misc::BKPT(code, settings);
        case id::thumb::SWI: return generators::thumb::misc::SWI(code, settings);
        case id::thumb::LDMIA: return generators::thumb::load::LDMIA(code, settings);
        case id::thumb::LDR1: return generators::thumb::load::LDR1(code, settings);
        case id::thumb::LDR2: return generators::thumb::load::LDR2(code, settings);
        case id::thumb::LDR3: return generators::thumb::load::LDR3(code, settings);
        case id::thumb::LDR4: return generators::thumb::load::LDR4(code, settings);
        case id::thumb::LDRB1: return generators::thumb::load::LDRB1(code, settings);
        case id::thumb::LDRB2: return generators::thumb::load::LDRB2(code, settings);
        case id::thumb::LDRH1: return generators::thumb::load::LDRH1(code, settings);
        case id::thumb::LDRH2: return generators::thumb::load::LDRH2(code, settings);
        case id::thumb::LDRSB: return generators::thumb::load::LDRSB(code, settings);
        case id::thumb::LDRSH: return generators::thumb::load::LDRSH(code, settings);
        case id::thumb::POP: return generators::thumb::load::POP(code, settings);
        case id::thumb::PUSH: return generators::thumb::store::PUSH(code, settings);
        case id::thumb::STMIA: return generators::thumb::store::STMIA(code, settings);
        case id::thumb::STR1: return generators::thumb::store::STR1(code, settings);
        case id::thumb::STR2: return generators::thumb::store::STR2(code, settings);
        case id::thumb::STR3: return generators::thumb::store::STR3(code, settings);
        case id::thumb::STRB1: return generators::thumb::store::STRB1(code, settings);
        case id::thumb::STRB2: return generators::thumb::store::STRB2(code, settings);
        case id::thumb::STRH1: return generators::thumb::store::STRH1(code, settings);
        case id::thumb::STRH2: return generators::thumb::store::STRH2(code, settings);
        default: return "idk, todo";
    }
}


std::string disassemble::arm_generate(const u32 code, const u32 PC, const settings settings) {
    const id::arm id = identifiers::arm(code);

    switch (id) {
        case id::arm::ADC: return generators::arm::math::ADC(code, settings);
        case id::arm::ADD: return generators::arm::math::ADD(code, settings);
        case id::arm::AND: return generators::arm::logic::AND(code, settings);
        case id::arm::B: return generators::arm::branching::B(code, PC, settings); 
        case id::arm::BL: return generators::arm::branching::BL(code, PC, settings); 
        case id::arm::BIC: return generators::arm::logic::BIC(code, settings); 
        case id::arm::CDP: return generators::arm::coprocessor::CDP(code, settings);
        case id::arm::CMN: return generators::arm::logic::CMN(code, settings);
        case id::arm::CMP: return generators::arm::logic::CMP(code, settings);
        case id::arm::EOR: return generators::arm::logic::EOR(code, settings);
        case id::arm::LDC: return generators::arm::coprocessor::LDC(code, settings);
        case id::arm::LDM1: return generators::arm::load::LDM1(code, settings);
        case id::arm::LDM2: return generators::arm::load::LDM2(code, settings);
        case id::arm::LDM3: return generators::arm::load::LDM3(code, settings);
        case id::arm::LDR: return generators::arm::load::LDR(code, settings);
        case id::arm::LDRB: return generators::arm::load::LDRB(code, settings);
        case id::arm::LDRBT: return generators::arm::load::LDRBT(code, settings);
        case id::arm::LDRT: return generators::arm::load::LDRT(code, settings);
        case id::arm::MCR: return generators::arm::coprocessor::MCR(code, settings);
        case id::arm::MLA: return generators::arm::multiply::MLA(code, settings);
        case id::arm::MOV: return generators::arm::movement::MOV(code, settings);
        case id::arm::MRC: return generators::arm::coprocessor::MRC(code, settings);
        case id::arm::MRS: return generators::arm::movement::MRS(code, settings);
        case id::arm::MSR_IMM: return generators::arm::movement::MSR_IMM(code, settings);
        case id::arm::MSR_REG: return generators::arm::movement::MSR_REG(code, settings);
        case id::arm::MUL: return generators::arm::multiply::MUL(code, settings);
        case id::arm::MVN: return generators::arm::movement::MVN(code, settings);
        case id::arm::ORR: return generators::arm::logic::ORR(code, settings);
        case id::arm::RSB: return generators::arm::math::RSB(code, settings);
        case id::arm::RSC: return generators::arm::math::RSC(code, settings);
        case id::arm::SBC: return generators::arm::math::SBC(code, settings);
        case id::arm::STC: return generators::arm::coprocessor::STC(code, settings);
        case id::arm::STM1: return generators::arm::store::STM1(code, settings);
        case id::arm::STM2: return generators::arm::store::STM2(code, settings);
        case id::arm::STR: return generators::arm::store::STR(code, settings);
        case id::arm::STRB: return generators::arm::store::STRB(code, settings);
        case id::arm::STRBT: return generators::arm::store::STRBT(code, settings);
        case id::arm::STRT: return generators::arm::store::STRT(code, settings);
        case id::arm::SUB: return generators::arm::math::SUB(code, settings);
        case id::arm::SWI: return generators::arm::misc::SWI(code, settings);
        case id::arm::NOP: return generators::arm::misc::NOP();
        case id::arm::SWP: return generators::arm::store::SWP(code, settings);
        case id::arm::SWPB: return generators::arm::store::SWPB(code, settings);
        case id::arm::TEQ: return generators::arm::logic::TEQ(code, settings);
        case id::arm::TST: return generators::arm::logic::TST(code, settings);
        case id::arm::PSR: return generators::arm::misc::PSR(code, settings);
        case id::arm::STRH: return generators::arm::store::STRH(code, settings);
        case id::arm::LDRH: return generators::arm::load::LDRH(code, settings);
        case id::arm::LDRSB: return generators::arm::load::LDRSB(code, settings);
        case id::arm::LDRSH: return generators::arm::load::LDRSH(code, settings);
        case id::arm::BKPT: return generators::arm::misc::BKPT(code, settings);
        case id::arm::BLX1: return generators::arm::branching::BLX1(code, PC, settings);
        case id::arm::BLX2: return generators::arm::branching::BLX2(code, settings);
        case id::arm::CLZ: return generators::arm::logic::CLZ(code, settings);
        case id::arm::BX: return generators::arm::branching::BX(code, settings); 
        case id::arm::SMLAL: return generators::arm::multiply::SMLAL(code, settings);
        case id::arm::SMULL: return generators::arm::multiply::SMULL(code, settings);
        case id::arm::UMLAL: return generators::arm::multiply::UMLAL(code, settings);
        case id::arm::UMULL: return generators::arm::multiply::UMULL(code, settings);
        case id::arm::LDRD: return generators::arm::dsp::LDRD(code, settings);
        case id::arm::MCRR: return generators::arm::dsp::MCRR(code, settings);
        case id::arm::MRRC: return generators::arm::dsp::MRRC(code, settings);
        case id::arm::PLD: return generators::arm::dsp::PLD(code, settings);
        case id::arm::QADD: return generators::arm::dsp::QADD(code, settings);
        case id::arm::QDADD: return generators::arm::dsp::QDADD(code, settings);
        case id::arm::QDSUB: return generators::arm::dsp::QDSUB(code, settings);
        case id::arm::QSUB: return generators::arm::dsp::QSUB(code, settings);
        case id::arm::SMLA: return generators::arm::dsp::SMLA(code, settings);
        case id::arm::SMLAW: return generators::arm::dsp::SMLAW(code, settings);
        case id::arm::SMUL: return generators::arm::dsp::SMUL(code, settings);
        case id::arm::SMULW: return generators::arm::dsp::SMULW(code, settings);
        case id::arm::STRD: return generators::arm::dsp::STRD(code, settings);
        case id::arm::FABSD: return generators::arm::vfp::FABSD(code, settings);
        case id::arm::FABSS: return generators::arm::vfp::FABSS(code, settings);
        case id::arm::FADDD: return generators::arm::vfp::FADDD(code, settings);
        case id::arm::FADDS: return generators::arm::vfp::FADDS(code, settings);
        case id::arm::FCMPD: return generators::arm::vfp::FCMPD(code, settings);
        case id::arm::FCMPED: return generators::arm::vfp::FCMPED(code, settings);
        case id::arm::FCMPES: return generators::arm::vfp::FCMPES(code, settings);
        case id::arm::FCMPEZD: return generators::arm::vfp::FCMPEZD(code, settings);
        case id::arm::FCMPEZS: return generators::arm::vfp::FCMPEZS(code, settings);
        case id::arm::FCMPS: return generators::arm::vfp::FCMPS(code, settings);
        case id::arm::FCMPZD: return generators::arm::vfp::FCMPZD(code, settings);
        case id::arm::FCMPZS: return generators::arm::vfp::FCMPZS(code, settings);
        case id::arm::FCPYD: return generators::arm::vfp::FCPYD(code, settings);
        case id::arm::FCPYS: return generators::arm::vfp::FCPYS(code, settings);
        case id::arm::FCVTDS: return generators::arm::vfp::FCVTDS(code, settings);
        case id::arm::FCVTSD: return generators::arm::vfp::FCVTSD(code, settings);
        case id::arm::FDIVD: return generators::arm::vfp::FDIVD(code, settings);
        case id::arm::FDIVS: return generators::arm::vfp::FDIVS(code, settings);
        case id::arm::FLDD: return generators::arm::vfp::FLDD(code, settings);
        case id::arm::FLDMD: return generators::arm::vfp::FLDMD(code, settings);
        case id::arm::FLDMS: return generators::arm::vfp::FLDMS(code, settings);
        case id::arm::FLDMX: return generators::arm::vfp::FLDMX(code, settings);
        case id::arm::FLDS: return generators::arm::vfp::FLDS(code, settings);
        case id::arm::FMACD: return generators::arm::vfp::FMACD(code, settings);
        case id::arm::FMACS: return generators::arm::vfp::FMACS(code, settings);
        case id::arm::FMDHR: return generators::arm::vfp::FMDHR(code, settings);
        case id::arm::FMDLR: return generators::arm::vfp::FMDLR(code, settings);
        case id::arm::FMRDH: return generators::arm::vfp::FMRDH(code, settings);
        case id::arm::FMRDL: return generators::arm::vfp::FMRDL(code, settings);
        case id::arm::FMRS: return generators::arm::vfp::FMRS(code, settings);
        case id::arm::FMRX: return generators::arm::vfp::FMRX(code, settings);
        case id::arm::FMSCD: return generators::arm::vfp::FMSCD(code, settings);
        case id::arm::FMSCS: return generators::arm::vfp::FMSCS(code, settings);
        case id::arm::FMSR: return generators::arm::vfp::FMSR(code, settings);
        case id::arm::FMSTAT: return generators::arm::vfp::FMSTAT(code, settings);
        case id::arm::FMULD: return generators::arm::vfp::FMULD(code, settings);
        case id::arm::FMULS: return generators::arm::vfp::FMULS(code, settings);
        case id::arm::FMXR: return generators::arm::vfp::FMXR(code, settings);
        case id::arm::FNEGD: return generators::arm::vfp::FNEGD(code, settings);
        case id::arm::FNEGS: return generators::arm::vfp::FNEGS(code, settings);
        case id::arm::FNMACD: return generators::arm::vfp::FNMACD(code, settings);
        case id::arm::FNMACS: return generators::arm::vfp::FNMACS(code, settings);
        case id::arm::FNMSCD: return generators::arm::vfp::FNMSCD(code, settings);
        case id::arm::FNMSCS: return generators::arm::vfp::FNMSCS(code, settings);
        case id::arm::FNMULD: return generators::arm::vfp::FNMULD(code, settings);
        case id::arm::FNMULS: return generators::arm::vfp::FNMULS(code, settings);
        case id::arm::FSITOD: return generators::arm::vfp::FSITOD(code, settings);
        case id::arm::FSITOS: return generators::arm::vfp::FSITOS(code, settings);
        case id::arm::FSQRTD: return generators::arm::vfp::FSQRTD(code, settings);
        case id::arm::FSQRTS: return generators::arm::vfp::FSQRTS(code, settings);
        case id::arm::FSTD: return generators::arm::vfp::FSTD(code, settings);
        case id::arm::FSTMD: return generators::arm::vfp::FSTMD(code, settings);
        case id::arm::FSTMS: return generators::arm::vfp::FSTMS(code, settings);
        case id::arm::FSTMX: return generators::arm::vfp::FSTMX(code, settings);
        case id::arm::FSTS: return generators::arm::vfp::FSTS(code, settings);
        case id::arm::FSUBD: return generators::arm::vfp::FSUBD(code, settings);
        case id::arm::FSUBS: return generators::arm::vfp::FSUBS(code, settings);
        case id::arm::FTOSID: return generators::arm::vfp::FTOSID(code, settings);
        case id::arm::FTOSIS: return generators::arm::vfp::FTOSIS(code, settings);
        case id::arm::FTOUID: return generators::arm::vfp::FTOUID(code, settings);
        case id::arm::FTOUIS: return generators::arm::vfp::FTOUIS(code, settings);
        case id::arm::FUITOD: return generators::arm::vfp::FUITOD(code, settings);
        case id::arm::FUITOS: return generators::arm::vfp::FUITOS(code, settings); 
        default: return "idk, todo";
    }
}






std::string disassemble::arm(const u32 code, const u32 PC, const settings settings) {
    std::string instruction = arm_generate(code, PC, settings);

    if (settings.capitals == false) {
        util::to_lower(instruction);
    }

    return instruction;
}



std::string disassemble::thumb(const u16 code, const u32 PC, const settings settings) {
    std::string instruction = thumb_generate(code, PC, settings);

    if (settings.capitals == false) {
        util::to_lower(instruction);
    }

    return instruction;
}