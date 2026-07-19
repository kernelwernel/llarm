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

    const sync_enum sync_code = synchronise();

    if (sync_code != sync_enum::NONE) {
        return;
    }

    reg.arm_increment_PC();
}


inline void CORE::arm_cycle_step() {
    current_pc = reg.force_read(id::reg::R15);

    const arm_fetch_struct arm_code_access = fetch.arm_fetch();

    if (arm_code_access.has_failed) {
        return;
    }

    current_arm_code = arm_code_access.code;

    const arm_decode_struct instruction = decode.arm_decode(arm_code_access.code);

    current_arm_id = instruction.id;

    execute.arm_execute(instruction);

    const u64 my_seq = exec_seq.fetch_add(1, std::memory_order_acq_rel) + 1;

    while (go_seq.load(std::memory_order_acquire) < my_seq) {
        // wait till the controller has released this cycle
    }

    const sync_enum sync_code = synchronise();

    if (sync_code != sync_enum::NONE) {
        return;
    }

    reg.arm_increment_PC();
}


inline void CORE::thumb_cycle_step() {
    current_pc = reg.force_read(id::reg::R15);

    const thumb_fetch_struct thumb_code_access = fetch.thumb_fetch();

    if (thumb_code_access.has_failed) {
        return;
    }

    current_thumb_code = thumb_code_access.code;

    const thumb_decode_struct instruction = decode.thumb_decode(thumb_code_access.code);
    current_thumb_id = instruction.id;

    execute.thumb_execute(instruction);

    const u64 my_seq = exec_seq.fetch_add(1, std::memory_order_acq_rel) + 1;

    while (go_seq.load(std::memory_order_acquire) < my_seq) {
        // wait till the controller has released this cycle
    }

    const sync_enum sync_code = synchronise();

    if (sync_code != sync_enum::NONE) {
        return;
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

    const sync_enum sync_code = synchronise();

    if (sync_code != sync_enum::NONE) {
        return;
    }

    reg.thumb_increment_PC();
}


void CORE::headless_mode() {
    // draining host input every single instruction would mean millions of mutex
    // locks per second for no benefit, since keystrokes arrive at human speed
    constexpr u32 HOST_INPUT_POLL_INTERVAL = 100000;
    u32 host_input_poll_counter = 0;

    while (true) {
        if (stop_requested.load(std::memory_order_relaxed)) {
            return;
        }

        if (is_halted) {
            if (is_terminated) {
                return;
            }

            const sync_enum sync_code = synchronise();

            switch (sync_code) {
                case sync_enum::IRQ:
                case sync_enum::FIQ: is_halted = false; continue;
                case sync_enum::NONE:
                case sync_enum::PC: continue;
            }
        }

        if (globals.instruction_set == id::instruction_sets::ARM) {
            arm_cycle_headless();
        } else {
            thumb_cycle_headless();
        }

        ++host_input_poll_counter;

        if (host_input_poll_counter >= HOST_INPUT_POLL_INTERVAL) {
            host_input_poll_counter = 0;
            uart.drain_host_input();
        }
    }
}


void CORE::step_mode() {
    while (true) {
        if (is_halted) {
            const sync_enum sync_code = synchronise();

            switch (sync_code) {
                case sync_enum::IRQ:
                case sync_enum::FIQ: is_halted = false; continue;
                case sync_enum::NONE: 
                case sync_enum::PC: continue;
            }
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
        reg.write(id::reg::SP, settings.memsize);
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


CORE::sync_enum CORE::synchronise() {
    timer.tick();

    if (timer.irq_pending()) { 
        vic.raise_irq(settings.timer_irq_source); 
    } else { 
        vic.clear_irq(settings.timer_irq_source); 
    }

    if (vic.fiq_pending() && !reg.read(id::cpsr::F)) { 
        exception.fiq(); 
        return sync_enum::FIQ;
    }

    if (vic.irq_pending() && !reg.read(id::cpsr::I)) { 
        exception.irq(); 
        return sync_enum::IRQ; 
    }

    // incrementing the PC can clobber it under certain conditions
    // (like exception handingling, branching, etc) so we're avoiding
    // this by letting the core know we shouldn't increment the PC 
    if (reg.pc_finalised) {
        reg.pc_finalised = false;
        return sync_enum::PC;
    }

    return sync_enum::NONE;
}