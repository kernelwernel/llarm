#include "opcodes.hpp"
#include "../../types.hpp"

// TODO implement the switch-shift (SWIFT) optimisation idea


bool opcodes::thumb::ADC(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::ADD1(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::ADD2(const thumb_code_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 0)
    );
}


bool opcodes::thumb::ADD3(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::ADD4(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::ADD5(const thumb_code_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0)
    );
}

bool opcodes::thumb::ADD6(const thumb_code_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 1)
    );
}

bool opcodes::thumb::ADD7(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::AND(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::ASR1(const thumb_code_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 0)
    );
}

bool opcodes::thumb::ASR2(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::B1(const thumb_code_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 1)
    );
}

bool opcodes::thumb::B2(const thumb_code_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0)
    );
}

bool opcodes::thumb::BIC(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::BL(const thumb_code_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0)
    );
}

bool opcodes::thumb::BX(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::CMN(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::CMP1(const thumb_code_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 1)
    );
}

bool opcodes::thumb::CMP2(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::CMP3(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::EOR(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::LDMIA(const thumb_code_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 1)
    );
}

bool opcodes::thumb::LDR1(const thumb_code_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 1)
    );
}

bool opcodes::thumb::LDR2(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::LDR3(const thumb_code_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 1)
    );
}

bool opcodes::thumb::LDR4(const thumb_code_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 1)
    );
}

bool opcodes::thumb::LDRB1(const thumb_code_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 1)
    );
}

bool opcodes::thumb::LDRB2(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::LDRH1(const thumb_code_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 1)
    );
}

bool opcodes::thumb::LDRH2(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::LDRSB(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::LDRSH(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::LSL1(const thumb_code_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0)
    );
}

bool opcodes::thumb::LSL2(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::LSR1(const thumb_code_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 1)
    );
}

bool opcodes::thumb::LSR2(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::MOV1(const thumb_code_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0)
    );
}

bool opcodes::thumb::MOV2(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::MOV3(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::MUL(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::MVN(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::NEG(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::NOP(const thumb_code_t &raw_code) noexcept {
    return (raw_code.none());
}

bool opcodes::thumb::ORR(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::POP(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::PUSH(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::ROR(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::SBC(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::STMIA(const thumb_code_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0)
    );
}

bool opcodes::thumb::STR1(const thumb_code_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0)
    );
}

bool opcodes::thumb::STR2(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::STR3(const thumb_code_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 0)
    );
}

bool opcodes::thumb::STRB1(const thumb_code_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 0)
    );
}

bool opcodes::thumb::STRB2(const thumb_code_t &raw_code) noexcept {
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


bool opcodes::thumb::STRH1(const thumb_code_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0)
    );
}

bool opcodes::thumb::STRH2(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::SUB1(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::SUB2(const thumb_code_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 1)
    );
}

bool opcodes::thumb::SUB3(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::SUB4(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::SWI(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::TST(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::v5::BKPT(const thumb_code_t &raw_code) noexcept {
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

bool opcodes::thumb::v5::BLX1(const thumb_code_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 1)
    );
}

bool opcodes::thumb::v5::BLX2(const thumb_code_t &raw_code) noexcept {
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