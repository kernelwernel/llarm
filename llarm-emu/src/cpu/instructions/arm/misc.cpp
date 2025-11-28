#include "../../core/registers.hpp"
#include "../instructions.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"

void INSTRUCTIONS::arm::misc::NOP(const u32 code) {
    return;
}


/** TODO, this part needs to be extensively analysed (A2-9)
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
 *    if R15[1:0] == 0b00 then // M[1:0] == 0b00, User mode
 *        R15[31:28] = <alu_out>[31:28] // update just NZCV
 *    else // a privileged mode
 *        R15[31:26] = <alu_out>[31:26] // update NZCVIF and ...
 *        R15[1:0] = <alu_out>[1:0] // ... update M[1:0]
 */
void INSTRUCTIONS::arm::misc::PSR(const u32 code) {
    const u8 opc = llarm::util::bit_range<u8>(code, 21, 22);
    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);

    const data_struct shifter_operand = address_mode.data_processing(code);
    
    u32 alu_out = 0;

    bool C = false;
    bool V = false;

    switch (opc) {
        case 0b00: alu_out = (reg.read(Rn_id) & shifter_operand.value); break;
        case 0b01: alu_out = (reg.read(Rn_id) ^ shifter_operand.value); break;
        case 0b10: // substraction
            alu_out = (reg.read(Rn_id) - shifter_operand.value); 
            V = operation.signed_overflow_sub(reg.read(Rn_id), shifter_operand.value);
            C = !operation.borrow_sub(reg.read(Rn_id), shifter_operand.value);
            break;

        case 0b11: // addition
            alu_out = (reg.read(Rn_id) + shifter_operand.value);
            V = operation.signed_overflow_add(reg.read(Rn_id), shifter_operand.value);
            C = operation.borrow_add(reg.read(Rn_id), shifter_operand.value);
            break;
    }

    reg.write(id::cpsr::N, (llarm::util::bit_fetch(alu_out, 31)));
    reg.write(id::cpsr::Z, (alu_out == 0));
    reg.write(id::cpsr::C, C);
    reg.write(id::cpsr::V, V);

    if ((reg.read(id::reg::R15) & 0b11) == 0b00) { // user mode
        return; // all the flag bit updates are done
    } else { // privileged
        reg.write(id::cpsr::I, (0));// TODO
        reg.write(id::cpsr::F, (0));// TODO
        reg.write(id::cpsr::M, (0));// TODO
    }
}


/**
 * if ConditionPassed(cond) then
 *   R14_svc = address of next instruction after the SWI instruction
 *   SPSR_svc = CPSR
 *   CPSR[4:0] = 0b10011 // Enter Supervisor mode
 *   CPSR[5] = 0 // Execute in ARM state
 *   CPSR[7] = 1 // Disable normal interrupts
 *   if high vectors configured then
 *     PC = 0xFFFF0008
 *   else
 *     PC = 0x00000008
 */
void INSTRUCTIONS::arm::misc::SWI(const u32 code) {
    reg.switch_mode(id::mode::SUPERVISOR);
    reg.write(id::reg::R14_svc, reg.read(id::reg::PC) + 4);
    reg.write(id::reg::SPSR_svc, reg.CPSR);
    reg.write(id::cpsr::T, 0);
    reg.write(id::cpsr::I, 1);

    if (coprocessor.read(id::cp15::R1_V)) {
        reg.write(id::reg::PC, 0xFFFF0008);
    } else {
        reg.write(id::reg::PC, 0x00000008);
    }
}


/**
 * if (not overridden by debug hardware)
 *     R14_abt = address of BKPT instruction + 4
 *     SPSR_abt = CPSR
 *     CPSR[4:0] = 0b10111 // Enter Abort mode
 *     CPSR[5] = 0 // Execute in ARM state
 *     CPSR[7] = 1 // Disable normal interrupts
 *     if high vectors configured then
 *         PC = 0xFFFF000C
 *     else
 *         PC = 0x0000000C
 */
void INSTRUCTIONS::arm::misc::BKPT(const u32 code) {
    reg.switch_mode(id::mode::ABORT);

    reg.write(id::reg::R14_abt, reg.read(id::reg::PC) + 4);
    reg.write(id::reg::SPSR_abt, reg.read(id::reg::CPSR));
    reg.write(id::cpsr::T, false);
    reg.write(id::cpsr::I, true);

    if (coprocessor.read(id::cp15::R1_V)) {
        reg.write(id::reg::PC, 0xFFFF000C);
    } else {
        reg.write(id::reg::PC, 0x0000000C);   
    }
}