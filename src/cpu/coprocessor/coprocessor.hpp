// TODO: THIS SHOULD BE DISABLED BEFORE V2, COPROCESSORS DIDN'T EXIST IN V1

// https://developer.arm.com/documentation/ddi0360/f/control-coprocessor-cp15/summary-of-control-coprocessor-cp15-registers-and-operations
// ^ super useful

// CPU ID codes:
// https://github.com/torvalds/linux/blob/619f0b6fad524f08d493a98d55bac9ab8895e3a6/arch/arm64/include/asm/cputype.h#L57 (ARM64)
// https://github.com/torvalds/linux/blob/619f0b6fad524f08d493a98d55bac9ab8895e3a6/arch/arm/include/asm/cputype.h#L66 (ARM32)

#pragma once

#include "../../types.hpp"
#include "../../settings.hpp"
#include "../../id.hpp"
#include "../../utility.hpp"
#include "../../out.hpp"

#include "cp15.hpp"

struct COPROCESSOR {
private:
    SETTINGS& settings;
    CP15& cp15;

public:
    id::coprocessor fetch_cp_id(const u8 raw_cp_num) {
        switch (raw_cp_num) {
            case 0b0000: return id::coprocessor::CP0;
            case 0b0001: return id::coprocessor::CP1;
            case 0b0010: return id::coprocessor::CP2;
            case 0b0011: return id::coprocessor::CP3;
            case 0b0100: return id::coprocessor::CP4;
            case 0b0101: return id::coprocessor::CP5;
            case 0b0110: return id::coprocessor::CP6;
            case 0b0111: return id::coprocessor::CP7;
            case 0b1000: return id::coprocessor::CP8;
            case 0b1001: return id::coprocessor::CP9;
            case 0b1010: return id::coprocessor::CP10;
            case 0b1011: return id::coprocessor::CP11;
            case 0b1100: return id::coprocessor::CP12;
            case 0b1101: return id::coprocessor::CP13;
            case 0b1110: return id::coprocessor::CP14;
            case 0b1111: return id::coprocessor::CP15;
            default: out::error("TODO");
        };
    }


    COPROCESSOR(SETTINGS& settings, GLOBALS& globals) : settings(settings) {
        // add more CP registers here
        CP15 cp15(settings, globals);
    }



public:
    id::cp cp_reg_identifier() {

    }


    void write(const id::cp cp_reg_id, const u64 value) {
        // check if the ID enum argument is in the CP15 range
        if (
            static_cast<u8>(cp_reg_id) > static_cast<u8>(id::cp::CP15_START) &&
            static_cast<u8>(cp_reg_id) < static_cast<u8>(id::cp::CP15_END)
        ) [[likely]] {
            cp15.write(cp_reg_id, util::bit_fetcher(value, 0, 31)); return;
        } 

        // TODO: ERROR (unknown CP reg id)
        return;
    }


    u32 read(const id::cp cp_reg_id) {
        // check if the ID enum argument is in the CP15 range
        if (
            static_cast<u8>(cp_reg_id) > static_cast<u8>(id::cp::CP15_START) &&
            static_cast<u8>(cp_reg_id) < static_cast<u8>(id::cp::CP15_END)
        ) {
            return cp15.read(cp_reg_id);
        }

        // TODO: ERROR (unknown CP reg id)
        return 0;
    }
};





// NOTES:
/*
MRC p15,0,<Rt>,c0,c0,0    ; Read CP15 Main ID Register
MRC p15,0,<Rt>,c0,c0,1    ; Read CP15 Cache Type Register
*/