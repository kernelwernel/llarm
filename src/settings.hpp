#include "types.hpp"
#include "id.hpp"

class SETTINGS {
public:
    bool is_thumb_enabled;
    bool is_arm_enabled;
    bool is_jazelle_enabled;
    bool is_enhanced_DSP_enabled;
    bool is_protection_unit_enabled;
    bool is_mmu_enabled;
    bool is_fcse_enabled;
    bool has_coprocessor;
    bool has_cache;
    u16 clock_speed_mhz; 
    u64 memsize;
    id::base_arch arch;
    id::specific_arch specific_arch;
    id::product_family product_family;
    id::implementor implementor;
    id::processor processor;
    u8 variant; // cpu variant, implementation defined
    u16 ppn; // primary part number, implementation defined
    u8 revision; // implementation defined
}


// MAKE SURE TO DO SANITY CHECKS ON:
// - variant, because the bit sizes may change depending on whether it's an ARM7 or post ARM7 processor and may silently truncate the value as a result
// the PPN, it must be either 0x0 or 0x7 at the top part

/*
 * https://en.wikipedia.org/wiki/List_of_ARM_processors
 * 
 * product family: ARM10E
 * ARM architecture: ARMv5TEJ
 * processor: ARM1026EJ-S
 * features: Thumb, Jazelle DBX, enhanced DSP instructions, (VFP)
 * cache/memory: Variable, MMU or MPU 
 */