#include "../../core/registers.hpp"
#include "../instructions.hpp"
#include "../operation.hpp"

#include <llarm/shared/util.hpp>
#include <llarm/shared/types.hpp>

#include <limits>


/**
 * if ConditionPassed(cond) then
 *     Rd = (Rm * Rs + Rn)[31:0]
 *     if S == 1 then
 *         N Flag = Rd[31]
 *         Z Flag = if Rd == 0 then 1 else 0
 *         C Flag = unaffected
 *         V Flag = unaffected
 */
void INSTRUCTIONS::arm::multiply::MLA(const u32 code) {
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rs = reg.read(code, 8, 11);
    const u32 Rn = reg.read(code, 12, 15);

    const u64 tmp = ((Rm * Rs) + Rn);
    const u32 Rd = llarm::util::bit_range(tmp, 0, 31);

    reg.write(code, 16, 19, Rd);

    if (llarm::util::bit_fetch(code, 20)) {
        reg.write(id::cpsr::N, (llarm::util::bit_fetch(Rd, 31)));
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
void INSTRUCTIONS::arm::multiply::MUL(const u32 code) {
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rs = reg.read(code, 8, 11);

    const u64 tmp = (static_cast<u64>(Rm * Rs));
    const u32 Rd = llarm::util::bit_range(tmp, 0, 31);

    reg.write(code, 16, 19, Rd);

    if (llarm::util::bit_fetch(code, 20)) {
        reg.write(id::cpsr::N, (llarm::util::bit_fetch(Rd, 31)));
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
void INSTRUCTIONS::arm::multiply::SMLAL(const u32 code) {
    const i32 Rm = static_cast<i32>(reg.read(code, 0, 3));
    const i32 Rs = static_cast<i32>(reg.read(code, 8, 11));

    const i64 result = static_cast<i64>(Rm) * static_cast<i64>(Rs);

    const u32 low_result = llarm::util::bit_range(result, 0, 31);
    const u32 high_result = llarm::util::bit_range(result, 32, 63);

    const id::reg RdLo_id = reg.fetch_reg_id(code, 12, 15);
    const id::reg RdHi_id = reg.fetch_reg_id(code, 16, 19);

    const u32 RdLo = low_result + reg.read(RdLo_id);
    const u32 RdHi = high_result + reg.read(RdHi_id) + operation::carry_add(low_result, reg.read(RdLo_id));

    reg.write(RdLo_id, RdLo);
    reg.write(RdHi_id, RdHi);

    if (llarm::util::bit_fetch(code, 20)) {
        reg.write(id::cpsr::N, (llarm::util::bit_fetch(RdHi, 31)));
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
void INSTRUCTIONS::arm::multiply::SMULL(const u32 code) {
    const i32 Rm = static_cast<i32>(reg.read(code, 0, 3));
    const i32 Rs = static_cast<i32>(reg.read(code, 8, 11));

    const i64 result = static_cast<i64>(Rm) * static_cast<i64>(Rs);

    const u32 RdLo = llarm::util::bit_range(result, 0, 31);
    const i32 RdHi = llarm::util::bit_range<i32>(result, 32, 63);
    
    reg.write(code, 12, 15, RdLo);
    reg.write(code, 16, 19, static_cast<u32>(RdHi));

    if (llarm::util::bit_fetch(code, 20)) {
        reg.write(id::cpsr::N, (llarm::util::bit_fetch(static_cast<u32>(RdHi), 31)));
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
void INSTRUCTIONS::arm::multiply::UMLAL(const u32 code) {
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rs = reg.read(code, 8, 11);

    const u64 result = static_cast<u64>(Rm) * static_cast<u64>(Rs);

    const u32 low_result = llarm::util::bit_range(result, 0, 31);
    const u32 high_result = llarm::util::bit_range(result, 32, 63);

    const id::reg RdLo_id = reg.fetch_reg_id(code, 12, 15);
    const id::reg RdHi_id = reg.fetch_reg_id(code, 16, 19);

    const u32 RdLo = low_result + reg.read(RdLo_id);
    const u32 RdHi = high_result + reg.read(RdHi_id) + operation::carry_add(low_result, reg.read(RdLo_id));

    reg.write(RdLo_id, RdLo);
    reg.write(RdHi_id, RdHi);

    if (llarm::util::bit_fetch(code, 20)) {
        reg.write(id::cpsr::N, (llarm::util::bit_fetch(RdHi, 31)));
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
void INSTRUCTIONS::arm::multiply::UMULL(const u32 code) {
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rs = reg.read(code, 8, 11);

    const u64 result = static_cast<u64>(Rm) * static_cast<u64>(Rs);

    const u32 RdLo = llarm::util::bit_range(result, 0, 31);
    const u32 RdHi = llarm::util::bit_range(result, 32, 63);

    reg.write(code, 12, 15, RdLo);
    reg.write(code, 16, 19, RdHi);

    if (llarm::util::bit_fetch(code, 20)) {
        reg.write(id::cpsr::N, (llarm::util::bit_fetch(RdHi, 31)));
        reg.write(id::cpsr::Z, ((RdHi == 0) && (RdLo == 0)));
    }
}


/**
 * if ConditionPassed(cond) then
 *    if X == 1 then
 *         operand2 = Rs Rotate_Right 16
 *    else
 *         operand2 = Rs
 *    product1 = Rm[15:0] * operand2[15:0] // Signed multiplication
 *    product2 = Rm[31:16] * operand2[31:16] // Signed multiplication
 *    Rd = Rn + product1 + product2
 *    if OverflowFrom(Rn + product1 + product2) then
 *       Q Flag = 1
 */
void INSTRUCTIONS::arm::multiply::SMLAD(const u32 code) {
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rs = reg.read(code, 8, 11);
    const u32 Rn = reg.read(code, 12, 15);

    const bool X = llarm::util::bit_fetch(code, 5);
    const u32 operand2 = X ? llarm::util::rotr(Rs, 16) : Rs;

    const i64 product1 = static_cast<i64>(operation::sign_extend(Rm & 0xFFFF, 15)) * operation::sign_extend(operand2 & 0xFFFF, 15);
    const i64 product2 = static_cast<i64>(operation::sign_extend((Rm >> 16) & 0xFFFF, 15)) * operation::sign_extend((operand2 >> 16) & 0xFFFF, 15);

    const i64 wide_result = static_cast<i64>(static_cast<i32>(Rn)) + product1 + product2;

    reg.write(code, 16, 19, static_cast<u32>(wide_result));

    if ((wide_result > std::numeric_limits<i32>::max()) || (wide_result < std::numeric_limits<i32>::min())) {
        reg.write(id::cpsr::Q, true);
    }
}


/**
 * if ConditionPassed(cond) then
 *    if X == 1 then
 *         operand2 = Rs Rotate_Right 16
 *    else
 *         operand2 = Rs
 *    product1 = Rm[15:0] * operand2[15:0] // Signed multiplication
 *    product2 = Rm[31:16] * operand2[31:16] // Signed multiplication
 *    accvalue = (RdHi:RdLo)
 *    result = accvalue + product1 + product2 // Signed addition
 *    RdLo = result[31:0]
 *    RdHi = result[63:32]
 */
void INSTRUCTIONS::arm::multiply::SMLALD(const u32 code) {
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rs = reg.read(code, 8, 11);

    const bool X = llarm::util::bit_fetch(code, 5);
    const u32 operand2 = X ? llarm::util::rotr(Rs, 16) : Rs;

    const i64 product1 = static_cast<i64>(operation::sign_extend(Rm & 0xFFFF, 15)) * operation::sign_extend(operand2 & 0xFFFF, 15);
    const i64 product2 = static_cast<i64>(operation::sign_extend((Rm >> 16) & 0xFFFF, 15)) * operation::sign_extend((operand2 >> 16) & 0xFFFF, 15);

    const id::reg RdLo_id = reg.fetch_reg_id(code, 12, 15);
    const id::reg RdHi_id = reg.fetch_reg_id(code, 16, 19);

    const i64 accvalue = (static_cast<i64>(reg.read(RdHi_id)) << 32) | reg.read(RdLo_id);
    const i64 result = accvalue + product1 + product2;

    reg.write(RdLo_id, static_cast<u32>(result));
    reg.write(RdHi_id, static_cast<u32>(static_cast<u64>(result) >> 32));
}


/**
 * if ConditionPassed(cond) then
 *    if X == 1 then
 *         operand2 = Rs Rotate_Right 16
 *    else
 *         operand2 = Rs
 *    product1 = Rm[15:0] * operand2[15:0] // Signed multiplication
 *    product2 = Rm[31:16] * operand2[31:16] // Signed multiplication
 *    diffofproducts = product1 - product2 // Signed subtraction
 *    Rd = Rn + diffofproducts
 *    if OverflowFrom(Rn + diffofproducts) then
 *       Q Flag = 1
 */
void INSTRUCTIONS::arm::multiply::SMLSD(const u32 code) {
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rs = reg.read(code, 8, 11);
    const u32 Rn = reg.read(code, 12, 15);

    const bool X = llarm::util::bit_fetch(code, 5);
    const u32 operand2 = X ? llarm::util::rotr(Rs, 16) : Rs;

    const i64 product1 = static_cast<i64>(operation::sign_extend(Rm & 0xFFFF, 15)) * operation::sign_extend(operand2 & 0xFFFF, 15);
    const i64 product2 = static_cast<i64>(operation::sign_extend((Rm >> 16) & 0xFFFF, 15)) * operation::sign_extend((operand2 >> 16) & 0xFFFF, 15);

    const i64 wide_result = static_cast<i64>(static_cast<i32>(Rn)) + (product1 - product2);

    reg.write(code, 16, 19, static_cast<u32>(wide_result));

    if ((wide_result > std::numeric_limits<i32>::max()) || (wide_result < std::numeric_limits<i32>::min())) {
        reg.write(id::cpsr::Q, true);
    }
}


/**
 * if ConditionPassed(cond) then
 *    if X == 1 then
 *         operand2 = Rs Rotate_Right 16
 *    else
 *         operand2 = Rs
 *    product1 = Rm[15:0] * operand2[15:0] // Signed multiplication
 *    product2 = Rm[31:16] * operand2[31:16] // Signed multiplication
 *    accvalue = (RdHi:RdLo)
 *    result = accvalue + product1 - product2 // Signed subtraction
 *    RdLo = result[31:0]
 *    RdHi = result[63:32]
 */
void INSTRUCTIONS::arm::multiply::SMLSLD(const u32 code) {
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rs = reg.read(code, 8, 11);

    const bool X = llarm::util::bit_fetch(code, 5);
    const u32 operand2 = X ? llarm::util::rotr(Rs, 16) : Rs;

    const i64 product1 = static_cast<i64>(operation::sign_extend(Rm & 0xFFFF, 15)) * operation::sign_extend(operand2 & 0xFFFF, 15);
    const i64 product2 = static_cast<i64>(operation::sign_extend((Rm >> 16) & 0xFFFF, 15)) * operation::sign_extend((operand2 >> 16) & 0xFFFF, 15);

    const id::reg RdLo_id = reg.fetch_reg_id(code, 12, 15);
    const id::reg RdHi_id = reg.fetch_reg_id(code, 16, 19);

    const i64 accvalue = (static_cast<i64>(reg.read(RdHi_id)) << 32) | reg.read(RdLo_id);
    const i64 result = accvalue + (product1 - product2);

    reg.write(RdLo_id, static_cast<u32>(result));
    reg.write(RdHi_id, static_cast<u32>(static_cast<u64>(result) >> 32));
}


/**
 * if ConditionPassed(cond) then
 *    value = Rm * Rs // Signed multiplication
 *    if R == 1 then
 *       Rd = ((Rn<<32) + value + 0x80000000)[63:32]
 *    else
 *       Rd = ((Rn<<32) + value)[63:32]
 */
void INSTRUCTIONS::arm::multiply::SMMLA(const u32 code) {
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rs = reg.read(code, 8, 11);
    const u32 Rn = reg.read(code, 12, 15);

    const bool R = llarm::util::bit_fetch(code, 5);

    const i64 value = static_cast<i64>(static_cast<i32>(Rm)) * static_cast<i32>(Rs);
    const u64 rounding = R ? 0x80000000ULL : 0ULL;

    const u64 result = (static_cast<u64>(Rn) << 32) + static_cast<u64>(value) + rounding;

    reg.write(code, 16, 19, static_cast<u32>(result >> 32));
}


/**
 * if ConditionPassed(cond) then
 *    value = Rm * Rs // Signed multiplication
 *    if R == 1 then
 *       Rd = ((Rn<<32) - value + 0x80000000)[63:32]
 *    else
 *       Rd = ((Rn<<32) - value)[63:32]
 */
void INSTRUCTIONS::arm::multiply::SMMLS(const u32 code) {
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rs = reg.read(code, 8, 11);
    const u32 Rn = reg.read(code, 12, 15);

    const bool R = llarm::util::bit_fetch(code, 5);

    const i64 value = static_cast<i64>(static_cast<i32>(Rm)) * static_cast<i32>(Rs);
    const u64 rounding = R ? 0x80000000ULL : 0ULL;

    const u64 result = (static_cast<u64>(Rn) << 32) - static_cast<u64>(value) + rounding;

    reg.write(code, 16, 19, static_cast<u32>(result >> 32));
}


/**
 * if ConditionPassed(cond) then
 *    if R == 1 then
 *       value = Rm * Rs + 0x80000000 // Signed multiplication
 *    else
 *       value = Rm * Rs // Signed multiplication
 *    Rd = value[63:32]
 */
void INSTRUCTIONS::arm::multiply::SMMUL(const u32 code) {
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rs = reg.read(code, 8, 11);

    const bool R = llarm::util::bit_fetch(code, 5);

    const i64 product = static_cast<i64>(static_cast<i32>(Rm)) * static_cast<i32>(Rs);
    const u64 value = static_cast<u64>(product) + (R ? 0x80000000ULL : 0ULL);

    reg.write(code, 16, 19, static_cast<u32>(value >> 32));
}


/**
 * if ConditionPassed(cond) then
 *    if X == 1 then
 *         operand2 = Rs Rotate_Right 16
 *    else
 *         operand2 = Rs
 *    product1 = Rm[15:0] * operand2[15:0] // Signed multiplication
 *    product2 = Rm[31:16] * operand2[31:16] // Signed multiplication
 *    Rd = product1 + product2
 *    if OverflowFrom(product1 + product2) then
 *       Q Flag = 1
 */
void INSTRUCTIONS::arm::multiply::SMUAD(const u32 code) {
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rs = reg.read(code, 8, 11);

    const bool X = llarm::util::bit_fetch(code, 5);
    const u32 operand2 = X ? llarm::util::rotr(Rs, 16) : Rs;

    const i64 product1 = static_cast<i64>(operation::sign_extend(Rm & 0xFFFF, 15)) * operation::sign_extend(operand2 & 0xFFFF, 15);
    const i64 product2 = static_cast<i64>(operation::sign_extend((Rm >> 16) & 0xFFFF, 15)) * operation::sign_extend((operand2 >> 16) & 0xFFFF, 15);

    const i64 wide_result = product1 + product2;

    reg.write(code, 16, 19, static_cast<u32>(wide_result));

    if ((wide_result > std::numeric_limits<i32>::max()) || (wide_result < std::numeric_limits<i32>::min())) {
        reg.write(id::cpsr::Q, true);
    }
}


/**
 * if ConditionPassed(cond) then
 *    if X == 1 then
 *         operand2 = Rs Rotate_Right 16
 *    else
 *         operand2 = Rs
 *    product1 = Rm[15:0] * operand2[15:0] // Signed multiplication
 *    product2 = Rm[31:16] * operand2[31:16] // Signed multiplication
 *    Rd = product1 - product2 // Signed subtraction
 */
void INSTRUCTIONS::arm::multiply::SMUSD(const u32 code) {
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rs = reg.read(code, 8, 11);

    const bool X = llarm::util::bit_fetch(code, 5);
    const u32 operand2 = X ? llarm::util::rotr(Rs, 16) : Rs;

    const i64 product1 = static_cast<i64>(operation::sign_extend(Rm & 0xFFFF, 15)) * operation::sign_extend(operand2 & 0xFFFF, 15);
    const i64 product2 = static_cast<i64>(operation::sign_extend((Rm >> 16) & 0xFFFF, 15)) * operation::sign_extend((operand2 >> 16) & 0xFFFF, 15);

    reg.write(code, 16, 19, static_cast<u32>(product1 - product2));
}


/**
 * if ConditionPassed(cond) then
 *    result = Rm * Rs + RdLo + RdHi // Unsigned multiplication and additions
 *    RdLo = result[31:0]
 *    RdHi = result[63:32]
 */
void INSTRUCTIONS::arm::multiply::UMAAL(const u32 code) {
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rs = reg.read(code, 8, 11);

    const id::reg RdLo_id = reg.fetch_reg_id(code, 12, 15);
    const id::reg RdHi_id = reg.fetch_reg_id(code, 16, 19);

    const u64 result = (static_cast<u64>(Rm) * static_cast<u64>(Rs)) + reg.read(RdLo_id) + reg.read(RdHi_id);

    reg.write(RdLo_id, static_cast<u32>(result));
    reg.write(RdHi_id, static_cast<u32>(result >> 32));
}