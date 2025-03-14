#include "../../../types.hpp"
#include "../../../id.hpp"
#include "../../core/registers.hpp"
#include "../instructions.hpp"

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
void INSTRUCTIONS::arm::logic::AND(const arm_code_t &code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);

    const ADDRESSING_MODE::data_struct shifter_operand = address_mode.data_processing(code);

    const u32 Rn = reg.read(code, 16, 19);

    const bool S = code.test(20);

    reg.write(Rd_id, Rn & shifter_operand.value);

    if ((S == 1) && (Rd_id == id::reg::R15)) {
        reg.write(id::reg::CPSR, id::reg::SPSR);
    } else if (S == 1) {
        const u32 Rd = reg.read(Rd_id);
        reg.write(id::cpsr::N, (Rd & (1 << 31)));
        reg.write(id::cpsr::Z, (Rd == 0));
        reg.write(id::cpsr::C, (shifter_operand.carry));
    }

    reg.arm_increment_PC();
}


/*
 * if Rm == 0
 *   Rd = 32
 * else
 *   Rd = 31 - (bit position of most significant ’1’ in Rm)
 */
void INSTRUCTIONS::arm::logic::CLZ(const arm_code_t &code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);

    const u32 Rm = reg.read(code, 0, 3);

    if (Rm == 0) {
        reg.write(Rd_id, 32);
    } else {
        reg.write(Rd_id, 31 - (std::bit_width(Rm) - 1));
    }

    reg.arm_increment_PC();
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
void INSTRUCTIONS::arm::logic::EOR(const arm_code_t &code) {
    const ADDRESSING_MODE::data_struct shifter_operand = address_mode.data_processing(code);

    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);

    const bool S = code.test(20);

    reg.write(Rd_id, (Rn ^ shifter_operand.value));

    if ((S == 1) && (Rd_id == id::reg::R15)) {
        reg.write(id::reg::CPSR, id::reg::SPSR);
    } else if (S == 1) {
        const u32 Rd = reg.read(Rd_id);
        reg.write(id::cpsr::N, (Rd & (1 << 31)));
        reg.write(id::cpsr::Z, (Rd == 0));
        reg.write(id::cpsr::C, shifter_operand.carry);
    }

    reg.arm_increment_PC();
}


/**
 * if ConditionPassed(cond) then
 *   alu_out = Rn - shifter_operand
 *   N Flag = alu_out[31]
 *   Z Flag = if alu_out == 0 then 1 else 0
 *   C Flag = NOT BorrowFrom(Rn - shifter_operand)
 *   V Flag = OverflowFrom(Rn - shifter_operand)
 */
void INSTRUCTIONS::arm::logic::CMP(const arm_code_t &code) {
    const ADDRESSING_MODE::data_struct shifter_operand = address_mode.data_processing(code);
    
    const u32 Rn = reg.read(code, 16, 19);

    const u32 alu_out = (Rn - shifter_operand.value);

    reg.write(id::cpsr::N, (alu_out & (1 << 31)));
    reg.write(id::cpsr::Z, (alu_out == 0));
    reg.write(id::cpsr::C, !operation.borrow_sub(Rn, shifter_operand.value));
    reg.write(id::cpsr::V, operation.overflow_sub(Rn, shifter_operand.value));

    reg.arm_increment_PC();
}


/**
 * if ConditionPassed(cond) then
 *   alu_out = Rn + shifter_operand
 *   N Flag = alu_out[31]
 *   Z Flag = if alu_out == 0 then 1 else 0
 *   C Flag = CarryFrom(Rn + shifter_operand)
 *   V Flag = OverflowFrom(Rn + shifter_operand)
 */
void INSTRUCTIONS::arm::logic::CMN(const arm_code_t &code) {
    const ADDRESSING_MODE::data_struct shifter_operand = address_mode.data_processing(code);
    
    const u32 Rn = reg.read(code, 16, 19);

    const u32 alu_out = (Rn + shifter_operand.value);

    reg.write(id::cpsr::N, (alu_out & (1 << 31)));
    reg.write(id::cpsr::Z, (alu_out == 0));
    reg.write(id::cpsr::C, operation.carry_add(Rn, shifter_operand.value));
    reg.write(id::cpsr::V, operation.overflow_add(Rn, shifter_operand.value));

    reg.arm_increment_PC();
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
void INSTRUCTIONS::arm::logic::ORR(const arm_code_t &code) {
    const ADDRESSING_MODE::data_struct shifter_operand = address_mode.data_processing(code);
        
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);

    const bool S = code.test(20);

    reg.write(Rd_id, (Rn | shifter_operand.value));

    if ((S == 1) && (Rd_id == id::reg::R15)) {
        reg.write(id::reg::CPSR, id::reg::SPSR);
    } else if (S == 1) {
        const u32 Rd = reg.read(Rd_id);
        reg.write(id::cpsr::N, (Rd & (1 << 31)));
        reg.write(id::cpsr::Z, (Rd == 0));
        reg.write(id::cpsr::C, shifter_operand.carry);
    }

    reg.arm_increment_PC();
}


/**
 * if ConditionPassed(cond) then
 *   alu_out = Rn EOR shifter_operand
 *   N Flag = alu_out[31]
 *   Z Flag = if alu_out == 0 then 1 else 0
 *   C Flag = shifter_carry_out
 *   V Flag = unaffected
 */
void INSTRUCTIONS::arm::logic::TEQ(const arm_code_t &code) {
    const ADDRESSING_MODE::data_struct shifter_operand = address_mode.data_processing(code);
        
    const u32 Rn = reg.read(code, 16, 19);

    const u32 alu_out = (Rn ^ shifter_operand.value);

    reg.write(id::cpsr::N, (alu_out & (1 << 31)));
    reg.write(id::cpsr::Z, (alu_out == 0));
    reg.write(id::cpsr::C, shifter_operand.carry);

    reg.arm_increment_PC();
}


/**
 * if ConditionPassed(cond) then
 *   alu_out = Rn AND shifter_operand
 *   N Flag = alu_out[31]
 *   Z Flag = if alu_out == 0 then 1 else 0
 *   C Flag = shifter_carry_out
 *   V Flag = unaffected
 */
void INSTRUCTIONS::arm::logic::TST(const arm_code_t &code) {
    const ADDRESSING_MODE::data_struct shifter_operand = address_mode.data_processing(code);
    
    const u32 Rn = reg.read(code, 16, 19);

    const u32 alu_out = (Rn & shifter_operand.value);

    reg.write(id::cpsr::N, (alu_out & (1 << 31)));
    reg.write(id::cpsr::Z, (alu_out == 0));
    reg.write(id::cpsr::C, shifter_operand.carry);

    reg.arm_increment_PC();
}