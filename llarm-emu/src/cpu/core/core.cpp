#include "core.hpp"
#include "src/id.hpp"

#include <llarm/shared/types.hpp>

#include <llarm/llarm-asm.hpp>


inline void CORE::arm_cycle_headless() {
    const arm_fetch_struct arm_code_access = fetch.arm_fetch();

    if (arm_code_access.has_failed) {
        return;
    }

    const arm_decode_struct instruction = decode.arm_decode(arm_code_access.code);

    execute.arm_execute(instruction);

    reg.arm_increment_PC();
}


inline void CORE::arm_cycle() {
    continue_cycle = false;

    const arm_fetch_struct arm_code_access = fetch.arm_fetch();

    if (arm_code_access.has_failed) {
        return;
    }

    current_arm_code = arm_code_access.code;
    
    const arm_decode_struct instruction = decode.arm_decode(arm_code_access.code);
    current_arm_id = instruction.id;

    execute.arm_execute(instruction);

    while (true) {
        if (continue_cycle == true) {
            break;
        }
    }

    reg.arm_increment_PC();
}


inline void CORE::thumb_cycle() {
    continue_cycle = false;

    const thumb_fetch_struct thumb_code_access = fetch.thumb_fetch();

    if (thumb_code_access.has_failed) {
        return;
    }

    current_thumb_code = thumb_code_access.code;

    const thumb_decode_struct instruction = decode.thumb_decode(thumb_code_access.code);
    current_thumb_id = instruction.id;

    execute.thumb_execute(instruction);

    while (true) {
        if (continue_cycle == true) {
            break;
        }
    }

    reg.thumb_increment_PC();
}


inline void CORE::thumb_cycle_headless() {
    const thumb_fetch_struct thumb_code_access = fetch.thumb_fetch();

    if (thumb_code_access.has_failed) {
        return;
    }

    const thumb_decode_struct instruction = decode.thumb_decode(thumb_code_access.code);

    execute.thumb_execute(instruction);

    reg.thumb_increment_PC();
}


void CORE::initialise(const bool is_headless) {
    // core reset, setup, and boot
    reg.reset();
    coprocessor.force_write(id::cp15::R1_M, false); // disable MMU/MPU
    coprocessor.force_write(id::cp15::R1_P, true); // set to 32-bit mode (maybe temporary idk)
    coprocessor.force_write(id::cp15::R1_D, true); // set to 32-bit mode (maybe temporary idk)
    // reg.switch_mode(id::mode::SUPERVISOR); only enable for system mode
    reg.switch_mode(id::mode::USER); // only for user programs, temporary
    //reg.write(id::cpsr::T, 1); // switch to thumb  // TODO: double check if it actually starts in thumb mode
    reg.write(id::cpsr::T, 0); // start in ARM mode, temporary
    memory.reset();

    if (!settings.fresh_system) {
        reg.write(id::reg::SP, util::get_kb(16));
    }

    if (is_headless) {
        while (true) {
            if (globals.instruction_set == id::instruction_sets::ARM) {
                arm_cycle_headless();
            } else {
                thumb_cycle_headless();
            }
        }

        return;
    }

    // instruction cycle 
    while (true) {
        switch (globals.instruction_set) {
            case id::instruction_sets::ARM: arm_cycle(); continue;
            case id::instruction_sets::THUMB: thumb_cycle(); continue;
        }
    }
}