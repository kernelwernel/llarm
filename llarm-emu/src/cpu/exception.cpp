#include "shared/types.hpp"
#include "../constants.hpp"
#include "../id.hpp"
#include "exception.hpp"

#include <map>

// TODO If an exception occurs when the processor is in a 26-bit mode, only the PC bits from R15[25:2] are
// copied to the link register. The remaining bits in the link register are zeroed. The PSR bits from
// R15[31:26] and R15[1:0] are copied into the SPSR, ready for a normal 32-bit return sequence.

// TODO check the PC increment thingy with the current instruction, i don't think what i did was right with the +8 thing (A6-3)

/*
 * R14_svc = UNPREDICTABLE value
 * SPSR_svc = UNPREDICTABLE value
 * CPSR[4:0] = 0b10011     // Enter Supervisor mode
 * CPSR[5] = 0             // Execute in ARM state
 * CPSR[6] = 1             // Disable fast interrupts
 * CPSR[7] = 1             // Disable normal interrupts
 * if high vectors configured then
 *   PC = 0xFFFF0000
 * else
 *   PC = 0x00000000
 */
void EXCEPTION::reset() {
    reg.switch_mode(id::mode::SUPERVISOR);
    reg.write(id::cpsr::T, 0);
    reg.write(id::cpsr::F, 1);
    reg.write(id::cpsr::I, 1);

    if (coprocessor.read(id::cp::CP15_R1_V)) {
        reg.write(id::reg::PC, 0xFFFF0000);
    } else {
        reg.write(id::reg::PC, 0x00000000);
    }
}


/*
 * R14_und = address of next instruction after the undefined instruction
 * SPSR_und = CPSR
 * CPSR[4:0] = 0b11011 // Enter Undefined mode
 * CPSR[5] = 0  // Execute in ARM state
 * CPSR[7] = 1  // Disable normal interrupts
 * if high vectors configured then
 * PC = 0xFFFF0004
 * else
 * PC = 0x00000004
 */
void EXCEPTION::undefined() {
    u8 inc = 0;

    if (reg.read(id::cpsr::T)) { // is in thumb mode
        inc = 2;
    } else { // is in arm mode
        inc = 4;
    }

    reg.switch_mode(id::mode::UNDEFINED);
    reg.write(id::reg::R14_und, reg.read(id::reg::PC) + inc);
    reg.write(id::reg::SPSR_und, reg.CPSR);
    reg.write(id::cpsr::T, 0);
    reg.write(id::cpsr::I, 1);

    if (coprocessor.read(id::cp::CP15_R1_V)) {
        reg.write(id::reg::PC, 0xFFFF0004);
    } else {
        reg.write(id::reg::PC, 0x00000004);
    }
}


/*
 * R14_svc = address of next instruction after the SWI instruction
 * SPSR_svc = CPSR
 * CPSR[4:0] = 0b10011 // Enter Supervisor mode
 * CPSR[5] = 0 // Execute in ARM state
 * CPSR[7] = 1 // Disable normal interrupts
 * if high vectors configured then
 *   PC = 0xFFFF0008
 * else
 *   PC = 0x00000008
 */
void EXCEPTION::swi() {
    u8 inc = 0;

    if (reg.read(id::cpsr::T)) { // is in thumb mode
        inc = 2;
    } else { // is in arm mode
        inc = 4;
    }

    reg.write(id::reg::R14_svc, reg.read(id::reg::PC) + inc);
    reg.write(id::reg::SPSR_svc, reg.CPSR);
    reg.switch_mode(id::mode::SUPERVISOR);
    reg.write(id::cpsr::T, 0);
    reg.write(id::cpsr::I, 1);

    if (coprocessor.read(id::cp::CP15_R1_V)) {
        reg.write(id::reg::PC, 0xFFFF0008);
    } else {
        reg.write(id::reg::PC, 0x00000008);
    }
}




/*
 * R14_abt = address of the aborted instruction + 4
 * SPSR_abt = CPSR
 * CPSR[4:0] = 0b10111 // Enter Abort mode
 * CPSR[5] = 0 // Execute in ARM state
 * CPSR[7] = 1 // Disable normal interrupts
 * if high vectors configured then
 *   PC = 0xFFFF000C
 * else
 *   PC = 0x0000000C
 */
void EXCEPTION::prefetch_abort() {
    reg.switch_mode(id::mode::ABORT);
    reg.write(id::reg::R14_abt, reg.read(id::reg::PC) + 4);
    reg.write(id::reg::SPSR_abt, reg.CPSR);
    reg.write(id::cpsr::T, 0);
    reg.write(id::cpsr::I, 1);

    if (coprocessor.read(id::cp::CP15_R1_V)) {
        reg.write(id::reg::PC, 0xFFFF000C);
    } else {
        reg.write(id::reg::PC, 0x0000000C);
    }
}


/*
 * R14_abt = address of the aborted instruction + 8
 * SPSR_abt = CPSR
 * CPSR[4:0] = 0b10111 // Enter Abort mode
 * CPSR[5] = 0 // Execute in ARM state
 * CPSR[7] = 1 // Disable normal interrupts
 * if high vectors configured then
 *   PC = 0xFFFF0010
 * else
 *   PC = 0x00000010
 */ 
void EXCEPTION::data_abort() {
    reg.switch_mode(id::mode::ABORT);
    reg.write(id::reg::R14_abt, reg.read(id::reg::PC) + 8);
    reg.write(id::reg::SPSR_abt, reg.CPSR);
    reg.write(id::cpsr::T, 0);
    reg.write(id::cpsr::I, 1);

    if (coprocessor.read(id::cp::CP15_R1_V)) {
        reg.write(id::reg::PC, 0xFFFF0010);
    } else {
        reg.write(id::reg::PC, 0x00000010);
    }
}


/*
 * R14_irq = address of next instruction to be executed + 4
 * SPSR_irq = CPSR
 * CPSR[4:0] = 0b10010 // Enter IRQ mode
 * CPSR[5] = 0 // Execute in ARM state
 * CPSR[7] = 1 // Disable normal interrupts
 * if high vectors configured then
 *   PC = 0xFFFF0018
 * else
 *   PC = 0x00000018
 */
void EXCEPTION::irq() {
    reg.switch_mode(id::mode::IRQ);
    reg.write(id::reg::R14_irq, reg.read(id::reg::PC) + 4);
    reg.write(id::reg::SPSR_irq, reg.CPSR);
    reg.write(id::cpsr::T, 0);
    reg.write(id::cpsr::I, 1);

    if (coprocessor.read(id::cp::CP15_R1_V)) {
        reg.write(id::reg::PC, 0xFFFF0018);
    } else {
        reg.write(id::reg::PC, 0x00000018);
    }
}


/*
 * R14_fiq = address of next instruction to be executed + 4
 * SPSR_fiq = CPSR
 * CPSR[4:0] = 0b10001 // Enter FIQ mode
 * CPSR[5] = 0 // Execute in ARM state
 * CPSR[6] = 1 // Disable fast interrupts
 * CPSR[7] = 1 // Disable normal interrupts
 * if high vectors configured then
 *   PC = 0xFFFF001C
 * else
 *   PC = 0x0000001C
 */
void EXCEPTION::fiq() {
    reg.switch_mode(id::mode::FIQ);
    reg.write(id::reg::R14_fiq, reg.read(id::reg::PC) + 4);
    reg.write(id::reg::SPSR_fiq, reg.CPSR);
    reg.write(id::cpsr::T, 0);
    reg.write(id::cpsr::F, 1);
    reg.write(id::cpsr::I, 1);

    if (coprocessor.read(id::cp::CP15_R1_V)) {
        reg.write(id::reg::PC, 0xFFFF001C);
    } else {
        reg.write(id::reg::PC, 0x0000001C);
    }
}


EXCEPTION::EXCEPTION(
    REGISTERS& reg, 
    COPROCESSOR& coprocessor
) : reg(reg), coprocessor(coprocessor) {

}