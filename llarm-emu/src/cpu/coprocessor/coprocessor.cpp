// TODO: THIS SHOULD BE DISABLED BEFORE V2, COPROCESSORS DIDN'T EXIST IN V1

// https://developer.arm.com/documentation/ddi0360/f/control-coprocessor-cp15/summary-of-control-coprocessor-cp15-registers-and-operations
// ^ super useful

// CPU ID codes:
// https://github.com/torvalds/linux/blob/619f0b6fad524f08d493a98d55bac9ab8895e3a6/arch/arm64/include/asm/cputype.h#L57 (ARM64)
// https://github.com/torvalds/linux/blob/619f0b6fad524f08d493a98d55bac9ab8895e3a6/arch/arm/include/asm/cputype.h#L66 (ARM32)

#include "../../id.hpp"
#include "cp15.hpp"

#include "coprocessor.hpp"

#include "shared/types.hpp"
#include "shared/out.hpp"


id::cp COPROCESSOR::fetch_cp_id(const u8 raw_cp_num) {
    switch (raw_cp_num) {
        case 0b0000: return id::cp::CP0;
        case 0b0001: return id::cp::CP1;
        case 0b0010: return id::cp::CP2;
        case 0b0011: return id::cp::CP3;
        case 0b0100: return id::cp::CP4;
        case 0b0101: return id::cp::CP5;
        case 0b0110: return id::cp::CP6;
        case 0b0111: return id::cp::CP7;
        case 0b1000: return id::cp::CP8;
        case 0b1001: return id::cp::CP9;
        case 0b1010: return id::cp::CP10;
        case 0b1011: return id::cp::CP11;
        case 0b1100: return id::cp::CP12;
        case 0b1101: return id::cp::CP13;
        case 0b1110: return id::cp::CP14;
        case 0b1111: return id::cp::CP15;
        default: shared::out::dev_error("Unknown coprocessor id argument for fetching_cp_id()");
    };
}


void COPROCESSOR::write(
    const u8 cp_id_bits, 
    const u8 CRn, 
    const u8 CRm,
    const u8 opcode_1, 
    const u8 opcode_2,
    const u64 value, 
    const bool is_forced
) {
    const id::cp cp_id = fetch_cp_id(cp_id_bits);

    switch (cp_id) {
        case id::cp::UNKNOWN: shared::out::dev_error("Unknown coprocessor id for write operation");
        case id::cp::CP0:
        case id::cp::CP1:
        case id::cp::CP2:
        case id::cp::CP3:
        case id::cp::CP4:
        case id::cp::CP5:
        case id::cp::CP6:
        case id::cp::CP7:
        case id::cp::CP8:
        case id::cp::CP9:
        case id::cp::CP10:
        case id::cp::CP11:
        case id::cp::CP12:
        case id::cp::CP13:
        case id::cp::CP14: shared::out::dev_error("Currently unsupported coprocessor in write operation");
        case id::cp::CP15:
            cp15.write(
                cp15.identify(CRn, CRm, opcode_2), 
                static_cast<u32>(value), 
                opcode_2,
                CRm,
                is_forced
            );
    }
}


u32 COPROCESSOR::read(
    const u8 cp_id_bits,
    const u8 CRn,
    const u8 CRm,
    const u8 opcode_1, 
    const u8 opcode_2
) {
    const id::cp cp_id = fetch_cp_id(cp_id_bits);

    switch (cp_id) {
        case id::cp::UNKNOWN: shared::out::error("Unknown coprocessor id for read operation"); // TODO dev error
        case id::cp::CP0:
        case id::cp::CP1:
        case id::cp::CP2:
        case id::cp::CP3:
        case id::cp::CP4:
        case id::cp::CP5:
        case id::cp::CP6:
        case id::cp::CP7:
        case id::cp::CP8:
        case id::cp::CP9:
        case id::cp::CP10:
        case id::cp::CP11:
        case id::cp::CP12:
        case id::cp::CP13:
        case id::cp::CP14:
        case id::cp::CP15: return cp15.read(cp15.identify(CRn, CRm, opcode_2));
    }
}


void COPROCESSOR::write(
    const id::cp15 cp15_id, 
    const u32 value,
    const bool is_forced
) {
    if (is_forced) {
        cp15.force_write(cp15_id, value);
    } else {
        cp15.write(cp15_id, value);
    }
}


void COPROCESSOR::force_write(
    const id::cp15 cp15_id, 
    const u32 value
) {
    write(cp15_id, value, true);
}


u32 COPROCESSOR::read(const id::cp15 cp15_id) {
    return cp15.read(cp15_id);
}


void COPROCESSOR::reset(const id::cp cp_id) {
    if (cp_id == id::cp::UNKNOWN) {
        // clear ALL coprocessors, add more of them here once i complete cp10, 11, and 14 TODO
        cp15.reset();
    }

    switch (cp_id) {
        case id::cp::UNKNOWN: shared::out::error("Unknown coprocessor id for read operation"); // TODO dev error
        case id::cp::CP0: return;
        case id::cp::CP1: return;
        case id::cp::CP2: return;
        case id::cp::CP3: return;
        case id::cp::CP4: return;
        case id::cp::CP5: return;
        case id::cp::CP6: return;
        case id::cp::CP7: return;
        case id::cp::CP8: return;
        case id::cp::CP9: return;
        case id::cp::CP10: return;
        case id::cp::CP11: return;
        case id::cp::CP12: return;
        case id::cp::CP13: return;
        case id::cp::CP14: return;
        case id::cp::CP15: cp15.reset(); return;
    }
}


COPROCESSOR::COPROCESSOR(
    SETTINGS& settings, 
    GLOBALS& globals, 
    CP15& cp15
) : settings(settings), 
    globals(globals), 
    cp15(cp15) 
{

}