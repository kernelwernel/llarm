#include "../../core/registers.hpp"
#include "../instructions.hpp"

#include "shared/util.hpp"
#include "shared/types.hpp"


/**
 * if ConditionPassed(cond) then
 *     Rd = (Rm * Rs + Rn)[31:0]
 *     if S == 1 then
 *         N Flag = Rd[31]
 *         Z Flag = if Rd == 0 then 1 else 0
 *         C Flag = unaffected
 *         V Flag = unaffected
 */
void INSTRUCTIONS::arm::multiply::MLA(const arm_code_t &code) {
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rs = reg.read(code, 8, 11);
    const u32 Rn = reg.read(code, 12, 15);

    const u64 tmp = (Rm * Rs + Rn);
    const u32 Rd = shared::util::bit_range(tmp, 0, 31);

    reg.write(code, 16, 19, Rd);

    if (code.test(20)) {
        reg.write(id::cpsr::N, (shared::util::bit_fetch(Rd, 31)));
        reg.write(id::cpsr::Z, (Rd == 0));
    }
}


/**
 * if ConditionPassed(cond) then
 *     Rd = (Rm * Rs)[31:0]
 *     if S == 1 then
 *         N Flag = Rd[31]
 *         Z Flag = if Rd == 0 then 1 else 0
 *         C Flag = unaffected
 *         V Flag = unaffected
 */
void INSTRUCTIONS::arm::multiply::MUL(const arm_code_t &code) {
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rs = reg.read(code, 8, 11);

    const u64 tmp = (Rm * Rs);
    const u32 Rd = shared::util::bit_range(code, 0, 31);

    reg.write(code, 16, 19, Rd);

    if (code.test(20)) {
        reg.write(id::cpsr::N, (shared::util::bit_fetch(Rd, 31)));
        reg.write(id::cpsr::Z, (Rd == 0));
    }
}


/**
 * if ConditionPassed(cond) then
 *     RdLo = (Rm * Rs)[31:0] + RdLo // signed multiplication
 *     RdHi = (Rm * Rs)[63:32] + RdHi + CarryFrom((Rm * Rs)[31:0] + RdLo)
 *     if S == 1 then
 *         N Flag = RdHi[31]
 *         Z Flag = if (RdHi == 0) and (RdLo == 0) then 1 else 0
 *         C Flag = unaffected
 *         V Flag = unaffected
 */
void INSTRUCTIONS::arm::multiply::SMLAL(const arm_code_t &code) {
    const i32 Rm = static_cast<i32>(reg.read(code, 0, 3));
    const i32 Rs = static_cast<i32>(reg.read(code, 8, 11));

    const i64 result = (Rm * Rs);

    const u32 low_result = shared::util::bit_range(result, 0, 31);
    const u32 high_result = shared::util::bit_range(result, 32, 63);

    const id::reg RdLo_id = reg.fetch_reg_id(code, 12, 15);
    const id::reg RdHi_id = reg.fetch_reg_id(code, 16, 19);

    const u32 RdLo = low_result + reg.read(RdLo_id);
    const u32 RdHi = high_result + reg.read(RdHi_id) + operation.carry_add(low_result, reg.read(RdLo_id));

    reg.write(RdLo_id, RdLo);
    reg.write(RdHi_id, RdHi);

    if (code.test(20)) {
        reg.write(id::cpsr::N, (shared::util::bit_fetch(RdHi, 31)));
        reg.write(id::cpsr::Z, ((RdHi == 0) && (RdLo == 0)));
    }
}


/**
 * if ConditionPassed(cond) then
 *     RdHi = (Rm * Rs)[63:32] // Signed multiplication
 *     RdLo = (Rm * Rs)[31:0]
 *     if S == 1 then
 *         N Flag = RdHi[31]
 *         Z Flag = if (RdHi == 0) and (RdLo == 0) then 1 else 0
 *         C Flag = unaffected
 *         V Flag = unaffected
 */
void INSTRUCTIONS::arm::multiply::SMULL(const arm_code_t &code) {
    const i32 Rm = static_cast<i32>(reg.read(code, 0, 3));
    const i32 Rs = static_cast<i32>(reg.read(code, 8, 11));

    const i64 result = (Rm * Rs);

    const u32 RdLo = shared::util::bit_range(result, 0, 31);
    const i32 RdHi = shared::util::bit_range(result, 32, 63);
    
    reg.write(code, 12, 15, RdLo);
    reg.write(code, 16, 19, RdHi);

    if (code.test(20)) {
        reg.write(id::cpsr::N, (shared::util::bit_fetch(RdHi, 31)));
        reg.write(id::cpsr::Z, ((RdHi == 0) && (RdLo == 0)));
    }
}

/**
 * if ConditionPassed(cond) then
 *     RdLo = (Rm * Rs)[31:0] + RdLo // Unsigned multiplication
 *     RdHi = (Rm * Rs)[63:32] + RdHi + CarryFrom((Rm * Rs)[31:0] + RdLo)
 *     if S == 1 then
 *         N Flag = RdHi[31]
 *         Z Flag = if (RdHi == 0) and (RdLo == 0) then 1 else 0
 *         C Flag = unaffected
 *         V Flag = unaffected
 */
void INSTRUCTIONS::arm::multiply::UMLAL(const arm_code_t &code) {
    const i32 Rm = static_cast<i32>(reg.read(code, 0, 3));
    const i32 Rs = static_cast<i32>(reg.read(code, 8, 11));

    const i64 result = (Rm * Rs);

    const u32 low_result = shared::util::bit_range(result, 0, 31);
    const u32 high_result = shared::util::bit_range(result, 32, 63);

    const id::reg RdLo_id = reg.fetch_reg_id(code, 12, 15);
    const id::reg RdHi_id = reg.fetch_reg_id(code, 16, 19);

    const u32 RdLo = low_result + reg.read(RdLo_id);
    const u32 RdHi = high_result + reg.read(RdHi_id) + operation.carry_add(low_result, reg.read(RdLo_id));

    reg.write(RdLo_id, RdLo);
    reg.write(RdHi_id, RdHi);

    if (code.test(20)) {
        reg.write(id::cpsr::N, (shared::util::bit_fetch(RdHi, 31)));
        reg.write(id::cpsr::Z, ((RdHi == 0) && (RdLo == 0)));
    }
}


/**
 * if ConditionPassed(cond) then
 *     RdHi = (Rm * Rs)[63:32] // Unsigned multiplication
 *     RdLo = (Rm * Rs)[31:0]
 *     if S == 1 then
 *         N Flag = RdHi[31]
 *         Z Flag = if (RdHi == 0) and (RdLo == 0) then 1 else 0
 *         C Flag = unaffected
 *         V Flag = unaffected
 */
void INSTRUCTIONS::arm::multiply::UMULL(const arm_code_t &code) {
    const i32 Rm = static_cast<i32>(reg.read(code, 0, 3));
    const i32 Rs = static_cast<i32>(reg.read(code, 8, 11));

    const i64 result = (Rm * Rs);

    const u32 RdLo = shared::util::bit_range(result, 0, 31);
    const u32 RdHi = shared::util::bit_range(result, 32, 63);
    
    reg.write(code, 12, 15, RdLo);
    reg.write(code, 16, 19, RdHi);

    if (code.test(20)) {
        reg.write(id::cpsr::N, (shared::util::bit_fetch(RdHi, 31)));
        reg.write(id::cpsr::Z, ((RdHi == 0) && (RdLo == 0)));
    }
}