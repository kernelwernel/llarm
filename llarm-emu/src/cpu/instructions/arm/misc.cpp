#include "../../core/registers.hpp"
#include "../instructions.hpp"
#include "../operation.hpp"

#include <llarm/shared/out.hpp>
#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>

void INSTRUCTIONS::arm::misc::NOP() {
    // literally does nothing
}


void INSTRUCTIONS::arm::misc::HALT() {
    is_halted = true;
    is_terminated = true;
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
            V = operation::overflow_sub(reg.read(Rn_id), shifter_operand.value);
            C = !operation::borrow_sub(reg.read(Rn_id), shifter_operand.value);
            break;

        case 0b11: // addition
            alu_out = (reg.read(Rn_id) + shifter_operand.value);
            V = operation::overflow_add(reg.read(Rn_id), shifter_operand.value);
            C = !operation::borrow_add(reg.read(Rn_id), shifter_operand.value);
            break;
    }

    reg.write(id::cpsr::N, (llarm::util::bit_fetch(alu_out, 31)));
    reg.write(id::cpsr::Z, (alu_out == 0));
    reg.write(id::cpsr::C, C);
    reg.write(id::cpsr::V, V);

    if ((reg.read(id::reg::R15) & 0b11) == 0b00) { // user mode
        return; // all the flag bit updates are done
    }

    // privileged
    reg.write(id::cpsr::I, 0);// TODO
    reg.write(id::cpsr::F, 0);// TODO
    reg.write(id::cpsr::M, 0);// TODO
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
void INSTRUCTIONS::arm::misc::SWI() {
    const u32 saved_cpsr = reg.read(id::reg::CPSR);
    reg.switch_mode(id::mode::SUPERVISOR);
    reg.write(id::reg::R14_svc, reg.force_read(id::reg::PC) + 4);
    reg.write(id::reg::SPSR_svc, saved_cpsr);
    reg.write(id::cpsr::T, 0);
    reg.write(id::cpsr::I, 1);

    if (coprocessor.read(id::cp15::R1_V)) {
        reg.write(id::reg::PC, 0xFFFF0004);
    } else {
        reg.write(id::reg::PC, 0x00000004);
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
void INSTRUCTIONS::arm::misc::BKPT() {
    const u32 CPSR = reg.read(id::reg::CPSR);
    reg.switch_mode(id::mode::ABORT);
    reg.write(id::reg::R14_abt, reg.force_read(id::reg::PC) + 4);
    reg.write(id::reg::SPSR_abt, CPSR);
    reg.write(id::cpsr::T, false);
    reg.write(id::cpsr::I, true);

    if (coprocessor.read(id::cp15::R1_V)) {
        reg.write(id::reg::PC, 0xFFFF0008);
    } else {
        reg.write(id::reg::PC, 0x00000008);
    }
}


/**
 * if InAPrivilegedMode() then
 *   if imod[1] == 1 then
 *     if A == 1 then CPSR[8] = imod[0]
 *     if I == 1 then CPSR[7] = imod[0]
 *     if F == 1 then CPSR[6] = imod[0]
 *   // else no change to the mask
 *   if mmod == 1 then
 *     CPSR[4:0] = mode
 */
void INSTRUCTIONS::arm::misc::CPS(const u32 code) {
    if (!reg.is_privileged()) {
        return;
    }

    const u8 imod = llarm::util::bit_range<u8>(code, 18, 19);
    const bool mmod = llarm::util::bit_fetch(code, 17);

    const bool affect_A = llarm::util::bit_fetch(code, 8);
    const bool affect_I = llarm::util::bit_fetch(code, 7);
    const bool affect_F = llarm::util::bit_fetch(code, 6);

    if (llarm::util::bit_fetch(imod, 1)) {
        const bool disable = llarm::util::bit_fetch(imod, 0);

        if (affect_A) {
            reg.write(id::cpsr::A, disable);
        }

        if (affect_I) {
            reg.write(id::cpsr::I, disable);
        }

        if (affect_F) {
            reg.write(id::cpsr::F, disable);
        }
    }

    if (mmod) {
        const u8 mode = llarm::util::bit_range<u8>(code, 0, 4);
        reg.write(id::cpsr::M, mode);
    }
}


/**
 * CPSR = CPSR with specified E bit modification
 */
void INSTRUCTIONS::arm::misc::SETEND(const u32 code) {
    const bool E = llarm::util::bit_fetch(code, 9);
    reg.write(id::cpsr::E, E);
}


/**
 * address = start_address
 * value = Memory[address,4]
 * if InAPrivilegedMode() then
 *     CPSR = Memory[address+4,4]
 * else
 *     UNPREDICTABLE
 * PC = value
 *
 * assert end_address == address + 8
 */
void INSTRUCTIONS::arm::misc::RFE(const u32 code) {
    const bool P = llarm::util::bit_fetch(code, 24);
    const bool U = llarm::util::bit_fetch(code, 23);
    const bool W = llarm::util::bit_fetch(code, 21);
    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);

    const u32 base = reg.read(Rn_id);

    u32 start_address = 0;

    if (!P && U) {
        start_address = base;
    } else if (P && U) {
        start_address = base + 4;
    } else if (!P && !U) {
        start_address = base - 4;
    } else {
        start_address = base - 8;
    }

    if (W) {
        reg.write(Rn_id, U ? (base + 8) : (base - 8));
    }

    if (!reg.is_privileged()) {
        llarm::out::unpredictable("RFE executed outside a privileged mode");
    }

    const mem_read_struct pc_access = memory.read(start_address, 4);

    if (pc_access.has_failed) {
        memory.manage_abort(pc_access.abort_code);
        return;
    }

    const mem_read_struct cpsr_access = memory.read(start_address + 4, 4);

    if (cpsr_access.has_failed) {
        memory.manage_abort(cpsr_access.abort_code);
        return;
    }

    reg.write(id::reg::CPSR, static_cast<u32>(cpsr_access.value));
    reg.write(id::reg::PC, static_cast<u32>(pc_access.value));
}


/**
 * MemoryAccess(B-bit, E-bit)
 * processor_id = ExecutingProcessor()
 * address = start_address
 * Memory[address,4] = R14
 * if Shared(address) then // from ARMv6
 *      physical_address = TLB(address)
 *      ClearExclusiveByAddress(physical_address,processor_id,4)
 * if CurrentModeHasSPSR() then
 *      Memory[address+4,4] = SPSR
 *      if Shared(address+4) then // from ARMv6
 *          physical_address = TLB(address+4)
 *          ClearExclusiveByAddress(physical_address,processor_id,4)
 * else
 *      UNPREDICTABLE
 * assert end_address == address + 8
 */
void INSTRUCTIONS::arm::misc::SRS(const u32 code) {
    const bool P = llarm::util::bit_fetch(code, 24);
    const bool U = llarm::util::bit_fetch(code, 23);
    const bool W = llarm::util::bit_fetch(code, 21);
    const u8 mode_bits = llarm::util::bit_range<u8>(code, 0, 4);

    const id::mode target_mode = reg.fetch_mode_id(mode_bits);

    id::reg R13_id = id::reg::R13;
    id::reg R14_id = id::reg::R14;
    id::reg SPSR_id = id::reg::SPSR;

    switch (target_mode) {
        case id::mode::FIQ:
        case id::mode::FIQ_26:
            R13_id = id::reg::R13_fiq;
            R14_id = id::reg::R14_fiq;
            SPSR_id = id::reg::SPSR_fiq;
            break;

        case id::mode::IRQ:
        case id::mode::IRQ_26:
            R13_id = id::reg::R13_irq;
            R14_id = id::reg::R14_irq;
            SPSR_id = id::reg::SPSR_irq;
            break;

        case id::mode::SUPERVISOR:
        case id::mode::SUPERVISOR_26:
            R13_id = id::reg::R13_svc;
            R14_id = id::reg::R14_svc;
            SPSR_id = id::reg::SPSR_svc;
            break;

        case id::mode::ABORT:
            R13_id = id::reg::R13_abt;
            R14_id = id::reg::R14_abt;
            SPSR_id = id::reg::SPSR_abt;
            break;

        case id::mode::UNDEFINED:
            R13_id = id::reg::R13_und;
            R14_id = id::reg::R14_und;
            SPSR_id = id::reg::SPSR_und;
            break;

        default:
            llarm::out::unpredictable("SRS specified a mode with no banked SPSR");
            return;
    }

    const u32 base = reg.read(R13_id);

    u32 start_address = 0;

    if (!P && U) {
        start_address = base;
    } else if (P && U) {
        start_address = base + 4;
    } else if (!P && !U) {
        start_address = base - 4;
    } else {
        start_address = base - 8;
    }

    if (W) {
        reg.write(R13_id, U ? (base + 8) : (base - 8));
    }

    const mem_write_struct r14_access = memory.write(start_address, reg.read(R14_id), 4);

    if (r14_access.has_failed) {
        memory.manage_abort(r14_access.abort_code);
        return;
    }

    const mem_write_struct spsr_access = memory.write(start_address + 4, reg.read(SPSR_id), 4);

    if (spsr_access.has_failed) {
        memory.manage_abort(spsr_access.abort_code);
        return;
    }
}