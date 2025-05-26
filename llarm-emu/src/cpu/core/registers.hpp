#pragma once

#include "../../id.hpp"
#include "../../constants.hpp"
#include "../coprocessor/coprocessor.hpp"
#include "../memory/26_bit_arch.hpp"
#include "../globals.hpp"

#include "shared/types.hpp"

struct REGISTERS {
private:
    COPROCESSOR& coprocessor;
    GLOBALS& globals;
    ARCH_26& arch_26;
    SETTINGS& settings;

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
    bool is_privileged();
    bool is_exception();
    bool current_mode_has_SPSR();
    
    id::reg fetch_reg_id(const u8) noexcept;
    id::reg fetch_reg_id(const arm_code_t&, const u8, const u8) noexcept;
    id::reg fetch_reg_id(const thumb_code_t&, const u8, const u8) noexcept;
    
    id::cond fetch_cond_id(const u8);
    id::cond fetch_cond_id(const arm_code_t&);

    bool check_cond(const id::cond);
    bool check_cond(const arm_code_t&);

    void write(const id::cpsr, const u8);
    void write(const id::reg reg_id);
    void write(const id::reg, const id::reg);
    void write(const id::reg, const u32);
    void write(const arm_code_t& code, const u8 start, const u8 end, const u32 value);

    u8 read(const id::cpsr);
    u32 read(const id::reg);
    u32 read(const arm_code_t&, const u8, const u8) noexcept;
    u32 read(const thumb_code_t&, const u8, const u8) noexcept;
    u32 read(const u8) noexcept;

    void access_check(const id::reg);

    id::mode fetch_mode_id(const u8);

    void switch_mode(const id::mode mode);

    id::mode read_mode();

    u32 read_PC();

    void write_PC(const u32 address);

    void thumb_increment_PC();

    void arm_increment_PC();

    void reset();

    REGISTERS(
        COPROCESSOR& coprocessor, 
        GLOBALS& globals,
        ARCH_26& arch_26,
        SETTINGS& settings
    ) : coprocessor(coprocessor), 
        globals(globals),
        arch_26(arch_26),
        settings(settings)
    {

    }
};