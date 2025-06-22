#include "opcodes.hpp"

#include "shared/types.hpp"

using namespace internal;


bool opcodes::arm::ADC(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1)
    );
}

bool opcodes::arm::ADD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 0)
    );
}

bool opcodes::arm::AND(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 0)
    );
}

bool opcodes::arm::UNDEFINED(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::NOP(const arm_code_t &raw_code) noexcept {
    return (raw_code.none());
}

bool opcodes::arm::PSR(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(20) == 1) &&
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 1)
    );
}


bool opcodes::arm::B(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 1)
    );
}


bool opcodes::arm::BL(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 1)
    );
}


bool opcodes::arm::BIC(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 0)
    );
}

bool opcodes::arm::CDP(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::CDP2(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(31) == 1) &&
        (raw_code.test(30) == 1) &&
        (raw_code.test(29) == 1) &&
        (raw_code.test(28) == 1) &&
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::CMN(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1)
    );
}

bool opcodes::arm::CMP(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 1)
    );
}

bool opcodes::arm::EOR(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1)
    );
}

bool opcodes::arm::LDC(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(20) == 0)
    );
}


bool opcodes::arm::LDC2(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(31) == 1) &&
        (raw_code.test(30) == 1) &&
        (raw_code.test(29) == 1) &&
        (raw_code.test(28) == 1) &&
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(20) == 0)
    );
}

bool opcodes::arm::LDM1(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(20) == 1)
    );
}

bool opcodes::arm::LDM2(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 1) &&
        (raw_code.test(15) == 0)
    );
}

bool opcodes::arm::LDM3(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(20) == 1) &&
        (raw_code.test(15) == 1)
    );
}

bool opcodes::arm::LDR(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(20) == 1)
    );
}

bool opcodes::arm::LDRB(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(20) == 1)
    );
}

bool opcodes::arm::LDRBT(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1)
    );
}

bool opcodes::arm::LDRT(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1)
    );
}

bool opcodes::arm::MCR(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(20) == 0) &&
        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::MCR2(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(31) == 1) &&
        (raw_code.test(30) == 1) &&
        (raw_code.test(29) == 1) &&
        (raw_code.test(28) == 1) &&
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(20) == 0) &&
        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::MLA(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 0) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::MOV(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1)
    );
}

bool opcodes::arm::MRC(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(20) == 1) &&
        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::MRC2(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(31) == 1) &&
        (raw_code.test(30) == 1) &&
        (raw_code.test(29) == 1) &&
        (raw_code.test(28) == 1) &&
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(20) == 1) &&
        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::MRS(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 0)
    );
}

bool opcodes::arm::MSR_IMM(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 0)
    );
}

bool opcodes::arm::MSR_REG(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 0) &&
        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 0) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::MUL(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 0) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::MVN(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 1)
    );
}

bool opcodes::arm::ORR(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 0)
    );
}

bool opcodes::arm::RSB(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 1)
    );
}

bool opcodes::arm::RSC(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 1)
    );
}

bool opcodes::arm::SBC(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 0)
    );
}

bool opcodes::arm::STC(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(20) == 0)
    );
}

bool opcodes::arm::STC2(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(31) == 1) &&
        (raw_code.test(30) == 1) &&
        (raw_code.test(29) == 1) &&
        (raw_code.test(28) == 1) &&
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(20) == 0)
    );
}

bool opcodes::arm::STM1(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(20) == 0)
    );
}

bool opcodes::arm::STM2(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 0)
    );
}

bool opcodes::arm::STR(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(20) == 0)
    );
}

bool opcodes::arm::STRB(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(20) == 0)
    );
}

bool opcodes::arm::STRBT(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 0)
    );
}

bool opcodes::arm::STRT(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 0)
    );
}

bool opcodes::arm::SUB(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 0)
    );
}

bool opcodes::arm::SWI(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 1)
    );
}

bool opcodes::arm::SWP(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 0) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 0) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::SWPB(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 0) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 0) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::TEQ(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1)
    );
}

bool opcodes::arm::TST(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 1)
    );
}

bool opcodes::arm::STRH(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(20) == 0) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 0) &&
        (raw_code.test(5) == 1) &&
        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::LDRH(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(20) == 1) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 0) &&
        (raw_code.test(5) == 1) &&
        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::LDRSB(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(20) == 1) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::LDRSH(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(20) == 1) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(5) == 1) &&
        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::BKPT(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(31) == 1) &&
        (raw_code.test(30) == 1) &&
        (raw_code.test(29) == 1) &&
        (raw_code.test(28) == 0) &&
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 0) &&
        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(5) == 1) &&
        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::BLX1(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(31) == 1) &&
        (raw_code.test(30) == 1) &&
        (raw_code.test(29) == 1) &&
        (raw_code.test(28) == 1) &&
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 1)
    );
}

bool opcodes::arm::BLX2(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 0) &&
        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 0) &&
        (raw_code.test(5) == 1) &&
        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::CLZ(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 0) &&
        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 0) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::BX(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 0) &&
        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 0) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 1)
    );
} 

bool opcodes::arm::SMLAL(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 0) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::SMULL(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 0) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::UMLAL(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 0) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::UMULL(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 0) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 1)
    );
}




bool opcodes::arm::LDRD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(20) == 0) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::MCRR(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 0)
    );
}

bool opcodes::arm::MRRC(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 1)
    );
}

bool opcodes::arm::PLD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(31) == 1) &&
        (raw_code.test(30) == 1) &&
        (raw_code.test(29) == 1) &&
        (raw_code.test(28) == 1) &&
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 1) &&
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 1)
    );
}

bool opcodes::arm::QADD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 0) &&
        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::QDADD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 0) &&
        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::QDSUB(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 0) &&
        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::QSUB(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 0) &&
        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::SMLA(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 0) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(4) == 0)
    );
}

// what the fuck is this? TODO
//bool opcodes::arm::(const arm_code_t &raw_code) noexcept {
//    return (
//        (raw_code.test(27) == 0) &&
//        (raw_code.test(26) == 0) &&
//        (raw_code.test(25) == 0) &&
//        (raw_code.test(24) == 1) &&
//        (raw_code.test(23) == 0) &&
//        (raw_code.test(22) == 1) &&
//        (raw_code.test(21) == 0) &&
//        (raw_code.test(20) == 0) &&
//        (raw_code.test(7) == 1) &&
//        (raw_code.test(4) == 0)
//    );
//}

bool opcodes::arm::SMLAW(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 0) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::SMUL(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 0) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::SMULW(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 0) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(5) == 1) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::STRD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(20) == 0) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(5) == 1) &&
        (raw_code.test(4) == 1)
    );
}



















bool opcodes::arm::FABSD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&
        (raw_code.test(19) == 0) &&
        (raw_code.test(18) == 0) &&
        (raw_code.test(17) == 0) &&
        (raw_code.test(16) == 0) &&
        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 0)
    );
}


bool opcodes::arm::FABSS(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&
        (raw_code.test(19) == 0) &&
        (raw_code.test(18) == 0) &&
        (raw_code.test(17) == 0) &&
        (raw_code.test(16) == 0) &&
        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(4) == 0)
    );
}


bool opcodes::arm::FADDD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&
        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&
        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 0) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FADDS(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&

        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&
        (raw_code.test(6) == 0) &&
        (raw_code.test(4) == 0)
    );
}


bool opcodes::arm::FCMPD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(19) == 0) &&
        (raw_code.test(18) == 1) &&
        (raw_code.test(17) == 0) &&
        (raw_code.test(16) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&
        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 0)
    );
}


bool opcodes::arm::FCMPED(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(19) == 0) &&
        (raw_code.test(18) == 1) &&
        (raw_code.test(17) == 0) &&
        (raw_code.test(16) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FCMPES(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(19) == 0) &&
        (raw_code.test(18) == 1) &&
        (raw_code.test(17) == 0) &&
        (raw_code.test(16) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(4) == 0)
    );
}


bool opcodes::arm::FCMPEZD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(19) == 0) &&
        (raw_code.test(18) == 1) &&
        (raw_code.test(17) == 0) &&
        (raw_code.test(16) == 1) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 0)
    );
}


bool opcodes::arm::FCMPEZS(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(19) == 0) &&
        (raw_code.test(18) == 1) &&
        (raw_code.test(17) == 0) &&
        (raw_code.test(16) == 1) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 0)
    );
}


bool opcodes::arm::FCMPS(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(19) == 0) &&
        (raw_code.test(18) == 1) &&
        (raw_code.test(17) == 0) &&
        (raw_code.test(16) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&
        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(4) == 0)
    );
}


bool opcodes::arm::FCMPZD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(19) == 0) &&
        (raw_code.test(18) == 1) &&
        (raw_code.test(17) == 0) &&
        (raw_code.test(16) == 1) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&
        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 0)
    );
}


bool opcodes::arm::FCMPZS(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(19) == 0) &&
        (raw_code.test(18) == 1) &&
        (raw_code.test(17) == 0) &&
        (raw_code.test(16) == 1) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&
        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 0)
    );
}


bool opcodes::arm::FCPYD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(19) == 0) &&
        (raw_code.test(18) == 0) &&
        (raw_code.test(17) == 0) &&
        (raw_code.test(16) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&
        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FCPYS(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(19) == 0) &&
        (raw_code.test(18) == 0) &&
        (raw_code.test(17) == 0) &&
        (raw_code.test(16) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&
        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FCVTDS(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(19) == 0) &&
        (raw_code.test(18) == 1) &&
        (raw_code.test(17) == 1) &&
        (raw_code.test(16) == 1) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FCVTSD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(19) == 0) &&
        (raw_code.test(18) == 1) &&
        (raw_code.test(17) == 1) &&
        (raw_code.test(16) == 1) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FDIVD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&
        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 0) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FDIVS(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&
        (raw_code.test(6) == 0) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FLDD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1)
    );
}

bool opcodes::arm::FLDMD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1)
    );
}

bool opcodes::arm::FLDMS(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0)
    );
}

bool opcodes::arm::FLDMX(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1)
    );
}

bool opcodes::arm::FLDS(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0)
    );
}

bool opcodes::arm::FMACD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&

        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 0) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FMACS(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&

        (raw_code.test(6) == 0) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FMDHR(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&

        (raw_code.test(7) == 0) &&
        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::FMDLR(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&

        (raw_code.test(7) == 0) &&
        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::FMRDH(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&

        (raw_code.test(7) == 0) &&
        (raw_code.test(4) == 1)
    );
}

/* what is this? todo
bool opcodes::arm::(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == ) &&
        (raw_code.test(20) == ) &&

        (raw_code.test(19) == ) &&
        (raw_code.test(18) == ) &&
        (raw_code.test(17) == ) &&
        (raw_code.test(16) == ) &&

        (raw_code.test(11) == ) &&
        (raw_code.test(10) == ) &&
        (raw_code.test(9) == ) &&
        (raw_code.test(8) == ) &&

        (raw_code.test(7) == ) &&
        (raw_code.test(6) == ) &&
        (raw_code.test(5) == ) &&
        (raw_code.test(4) == )
    );
}
*/


bool opcodes::arm::FMRDL(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&

        (raw_code.test(7) == 0) &&
        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::FMRS(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&

        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::FMRX(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&

        (raw_code.test(7) == 0) &&
        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::FMSCD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&

        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 0) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FMSCS(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&

        (raw_code.test(6) == 0) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FMSR(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&

        (raw_code.test(4) == 1)
    );
}


bool opcodes::arm::FMSTAT(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(19) == 0) &&
        (raw_code.test(18) == 0) &&
        (raw_code.test(17) == 0) &&
        (raw_code.test(16) == 1) &&

        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 1) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&

        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::FMULD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&

        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 0) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FMULS(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&

        (raw_code.test(6) == 0) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FMXR(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&

        (raw_code.test(7) == 0) &&
        (raw_code.test(4) == 1)
    );
}

bool opcodes::arm::FNEGD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(19) == 0) &&
        (raw_code.test(18) == 0) &&
        (raw_code.test(17) == 0) &&
        (raw_code.test(16) == 1) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&

        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FNEGS(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(19) == 0) &&
        (raw_code.test(18) == 0) &&
        (raw_code.test(17) == 0) &&
        (raw_code.test(16) == 1) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&

        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FNMACD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&

        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FNMACS(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&

        (raw_code.test(6) == 1) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FNMSCD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&

        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FNMSCS(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&

        (raw_code.test(6) == 1) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FNMULD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&

        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FNMULS(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&

        (raw_code.test(6) == 1) &&
        (raw_code.test(4) == 0)
    );
}


bool opcodes::arm::FSITOD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(19) == 1) &&
        (raw_code.test(18) == 0) &&
        (raw_code.test(17) == 0) &&
        (raw_code.test(16) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&

        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FSITOS(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(19) == 1) &&
        (raw_code.test(18) == 0) &&
        (raw_code.test(17) == 0) &&
        (raw_code.test(16) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&

        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(4) == 0)
    );
}


bool opcodes::arm::FSQRTD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(19) == 0) &&
        (raw_code.test(18) == 0) &&
        (raw_code.test(17) == 0) &&
        (raw_code.test(16) == 1) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&

        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 0)
    );
}


bool opcodes::arm::FSQRTS(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(19) == 0) &&
        (raw_code.test(18) == 0) &&
        (raw_code.test(17) == 0) &&
        (raw_code.test(16) == 1) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&

        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FSTD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1)
    );
}

bool opcodes::arm::FSTMD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(20) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1)
    );
}

bool opcodes::arm::FSTMS(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(20) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0)
    );
}

bool opcodes::arm::FSTMX(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(20) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1)
    );
}

bool opcodes::arm::FSTS(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0)
    );
}

bool opcodes::arm::FSUBD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&

        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FSUBS(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&

        (raw_code.test(6) == 1) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FTOSID(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(19) == 1) &&
        (raw_code.test(18) == 1) &&
        (raw_code.test(17) == 0) &&
        (raw_code.test(16) == 1) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&

        (raw_code.test(6) == 1) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FTOSIS(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(19) == 1) &&
        (raw_code.test(18) == 1) &&
        (raw_code.test(17) == 0) &&
        (raw_code.test(16) == 1) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&

        (raw_code.test(6) == 1) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FTOUID(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(19) == 1) &&
        (raw_code.test(18) == 1) &&
        (raw_code.test(17) == 0) &&
        (raw_code.test(16) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&

        (raw_code.test(6) == 1) &&
        (raw_code.test(5) == 0) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FTOUIS(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(19) == 1) &&
        (raw_code.test(18) == 1) &&
        (raw_code.test(17) == 0) &&
        (raw_code.test(16) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&

        (raw_code.test(6) == 1) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FUITOD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(19) == 1) &&
        (raw_code.test(18) == 0) &&
        (raw_code.test(17) == 0) &&
        (raw_code.test(16) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 1) &&

        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::FUITOS(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1) &&

        (raw_code.test(19) == 1) &&
        (raw_code.test(18) == 0) &&
        (raw_code.test(17) == 0) &&
        (raw_code.test(16) == 0) &&

        (raw_code.test(11) == 1) &&
        (raw_code.test(10) == 0) &&
        (raw_code.test(9) == 1) &&
        (raw_code.test(8) == 0) &&

        (raw_code.test(7) == 0) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(4) == 0)
    );
}