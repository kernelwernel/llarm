#pragma once

#include "../../settings.hpp"
#include "../globals.hpp"
#include "../exception.hpp"
#include "../memory/memory.hpp"
#include "../memory/mmu.hpp"
#include "../memory/mpu.hpp"
#include "../memory/tlb.hpp"
#include "../memory/ram.hpp"
#include "../memory/fcse.hpp"
#include "../coprocessor/coprocessor.hpp"
#include "../instructions/instructions.hpp"
#include "../instructions/operation.hpp"
#include "../vfp/registers.hpp"
#include "../vfp/addressing_modes.hpp"
#include "cycle/fetch.hpp"
#include "cycle/decode.hpp"
#include "cycle/execute.hpp"
#include "registers.hpp"

#include <llarm/llarm-asm.hpp>
#include <llarm/shared/types.hpp>

struct CORE {
public:
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

    // memory modules
    ALIGNMENT alignment;
    RAM ram;
    MMU mmu;
    MPU mpu;
    FCSE fcse;
    MEMORY memory;

    // instructions modules
    OPERATION operation;
    ADDRESSING_MODE address_mode;
    INSTRUCTIONS instructions;

    // core cycle modules
    FETCH fetch;
    DECODE decode;
    EXECUTE execute;

public:
    void initialise(const std::vector<u8> &binary);

    void arm_cycle_headless();
    void arm_cycle(const llarm::as::settings &settings);
    void thumb_cycle();

public:
    // for end-user library access purposes
    llarm::as::arm_id current_arm_id;
    u32 current_arm_code;
    bool continue_cycle;

public:
    CORE(const std::vector<u8> &binary) :
        settings(default_settings()), 
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
        alignment(coprocessor, settings),
        ram(globals),
        mmu(globals, ram, alignment, coprocessor, settings, tlb),
        mpu(globals, coprocessor, settings, ram, fcse),
        fcse(coprocessor, settings),
        memory(reg, ram, mmu, mpu, fcse, arch_26, exception),
        operation(),
        address_mode(reg, operation),
        instructions(reg, address_mode, operation, coprocessor, settings, memory, exception, vfp_reg, vfp_exception, vfp_addressing_mode),
        fetch(reg, memory, globals),
        decode(reg, settings),
        execute(instructions, exception)
    {
        initialise(binary);
    }
};