#include "../../../id.hpp"
#include "../../core/registers.hpp"
#include "../instructions.hpp"
#include "../operation.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>

#include <cstdlib>


/*
 * if ConditionPassed(cond) then
 *   Rd = Rn AND shifter_operand
 *   if S == 1 and Rd == R15 then
 *     CPSR = SPSR
 *   else if S == 1 then
 *     N Flag = Rd[31]
 *     Z Flag = if Rd == 0 then 1 else 0
 *     C Flag = shifter_carry_out
 *     V Flag = unaffected
 */
void INSTRUCTIONS::arm::logic::AND(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);

    const data_struct shifter_operand = address_mode.data_processing(code);

    const u32 Rn = reg.read(code, 16, 19);

    const bool S = llarm::util::bit_fetch(code, 20);

    reg.write(Rd_id, Rn & shifter_operand.value);

    if ((S == 1) && (Rd_id == id::reg::R15)) {
        reg.write(id::reg::CPSR, id::reg::SPSR);
    } else if (S == 1) {
        const u32 Rd = reg.read(Rd_id);
        reg.write(id::cpsr::N, (llarm::util::bit_fetch(Rd, 31)));
        reg.write(id::cpsr::Z, (Rd == 0));
        reg.write(id::cpsr::C, (shifter_operand.carry));
    }
}


/*
 * if ConditionPassed(cond) then
 *   if Rm == 0
 *     Rd = 32
 *   else
 *     Rd = 31 - (bit position of most significant ’1’ in Rm)
 */
void INSTRUCTIONS::arm::logic::CLZ(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);

    const u32 Rm = reg.read(code, 0, 3);

    if (Rm == 0) {
        reg.write(Rd_id, 32);
    } else {
        reg.write(Rd_id, static_cast<u32>(31 - llarm::util::get_msb(Rm)));
    }
}


/*
 * if ConditionPassed(cond) then
 *   Rd = Rn EOR shifter_operand
 *   if S == 1 and Rd == R15 then
 *     CPSR = SPSR
 *   else if S == 1 then
 *     N Flag = Rd[31]
 *     Z Flag = if Rd == 0 then 1 else 0
 *     C Flag = shifter_carry_out
 *     V Flag = unaffected
 */
void INSTRUCTIONS::arm::logic::EOR(const u32 code) {
    const data_struct shifter_operand = address_mode.data_processing(code);

    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);

    const bool S = llarm::util::bit_fetch(code, 20);

    reg.write(Rd_id, (Rn ^ shifter_operand.value));

    if ((S == 1) && (Rd_id == id::reg::R15)) {
        reg.write(id::reg::CPSR, id::reg::SPSR);
    } else if (S == 1) {
        const u32 Rd = reg.read(Rd_id);
        reg.write(id::cpsr::N, (llarm::util::bit_fetch(Rd, 31)));
        reg.write(id::cpsr::Z, (Rd == 0));
        reg.write(id::cpsr::C, shifter_operand.carry);
    }
}


/**
 * if ConditionPassed(cond) then
 *   alu_out = Rn - shifter_operand
 *   N Flag = alu_out[31]
 *   Z Flag = if alu_out == 0 then 1 else 0
 *   C Flag = NOT BorrowFrom(Rn - shifter_operand)
 *   V Flag = OverflowFrom(Rn - shifter_operand)
 */
void INSTRUCTIONS::arm::logic::CMP(const u32 code) {
    const data_struct shifter_operand = address_mode.data_processing(code);
    
    const u32 Rn = reg.read(code, 16, 19);

    const u32 alu_out = (Rn - shifter_operand.value);

    reg.write(id::cpsr::N, (llarm::util::bit_fetch(alu_out, 31)));
    reg.write(id::cpsr::Z, (alu_out == 0));
    reg.write(id::cpsr::C, !operation::borrow_sub(Rn, shifter_operand.value));
    reg.write(id::cpsr::V, operation::overflow_sub(Rn, shifter_operand.value));
} 


/**
 * if ConditionPassed(cond) then
 *   alu_out = Rn + shifter_operand
 *   N Flag = alu_out[31]
 *   Z Flag = if alu_out == 0 then 1 else 0
 *   C Flag = CarryFrom(Rn + shifter_operand)
 *   V Flag = OverflowFrom(Rn + shifter_operand)
 */
void INSTRUCTIONS::arm::logic::CMN(const u32 code) {
    const data_struct shifter_operand = address_mode.data_processing(code);
    
    const u32 Rn = reg.read(code, 16, 19);

    const u32 alu_out = (Rn + shifter_operand.value);

    reg.write(id::cpsr::N, (llarm::util::bit_fetch(alu_out, 31)));
    reg.write(id::cpsr::Z, (alu_out == 0));
    reg.write(id::cpsr::C, operation::carry_add(Rn, shifter_operand.value));
    reg.write(id::cpsr::V, operation::overflow_add(Rn, shifter_operand.value));
}


/**
 * if ConditionPassed(cond) then
 *     Rd = Rn AND NOT shifter_operand
 *     if S == 1 and Rd == R15 then
 *         CPSR = SPSR
 *     else if S == 1 then
 *         N Flag = Rd[31]
 *         Z Flag = if Rd == 0 then 1 else 0
 *         C Flag = shifter_carry_out
 *         V Flag = unaffected
 */
void INSTRUCTIONS::arm::logic::BIC(const u32 code) {
    const data_struct shifter_operand = address_mode.data_processing(code);

    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rd = (Rn & ~shifter_operand.value);
    const bool S = llarm::util::bit_fetch(code, 20);

    reg.write(Rd_id, Rd);

    if (S == 1) {
        if (Rd_id == id::reg::R15) {
            reg.write(id::reg::CPSR, id::reg::SPSR);
        } else {
            reg.write(id::cpsr::N, (llarm::util::bit_fetch(Rd, 31)));
            reg.write(id::cpsr::Z, (Rd == 0));
            reg.write(id::cpsr::C, shifter_operand.carry);
        }
    }
}


/**
 * if ConditionPassed(cond) then
 *   Rd = Rn OR shifter_operand
 *   if S == 1 and Rd == R15 then
 *     CPSR = SPSR
 *   else if S == 1 then
 *     N Flag = Rd[31]
 *     Z Flag = if Rd == 0 then 1 else 0
 *     C Flag = shifter_carry_out
 *     V Flag = unaffected
 */
void INSTRUCTIONS::arm::logic::ORR(const u32 code) {
    const data_struct shifter_operand = address_mode.data_processing(code);
        
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);

    const bool S = llarm::util::bit_fetch(code, 20);

    reg.write(Rd_id, (Rn | shifter_operand.value));

    if ((S == 1) && (Rd_id == id::reg::R15)) {
        reg.write(id::reg::CPSR, id::reg::SPSR);
    } else if (S == 1) {
        const u32 Rd = reg.read(Rd_id);
        reg.write(id::cpsr::N, (llarm::util::bit_fetch(Rd, 31)));
        reg.write(id::cpsr::Z, (Rd == 0));
        reg.write(id::cpsr::C, shifter_operand.carry);
    }
}


/**
 * if ConditionPassed(cond) then
 *   alu_out = Rn EOR shifter_operand
 *   N Flag = alu_out[31]
 *   Z Flag = if alu_out == 0 then 1 else 0
 *   C Flag = shifter_carry_out
 *   V Flag = unaffected
 */
void INSTRUCTIONS::arm::logic::TEQ(const u32 code) {
    const data_struct shifter_operand = address_mode.data_processing(code);
        
    const u32 Rn = reg.read(code, 16, 19);

    const u32 alu_out = (Rn ^ shifter_operand.value);

    reg.write(id::cpsr::N, (llarm::util::bit_fetch(alu_out, 31)));
    reg.write(id::cpsr::Z, (alu_out == 0));
    reg.write(id::cpsr::C, shifter_operand.carry);
}


/**
 * if ConditionPassed(cond) then
 *   alu_out = Rn AND shifter_operand
 *   N Flag = alu_out[31]
 *   Z Flag = if alu_out == 0 then 1 else 0
 *   C Flag = shifter_carry_out
 *   V Flag = unaffected
 */
void INSTRUCTIONS::arm::logic::TST(const u32 code) {
    const data_struct shifter_operand = address_mode.data_processing(code);

    const u32 Rn = reg.read(code, 16, 19);

    const u32 alu_out = (Rn & shifter_operand.value);

    reg.write(id::cpsr::N, (llarm::util::bit_fetch(alu_out, 31)));
    reg.write(id::cpsr::Z, (alu_out == 0));
    reg.write(id::cpsr::C, shifter_operand.carry);
}


/**
 * if ConditionPassed(cond) then
 *   Rd[31:24] = Rm[ 7: 0]
 *   Rd[23:16] = Rm[15: 8]
 *   Rd[15: 8] = Rm[23:16]
 *   Rd[ 7: 0] = Rm[31:24]
 */
void INSTRUCTIONS::arm::logic::REV(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rm = reg.read(code, 0, 3);

    const u32 result = (
        ((Rm & 0x000000FF) << 24) |
        ((Rm & 0x0000FF00) << 8) |
        ((Rm & 0x00FF0000) >> 8) |
        ((Rm & 0xFF000000) >> 24)
    );

    reg.write(Rd_id, result);
}


/**
 * if ConditionPassed(cond) then
 *   Rd[15: 8] = Rm[ 7: 0]
 *   Rd[ 7: 0] = Rm[15: 8]
 *   Rd[31:24] = Rm[23:16]
 *   Rd[23:16] = Rm[31:24]
 */
void INSTRUCTIONS::arm::logic::REV16(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rm = reg.read(code, 0, 3);

    const u32 result = (
        ((Rm & 0x00FF0000) << 8) |
        ((Rm & 0xFF000000) >> 8) |
        ((Rm & 0x000000FF) << 8) |
        ((Rm & 0x0000FF00) >> 8)
    );

    reg.write(Rd_id, result);
}


/**
 * if ConditionPassed(cond) then
 *   Rd[15: 8] = Rm[ 7: 0]
 *   Rd[ 7: 0] = Rm[15: 8]
 *   if Rm[7] == 1 then
 *     Rd[31:16] = 0xFFFF
 *   else
 *     Rd[31:16] = 0x0000
 */
void INSTRUCTIONS::arm::logic::REVSH(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rm = reg.read(code, 0, 3);

    const u8 byte0 = static_cast<u8>(Rm & 0xFF);
    const u8 byte1 = static_cast<u8>((Rm >> 8) & 0xFF);

    reg.write(Rd_id, static_cast<u32>(operation::sign_extend(static_cast<u32>((byte0 << 8) | byte1), 15)));
}


/**
 * if ConditionPassed(cond) then
 *   Rd[15:0] = Rn[15:0]
 *   Rd[31:16] = (Rm Logical_Shift_Left shift_imm)[31:16]
 */
void INSTRUCTIONS::arm::logic::PKHBT(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const u8 shift_imm = llarm::util::bit_range<u8>(code, 7, 11);

    const u32 result = (Rn & 0x0000FFFF) | ((Rm << shift_imm) & 0xFFFF0000);

    reg.write(Rd_id, result);
}


/**
 * if ConditionPassed(cond) then
 *   if shift_imm == 0 then // ASR #32 case
 *     if Rm[31] == 0 then Rd[15:0] = 0x0000 else Rd[15:0] = 0xFFFF
 *   else
 *     Rd[15:0] = (Rm Arithmetic_Shift_Right shift_imm)[15:0]
 *   Rd[31:16] = Rn[31:16]
 */
void INSTRUCTIONS::arm::logic::PKHTB(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const u8 shift_imm = llarm::util::bit_range<u8>(code, 7, 11);

    const u32 lower_half = [Rm, shift_imm]() -> u32 {
        if (shift_imm == 0) { // ASR #32 case
            return llarm::util::bit_fetch(Rm, 31) ? 0x0000FFFF : 0x00000000;
        }

        return operation::arithmetic_shift_right(Rm, shift_imm) & 0x0000FFFF;
    }();

    reg.write(Rd_id, lower_half | (Rn & 0xFFFF0000));
}


/**
 * if ConditionPassed(cond) then
 *   if shift == 1 then
 *     if shift_imm == 0 then
 *       operand = (Rm Arithmetic_Shift_Right 32)[31:0]
 *     else
 *       operand = (Rm Arithmetic_Shift_Right shift_imm)[31:0]
 *   else
 *     operand = (Rm Logical_Shift_Left shift_imm)[31:0]
 *   Rd = SignedSat(operand, sat_imm + 1)
 *   if SignedDoesSat(operand, sat_imm + 1) then
 *     Q Flag = 1
 */
void INSTRUCTIONS::arm::logic::SSAT(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rm = reg.read(code, 0, 3);

    const u8 sat_imm = llarm::util::bit_range<u8>(code, 16, 20);
    const u8 shift_imm = llarm::util::bit_range<u8>(code, 7, 11);
    const bool sh = llarm::util::bit_fetch(code, 6);

    const u32 operand = [Rm, shift_imm, sh]() -> u32 {
        if (!sh) {
            return Rm << shift_imm;
        }

        if (shift_imm == 0) { // ASR #32 case
            return llarm::util::bit_fetch(Rm, 31) ? 0xFFFFFFFF : 0x00000000;
        }

        return operation::arithmetic_shift_right(Rm, shift_imm);
    }();

    const u32 n = static_cast<u32>(sat_imm) + 1;

    reg.write(Rd_id, static_cast<u32>(operation::signed_sat(operand, n)));

    if (operation::signed_does_sat(operand, n)) {
        reg.write(id::cpsr::Q, true);
    }
}


/**
 * if ConditionPassed(cond) then
 *   Rd[15:0] = SignedSat(Rm[15:0], sat_imm + 1)
 *   Rd[31:16] = SignedSat(Rm[31:16], sat_imm + 1)
 *   if SignedDoesSat(Rm[15:0], sat_imm + 1) OR SignedDoesSat(Rm[31:16], sat_imm + 1) then
 *     Q Flag = 1
 */
void INSTRUCTIONS::arm::logic::SSAT16(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rm = reg.read(code, 0, 3);

    const u8 sat_imm = llarm::util::bit_range<u8>(code, 16, 19);
    const u32 n = static_cast<u32>(sat_imm) + 1;

    const u32 low_operand = static_cast<u32>(operation::sign_extend(Rm & 0xFFFF, 15));
    const u32 high_operand = static_cast<u32>(operation::sign_extend((Rm >> 16) & 0xFFFF, 15));

    const u32 low = static_cast<u32>(operation::signed_sat(low_operand, n)) & 0xFFFF;
    const u32 high = static_cast<u32>(operation::signed_sat(high_operand, n)) & 0xFFFF;

    reg.write(Rd_id, low | (high << 16));

    if (operation::signed_does_sat(low_operand, n) || operation::signed_does_sat(high_operand, n)) {
        reg.write(id::cpsr::Q, true);
    }
}


/**
 * if ConditionPassed(cond) then
 *   if shift == 1 then
 *     if shift_imm == 0 then
 *       operand = (Rm Arithmetic_Shift_Right 32)[31:0]
 *     else
 *       operand = (Rm Arithmetic_Shift_Right shift_imm)[31:0]
 *   else
 *     operand = (Rm Logical_Shift_Left shift_imm)[31:0]
 *   Rd = UnsignedSat(operand, sat_imm) // operand treated as signed
 *   if UnsignedDoesSat(operand, sat_imm) then
 *     Q Flag = 1
 */
void INSTRUCTIONS::arm::logic::USAT(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rm = reg.read(code, 0, 3);

    const u8 sat_imm = llarm::util::bit_range<u8>(code, 16, 20);
    const u8 shift_imm = llarm::util::bit_range<u8>(code, 7, 11);
    const bool sh = llarm::util::bit_fetch(code, 6);

    const u32 operand = [Rm, shift_imm, sh]() -> u32 {
        if (!sh) {
            return Rm << shift_imm;
        }

        if (shift_imm == 0) { // ASR #32 case
            return llarm::util::bit_fetch(Rm, 31) ? 0xFFFFFFFF : 0x00000000;
        }

        return operation::arithmetic_shift_right(Rm, shift_imm);
    }();

    reg.write(Rd_id, operation::unsigned_sat(operand, sat_imm));

    if (operation::unsigned_does_sat(operand, sat_imm)) {
        reg.write(id::cpsr::Q, true);
    }
}


/**
 * if ConditionPassed(cond) then
 *   Rd[15:0] = UnsignedSat(Rm[15:0], sat_imm) // Rm[15:0] treated as signed
 *   Rd[31:16] = UnsignedSat(Rm[31:16], sat_imm) // Rm[31:16] treated as signed
 *   if UnsignedDoesSat(Rm[15:0], sat_imm) OR UnsignedDoesSat(Rm[31:16], sat_imm) then
 *     Q Flag = 1
 */
void INSTRUCTIONS::arm::logic::USAT16(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rm = reg.read(code, 0, 3);

    const u8 sat_imm = llarm::util::bit_range<u8>(code, 16, 19);

    const u32 low_operand = static_cast<u32>(operation::sign_extend(Rm & 0xFFFF, 15));
    const u32 high_operand = static_cast<u32>(operation::sign_extend((Rm >> 16) & 0xFFFF, 15));

    const u32 low = operation::unsigned_sat(low_operand, sat_imm) & 0xFFFF;
    const u32 high = operation::unsigned_sat(high_operand, sat_imm) & 0xFFFF;

    reg.write(Rd_id, low | (high << 16));

    if (operation::unsigned_does_sat(low_operand, sat_imm) || operation::unsigned_does_sat(high_operand, sat_imm)) {
        reg.write(id::cpsr::Q, true);
    }
}


/**
 * if ConditionPassed(cond) then
 *
 *     if Rm[7:0] < Rs[7:0] then // Unsigned comparison
 *          diff1 = Rs[7:0] - Rm[7:0]
 *     else
 *          diff1 = Rm[7:0] - Rs[7:0]
 *
 *     if Rm[15:8] < Rs[15:8] then // Unsigned comparison
 *          diff2 = Rs[15:8] - Rm[15:8]
 *     else
 *          diff2 = Rm[15:8] - Rs[15:8]
 *
 *     if Rm[23:16] < Rs[23:16] then // Unsigned comparison
 *          diff3 = Rs[23:16] - Rm[23:16]
 *     else
 *          diff3 = Rm[23:16] - Rs[23:16]
 *
 *     if Rm[31:24] < Rs[31:24] then // Unsigned comparison
 *          diff4 = Rs[31:24] - Rm[31:24]
 *     else
 *          diff4 = Rm[31:24] - Rs[31:24]
 *
 *     Rd = ZeroExtend(diff1) + ZeroExtend(diff2)
 *                            + ZeroExtend(diff3) + ZeroExtend(diff4]
 */
void INSTRUCTIONS::arm::logic::USAD8(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rs = reg.read(code, 8, 11);

    const u32 diff1 = static_cast<u32>(std::abs(static_cast<i32>((Rm & 0xFF)) - static_cast<i32>(Rs & 0xFF)));
    const u32 diff2 = static_cast<u32>(std::abs(static_cast<i32>((Rm >> 8) & 0xFF) - static_cast<i32>((Rs >> 8) & 0xFF)));
    const u32 diff3 = static_cast<u32>(std::abs(static_cast<i32>((Rm >> 16) & 0xFF) - static_cast<i32>((Rs >> 16) & 0xFF)));
    const u32 diff4 = static_cast<u32>(std::abs(static_cast<i32>((Rm >> 24) & 0xFF) - static_cast<i32>((Rs >> 24) & 0xFF)));

    reg.write(Rd_id, diff1 + diff2 + diff3 + diff4);
}


/**
 * if ConditionPassed(cond) then
 *
 *     if Rm[7:0] < Rs[7:0] then // Unsigned comparison
 *          diff1 = Rs[7:0] - Rm[7:0]
 *     else
 *          diff1 = Rm[7:0] - Rs[7:0]
 *
 *     if Rm[15:8] < Rs[15:8] then // Unsigned comparison
 *          diff2 = Rs[15:8] - Rm[15:8]
 *     else
 *          diff2 = Rm[15:8] - Rs[15:8]
 *
 *     if Rm[23:16] < Rs[23:16] then // Unsigned comparison
 *          diff3 = Rs[23:16] - Rm[23:16]
 *     else
 *          diff3 = Rm[23:16] - Rs[23:16]
 *
 *     if Rm[31:24] < Rs[31:24] then // Unsigned comparison
 *          diff4 = Rs[31:24] - Rm[31:24]
 *     else
 *          diff4 = Rm[31:24] - Rs[31:24]
 *
 *     Rd = Rn + ZeroExtend(diff1) + ZeroExtend(diff2)
 *                                 + ZeroExtend(diff3) + ZeroExtend(diff4]
 */
void INSTRUCTIONS::arm::logic::USADA8(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 16, 19);
    const u32 Rn = reg.read(code, 12, 15);
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rs = reg.read(code, 8, 11);

    const u32 diff1 = static_cast<u32>(std::abs(static_cast<i32>((Rm & 0xFF)) - static_cast<i32>(Rs & 0xFF)));
    const u32 diff2 = static_cast<u32>(std::abs(static_cast<i32>((Rm >> 8) & 0xFF) - static_cast<i32>((Rs >> 8) & 0xFF)));
    const u32 diff3 = static_cast<u32>(std::abs(static_cast<i32>((Rm >> 16) & 0xFF) - static_cast<i32>((Rs >> 16) & 0xFF)));
    const u32 diff4 = static_cast<u32>(std::abs(static_cast<i32>((Rm >> 24) & 0xFF) - static_cast<i32>((Rs >> 24) & 0xFF)));

    reg.write(Rd_id, Rn + diff1 + diff2 + diff3 + diff4);
}