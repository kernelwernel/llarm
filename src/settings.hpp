#include "types.hpp"

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
    u8 version; // (1-9)
    u64 clock_speed_mhz; 
    u64 memsize;
    std::string cpu_model_name;
}




/*
 * https://en.wikipedia.org/wiki/List_of_ARM_processors
 * 
 * product family: ARM10E
 * ARM architecture: ARMv5TEJ
 * processor: ARM1026EJ-S
 * features: Thumb, Jazelle DBX, enhanced DSP instructions, (VFP)
 * cache/memory: Variable, MMU or MPU 
 */