#include "cpu/instructions/instructions.hpp"
#include "types.hpp"
#include "utility.hpp"
#include "settings.hpp"
#include <iostream>

void instructions::thumb::misc::NOP([[maybe_unused]] const thumb_code_t &code, [[maybe_unused]] REGISTERS& reg) noexcept {
    return;
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
void instructions::thumb::misc::BKPT(const thumb_code_t &code, REGISTERS& reg) {
    if (settings.has_debug_hardware) {
        // TODO: switch to the debug hardware functionality (idk how)
        reg.thumb_increment_PC();
        return;
    }

    const u8 immed_8 = util::bit_fetcher<u8>(code, 0, 7);

    reg.write(id::reg::R14_abt, (reg.read(id::reg::PC) + 4));
    reg.write(id::reg::SPSR_abt, (reg.read(id::reg::CPSR)));
    reg.switch_mode(id::mode::ABORT);
    reg.write(id::cpsr::T, false);
    reg.write(id::cpsr::I, true);

    if (settings.has_high_vectors) {
        reg.write(id::reg::PC, (0xFFFF000C));
    } else {
        reg.write(id::reg::PC, (0x0000000C));
    }
}

// TODO
void instructions::thumb::misc::SWI(const thumb_code_t &code, REGISTERS& reg) {
    const u8 immed_8 = util::bit_fetcher<u8>(code, 0, 7);
    // CONTINUE
}