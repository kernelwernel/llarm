#pragma once

#include "id.hpp"
#include "types.hpp"
#include "constants.hpp"
#include "coprocessor.hpp"
#include "globals.hpp"

struct REGISTERS {
private:
    COPROCESSOR& coprocessor;
    GLOBALS& globals;

public:
    // unbanked
    u32 R0 = 0;
    u32 R1 = 0;
    u32 R2 = 0;
    u32 R3 = 0;
    u32 R4 = 0;
    u32 R5 = 0;
    u32 R6 = 0;
    u32 R7 = 0;

    // fast interrupt
    u32 R8_fiq = 0;
    u32 R9_fiq = 0;
    u32 R10_fiq = 0;
    u32 R11_fiq = 0;
    u32 R12_fiq = 0;
    u32 R13_fiq = 0;
    u32 R14_fiq = 0;

    // supervisor
    u32 R13_svc = 0;
    u32 R14_svc = 0;

    // abort
    u32 R13_abt = 0;
    u32 R14_abt = 0;

    // undefined 
    u32 R13_und = 0;
    u32 R14_und = 0;

    // interrupt
    u32 R13_irq = 0;
    u32 R14_irq = 0;

    // banked registers (for all modes except FIQ)
    u32 R8 = 0;
    u32 R9 = 0;
    u32 R10 = 0;
    u32 R11 = 0;
    u32 R12 = 0;
    u32 R13 = 0; // only for user and system mode
    u32 R14 = 0; // only for user and system mode

    u32 R15 = 0; // program counter (R15)

    u32 CPSR = 0; // current program status register

    // for all modes except user and system
    u32 SPSR_svc = 0; // saved program status registers
    u32 SPSR_abt = 0;
    u32 SPSR_und = 0;
    u32 SPSR_irq = 0;
    u32 SPSR_fiq = 0;

public:
    [[nodiscard]] id::mode read_mode();

    [[nodiscard]] bool is_priviledged();
    [[nodiscard]] bool is_exception();

    [[nodiscard]] u8 read_cpsr(const id::cpsr);

    void write_cpsr(const id::cpsr, const u8);
    void write_cpsr(const id::reg reg_id);

    [[nodiscard]] id::reg fetch_reg_id(const u8) noexcept;
    [[nodiscard]] id::reg fetch_reg_id(const arm_code_t&, const u8, const u8) noexcept;
    [[nodiscard]] id::reg fetch_reg_id(const thumb_code_t&, const u8, const u8) noexcept;

    [[nodiscard]] id::cond fetch_cond_id(const u8);
    [[nodiscard]] id::cond fetch_cond_id(const arm_code_t&);
    [[nodiscard]] id::mode fetch_mode_id(const constants::mode);

    [[nodiscard]] u32 read(const id::reg);
    [[nodiscard]] u32 read(const arm_code_t&, const u8, const u8) noexcept;
    [[nodiscard]] u32 read(const thumb_code_t&, const u8, const u8) noexcept;
    [[nodiscard]] u32 read(const u8) noexcept;

    void write(const id::reg, const u32);

    [[nodiscard]] bool check_cond(const id::cond);


    void switch_mode(const id::mode mode) {
        switch (mode) {
            case id::mode::USER:          reg.write_cpsr(id::cpsr::M, constants::mode::USER); return;
            case id::mode::SUPERVISOR:    reg.write_cpsr(id::cpsr::M, constants::mode::SUPERVISOR); return;
            case id::mode::ABORT:         reg.write_cpsr(id::cpsr::M, constants::mode::ABORT); return;
            case id::mode::UNDEFINED:     reg.write_cpsr(id::cpsr::M, constants::mode::UNDEFINED); return;
            case id::mode::FIQ:           reg.write_cpsr(id::cpsr::M, constants::mode::FIQ); return;
            case id::mode::IRQ:           reg.write_cpsr(id::cpsr::M, constants::mode::IRQ); return;
            case id::mode::SYSTEM:        reg.write_cpsr(id::cpsr::M, constants::mode::SYSTEM); return;
            case id::mode::FIQ_26:        reg.write_cpsr(id::cpsr::M, constants::mode::FIQ_26); return;
            case id::mode::IRQ_26:        reg.write_cpsr(id::cpsr::M, constants::mode::IRQ_26); return;
            case id::mode::SUPERVISOR_26: reg.write_cpsr(id::cpsr::M, constants::mode::SUPERVISOR_26); return;
            case id::mode::USER_26:       reg.write_cpsr(id::cpsr::M, constants::mode::USER_26); return;
        }
    }

    id::mode read_mode() {
        switch (read_cpsr(id::cpsr::M)) {
            case constants::mode::USER: return id::mode::USER;
            case constants::mode::SUPERVISOR: return id::mode::SUPERVISOR;
            case constants::mode::ABORT: return id::mode::ABORT;
            case constants::mode::UNDEFINED: return id::mode::UNDEFINED;
            case constants::mode::FIQ: return id::mode::FIQ;
            case constants::mode::IRQ: return id::mode::IRQ;
            case constants::mode::SYSTEM: return id::mode::SYSTEM;
            case constants::mode::FIQ_26: return id::mode::FIQ_26;
            case constants::mode::IRQ_26: return id::mode::IRQ_26;
            case constants::mode::SUPERVISOR_26: return id::mode::SUPERVISOR_26;
            case constants::mode::USER_26: return id::mode::USER_26;
            default:
                out::error("No known enum value for read_mode()");
        }
    }


    u32 read_PC() {
        // [25:2]
        static constinit u32 pc_mask_26 = 0x3FFFFFC;

        // [31:2]
        static constinit u32 pc_mask_32 = 0xFFFFFFFC;

        if (coprocessor.is_26_bit_arch_address()) {
            return ((R15 & pc_mask_26) >> 2); 
        } else {
            return ((R15 & pc_mask_32) >> 2);
        }
    }


    void write_PC(const u32 address) {
        if (coprocessor.is_26_bit_arch_address()) {
            R15 = util::swap_bits(R15, 2, 26, (address & 0x03FFFFFF));
        } else {
            R15 = address;
        }
    }

    void thumb_increment_PC();

    void arm_increment_PC();

    REGISTERS(COPROCESSOR& coprocessor, GLOBALS& globals) : coprocessor(coprocessor), globals(globals) {

    }
};