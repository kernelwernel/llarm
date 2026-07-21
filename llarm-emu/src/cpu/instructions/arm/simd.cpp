#include "../../core/registers.hpp"
#include "../instructions.hpp"
#include "../operation.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>


/**
 * if ConditionPassed(cond) then
 *     sum = Rn[15:0] + Rm[15:0] // Signed addition
 *     Rd[15:0] = sum[15:0]
 *     GE[1:0] = if sum >= 0 then 0b11 else 0
 *     sum = Rn[31:16] + Rm[31:16] // Signed addition
 *     Rd[31:16] = sum[15:0]
 *     GE[3:2] = if sum >= 0 then 0b11 else 0
 */
void INSTRUCTIONS::arm::simd::SADD16(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const i32 sum_lo = operation::sign_extend(Rn & 0xFFFF, 15) + operation::sign_extend(Rm & 0xFFFF, 15);
    const i32 sum_hi = operation::sign_extend((Rn >> 16) & 0xFFFF, 15) + operation::sign_extend((Rm >> 16) & 0xFFFF, 15);

    reg.write(Rd_id, (static_cast<u32>(sum_lo) & 0xFFFF) | ((static_cast<u32>(sum_hi) & 0xFFFF) << 16));
    reg.write(id::cpsr::GE, static_cast<u8>((sum_lo >= 0 ? 0b0011 : 0) | (sum_hi >= 0 ? 0b1100 : 0)));
}


/**
 * if ConditionPassed(cond) then
 *     sum = Rn[7:0] + Rm[7:0] // Signed addition
 *     Rd[7:0] = sum[7:0]
 *     GE[0] = if sum >= 0 then 1 else 0
 *     sum = Rn[15:8] + Rm[15:8] // Signed addition
 *     Rd[15:8] = sum[7:0]
 *     GE[1] = if sum >= 0 then 1 else 0
 *     sum = Rn[23:16] + Rm[23:16] // Signed addition
 *     Rd[23:16] = sum[7:0]
 *     GE[2] = if sum >= 0 then 1 else 0
 *     sum = Rn[31:24] + Rm[31:24] // Signed addition
 *     Rd[31:24] = sum[7:0]
 *     GE[3] = if sum >= 0 then 1 else 0
 */
void INSTRUCTIONS::arm::simd::SADD8(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const i32 sum0 = operation::sign_extend(Rn & 0xFF, 7) + operation::sign_extend(Rm & 0xFF, 7);
    const i32 sum1 = operation::sign_extend((Rn >> 8) & 0xFF, 7) + operation::sign_extend((Rm >> 8) & 0xFF, 7);
    const i32 sum2 = operation::sign_extend((Rn >> 16) & 0xFF, 7) + operation::sign_extend((Rm >> 16) & 0xFF, 7);
    const i32 sum3 = operation::sign_extend((Rn >> 24) & 0xFF, 7) + operation::sign_extend((Rm >> 24) & 0xFF, 7);

    const u32 result = (
        (static_cast<u32>(sum0) & 0xFF) |
        ((static_cast<u32>(sum1) & 0xFF) << 8) |
        ((static_cast<u32>(sum2) & 0xFF) << 16) |
        ((static_cast<u32>(sum3) & 0xFF) << 24)
    );

    reg.write(Rd_id, result);

    reg.write(id::cpsr::GE, static_cast<u8>(
        (sum0 >= 0 ? 0b0001 : 0) |
        (sum1 >= 0 ? 0b0010 : 0) |
        (sum2 >= 0 ? 0b0100 : 0) |
        (sum3 >= 0 ? 0b1000 : 0)
    ));
}


/**
 * if ConditionPassed(cond) then
 *     sum = Rn[31:16] + Rm[15:0] // Signed addition
 *     Rd[31:16] = sum[15:0]
 *     GE[3:2] = if sum >= 0 then 0b11 else 0
 *     diff = Rn[15:0] - Rm[31:16] // Signed subtraction
 *     Rd[15:0] = diff[15:0]
 *     GE[1:0] = if diff >= 0 then 0b11 else 0
 */
void INSTRUCTIONS::arm::simd::SADDSUBX(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const i32 sum_hi = operation::sign_extend((Rn >> 16) & 0xFFFF, 15) + operation::sign_extend(Rm & 0xFFFF, 15);
    const i32 diff_lo = operation::sign_extend(Rn & 0xFFFF, 15) - operation::sign_extend((Rm >> 16) & 0xFFFF, 15);

    reg.write(Rd_id, (static_cast<u32>(diff_lo) & 0xFFFF) | ((static_cast<u32>(sum_hi) & 0xFFFF) << 16));
    reg.write(id::cpsr::GE, static_cast<u8>((diff_lo >= 0 ? 0b0011 : 0) | (sum_hi >= 0 ? 0b1100 : 0)));
}


/**
 * if ConditionPassed(cond) then
 *     diff = Rn[15:0] - Rm[15:0] // Signed subtraction
 *     Rd[15:0] = diff[15:0]
 *     GE[1:0] = if diff >= 0 then 0b11 else 0
 *     diff = Rn[31:16] - Rm[31:16] // Signed subtraction
 *     Rd[31:16] = diff[15:0]
 *     GE[3:2] = if diff >= 0 then 0b11 else 0
 */
void INSTRUCTIONS::arm::simd::SSUB16(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const i32 diff_lo = operation::sign_extend(Rn & 0xFFFF, 15) - operation::sign_extend(Rm & 0xFFFF, 15);
    const i32 diff_hi = operation::sign_extend((Rn >> 16) & 0xFFFF, 15) - operation::sign_extend((Rm >> 16) & 0xFFFF, 15);

    reg.write(Rd_id, (static_cast<u32>(diff_lo) & 0xFFFF) | ((static_cast<u32>(diff_hi) & 0xFFFF) << 16));
    reg.write(id::cpsr::GE, static_cast<u8>((diff_lo >= 0 ? 0b0011 : 0) | (diff_hi >= 0 ? 0b1100 : 0)));
}


/**
 * if ConditionPassed(cond) then
 *     diff = Rn[7:0] - Rm[7:0] // Signed subtraction
 *     Rd[7:0] = diff[7:0]
 *     GE[0] = if diff >= 0 then 1 else 0
 *     diff = Rn[15:8] - Rm[15:8] // Signed subtraction
 *     Rd[15:8] = diff[7:0]
 *     GE[1] = if diff >= 0 then 1 else 0
 *     diff = Rn[23:16] - Rm[23:16] // Signed subtraction
 *     Rd[23:16] = diff[7:0]
 *     GE[2] = if diff >= 0 then 1 else 0
 *     diff = Rn[31:24] - Rm[31:24] // Signed subtraction
 *     Rd[31:24] = diff[7:0]
 *     GE[3] = if diff >= 0 then 1 else 0
 */
void INSTRUCTIONS::arm::simd::SSUB8(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const i32 diff0 = operation::sign_extend(Rn & 0xFF, 7) - operation::sign_extend(Rm & 0xFF, 7);
    const i32 diff1 = operation::sign_extend((Rn >> 8) & 0xFF, 7) - operation::sign_extend((Rm >> 8) & 0xFF, 7);
    const i32 diff2 = operation::sign_extend((Rn >> 16) & 0xFF, 7) - operation::sign_extend((Rm >> 16) & 0xFF, 7);
    const i32 diff3 = operation::sign_extend((Rn >> 24) & 0xFF, 7) - operation::sign_extend((Rm >> 24) & 0xFF, 7);

    const u32 result = (
        (static_cast<u32>(diff0) & 0xFF) |
        ((static_cast<u32>(diff1) & 0xFF) << 8) |
        ((static_cast<u32>(diff2) & 0xFF) << 16) |
        ((static_cast<u32>(diff3) & 0xFF) << 24)
    );

    reg.write(Rd_id, result);

    reg.write(id::cpsr::GE, static_cast<u8>(
        (diff0 >= 0 ? 0b0001 : 0) |
        (diff1 >= 0 ? 0b0010 : 0) |
        (diff2 >= 0 ? 0b0100 : 0) |
        (diff3 >= 0 ? 0b1000 : 0)
    ));
}


/**
 * if ConditionPassed(cond) then
 *     diff = Rn[31:16] - Rm[15:0] // Signed subtraction
 *     Rd[31:16] = diff[15:0]
 *     GE[3:2] = if diff >= 0 then 0b11 else 0
 *     sum = Rn[15:0] + Rm[31:16] // Signed addition
 *     Rd[15:0] = sum[15:0]
 *     GE[1:0] = if sum >= 0 then 0b11 else 0
 */
void INSTRUCTIONS::arm::simd::SSUBADDX(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const i32 diff_hi = operation::sign_extend((Rn >> 16) & 0xFFFF, 15) - operation::sign_extend(Rm & 0xFFFF, 15);
    const i32 sum_lo = operation::sign_extend(Rn & 0xFFFF, 15) + operation::sign_extend((Rm >> 16) & 0xFFFF, 15);

    reg.write(Rd_id, (static_cast<u32>(sum_lo) & 0xFFFF) | ((static_cast<u32>(diff_hi) & 0xFFFF) << 16));
    reg.write(id::cpsr::GE, static_cast<u8>((sum_lo >= 0 ? 0b0011 : 0) | (diff_hi >= 0 ? 0b1100 : 0)));
}


/**
 * if ConditionPassed(cond) then
 *     sum = Rn[15:0] + Rm[15:0] // Signed addition
 *     Rd[15:0] = sum[16:1]
 *     sum = Rn[31:16] + Rm[31:16] // Signed addition
 *     Rd[31:16] = sum[16:1]
 */
void INSTRUCTIONS::arm::simd::SHADD16(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const i32 sum_lo = (operation::sign_extend(Rn & 0xFFFF, 15) + operation::sign_extend(Rm & 0xFFFF, 15)) >> 1;
    const i32 sum_hi = (operation::sign_extend((Rn >> 16) & 0xFFFF, 15) + operation::sign_extend((Rm >> 16) & 0xFFFF, 15)) >> 1;

    reg.write(Rd_id, (static_cast<u32>(sum_lo) & 0xFFFF) | ((static_cast<u32>(sum_hi) & 0xFFFF) << 16));
}


/**
 * if ConditionPassed(cond) then
 *     sum = Rn[7:0] + Rm[7:0] // Signed addition
 *     Rd[7:0] = sum[8:1]
 *     sum = Rn[15:8] + Rm[15:8] // Signed addition
 *     Rd[15:8] = sum[8:1]
 *     sum = Rn[23:16] + Rm[23:16] // Signed addition
 *     Rd[23:16] = sum[8:1]
 *     sum = Rn[31:24] + Rm[31:24] // Signed addition
 *     Rd[31:24] = sum[8:1]
 */
void INSTRUCTIONS::arm::simd::SHADD8(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const i32 sum0 = (operation::sign_extend(Rn & 0xFF, 7) + operation::sign_extend(Rm & 0xFF, 7)) >> 1;
    const i32 sum1 = (operation::sign_extend((Rn >> 8) & 0xFF, 7) + operation::sign_extend((Rm >> 8) & 0xFF, 7)) >> 1;
    const i32 sum2 = (operation::sign_extend((Rn >> 16) & 0xFF, 7) + operation::sign_extend((Rm >> 16) & 0xFF, 7)) >> 1;
    const i32 sum3 = (operation::sign_extend((Rn >> 24) & 0xFF, 7) + operation::sign_extend((Rm >> 24) & 0xFF, 7)) >> 1;

    reg.write(Rd_id, (
        (static_cast<u32>(sum0) & 0xFF) |
        ((static_cast<u32>(sum1) & 0xFF) << 8) |
        ((static_cast<u32>(sum2) & 0xFF) << 16) |
        ((static_cast<u32>(sum3) & 0xFF) << 24)
    ));
}


/**
 * if ConditionPassed(cond) then
 *     sum = Rn[31:16] + Rm[15:0] // Signed addition
 *     Rd[31:16] = sum[16:1]
 *     diff = Rn[15:0] - Rm[31:16] // Signed subtraction
 *     Rd[15:0] = diff[16:1]
 */
void INSTRUCTIONS::arm::simd::SHADDSUBX(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const i32 sum_hi = (operation::sign_extend((Rn >> 16) & 0xFFFF, 15) + operation::sign_extend(Rm & 0xFFFF, 15)) >> 1;
    const i32 diff_lo = (operation::sign_extend(Rn & 0xFFFF, 15) - operation::sign_extend((Rm >> 16) & 0xFFFF, 15)) >> 1;

    reg.write(Rd_id, (static_cast<u32>(diff_lo) & 0xFFFF) | ((static_cast<u32>(sum_hi) & 0xFFFF) << 16));
}


/**
 * if ConditionPassed(cond) then
 *     diff = Rn[15:0] - Rm[15:0] // Signed subtraction
 *     Rd[15:0] = diff[16:1]
 *     diff = Rn[31:16] - Rm[31:16] // Signed subtraction
 *     Rd[31:16] = diff[16:1]
 */
void INSTRUCTIONS::arm::simd::SHSUB16(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const i32 diff_lo = (operation::sign_extend(Rn & 0xFFFF, 15) - operation::sign_extend(Rm & 0xFFFF, 15)) >> 1;
    const i32 diff_hi = (operation::sign_extend((Rn >> 16) & 0xFFFF, 15) - operation::sign_extend((Rm >> 16) & 0xFFFF, 15)) >> 1;

    reg.write(Rd_id, (static_cast<u32>(diff_lo) & 0xFFFF) | ((static_cast<u32>(diff_hi) & 0xFFFF) << 16));
}


/**
 * if ConditionPassed(cond) then
 *     diff = Rn[7:0] - Rm[7:0] // Signed subtraction
 *     Rd[7:0] = diff[8:1]
 *     diff = Rn[15:8] - Rm[15:8] // Signed subtraction
 *     Rd[15:8] = diff[8:1]
 *     diff = Rn[23:16] - Rm[23:16] // Signed subtraction
 *     Rd[23:16] = diff[8:1]
 *     diff = Rn[31:24] - Rm[31:24] // Signed subtraction
 *     Rd[31:24] = diff[8:1]
 */
void INSTRUCTIONS::arm::simd::SHSUB8(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const i32 diff0 = (operation::sign_extend(Rn & 0xFF, 7) - operation::sign_extend(Rm & 0xFF, 7)) >> 1;
    const i32 diff1 = (operation::sign_extend((Rn >> 8) & 0xFF, 7) - operation::sign_extend((Rm >> 8) & 0xFF, 7)) >> 1;
    const i32 diff2 = (operation::sign_extend((Rn >> 16) & 0xFF, 7) - operation::sign_extend((Rm >> 16) & 0xFF, 7)) >> 1;
    const i32 diff3 = (operation::sign_extend((Rn >> 24) & 0xFF, 7) - operation::sign_extend((Rm >> 24) & 0xFF, 7)) >> 1;

    reg.write(Rd_id, (
        (static_cast<u32>(diff0) & 0xFF) |
        ((static_cast<u32>(diff1) & 0xFF) << 8) |
        ((static_cast<u32>(diff2) & 0xFF) << 16) |
        ((static_cast<u32>(diff3) & 0xFF) << 24)
    ));
}


/**
 * if ConditionPassed(cond) then
 *     diff = Rn[31:16] - Rm[15:0] // Signed subtraction
 *     Rd[31:16] = diff[16:1]
 *     sum = Rn[15:0] + Rm[31:16] // Signed addition
 *     Rd[15:0] = sum[16:1]
 */
void INSTRUCTIONS::arm::simd::SHSUBADDX(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const i32 diff_hi = (operation::sign_extend((Rn >> 16) & 0xFFFF, 15) - operation::sign_extend(Rm & 0xFFFF, 15)) >> 1;
    const i32 sum_lo = (operation::sign_extend(Rn & 0xFFFF, 15) + operation::sign_extend((Rm >> 16) & 0xFFFF, 15)) >> 1;

    reg.write(Rd_id, (static_cast<u32>(sum_lo) & 0xFFFF) | ((static_cast<u32>(diff_hi) & 0xFFFF) << 16));
}


/**
 * if ConditionPassed(cond) then
 *     Rd[15:0] = SignedSat(Rn[15:0] + Rm[15:0], 16)
 *     Rd[31:16] = SignedSat(Rn[31:16] + Rm[31:16], 16)
 */
void INSTRUCTIONS::arm::simd::QADD16(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const i32 sum_lo = operation::sign_extend(Rn & 0xFFFF, 15) + operation::sign_extend(Rm & 0xFFFF, 15);
    const i32 sum_hi = operation::sign_extend((Rn >> 16) & 0xFFFF, 15) + operation::sign_extend((Rm >> 16) & 0xFFFF, 15);

    const u32 lo = static_cast<u32>(operation::signed_sat(static_cast<u32>(sum_lo), 16)) & 0xFFFF;
    const u32 hi = static_cast<u32>(operation::signed_sat(static_cast<u32>(sum_hi), 16)) & 0xFFFF;

    reg.write(Rd_id, lo | (hi << 16));
}


/**
 * if ConditionPassed(cond) then
 *     Rd[7:0] = SignedSat(Rn[7:0] + Rm[7:0], 8)
 *     Rd[15:8] = SignedSat(Rn[15:8] + Rm[15:8], 8)
 *     Rd[23:16] = SignedSat(Rn[23:16] + Rm[23:16], 8)
 *     Rd[31:24] = SignedSat(Rn[31:24] + Rm[31:24], 8)
 */
void INSTRUCTIONS::arm::simd::QADD8(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const i32 sum0 = operation::sign_extend(Rn & 0xFF, 7) + operation::sign_extend(Rm & 0xFF, 7);
    const i32 sum1 = operation::sign_extend((Rn >> 8) & 0xFF, 7) + operation::sign_extend((Rm >> 8) & 0xFF, 7);
    const i32 sum2 = operation::sign_extend((Rn >> 16) & 0xFF, 7) + operation::sign_extend((Rm >> 16) & 0xFF, 7);
    const i32 sum3 = operation::sign_extend((Rn >> 24) & 0xFF, 7) + operation::sign_extend((Rm >> 24) & 0xFF, 7);

    const u32 b0 = static_cast<u32>(operation::signed_sat(static_cast<u32>(sum0), 8)) & 0xFF;
    const u32 b1 = static_cast<u32>(operation::signed_sat(static_cast<u32>(sum1), 8)) & 0xFF;
    const u32 b2 = static_cast<u32>(operation::signed_sat(static_cast<u32>(sum2), 8)) & 0xFF;
    const u32 b3 = static_cast<u32>(operation::signed_sat(static_cast<u32>(sum3), 8)) & 0xFF;

    reg.write(Rd_id, b0 | (b1 << 8) | (b2 << 16) | (b3 << 24));
}


/**
 * if ConditionPassed(cond) then
 *     Rd[31:16] = SignedSat(Rn[31:16] + Rm[15:0], 16)
 *     Rd[15:0] = SignedSat(Rn[15:0] - Rm[31:16], 16)
 */
void INSTRUCTIONS::arm::simd::QADDSUBX(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const i32 sum_hi = operation::sign_extend((Rn >> 16) & 0xFFFF, 15) + operation::sign_extend(Rm & 0xFFFF, 15);
    const i32 diff_lo = operation::sign_extend(Rn & 0xFFFF, 15) - operation::sign_extend((Rm >> 16) & 0xFFFF, 15);

    const u32 hi = static_cast<u32>(operation::signed_sat(static_cast<u32>(sum_hi), 16)) & 0xFFFF;
    const u32 lo = static_cast<u32>(operation::signed_sat(static_cast<u32>(diff_lo), 16)) & 0xFFFF;

    reg.write(Rd_id, lo | (hi << 16));
}


/**
 * if ConditionPassed(cond) then
 *     Rd[15:0] = SignedSat(Rn[15:0] - Rm[15:0], 16)
 *     Rd[31:16] = SignedSat(Rn[31:16] - Rm[31:16], 16)
 */
void INSTRUCTIONS::arm::simd::QSUB16(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const i32 diff_lo = operation::sign_extend(Rn & 0xFFFF, 15) - operation::sign_extend(Rm & 0xFFFF, 15);
    const i32 diff_hi = operation::sign_extend((Rn >> 16) & 0xFFFF, 15) - operation::sign_extend((Rm >> 16) & 0xFFFF, 15);

    const u32 lo = static_cast<u32>(operation::signed_sat(static_cast<u32>(diff_lo), 16)) & 0xFFFF;
    const u32 hi = static_cast<u32>(operation::signed_sat(static_cast<u32>(diff_hi), 16)) & 0xFFFF;

    reg.write(Rd_id, lo | (hi << 16));
}


/**
 * if ConditionPassed(cond) then
 *     Rd[7:0] = SignedSat(Rn[7:0] - Rm[7:0], 8)
 *     Rd[15:8] = SignedSat(Rn[15:8] - Rm[15:8], 8)
 *     Rd[23:16] = SignedSat(Rn[23:16] - Rm[23:16], 8)
 *     Rd[31:24] = SignedSat(Rn[31:24] - Rm[31:24], 8)
 */
void INSTRUCTIONS::arm::simd::QSUB8(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const i32 diff0 = operation::sign_extend(Rn & 0xFF, 7) - operation::sign_extend(Rm & 0xFF, 7);
    const i32 diff1 = operation::sign_extend((Rn >> 8) & 0xFF, 7) - operation::sign_extend((Rm >> 8) & 0xFF, 7);
    const i32 diff2 = operation::sign_extend((Rn >> 16) & 0xFF, 7) - operation::sign_extend((Rm >> 16) & 0xFF, 7);
    const i32 diff3 = operation::sign_extend((Rn >> 24) & 0xFF, 7) - operation::sign_extend((Rm >> 24) & 0xFF, 7);

    const u32 b0 = static_cast<u32>(operation::signed_sat(static_cast<u32>(diff0), 8)) & 0xFF;
    const u32 b1 = static_cast<u32>(operation::signed_sat(static_cast<u32>(diff1), 8)) & 0xFF;
    const u32 b2 = static_cast<u32>(operation::signed_sat(static_cast<u32>(diff2), 8)) & 0xFF;
    const u32 b3 = static_cast<u32>(operation::signed_sat(static_cast<u32>(diff3), 8)) & 0xFF;

    reg.write(Rd_id, b0 | (b1 << 8) | (b2 << 16) | (b3 << 24));
}


/**
 * if ConditionPassed(cond) then
 *     Rd[31:16] = SignedSat(Rn[31:16] - Rm[15:0], 16)
 *     Rd[15:0] = SignedSat(Rn[15:0] + Rm[31:16], 16)
 */
void INSTRUCTIONS::arm::simd::QSUBADDX(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const i32 diff_hi = operation::sign_extend((Rn >> 16) & 0xFFFF, 15) - operation::sign_extend(Rm & 0xFFFF, 15);
    const i32 sum_lo = operation::sign_extend(Rn & 0xFFFF, 15) + operation::sign_extend((Rm >> 16) & 0xFFFF, 15);

    const u32 hi = static_cast<u32>(operation::signed_sat(static_cast<u32>(diff_hi), 16)) & 0xFFFF;
    const u32 lo = static_cast<u32>(operation::signed_sat(static_cast<u32>(sum_lo), 16)) & 0xFFFF;

    reg.write(Rd_id, lo | (hi << 16));
}


/**
 * if ConditionPassed(cond) then
 *     Rd[15:0] = Rn[15:0] + Rm[15:0]
 *     GE[1:0] = if CarryFrom16(Rn[15:0] + Rm[15:0]) == 1 then 0b11 else 0
 *     Rd[31:16] = Rn[31:16] + Rm[31:16]
 *     GE[3:2] = if CarryFrom16(Rn[31:16] + Rm[31:16]) == 1 then 0b11 else 0
 */
void INSTRUCTIONS::arm::simd::UADD16(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const u32 sum_lo = (Rn & 0xFFFF) + (Rm & 0xFFFF);
    const u32 sum_hi = ((Rn >> 16) & 0xFFFF) + ((Rm >> 16) & 0xFFFF);

    reg.write(Rd_id, (sum_lo & 0xFFFF) | ((sum_hi & 0xFFFF) << 16));
    reg.write(id::cpsr::GE, static_cast<u8>((sum_lo >= 0x10000 ? 0b0011 : 0) | (sum_hi >= 0x10000 ? 0b1100 : 0)));
}


/**
 * if ConditionPassed(cond) then
 *     Rd[7:0] = Rn[7:0] + Rm[7:0]
 *     GE[0] = CarryFrom8(Rn[7:0] + Rm[7:0])
 *     Rd[15:8] = Rn[15:8] + Rm[15:8]
 *     GE[1] = CarryFrom8(Rn[15:8] + Rm[15:8])
 *     Rd[23:16] = Rn[23:16] + Rm[23:16]
 *     GE[2] = CarryFrom8(Rn[23:16] + Rm[23:16])
 *     Rd[31:24] = Rn[31:24] + Rm[31:24]
 *     GE[3] = CarryFrom8(Rn[31:24] + Rm[31:24])
 */
void INSTRUCTIONS::arm::simd::UADD8(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const u32 sum0 = (Rn & 0xFF) + (Rm & 0xFF);
    const u32 sum1 = ((Rn >> 8) & 0xFF) + ((Rm >> 8) & 0xFF);
    const u32 sum2 = ((Rn >> 16) & 0xFF) + ((Rm >> 16) & 0xFF);
    const u32 sum3 = ((Rn >> 24) & 0xFF) + ((Rm >> 24) & 0xFF);

    reg.write(Rd_id, (
        (sum0 & 0xFF) |
        ((sum1 & 0xFF) << 8) |
        ((sum2 & 0xFF) << 16) |
        ((sum3 & 0xFF) << 24)
    ));

    reg.write(id::cpsr::GE, static_cast<u8>(
        (sum0 >= 0x100 ? 0b0001 : 0) |
        (sum1 >= 0x100 ? 0b0010 : 0) |
        (sum2 >= 0x100 ? 0b0100 : 0) |
        (sum3 >= 0x100 ? 0b1000 : 0)
    ));
}


/**
 * if ConditionPassed(cond) then
 *     sum = Rn[31:16] + Rm[15:0] // unsigned addition
 *     Rd[31:16] = sum[15:0]
 *     GE[3:2] = if CarryFrom16(Rn[31:16] + Rm[15:0]) then 0b11 else 0
 *     diff = Rn[15:0] - Rm[31:16] // unsigned subtraction
 *     Rd[15:0] = diff[15:0]
 *     GE[1:0] = if BorrowFrom(Rn[15:0] - Rm[31:16]) then 0b11 else 0
 */
void INSTRUCTIONS::arm::simd::UADDSUBX(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const u32 Rn_lo = Rn & 0xFFFF;
    const u32 Rn_hi = (Rn >> 16) & 0xFFFF;
    const u32 Rm_lo = Rm & 0xFFFF;
    const u32 Rm_hi = (Rm >> 16) & 0xFFFF;

    const u32 sum_hi = Rn_hi + Rm_lo;
    const i32 diff_lo = static_cast<i32>(Rn_lo) - static_cast<i32>(Rm_hi);
    const bool borrow_lo = (Rn_lo < Rm_hi);

    reg.write(Rd_id, (static_cast<u32>(diff_lo) & 0xFFFF) | ((sum_hi & 0xFFFF) << 16));
    reg.write(id::cpsr::GE, static_cast<u8>((borrow_lo ? 0b0011 : 0) | (sum_hi >= 0x10000 ? 0b1100 : 0)));
}


/**
 * if ConditionPassed(cond) then
 *     Rd[15:0] = Rn[15:0] - Rm[15:0]
 *     GE[1:0] = if BorrowFrom(Rn[15:0] - Rm[15:0]) then 0 else 0b11
 *     Rd[31:16] = Rn[31:16] - Rm[31:16]
 *     GE[3:2] = if BorrowFrom(Rn[31:16] - Rm[31:16]) then 0 else 0b11
 */
void INSTRUCTIONS::arm::simd::USUB16(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const u32 Rn_lo = Rn & 0xFFFF;
    const u32 Rn_hi = (Rn >> 16) & 0xFFFF;
    const u32 Rm_lo = Rm & 0xFFFF;
    const u32 Rm_hi = (Rm >> 16) & 0xFFFF;

    const i32 diff_lo = static_cast<i32>(Rn_lo) - static_cast<i32>(Rm_lo);
    const i32 diff_hi = static_cast<i32>(Rn_hi) - static_cast<i32>(Rm_hi);

    reg.write(Rd_id, (static_cast<u32>(diff_lo) & 0xFFFF) | ((static_cast<u32>(diff_hi) & 0xFFFF) << 16));
    reg.write(id::cpsr::GE, static_cast<u8>((diff_lo >= 0 ? 0b0011 : 0) | (diff_hi >= 0 ? 0b1100 : 0)));
}


/**
 * if ConditionPassed(cond) then
 *     Rd[7:0] = Rn[7:0] - Rm[7:0]
 *     GE[0] = NOT BorrowFrom(Rn[7:0] - Rm[7:0])
 *     Rd[15:8] = Rn[15:8] - Rm[15:8]
 *     GE[1] = NOT BorrowFrom(Rn[15:8] - Rm[15:8])
 *     Rd[23:16] = Rn[23:16] - Rm[23:16]
 *     GE[2] = NOT BorrowFrom(Rn[23:16] - Rm[23:16])
 *     Rd[31:24] = Rn[31:24] - Rm[31:24]
 *     GE[3] = NOT BorrowFrom(Rn[31:24] - Rm[31:24])
 */
void INSTRUCTIONS::arm::simd::USUB8(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const i32 diff0 = static_cast<i32>(Rn & 0xFF) - static_cast<i32>(Rm & 0xFF);
    const i32 diff1 = static_cast<i32>((Rn >> 8) & 0xFF) - static_cast<i32>((Rm >> 8) & 0xFF);
    const i32 diff2 = static_cast<i32>((Rn >> 16) & 0xFF) - static_cast<i32>((Rm >> 16) & 0xFF);
    const i32 diff3 = static_cast<i32>((Rn >> 24) & 0xFF) - static_cast<i32>((Rm >> 24) & 0xFF);

    reg.write(Rd_id, (
        (static_cast<u32>(diff0) & 0xFF) |
        ((static_cast<u32>(diff1) & 0xFF) << 8) |
        ((static_cast<u32>(diff2) & 0xFF) << 16) |
        ((static_cast<u32>(diff3) & 0xFF) << 24)
    ));

    reg.write(id::cpsr::GE, static_cast<u8>(
        (diff0 >= 0 ? 0b0001 : 0) |
        (diff1 >= 0 ? 0b0010 : 0) |
        (diff2 >= 0 ? 0b0100 : 0) |
        (diff3 >= 0 ? 0b1000 : 0)
    ));
}


/**
 * if ConditionPassed(cond) then
 *     diff = Rn[31:16] - Rm[15:0] // unsigned subtraction
 *     Rd[31:16] = diff[15:0]
 *     GE[3:2] = if BorrowFrom(Rn[31:16] - Rm[15:0]) then 0b11 else 0
 *     sum = Rn[15:0] + Rm[31:16] // unsigned addition
 *     Rd[15:0] = sum[15:0]
 *     GE[1:0] = if CarryFrom16(Rn[15:0] + Rm[31:16]) then 0b11 else 0
 */
void INSTRUCTIONS::arm::simd::USUBADDX(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const u32 Rn_lo = Rn & 0xFFFF;
    const u32 Rn_hi = (Rn >> 16) & 0xFFFF;
    const u32 Rm_lo = Rm & 0xFFFF;
    const u32 Rm_hi = (Rm >> 16) & 0xFFFF;

    const i32 diff_hi = static_cast<i32>(Rn_hi) - static_cast<i32>(Rm_lo);
    const bool borrow_hi = (Rn_hi < Rm_lo);
    const u32 sum_lo = Rn_lo + Rm_hi;

    reg.write(Rd_id, (sum_lo & 0xFFFF) | ((static_cast<u32>(diff_hi) & 0xFFFF) << 16));
    reg.write(id::cpsr::GE, static_cast<u8>((sum_lo >= 0x10000 ? 0b0011 : 0) | (borrow_hi ? 0b1100 : 0)));
}


/**
 * if ConditionPassed(cond) then
 *     sum = Rn[15:0] + Rm[15:0] // Unsigned addition
 *     Rd[15:0] = sum[16:1]
 *     sum = Rn[31:16] + Rm[31:16] // Unsigned addition
 *     Rd[31:16] = sum[16:1]
 */
void INSTRUCTIONS::arm::simd::UHADD16(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const u32 sum_lo = ((Rn & 0xFFFF) + (Rm & 0xFFFF)) >> 1;
    const u32 sum_hi = (((Rn >> 16) & 0xFFFF) + ((Rm >> 16) & 0xFFFF)) >> 1;

    reg.write(Rd_id, (sum_lo & 0xFFFF) | ((sum_hi & 0xFFFF) << 16));
}


/**
 * if ConditionPassed(cond) then
 *     sum = Rn[7:0] + Rm[7:0] // Unsigned addition
 *     Rd[7:0] = sum[8:1]
 *     sum = Rn[15:8] + Rm[15:8] // Unsigned addition
 *     Rd[15:8] = sum[8:1]
 *     sum = Rn[23:16] + Rm[23:16] // Unsigned addition
 *     Rd[23:16] = sum[8:1]
 *     sum = Rn[31:24] + Rm[31:24] // Unsigned addition
 *     Rd[31:24] = sum[8:1]
 */
void INSTRUCTIONS::arm::simd::UHADD8(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const u32 sum0 = ((Rn & 0xFF) + (Rm & 0xFF)) >> 1;
    const u32 sum1 = (((Rn >> 8) & 0xFF) + ((Rm >> 8) & 0xFF)) >> 1;
    const u32 sum2 = (((Rn >> 16) & 0xFF) + ((Rm >> 16) & 0xFF)) >> 1;
    const u32 sum3 = (((Rn >> 24) & 0xFF) + ((Rm >> 24) & 0xFF)) >> 1;

    reg.write(Rd_id, (
        (sum0 & 0xFF) |
        ((sum1 & 0xFF) << 8) |
        ((sum2 & 0xFF) << 16) |
        ((sum3 & 0xFF) << 24)
    ));
}


/**
 * if ConditionPassed(cond) then
 *     sum = Rn[31:16] + Rm[15:0] // Unsigned addition
 *     Rd[31:16] = sum[16:1]
 *     diff = Rn[15:0] - Rm[31:16] // Unsigned subtraction
 *     Rd[15:0] = diff[16:1]
 */
void INSTRUCTIONS::arm::simd::UHADDSUBX(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const u32 sum_hi = (((Rn >> 16) & 0xFFFF) + (Rm & 0xFFFF)) >> 1;
    const i32 diff_lo = (static_cast<i32>(Rn & 0xFFFF) - static_cast<i32>((Rm >> 16) & 0xFFFF)) >> 1;

    reg.write(Rd_id, (static_cast<u32>(diff_lo) & 0xFFFF) | ((sum_hi & 0xFFFF) << 16));
}


/**
 * if ConditionPassed(cond) then
 *     diff = Rn[15:0] - Rm[15:0] // Unsigned subtraction
 *     Rd[15:0] = diff[16:1]
 *     diff = Rn[31:16] - Rm[31:16] // Unsigned subtraction
 *     Rd[31:16] = diff[16:1]
 */
void INSTRUCTIONS::arm::simd::UHSUB16(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const i32 diff_lo = (static_cast<i32>(Rn & 0xFFFF) - static_cast<i32>(Rm & 0xFFFF)) >> 1;
    const i32 diff_hi = (static_cast<i32>((Rn >> 16) & 0xFFFF) - static_cast<i32>((Rm >> 16) & 0xFFFF)) >> 1;

    reg.write(Rd_id, (static_cast<u32>(diff_lo) & 0xFFFF) | ((static_cast<u32>(diff_hi) & 0xFFFF) << 16));
}


/**
 * if ConditionPassed(cond) then
 *     diff = Rn[7:0] - Rm[7:0] // Unsigned subtraction
 *     Rd[7:0] = diff[8:1]
 *     diff = Rn[15:8] - Rm[15:8] // Unsigned subtraction
 *     Rd[15:8] = diff[8:1]
 *     diff = Rn[23:16] - Rm[23:16] // Unsigned subtraction
 *     Rd[23:16] = diff[8:1]
 *     diff = Rn[31:24] - Rm[31:24] // Unsigned subtraction
 *     Rd[31:24] = diff[8:1]
 */
void INSTRUCTIONS::arm::simd::UHSUB8(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const i32 diff0 = (static_cast<i32>(Rn & 0xFF) - static_cast<i32>(Rm & 0xFF)) >> 1;
    const i32 diff1 = (static_cast<i32>((Rn >> 8) & 0xFF) - static_cast<i32>((Rm >> 8) & 0xFF)) >> 1;
    const i32 diff2 = (static_cast<i32>((Rn >> 16) & 0xFF) - static_cast<i32>((Rm >> 16) & 0xFF)) >> 1;
    const i32 diff3 = (static_cast<i32>((Rn >> 24) & 0xFF) - static_cast<i32>((Rm >> 24) & 0xFF)) >> 1;

    reg.write(Rd_id, (
        (static_cast<u32>(diff0) & 0xFF) |
        ((static_cast<u32>(diff1) & 0xFF) << 8) |
        ((static_cast<u32>(diff2) & 0xFF) << 16) |
        ((static_cast<u32>(diff3) & 0xFF) << 24)
    ));
}


/**
 * if ConditionPassed(cond) then
 *     diff = Rn[31:16] - Rm[15:0] // Unsigned subtraction
 *     Rd[31:16] = diff[16:1]
 *     sum = Rn[15:0] + Rm[31:16] // Unsigned addition
 *     Rd[15:0] = sum[16:1]
 */
void INSTRUCTIONS::arm::simd::UHSUBADDX(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const i32 diff_hi = (static_cast<i32>((Rn >> 16) & 0xFFFF) - static_cast<i32>(Rm & 0xFFFF)) >> 1;
    const u32 sum_lo = ((Rn & 0xFFFF) + ((Rm >> 16) & 0xFFFF)) >> 1;

    reg.write(Rd_id, (sum_lo & 0xFFFF) | ((static_cast<u32>(diff_hi) & 0xFFFF) << 16));
}


/**
 * if ConditionPassed(cond) then
 *     Rd[15:0] = UnsignedSat(Rn[15:0] + Rm[15:0], 16)
 *     Rd[31:16] = UnsignedSat(Rn[31:16] + Rm[31:16], 16)
 */
void INSTRUCTIONS::arm::simd::UQADD16(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const u32 sum_lo = (Rn & 0xFFFF) + (Rm & 0xFFFF);
    const u32 sum_hi = ((Rn >> 16) & 0xFFFF) + ((Rm >> 16) & 0xFFFF);

    const u32 lo = operation::unsigned_sat(sum_lo, 16);
    const u32 hi = operation::unsigned_sat(sum_hi, 16);

    reg.write(Rd_id, lo | (hi << 16));
}


/**
 * if ConditionPassed(cond) then
 *     Rd[7:0] = UnsignedSat(Rn[7:0] + Rm[7:0], 8)
 *     Rd[15:8] = UnsignedSat(Rn[15:8] + Rm[15:8], 8)
 *     Rd[23:16] = UnsignedSat(Rn[23:16] + Rm[23:16], 8)
 *     Rd[31:24] = UnsignedSat(Rn[31:24] + Rm[31:24], 8)
 */
void INSTRUCTIONS::arm::simd::UQADD8(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const u32 sum0 = (Rn & 0xFF) + (Rm & 0xFF);
    const u32 sum1 = ((Rn >> 8) & 0xFF) + ((Rm >> 8) & 0xFF);
    const u32 sum2 = ((Rn >> 16) & 0xFF) + ((Rm >> 16) & 0xFF);
    const u32 sum3 = ((Rn >> 24) & 0xFF) + ((Rm >> 24) & 0xFF);

    const u32 b0 = operation::unsigned_sat(sum0, 8);
    const u32 b1 = operation::unsigned_sat(sum1, 8);
    const u32 b2 = operation::unsigned_sat(sum2, 8);
    const u32 b3 = operation::unsigned_sat(sum3, 8);

    reg.write(Rd_id, b0 | (b1 << 8) | (b2 << 16) | (b3 << 24));
}


/**
 * if ConditionPassed(cond) then
 *     Rd[15:0] = UnsignedSat(Rn[15:0] - Rm[31:16], 16)
 *     Rd[31:16] = UnsignedSat(Rn[31:16] + Rm[15:0], 16)
 */
void INSTRUCTIONS::arm::simd::UQADDSUBX(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const u32 sum_hi = ((Rn >> 16) & 0xFFFF) + (Rm & 0xFFFF);
    const i32 diff_lo = static_cast<i32>(Rn & 0xFFFF) - static_cast<i32>((Rm >> 16) & 0xFFFF);

    const u32 hi = operation::unsigned_sat(sum_hi, 16);
    const u32 lo = operation::unsigned_sat(static_cast<u32>(diff_lo), 16);

    reg.write(Rd_id, lo | (hi << 16));
}


/**
 * if ConditionPassed(cond) then
 *     Rd[15:0] = UnsignedSat(Rn[15:0] - Rm[15:0], 16)
 *     Rd[31:16] = UnsignedSat(Rn[31:16] - Rm[31:16], 16)
 */
void INSTRUCTIONS::arm::simd::UQSUB16(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const i32 diff_lo = static_cast<i32>(Rn & 0xFFFF) - static_cast<i32>(Rm & 0xFFFF);
    const i32 diff_hi = static_cast<i32>((Rn >> 16) & 0xFFFF) - static_cast<i32>((Rm >> 16) & 0xFFFF);

    const u32 lo = operation::unsigned_sat(static_cast<u32>(diff_lo), 16);
    const u32 hi = operation::unsigned_sat(static_cast<u32>(diff_hi), 16);

    reg.write(Rd_id, lo | (hi << 16));
}


/**
 * if ConditionPassed(cond) then
 *     Rd[7:0] = UnsignedSat(Rn[7:0] - Rm[7:0], 8)
 *     Rd[15:8] = UnsignedSat(Rn[15:8] - Rm[15:8], 8)
 *     Rd[23:16] = UnsignedSat(Rn[23:16] - Rm[23:16], 8)
 *     Rd[31:24] = UnsignedSat(Rn[31:24] - Rm[31:24], 8)
 */
void INSTRUCTIONS::arm::simd::UQSUB8(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const i32 diff0 = static_cast<i32>(Rn & 0xFF) - static_cast<i32>(Rm & 0xFF);
    const i32 diff1 = static_cast<i32>((Rn >> 8) & 0xFF) - static_cast<i32>((Rm >> 8) & 0xFF);
    const i32 diff2 = static_cast<i32>((Rn >> 16) & 0xFF) - static_cast<i32>((Rm >> 16) & 0xFF);
    const i32 diff3 = static_cast<i32>((Rn >> 24) & 0xFF) - static_cast<i32>((Rm >> 24) & 0xFF);

    const u32 b0 = operation::unsigned_sat(static_cast<u32>(diff0), 8);
    const u32 b1 = operation::unsigned_sat(static_cast<u32>(diff1), 8);
    const u32 b2 = operation::unsigned_sat(static_cast<u32>(diff2), 8);
    const u32 b3 = operation::unsigned_sat(static_cast<u32>(diff3), 8);

    reg.write(Rd_id, b0 | (b1 << 8) | (b2 << 16) | (b3 << 24));
}


/**
 * if ConditionPassed(cond) then
 *     Rd[31:16] = UnsignedSat(Rn[31:16] - Rm[15:0], 16)
 *     Rd[15:0] = UnsignedSat(Rn[15:0] + Rm[31:16], 16)
 */
void INSTRUCTIONS::arm::simd::UQSUBADDX(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const i32 diff_hi = static_cast<i32>((Rn >> 16) & 0xFFFF) - static_cast<i32>(Rm & 0xFFFF);
    const u32 sum_lo = (Rn & 0xFFFF) + ((Rm >> 16) & 0xFFFF);

    const u32 hi = operation::unsigned_sat(static_cast<u32>(diff_hi), 16);
    const u32 lo = operation::unsigned_sat(sum_lo, 16);

    reg.write(Rd_id, lo | (hi << 16));
}
