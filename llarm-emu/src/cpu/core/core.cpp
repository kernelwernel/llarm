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

    timer.tick();

    if (timer.irq_pending()) { 
        vic.raise_irq(settings.timer_irq_source);
    } else { 
        vic.clear_irq(settings.timer_irq_source);
    }
     
    if (vic.fiq_pending() && !reg.read(id::cpsr::F)) { exception.fiq(); return; }
    if (vic.irq_pending() && !reg.read(id::cpsr::I)) { exception.irq(); return; }

    reg.arm_increment_PC();
}


inline void CORE::arm_cycle_step() {
    continue_cycle = false;
    execution_done = false;
    current_pc = reg.force_read(id::reg::R15);

    const arm_fetch_struct arm_code_access = fetch.arm_fetch();

    if (arm_code_access.has_failed) {
        return;
    }

    current_arm_code = arm_code_access.code;

    const arm_decode_struct instruction = decode.arm_decode(arm_code_access.code);

    current_arm_id = instruction.id;

    execute.arm_execute(instruction);

    execution_done = true;

    while (!continue_cycle.load()) {
        // wait till continue_cycle variable is true
    }

    //std::cout << "reached end of cycle\n";

    timer.tick();

    if (timer.irq_pending()) { 
        vic.raise_irq(settings.timer_irq_source);
    } else { 
        vic.clear_irq(settings.timer_irq_source);
    }
     
    if (vic.fiq_pending() && !reg.read(id::cpsr::F)) { exception.fiq(); return; }
    if (vic.irq_pending() && !reg.read(id::cpsr::I)) { exception.irq(); return; }

    reg.arm_increment_PC();
}


inline void CORE::thumb_cycle_step() {
    continue_cycle = false;
    execution_done = false;
    current_pc = reg.force_read(id::reg::R15);

    const thumb_fetch_struct thumb_code_access = fetch.thumb_fetch();

    if (thumb_code_access.has_failed) {
        return;
    }

    current_thumb_code = thumb_code_access.code;

    const thumb_decode_struct instruction = decode.thumb_decode(thumb_code_access.code);
    current_thumb_id = instruction.id;

    execute.thumb_execute(instruction);

    execution_done = true;

    while (true) {
        if (continue_cycle == true) {
            break;
        }
    }

    timer.tick();

    if (timer.irq_pending()) { 
        vic.raise_irq(settings.timer_irq_source);
    } else { 
        vic.clear_irq(settings.timer_irq_source);
    }

    if (vic.fiq_pending() && !reg.read(id::cpsr::F)) { exception.fiq(); return; }
    if (vic.irq_pending() && !reg.read(id::cpsr::I)) { exception.irq(); return; }

    reg.thumb_increment_PC();
}


inline void CORE::thumb_cycle_headless() {
    const thumb_fetch_struct thumb_code_access = fetch.thumb_fetch();

    if (thumb_code_access.has_failed) {
        return;
    }

    const thumb_decode_struct instruction = decode.thumb_decode(thumb_code_access.code);

    execute.thumb_execute(instruction);

    timer.tick();

    if (timer.irq_pending()) { 
        vic.raise_irq(settings.timer_irq_source); 
    } else { 
        vic.clear_irq(settings.timer_irq_source); 
    }

    if (vic.fiq_pending() && !reg.read(id::cpsr::F)) { exception.fiq(); return; }
    if (vic.irq_pending() && !reg.read(id::cpsr::I)) { exception.irq(); return; }

    reg.thumb_increment_PC();
}


void CORE::headless_mode() {
    while (true) {
        if (is_halted) {
            if (is_terminated) {
                return;
            }

            timer.tick();

            if (timer.irq_pending()) {
                vic.raise_irq(settings.timer_irq_source);
            } else {
                vic.clear_irq(settings.timer_irq_source);
            }

            if (vic.fiq_pending() && !reg.read(id::cpsr::F)) {
                is_halted = false;
                exception.fiq();
            } else if (vic.irq_pending() && !reg.read(id::cpsr::I)) {
                is_halted = false;
                exception.irq();
            }

            continue;
        }

        if (globals.instruction_set == id::instruction_sets::ARM) {
            arm_cycle_headless();
        } else {
            thumb_cycle_headless();
        }
    }
}


void CORE::step_mode() {
    while (true) {
        if (is_halted) {
            timer.tick();

            if (timer.irq_pending()) {
                vic.raise_irq(settings.timer_irq_source);
            } else {
                vic.clear_irq(settings.timer_irq_source);
            }

            if (vic.fiq_pending() && !reg.read(id::cpsr::F)) {
                is_halted = false;
                exception.fiq();
            } else if (vic.irq_pending() && !reg.read(id::cpsr::I)) {
                is_halted = false;
                exception.irq();
            }

            continue;
        }

        if (globals.instruction_set == id::instruction_sets::ARM) {
            arm_cycle_step();
        } else {
            thumb_cycle_step();
        }
    }
}


void CORE::initialise(const bool is_headless) {
    globals.is_little_endian = settings.is_little_endian;
    reg.reset();
    coprocessor.force_write(id::cp15::R1_M, false);
    coprocessor.force_write(id::cp15::R1_P, true);
    coprocessor.force_write(id::cp15::R1_D, true);

    if (settings.linux_boot) {
        reg.switch_mode(id::mode::SUPERVISOR);
        reg.write(id::cpsr::I, 1);
        reg.write(id::cpsr::F, 1);
        reg.write(id::cpsr::T, 0);
        reg.write(id::reg::R0, 0);
        reg.write(id::reg::R1, settings.machine_type);
        reg.write(id::reg::R2, settings.dtb_load_address);
        reg.force_write(id::reg::R15, settings.binary_load_address);
    } else {
        reg.switch_mode(id::mode::USER);
        reg.write(id::cpsr::T, 0);
        if (!settings.fresh_system) {
            reg.write(id::reg::SP, util::get_kb(16));
        }
    }

    memory.reset();

    if (is_headless) {
        headless_mode();
        return;
    }

    step_mode();
}