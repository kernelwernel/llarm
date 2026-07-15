#include "../../../id.hpp"
#include "../../core/registers.hpp"
#include "../instructions.hpp"
#include "../operation.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>

/*
 * if ConditionPassed(cond) then
 *   Rd = Rn + shifter_operand + C Flag
 *   if S == 1 and Rd == R15 then
 *     CPSR = SPSR
 *   else if S == 1 then
 *     N Flag = Rd[31]
 *     Z Flag = if Rd == 0 then 1 else 0
 *     C Flag = CarryFrom(Rn + shifter_operand + C Flag)
 *     V Flag = OverflowFrom(Rn + shifter_operand + C Flag)
 */
void INSTRUCTIONS::arm::math::ADC(const u32 code) {
    const data_struct shifter_operand = address_mode.data_processing(code);

    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);

    const bool S = llarm::util::bit_fetch(code, 20);

    const u32 carry_in = reg.read(id::cpsr::C);

    reg.write(Rd_id, (Rn + shifter_operand.value + carry_in));

    const u32 Rd = reg.read(Rd_id);

    if ((S == 1) && (Rd_id == id::reg::R15)) {
        reg.write(id::reg::CPSR, id::reg::SPSR);
    } else if (S == 1) {
        reg.write(id::cpsr::N, (llarm::util::bit_fetch(Rd, 31)));
        reg.write(id::cpsr::Z, (Rd == 0));
        reg.write(id::cpsr::C, operation::carry_add(Rn, shifter_operand.value, carry_in));
        reg.write(id::cpsr::V, operation::overflow_add(Rn, shifter_operand.value, carry_in));
    }
}


/*
 * if ConditionPassed(cond) then
 *   Rd = Rn + shifter_operand
 *   if S == 1 and Rd == R15 then
 *     CPSR = SPSR
 *   else if S == 1 then
 *     N Flag = Rd[31]
 *     Z Flag = if Rd == 0 then 1 else 0
 *     C Flag = CarryFrom(Rn + shifter_operand)
 *     V Flag = OverflowFrom(Rn + shifter_operand)
 */
void INSTRUCTIONS::arm::math::ADD(const u32 code) {
    const data_struct shifter_operand = address_mode.data_processing(code);

    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);

    const bool S = llarm::util::bit_fetch(code, 20);

    reg.write(Rd_id, (Rn + shifter_operand.value));

    if ((S == 1) && (Rd_id == id::reg::R15)) {
        reg.write(id::reg::CPSR, id::reg::SPSR);
    } else if (S == 1) {
        const u32 Rd = reg.read(Rd_id);
        reg.write(id::cpsr::N, (llarm::util::bit_fetch(Rd, 31)));
        reg.write(id::cpsr::Z, (Rd == 0));
        reg.write(id::cpsr::C, operation::carry_add(Rn, shifter_operand.value));
        reg.write(id::cpsr::V, operation::overflow_add(Rn, shifter_operand.value));
    }
}


/**
 * if ConditionPassed(cond) then
 *   Rd = shifter_operand - Rn - NOT(C Flag)
 *   if S == 1 and Rd == R15 then
 *     CPSR = SPSR
 *   else if S == 1 then
 *     N Flag = Rd[31]
 *     Z Flag = if Rd == 0 then 1 else 0
 *     C Flag = NOT BorrowFrom(shifter_operand - Rn - NOT(C Flag))
 *     V Flag = OverflowFrom(shifter_operand - Rn - NOT(C Flag))
 */
void INSTRUCTIONS::arm::math::RSC(const u32 code) {
    const data_struct shifter_operand = address_mode.data_processing(code);
    
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);

    const bool S = llarm::util::bit_fetch(code, 20);

    const u32 not_carry_in = !(reg.read(id::cpsr::C));

    reg.write(Rd_id, (shifter_operand.value - Rn - not_carry_in));

    if ((S == 1) && (Rd_id == id::reg::R15)) {
        reg.write(id::reg::CPSR, id::reg::SPSR);
    } else if (S == 1) {
        const u32 Rd = reg.read(Rd_id);
        reg.write(id::cpsr::N, (llarm::util::bit_fetch(Rd, 31)));
        reg.write(id::cpsr::Z, (Rd == 0));
        reg.write(id::cpsr::C, !operation::borrow_sub(shifter_operand.value, Rn, not_carry_in));
        reg.write(id::cpsr::V, operation::overflow_sub(shifter_operand.value, Rn, not_carry_in));
    }
}


/**
 * if ConditionPassed(cond) then
 *   Rd = Rn - shifter_operand - NOT(C Flag)
 *   if S == 1 and Rd == R15 then
 *     CPSR = SPSR
 *   else if S == 1 then
 *     N Flag = Rd[31]
 *     Z Flag = if Rd == 0 then 1 else 0
 *     C Flag = NOT BorrowFrom(Rn - shifter_operand - NOT(C Flag))
 *     V Flag = OverflowFrom(Rn - shifter_operand - NOT(C Flag)
 */ 
void INSTRUCTIONS::arm::math::SBC(const u32 code) {
    const data_struct shifter_operand = address_mode.data_processing(code);

    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);

    const bool S = llarm::util::bit_fetch(code, 20);

    // captured before Rd is written; see ADC for why this can't be a fresh
    // reg.read(id::cpsr::C) below (the C flag gets overwritten by borrow-out first)
    const u32 not_carry_in = !(reg.read(id::cpsr::C));

    reg.write(Rd_id, (Rn - shifter_operand.value - not_carry_in));

    if ((S == 1) && (Rd_id == id::reg::R15)) {
        reg.write(id::reg::CPSR, id::reg::SPSR);
    } else if (S == 1) {
        const u32 Rd = reg.read(Rd_id);
        reg.write(id::cpsr::N, (llarm::util::bit_fetch(Rd, 31)));
        reg.write(id::cpsr::Z, (Rd == 0));
        reg.write(id::cpsr::C, !operation::borrow_sub(Rn, shifter_operand.value, not_carry_in));
        reg.write(id::cpsr::V, operation::overflow_sub(Rn, shifter_operand.value, not_carry_in));
    }
}


/**
 * if ConditionPassed(cond) then
 *   Rd = shifter_operand - Rn
 *   if S == 1 and Rd == R15 then
 *     CPSR = SPSR
 *   else if S == 1 then
 *     N Flag = Rd[31]
 *     Z Flag = if Rd == 0 then 1 else 0
 *     C Flag = NOT BorrowFrom(shifter_operand - Rn)
 *     V Flag = OverflowFrom(shifter_operand - Rn)
 */ 
void INSTRUCTIONS::arm::math::RSB(const u32 code) {
    const data_struct shifter_operand = address_mode.data_processing(code);

    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);

    const bool S = llarm::util::bit_fetch(code, 20);

    reg.write(Rd_id, (shifter_operand.value - Rn));

    if ((S == 1) && (Rd_id == id::reg::R15)) {
        reg.write(id::reg::CPSR, id::reg::SPSR);
    } else if (S == 1) {
        const u32 Rd = reg.read(Rd_id);
        reg.write(id::cpsr::N, (llarm::util::bit_fetch(Rd, 31)));
        reg.write(id::cpsr::Z, (Rd == 0));
        reg.write(id::cpsr::C, !operation::borrow_sub(shifter_operand.value, Rn));
        reg.write(id::cpsr::V, operation::overflow_sub(shifter_operand.value, Rn));
    }
}


/**
 * if ConditionPassed(cond) then
 *   Rd = Rn - shifter_operand
 *   if S == 1 and Rd == R15 then
 *     CPSR = SPSR
 *   else if S == 1 then
 *     N Flag = Rd[31]
 *     Z Flag = if Rd == 0 then 1 else 0
 *     C Flag = NOT BorrowFrom(Rn - shifter_operand)
 *     V Flag = OverflowFrom(Rn - shifter_operand)
 */
void INSTRUCTIONS::arm::math::SUB(const u32 code) {
    const data_struct shifter_operand = address_mode.data_processing(code);

    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);

    const bool S = llarm::util::bit_fetch(code, 20);

    reg.write(Rd_id, (Rn - shifter_operand.value));

    if ((S == 1) && (Rd_id == id::reg::R15)) {
        reg.write(id::reg::CPSR, id::reg::SPSR);
    } else if (S == 1) {
        const u32 Rd = reg.read(Rd_id);
        reg.write(id::cpsr::N, (llarm::util::bit_fetch(Rd, 31)));
        reg.write(id::cpsr::Z, (Rd == 0));
        reg.write(id::cpsr::C, !operation::borrow_sub(Rn, shifter_operand.value));
        reg.write(id::cpsr::V, operation::overflow_sub(Rn, shifter_operand.value));
    }
}


/**
 * if ConditionPassed(cond) then
 *   operand2 = Rm Rotate_Right(8 * rotate)
 *   Rd[31:0] = SignExtend(operand2[7:0])
 */
void INSTRUCTIONS::arm::math::SXTB(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rm = reg.read(code, 0, 3);
    const u8 rotate = llarm::util::bit_range<u8>(code, 10, 11);

    const u32 operand2 = llarm::util::rotr(Rm, static_cast<u8>(rotate * 8));

    reg.write(Rd_id, static_cast<u32>(operation::sign_extend(operand2 & 0xFF, 7)));
}


/**
 * if ConditionPassed(cond) then
 *   operand2 = Rm Rotate_Right(8 * rotate)
 *   Rd = Rn + SignExtend(operand2[7:0])
 */
void INSTRUCTIONS::arm::math::SXTAB(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);
    const u8 rotate = llarm::util::bit_range<u8>(code, 10, 11);

    const u32 operand2 = llarm::util::rotr(Rm, static_cast<u8>(rotate * 8));

    reg.write(Rd_id, Rn + static_cast<u32>(operation::sign_extend(operand2 & 0xFF, 7)));
}


/**
 * if ConditionPassed(cond) then
 *   operand2 = Rm Rotate_Right(8 * rotate)
 *   Rd[15:0] = SignExtend(operand2[7:0])
 *   Rd[31:16] = SignExtend(operand2[23:16])
 */
void INSTRUCTIONS::arm::math::SXTB16(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rm = reg.read(code, 0, 3);
    const u8 rotate = llarm::util::bit_range<u8>(code, 10, 11);

    const u32 operand2 = llarm::util::rotr(Rm, static_cast<u8>(rotate * 8));

    const u32 low = static_cast<u32>(operation::sign_extend(operand2 & 0xFF, 7)) & 0xFFFF;
    const u32 high = static_cast<u32>(operation::sign_extend((operand2 >> 16) & 0xFF, 7)) & 0xFFFF;

    reg.write(Rd_id, low | (high << 16));
}


/**
 * if ConditionPassed(cond) then
 *   operand2 = Rm Rotate_Right(8 * rotate)
 *   Rd[15:0] = Rn[15:0] + SignExtend(operand2[7:0])
 *   Rd[31:16] = Rn[31:16] + SignExtend(operand2[23:16])
 */
void INSTRUCTIONS::arm::math::SXTAB16(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);
    const u8 rotate = llarm::util::bit_range<u8>(code, 10, 11);

    const u32 operand2 = llarm::util::rotr(Rm, static_cast<u8>(rotate * 8));

    const u32 low = ((Rn & 0xFFFF) + static_cast<u32>(operation::sign_extend(operand2 & 0xFF, 7))) & 0xFFFF;
    const u32 high = (((Rn >> 16) & 0xFFFF) + static_cast<u32>(operation::sign_extend((operand2 >> 16) & 0xFF, 7))) & 0xFFFF;

    reg.write(Rd_id, low | (high << 16));
}


/**
 * if ConditionPassed(cond) then
 *   operand2 = Rm Rotate_Right(8 * rotate)
 *   Rd[31:0] = SignExtend(operand2[15:0])
 */
void INSTRUCTIONS::arm::math::SXTH(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rm = reg.read(code, 0, 3);
    const u8 rotate = llarm::util::bit_range<u8>(code, 10, 11);

    const u32 operand2 = llarm::util::rotr(Rm, static_cast<u8>(rotate * 8));

    reg.write(Rd_id, static_cast<u32>(operation::sign_extend(operand2 & 0xFFFF, 15)));
}


/**
 * if ConditionPassed(cond) then
 *   operand2 = Rm Rotate_Right(8 * rotate)
 *   Rd = Rn + SignExtend(operand2[15:0])
 */
void INSTRUCTIONS::arm::math::SXTAH(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);
    const u8 rotate = llarm::util::bit_range<u8>(code, 10, 11);

    const u32 operand2 = llarm::util::rotr(Rm, static_cast<u8>(rotate * 8));

    reg.write(Rd_id, Rn + static_cast<u32>(operation::sign_extend(operand2 & 0xFFFF, 15)));
}


/**
 * if ConditionPassed(cond) then
 *   Rd[31:0] = (Rm Rotate_Right(8 * rotate)) AND 0x000000ff
 */
void INSTRUCTIONS::arm::math::UXTB(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rm = reg.read(code, 0, 3);
    const u8 rotate = llarm::util::bit_range<u8>(code, 10, 11);

    reg.write(Rd_id, llarm::util::rotr(Rm, static_cast<u8>(rotate * 8)) & 0x000000FF);
}


/**
 * if ConditionPassed(cond) then
 *   operand2 = (Rm Rotate_Right(8 * rotate)) AND 0x000000ff
 *   Rd = Rn + operand2
 */
void INSTRUCTIONS::arm::math::UXTAB(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);
    const u8 rotate = llarm::util::bit_range<u8>(code, 10, 11);

    const u32 operand2 = llarm::util::rotr(Rm, static_cast<u8>(rotate * 8)) & 0x000000FF;

    reg.write(Rd_id, Rn + operand2);
}


/**
 * if ConditionPassed(cond) then
 *   Rd[31:0] = (Rm Rotate_Right(8 * rotate)) AND 0x00ff00ff
 */
void INSTRUCTIONS::arm::math::UXTB16(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rm = reg.read(code, 0, 3);
    const u8 rotate = llarm::util::bit_range<u8>(code, 10, 11);

    reg.write(Rd_id, llarm::util::rotr(Rm, static_cast<u8>(rotate * 8)) & 0x00FF00FF);
}


/**
 * if ConditionPassed(cond) then
 *   operand2 = (Rm Rotate_Right(8 * rotate)) AND 0x00ff00ff
 *   Rd[15:0] = Rn[15:0] + operand2[15:0]
 *   Rd[31:16] = Rn[31:16] + operand2[23:16]
 */
void INSTRUCTIONS::arm::math::UXTAB16(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);
    const u8 rotate = llarm::util::bit_range<u8>(code, 10, 11);

    const u32 operand2 = llarm::util::rotr(Rm, static_cast<u8>(rotate * 8)) & 0x00FF00FF;

    const u32 low = ((Rn & 0xFFFF) + (operand2 & 0xFFFF)) & 0xFFFF;
    const u32 high = (((Rn >> 16) & 0xFFFF) + ((operand2 >> 16) & 0xFFFF)) & 0xFFFF;

    reg.write(Rd_id, low | (high << 16));
}


/**
 * if ConditionPassed(cond) then
 *   Rd[31:0] = (Rm Rotate_Right(8 * rotate)) AND 0x0000ffff
 */
void INSTRUCTIONS::arm::math::UXTH(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rm = reg.read(code, 0, 3);
    const u8 rotate = llarm::util::bit_range<u8>(code, 10, 11);

    reg.write(Rd_id, llarm::util::rotr(Rm, static_cast<u8>(rotate * 8)) & 0x0000FFFF);
}


/**
 * if ConditionPassed(cond) then
 *   operand2 = (Rm Rotate_Right(8 * rotate)) AND 0x0000ffff
 *   Rd = Rn + operand2
 */
void INSTRUCTIONS::arm::math::UXTAH(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);
    const u8 rotate = llarm::util::bit_range<u8>(code, 10, 11);

    const u32 operand2 = llarm::util::rotr(Rm, static_cast<u8>(rotate * 8)) & 0x0000FFFF;

    reg.write(Rd_id, Rn + operand2);
}


/**
 * if ConditionPassed(cond) then
 *   Rd[7:0]   = if GE[0] == 1 then Rn[7:0]   else Rm[7:0]
 *   Rd[15:8]  = if GE[1] == 1 then Rn[15:8]  else Rm[15:8]
 *   Rd[23:16] = if GE[2] == 1 then Rn[23:16] else Rm[23:16]
 *   Rd[31:24] = if GE[3] == 1 then Rn[31:24] else Rm[31:24]
 */
void INSTRUCTIONS::arm::math::SEL(const u32 code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);

    const u8 GE = reg.read(id::cpsr::GE);

    u32 result = 0;

    for (u8 byte_index = 0; byte_index < 4; byte_index++) {
        const u8 shift = static_cast<u8>(byte_index * 8);
        const u32 byte_mask = (0xFFu << shift);
        const u32 source = llarm::util::bit_fetch(GE, byte_index) ? Rn : Rm;

        result |= (source & byte_mask);
    }

    reg.write(Rd_id, result);
}