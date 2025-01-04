#include "types.hpp"
#include "utility.hpp"
#include "cpu/instructions/instructions.hpp"
#include "cpu/core/registers.hpp"

#include <bit>








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
void instructions::arm::logic::AND(const arm_code_t &code, REGISTERS &reg) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);

    const u16 shifter_operand = util::bit_fetcher<u16>(code, 0, 11);
    const u32 Rn = reg.read(code, 16, 19);

    const bool S = code.test(20);
    const bool I = code.test(25);

    reg.write(Rd_id, Rn & shifter_operand);

    if ((S == 1) && (Rd_id == id::reg::R15)) {
        reg.write_cpsr(id::reg::CURRENT_SPSR);
    } else if (S == 1) {
        const u32 Rd = reg.read(Rd_id);
        reg.write_cpsr(id::cpsr::N, (Rd & (1 << 31)));
        reg.write_cpsr(id::cpsr::Z, (Rd == 0));
        //TODO:
        //reg.write_cpsr(id::cpsr::C, ());
    }

    reg.increment_PC();
}


/*
 * if Rm == 0
 *   Rd = 32
 * else
 *   Rd = 31 - (bit position of most significant ’1’ in Rm)
 */
void instructions::arm::logic::CLZ(const arm_code_t &code, REGISTERS &reg) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 12, 15);

    const u32 Rm = reg.read(code, 0, 3);

    if (Rm == 0) {
        reg.write(Rd_id, 32);
    } else {
        reg.write(Rd_id, 31 - (std::bit_width(Rm) - 1));
    }

    reg.increment_PC();
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
void instructions::arm::logic::EOR(const arm_code_t &code, REGISTERS &reg) {
    
}