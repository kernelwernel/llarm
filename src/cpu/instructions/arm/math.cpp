#include "types.hpp"
#include "utility.hpp"
#include "cpu/instructions/instructions.hpp"
#include "cpu/core/registers.hpp"

#include <limits>


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
void instructions::arm::math::ADC(const arm_code_t &code, REGISTERS &reg) {
    const u16 shifter_operand = util::bit_fetcher<u16>(code, 0, 11);

    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);

    const bool S = code.test(20);
    const bool I = code.test(25);

    reg.write(Rd_id, (Rn + shifter_operand + reg.read(id::cpsr::C)));

    const u32 Rd = reg.read(Rd_id);

    if ((S == 1) && (Rd == reg.read(id::reg::R15))) {
        reg.write(id::reg::SPSR);
    } else if (S == 1) {
        reg.write(id::cpsr::N, (Rd & (1 << 31)));
        reg.write(id::cpsr::Z, (Rd == 0));
        reg.write(id::cpsr::C, util::carry_add(Rn, shifter_operand, reg.read(id::cpsr::C)));
        reg.write(id::cpsr::V, util::overflow_add(Rn, shifter_operand, reg.read(id::cpsr::C)));
    }


    reg.arm_increment_PC();
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
void instructions::arm::math::ADD(const arm_code_t &code, REGISTERS &reg) {
    const u16 shifter_operand = util::bit_fetcher<u16>(code, 0, 11);

    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);

    const bool S = code.test(20);
    const bool I = code.test(25);

    reg.write(Rd_id, (Rn + shifter_operand));

    if ((S == 1) && (Rd_id == id::reg::R15)) {
        reg.write(id::reg::SPSR);
    } else if (S == 1) {
        const u32 Rd = reg.read(Rd_id);
        reg.write(id::cpsr::N, (Rd & (1 << 31)));
        reg.write(id::cpsr::Z, (Rd == 0));
        reg.write(id::cpsr::C, util::carry_add(Rn, shifter_operand));
        reg.write(id::cpsr::V, util::overflow_add(Rn, shifter_operand));
    }

    reg.arm_increment_PC();
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
void instructions::arm::math::RSC(const arm_code_t &code, REGISTERS &reg) {
    const u16 shifter_operand = util::bit_fetcher<u16>(code, 0, 11);
    
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.fetch_reg_id(code, 16, 19);

    const bool S = code.test(20);

    reg.write(Rd_id, (shifter_operand - Rn - !(reg.read(id::cpsr::C))));

    if ((S == 1) && (Rd_id == id::reg::R15)) {
        reg.write(id::reg::SPSR);
    } else if (S == 1) {
        const u32 Rd = reg.read(Rd_id);
        reg.write(id::cpsr::N, (Rd & (1 << 31)));
        reg.write(id::cpsr::Z, (Rd == 0));
        reg.write(id::cpsr::C, !util::borrow_sub(shifter_operand, Rn, !(reg.read(id::cpsr::C))));
        reg.write(id::cpsr::V, util::overflow_sub(shifter_operand, Rn, !(reg.read(id::cpsr::C))));
    }

    reg.arm_increment_PC();
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
void instructions::arm::math::SBC(const arm_code_t &code, REGISTERS &reg) {
    const u16 shifter_operand = util::bit_fetcher<u16>(code, 0, 11);
    
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.fetch_reg_id(code, 16, 19);

    const bool S = code.test(20);

    reg.write(Rd_id, (Rn - shifter_operand - !(reg.read(id::cpsr::C))));

    if ((S == 1) && (Rd_id == id::reg::R15)) {
        reg.write(id::reg::SPSR);
    } else if (S == 1) {
        const u32 Rd = reg.read(Rd_id);
        reg.write(id::cpsr::N, (Rd & (1 << 31)));
        reg.write(id::cpsr::Z, (Rd == 0));
        reg.write(id::cpsr::C, !util::borrow_sub(Rn, shifter_operand, !(reg.read(id::cpsr::C))));
        reg.write(id::cpsr::V, util::overflow_sub(Rn, shifter_operand, !(reg.read(id::cpsr::C))));
    }

    reg.arm_increment_PC();
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
void instructions::arm::math::RSB(const arm_code_t &code, REGISTERS &reg) {
    const u16 shifter_operand = util::bit_fetcher<u16>(code, 0, 11);
    
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.fetch_reg_id(code, 16, 19);

    const bool S = code.test(20);

    reg.write(Rd_id, (shifter_operand - Rn));

    if ((S == 1) && (Rd_id == id::reg::R15)) {
        reg.write(id::reg::SPSR);
    } else if (S == 1) {
        const u32 Rd = reg.read(Rd_id);
        reg.write(id::cpsr::N, (Rd & (1 << 31)));
        reg.write(id::cpsr::Z, (Rd == 0));
        reg.write(id::cpsr::C, !util::borrow_sub(shifter_operand, Rn));
        reg.write(id::cpsr::V, util::overflow_sub(shifter_operand, Rn));
    }

    reg.arm_increment_PC();
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
void instructions::arm::math::SUB(const arm_code_t &code, REGISTERS &reg) {
    const u16 shifter_operand = util::bit_fetcher<u16>(code, 0, 11);
    
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.fetch_reg_id(code, 16, 19);

    const bool S = code.test(20);

    reg.write(Rd_id, (Rn - shifter_operand));

    if ((S == 1) && (Rd_id == id::reg::R15)) {
        reg.write(id::reg::SPSR);
    } else if (S == 1) {
        const u32 Rd = reg.read(Rd_id);
        reg.write(id::cpsr::N, (Rd & (1 << 31)));
        reg.write(id::cpsr::Z, (Rd == 0));
        reg.write(id::cpsr::C, !util::borrow_sub(Rn, shifter_operand));
        reg.write(id::cpsr::V, util::overflow_sub(Rn, shifter_operand));
    }

    reg.arm_increment_PC();
}
