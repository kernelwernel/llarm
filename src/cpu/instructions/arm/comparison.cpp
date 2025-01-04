#include "types.hpp"
#include "utility.hpp"
#include "cpu/instructions/instructions.hpp"
#include "cpu/core/registers.hpp"




/*
 * if ConditionPassed(cond) then
 *   alu_out = Rn + shifter_operand
 *   N Flag = alu_out[31]
 *   Z Flag = if alu_out == 0 then 1 else 0
 *   C Flag = CarryFrom(Rn + shifter_operand)
 *   V Flag = OverflowFrom(Rn + shifter_operand)
 */
void instructions::arm::compare::CMN(const arm_code_t &code, REGISTERS &reg) {

}

