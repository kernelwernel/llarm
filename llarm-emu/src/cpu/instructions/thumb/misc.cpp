#include "../../instructions/instructions.hpp"
#include "../../core/registers.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>

/**
 * if InAPrivilegedMode() then
 * if A == 1 then CPSR[8] = imod
 * if I == 1 then CPSR[7] = imod
 * if F == 1 then CPSR[6] = imod
 * // else no change to interrupt disable bits
 */
void INSTRUCTIONS::thumb::misc::CPS(const u16 code) {
    if (!reg.is_privileged()) {
        return;
    }

    const bool disable   = llarm::util::bit_fetch(code, 4);
    const bool affect_A  = llarm::util::bit_fetch(code, 2);
    const bool affect_I  = llarm::util::bit_fetch(code, 1);
    const bool affect_F  = llarm::util::bit_fetch(code, 0);

    if (affect_I) {
        reg.write(id::cpsr::I, disable);
    }

    if (affect_F) {
        reg.write(id::cpsr::F, disable);
    }

    if (affect_A) {
        reg.write(id::cpsr::A, disable);
    }
}


void INSTRUCTIONS::thumb::misc::NOP() {
    // literally nothing happens here
}

/**
 * if (not overridden by debug hardware)
 *     R14_abt = address of BKPT instruction + 4
 *     SPSR_abt = CPSR
 *     CPSR[4:0] = 0b10111 // Enter Abort mode
 *     CPSR[5] = 0 // Execute in ARM state
 *     // CPSR[6] is unchanged
 *     CPSR[7] = 1 // Disable normal interrupts
 *     if high vectors configured then
 *         PC = 0xFFFF000C
 *     else 
 *         PC = 0x0000000C
 */
void INSTRUCTIONS::thumb::misc::BKPT(const u16 code) {
    (void)code; // TODO
    if (settings.has_debug_hardware) {
        // TODO: switch to the debug hardware functionality (idk how)
    
        return;
    }

    // IGNORED BY THE ARM HARDWARE, only here for debug purposes
    // const u8 immed_8 = llarm::util::bit_range<u8>(code, 0, 7);

    reg.write(id::reg::R14_abt, (reg.read(id::reg::PC) + 4));
    reg.write(id::reg::SPSR_abt, (reg.read(id::reg::CPSR)));
    reg.switch_mode(id::mode::ABORT);
    reg.write(id::cpsr::T, false);
    reg.write(id::cpsr::I, true);

    if (settings.has_high_vectors) {
        reg.write(id::reg::PC, 0xFFFF000C);
    } else {
        reg.write(id::reg::PC, 0x0000000C);
    }
}


/**
 * R14_svc = address of next instruction after the SWI instruction
 * SPSR_svc = CPSR
 * CPSR[4:0] = 0b10011 // Enter Supervisor mode
 * CPSR[5] = 0 // Execute in ARM state
 * // CPSR[6] is unchanged
 * CPSR[7] = 1 // Disable normal interrupts
 * if high vectors configured then
 *   PC = 0xFFFF0008
 * else
 *   PC = 0x00000008
 */
void INSTRUCTIONS::thumb::misc::SWI() {
    // IGNORED BY THE ARM HARDWARE, only here for debug purposes
    // const u8 immed_8 = llarm::util::bit_range<u8>(code, 0, 7);

    reg.write(id::reg::R14_svc, (reg.read(id::reg::PC) + 2));
    reg.write(id::reg::SPSR_svc, (reg.read(id::reg::CPSR)));
    reg.switch_mode(id::mode::SUPERVISOR);
    reg.write(id::cpsr::T, false);
    reg.write(id::cpsr::I, true);

    if (settings.has_high_vectors) {
        reg.write(id::reg::PC, 0xFFFF0008);
    } else {
        reg.write(id::reg::PC, 0x00000008);
    }
}


/**
 * CPSR = CPSR with specified E bit modification
 */
void INSTRUCTIONS::thumb::misc::SETEND(const u16 code) {
    const bool E = llarm::util::bit_fetch(code, 3);
    u32 cpsr = reg.read(id::reg::CPSR);
    llarm::util::modify_bit(cpsr, 9, E);
    reg.write(id::reg::CPSR, cpsr);
}