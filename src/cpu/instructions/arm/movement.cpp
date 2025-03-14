#include "../../../types.hpp"
#include "../../core/registers.hpp"
#include "../instructions.hpp"

/**
 * if ConditionPassed(cond) then
 *   Rd = shifter_operand
 *   if S == 1 and Rd == R15 then
 *     CPSR = SPSR
 *   else if S == 1 then
 *     N Flag = Rd[31]
 *     Z Flag = if Rd == 0 then 1 else 0
 *     C Flag = shifter_carry_out
 *     V Flag = unaffected
 */
void INSTRUCTIONS::arm::movement::MOV(const arm_code_t &code) {
    const ADDRESSING_MODE::data_struct shifter_operand = address_mode.data_processing(code);
    
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);

    const bool S = code.test(20);

    reg.write(Rd_id, shifter_operand.value);

    const u32 Rd = reg.read(Rd_id);

    if ((S == 1) && (Rd_id == id::reg::R15)) {
        reg.write(id::reg::CPSR, id::reg::SPSR);
    } else {
        reg.write(id::cpsr::N, (Rd & (1 << 31)));
        reg.write(id::cpsr::Z, (Rd == 0));
        reg.write(id::cpsr::C, (shifter_operand.carry));
    }

    reg.arm_increment_PC();
} 


/**
 * if ConditionPassed(cond) then
 *   Rd = NOT shifter_operand
 *   if S == 1 and Rd == R15 then
 *     CPSR = SPSR
 *   else if S == 1 then
 *     N Flag = Rd[31]
 *     Z Flag = if Rd == 0 then 1 else 0
 *     C Flag = shifter_carry_out
 *     V Flag = unaffected
 */
void INSTRUCTIONS::arm::movement::MVN(const arm_code_t &code) {
    const ADDRESSING_MODE::data_struct shifter_operand = address_mode.data_processing(code);
    
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);

    const bool S = code.test(20);

    reg.write(Rd_id, ~shifter_operand.value);

    const u32 Rd = reg.read(Rd_id);

    if ((S == 1) && (Rd_id == id::reg::R15)) {
        reg.write(id::reg::CPSR, id::reg::SPSR);
    } else {
        reg.write(id::cpsr::N, (Rd & (1 << 31)));
        reg.write(id::cpsr::Z, (Rd == 0));
        reg.write(id::cpsr::C, (shifter_operand.carry));
    }

    reg.arm_increment_PC();
}


void INSTRUCTIONS::arm::movement::MRS(const arm_code_t&) {};// TODO
void INSTRUCTIONS::arm::movement::MSR(const arm_code_t&) {};// TODO