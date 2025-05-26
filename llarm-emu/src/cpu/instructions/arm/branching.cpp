#include "../../instructions/instructions.hpp"
#include "../../core/registers.hpp"

#include "shared/types.hpp"

/*
 * if ConditionPassed(cond) then
 *   if L == 1 then
 *     LR = address of the instruction after the branch instruction
 *   PC = PC + (SignExtend(signed_immed_24) << 2)
 */
void INSTRUCTIONS::arm::branching::B(const arm_code_t &code) {
    const i32 signed_immed_24 = shared::util::bit_range<i32>(code, 0, 23);
    const bool L = code.test(24);

    if (L == 1) {
        reg.write(id::reg::LR, reg.read(id::reg::PC) + 4); // TODO: check if this is correct
    }

    const u32 address = (reg.read(id::reg::PC) + (operation.sign_extend(signed_immed_24, 23) << 2) + 4);

    // All 32 bits are stored in the Link register (R14) after a Branch with Link instruction or an exception entry.

    reg.write(id::reg::PC, address);
}


/*
 * same as B but with L bit as true. This is separate to the B instruction
 * for the sake of standardised structures without having edgecases
 */
void INSTRUCTIONS::arm::branching::BL(const arm_code_t &code) {
    B(code);
}


/*
 * if ConditionPassed(cond) then
 *   T Flag = Rm[0]
 *   PC = Rm AND 0xFFFFFFFE
 */
// TODO
void INSTRUCTIONS::arm::branching::BX(const arm_code_t &code) {
    const u32 Rm = reg.read(code, 0, 3);

    reg.write(id::cpsr::T, (Rm & 1));

    reg.write(id::reg::PC, (Rm & 0xFFFFFFFE));
}


void INSTRUCTIONS::arm::branching::BLX1(const arm_code_t &code) {
    // TODO
}


void INSTRUCTIONS::arm::branching::BLX2(const arm_code_t &code) {
    // TODO
}