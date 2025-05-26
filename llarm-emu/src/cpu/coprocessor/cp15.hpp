// TODO: THIS SHOULD BE DISABLED BEFORE V2, COPROCESSORS DIDN'T EXIST IN V1

// https://developer.arm.com/documentation/ddi0360/f/control-coprocessor-cp15/summary-of-control-coprocessor-cp15-registers-and-operations
// ^ super useful

// CPU ID codes:
// https://github.com/torvalds/linux/blob/619f0b6fad524f08d493a98d55bac9ab8895e3a6/arch/arm64/include/asm/cputype.h#L57 (ARM64)
// https://github.com/torvalds/linux/blob/619f0b6fad524f08d493a98d55bac9ab8895e3a6/arch/arm/include/asm/cputype.h#L66 (ARM32)

#pragma once

#include "../../settings.hpp"
#include "../../id.hpp"
#include "../globals.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"

/**
 * NOTE: 
 * MMU = memory management unit
 * MPU = memory protection unit
 * 
 * The registers in CP15 are very wonky and confusing to conceptually understand.
 * A lot of them have shared functionalities where their usage depends on whether
 * the memory system is an MMU or an MPU, which both are non-homogenous and can't 
 * work together at the same time. For example, the R2 register has different 
 * interpretations: the MMU sees it as a translation table address, while the MPU 
 * sees it as a storage for cachability bits. 
 * 
 * But the wonkiness doesn't end there. R0 has different use cases depending on
 * the MCR/MRC instruction's operands. It can both be used to store the processor's
 * information and ID, while on the other hand it can be used to store information
 * about the cache. 
 * 
 * Just thought I should clarify this. It took me a while to figure this out, so I
 * hope this will clear any misunderstandings as to why the registers and the file
 * itself is structured in this unintuitive way. Also, hope you have a great day :)
 */
struct CP15 {
private:
    SETTINGS& settings;
    GLOBALS& globals;

public:

    // ID codes
    u32 R0_ID = 0;    // processor ID 
    u32 R0_CACHE = 0; // Cache 

    // control bits 
    u32 R1 = 0;
    
    // MMU: translation table
    // MPU: cachability bits
    u32 R2 = 0;
    
    // MMU: domain access control
    // MPU: bufferability bits
    u32 R3 = 0;

    // MMU: reserved
    // MPU: reserved
    u32 R4 = 0;

    // MMU: fault status
    // MPU: access permission bits
    u32 R5 = 0;

    // MMU: fault address
    u32 R6 = 0;

    // protection area control
    u32 R6_PU_0 = 0;
    u32 R6_PU_1 = 0;
    u32 R6_PU_2 = 0;
    u32 R6_PU_3 = 0;
    u32 R6_PU_4 = 0;
    u32 R6_PU_5 = 0;
    u32 R6_PU_6 = 0;
    u32 R6_PU_7 = 0;

    // cache/write buffer control
    u32 R7 = 0;

    // MMU: TLB control, this register doesn't really exist (B3-26
    // MPU: reserved
    u32 R8 = 0; // reserved

    // cache lockdown
    u32 R9 = 0;

    // MMU: TLB lockdown
    // MPU: reserved
    u32 R10;

    // reserved
    u32 R11 = 0;

    // reserved
    u32 R12 = 0;

    // FCSE: process ID
    u32 R13 = 0;

    // reserved
    u32 R14 = 0;

     // implementation defined, not important
    u32 R15 = 0;

private:
    static constexpr bool FORCED = true;

public:
    u32 read(const id::cp reg) {
        switch (reg) {
            case id::cp::CP15_START: return 0; // TODO WARNING
            case id::cp::CP15_END: return 0; // TODO WARNING
            case id::cp::CP15_R0_ID: return R0_ID;
            case id::cp::CP15_R0_ID_REVISION: return shared::util::bit_range(R0_ID, 0, 3);
            case id::cp::CP15_R0_ID_IMPLEMENTOR: return shared::util::bit_range(R0_ID, 24, 31);
            case id::cp::CP15_R0_ID_PPN: return shared::util::bit_range(R0_ID, 4, 15);
            case id::cp::CP15_R0_ID_PRE7_ID: return shared::util::bit_range(R0_ID, 4, 31);
            case id::cp::CP15_R0_ID_PRE7_REVISION: return shared::util::bit_range(R0_ID, 0, 3);
            case id::cp::CP15_R0_ID_7_REVISION: return shared::util::bit_range(R0_ID, 0, 3);
            case id::cp::CP15_R0_ID_7_PPN: return shared::util::bit_range(R0_ID, 4, 15);
            case id::cp::CP15_R0_ID_7_PPN_TOP: return shared::util::bit_range(R0_ID, 12, 15);
            case id::cp::CP15_R0_ID_7_VARIANT: return shared::util::bit_range(R0_ID, 16, 22);
            case id::cp::CP15_R0_ID_7_A: return shared::util::bit_fetch(R0_ID, 23);
            case id::cp::CP15_R0_ID_7_IMPLEMENTOR: return shared::util::bit_range(R0_ID, 24, 31);
            case id::cp::CP15_R0_ID_POST7_IMPLEMENTOR: return shared::util::bit_range(R0_ID, 24, 31);
            case id::cp::CP15_R0_ID_POST7_VARIANT: return shared::util::bit_range(R0_ID, 20, 23);
            case id::cp::CP15_R0_ID_POST7_ARCHITECTURE: return shared::util::bit_range(R0_ID, 16, 19);
            case id::cp::CP15_R0_ID_POST7_PPN: return shared::util::bit_range(R0_ID, 4, 15);
            case id::cp::CP15_R0_ID_POST7_PPN_TOP: return shared::util::bit_range(R0_ID, 12, 15);
            case id::cp::CP15_R0_ID_POST7_REVISION: return shared::util::bit_range(R0_ID, 0, 3);
            case id::cp::CP15_R0_CACHE: return R0_CACHE;
            case id::cp::CP15_R0_CACHE_CTYPE: return shared::util::bit_range(R0_CACHE, 25, 28);
            case id::cp::CP15_R0_CACHE_S: return shared::util::bit_fetch(R0_CACHE, 24);
            case id::cp::CP15_R0_CACHE_DSIZE: return shared::util::bit_range(R0_CACHE, 12, 23);
            case id::cp::CP15_R0_CACHE_DSIZE_LEN: return shared::util::bit_range(R0_CACHE, 12, 13);
            case id::cp::CP15_R0_CACHE_DSIZE_M: return shared::util::bit_fetch(R0_CACHE, 14);
            case id::cp::CP15_R0_CACHE_DSIZE_ASSOC: return shared::util::bit_range(R0_CACHE, 15, 17);
            case id::cp::CP15_R0_CACHE_DSIZE_SIZE: return shared::util::bit_range(R0_CACHE, 18, 20);
            case id::cp::CP15_R0_CACHE_ISIZE: return shared::util::bit_range(R0_CACHE, 0, 11);
            case id::cp::CP15_R0_CACHE_ISIZE_LEN: return shared::util::bit_range(R0_CACHE, 0, 1);
            case id::cp::CP15_R0_CACHE_ISIZE_M: return shared::util::bit_fetch(R0_CACHE, 2);
            case id::cp::CP15_R0_CACHE_ISIZE_ASSOC: return shared::util::bit_range(R0_CACHE, 3, 5);
            case id::cp::CP15_R0_CACHE_ISIZE_SIZE: return shared::util::bit_range(R0_CACHE, 6, 8);
            case id::cp::CP15_R1: return R1;
            case id::cp::CP15_R1_M: return (R1 & 1);
            case id::cp::CP15_R1_A: return shared::util::bit_fetch(R1, 1);
            case id::cp::CP15_R1_C: return shared::util::bit_fetch(R1, 2);
            case id::cp::CP15_R1_W: return shared::util::bit_fetch(R1, 3);
            case id::cp::CP15_R1_P: return shared::util::bit_fetch(R1, 4);
            case id::cp::CP15_R1_D: return shared::util::bit_fetch(R1, 5);
            case id::cp::CP15_R1_L: return shared::util::bit_fetch(R1, 6);
            case id::cp::CP15_R1_B: return shared::util::bit_fetch(R1, 7);
            case id::cp::CP15_R1_S: return shared::util::bit_fetch(R1, 8);
            case id::cp::CP15_R1_R: return shared::util::bit_fetch(R1, 9);
            case id::cp::CP15_R1_F: return shared::util::bit_fetch(R1, 10);
            case id::cp::CP15_R1_Z: return shared::util::bit_fetch(R1, 11);
            case id::cp::CP15_R1_I: return shared::util::bit_fetch(R1, 12);
            case id::cp::CP15_R1_V: return shared::util::bit_fetch(R1, 13);
            case id::cp::CP15_R1_RR: return shared::util::bit_fetch(R1, 14);
            case id::cp::CP15_R1_L4: return shared::util::bit_fetch(R1, 15);
            case id::cp::CP15_R2: return R2;
            case id::cp::CP15_R2_MMU: return R2;
            case id::cp::CP15_R2_MMU_TRANSLATION_BASE: return shared::util::bit_range(R2, 14, 31);
            case id::cp::CP15_R2_PU: return R2;
            case id::cp::CP15_R2_PU_C0: return (R2 & 1);
            case id::cp::CP15_R2_PU_C1: return shared::util::bit_fetch(R2, 1);
            case id::cp::CP15_R2_PU_C2: return shared::util::bit_fetch(R2, 2);
            case id::cp::CP15_R2_PU_C3: return shared::util::bit_fetch(R2, 3);
            case id::cp::CP15_R2_PU_C4: return shared::util::bit_fetch(R2, 4);
            case id::cp::CP15_R2_PU_C5: return shared::util::bit_fetch(R2, 5);
            case id::cp::CP15_R2_PU_C6: return shared::util::bit_fetch(R2, 6);
            case id::cp::CP15_R2_PU_C7: return shared::util::bit_fetch(R2, 7);
            case id::cp::CP15_R3: return R3;
            case id::cp::CP15_R3_MMU: return R3;
            case id::cp::CP15_R3_MMU_D0: return shared::util::bit_range(R3, 0, 1);
            case id::cp::CP15_R3_MMU_D1: return shared::util::bit_range(R3, 2, 3);
            case id::cp::CP15_R3_MMU_D2: return shared::util::bit_range(R3, 4, 5);
            case id::cp::CP15_R3_MMU_D3: return shared::util::bit_range(R3, 6, 7);
            case id::cp::CP15_R3_MMU_D4: return shared::util::bit_range(R3, 8, 9);
            case id::cp::CP15_R3_MMU_D5: return shared::util::bit_range(R3, 10, 11);
            case id::cp::CP15_R3_MMU_D6: return shared::util::bit_range(R3, 12, 13);
            case id::cp::CP15_R3_MMU_D7: return shared::util::bit_range(R3, 14, 15);
            case id::cp::CP15_R3_MMU_D8: return shared::util::bit_range(R3, 16, 17);
            case id::cp::CP15_R3_MMU_D9: return shared::util::bit_range(R3, 18, 19);
            case id::cp::CP15_R3_MMU_D10: return shared::util::bit_range(R3, 20, 21);
            case id::cp::CP15_R3_MMU_D11: return shared::util::bit_range(R3, 22, 23);
            case id::cp::CP15_R3_MMU_D12: return shared::util::bit_range(R3, 24, 25);
            case id::cp::CP15_R3_MMU_D13: return shared::util::bit_range(R3, 26, 27);
            case id::cp::CP15_R3_MMU_D14: return shared::util::bit_range(R3, 28, 29);
            case id::cp::CP15_R3_MMU_D15: return shared::util::bit_range(R3, 30, 31);
            case id::cp::CP15_R3_PU: return R3;
            case id::cp::CP15_R3_PU_B0: return (R3 & 1);
            case id::cp::CP15_R3_PU_B1: return shared::util::bit_fetch(R3, 1);
            case id::cp::CP15_R3_PU_B2: return shared::util::bit_fetch(R3, 2);
            case id::cp::CP15_R3_PU_B3: return shared::util::bit_fetch(R3, 3);
            case id::cp::CP15_R3_PU_B4: return shared::util::bit_fetch(R3, 4);
            case id::cp::CP15_R3_PU_B5: return shared::util::bit_fetch(R3, 5);
            case id::cp::CP15_R3_PU_B6: return shared::util::bit_fetch(R3, 6);
            case id::cp::CP15_R3_PU_B7: return shared::util::bit_fetch(R3, 7);
            case id::cp::CP15_R4: return R4;
            case id::cp::CP15_R4_MMU: return R4;
            case id::cp::CP15_R4_PU: return R4;
            case id::cp::CP15_R5: return R5;
            case id::cp::CP15_R5_MMU: return R5;
            case id::cp::CP15_R5_MMU_DOMAIN: return shared::util::bit_range(R5, 4, 7);
            case id::cp::CP15_R5_MMU_STATUS: return shared::util::bit_range(R5, 0, 3);
            case id::cp::CP15_R5_PU: return R5;
            case id::cp::CP15_R5_PU_AP0: return shared::util::bit_range(R5, 0, 1);
            case id::cp::CP15_R5_PU_AP1: return shared::util::bit_range(R5, 2, 3);
            case id::cp::CP15_R5_PU_AP2: return shared::util::bit_range(R5, 4, 5);
            case id::cp::CP15_R5_PU_AP3: return shared::util::bit_range(R5, 6, 7);
            case id::cp::CP15_R5_PU_AP4: return shared::util::bit_range(R5, 8, 9);
            case id::cp::CP15_R5_PU_AP5: return shared::util::bit_range(R5, 10, 11);
            case id::cp::CP15_R5_PU_AP6: return shared::util::bit_range(R5, 12, 13);
            case id::cp::CP15_R5_PU_AP7: return shared::util::bit_range(R5, 14, 15);
            case id::cp::CP15_R6_MMU: return R6;
            case id::cp::CP15_R6_MMU_FAR: return R6; // same as above, this is added for the sake of completeness 
            case id::cp::CP15_R6_PU_0: return R6_PU_0;
            case id::cp::CP15_R6_PU_0_BASE_ADDRESS: return shared::util::bit_range(R6_PU_0, 12, 31);
            case id::cp::CP15_R6_PU_0_SIZE: return shared::util::bit_range(R6_PU_0, 1, 5);
            case id::cp::CP15_R6_PU_0_E: return (R6_PU_0 & 1);
            case id::cp::CP15_R6_PU_1: return R6_PU_1;
            case id::cp::CP15_R6_PU_1_BASE_ADDRESS: return shared::util::bit_range(R6_PU_1, 12, 31);
            case id::cp::CP15_R6_PU_1_SIZE: return shared::util::bit_range(R6_PU_1, 1, 5);
            case id::cp::CP15_R6_PU_1_E: return (R6_PU_1 & 1);
            case id::cp::CP15_R6_PU_2: return R6_PU_2;
            case id::cp::CP15_R6_PU_2_BASE_ADDRESS: return shared::util::bit_range(R6_PU_2, 12, 31);
            case id::cp::CP15_R6_PU_2_SIZE: return shared::util::bit_range(R6_PU_2, 1, 5);
            case id::cp::CP15_R6_PU_2_E: return (R6_PU_2 & 1);
            case id::cp::CP15_R6_PU_3: return R6_PU_3;
            case id::cp::CP15_R6_PU_3_BASE_ADDRESS: return shared::util::bit_range(R6_PU_3, 12, 31);
            case id::cp::CP15_R6_PU_3_SIZE: return shared::util::bit_range(R6_PU_3, 1, 5);
            case id::cp::CP15_R6_PU_3_E: return (R6_PU_3 & 1);
            case id::cp::CP15_R6_PU_4: return R6_PU_4;
            case id::cp::CP15_R6_PU_4_BASE_ADDRESS: return shared::util::bit_range(R6_PU_4, 12, 31);
            case id::cp::CP15_R6_PU_4_SIZE: return shared::util::bit_range(R6_PU_4, 1, 5);
            case id::cp::CP15_R6_PU_4_E: return (R6_PU_4 & 1);
            case id::cp::CP15_R6_PU_5: return R6_PU_5;
            case id::cp::CP15_R6_PU_5_BASE_ADDRESS: return shared::util::bit_range(R6_PU_5, 12, 31);
            case id::cp::CP15_R6_PU_5_SIZE: return shared::util::bit_range(R6_PU_5, 1, 5);
            case id::cp::CP15_R6_PU_5_E: return (R6_PU_5 & 1);
            case id::cp::CP15_R6_PU_6: return R6_PU_6;
            case id::cp::CP15_R6_PU_6_BASE_ADDRESS: return shared::util::bit_range(R6_PU_6, 12, 31);
            case id::cp::CP15_R6_PU_6_SIZE: return shared::util::bit_range(R6_PU_6, 1, 5);
            case id::cp::CP15_R6_PU_6_E: return (R6_PU_6 & 1);
            case id::cp::CP15_R6_PU_7: return R6_PU_7;
            case id::cp::CP15_R6_PU_7_BASE_ADDRESS: return shared::util::bit_range(R6_PU_7, 12, 31);
            case id::cp::CP15_R6_PU_7_SIZE: return shared::util::bit_range(R6_PU_7, 1, 5);
            case id::cp::CP15_R6_PU_7_E: return (R6_PU_7 & 1);
            case id::cp::CP15_R7: return R7;
            case id::cp::CP15_R7_CACHE_INDEX: // TODO
            case id::cp::CP15_R7_CACHE_SET: // TODO
            case id::cp::CP15_R8_MMU: return 0; // UNPREDICTABLE
            case id::cp::CP15_R8_PU: return R8;
            case id::cp::CP15_R9: return R9;
            case id::cp::CP15_R9_CACHE_INDEX: // TODO
            case id::cp::CP15_R9_CACHE_L: // TODO
            case id::cp::CP15_R10: return R10;
            case id::cp::CP15_R10_MMU: return R10;
            case id::cp::CP15_R10_MMU_BASE: // TODO: SEE PAGE B3-27
            case id::cp::CP15_R10_MMU_VICTIM: // TODO: SEE PAGE B3-27
            case id::cp::CP15_R10_MMU_P: return (R10 & 1);
            case id::cp::CP15_R10_PU: return R10;
            case id::cp::CP15_R11: return R11;
            case id::cp::CP15_R12: return R12;
            case id::cp::CP15_R13: return R13;
            case id::cp::CP15_R13_PID: return shared::util::bit_range(R13, 25, 31);
            case id::cp::CP15_R14: return R14;
            case id::cp::CP15_R15: return R15;
            default: shared::out::error("TODO");
        }
    }































    void write(const id::cp reg, const u32 value, const bool forced = false) {
        switch (reg) {
            case id::cp::CP15_END: return; // TODO: WARNING
            case id::cp::CP15_START: return; // TODO: WARNING
            case id::cp::CP15_R0_ID: R0_ID = value; return;
            case id::cp::CP15_R0_ID_REVISION: util::swap_bits(R0_ID, 0, 3, value); return;
            case id::cp::CP15_R0_ID_IMPLEMENTOR: util::swap_bits(R0_ID, 24, 31, value); return;
            case id::cp::CP15_R0_ID_PPN: util::swap_bits(R0_ID, 4, 15, value); return;
            case id::cp::CP15_R0_ID_PRE7_ID: util::swap_bits(R0_ID, 0, 3, value); return;
            case id::cp::CP15_R0_ID_PRE7_REVISION: util::swap_bits(R0_ID, 4, 31, value); return;
            case id::cp::CP15_R0_ID_7_REVISION: util::swap_bits(R0_ID, 0, 3, value); return;
            case id::cp::CP15_R0_ID_7_PPN: util::swap_bits(R0_ID, 4, 15, value); return;
            case id::cp::CP15_R0_ID_7_PPN_TOP: util::swap_bits(R0_ID, 12, 15, value); return;
            case id::cp::CP15_R0_ID_7_VARIANT: util::swap_bits(R0_ID, 16, 22, value); return;
            case id::cp::CP15_R0_ID_7_A: util::modify_bit(R0_ID, 23, value); return;
            case id::cp::CP15_R0_ID_7_IMPLEMENTOR: util::swap_bits(R0_ID, 24, 31, value); return;
            case id::cp::CP15_R0_ID_POST7_REVISION: util::swap_bits(R0_ID, 0, 3, value); return;
            case id::cp::CP15_R0_ID_POST7_PPN: util::swap_bits(R0_ID, 4, 15, value); return;
            case id::cp::CP15_R0_ID_POST7_PPN_TOP: util::swap_bits(R0_ID, 12, 15, value); return;
            case id::cp::CP15_R0_ID_POST7_ARCHITECTURE: util::swap_bits(R0_ID, 16, 19, value); return;
            case id::cp::CP15_R0_ID_POST7_VARIANT: util::swap_bits(R0_ID, 20, 23, value); return;
            case id::cp::CP15_R0_ID_POST7_IMPLEMENTOR: util::swap_bits(R0_ID, 24, 31, value); return;
            case id::cp::CP15_R0_CACHE: R0_CACHE = value; return;
            case id::cp::CP15_R0_CACHE_CTYPE: util::swap_bits(R0_CACHE, 25, 28, value); return;
            case id::cp::CP15_R0_CACHE_S: util::modify_bit(R0_CACHE, 24, value); return;

            case id::cp::CP15_R0_CACHE_DSIZE: util::swap_bits(R0_CACHE, 12, 23, value); return;
            case id::cp::CP15_R0_CACHE_DSIZE_LEN: util::swap_bits(R0_CACHE, 12, 13, value); return;
            case id::cp::CP15_R0_CACHE_DSIZE_M: util::modify_bit(R0_CACHE, 14, value); return;
            case id::cp::CP15_R0_CACHE_DSIZE_ASSOC: util::swap_bits(R0_CACHE, 15, 17, value); return;
            case id::cp::CP15_R0_CACHE_DSIZE_SIZE: util::swap_bits(R0_CACHE, 18, 20, value); return;
            case id::cp::CP15_R0_CACHE_ISIZE: util::swap_bits(R0_CACHE, 0, 11, value); return;
            case id::cp::CP15_R0_CACHE_ISIZE_LEN: util::swap_bits(R0_CACHE, 0, 1, value); return;
            case id::cp::CP15_R0_CACHE_ISIZE_M: util::modify_bit(R0_CACHE, 2, value); return;
            case id::cp::CP15_R0_CACHE_ISIZE_ASSOC: util::swap_bits(R0_CACHE, 3, 5, value); return;
            case id::cp::CP15_R0_CACHE_ISIZE_SIZE: util::swap_bits(R0_CACHE, 6, 8, value); return;

            case id::cp::CP15_R1: R1 = value; return;
            case id::cp::CP15_R1_M: 
                // On systems without an MMU or Protection Unit, 
                // this bit reads as 0 and ignores writes. (B2-13)
                if (settings.is_mpu_enabled) {
                    if ((R6_PU_0 + R6_PU_1 + R6_PU_2 + R6_PU_3 + R6_PU_4 + R6_PU_5 + R6_PU_6 + R6_PU_7) == 0) {
                        // TODO warning: PU must have at least a single protection region setup
                    }

                    util::modify_bit(R1, 0, value); 
                } else if (settings.is_mmu_enabled) {
                    util::modify_bit(R1, 0, value); 
                } else if (forced) {
                    util::modify_bit(R1, 0, value); 
                }
                return;

            case id::cp::CP15_R1_A: 
                // For other memory systems, this bit ignores writes, and 
                // reads as 1 or 0 according to whether the memory system 
                // does or does not check the alignment of data memory accesses.
                if (settings.has_alignment_fault_checking || forced) {
                    util::modify_bit(R1, 1, value);
                }
                return;

            case id::cp::CP15_R1_C:
                // If a unified cache is used, this is the enable/disable 
                // bit for the unified cache. If separate caches are used, 
                // this is the enable/disable bit for the data cache

                // If the cache is not implemented, this bit reads as 0 
                // and ignores writes. If the cache cannot be disabled, 
                // this bit reads as 1 and ignores writes.
                if ((settings.cache_cannot_disable || !settings.has_cache) && !forced) {
                    return;
                }

                if (settings.has_cache || forced) {
                    util::modify_bit(R1, 2, value); 
                }

                return;

            case id::cp::CP15_R1_W:
                // If the write buffer is not implemented, this bit reads 
                // as 0 and ignores writes. If the write buffer cannot be 
                // disabled, this bit reads as 1 and ignores writes.
                if ((settings.write_buffer_cannot_disable || settings.has_write_buffer) && !forced) {
                    return;
                }

                if (settings.has_write_buffer || forced) {
                    util::modify_bit(R1, 3, value);
                }

                return;

            case id::cp::CP15_R1_P:
                // On ARM processors which do not support 26-bit backwards-
                // compatibility configurations, this bit reads as 1 and 
                // ignores writes.
                if (settings.no_26_bits && !forced) {
                    return;
                }
                
                util::modify_bit(R1, 4, value);
                return;

            case id::cp::CP15_R1_D:
                // On ARM processors which do not support 26-bit backwards-
                // compatibility configurations, this bit reads as 1 and 
                // ignores writes
                if (settings.no_26_bits && !forced) {
                    return;
                }

                util::modify_bit(R1, 5, value);
                return;

            case id::cp::CP15_R1_L: // TODO, idk what the fuck is the "old abort model"
                // On later processors, this bit reads as 1 and ignores writes.
                if ((static_cast<u8>(settings.arch) > 3) && !forced) {
                    return;
                }

                util::modify_bit(R1, 6, value);  
                return;

            case id::cp::CP15_R1_B: 
                // On ARM processors that support only little-endian memory systems, 
                // this bit reads as 0 and ignores writes. On ARM processors that 
                // support only big-endian memory systems, this bit reads as 1 and 
                // ignores writes
                if ((settings.only_little_endian || settings.only_big_endian) && !forced) {
                    return;
                }

                util::modify_bit(R1, 7, value);
                return;

            case id::cp::CP15_R1_S:     
                util::modify_bit(R1, 8, value);  
                return;

            case id::cp::CP15_R1_R:     
                util::modify_bit(R1, 9, value);
                return;

            case id::cp::CP15_R1_F: 
                util::modify_bit(R1, 10, value);
                return; 

            case id::cp::CP15_R1_Z: 
                // If branch prediction cannot be disabled, this bit reads as 1 
                // and ignores writes. On ARM processors that do not support 
                // branch prediction, this bit reads as 0 and ignores writes
                if (settings.branch_prediction_cannot_disable && !forced) {
                    return;
                }

                if (settings.has_branch_prediction || forced) {
                    util::modify_bit(R1, 11, value); 
                }
                
                return;
    
            case id::cp::CP15_R1_I: 
                // If a unified cache is used or the instruction cache is not 
                // implemented, this bit reads as 0 and ignores writes. If the 
                // instruction cache cannot be disabled, this bit reads as 1 
                // and ignores writes.
                if (
                    (
                        (settings.has_separate_inst_cache == false) ||
                        (settings.has_unified_cache) ||
                        (settings.instruction_cache_cannot_disable)
                    ) && !forced
                ) {
                    return;
                }

                if (settings.has_separate_cache || forced) {
                    util::modify_bit(R1, 12, value); 
                }
                
                return;

            case id::cp::CP15_R1_V: 
                // On ARM processors that do not support high vectors, 
                // this bit reads as 0 and ignores writes.
                if (settings.has_high_vectors || forced) {
                    util::modify_bit(R1, 13, value); 
                }

                return;

            case id::cp::CP15_R1_RR:    
                // If the cache does not allow a choice of replacement 
                // strategy this bit should ignore writes, and read as 
                // 0 or 1 according to whether the replacement strategy 
                // has a reasonably easily predictable worst-case performance.
                if (!settings.has_cache && !forced) {
                    return;
                }

                if (settings.has_predictable_cache_strategy || forced) {
                    util::modify_bit(R1, 14, value);
                }

                return;

            case id::cp::CP15_R1_L4: 
                // For some ARM processors that support architecture 
                // version 5 or above, this bit controls a backwards-
                // compatibility feature with previous versions of 
                // the architecture.
                if ((static_cast<u8>(settings.arch) >= 5) && !forced) {
                    return;
                }
            
                if (settings.is_L4_bit_enabled_cp15 || forced) {
                    util::modify_bit(R1, 15, value);
                }

                return;

            case id::cp::CP15_R2_MMU: R2 = value; return;
            case id::cp::CP15_R2_MMU_TRANSLATION_BASE:  
                if (R2 == value) {
                    return;
                }

                util::swap_bits(R2, 14, 31, value);
                // mmu.flush_tlb(); // B3-3 TODO, ENABLED THIS WHEN MMU DEVELOPMENT STARTS
                return;
            case id::cp::CP15_R2: R2 = value; return;
            case id::cp::CP15_R2_PU: R2 = value; return;
            case id::cp::CP15_R2_PU_C0: util::modify_bit(R2, 0, value); return;
            case id::cp::CP15_R2_PU_C1: util::modify_bit(R2, 1, value); return;
            case id::cp::CP15_R2_PU_C2: util::modify_bit(R2, 2, value); return;
            case id::cp::CP15_R2_PU_C3: util::modify_bit(R2, 3, value); return;
            case id::cp::CP15_R2_PU_C4: util::modify_bit(R2, 4, value); return;
            case id::cp::CP15_R2_PU_C5: util::modify_bit(R2, 5, value); return;
            case id::cp::CP15_R2_PU_C6: util::modify_bit(R2, 6, value); return;
            case id::cp::CP15_R2_PU_C7: util::modify_bit(R2, 7, value); return;
            case id::cp::CP15_R3: R3 = value; return;
            case id::cp::CP15_R3_MMU: R3 = value; return;
            case id::cp::CP15_R3_MMU_D0: util::swap_bits(R3, 0, 1, value);  return;
            case id::cp::CP15_R3_MMU_D1: util::swap_bits(R3, 2, 3, value);  return;
            case id::cp::CP15_R3_MMU_D2: util::swap_bits(R3, 4, 5, value);  return;
            case id::cp::CP15_R3_MMU_D3: util::swap_bits(R3, 6, 7, value);  return;
            case id::cp::CP15_R3_MMU_D4: util::swap_bits(R3, 8, 9, value);  return;
            case id::cp::CP15_R3_MMU_D5: util::swap_bits(R3, 10, 11, value); return;
            case id::cp::CP15_R3_MMU_D6: util::swap_bits(R3, 12, 13, value); return;
            case id::cp::CP15_R3_MMU_D7: util::swap_bits(R3, 14, 15, value); return;
            case id::cp::CP15_R3_MMU_D8: util::swap_bits(R3, 16, 17, value); return;
            case id::cp::CP15_R3_MMU_D9: util::swap_bits(R3, 18, 19, value); return;
            case id::cp::CP15_R3_MMU_D10: util::swap_bits(R3, 20, 21, value); return;
            case id::cp::CP15_R3_MMU_D11: util::swap_bits(R3, 22, 23, value); return;
            case id::cp::CP15_R3_MMU_D12: util::swap_bits(R3, 24, 25, value); return;
            case id::cp::CP15_R3_MMU_D13: util::swap_bits(R3, 26, 27, value); return;
            case id::cp::CP15_R3_MMU_D14: util::swap_bits(R3, 28, 29, value); return;
            case id::cp::CP15_R3_MMU_D15: util::swap_bits(R3, 30, 31, value); return;
            case id::cp::CP15_R3_PU: R3 = value; return;
            case id::cp::CP15_R3_PU_B0: util::modify_bit(R3, 0, value); return;
            case id::cp::CP15_R3_PU_B1: util::modify_bit(R3, 1, value); return;
            case id::cp::CP15_R3_PU_B2: util::modify_bit(R3, 2, value); return;
            case id::cp::CP15_R3_PU_B3: util::modify_bit(R3, 3, value); return;
            case id::cp::CP15_R3_PU_B4: util::modify_bit(R3, 4, value); return;
            case id::cp::CP15_R3_PU_B5: util::modify_bit(R3, 5, value); return;
            case id::cp::CP15_R3_PU_B6: util::modify_bit(R3, 6, value); return;
            case id::cp::CP15_R3_PU_B7: util::modify_bit(R3, 7, value); return;

            case id::cp::CP15_R4: R4 = value; return;
            case id::cp::CP15_R4_MMU: R4 = value; return;
            case id::cp::CP15_R4_PU: R4 = value; return;

            case id::cp::CP15_R5: R5 = value; return;
            case id::cp::CP15_R5_MMU: R5 = value; return;
            case id::cp::CP15_R5_MMU_DOMAIN: util::swap_bits(R5, 4, 7, value); return;
            case id::cp::CP15_R5_MMU_STATUS: util::swap_bits(R5, 0, 3, value); return;
            case id::cp::CP15_R5_PU: R5 = value; return;
            case id::cp::CP15_R5_PU_AP0: util::swap_bits(R5, 0, 1, value); return;
            case id::cp::CP15_R5_PU_AP1: util::swap_bits(R5, 2, 3, value); return;
            case id::cp::CP15_R5_PU_AP2: util::swap_bits(R5, 4, 5, value); return;
            case id::cp::CP15_R5_PU_AP3: util::swap_bits(R5, 6, 7, value); return;
            case id::cp::CP15_R5_PU_AP4: util::swap_bits(R5, 8, 9, value); return;
            case id::cp::CP15_R5_PU_AP5: util::swap_bits(R5, 10, 11, value); return;
            case id::cp::CP15_R5_PU_AP6: util::swap_bits(R5, 12, 13, value); return;
            case id::cp::CP15_R5_PU_AP7: util::swap_bits(R5, 14, 15, value); return;
            case id::cp::CP15_R6_MMU: R6 = value; return;
            case id::cp::CP15_R6_MMU_FAR: R6 = value; return;
            case id::cp::CP15_R6_PU_0: R6_PU_0 = value; return;
            case id::cp::CP15_R6_PU_0_BASE_ADDRESS: 
                globals.mpu_address_change = true;
                util::swap_bits(R6_PU_0, 12, 31, value); 
                return;
            case id::cp::CP15_R6_PU_0_SIZE:         
                globals.mpu_address_change = true;
                util::swap_bits(R6_PU_0, 1, 5, value); 
                return;
            case id::cp::CP15_R6_PU_0_E:            
                globals.mpu_address_change = true;
                util::modify_bit(R6_PU_0, 0, value); 
                return;
            case id::cp::CP15_R6_PU_1:              
                globals.mpu_address_change = true;
                R6_PU_1 = value; 
                return;
            case id::cp::CP15_R6_PU_1_BASE_ADDRESS: 
                globals.mpu_address_change = true;
                util::swap_bits(R6_PU_1, 12, 31, value); 
                return; 
            case id::cp::CP15_R6_PU_1_SIZE:         
                globals.mpu_address_change = true;
                util::swap_bits(R6_PU_1, 1, 5, value); 
                return; // same
            case id::cp::CP15_R6_PU_1_E:            
                globals.mpu_address_change = true;
                util::modify_bit(R6_PU_1, 0, value); 
                return;
            case id::cp::CP15_R6_PU_2:              
                globals.mpu_address_change = true;
                R6_PU_2 = value; 
                return;
            case id::cp::CP15_R6_PU_2_BASE_ADDRESS: 
                globals.mpu_address_change = true;
                util::swap_bits(R6_PU_2, 12, 31, value); 
                return;
            case id::cp::CP15_R6_PU_2_SIZE:         
                globals.mpu_address_change = true;
                util::swap_bits(R6_PU_2, 1, 5, value); 
                return;
            case id::cp::CP15_R6_PU_2_E:            
                globals.mpu_address_change = true;
                util::modify_bit(R6_PU_2, 0, value);
                return;
            case id::cp::CP15_R6_PU_3:              
                globals.mpu_address_change = true;
                R6_PU_3 = value;
                return;
            case id::cp::CP15_R6_PU_3_BASE_ADDRESS: 
                globals.mpu_address_change = true;
                util::swap_bits(R6_PU_3, 12, 31, value);
                return;
            case id::cp::CP15_R6_PU_3_SIZE:         
                globals.mpu_address_change = true;
                util::swap_bits(R6_PU_3, 1, 5, value); 
                return;
            case id::cp::CP15_R6_PU_3_E:            
                globals.mpu_address_change = true;
                util::modify_bit(R6_PU_3, 0, value);
                return;
            case id::cp::CP15_R6_PU_4:              
                globals.mpu_address_change = true;
                R6_PU_4 = value;
                return;
            case id::cp::CP15_R6_PU_4_BASE_ADDRESS: 
                globals.mpu_address_change = true;
                util::swap_bits(R6_PU_4, 12, 31, value); 
                return;
            case id::cp::CP15_R6_PU_4_SIZE:         
                globals.mpu_address_change = true;
                util::swap_bits(R6_PU_4, 1, 5, value); 
                return;
            case id::cp::CP15_R6_PU_4_E:            
                globals.mpu_address_change = true;
                util::modify_bit(R6_PU_4, 0, value);
                 return;
            case id::cp::CP15_R6_PU_5:              
                globals.mpu_address_change = true;
                R6_PU_5 = value; 
                return;
            case id::cp::CP15_R6_PU_5_BASE_ADDRESS: 
                globals.mpu_address_change = true;
                util::swap_bits(R6_PU_5, 12, 31, value); 
                return;
            case id::cp::CP15_R6_PU_5_SIZE:         
                globals.mpu_address_change = true;
                util::swap_bits(R6_PU_5, 1, 5, value); 
                return;
            case id::cp::CP15_R6_PU_5_E:            
                globals.mpu_address_change = true;
                util::modify_bit(R6_PU_5, 0, value); 
                return;
            case id::cp::CP15_R6_PU_6:              
                globals.mpu_address_change = true;
                R6_PU_6 = value; 
                return;
            case id::cp::CP15_R6_PU_6_BASE_ADDRESS: 
                globals.mpu_address_change = true;
                util::swap_bits(R6_PU_6, 12, 31, value); 
                return;
            case id::cp::CP15_R6_PU_6_SIZE:         
                globals.mpu_address_change = true;
                util::swap_bits(R6_PU_6, 1, 5, value); 
                return;
            case id::cp::CP15_R6_PU_6_E:            
                globals.mpu_address_change = true;
                util::modify_bit(R6_PU_6, 0, value); 
                return;
            case id::cp::CP15_R6_PU_7:              
                globals.mpu_address_change = true;
                R6_PU_7 = value; 
                return;
            case id::cp::CP15_R6_PU_7_BASE_ADDRESS: 
                globals.mpu_address_change = true;
                util::swap_bits(R6_PU_7, 12, 31, value); 
                return;
            case id::cp::CP15_R6_PU_7_SIZE:         
                globals.mpu_address_change = true;
                util::swap_bits(R6_PU_7, 1, 5, value); 
                return;
            case id::cp::CP15_R6_PU_7_E:            
                globals.mpu_address_change = true;
                util::modify_bit(R6_PU_7, 0, value); 
                return;
            case id::cp::CP15_R7:     R7 = value; return;
            case id::cp::CP15_R7_CACHE_INDEX: // TODO
            case id::cp::CP15_R7_CACHE_SET: // TODO
            case id::cp::CP15_R8_MMU:       
                // see page B3-26 for TLB invalidation function list
                return;
            case id::cp::CP15_R8_PU:        R8 = value; return;
            case id::cp::CP15_R9:           R9 = value; return;
            case id::cp::CP15_R9_CACHE_INDEX: // TODO
            case id::cp::CP15_R9_CACHE_L: // TODO
            case id::cp::CP15_R10:          R10 = value; return;
            case id::cp::CP15_R10_MMU:      R10 = value; return;
            case id::cp::CP15_R10_MMU_BASE: // TODO: SEE PAGE B3-27
            case id::cp::CP15_R10_MMU_VICTIM: // TODO: SEE PAGE B3-27
            case id::cp::CP15_R10_MMU_P:    util::modify_bit(R10, 0, value); break;
            case id::cp::CP15_R10_PU:       R10 = value; return;
            case id::cp::CP15_R11:          R11 = value; return;
            case id::cp::CP15_R12:          R12 = value; return;
            case id::cp::CP15_R13:          R13 = value; return;
            case id::cp::CP15_R13_PID:      util::swap_bits(R13, 25, 31, value); return;
            case id::cp::CP15_R14:          R14 = value; return;
            case id::cp::CP15_R15:          R15 = value; return;
        };
    }



























private:
    void setup_R0_processor_id() {
        bool pre_arm7 = false;
        bool arm7 = false;
        bool post_arm7 = false;

        switch (settings.product_family) {
            case id::product_family::ARM1:
            case id::product_family::ARM2:
            case id::product_family::ARM2aS:
            case id::product_family::ARM6: pre_arm7 = true; break;
            case id::product_family::ARM7:
            case id::product_family::ARM7T:
            case id::product_family::ARM7EJ: arm7 = true; break;
            default: 
                post_arm7 = true; break;
        }


        write(id::cp::CP15_R0_ID_REVISION, settings.revision);


        if (pre_arm7) {
            switch (settings.processor) {
                case id::processor::ARM3:   write(id::cp::CP15_R0_ID_PRE7_ID, 0x4156030); break;
                case id::processor::ARM600: write(id::cp::CP15_R0_ID_PRE7_ID, 0x4156060); break;
                case id::processor::ARM610: write(id::cp::CP15_R0_ID_PRE7_ID, 0x4156061); break;
                case id::processor::ARM620: write(id::cp::CP15_R0_ID_PRE7_ID, 0x4156062); break;
                // TODO: ADD MORE
                // could be useful:
                // https://github.com/NetBSD/src/blob/461e4391743c2e1fdff97bb2b351cfb1a5fd083a/sys/arch/arm/include/cputypes.h#L113
                default: write(id::cp::CP15_R0_ID_PRE7_ID, 0);
            }
        } else {
            // https://developer.arm.com/documentation/ddi0406/b/Appendices/ARMv4-and-ARMv5-Differences/System-Control-coprocessor--CP15--support/c0--ID-support?lang=en#CHDGAGJH

            if (arm7) {
                // variant (ARM7 specific)
                write(id::cp::CP15_R0_ID_7_VARIANT, settings.variant);

                // A bit
                if (settings.specific_arch == id::specific_arch::ARMv3) {
                    write(id::cp::CP15_R0_ID_7_A, false);
                } else if (settings.specific_arch == id::specific_arch::ARMv4T) {
                    write(id::cp::CP15_R0_ID_7_A, true);
                } else {
                    // TODO: add an error, not sure here
                }
            } else if (post_arm7) {
                // architecure
                switch (settings.specific_arch) {
                    case id::specific_arch::ARMv4:    write(id::cp::CP15_R0_ID_POST7_ARCHITECTURE, 0x1); break;
                    case id::specific_arch::ARMv4T:   write(id::cp::CP15_R0_ID_POST7_ARCHITECTURE, 0x2); break;
                    case id::specific_arch::ARMv5:    write(id::cp::CP15_R0_ID_POST7_ARCHITECTURE, 0x3); break; // obsolete
                    case id::specific_arch::ARMv5T:   write(id::cp::CP15_R0_ID_POST7_ARCHITECTURE, 0x4); break;
                    case id::specific_arch::ARMv5TE:  write(id::cp::CP15_R0_ID_POST7_ARCHITECTURE, 0x5); break;
                    case id::specific_arch::ARMv5TEJ: write(id::cp::CP15_R0_ID_POST7_ARCHITECTURE, 0x6); break;
                    case id::specific_arch::ARMv6:    write(id::cp::CP15_R0_ID_POST7_ARCHITECTURE, 0x7); break;
                    // https://en.wikipedia.org/wiki/Comparison_of_ARM_processors
                    default: write(id::cp::CP15_R0_ID_POST7_ARCHITECTURE, 0xF); // defined by CPUID scheme, TODO: research wtf this actually is
                }

                // variant (post-ARM7 specific)
                write(id::cp::CP15_R0_ID_POST7_VARIANT, settings.variant);
            }

            // implementor
            // source: https://developer.arm.com/documentation/ddi0406/b/System-Level-Architecture/Virtual-Memory-System-Architecture--VMSA-/CP15-registers-for-a-VMSA-implementation/c0--Main-ID-Register--MIDR-?lang=en
            switch (settings.implementor) {
                case id::implementor::ARM:      write(id::cp::CP15_R0_ID_IMPLEMENTOR, constants::implementor::ARM /* A */); break;
                case id::implementor::BRCM:     write(id::cp::CP15_R0_ID_IMPLEMENTOR, constants::implementor::BRCM /* B */); break;
                case id::implementor::DEC:      write(id::cp::CP15_R0_ID_IMPLEMENTOR, constants::implementor::DEC /* D */); break;
                case id::implementor::MOTOROLA: write(id::cp::CP15_R0_ID_IMPLEMENTOR, constants::implementor::MOTOROLA /* M */); break;
                case id::implementor::QUALCOMM: write(id::cp::CP15_R0_ID_IMPLEMENTOR, constants::implementor::QUALCOMM /* Q */); break;
                case id::implementor::MARVELL:  write(id::cp::CP15_R0_ID_IMPLEMENTOR, constants::implementor::MARVELL /* V */); break;
                case id::implementor::INTEL:    write(id::cp::CP15_R0_ID_IMPLEMENTOR, constants::implementor::INTEL /* i */); break;
                case id::implementor::LLARM:   
                    u8 implementor_code = 0;

                    // if this is some kind of malware environment sandbox, try to hide that it's an emulator
                    if (settings.anti_emulation_detection) {
                        implementor_code = constants::implementor::ARM;
                    } else {
                        implementor_code = constants::implementor::LLARM;
                    }

                    write(id::cp::CP15_R0_ID_IMPLEMENTOR, implementor_code);
                    break;
            }

            // primary part number
            write(id::cp::CP15_R0_ID_PPN, settings.ppn);
        }

        // last minute CPU checks just in case (TODO)

    }















    // TODO (B2-9)
    void setup_R0_cache() {
        if (!settings.has_cache) {
            return;
        }

        const bool unified = settings.has_unified_cache;
        const bool separate = settings.has_separate_cache;

        // S bit
        if (unified) {
            write(id::cp::CP15_R0_CACHE_S, false);
        } else if (separate) {
            write(id::cp::CP15_R0_CACHE_S, true);
        } else {
            // TODO error
        }

        // ctype field
        write(id::cp::CP15_R0_CACHE_CTYPE, settings.cache_ctype_field);

        // if M = 0
        constexpr u32 KB_1 = util::get_kb(1);
        constexpr u32 KB_2 = util::get_kb(2);
        constexpr u32 KB_4 = util::get_kb(4);
        constexpr u32 KB_8 = util::get_kb(8);
        constexpr u32 KB_16 = util::get_kb(16);
        constexpr u32 KB_32 = util::get_kb(32);
        constexpr u32 KB_64 = util::get_kb(64);

        // if M = 1 (the numbers are super weird here, blame ARM for this weird standard)
        constexpr u32 KB_1_POINT_5 = (util::get_kb(1) | (util::get_kb(1) >> 1));
        constexpr u32 KB_3 = (util::get_kb(2) | (util::get_kb(2) >> 1));
        constexpr u32 KB_6 = (util::get_kb(4) | (util::get_kb(4) >> 1));
        constexpr u32 KB_12 = (util::get_kb(8) | (util::get_kb(8) >> 1));
        constexpr u32 KB_24 = (util::get_kb(16) | (util::get_kb(16) >> 1));
        constexpr u32 KB_48 = (util::get_kb(32) | (util::get_kb(32) >> 1));
        constexpr u32 KB_96 = (util::get_kb(64) | (util::get_kb(64) >> 1));

        // data cache size
        switch (settings.data_cache_size) {
            case 512 /* bytes */:
            case 768 /* bytes */: write(id::cp::CP15_R0_CACHE_DSIZE_SIZE, 0b000); break;
            case KB_1: 
            case KB_1_POINT_5: write(id::cp::CP15_R0_CACHE_DSIZE_SIZE, 0b001); break;
            case KB_2: 
            case KB_3: write(id::cp::CP15_R0_CACHE_DSIZE_SIZE, 0b010); break;
            case KB_4: 
            case KB_6: write(id::cp::CP15_R0_CACHE_DSIZE_SIZE, 0b011); break;
            case KB_8: 
            case KB_12: write(id::cp::CP15_R0_CACHE_DSIZE_SIZE, 0b100); break;
            case KB_16: 
            case KB_24: write(id::cp::CP15_R0_CACHE_DSIZE_SIZE, 0b101); break;
            case KB_32: 
            case KB_48: write(id::cp::CP15_R0_CACHE_DSIZE_SIZE, 0b110); break;
            case KB_64: 
            case KB_96: write(id::cp::CP15_R0_CACHE_DSIZE_SIZE, 0b111); break;
            default: break; // TODO ADD ERROR
        }

        // instruction cache size
        switch (settings.instruction_cache_size) {
            case 512:
            case 768: write(id::cp::CP15_R0_CACHE_ISIZE_SIZE, 0b000); break;
            case KB_1: 
            case KB_1_POINT_5: write(id::cp::CP15_R0_CACHE_ISIZE_SIZE, 0b001); break;
            case KB_2: 
            case KB_3: write(id::cp::CP15_R0_CACHE_ISIZE_SIZE, 0b010); break;
            case KB_4: 
            case KB_6: write(id::cp::CP15_R0_CACHE_ISIZE_SIZE, 0b011); break;
            case KB_8: 
            case KB_12: write(id::cp::CP15_R0_CACHE_ISIZE_SIZE, 0b100); break;
            case KB_16: 
            case KB_24: write(id::cp::CP15_R0_CACHE_ISIZE_SIZE, 0b101); break;
            case KB_32: 
            case KB_48: write(id::cp::CP15_R0_CACHE_ISIZE_SIZE, 0b110); break;
            case KB_64: 
            case KB_96: write(id::cp::CP15_R0_CACHE_ISIZE_SIZE, 0b111); break;
            default: break; // TODO ADD ERROR OR WARNING
        }

        // data cache line length
        switch (settings.data_cache_line_length_bytes) {
            case 8: write(id::cp::CP15_R0_CACHE_DSIZE_LEN, 0b00); break;
            case 16: write(id::cp::CP15_R0_CACHE_DSIZE_LEN, 0b01); break;
            case 32: write(id::cp::CP15_R0_CACHE_DSIZE_LEN, 0b10); break;
            case 64: write(id::cp::CP15_R0_CACHE_DSIZE_LEN, 0b11); break;
            default: break; // TODO ADD ERROR OR WARNING 
        }

        // instruction cache line length
        switch (settings.instruction_cache_line_length_bytes) {
            case 8: write(id::cp::CP15_R0_CACHE_ISIZE_LEN, 0b00); break;
            case 16: write(id::cp::CP15_R0_CACHE_ISIZE_LEN, 0b01); break;
            case 32: write(id::cp::CP15_R0_CACHE_ISIZE_LEN, 0b10); break;
            case 64: write(id::cp::CP15_R0_CACHE_ISIZE_LEN, 0b11); break;
            default: break; // TODO ADD ERROR OR WARNING 
        }

        // data cache associativity
        switch (settings.data_cache_assoc_way) {
            case 1: write(id::cp::CP15_R0_CACHE_DSIZE_ASSOC, 0b000); break;
            case 2:
            case 3: write(id::cp::CP15_R0_CACHE_DSIZE_ASSOC, 0b001); break;
            case 4: 
            case 6: write(id::cp::CP15_R0_CACHE_DSIZE_ASSOC, 0b010); break;
            case 8:
            case 12: write(id::cp::CP15_R0_CACHE_DSIZE_ASSOC, 0b011); break;
            case 16:
            case 24: write(id::cp::CP15_R0_CACHE_DSIZE_ASSOC, 0b100); break;
            case 32:
            case 48: write(id::cp::CP15_R0_CACHE_DSIZE_ASSOC, 0b101); break;
            case 64:
            case 96: write(id::cp::CP15_R0_CACHE_DSIZE_ASSOC, 0b110); break;
            case 128:
            case 192: write(id::cp::CP15_R0_CACHE_DSIZE_ASSOC, 0b111); break;
            default: break; // TODO ADD ERROR OR WARNING
        }

        // instruction cache associativity
        switch (settings.instruction_cache_assoc_way) {
            case 1: write(id::cp::CP15_R0_CACHE_ISIZE_ASSOC, 0b000); break;
            case 2:
            case 3: write(id::cp::CP15_R0_CACHE_ISIZE_ASSOC, 0b001); break;
            case 4: 
            case 6: write(id::cp::CP15_R0_CACHE_ISIZE_ASSOC, 0b010); break;
            case 8:
            case 12: write(id::cp::CP15_R0_CACHE_ISIZE_ASSOC, 0b011); break;
            case 16:
            case 24: write(id::cp::CP15_R0_CACHE_ISIZE_ASSOC, 0b100); break;
            case 32:
            case 48: write(id::cp::CP15_R0_CACHE_ISIZE_ASSOC, 0b101); break;
            case 64:
            case 96: write(id::cp::CP15_R0_CACHE_ISIZE_ASSOC, 0b110); break;
            case 128:
            case 192: write(id::cp::CP15_R0_CACHE_ISIZE_ASSOC, 0b111); break;
            default: break; // TODO ADD ERROR OR WARNING
        }


        // M bit (data cache)
        if (
            (shared::util::popcount(settings.data_cache_size) == 2) &&
            (shared::util::popcount(settings.data_cache_assoc_way) == 2)
        ) {
            write(id::cp::CP15_R0_CACHE_DSIZE_M, true);
        } else if (
            (shared::util::popcount(settings.data_cache_size) == 1) &&
            (shared::util::popcount(settings.data_cache_assoc_way) == 1)
        ) {
            write(id::cp::CP15_R0_CACHE_DSIZE_M, false);
        } else {
            // ADD WARNING OR ERROR HERE IDK
        }


        // M bit (instruction cache)
        if (
            (shared::util::popcount(settings.instruction_cache_size) == 2) &&
            (shared::util::popcount(settings.instruction_cache_assoc_way) == 2)
        ) {
            write(id::cp::CP15_R0_CACHE_ISIZE_M, true);
        } else if (
            (shared::util::popcount(settings.instruction_cache_size) == 1) &&
            (shared::util::popcount(settings.instruction_cache_assoc_way) == 1)
        ) {
            write(id::cp::CP15_R0_CACHE_ISIZE_M, false);
        } else {
            // ADD WARNING OR ERROR HERE IDK
        }
    }
















    void setup_R1_control() {
        // M
        write(id::cp::CP15_R1_M, settings.is_mmu_enabled, FORCED);

        // A
        write(id::cp::CP15_R1_A, settings.has_alignment_fault_checking, FORCED);

        // C
        if (settings.has_cache) {
            if (settings.cache_cannot_disable) {
                write(id::cp::CP15_R1_C, true, FORCED);
            } else if (settings.has_unified_cache) {
                write(id::cp::CP15_R1_C, true, FORCED);
            } else if (settings.has_separate_data_cache && settings.has_separate_cache) {
                write(id::cp::CP15_R1_C, true, FORCED);
            } else {
                write(id::cp::CP15_R1_C, false, FORCED); // maybe, idk
                // error TODO
            }
        } else {
            write(id::cp::CP15_R1_C, false, FORCED); // no cache present
        }

        // W
        write(id::cp::CP15_R1_W, settings.has_write_buffer, FORCED);

        // P
        if (settings.no_26_bits || settings.backwards_compat_support_26_bits) {
            write(id::cp::CP15_R1_P, true, FORCED);
        } else if (settings.only_26_bits) {
            write(id::cp::CP15_R1_P, false, FORCED);
        } else {
            // TODO dev error config
        }

        // D
        if (settings.no_26_bits || settings.backwards_compat_support_26_bits) {
            write(id::cp::CP15_R1_D, true, FORCED);
        } else if (settings.only_26_bits) {
            write(id::cp::CP15_R1_D, false, FORCED);
        } else {
            // TODO dev error config
        }

        // L
        if (settings.is_abort_model_early) {
            write(id::cp::CP15_R1_L, false, FORCED);
        } else if (settings.is_abort_model_late) {
            write(id::cp::CP15_R1_L, true, FORCED);
        } else {
            // TODO dev error config
        }

        // B
        if (settings.only_little_endian) {
            write(id::cp::CP15_R1_B, false, FORCED);
            globals.is_little_endian = true;
        } else if (settings.only_big_endian) {
            write(id::cp::CP15_R1_B, true, FORCED);
            globals.is_little_endian = false;
        } else {
            if (settings.is_little_endian) {
                write(id::cp::CP15_R1_B, false, FORCED);
                globals.is_little_endian = true;
            } else if (settings.is_big_endian) {
                write(id::cp::CP15_R1_B, true, FORCED);
                globals.is_little_endian = false;
            } else {
                // TODO dev error config
            }
        }


        // S
        write(id::cp::CP15_R1_S, settings.has_system_protection_bit, FORCED);

        // R
        write(id::cp::CP15_R1_S, settings.has_rom_protection_bit, FORCED);

        // F
        write(id::cp::CP15_R1_F, settings.has_F_bit_enabled_cp15, FORCED);

        // Z
        write(id::cp::CP15_R1_Z, settings.has_branch_prediction, FORCED);

        // I
        write(id::cp::CP15_R1_I, settings.has_separate_inst_cache, FORCED);

        // V
        write(id::cp::CP15_R1_V, settings.has_high_vectors, FORCED);

        // RR
        write(id::cp::CP15_R1_RR, settings.has_predictable_cache_strategy, FORCED);

        // L4
        write(id::cp::CP15_R1_L4, settings.is_L4_bit_enabled_cp15, FORCED);
    }










public:
    CP15(SETTINGS& settings, GLOBALS& globals) : settings(settings), globals(globals) {
        // R0 setup
        setup_R0_processor_id();
        setup_R0_cache();

        // R1 setup
        setup_R1_control();

        // R2_MMU is implemented by the programmer
        // R3_MMU is implemented by the programmer
        // R4_MMU is reserved
        // R5_MMU is implemented by the programmer
        // R6_MMU is implemented by the programmer
        // R8_MMU is a special write-only register, different implementation required
        // R10_MMU is implemented by the programmer

        // R2_PU is implemented by the programmer
        // R3_PU is implemented by the programmer
        // R4_PU is reserved
        // R5_PU is implemented by the programmer
        // R6_PU is implemented by the programmer
        // R8_PU is reserved
        // R10_PU is reserved

        // R7_CACHE is a special write-only register, different implementation required
        // R9_CACHE i honestly don't know, TODO
    }


};





// NOTES:
/*
MRC p15,0,<Rt>,c0,c0,0    ; Read CP15 Main ID Register
MRC p15,0,<Rt>,c0,c0,1    ; Read CP15 Cache Type Register
*/