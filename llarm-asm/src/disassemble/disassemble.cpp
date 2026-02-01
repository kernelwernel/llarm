#include "disassemble.hpp"
#include "../identifiers/u16_thumb.hpp"
#include "../identifiers/u32_arm.hpp"
#include "../id/instruction_id.hpp"
#include "generators/generators.hpp"
#include "../settings.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"
#include "shared/out.hpp"

#include <string>

using namespace internal;

std::string disassemble::thumb_generate(const u16 code, const u32 PC, const settings settings) {
    const thumb_id id = ident::u16_thumb::thumb(code);

    switch (id) {
        case thumb_id::ADC: return generators::thumb::math::ADC(code, settings);
        case thumb_id::ADD1: return generators::thumb::math::ADD1(code, settings);
        case thumb_id::ADD2: return generators::thumb::math::ADD2(code, settings);
        case thumb_id::ADD3: return generators::thumb::math::ADD3(code, settings);
        case thumb_id::ADD4: return generators::thumb::math::ADD4(code, settings);
        case thumb_id::ADD5: return generators::thumb::math::ADD5(code, settings);
        case thumb_id::ADD6: return generators::thumb::math::ADD6(code, settings);
        case thumb_id::ADD7: return generators::thumb::math::ADD7(code, settings);
        case thumb_id::SBC: return generators::thumb::math::SBC(code, settings);
        case thumb_id::SUB1: return generators::thumb::math::SUB1(code, settings);
        case thumb_id::SUB2: return generators::thumb::math::SUB2(code, settings);
        case thumb_id::SUB3: return generators::thumb::math::SUB3(code, settings);
        case thumb_id::SUB4: return generators::thumb::math::SUB4(code, settings);
        case thumb_id::MUL: return generators::thumb::math::MUL(code, settings);
        case thumb_id::AND: return generators::thumb::logic::AND(code, settings);
        case thumb_id::ASR1: return generators::thumb::logic::ASR1(code, settings);
        case thumb_id::ASR2: return generators::thumb::logic::ASR2(code, settings);
        case thumb_id::BIC: return generators::thumb::logic::BIC(code, settings);
        case thumb_id::EOR: return generators::thumb::logic::EOR(code, settings);
        case thumb_id::LSL1: return generators::thumb::logic::LSL1(code, settings);
        case thumb_id::LSL2: return generators::thumb::logic::LSL2(code, settings);
        case thumb_id::LSR1: return generators::thumb::logic::LSR1(code, settings);
        case thumb_id::LSR2: return generators::thumb::logic::LSR2(code, settings);
        case thumb_id::NEG: return generators::thumb::logic::NEG(code, settings);
        case thumb_id::ORR: return generators::thumb::logic::ORR(code, settings);
        case thumb_id::ROR: return generators::thumb::logic::ROR(code, settings);
        case thumb_id::TST: return generators::thumb::logic::TST(code, settings);
        case thumb_id::CMN: return generators::thumb::comparison::CMN(code, settings);
        case thumb_id::CMP1: return generators::thumb::comparison::CMP1(code, settings);
        case thumb_id::CMP2: return generators::thumb::comparison::CMP2(code, settings);
        case thumb_id::CMP3: return generators::thumb::comparison::CMP3(code, settings);
        case thumb_id::MOV1: return generators::thumb::movement::MOV1(code, settings);
        case thumb_id::MOV2: return generators::thumb::movement::MOV2(code, settings);
        case thumb_id::MOV3: return generators::thumb::movement::MOV3(code, settings);
        case thumb_id::MVN: return generators::thumb::movement::MVN(code, settings);
        case thumb_id::B1: return generators::thumb::branching::B1(code, PC, settings);
        case thumb_id::B2: return generators::thumb::branching::B2(code, PC, settings);
        case thumb_id::BL: // TODO
        case thumb_id::BLX1: // TODO
        case thumb_id::BLX2: return generators::thumb::branching::BLX2(code, settings);
        case thumb_id::BX: return generators::thumb::branching::BX(code, settings);
        case thumb_id::BKPT: return generators::thumb::misc::BKPT(code, settings);
        case thumb_id::SWI: return generators::thumb::misc::SWI(code, settings);
        case thumb_id::LDMIA: return generators::thumb::load::LDMIA(code, settings);
        case thumb_id::LDR1: return generators::thumb::load::LDR1(code, settings);
        case thumb_id::LDR2: return generators::thumb::load::LDR2(code, settings);
        case thumb_id::LDR3: return generators::thumb::load::LDR3(code, settings);
        case thumb_id::LDR4: return generators::thumb::load::LDR4(code, settings);
        case thumb_id::LDRB1: return generators::thumb::load::LDRB1(code, settings);
        case thumb_id::LDRB2: return generators::thumb::load::LDRB2(code, settings);
        case thumb_id::LDRH1: return generators::thumb::load::LDRH1(code, settings);
        case thumb_id::LDRH2: return generators::thumb::load::LDRH2(code, settings);
        case thumb_id::LDRSB: return generators::thumb::load::LDRSB(code, settings);
        case thumb_id::LDRSH: return generators::thumb::load::LDRSH(code, settings);
        case thumb_id::POP: return generators::thumb::load::POP(code, settings);
        case thumb_id::PUSH: return generators::thumb::store::PUSH(code, settings);
        case thumb_id::STMIA: return generators::thumb::store::STMIA(code, settings);
        case thumb_id::STR1: return generators::thumb::store::STR1(code, settings);
        case thumb_id::STR2: return generators::thumb::store::STR2(code, settings);
        case thumb_id::STR3: return generators::thumb::store::STR3(code, settings);
        case thumb_id::STRB1: return generators::thumb::store::STRB1(code, settings);
        case thumb_id::STRB2: return generators::thumb::store::STRB2(code, settings);
        case thumb_id::STRH1: return generators::thumb::store::STRH1(code, settings);
        case thumb_id::STRH2: return generators::thumb::store::STRH2(code, settings);
        case thumb_id::UNDEFINED: llarm::out::error("Undefined instruction encountered for thumb disassembly");
        case thumb_id::UNKNOWN: llarm::out::error("Unknown instruction encountered for disassembly");
        case thumb_id::NOP: llarm::out::error("NOP instruction encountered for thumb disassembly");
    }
}


std::string disassemble::arm_generate(const u32 code, const u32 PC, const settings settings) {
    const arm_id id = ident::u32_arm::arm(code);

    switch (id) {
        case arm_id::ADC: return generators::arm::math::ADC(code, settings);
        case arm_id::ADD: return generators::arm::math::ADD(code, settings);
        case arm_id::AND: return generators::arm::logic::AND(code, settings);
        case arm_id::B: return generators::arm::branching::B(code, PC, settings); 
        case arm_id::BL: return generators::arm::branching::BL(code, PC, settings); 
        case arm_id::BIC: return generators::arm::logic::BIC(code, settings); 
        case arm_id::CDP2: 
        case arm_id::CDP: return generators::arm::coprocessor::CDP(code, settings);
        case arm_id::CMN: return generators::arm::logic::CMN(code, settings);
        case arm_id::CMP: return generators::arm::logic::CMP(code, settings);
        case arm_id::EOR: return generators::arm::logic::EOR(code, settings);
        case arm_id::LDC2:
        case arm_id::LDC: return generators::arm::coprocessor::LDC(code, settings);
        case arm_id::LDM1: return generators::arm::load::LDM1(code, settings);
        case arm_id::LDM2: return generators::arm::load::LDM2(code, settings);
        case arm_id::LDM3: return generators::arm::load::LDM3(code, settings);
        case arm_id::LDR: return generators::arm::load::LDR(code, settings);
        case arm_id::LDRB: return generators::arm::load::LDRB(code, settings);
        case arm_id::LDRBT: return generators::arm::load::LDRBT(code, settings);
        case arm_id::LDRT: return generators::arm::load::LDRT(code, settings);
        case arm_id::MCR2: 
        case arm_id::MCR: return generators::arm::coprocessor::MCR(code, settings);
        case arm_id::MLA: return generators::arm::multiply::MLA(code, settings);
        case arm_id::MOV: return generators::arm::movement::MOV(code, settings);
        case arm_id::MRC2: 
        case arm_id::MRC: return generators::arm::coprocessor::MRC(code, settings);
        case arm_id::MRS: return generators::arm::movement::MRS(code, settings);
        case arm_id::MSR_IMM: return generators::arm::movement::MSR_IMM(code, settings);
        case arm_id::MSR_REG: return generators::arm::movement::MSR_REG(code, settings);
        case arm_id::MUL: return generators::arm::multiply::MUL(code, settings);
        case arm_id::MVN: return generators::arm::movement::MVN(code, settings);
        case arm_id::ORR: return generators::arm::logic::ORR(code, settings);
        case arm_id::RSB: return generators::arm::math::RSB(code, settings);
        case arm_id::RSC: return generators::arm::math::RSC(code, settings);
        case arm_id::SBC: return generators::arm::math::SBC(code, settings);
        case arm_id::STC2: 
        case arm_id::STC: return generators::arm::coprocessor::STC(code, settings);
        case arm_id::STM1: return generators::arm::store::STM1(code, settings);
        case arm_id::STM2: return generators::arm::store::STM2(code, settings);
        case arm_id::STR: return generators::arm::store::STR(code, settings);
        case arm_id::STRB: return generators::arm::store::STRB(code, settings);
        case arm_id::STRBT: return generators::arm::store::STRBT(code, settings);
        case arm_id::STRT: return generators::arm::store::STRT(code, settings);
        case arm_id::SUB: return generators::arm::math::SUB(code, settings);
        case arm_id::SWI: return generators::arm::misc::SWI(code, settings);
        case arm_id::NOP: return generators::arm::misc::NOP();
        case arm_id::SWP: return generators::arm::store::SWP(code, settings);
        case arm_id::SWPB: return generators::arm::store::SWPB(code, settings);
        case arm_id::TEQ: return generators::arm::logic::TEQ(code, settings);
        case arm_id::TST: return generators::arm::logic::TST(code, settings);
        case arm_id::CMNP: return generators::arm::misc::PSR(code, settings);
        case arm_id::CMPP: return generators::arm::misc::PSR(code, settings);
        case arm_id::TEQP: return generators::arm::misc::PSR(code, settings);
        case arm_id::TSTP: return generators::arm::misc::PSR(code, settings);
        case arm_id::STRH: return generators::arm::store::STRH(code, settings);
        case arm_id::LDRH: return generators::arm::load::LDRH(code, settings);
        case arm_id::LDRSB: return generators::arm::load::LDRSB(code, settings);
        case arm_id::LDRSH: return generators::arm::load::LDRSH(code, settings);
        case arm_id::BKPT: return generators::arm::misc::BKPT(code, settings);
        case arm_id::BLX1: return generators::arm::branching::BLX1(code, PC, settings);
        case arm_id::BLX2: return generators::arm::branching::BLX2(code, settings);
        case arm_id::CLZ: return generators::arm::logic::CLZ(code, settings);
        case arm_id::BX: return generators::arm::branching::BX(code, settings); 
        case arm_id::SMLAL: return generators::arm::multiply::SMLAL(code, settings);
        case arm_id::SMULL: return generators::arm::multiply::SMULL(code, settings);
        case arm_id::UMLAL: return generators::arm::multiply::UMLAL(code, settings);
        case arm_id::UMULL: return generators::arm::multiply::UMULL(code, settings);
        case arm_id::LDRD: return generators::arm::dsp::LDRD(code, settings);
        case arm_id::MCRR: return generators::arm::dsp::MCRR(code, settings);
        case arm_id::MRRC: return generators::arm::dsp::MRRC(code, settings);
        case arm_id::PLD: return generators::arm::dsp::PLD(code, settings);
        case arm_id::QADD: return generators::arm::dsp::QADD(code, settings);
        case arm_id::QDADD: return generators::arm::dsp::QDADD(code, settings);
        case arm_id::QDSUB: return generators::arm::dsp::QDSUB(code, settings);
        case arm_id::QSUB: return generators::arm::dsp::QSUB(code, settings);
        case arm_id::SMLAXY: return generators::arm::dsp::SMLAXY(code, settings);
        case arm_id::SMLALXY: return generators::arm::dsp::SMLALXY(code, settings);
        case arm_id::SMLAWY: return generators::arm::dsp::SMLAWY(code, settings);
        case arm_id::SMULXY: return generators::arm::dsp::SMULXY(code, settings);
        case arm_id::SMULWY: return generators::arm::dsp::SMULWY(code, settings);
        case arm_id::STRD: return generators::arm::dsp::STRD(code, settings);
        case arm_id::FABSD: return generators::arm::vfp::FABSD(code, settings);
        case arm_id::FABSS: return generators::arm::vfp::FABSS(code, settings);
        case arm_id::FADDD: return generators::arm::vfp::FADDD(code, settings);
        case arm_id::FADDS: return generators::arm::vfp::FADDS(code, settings);
        case arm_id::FCMPD: return generators::arm::vfp::FCMPD(code, settings);
        case arm_id::FCMPED: return generators::arm::vfp::FCMPED(code, settings);
        case arm_id::FCMPES: return generators::arm::vfp::FCMPES(code, settings);
        case arm_id::FCMPEZD: return generators::arm::vfp::FCMPEZD(code, settings);
        case arm_id::FCMPEZS: return generators::arm::vfp::FCMPEZS(code, settings);
        case arm_id::FCMPS: return generators::arm::vfp::FCMPS(code, settings);
        case arm_id::FCMPZD: return generators::arm::vfp::FCMPZD(code, settings);
        case arm_id::FCMPZS: return generators::arm::vfp::FCMPZS(code, settings);
        case arm_id::FCPYD: return generators::arm::vfp::FCPYD(code, settings);
        case arm_id::FCPYS: return generators::arm::vfp::FCPYS(code, settings);
        case arm_id::FCVTDS: return generators::arm::vfp::FCVTDS(code, settings);
        case arm_id::FCVTSD: return generators::arm::vfp::FCVTSD(code, settings);
        case arm_id::FDIVD: return generators::arm::vfp::FDIVD(code, settings);
        case arm_id::FDIVS: return generators::arm::vfp::FDIVS(code, settings);
        case arm_id::FLDD: return generators::arm::vfp::FLDD(code, settings);
        case arm_id::FLDMD: return generators::arm::vfp::FLDMD(code, settings);
        case arm_id::FLDMS: return generators::arm::vfp::FLDMS(code, settings);
        case arm_id::FLDMX: return generators::arm::vfp::FLDMX(code, settings);
        case arm_id::FLDS: return generators::arm::vfp::FLDS(code, settings);
        case arm_id::FMACD: return generators::arm::vfp::FMACD(code, settings);
        case arm_id::FMACS: return generators::arm::vfp::FMACS(code, settings);
        case arm_id::FMDHR: return generators::arm::vfp::FMDHR(code, settings);
        case arm_id::FMDLR: return generators::arm::vfp::FMDLR(code, settings);
        case arm_id::FMRDH: return generators::arm::vfp::FMRDH(code, settings);
        case arm_id::FMRDL: return generators::arm::vfp::FMRDL(code, settings);
        case arm_id::FMRS: return generators::arm::vfp::FMRS(code, settings);
        case arm_id::FMRX: return generators::arm::vfp::FMRX(code, settings);
        case arm_id::FMSCD: return generators::arm::vfp::FMSCD(code, settings);
        case arm_id::FMSCS: return generators::arm::vfp::FMSCS(code, settings);
        case arm_id::FMSR: return generators::arm::vfp::FMSR(code, settings);
        case arm_id::FMSTAT: return generators::arm::vfp::FMSTAT(code, settings);
        case arm_id::FMULD: return generators::arm::vfp::FMULD(code, settings);
        case arm_id::FMULS: return generators::arm::vfp::FMULS(code, settings);
        case arm_id::FMXR: return generators::arm::vfp::FMXR(code, settings);
        case arm_id::FNEGD: return generators::arm::vfp::FNEGD(code, settings);
        case arm_id::FNEGS: return generators::arm::vfp::FNEGS(code, settings);
        case arm_id::FNMACD: return generators::arm::vfp::FNMACD(code, settings);
        case arm_id::FNMACS: return generators::arm::vfp::FNMACS(code, settings);
        case arm_id::FNMSCD: return generators::arm::vfp::FNMSCD(code, settings);
        case arm_id::FNMSCS: return generators::arm::vfp::FNMSCS(code, settings);
        case arm_id::FNMULD: return generators::arm::vfp::FNMULD(code, settings);
        case arm_id::FNMULS: return generators::arm::vfp::FNMULS(code, settings);
        case arm_id::FSITOD: return generators::arm::vfp::FSITOD(code, settings);
        case arm_id::FSITOS: return generators::arm::vfp::FSITOS(code, settings);
        case arm_id::FSQRTD: return generators::arm::vfp::FSQRTD(code, settings);
        case arm_id::FSQRTS: return generators::arm::vfp::FSQRTS(code, settings);
        case arm_id::FSTD: return generators::arm::vfp::FSTD(code, settings);
        case arm_id::FSTMD: return generators::arm::vfp::FSTMD(code, settings);
        case arm_id::FSTMS: return generators::arm::vfp::FSTMS(code, settings);
        case arm_id::FSTMX: return generators::arm::vfp::FSTMX(code, settings);
        case arm_id::FSTS: return generators::arm::vfp::FSTS(code, settings);
        case arm_id::FSUBD: return generators::arm::vfp::FSUBD(code, settings);
        case arm_id::FSUBS: return generators::arm::vfp::FSUBS(code, settings);
        case arm_id::FTOSID: return generators::arm::vfp::FTOSID(code, settings);
        case arm_id::FTOSIS: return generators::arm::vfp::FTOSIS(code, settings);
        case arm_id::FTOUID: return generators::arm::vfp::FTOUID(code, settings);
        case arm_id::FTOUIS: return generators::arm::vfp::FTOUIS(code, settings);
        case arm_id::FUITOD: return generators::arm::vfp::FUITOD(code, settings);
        case arm_id::FUITOS: return generators::arm::vfp::FUITOS(code, settings); 
        case arm_id::UNKNOWN: llarm::out::error("Unknown instruction encountered for disassembly");
        case arm_id::UNDEFINED: llarm::out::error("Undefined instruction encountered for disassembly");
    }
}


std::string disassemble::arm(const u32 code, const u32 PC, const settings settings) {
    std::string instruction = arm_generate(code, PC, settings);

    if (settings.capitals == false) {
        llarm::util::to_lower(instruction);
    }

    return instruction;
}


std::string disassemble::thumb(const u16 code, const u32 PC, const settings settings) {
    std::string instruction = thumb_generate(code, PC, settings);

    if (settings.capitals == false) {
        llarm::util::to_lower(instruction);
    }

    return instruction;
}