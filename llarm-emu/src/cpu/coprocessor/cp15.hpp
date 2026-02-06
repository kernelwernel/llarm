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
#include "../memory/tlb.hpp"

#include <llarm/shared/types.hpp>

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
    TLB& tlb;

public:

    u32 R0_ID = 0;    // processor ID 
    u32 R0_CACHE = 0; // cache 

    // control bits 
    u32 R1 = 0;
    
    // MMU: translation table
    // MPU: cachability bits
    u32 R2 = 0;
    
    // MMU: domain access control
    // MPU: bufferability bits
    u32 R3 = 0;
    u32 R3_PU_INST = 0;
    u32 R3_PU_DATA = 0;

    // MMU: reserved
    // MPU: reserved
    u32 R4 = 0;

    // MMU: fault status
    // MPU: access permission bits
    u32 R5 = 0;
    u32 R5_PU_INST = 0;
    u32 R5_PU_DATA = 0;

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

    u32 R6_PU_INST_0 = 0;
    u32 R6_PU_INST_1 = 0;
    u32 R6_PU_INST_2 = 0;
    u32 R6_PU_INST_3 = 0;
    u32 R6_PU_INST_4 = 0;
    u32 R6_PU_INST_5 = 0;
    u32 R6_PU_INST_6 = 0;
    u32 R6_PU_INST_7 = 0;

    u32 R6_PU_DATA_0 = 0;
    u32 R6_PU_DATA_1 = 0;
    u32 R6_PU_DATA_2 = 0;
    u32 R6_PU_DATA_3 = 0;
    u32 R6_PU_DATA_4 = 0;
    u32 R6_PU_DATA_5 = 0;
    u32 R6_PU_DATA_6 = 0;
    u32 R6_PU_DATA_7 = 0;

    // cache/write buffer control
    u32 R7 = 0;

    // MMU: TLB control, this register doesn't really exist since it's write-only (B3-26)
    // MPU: reserved
    u32 R8 = 0;

    // cache lockdown
    u32 R9 = 0;

    // MMU: TLB lockdown
    // MPU: reserved
    u32 R10 = 0;
    u32 R10_INST = 0;
    u32 R10_DATA = 0;

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

public:
    id::cp15 identify_R6(const u8 CRm, const u8 opcode_2);
    id::cp15 identify(const u8 CRn, const u8 CRm, const u8 opcode2);

    u32 read(const id::cp15 reg);

    void force_write(const id::cp15 reg, const u32 value);
    void write(const id::cp15 reg, const u32 value);
    void write(const id::cp15 reg, const u32 value, const u8 opcode_2, const u8 CRm, const u32 data, const bool forced = false);

    void reset();

private:
    void setup_R0_processor_id();

    // TODO (B2-9)
    void setup_R0_cache();

    void setup_R1_control();

public:
    CP15(SETTINGS& settings, GLOBALS& globals, TLB& tlb);
};