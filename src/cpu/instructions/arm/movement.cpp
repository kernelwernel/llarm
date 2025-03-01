#include "types.hpp"
#include "utility.hpp"
#include "cpu/instructions/instructions.hpp"
#include "cpu/core/registers.hpp"


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
void MOV(const arm_code_t &code, REGISTERS &reg) {
    const u16 shifter_operand = util::bit_fetcher<u16>(code, 0, 11);
    
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);

    const bool S = code.test(20);

    reg.write(Rd_id, 

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
void MVN(const arm_code_t &code, REGISTERS &reg) {
    const u16 shifter_operand = util::bit_fetcher<u16>(code, 0, 11);
    
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);

    const bool S = code.test(20);

    reg.arm_increment_PC();  
}