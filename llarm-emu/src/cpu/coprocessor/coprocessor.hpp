// TODO: THIS SHOULD BE DISABLED BEFORE V2, COPROCESSORS DIDN'T EXIST IN V1

// https://developer.arm.com/documentation/ddi0360/f/control-coprocessor-cp15/summary-of-control-coprocessor-cp15-registers-and-operations
// ^ super useful

// CPU ID codes:
// https://github.com/torvalds/linux/blob/619f0b6fad524f08d493a98d55bac9ab8895e3a6/arch/arm64/include/asm/cputype.h#L57 (ARM64)
// https://github.com/torvalds/linux/blob/619f0b6fad524f08d493a98d55bac9ab8895e3a6/arch/arm/include/asm/cputype.h#L66 (ARM32)

#pragma once

#include "../../settings.hpp"
#include "../../id.hpp"
#include "../../utility.hpp"

#include "shared/types.hpp"
#include "shared/out.hpp"

#include "cp15.hpp"

struct COPROCESSOR {
private:
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
            default: shared::out::error("TODO");
        };
    }


    COPROCESSOR(CP15& cp15) : cp15(cp15) {

    }



public:
    //id::cp cp_reg_identifier() {
//
    //}


    void write(const id::cp cp_reg_id, const u64 value, const bool is_forced = false) {
        // check if the ID enum argument is in the CP15 range
        if (
            static_cast<u8>(cp_reg_id) > static_cast<u8>(id::cp::CP15_START) &&
            static_cast<u8>(cp_reg_id) < static_cast<u8>(id::cp::CP15_END)
        ) [[likely]] {
            cp15.write(cp_reg_id, shared::util::bit_range(value, 0, 31), is_forced); return;
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


    u32 read(
        const u8 CRn, 
        const u8 opcode_1, 
        const u8 CRm, 
        const u8 opcode_2
    ) {
        if ((opcode_1 != 0) && (CRn != 15)) {
            return 0; // TODO: add warning or error idk, this doesn't exist
        }

        // coprocessor number
        switch (CRn) {
            case 0:
                if (CRm == 0) {
                    if (opcode_2 == 0) { 
                        return read(id::cp::CP15_R0_ID); 
                    } else if (opcode_2 == 1) { 
                        return read(id::cp::CP15_R0_CACHE);
                    }
                }

                break;

            case 1:
                if (CRm == 0) {
                    if (opcode_2 == 0) { 
                        return read(id::cp::CP15_R1); 
                    }
                }

                break;

            case 2:
                if (CRm == 0) {
                    // ?????? TODO
                }

                break;

            case 3:
            // TODO rewrite thi, because MMU and PU merge together as registers cuz they're non-mutually exclusive
                if ((CRm == 0) && (opcode_2 == 0)) {
                    return read(id::cp::CP15_R3_MMU);
                }

                break;

            case 4:
                return read(id::cp::CP15_R4);

            case 5:
                if (CRm == 0) {

                }

            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            default: break;
        }

        return 0; // error or warning
    }
};





// NOTES:
/*
MRC p15,0,<Rt>,c0,c0,0    ; Read CP15 Main ID Register
MRC p15,0,<Rt>,c0,c0,1    ; Read CP15 Cache Type Register
*/