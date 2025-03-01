#pragma once

#include "id.hpp"
#include "core/registers.hpp"
#include "instruction_set.hpp"
#include "coprocessor.hpp"

struct SYSTEM {
private:
    REGISTERS& reg;
    INSTRUCTION_SET& instruction_set;
    COPROCESSOR& coprocessor;

public:
/*
    void switch_mode(const id::mode mode) {
        switch (mode) {
            case id::mode::USER:       reg.write(id::cpsr::M, constants::mode::USER); return;
            case id::mode::SUPERVISOR: reg.write(id::cpsr::M, constants::mode::SUPERVISOR); return;
            case id::mode::ABORT:      reg.write(id::cpsr::M, constants::mode::ABORT); return;
            case id::mode::UNDEFINED:  reg.write(id::cpsr::M, constants::mode::UNDEFINED); return;
            case id::mode::FIQ:        reg.write(id::cpsr::M, constants::mode::FIQ); return;
            case id::mode::IRQ:        reg.write(id::cpsr::M, constants::mode::IRQ); return;
            case id::mode::SYSTEM:     reg.write(id::cpsr::M, constants::mode::SYSTEM); return;
        }
    }

    id::mode read_mode() {
        switch (read(id::cpsr::M)) {
            case constants::mode::USER: return id::mode::USER;
            case constants::mode::SUPERVISOR: return id::mode::SUPERVISOR;
            case constants::mode::ABORT: return id::mode::ABORT;
            case constants::mode::UNDEFINED: return id::mode::UNDEFINED;
            case constants::mode::FIQ: return id::mode::FIQ;
            case constants::mode::IRQ: return id::mode::IRQ;
            case constants::mode::SYSTEM: return id::mode::SYSTEM;
            default:
                out::error("No known enum value for read_mode()");
        }
    }
*/
    bool is_thumb() noexcept {
        return (reg.read(id::cpsr::T) == 1);
    }

    bool is_arm() noexcept {
        return (reg.read(id::cpsr::T) == 0);
    }

    void switch_to_arm() {
        reg.write(id::cpsr::T, 0);
        globals.instruction_set = id::instruction_sets::ARM;
    }

    void switch_to_thumb() {
        reg.write(id::cpsr::T, 1);
        globals.instruction_set = id::instruction_sets::THUMB;
    }

    void enable_mmu() {
        coprocessor.write_control(id::cp::CP15_R1_M, true);
    }

    void disable_mmu() {
        coprocessor.write_control(id::cp::CP15_R1_M, false);  
    }

    bool switch_to_26_bit_arch() {
        coprocessor.write_cp15(id::cp::CP15_R1_P, false);
        coprocessor.write_cp15(id::cp::CP15_R1_D, false);
    }

    bool switch_to_32_bit_arch() {
        coprocessor.write_cp15(id::cp::CP15_R1_P, true);
        coprocessor.write_cp15(id::cp::CP15_R1_D, true);
    }

    SYSTEM(
        REGISTERS& reg, 
        INSTRUCTION_SET& instruction_set, 
        COPROCESSOR& coprocessor
    ) : reg(reg), instruction_set(instruction_set), coprocessor(coprocessor) {

    }
}


// TODO remove this fucking garbage