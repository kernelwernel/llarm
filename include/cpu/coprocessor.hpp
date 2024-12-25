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
    u32 R8_MMU = 0; // TLB control
    u32 R8_PU  = 0; // reserved

    // Cache and write buffer 
    u32 R9_CACHE = 0; // cache lockdown

    // Memory protection and control
    u32 R10_MMU = 0; // TLB lockdown
    u32 R10_PU  = 0; // reserved
    
    u32 R11_RESERVED = 0;

    u32 R12_RESERVED = 0;

    // Process ID
    u32 R13_ID = 0; // process ID

    u32 R14_RESERVED = 0;

    u32 R15_IMPL = 0; // implementation defined, not important


public:
    u32 read(const id::cp15 reg) {
        switch (reg) {
            case id::cp15::R0_ID: return R0_ID;
            case id::cp15::R0_CACHE: return R0_CACHE;
            case id::cp15::R1_CONTROL: return R1_CONTROL;
            case id::cp15::R1_M: return (R1_CONTROL & 1);          // MMU or Protection Unit enable disable
            case id::cp15::R1_A: return (R1_CONTROL & (1 << 1));   // alignment fault checking
            case id::cp15::R1_C: return (R1_CONTROL & (1 << 2));   // unified cache
            case id::cp15::R1_W: return (R1_CONTROL & (1 << 3));   // write buffer
            case id::cp15::R1_P: return (R1_CONTROL & (1 << 4));   // 26-bit backwards-compatibility configurations (PROG32)
            case id::cp15::R1_D: return (R1_CONTROL & (1 << 5));   // 26-bit backwards-compatibility configurations (DATA32)
            case id::cp15::R1_L: return (R1_CONTROL & (1 << 6));   // abort model of the processor
            case id::cp15::R1_B: return (R1_CONTROL & (1 << 7));   // endianness of the memory system
            case id::cp15::R1_S: return (R1_CONTROL & (1 << 8));   // system protection bit
            case id::cp15::R1_R: return (R1_CONTROL & (1 << 9));   // ROM protection bit
            case id::cp15::R1_F: return (R1_CONTROL & (1 << 10));  // IMPLEMENTATION DEFINED
            case id::cp15::R1_Z: return (R1_CONTROL & (1 << 11));  // branch prediction
            case id::cp15::R1_I: return (R1_CONTROL & (1 << 12));  // instruction cache
            case id::cp15::R1_V: return (R1_CONTROL & (1 << 13));  // high vectors
            case id::cp15::R1_RR: return (R1_CONTROL & (1 << 14)); // cache strategy
            case id::cp15::R1_L4: return (R1_CONTROL & (1 << 15)); // ARMv5+ backwards compatibility
            case id::cp15::R2_MMU: return R2_MMU;
            case id::cp15::R2_PU: return R2_PU;
            case id::cp15::R2_PU_C0: return (R2_PU & 1);
            case id::cp15::R2_PU_C1: return (R2_PU & (1 << 1));
            case id::cp15::R2_PU_C2: return (R2_PU & (1 << 2));
            case id::cp15::R2_PU_C3: return (R2_PU & (1 << 3));
            case id::cp15::R2_PU_C4: return (R2_PU & (1 << 4));
            case id::cp15::R2_PU_C5: return (R2_PU & (1 << 5));
            case id::cp15::R2_PU_C6: return (R2_PU & (1 << 6));
            case id::cp15::R2_PU_C7: return (R2_PU & (1 << 7));
            case id::cp15::R3_MMU: return R3_MMU;
            case id::cp15::R3_PU: return R3_PU;
            case id::cp15::R3_PU_B0: return (R3_PU & 1);
            case id::cp15::R3_PU_B1: return (R3_PU & (1 << 1));
            case id::cp15::R3_PU_B2: return (R3_PU & (1 << 2));
            case id::cp15::R3_PU_B3: return (R3_PU & (1 << 3));
            case id::cp15::R3_PU_B4: return (R3_PU & (1 << 4));
            case id::cp15::R3_PU_B5: return (R3_PU & (1 << 5));
            case id::cp15::R3_PU_B6: return (R3_PU & (1 << 6));
            case id::cp15::R3_PU_B7: return (R3_PU & (1 << 7));
            case id::cp15::R4_MMU: return R4_MMU;
            case id::cp15::R4_PU: return R4_PU;
            case id::cp15::R5_MMU: return R5_MMU;
            case id::cp15::R5_PU: return R5_PU;
            case id::cp15::R6_MMU: return R6_MMU;
            case id::cp15::R6_PU: return R6_PU;
            case id::cp15::R7_CACHE: return R7_CACHE;
            case id::cp15::R8_MMU: return R8_MMU;
            case id::cp15::R8_PU: return R8_PU;
            case id::cp15::R9_CACHE: return R9_CACHE;
            case id::cp15::R10_MMU: return R10_MMU;
            case id::cp15::R10_PU: return R10_PU;
            case id::cp15::R11_RESERVED: return R11_RESERVED;
            case id::cp15::R12_RESERVED: return R12_RESERVED;
            case id::cp15::R13_ID: return R13_ID;
            case id::cp15::R14_RESERVED: return R14_RESERVED;
            case id::cp15::R15_IMPL: return R15_IMPL;
        }
    }


    void write(const id::cp15 reg, const u32 value) {
        auto modify_bit = [=](u32 &cp_reg, const u8 position) {
            if (value) {
                cp_reg |= (1U << position);
            } else {
                cp_reg &= ~(1U << position);
            }
            return;
        };

        auto swap_bits = [=](u32 &cp_reg, const u8 index, const u8 width) {
            u32 mask = ((1u << width) - 1) << index;
            cp_reg &= ~mask;
            cp_reg |= (value << index) & mask;
            return;
        };

        switch (reg) {
        R3_MMU,
        R3_PU,
        R3_PU_B0,
        R3_PU_B1,
        R3_PU_B2,
        R3_PU_B3,
        R3_PU_B4,
        R3_PU_B5,
        R3_PU_B6,
        R3_PU_B7,
        R4_MMU,
        R4_PU,
        R5_MMU,
        R5_PU,
        R5_PU_AP0,
        R5_PU_AP1,
        R5_PU_AP2,
        R5_PU_AP3,
        R5_PU_AP4,
        R5_PU_AP5,
        R5_PU_AP6,
        R5_PU_AP7,
        R6_MMU,
        R6_PU,
        R7_CACHE,
        R8_MMU,
        R8_PU,
        R9_CACHE,
        R10_MMU,
        R10_PU,
        R11_RESERVED,
        R12_RESERVED,
        R13_ID,
        R14_RESERVED,
        R15_IMPL

            case id::cp15::R0_ID: R0_ID = value; return;
            case id::cp15::R0_CACHE: R0_CACHE = value; return;
            case id::cp15::R1_CONTROL: R1_CONTROL = value; return;
            case id::cp15::R1_M: 
                if (settings.is_mmu_enabled || settings.is_protection_unit_enabled) {
                    flip(0); 
                }

                return;
            case id::cp15::R1_A:     modify_bit(R1_CONTROL, 1);  return;
            case id::cp15::R1_C:     modify_bit(R1_CONTROL, 2);  return;
            case id::cp15::R1_W:     modify_bit(R1_CONTROL, 3);  return;
            case id::cp15::R1_P:     modify_bit(R1_CONTROL, 4);  return;
            case id::cp15::R1_D:     modify_bit(R1_CONTROL, 5);  return;
            case id::cp15::R1_L:     modify_bit(R1_CONTROL, 6);  return;
            case id::cp15::R1_B:     modify_bit(R1_CONTROL, 7);  return;
            case id::cp15::R1_S:     modify_bit(R1_CONTROL, 8);  return;
            case id::cp15::R1_R:     modify_bit(R1_CONTROL, 9);  return;
            case id::cp15::R1_F:     modify_bit(R1_CONTROL, 10); return;
            case id::cp15::R1_Z:     modify_bit(R1_CONTROL, 11); return;
            case id::cp15::R1_I:     modify_bit(R1_CONTROL, 12); return;
            case id::cp15::R1_V:     modify_bit(R1_CONTROL, 13); return;
            case id::cp15::R1_RR:    modify_bit(R1_CONTROL, 14); return;
            case id::cp15::R1_L4:    modify_bit(R1_CONTROL, 15); return;
            case id::cp15::R2_MMU:   R2_MMU = value; return;
            case id::cp15::R2_PU:    R2_PU = value; return;
            case id::cp15::R2_PU_C0: modify_bit(R2_PU, 0); return;
            case id::cp15::R2_PU_C1: modify_bit(R2_PU, 1); return;
            case id::cp15::R2_PU_C2: modify_bit(R2_PU, 2); return;
            case id::cp15::R2_PU_C3: modify_bit(R2_PU, 3); return;
            case id::cp15::R2_PU_C4: modify_bit(R2_PU, 4); return;
            case id::cp15::R2_PU_C5: modify_bit(R2_PU, 5); return;
            case id::cp15::R2_PU_C6: modify_bit(R2_PU, 6); return;
            case id::cp15::R2_PU_C7: modify_bit(R2_PU, 7); return;

            case id::cp15::R3_PU_B0: modify_bit(R3_PU, 0); return;
            case id::cp15::R3_PU_B1: modify_bit(R3_PU, 1); return;
            case id::cp15::R3_PU_B2: modify_bit(R3_PU, 2); return;
            case id::cp15::R3_PU_B3: modify_bit(R3_PU, 3); return;
            case id::cp15::R3_PU_B4: modify_bit(R3_PU, 4); return;
            case id::cp15::R3_PU_B5: modify_bit(R3_PU, 5); return;
            case id::cp15::R3_PU_B6: modify_bit(R3_PU, 6); return;
            case id::cp15::R3_PU_B7: modify_bit(R3_PU, 7); return;
        }
    }


    void write_control(const id::cp15 reg_bit, const bool value) {
        auto flip = [=](const u8 position) {
            if (value) {
                R1_CONTROL |= (1U << position);
            } else {
                R1_CONTROL &= ~(1U << position);
            }

            return;
        };

        switch (reg_bit) {


        }
    }

    id::memory get_access_perm_type(const id::cp15 region) {
        u8 raw_permission_bits = 0;

        const u32 PU_REG_COPY = read(id::cp15::R5_PU);

        switch (region) {
            case id::cp15::R5_PU_AP0: raw_permission_bits = (PU_REG_COPY & 0b11); break;
            case id::cp15::R5_PU_AP1: raw_permission_bits = (PU_REG_COPY & (0b11 << 2)); break;
            case id::cp15::R5_PU_AP2: raw_permission_bits = (PU_REG_COPY & (0b11 << 4)); break;
            case id::cp15::R5_PU_AP3: raw_permission_bits = (PU_REG_COPY & (0b11 << 6)); break;
            case id::cp15::R5_PU_AP4: raw_permission_bits = (PU_REG_COPY & (0b11 << 8)); break;
            case id::cp15::R5_PU_AP5: raw_permission_bits = (PU_REG_COPY & (0b11 << 10)); break;
            case id::cp15::R5_PU_AP6: raw_permission_bits = (PU_REG_COPY & (0b11 << 12)); break;
            case id::cp15::R5_PU_AP7: raw_permission_bits = (PU_REG_COPY & (0b11 << 14)); break;
        }

        const bool is_priviledged = (reg::read_mode() != id::mode::USER);

        if (is_priviledged) {
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

    COPROCESSOR(memory, settings) : settings(settings) {
        // CP15 setup


        // R1
        
    }


private:



};

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