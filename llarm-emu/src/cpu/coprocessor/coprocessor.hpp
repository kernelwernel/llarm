// TODO: THIS SHOULD BE DISABLED BEFORE V2, COPROCESSORS DIDN'T EXIST IN V1

// https://developer.arm.com/documentation/ddi0360/f/control-coprocessor-cp15/summary-of-control-coprocessor-cp15-registers-and-operations
// ^ super useful

// CPU ID codes:
// https://github.com/torvalds/linux/blob/619f0b6fad524f08d493a98d55bac9ab8895e3a6/arch/arm64/include/asm/cputype.h#L57 (ARM64)
// https://github.com/torvalds/linux/blob/619f0b6fad524f08d493a98d55bac9ab8895e3a6/arch/arm/include/asm/cputype.h#L66 (ARM32)

#pragma once

#include "../../id.hpp"

#include "cp15.hpp"
#include "../../settings.hpp"
#include "../core/globals.hpp"

#include <llarm/shared/types.hpp>


struct COPROCESSOR {
private:
    SETTINGS& settings;
    GLOBALS& globals;
    CP15& cp15;

public:
    id::cp fetch_cp_id(const u8 raw_cp_num);

    void write(
        const id::cp15 cp15_id, 
        const u32 value,
        const bool is_forced = false
    );

    void force_write(
        const id::cp15 cp15_id, 
        const u32 value
    );

    u32 read(const id::cp15 cp15_id);

    void write(
        const u8 cp_id_bits, 
        const u8 CRn,
        const u8 CRm,
        //const u8 opcode_1, 
        const u8 opcode_2,
        const u64 value, 
        const bool is_forced = false
    );

    u32 read(
        const u8 cp_id_bits, 
        const u8 CRn, 
        const u8 CRm,
        //const u8 opcode_1, 
        const u8 opcode_2
    );

    void reset(const id::cp cp = id::cp::UNKNOWN);

    COPROCESSOR(
        SETTINGS& settings, 
        GLOBALS& globals, 
        CP15& cp15
    );
};