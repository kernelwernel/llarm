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
    bool cache_cannot_disable;
    bool has_unified_cache;
    bool has_separate_cache; // should be enabled if either 2 caches below are enabled 
    bool has_separate_inst_cache;
    bool has_separate_data_cache;
    bool has_alignment_fault_checking;
    bool has_write_buffer;
    bool write_buffer_cannot_disable;
    bool backwards_compat_support_26_bits;
    bool no_clock_constraint; // basically means it'll execute as fast as the host machine can run without clock delays for accuracy reasons
    u8 thumb_version; // either 1 or 2
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