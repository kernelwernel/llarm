#include "types.hpp"
#include "utility.hpp"
#include "cpu/instructions/instructions.hpp"
#include "cpu/core/registers.hpp"



/*
 * if ConditionPassed(cond) then
 *   if L == 1 then
 *     LR = address of the instruction after the branch instruction
 *   PC = PC + (SignExtend(signed_immed_24) << 2)
 */
//TODO
void instructions::arm::branching::B(const arm_code_t &code, REGISTERS &reg) {
    const i32 signed_immed_24 = util::bit_fetcher<i32>(code, 3, 5);
    const bool L = code.test(24);

    if (L == 1) {
        
    }

}


/*
 * if ConditionPassed(cond) then
 *   T Flag = Rm[0]
 *   PC = Rm AND 0xFFFFFFFE
 */
// TODO
void instructions::arm::branching::BX(const arm_code_t &code, REGISTERS &reg) {
    const u32 Rm = reg.read(code, 0, 3);

    if ((Rm & 1) == 0) {
        // arm
    } else {
        // thumb
    }

    reg.write(id::reg::PC, Rm & 0xFFFFFFFE);
}