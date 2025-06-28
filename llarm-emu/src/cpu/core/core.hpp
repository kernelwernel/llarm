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
#include "../vfp/vfp.hpp"
#include "../vfp/registers.hpp"
#include "cycle/fetch.hpp"
#include "cycle/decode.hpp"
#include "cycle/execute.hpp"
#include "registers.hpp"


#include "shared/types.hpp"

struct CORE {
private:
    // essential settings
    SETTINGS settings;
    GLOBALS globals;
    TLB tlb;
    CP15 cp15;
    VFP_REG vfp_reg;
    VFP_EXCEPTION vfp_exception;
    VFP vfp;
    COPROCESSOR coprocessor;
    ARCH_26 arch_26;
    REGISTERS reg;
    EXCEPTION exception;

    // memory
    ALIGNMENT alignment;
    RAM ram;
    MMU mmu;
    MPU mpu;
    FCSE fcse;
    MEMORY memory;

    // instructions
    OPERATION operation;
    ADDRESSING_MODE address_mode;
    INSTRUCTIONS instructions;

    // core cycle
    FETCH fetch;
    DECODE decode;
    EXECUTE execute;

public:
    void initialise(const std::vector<u8> &binary);

    void arm_cycle(const llarm::as::settings &settings);
    void thumb_cycle();

public:
    CORE(const std::vector<u8> &binary) :
        settings(default_settings()), 
        globals(),
        tlb(settings),
        cp15(settings, globals, tlb),
        vfp_reg(settings),
        vfp_exception(vfp_reg),
        vfp(vfp_reg, vfp_exception),
        coprocessor(settings, globals, cp15),
        arch_26(coprocessor, settings),
        reg(coprocessor, globals, arch_26, settings),
        exception(reg, coprocessor),
        alignment(coprocessor, settings),
        ram(globals),
        mmu(globals, ram, alignment, coprocessor, settings, tlb),
        mpu(globals, coprocessor, settings, ram, fcse),
        fcse(coprocessor, settings),
        memory(reg, ram, mmu, mpu, fcse, arch_26, exception),
        operation(),
        address_mode(reg, operation),
        instructions(reg, address_mode, operation, coprocessor, settings, memory, exception),
        fetch(reg, memory, globals),
        decode(reg, settings),
        execute(instructions, exception)
    {
        initialise(binary);
    }
};