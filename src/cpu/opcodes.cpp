#include "cpu/opcodes.hpp"
#include "types.hpp"

[[nodiscard]] bool opcodes::ADC(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1)
    );
}

[[nodiscard]] bool opcodes::ADD(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 0)
    );
}

[[nodiscard]] bool opcodes::AND(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 0)
    );
}

[[nodiscard]] bool opcodes::UNDEFINED(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(4) == 1)
    );
}

[[nodiscard]] bool opcodes::NOP(const code_t &raw_code) noexcept {
    return (raw_code.none());
}

[[nodiscard]] bool opcodes::B_BL(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 1)
    );
}

[[nodiscard]] bool opcodes::BIC(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 0)
    );
}

[[nodiscard]] bool opcodes::CDP(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(4) == 0)
    );
}

[[nodiscard]] bool opcodes::CMN(const code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::CMP(const code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::EOR(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1)
    );
}

[[nodiscard]] bool opcodes::LDC(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(20) == 0)
    );
}

[[nodiscard]] bool opcodes::LDM(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(20) == 1)
    );
}

[[nodiscard]] bool opcodes::LDM2(const code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::LDM3(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(20) == 1) &&
        (raw_code.test(15) == 1)
    );
}

[[nodiscard]] bool opcodes::LDR(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(20) == 1)
    );
}

[[nodiscard]] bool opcodes::LDRB(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(20) == 1)
    );
}

[[nodiscard]] bool opcodes::LDRBT(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1)
    );
}

[[nodiscard]] bool opcodes::LDRT(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 1)
    );
}

[[nodiscard]] bool opcodes::MCR(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(20) == 0) &&
        (raw_code.test(4) == 1)
    );
}

[[nodiscard]] bool opcodes::MLA(const code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::MOV(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1)
    );
}

[[nodiscard]] bool opcodes::MRC(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(20) == 1) &&
        (raw_code.test(4) == 1)
    );
}

[[nodiscard]] bool opcodes::MRS(const code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::MSR_IMM(const code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::MSR_OPR(const code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::MUL(const code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::MVN(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 1)
    );
}

[[nodiscard]] bool opcodes::ORR(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 1) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 0)
    );
}

[[nodiscard]] bool opcodes::RSB(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 1)
    );
}

[[nodiscard]] bool opcodes::RSC(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 1)
    );
}

[[nodiscard]] bool opcodes::SBC(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 1) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 0)
    );
}

[[nodiscard]] bool opcodes::STC(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(20) == 0)
    );
}

[[nodiscard]] bool opcodes::STM1(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(20) == 0)
    );
}

[[nodiscard]] bool opcodes::STM2(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(25) == 0) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 0) &&
        (raw_code.test(20) == 0)
    );
}

[[nodiscard]] bool opcodes::STR(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(20) == 0)
    );
}

[[nodiscard]] bool opcodes::STRB(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(20) == 0)
    );
}

[[nodiscard]] bool opcodes::STRBT(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 0)
    );
}

[[nodiscard]] bool opcodes::STRT(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(22) == 0) &&
        (raw_code.test(21) == 1) &&
        (raw_code.test(20) == 0)
    );
}

[[nodiscard]] bool opcodes::SUB(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 0) &&
        (raw_code.test(26) == 0) &&
        (raw_code.test(24) == 0) &&
        (raw_code.test(23) == 0) &&
        (raw_code.test(22) == 1) &&
        (raw_code.test(21) == 0)
    );
}

[[nodiscard]] bool opcodes::SWI(const code_t &raw_code) noexcept {
    return (
        (raw_code.test(27) == 1) &&
        (raw_code.test(26) == 1) &&
        (raw_code.test(25) == 1) &&
        (raw_code.test(24) == 1)
    );
}

[[nodiscard]] bool opcodes::SWP(const code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::SWPB(const code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::TEQ(const code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::TST(const code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::v4::STRH(const code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::v4::LDRH(const code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::v4::LDRSB(const code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::v4::LDRSH(const code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::v5::BKPT(const code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::v5::BLX1(const code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::v5::BLX2(const code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::v5::CLZ(const code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::v5v4t::BX(const code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::M::SMLAL(const code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::M::SMULL(const code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::M::UMLAL(const code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::M::UMULL(const code_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::ADC(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::ADD1(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::ADD2(const thumbcode_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 0)
    );
}


[[nodiscard]] bool opcodes::thumb::ADD3(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::ADD4(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::ADD5(const thumbcode_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0)
    );
}

[[nodiscard]] bool opcodes::thumb::ADD6(const thumbcode_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 1)
    );
}

[[nodiscard]] bool opcodes::thumb::ADD7(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::AND(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::ASR1(const thumbcode_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 0)
    );
}

[[nodiscard]] bool opcodes::thumb::ASR2(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::B1(const thumbcode_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 1)
    );
}

[[nodiscard]] bool opcodes::thumb::B2(const thumbcode_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0)
    );
}

[[nodiscard]] bool opcodes::thumb::BIC(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::BL(const thumbcode_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0)
    );
}

[[nodiscard]] bool opcodes::thumb::BX(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::CMN(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::CMP1(const thumbcode_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 1)
    );
}

[[nodiscard]] bool opcodes::thumb::CMP2(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::CMP3(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::EOR(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::LDMIA(const thumbcode_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 1)
    );
}

[[nodiscard]] bool opcodes::thumb::LDR1(const thumbcode_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 1)
    );
}

[[nodiscard]] bool opcodes::thumb::LDR2(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::LDR3(const thumbcode_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 1)
    );
}

[[nodiscard]] bool opcodes::thumb::LDR4(const thumbcode_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 1)
    );
}

[[nodiscard]] bool opcodes::thumb::LDRB1(const thumbcode_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 1)
    );
}

[[nodiscard]] bool opcodes::thumb::LDRB2(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::LDRH1(const thumbcode_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 1)
    );
}

[[nodiscard]] bool opcodes::thumb::LDRH2(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::LDRSB(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::LDRSH(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::LSL1(const thumbcode_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0)
    );
}

[[nodiscard]] bool opcodes::thumb::LSL2(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::LSR1(const thumbcode_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 1)
    );
}

[[nodiscard]] bool opcodes::thumb::LSR2(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::MOV1(const thumbcode_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0)
    );
}

[[nodiscard]] bool opcodes::thumb::MOV2(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::MOV3(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::MUL(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::MVN(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::NEG(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::NOP(const thumbcode_t &raw_code) noexcept {
    return (raw_code.none());
}

[[nodiscard]] bool opcodes::thumb::ORR(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::POP(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::PUSH(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::ROR(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::SBC(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::STMIA(const thumbcode_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0)
    );
}

[[nodiscard]] bool opcodes::thumb::STR1(const thumbcode_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0)
    );
}

[[nodiscard]] bool opcodes::thumb::STR2(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::STR3(const thumbcode_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 0)
    );
}

[[nodiscard]] bool opcodes::thumb::STRB1(const thumbcode_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 0)
    );
}

[[nodiscard]] bool opcodes::thumb::STRB2(const thumbcode_t &raw_code) noexcept {
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


[[nodiscard]] bool opcodes::thumb::STRH1(const thumbcode_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 0) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 0)
    );
}

[[nodiscard]] bool opcodes::thumb::STRH2(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::SUB1(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::SUB2(const thumbcode_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 0) &&
        (raw_code.test(14) == 0) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 1) &&
        (raw_code.test(11) == 1)
    );
}

[[nodiscard]] bool opcodes::thumb::SUB3(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::SUB4(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::SWI(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::TST(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::v5::BKPT(const thumbcode_t &raw_code) noexcept {
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

[[nodiscard]] bool opcodes::thumb::v5::BLX1(const thumbcode_t &raw_code) noexcept {
    return (
        (raw_code.test(15) == 1) &&
        (raw_code.test(14) == 1) &&
        (raw_code.test(13) == 1) &&
        (raw_code.test(12) == 0) &&
        (raw_code.test(11) == 1)
    );
}

[[nodiscard]] bool opcodes::thumb::v5::BLX2(const thumbcode_t &raw_code) noexcept {
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