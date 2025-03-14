#include "opcodes.hpp"
#include "../../types.hpp"

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


bool opcodes::arm::B_BL(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::LDM(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::MSR_OPR(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::v4::STRH(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::v4::LDRH(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::v4::LDRSB(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::v4::LDRSH(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::v5::BKPT(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::v5::BLX1(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::v5::BLX2(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::v5::CLZ(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::v5v4t::BX(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::M::SMLAL(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::M::SMULL(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::M::UMLAL(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::M::UMULL(const arm_code_t &raw_code) noexcept {
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




bool opcodes::arm::dsp::LDRD(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::dsp::MCRR(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::dsp::MRRC(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::dsp::PLD(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::dsp::QADD(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::dsp::QDADD(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::dsp::QDSUB(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::dsp::QSUB(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::dsp::SMLA(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::dsp::SMLAL(const arm_code_t &raw_code) noexcept {
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
        (raw_code.test(4) == 0)
    );
}

bool opcodes::arm::dsp::SMLAW(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::dsp::SMUL(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::dsp::SMULW(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::dsp::STRD(const arm_code_t &raw_code) noexcept {
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



















bool opcodes::arm::vfp::FABSD(const arm_code_t &raw_code) noexcept {
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


bool opcodes::arm::vfp::FABSS(const arm_code_t &raw_code) noexcept {
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


bool opcodes::arm::vfp::FADDD(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FADDS(const arm_code_t &raw_code) noexcept {
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


bool opcodes::arm::vfp::FCMPD(const arm_code_t &raw_code) noexcept {
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


bool opcodes::arm::vfp::FCMPED(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FCMPES(const arm_code_t &raw_code) noexcept {
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


bool opcodes::arm::vfp::FCMPEZD(const arm_code_t &raw_code) noexcept {
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


bool opcodes::arm::vfp::FCMPEZS(const arm_code_t &raw_code) noexcept {
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


bool opcodes::arm::vfp::FCMPS(const arm_code_t &raw_code) noexcept {
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


bool opcodes::arm::vfp::FCMPZD(const arm_code_t &raw_code) noexcept {
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


bool opcodes::arm::vfp::FCMPZS(const arm_code_t &raw_code) noexcept {
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


bool opcodes::arm::vfp::FCPYD(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FCPYS(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FCVTDS(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FCVTSD(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FDIVD(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FDIVS(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FLDD(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FLDMD(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FLDMS(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FLDMX(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FLDS(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FMACD(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FMACS(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FMDHR(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FMDLR(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FMRDH(const arm_code_t &raw_code) noexcept {
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

/*
bool opcodes::arm::vfp::(const arm_code_t &raw_code) noexcept {
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


bool opcodes::arm::vfp::FMRDL(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FMRS(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FMRX(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FMSCD(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FMSCS(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FMSR(const arm_code_t &raw_code) noexcept {
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


bool opcodes::arm::vfp::FMSTAT(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FMULD(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FMULS(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FMXR(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FNEGD(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FNEGS(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FNMACD(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FNMACS(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FNMSCD(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FNMSCS(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FNMULD(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FNMULS(const arm_code_t &raw_code) noexcept {
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


bool opcodes::arm::vfp::FSITOD(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FSITOS(const arm_code_t &raw_code) noexcept {
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


bool opcodes::arm::vfp::FSQRTD(const arm_code_t &raw_code) noexcept {
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


bool opcodes::arm::vfp::FSQRTS(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FSTD(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FSTMD(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FSTMS(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FSTMX(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FSTS(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FSUBD(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FSUBS(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FTOSID(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FTOSIS(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FTOUID(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FTOUIS(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FUITOD(const arm_code_t &raw_code) noexcept {
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

bool opcodes::arm::vfp::FUITOS(const arm_code_t &raw_code) noexcept {
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