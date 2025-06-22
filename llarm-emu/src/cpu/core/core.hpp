#pragma once

#include "../../types_extra.hpp"
#include "../../settings.hpp"
#include "../../id.hpp"
#include "../globals.hpp"
#include "../instruction_set.hpp"
#include "../exception.hpp"
#include "../core/core.hpp"
#include "../memory/memory.hpp"
#include "../memory/mmu.hpp"
#include "../memory/mpu.hpp"
#include "../memory/tlb.hpp"
#include "../memory/ram.hpp"
#include "../memory/fcse.hpp"
#include "../coprocessor/coprocessor.hpp"
#include "../instructions/instructions.hpp"
#include "../instructions/operation.hpp"
#include "cycle/fetch.hpp"
#include "cycle/decode.hpp"
#include "cycle/execute.hpp"
#include "registers.hpp"

#include <vector>

#include "shared/types.hpp"

struct core {
private:
    // essential settings
    SETTINGS settings;

    settings = settings.default_settings();

    GLOBALS globals;
    TLB tlb(settings);
    CP15 cp15(settings, globals, tlb);
    COPROCESSOR coprocessor(settings, globals, cp15);
    ARCH_26 arch_26(coprocessor, settings);
    REGISTERS reg(coprocessor, globals, arch_26, settings);
    EXCEPTION exception(reg, coprocessor);

    // memory
    ALIGNMENT alignment(coprocessor, settings);
    RAM ram(globals);
    MMU mmu(globals, ram, alignment, coprocessor, settings, tlb);
    MPU mpu(globals, coprocessor, settings, ram, fcse);
    FCSE fcse(coprocessor, settings);
    MEMORY memory(reg, ram, mmu, mpu, fcse, arch_26, exception);

    // instructions
    OPERATION operation;
    ADDRESSING_MODE address_mode(reg, operation);
    INSTRUCTIONS instructions(reg, address_mode, operation, coprocessor, settings, memory);
    INSTRUCTION_SET instruction_set(settings, instructions);

    // core cycle
    FETCH fetch(reg, memory, globals);
    DECODE decode(instruction_set, reg, settings);
    EXECUTE execute(instruction_set);

public:
    void initialise(const std::vector<u8> &binary);

    void arm_cycle();

public:
    core() {

    }
}