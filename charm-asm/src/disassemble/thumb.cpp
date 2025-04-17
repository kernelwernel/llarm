#include "disassemble.hpp"
#include "../identifiers/identifiers.hpp"
#include "../instruction_id.hpp"
#include "generators/generators.hpp"

#include <charm/internal/shared/types.hpp>

#include <string>

using namespace internal;

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
        case id::thumb::POP:
        case id::thumb::PUSH:
        case id::thumb::STMIA:
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