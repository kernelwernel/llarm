#include "cpu/instructions/instructions.hpp"
#include "types.hpp"
#include "utility.hpp"
#include "operations.hpp"
#include <iostream>

void instructions::arm::misc::NOP([[maybe_unused]] const arm_code_t &code, [[maybe_unused]] REGISTERS& reg) noexcept {
    return;
}


/** TODO (A2-9)
 * if ConditionPassed(<cond>) then
 *    case <opc> of
 *        0b00 // TSTP
 *            <alu_out> = Rn AND <shifter_operand>
 *        0b01 // TEQP
 *            <alu_out> = Rn EOR <shifter_operand>
 *        0b10 // CMPP
 *            <alu_out> = Rn - <shifter_operand>
 *        0b11 // CMNP
 *            <alu_out> = Rn + <shifter_operand>
 *    endcase
 *    if R15[1:0] == 0b00 then /* M[1:0] == 0b00, User mode
 *        R15[31:28] = <alu_out>[31:28] // update just NZCV
 *    else // a privileged mode
 *        R15[31:26] = <alu_out>[31:26] // update NZCVIF and ...
 *        R15[1:0] = <alu_out>[1:0] // ... update M[1:0]
 */
void instructions::arm::misc::PSR(const arm_code_t &code, [[maybe_unused]] REGISTERS& reg) noexcept {
    const u8 opc = util::bit_fetcher(code, 21, 22);
    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);
    const u16 shifter_operand = util::bit_fetcher(code, 0, 11);
    
    u32 alu_out = 0;

    bool C = false;
    bool V = false;

    switch (opc) {
        case 0b00: alu_out = (reg.read(Rn_id) & shifter_operand); break;
        case 0b01: alu_out = (reg.read(Rn_id) ^ shifter_operand); break;
        case 0b10: // substraction
            alu_out = (reg.read(Rn_id) - shifter_operand); 
            V = operation::signed_overflow_sub(reg.read(Rn_id), shifter_operand);
            C = !operation::borrow_sub(reg.read(Rn_id), shifter_operand);
            break;

        case 0b11: // addition
            alu_out = (reg.read(Rn_id) + shifter_operand);
            V = operation::signed_overflow_add(reg.read(Rn_id), shifter_operand);
            C = operation::borrow_add(reg.read(Rn_id), shifter_operand);
            break;
    }

    reg.write_cpsr(id::cpsr::N, (alu_out & (1 << 31)));
    reg.write_cpsr(id::cpsr::Z, (alu_out == 0));
    reg.write_cpsr(id::cpsr::C, C);
    reg.write_cpsr(id::cpsr::V, V);


    if ((reg.read(id::reg::R15) & 0b11) == 0b00) { // user mode
        return; // all the flag bit updates are done
    } else { // privileged
        reg.write_cpsr(id::cpsr::I, ());
        reg.write_cpsr(id::cpsr::F, ());

        reg.write_cpsr(id::cpsr::M, ());
    }
}

