#pragma once

#include "id.hpp"
#include "types.hpp"
#include "constants.hpp"

struct REGISTERS {
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

    u32 PC = 0; // program counter (R15)

    u32 CPSR = 0; // current program status register

    // for all modes except user and system
    u32 SPSR_svc = 0; // saved program status registers
    u32 SPSR_abt = 0;
    u32 SPSR_und = 0;
    u32 SPSR_irq = 0;
    u32 SPSR_fiq = 0;

public:
    // sys.read_mode() already exists, but I can't use it within this class because of dependency hierarchies,
    // so I'm making an exact copy of the function here so that I don't break the structure in an inconvenient way
    [[nodiscard]] id::mode read_mode();
    [[nodiscard]] bool is_priviledged();

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

    void thumb_increment_PC();

    void increment_PC();
};