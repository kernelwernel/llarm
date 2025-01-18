// TODO: THIS SHOULD BE DISABLED BEFORE V2, COPROCESSORS DIDN'T EXIST IN V1

// https://developer.arm.com/documentation/ddi0360/f/control-coprocessor-cp15/summary-of-control-coprocessor-cp15-registers-and-operations
// ^ super useful

// CPU ID codes:
// https://github.com/torvalds/linux/blob/619f0b6fad524f08d493a98d55bac9ab8895e3a6/arch/arm64/include/asm/cputype.h#L57 (ARM64)
// https://github.com/torvalds/linux/blob/619f0b6fad524f08d493a98d55bac9ab8895e3a6/arch/arm/include/asm/cputype.h#L66 (ARM32)

#pragma once

#include "types.hpp"
#include "settings.hpp"
#include "id.hpp"

struct COPROCESSOR {
private:
    SETTINGS& settings;

public:
    // ID codes
    u32 R0_ID = 0;    // processor ID 
    u32 R0_CACHE = 0; // Cache 

    // Control bits 
    u32 R1_CONTROL = 0; // miscellaneous control bits

    // NOTE: 
    // MMU = memory management unit
    // PU = protection unit
    
    // Memory protection and control
    u32 R2_MMU = 0; // translation table
    u32 R2_PU  = 0; // cachability bits
    
    // Memory protection and control 
    u32 R3_MMU = 0; // domain access control
    u32 R3_PU  = 0; // bufferability bits

    // Memory protection and control
    u32 R4_MMU = 0; // reserved
    u32 R4_PU  = 0; // reserved

    // Memory protection and control
    u32 R5_MMU = 0; // fault status
    u32 R5_PU  = 0; // access permission bits

    // Memory protection and control
    u32 R6_MMU = 0; // fault address 
    u32 R6_PU  = 0; // protection area control

    // Cache and write buffer
    u32 R7_CACHE = 0; // cache/write buffer control

    // Memory protection and control
    // u32 R8_MMU = 0; // TLB control, this register doesn't really exist (B3-26)
    u32 R8_PU  = 0; // reserved

    // Cache and write buffer 
    u32 R9_CACHE = 0; // cache lockdown

    // Memory protection and control
    u32 R10_MMU = 0; // TLB lockdown
    u32 R10_PU  = 0; // reserved
    
    u32 R11_RESERVED = 0;

    u32 R12_RESERVED = 0;

    // Process ID
    u32 R13_PID = 0; // process ID

    u32 R14_RESERVED = 0;

    u32 R15_IMPL = 0; // implementation defined, not important

/*
    u32 read_cp15(const id::cp15 reg) {
        switch (reg) {
            case id::cp::CP15_R0_ID: return R0_ID;
            case id::cp::CP15_R0_CACHE: return R0_CACHE;
            case id::cp::CP15_R1_CONTROL: return R1_CONTROL;
            case id::cp::CP15_R1_M: return (R1_CONTROL & 1);          // MMU or Protection Unit enable disable
            case id::cp::CP15_R1_A: return (R1_CONTROL & (1 << 1));   // alignment fault checking
            case id::cp::CP15_R1_C: return (R1_CONTROL & (1 << 2));   // unified cache
            case id::cp::CP15_R1_W: return (R1_CONTROL & (1 << 3));   // write buffer
            case id::cp::CP15_R1_P: return (R1_CONTROL & (1 << 4));   // 26-bit backwards-compatibility configurations (PROG32)
            case id::cp::CP15_R1_D: return (R1_CONTROL & (1 << 5));   // 26-bit backwards-compatibility configurations (DATA32)
            case id::cp::CP15_R1_L: return (R1_CONTROL & (1 << 6));   // abort model of the processor
            case id::cp::CP15_R1_B: return (R1_CONTROL & (1 << 7));   // endianness of the memory system
            case id::cp::CP15_R1_S: return (R1_CONTROL & (1 << 8));   // system protection bit
            case id::cp::CP15_R1_R: return (R1_CONTROL & (1 << 9));   // ROM protection bit
            case id::cp::CP15_R1_F: return (R1_CONTROL & (1 << 10));  // IMPLEMENTATION DEFINED
            case id::cp::CP15_R1_Z: return (R1_CONTROL & (1 << 11));  // branch prediction
            case id::cp::CP15_R1_I: return (R1_CONTROL & (1 << 12));  // instruction cache
            case id::cp::CP15_R1_V: return (R1_CONTROL & (1 << 13));  // high vectors
            case id::cp::CP15_R1_RR: return (R1_CONTROL & (1 << 14)); // cache strategy
            case id::cp::CP15_R1_L4: return (R1_CONTROL & (1 << 15)); // ARMv5+ backwards compatibility
            case id::cp::CP15_R2_MMU: return R2_MMU;
            case id::cp::CP15_R2_PU: return R2_PU;
            case id::cp::CP15_R2_PU_C0: return (R2_PU & 1);
            case id::cp::CP15_R2_PU_C1: return (R2_PU & (1 << 1));
            case id::cp::CP15_R2_PU_C2: return (R2_PU & (1 << 2));
            case id::cp::CP15_R2_PU_C3: return (R2_PU & (1 << 3));
            case id::cp::CP15_R2_PU_C4: return (R2_PU & (1 << 4));
            case id::cp::CP15_R2_PU_C5: return (R2_PU & (1 << 5));
            case id::cp::CP15_R2_PU_C6: return (R2_PU & (1 << 6));
            case id::cp::CP15_R2_PU_C7: return (R2_PU & (1 << 7));
            case id::cp::CP15_R3_MMU: return R3_MMU;
            case id::cp::CP15_R3_PU: return R3_PU;
            case id::cp::CP15_R3_PU_B0: return (R3_PU & 1);
            case id::cp::CP15_R3_PU_B1: return (R3_PU & (1 << 1));
            case id::cp::CP15_R3_PU_B2: return (R3_PU & (1 << 2));
            case id::cp::CP15_R3_PU_B3: return (R3_PU & (1 << 3));
            case id::cp::CP15_R3_PU_B4: return (R3_PU & (1 << 4));
            case id::cp::CP15_R3_PU_B5: return (R3_PU & (1 << 5));
            case id::cp::CP15_R3_PU_B6: return (R3_PU & (1 << 6));
            case id::cp::CP15_R3_PU_B7: return (R3_PU & (1 << 7));
            case id::cp::CP15_R4_MMU: return R4_MMU;
            case id::cp::CP15_R4_PU: return R4_PU;
            case id::cp::CP15_R5_MMU: return R5_MMU;
            case id::cp::CP15_R5_PU: return R5_PU;
            case id::cp::CP15_R6_MMU: return R6_MMU;
            case id::cp::CP15_R6_PU: return R6_PU;
            case id::cp::CP15_R7_CACHE: return R7_CACHE;
            //case id::cp::CP15_R8_MMU: return R8_MMU;
            // case id::cp::CP15_R8_MMU: return 0; // WRITE ONLY 
            case id::cp::CP15_R8_PU: return R8_PU;
            case id::cp::CP15_R9_CACHE: return R9_CACHE;
            case id::cp::CP15_R10_MMU: return R10_MMU;
            case id::cp::CP15_R10_PU: return R10_PU;
            case id::cp::CP15_R11_RESERVED: return R11_RESERVED;
            case id::cp::CP15_R12_RESERVED: return R12_RESERVED;
            case id::cp::CP15_R13_PID: return R13_PID;
            case id::cp::CP15_R14_RESERVED: return R14_RESERVED;
            case id::cp::CP15_R15_IMPL: return R15_IMPL;
        }
    }
    */


    void write_cp15(const id::cp reg, const u32 value) {

        // TODO REPLACE THE ABOVE LAMBDAS WITH UTIL FUNCTIONS

        switch (reg) {
            case id::cp::CP15_R0_ID: R0_ID = value; return;
            case id::cp::CP15_R0_ID_IMPLEMENTOR: // TODO
            case id::cp::CP15_R0_ID_PPN: util::swap_bits(R0_ID, 4, ); break;
            case id::cp::CP15_R0_ID_PPN_TOP: // TODO If bits[15:12] of the ID code are 0x7, the ID code is interpreted as follows:
            case id::cp::CP15_R0_ID_PPN_LOWER:
            case id::cp::CP15_R0_ID_REVISION: util::swap_bits(R0_ID, 0, 3); break;
            case id::cp::CP15_R0_ID_POST7_VARIANT: // TODO
            case id::cp::CP15_R0_ID_POST7_ARCH: // TODO
            case id::cp::CP15_R0_ID_7_VARIANT: // TODO
            case id::cp::CP15_R0_ID_7_A: // TODO
            case id::cp::CP15_R0_ID_PRE7_ID: // TODO

            case id::cp::CP15_R0_CACHE: R0_CACHE = value; return;
            case id::cp::CP15_R0_CACHE_CTYPE: // TODO
            case id::cp::CP15_R0_CACHE_S: // TODO
            case id::cp::CP15_R0_CACHE_DSIZE: // TODO
            case id::cp::CP15_R0_CACHE_ISIZE: // TODO
            case id::cp::CP15_R1_CONTROL: R1_CONTROL = value; return;
            case id::cp::CP15_R1_M: 
                if (settings.is_mmu_enabled || settings.is_protection_unit_enabled) {
                    util::modify_bit(R1_CONTROL, 0, value); 
                }
                return;

            case id::cp::CP15_R1_A: 
                if (settings.has_alignment_fault_checking) {
                    util::modify_bit(R1_CONTROL, 1, value);
                }
                return;

            case id::cp::CP15_R1_C:
                if (settings.cache_cannot_disable) {
                    return;
                }

                if (settings.has_cache) {
                    util::modify_bit(R1_CONTROL, 2, value); 
                }

                return;

            case id::cp::CP15_R1_W:
                if (settings.write_buffer_cannot_disable) {
                    return;
                }

                if (settings.has_write_buffer) {
                    util::modify_bit(R1_CONTROL, 3, value);
                }

                return;

            case id::cp::CP15_R1_P:
                if (settings.no_26_bits) {
                    return;
                }
                
                util::modify_bit(R1_CONTROL, 4, value);
                return;

            case id::cp::CP15_R1_D:
                if (settings.no_26_bits) {
                    return;
                }

                util::modify_bit(R1_CONTROL, 5, value);
                return;

            case id::cp::CP15_R1_L:
                if (static_cast<u8>(settings.arch) > 3) {
                    return;
                }

                util::modify_bit(R1_CONTROL, 6, value);  
                return;

            case id::cp::CP15_R1_B: 
                if (settings.only_little_endian || settings.only_big_endian) {
                    return;
                }

                util::modify_bit(R1_CONTROL, 7, value);
                return;

            case id::cp::CP15_R1_S:     util::modify_bit(R1_CONTROL, 8, value);  return; // TODO (B2-15)
            case id::cp::CP15_R1_R:     util::modify_bit(R1_CONTROL, 9, value);  return; // TODO (B2-15)

            case id::cp::CP15_R1_F: 
                // implementation defined
                util::modify_bit(R1_CONTROL, 10, value);
                return; 

            case id::cp::CP15_R1_Z: 
                if (settings.branch_prediction_cannot_disable) {
                    return;
                }

                if (settings.has_branch_prediction) {
                    util::modify_bit(R1_CONTROL, 11, value); 
                }
                
                return;
    
            case id::cp::CP15_R1_I: 
                if (
                    (settings.has_separate_inst_cache == false) ||
                    (settings.has_unified_cache) ||
                    (settings.instruction_cache_cannot_disable)
                ) {
                    return;
                }

                if (settings.has_separate_cache) {
                    util::modify_bit(R1_CONTROL, 12, value); 
                }
                
                return;

            case id::cp::CP15_R1_V: 
                if (settings.has_high_vectors) {
                    util::modify_bit(R1_CONTROL, 13, value); 
                }

                return;

            case id::cp::CP15_R1_RR:    util::modify_bit(R1_CONTROL, 14, value); return; // TODO (B2-16)
            case id::cp::CP15_R1_L4:    util::modify_bit(R1_CONTROL, 15, value); return; // TODO (B2-16)

            case id::cp::CP15_R2_MMU:   R2_MMU = value; return;
            case id::cp::CP15_R2_MMU_TRANSLATION_BASE: // TODO
            case id::cp::CP15_R2_PU:    R2_PU = value; return;
            case id::cp::CP15_R2_PU_C0: util::modify_bit(R2_PU, 0, value); return;
            case id::cp::CP15_R2_PU_C1: util::modify_bit(R2_PU, 1, value); return;
            case id::cp::CP15_R2_PU_C2: util::modify_bit(R2_PU, 2, value); return;
            case id::cp::CP15_R2_PU_C3: util::modify_bit(R2_PU, 3, value); return;
            case id::cp::CP15_R2_PU_C4: util::modify_bit(R2_PU, 4, value); return;
            case id::cp::CP15_R2_PU_C5: util::modify_bit(R2_PU, 5, value); return;
            case id::cp::CP15_R2_PU_C6: util::modify_bit(R2_PU, 6, value); return;
            case id::cp::CP15_R2_PU_C7: util::modify_bit(R2_PU, 7, value); return;
            case id::cp::CP15_R3_MMU:   R3_MMU = value; return;
            case id::cp::CP15_R3_MMU_D0:  util::swap_bits(R3_MMU, 0, 2, value);  return;
            case id::cp::CP15_R3_MMU_D1:  util::swap_bits(R3_MMU, 2, 2, value);  return;
            case id::cp::CP15_R3_MMU_D2:  util::swap_bits(R3_MMU, 4, 2, value);  return;
            case id::cp::CP15_R3_MMU_D3:  util::swap_bits(R3_MMU, 6, 2, value);  return;
            case id::cp::CP15_R3_MMU_D4:  util::swap_bits(R3_MMU, 8, 2, value);  return;
            case id::cp::CP15_R3_MMU_D5:  util::swap_bits(R3_MMU, 10, 2, value); return;
            case id::cp::CP15_R3_MMU_D6:  util::swap_bits(R3_MMU, 12, 2, value); return;
            case id::cp::CP15_R3_MMU_D7:  util::swap_bits(R3_MMU, 14, 2, value); return;
            case id::cp::CP15_R3_MMU_D8:  util::swap_bits(R3_MMU, 16, 2, value); return;
            case id::cp::CP15_R3_MMU_D9:  util::swap_bits(R3_MMU, 18, 2, value); return;
            case id::cp::CP15_R3_MMU_D10: util::swap_bits(R3_MMU, 20, 2, value); return;
            case id::cp::CP15_R3_MMU_D11: util::swap_bits(R3_MMU, 22, 2, value); return;
            case id::cp::CP15_R3_MMU_D12: util::swap_bits(R3_MMU, 24, 2, value); return;
            case id::cp::CP15_R3_MMU_D13: util::swap_bits(R3_MMU, 26, 2, value); return;
            case id::cp::CP15_R3_MMU_D14: util::swap_bits(R3_MMU, 28, 2, value); return;
            case id::cp::CP15_R3_MMU_D15: util::swap_bits(R3_MMU, 30, 2, value); return;
            case id::cp::CP15_R3_PU:    R3_PU = value; return;
            case id::cp::CP15_R3_PU_B0: util::modify_bit(R3_PU, 0, value); return;
            case id::cp::CP15_R3_PU_B1: util::modify_bit(R3_PU, 1, value); return;
            case id::cp::CP15_R3_PU_B2: util::modify_bit(R3_PU, 2, value); return;
            case id::cp::CP15_R3_PU_B3: util::modify_bit(R3_PU, 3, value); return;
            case id::cp::CP15_R3_PU_B4: util::modify_bit(R3_PU, 4, value); return;
            case id::cp::CP15_R3_PU_B5: util::modify_bit(R3_PU, 5, value); return;
            case id::cp::CP15_R3_PU_B6: util::modify_bit(R3_PU, 6, value); return;
            case id::cp::CP15_R3_PU_B7: util::modify_bit(R3_PU, 7, value); return;

            case id::cp::CP15_R4_MMU:   R4_MMU = value; return;
            case id::cp::CP15_R4_PU:    R4_PU = value; return;

            case id::cp::CP15_R5_MMU:   R5_MMU = value; return;
            case id::cp::CP15_R5_MMU_DOMAIN: // TODO
            case id::cp::CP15_R5_MMU_STATUS: // TODO
            case id::cp::CP15_R5_PU:    R5_PU = value; return;
            case id::cp::CP15_R5_PU_AP0: util::swap_bits(R5_PU, 0, 2, value); return;
            case id::cp::CP15_R5_PU_AP1: util::swap_bits(R5_PU, 2, 2, value); return;
            case id::cp::CP15_R5_PU_AP2: util::swap_bits(R5_PU, 4, 2, value); return;
            case id::cp::CP15_R5_PU_AP3: util::swap_bits(R5_PU, 6, 2, value); return;
            case id::cp::CP15_R5_PU_AP4: util::swap_bits(R5_PU, 8, 2, value); return;
            case id::cp::CP15_R5_PU_AP5: util::swap_bits(R5_PU, 10, 2, value); return;
            case id::cp::CP15_R5_PU_AP6: util::swap_bits(R5_PU, 12, 2, value); return;
            case id::cp::CP15_R5_PU_AP7: util::swap_bits(R5_PU, 14, 2, value); return;
            case id::cp::CP15_R6_MMU:    R6_MMU; return;
            case id::cp::CP15_R6_MMU_FAR: // TODO
            case id::cp::CP15_R6_PU:     R6_PU = value; return;
            case id::cp::CP15_R6_PU_BASE_ADDRESS: util::swap_bits(R6_PU, 12, 19, value); return; // TODO: test if this works
            case id::cp::CP15_R6_PU_SIZE:   util::swap_bits(R6_PU, 1, 5, value); return; // same
            case id::cp::CP15_R6_PU_E:      util::modify_bit(R6_PU, 0, value); return;
            case id::cp::CP15_R7_CACHE:     R7_CACHE = value; return;
            case id::cp::CP15_R7_CACHE_INDEX: // TODO
            case id::cp::CP15_R7_CACHE_SET: // TODO
            case id::cp::CP15_R8_MMU:       
                // see page B3-26 for TLB invalidation function list
                return;
            case id::cp::CP15_R8_PU:        R8_PU = value; return;
            case id::cp::CP15_R9_CACHE:     R9_CACHE = value; return;
            case id::cp::CP15_R9_CACHE_INDEX: // TODO
            case id::cp::CP15_R9_CACHE_L: // TODO
            case id::cp::CP15_R10_MMU:      R10_MMU = value; return;
            case id::cp::CP15_R10_MMU_BASE: // TODO: SEE PAGE B3-27
            case id::cp::CP15_R10_MMU_VICTIM: // TODO: SEE PAGE B3-27
            case id::cp::CP15_R10_MMU_P:    util::modify_bit(R10_MMU, 0, value); break;
            case id::cp::CP15_R10_PU:       R10_PU = value; return;
            case id::cp::CP15_R11_RESERVED: R11_RESERVED = value; return;
            case id::cp::CP15_R12_RESERVED: R12_RESERVED = value; return;
            case id::cp::CP15_R13_PID:      R13_PID = value; return;
            case id::cp::CP15_R14_RESERVED: R14_RESERVED = value; return;
            case id::cp::CP15_R15_IMPL:     R15_IMPL = value; return;
        };
    }

    /*
    id::cp15 fetch_specific_cp15_reg(const id::cp_reg cp_reg_id, const u8 opcode1, const u8 opcode2) {
        switch (cp_reg_id) {
            case id::cp_reg::CP15_R0:
                if (opcode2 == 1) {
                    return id::cp::CP15_R0_CACHE;
                } else {
                    return id::cp::CP15_R0_ID;
                }
            case id::cp_reg::CP15_R1:
            case id::cp_reg::CP15_R2:
            case id::cp_reg::CP15_R3:
            case id::cp_reg::CP15_R4:
            case id::cp_reg::CP15_R5:
            case id::cp_reg::CP15_R6:
            case id::cp_reg::CP15_R7:
            case id::cp_reg::CP15_R8:
            case id::cp_reg::CP15_R9:
            case id::cp_reg::CP15_R10:
            case id::cp_reg::CP15_R11:
            case id::cp_reg::CP15_R12:
            case id::cp_reg::CP15_R13:
            case id::cp_reg::CP15_R14:
            case id::cp_reg::CP15_R15:
        };
    }
    */

    bool is_26_bit_arch_program() {
        if (settings.no_26_bits) {
            return false;
        } else if (settings.only_26_bits) {
            return true;
        }

        return (read(id::cp::CP15_R1_P) == false);
    }

    bool is_26_bit_arch_address() {
        if (settings.no_26_bits) {
            return false;
        } else if (settings.only_26_bits) {
            return true;
        }

        return (read(id::cp::CP15_R1_D) == false);
    }

    bool is_only_26_bit_arch() {
        return settings.only_26_bits;
    }

    bool is_26_bit_arch_backwards_support() {
        return settings.backwards_compat_support_26_bits;
    }

    bool no_26_bit_arch_support() {
        return settings.no_26_bits;
    }




public:
    void write() {}


    u32 read(const id::coprocessor cp_id, const id::cp_reg cp_reg_id, const u8 opcode1, const u8 opcode2) {
        switch (cp_id) {
            case id::coprocessor::CP0: return 0;
            case id::coprocessor::CP1: return 0;
            case id::coprocessor::CP2: return 0;
            case id::coprocessor::CP3: return 0;
            case id::coprocessor::CP4: return 0;
            case id::coprocessor::CP5: return 0;
            case id::coprocessor::CP6: return 0;
            case id::coprocessor::CP7: return 0;
            case id::coprocessor::CP8: return 0;
            case id::coprocessor::CP9: return 0;
            case id::coprocessor::CP10: return 0;
            case id::coprocessor::CP11: return 0;
            case id::coprocessor::CP12: return 0;
            case id::coprocessor::CP13: return 0;
            case id::coprocessor::CP14: return 0;
            case id::coprocessor::CP15 [[likely]]: read_cp15();
        }
    }



    id::memory get_access_perm_type(const id::cp15 region) {
        u8 raw_permission_bits = 0;

        const u32 PU_REG_COPY = read(id::cp::CP15_R5_PU);

        switch (region) {
            case id::cp::CP15_R5_PU_AP0: raw_permission_bits = (PU_REG_COPY & 0b11); break;
            case id::cp::CP15_R5_PU_AP1: raw_permission_bits = (PU_REG_COPY & (0b11 << 2)); break;
            case id::cp::CP15_R5_PU_AP2: raw_permission_bits = (PU_REG_COPY & (0b11 << 4)); break;
            case id::cp::CP15_R5_PU_AP3: raw_permission_bits = (PU_REG_COPY & (0b11 << 6)); break;
            case id::cp::CP15_R5_PU_AP4: raw_permission_bits = (PU_REG_COPY & (0b11 << 8)); break;
            case id::cp::CP15_R5_PU_AP5: raw_permission_bits = (PU_REG_COPY & (0b11 << 10)); break;
            case id::cp::CP15_R5_PU_AP6: raw_permission_bits = (PU_REG_COPY & (0b11 << 12)); break;
            case id::cp::CP15_R5_PU_AP7: raw_permission_bits = (PU_REG_COPY & (0b11 << 14)); break;
        }

        if (reg.is_priviledged()) {
            switch (raw_permission_bits) {
                case 0b00: return id::memory::NO_ACCESS_PERMISSION;
                case 0b01: return id::memory::READ_WRITE;
                case 0b10: return id::memory::READ_WRITE;
                case 0b11: return id::memory::READ_WRITE;
            }
        } else {
            switch (raw_permission_bits) {
                case 0b00: return id::memory::NO_ACCESS_PERMISSION;
                case 0b01: return id::memory::NO_ACCESS_PERMISSION;
                case 0b10: return id::memory::READ;
                case 0b11: return id::memory::READ_WRITE;
            }
        }
    }

    COPROCESSOR(MEMORY& memory, SETTINGS& settings) : settings(settings) {
        // CP15 setup
        setup_R0_processor_id();
        setup_R0_cache();


        // R1
        
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


        // revision, this is universal to all ID types
        write_cp15(id::cp::CP15_R0_ID_REVISION, settings.revision);


        if (pre_arm7) {
            switch (settings.processor) {
                case id::processor::ARM3:   write_cp15(id::cp::CP15_R0_ID_PRE7_ID, 0x4156030); break;
                case id::processor::ARM600: write_cp15(id::cp::CP15_R0_ID_PRE7_ID, 0x4156060); break;
                case id::processor::ARM610: write_cp15(id::cp::CP15_R0_ID_PRE7_ID, 0x4156061); break;
                case id::processor::ARM620: write_cp15(id::cp::CP15_R0_ID_PRE7_ID, 0x4156062); break;
                // TODO: ADD MORE
                // could be useful:
                // https://github.com/NetBSD/src/blob/461e4391743c2e1fdff97bb2b351cfb1a5fd083a/sys/arch/arm/include/cputypes.h#L113
            }
        } else {
            // https://developer.arm.com/documentation/ddi0406/b/Appendices/ARMv4-and-ARMv5-Differences/System-Control-coprocessor--CP15--support/c0--ID-support?lang=en#CHDGAGJH

            if (arm7) {
                // variant (ARM7 specific)
                write_cp15(id::cp::CP15_R0_ID_7_VARIANT, settings.variant);

                // A bit
                if (settings.specific_arch == id::specific_arch::ARMv3) {
                    write_cp15(id::cp::CP15_R0_ID_7_A, false);
                } else if (settings.specific_arch == id::specific_arch::ARMv4T) {
                    write_cp15(id::cp::CP15_R0_ID_7_A, true);
                } else {
                    // TODO: add an error, not sure here
                }
            } else if (post_arm7) {
                // architecure
                switch (settings.specific_arch) {
                    case id::specific_arch::ARMv4:    write_cp15(id::cp::CP15_R0_ID_POST7_ARCH, 0x1); break;
                    case id::specific_arch::ARMv4T:   write_cp15(id::cp::CP15_R0_ID_POST7_ARCH, 0x2); break;
                    case id::specific_arch::ARMv5:    write_cp15(id::cp::CP15_R0_ID_POST7_ARCH, 0x3); break; // obsolete
                    case id::specific_arch::ARMv5T:   write_cp15(id::cp::CP15_R0_ID_POST7_ARCH, 0x4); break;
                    case id::specific_arch::ARMv5TE:  write_cp15(id::cp::CP15_R0_ID_POST7_ARCH, 0x5); break;
                    case id::specific_arch::ARMv5TEJ: write_cp15(id::cp::CP15_R0_ID_POST7_ARCH, 0x6); break;
                    case id::specific_arch::ARMv6:    write_cp15(id::cp::CP15_R0_ID_POST7_ARCH, 0x7); break;
                    // https://en.wikipedia.org/wiki/Comparison_of_ARM_processors
                    default: write_cp15(id::cp::CP15_R0_ID_POST7_ARCH, 0xF); // defined by CPUID scheme, TODO: research wtf this actually is
                }

                // variant (post-ARM7 specific)
                write_cp15(id::cp::CP15_R0_ID_POST7_VARIANT, settings.variant)
            }

            // implementor
            // source: https://developer.arm.com/documentation/ddi0406/b/System-Level-Architecture/Virtual-Memory-System-Architecture--VMSA-/CP15-registers-for-a-VMSA-implementation/c0--Main-ID-Register--MIDR-?lang=en
            switch (settings.implementor) {
                case id::implementor::ARM:      write_cp15(id::cp::CP15_R0_ID_IMPLEMENTOR, 0x41); break; // A
                case id::implementor::BRCM:     write_cp15(id::cp::CP15_R0_ID_IMPLEMENTOR, 0x42); break; // B
                case id::implementor::DEC:      write_cp15(id::cp::CP15_R0_ID_IMPLEMENTOR, 0x44); break; // D
                case id::implementor::MOTOROLA: write_cp15(id::cp::CP15_R0_ID_IMPLEMENTOR, 0x4D); break; // M
                case id::implementor::QUALCOMM: write_cp15(id::cp::CP15_R0_ID_IMPLEMENTOR, 0x51); break; // Q
                case id::implementor::MARVELL:  write_cp15(id::cp::CP15_R0_ID_IMPLEMENTOR, 0x56); break; // V
                case id::implementor::INTEL:    write_cp15(id::cp::CP15_R0_ID_IMPLEMENTOR, 0x69); break; // i
                case id::implementor::CHARM:    write_cp15(id::cp::CP15_R0_ID_IMPLEMENTOR, 0x43); break; // C (custom)
            }

            // primary part number
            write_cp15(id::cp::CP15_R0_ID_PPN, settings.ppn);
        }

        // last minute CPU checks just in case (TODO)

    }


    // TODO (B2-9)
    void setup_R0_cache() {
        const bool unified = settings.has_unified_cache;
        const bool separate = settings.has_separate_cache;

        if (unified) {
            write_cp15(id::cp::CP15_R0_CACHE_S, false);
        } else if (separate) {
            write_cp15(id::cp::CP15_R0_CACHE_S, true);
        } else {
            // TODO error
        }
    }


    void setup_R1_CONTROL() {
        // M
        write_cp15(id::cp::CP15_R1_M, settings.is_mmu_enabled);

        // A
        write_cp15(id::cp::CP15_R1_A, settings.has_alignment_fault_checking);

        // C
        if (settings.has_cache) {
            if (settings.cache_cannot_disable) {
                write_cp15(id::cp::CP15_R1_C, true);
            } else if (settings.has_unified_cache) {
                write_cp15(id::cp::CP15_R1_C, true);
            } else if (settings.has_separate_data_cache && settings.has_separate_cache) {
                write_cp15(id::cp::CP15_R1_C, true);
            } else {
                write_cp15(id::cp::CP15_R1_C, false); // maybe, idk
                // error TODO
            }
        } else {
            write_cp15(id::cp::CP15_R1_C, false); // no cache present
        }

        // W
        if (settings.has_write_buffer) {
            write_cp15(id::cp::CP15_R1_W, true);
        } else {
            write_cp15(id::cp::CP15_R1_W, false); // no write buffer present
        }

        // P
        if (settings.no_26_bits || settings.backwards_compat_support_26_bits) {
            write_cp15(id::cp::CP15_R1_P, true);
        } else if (settings.only_26_bits) {
            write_cp15(id::cp::CP15_R1_P, false);
        } else {
            // TODO dev error config
        }

        // D
        if (settings.no_26_bits || settings.backwards_compat_support_26_bits) {
            write_cp15(id::cp::CP15_R1_D, true);
        } else if (settings.only_26_bits) {
            write_cp15(id::cp::CP15_R1_D, false);
        } else {
            // TODO dev error config
        }

        // L
        if (settings.is_abort_model_early) {
            write_cp15(id::cp::CP15_R1_L, false);
        } else if (settings.is_abort_model_late) {
            write_cp15(id::cp::CP15_R1_L, true);
        } else {
            // TODO dev error config
        }

        // B
        if (settings.is_little_endian) {
            write_cp15(id::cp::CP15_R1_B, false);
        } else if (settings.is_big_endian) {
            write_cp15(id::cp::CP15_R1_B, true);
        } else {
            // TODO dev error config
        }


        // TODO: make the write ignore mechanisms based on the flags at page B2-14
        
    }


};



/*
0b00000 to 0b01010UNPREDICTABLE-

auto get_size = [](const u8 raw_size_bits) -> u64 {
    case 0b01011: return std::pow(2, 12); // 4KB
    case 0b01100: return std::pow(2, 13); // 8KB
    case 0b01101: return std::pow(2, 14); // 16KB
    case 0b01110: return std::pow(2, 15); // 32KB
    case 0b01111: return std::pow(2, 16); // 64KB
    case 0b10000: return std::pow(2, 17); // 128KB
    case 0b10001: return std::pow(2, 18); // 256KB
    case 0b10010: return std::pow(2, 19); // 512KB
    case 0b10011: return std::pow(2, 20); // 1MB
    case 0b10100: return std::pow(2, 21); // 2MB
    case 0b10101: return std::pow(2, 22); // 4MB
    case 0b10110: return std::pow(2, 23); // 8MB
    case 0b10111: return std::pow(2, 24); // 16MB
    case 0b11000: return std::pow(2, 25); // 32MB
    case 0b11001: return std::pow(2, 26); // 64MB
    case 0b11010: return std::pow(2, 27); // 128MB
    case 0b11011: return std::pow(2, 28); // 256MB
    case 0b11100: return std::pow(2, 29); // 512MB
    case 0b11101: return std::pow(2, 30); // 1GB
    case 0b11110: return std::pow(2, 31); // 2GB
    case 0b11111: return std::pow(2, 32); // 4GB
};

Bit[12] must be zero
Bits[13:12] must be zero
Bits[14:12] must be zero
Bits[15:12] must be zero
Bits[16:12] must be zero
Bits[17:12] must be zero
Bits[18:12] must be zero
Bits[19:12] must be zero
Bits[20:12] must be zero
Bits[21:12] must be zero
Bits[22:12] must be zero
Bits[23:12] must be zero
Bits[24:12] must be zero
Bits[25:12] must be zero
Bits[26:12] must be zero
Bits[27:12] must be zero
Bits[28:12] must be zero
Bits[29:12] must be zero
Bits[30:12] must be zero
Bits[31:12] must be zero
*/




// NOTES:
/*
MRC p15,0,<Rt>,c0,c0,0    ; Read CP15 Main ID Register
MRC p15,0,<Rt>,c0,c0,1    ; Read CP15 Cache Type Register
*/