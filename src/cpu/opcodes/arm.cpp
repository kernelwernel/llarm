#include "cpu/opcodes/opcodes.hpp"
#include "types.hpp"

[[nodiscard]] bool opcodes::ADC(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1)
    );
}

[[nodiscard]] bool opcodes::ADD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 0)
    );
}

[[nodiscard]] bool opcodes::AND(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 0)
    );
}

[[nodiscard]] bool opcodes::UNDEFINED(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(4) == 1)
    );
}

[[nodiscard]] bool opcodes::NOP(const arm_code_t &raw_code) noexcept {
    return (raw_code.none());
}

[[nodiscard]] bool opcodes::PSR(const arm_code_t &raw_code) noexcept {
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


[[nodiscard]] bool opcodes::B_BL(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 1)
    );
}

[[nodiscard]] bool opcodes::BIC(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 0)
    );
}

[[nodiscard]] bool opcodes::CDP(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(4) == 0)
    );
}

[[nodiscard]] bool opcodes::CMN(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::CMP(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::EOR(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1)
    );
}

[[nodiscard]] bool opcodes::LDC(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(20) == 0)
    );
}

[[nodiscard]] bool opcodes::LDM(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(20) == 1)
    );
}

[[nodiscard]] bool opcodes::LDM2(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::LDM3(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(20) == 1) &&
        (raw_code.test(15) == 1)
    );
}

[[nodiscard]] bool opcodes::LDR(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(20) == 1)
    );
}

[[nodiscard]] bool opcodes::LDRB(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(20) == 1)
    );
}

[[nodiscard]] bool opcodes::LDRBT(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1)
    );
}

[[nodiscard]] bool opcodes::LDRT(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1)
    );
}

[[nodiscard]] bool opcodes::MCR(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(20) == 0) &&
        (raw_code.test(4) == 1)
    );
}

[[nodiscard]] bool opcodes::MLA(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::MOV(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1)
    );
}

[[nodiscard]] bool opcodes::MRC(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(20) == 1) &&
        (raw_code.test(4) == 1)
    );
}

[[nodiscard]] bool opcodes::MRS(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::MSR_IMM(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::MSR_OPR(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::MUL(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::MVN(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 1)
    );
}

[[nodiscard]] bool opcodes::ORR(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 0)
    );
}

[[nodiscard]] bool opcodes::RSB(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 1)
    );
}

[[nodiscard]] bool opcodes::RSC(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 1)
    );
}

[[nodiscard]] bool opcodes::SBC(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 0)
    );
}

[[nodiscard]] bool opcodes::STC(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(20) == 0)
    );
}

[[nodiscard]] bool opcodes::STM1(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(20) == 0)
    );
}

[[nodiscard]] bool opcodes::STM2(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 0)
    );
}

[[nodiscard]] bool opcodes::STR(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(20) == 0)
    );
}

[[nodiscard]] bool opcodes::STRB(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(20) == 0)
    );
}

[[nodiscard]] bool opcodes::STRBT(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 0)
    );
}

[[nodiscard]] bool opcodes::STRT(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 0)
    );
}

[[nodiscard]] bool opcodes::SUB(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 0)
    );
}

[[nodiscard]] bool opcodes::SWI(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 1)
    );
}

[[nodiscard]] bool opcodes::SWP(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::SWPB(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::TEQ(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::TST(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::v4::STRH(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::v4::LDRH(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::v4::LDRSB(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::v4::LDRSH(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::v5::BKPT(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::v5::BLX1(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::v5::BLX2(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::v5::CLZ(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::v5v4t::BX(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::M::SMLAL(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::M::SMULL(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::M::UMLAL(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::M::UMULL(const arm_code_t &raw_code) noexcept {
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




[[nodiscard]] bool opcodes::DSP::LDRD(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::DSP::MCRR(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::DSP::MRRC(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::DSP::PLD(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::DSP::QADD(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::DSP::QDADD(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::DSP::QDSUB(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::DSP::QSUB(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::DSP::SMLA(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::DSP::SMLAL(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::DSP::SMLAW(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::DSP::SMUL(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::DSP::SMULW(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::DSP::STRD(const arm_code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(20) == 0) &&
        (raw_code.test(7) == 1) &&
        (raw_code.test(6) == 1) &&
        (raw_code.test(5) == 1) &&
        (raw_code.test(4) == 1) &&
    );
}



















[[nodiscard]] bool opcodes::VFP::FABSD(const arm_code_t &raw_code) noexcept {
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


[[nodiscard]] bool opcodes::VFP::FABSS(const arm_code_t &raw_code) noexcept {
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


[[nodiscard]] bool opcodes::VFP::FADDD(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FADDS(const arm_code_t &raw_code) noexcept {
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


[[nodiscard]] bool opcodes::VFP::FCMPD(const arm_code_t &raw_code) noexcept {
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


[[nodiscard]] bool opcodes::VFP::FCMPED(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FCMPES(const arm_code_t &raw_code) noexcept {
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


[[nodiscard]] bool opcodes::VFP::FCMPEZD(const arm_code_t &raw_code) noexcept {
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


[[nodiscard]] bool opcodes::VFP::FCMPEZS(const arm_code_t &raw_code) noexcept {
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


[[nodiscard]] bool opcodes::VFP::FCMPS(const arm_code_t &raw_code) noexcept {
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


[[nodiscard]] bool opcodes::VFP::FCMPZD(const arm_code_t &raw_code) noexcept {
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


[[nodiscard]] bool opcodes::VFP::FCMPZS(const arm_code_t &raw_code) noexcept {
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


[[nodiscard]] bool opcodes::VFP::FCPYD(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FCPYS(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FCVTDS(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FCVTSD(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FDIVD(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FDIVS(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FLDD(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FLDMD(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FLDMS(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FLDMX(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FLDS(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FMACD(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FMACS(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FMDHR(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FMDLR(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FMRDH(const arm_code_t &raw_code) noexcept {
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
[[nodiscard]] bool opcodes::VFP::(const arm_code_t &raw_code) noexcept {
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


[[nodiscard]] bool opcodes::VFP::FMRDL(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FMRS(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FMRX(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FMSCD(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FMSCS(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FMSR(const arm_code_t &raw_code) noexcept {
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


[[nodiscard]] bool opcodes::VFP::FMSTAT(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FMULD(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FMULS(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FMXR(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FNEGD(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FNEGS(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FNMACD(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FNMACS(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FNMSCD(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FNMSCS(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FNMULD(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FNMULS(const arm_code_t &raw_code) noexcept {
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


[[nodiscard]] bool opcodes::VFP::FSITOD(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FSITOS(const arm_code_t &raw_code) noexcept {
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


[[nodiscard]] bool opcodes::VFP::FSQRTD(const arm_code_t &raw_code) noexcept {
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


[[nodiscard]] bool opcodes::VFP::FSQRTS(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FSTD(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FSTMD(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FSTMS(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FSTMX(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FSTS(const arm_code_t &raw_code) noexcept {
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
        (raw_code.test(8) == 0) &&
    );
}

[[nodiscard]] bool opcodes::VFP::FSUBD(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FSUBS(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FTOSID(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FTOSIS(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FTOUID(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FTOUIS(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FUITOD(const arm_code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::VFP::FUITOS(const arm_code_t &raw_code) noexcept {
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