#pragma once

#include "../../settings.hpp"
#include "globals.hpp"
#include "exception.hpp"
#include "../../vic/vic.hpp"
#include "../memory/memory.hpp"
#include "../memory/cache.hpp"
#include "../memory/mmu.hpp"
#include "../memory/mpu.hpp"
#include "../memory/tlb.hpp"
#include "../../ram/ram.hpp"
#include "../memory/fcse.hpp"
#include "../coprocessor/coprocessor.hpp"
#include "../instructions/instructions.hpp"
#include "../vfp/registers.hpp"
#include "../vfp/addressing_modes.hpp"
#include "cycle/fetch.hpp"
#include "cycle/decode.hpp"
#include "cycle/execute.hpp"
#include "registers.hpp"

#include <llarm/llarm-asm.hpp>
#include <llarm/shared/types.hpp>

struct CORE {
    // essential modules
    SETTINGS settings;
    GLOBALS globals;
    TLB tlb;
    CP15 cp15;
    VFP_REG vfp_reg;
    VFP_EXCEPTION vfp_exception;
    COPROCESSOR coprocessor;
    ARCH_26 arch_26;
    REGISTERS reg;
    VFP_ADDRESS_MODE vfp_addressing_mode;
    EXCEPTION exception;
    VIC vic;

    // memory modules
    ALIGNMENT alignment;
    RAM ram;
    CACHE cache;
    MMU mmu;
    MPU mpu;
    FCSE fcse;
    MEMORY memory;

    // instructions modules
    ADDRESSING_MODE address_mode;
    INSTRUCTIONS instructions;

    // core cycle modules
    FETCH fetch;
    DECODE decode;
    EXECUTE execute;

    // internal core state variables
    bool is_halted = false;

    void initialise(const bool is_headless = false);

    void arm_cycle_headless();
    void arm_cycle();
    void thumb_cycle_headless();
    void thumb_cycle();

    // for end-user library access purposes
    llarm::as::arm_id current_arm_id = arm_id::UNKNOWN;
    llarm::as::thumb_id current_thumb_id = thumb_id::UNKNOWN;
    u32 current_arm_code = 0;
    u16 current_thumb_code = 0;
    bool continue_cycle = false;

    CORE(const SETTINGS& init_settings, RAM &ram, VIC& vic) :
        settings(init_settings),
        globals(),
        tlb(settings),
        cp15(settings, globals, tlb),
        vfp_reg(settings),
        vfp_exception(vfp_reg),
        coprocessor(settings, globals, cp15),
        arch_26(coprocessor, settings),
        reg(coprocessor, globals, arch_26, settings),
        vfp_addressing_mode(settings, reg, vfp_reg),
        exception(reg, coprocessor),
        vic(vic),
        alignment(coprocessor, settings),
        ram(ram),
        cache(settings, coprocessor, ram, is_halted),
        mmu(globals, ram, alignment, coprocessor, settings, tlb, cache),
        mpu(globals, coprocessor, settings, ram, fcse),
        fcse(coprocessor, settings),
        memory(reg, ram, mmu, mpu, fcse, arch_26, exception),
        address_mode(reg),
        instructions(reg, address_mode, coprocessor, settings, memory, exception, vfp_reg, vfp_exception, vfp_addressing_mode),
        fetch(reg, memory, globals),
        decode(reg, settings),
        execute(instructions, exception)
    {

    }
};