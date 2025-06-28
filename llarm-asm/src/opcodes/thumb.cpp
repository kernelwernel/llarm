#include "opcodes.hpp"

#include "shared/types.hpp"

using namespace internal;

// TODO implement the switch-shift (SWIFT) optimisation idea

bool opcodes::thumb::ADC(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 0) &&
        (raw_code.test(8) == 1) &&
        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 1)
    );
}

bool opcodes::thumb::ADD1(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 1) &&
        (raw_code.test(9) == 0)
    );
}

bool opcodes::thumb::ADD2(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 0)
    );
}


bool opcodes::thumb::ADD3(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 0)
    );
}

bool opcodes::thumb::ADD4(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 1) &&
        (raw_code.test(9) == 0) &&
        (raw_code.test(8) == 0)
    );
}

bool opcodes::thumb::ADD5(const u16raw_code) {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0)
    );
}

bool opcodes::thumb::ADD6(const u16raw_code) {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 1)
    );
}

bool opcodes::thumb::ADD7(const u16raw_code) {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 0) &&
        (raw_code.test(8) == 0) &&
        (raw_code.test(7) == 0)
    );
}

bool opcodes::thumb::AND(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 0) &&
        (raw_code.test(8) == 0) &&
        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 0)
    );
}

bool opcodes::thumb::ASR1(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 0)
    );
}

bool opcodes::thumb::ASR2(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 0) &&
        (raw_code.test(8) == 1) &&
        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 0)
    );
}

bool opcodes::thumb::B1(const u16raw_code) {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 1)
    );
}

bool opcodes::thumb::B2(const u16raw_code) {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0)
    );
}

bool opcodes::thumb::BIC(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 0)
    );
}

bool opcodes::thumb::BL(const u16raw_code) {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0)
    );
}

bool opcodes::thumb::BX(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 1) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&
        (raw_code.test(7) == 0)
    );
}

bool opcodes::thumb::CMN(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 1)
    );
}

bool opcodes::thumb::CMP1(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 1)
    );
}

bool opcodes::thumb::CMP2(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 0)
    );
}

bool opcodes::thumb::CMP3(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 1) &&
        (raw_code.test(9) == 0) &&
        (raw_code.test(8) == 1)
    );
}

bool opcodes::thumb::EOR(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 0) &&
        (raw_code.test(8) == 0) &&
        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 1)
    );
}

bool opcodes::thumb::LDMIA(const u16raw_code) {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 1)
    );
}

bool opcodes::thumb::LDR1(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 1)
    );
}

bool opcodes::thumb::LDR2(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 0)
    );
}

bool opcodes::thumb::LDR3(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 1)
    );
}

bool opcodes::thumb::LDR4(const u16raw_code) {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 1)
    );
}

bool opcodes::thumb::LDRB1(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 1)
    );
}

bool opcodes::thumb::LDRB2(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 1) &&
        (raw_code.test(9) == 0)
    );
}

bool opcodes::thumb::LDRH1(const u16raw_code) {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 1)
    );
}

bool opcodes::thumb::LDRH2(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1)
    );
}

bool opcodes::thumb::LDRSB(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 1) &&
        (raw_code.test(9) == 1)
    );
}

bool opcodes::thumb::LDRSH(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 1) &&
        (raw_code.test(9) == 1)
    );
}

bool opcodes::thumb::LSL1(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0)
    );
}

bool opcodes::thumb::LSL2(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 0) &&
        (raw_code.test(8) == 0) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 0)
    );
}

bool opcodes::thumb::LSR1(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 1)
    );
}

bool opcodes::thumb::LSR2(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 0) &&
        (raw_code.test(8) == 0) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 1)
    );
}

bool opcodes::thumb::MOV1(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0)
    );
}

bool opcodes::thumb::MOV2(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 1) &&
        (raw_code.test(9) == 0) &&
        (raw_code.test(8) == 0) &&
        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 0)
    );
}

bool opcodes::thumb::MOV3(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 1) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0)
    );
}

bool opcodes::thumb::MUL(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&
        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 1)
    );
}

bool opcodes::thumb::MVN(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 1)
    );
}

bool opcodes::thumb::NEG(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&
        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 1)
    );
}

bool opcodes::thumb::NOP(const u16raw_code) {
    return (raw_code.none());
}

bool opcodes::thumb::ORR(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&
        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 0)
    );
}

bool opcodes::thumb::POP(const u16raw_code) {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 1) &&
        (raw_code.test(9) == 0)
    );
}

bool opcodes::thumb::PUSH(const u16raw_code) {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 1) &&
        (raw_code.test(9) == 0)
    );
}

bool opcodes::thumb::ROR(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 0) &&
        (raw_code.test(8) == 1) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 1)
    );
}

bool opcodes::thumb::SBC(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 0) &&
        (raw_code.test(8) == 1) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 0)
    );
}

bool opcodes::thumb::STMIA(const u16raw_code) {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0)
    );
}

bool opcodes::thumb::STR1(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0)
    );
}

bool opcodes::thumb::STR2(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 0)
    );
}

bool opcodes::thumb::STR3(const u16raw_code) {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 0)
    );
}

bool opcodes::thumb::STRB1(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 0)
    );
}

bool opcodes::thumb::STRB2(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 1) &&
        (raw_code.test(9) == 0)
    );
}


bool opcodes::thumb::STRH1(const u16raw_code) {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0)
    );
}

bool opcodes::thumb::STRH2(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1)
    );
}

bool opcodes::thumb::SUB1(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 1) &&
        (raw_code.test(9) == 1)
    );
}

bool opcodes::thumb::SUB2(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 1)
    );
}

bool opcodes::thumb::SUB3(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1)
    );
}

bool opcodes::thumb::SUB4(const u16raw_code) {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 0) &&
        (raw_code.test(8) == 0) &&
        (raw_code.test(7) == 1)
    );
}

bool opcodes::thumb::SWI(const u16raw_code) {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 1) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1)
    );
}

bool opcodes::thumb::TST(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&
        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 0)
    );
}

bool opcodes::thumb::BKPT(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 0)
    );
}

bool opcodes::thumb::BLX1(const u16raw_code) {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 1)
    );
}

bool opcodes::thumb::BLX2(const u16raw_code) {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0) &&
        (raw_code.test(10) == 1) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&
        (raw_code.test(7) == 1)
    );
}