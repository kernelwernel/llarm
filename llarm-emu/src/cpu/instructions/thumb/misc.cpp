#include "shared/types.hpp"
#include "../../../utility.hpp"
#include "../../instructions/instructions.hpp"
#include "../../core/registers.hpp"

void INSTRUCTIONS::thumb::misc::NOP(const thumb_code_t &code) noexcept {
    std::exit(0);
    ;
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
void INSTRUCTIONS::thumb::misc::BKPT(const thumb_code_t &code) {
    if (settings.has_debug_hardware) {
        // TODO: switch to the debug hardware functionality (idk how)
        ;
        return;
    }

    // IGNORED BY THE ARM HARDWARE, only here for debug purposes
    // const u8 immed_8 = shared::util::bit_range<u8>(code, 0, 7);

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
void INSTRUCTIONS::thumb::misc::SWI(const thumb_code_t &code) {
    // IGNORED BY THE ARM HARDWARE, only here for debug purposes
    // const u8 immed_8 = shared::util::bit_range<u8>(code, 0, 7);

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