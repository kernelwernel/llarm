#pragma once

#include "id.hpp"
#include "utility.hpp"
#include "constants.hpp"

#include "shared/types.hpp"

struct SETTINGS {
    bool is_thumb_enabled;
    bool is_arm_enabled;
    bool is_jazelle_enabled;
    bool is_enhanced_DSP_enabled;
    bool is_mpu_enabled; // not to be confused with both
    bool is_mmu_enabled; // not to be confused with both
    /**/ bool is_fcse_enabled;
    bool has_coprocessor;
    /**/ bool has_cache;
    /**/ bool cache_cannot_disable;
    /**/ bool has_unified_cache;
    /**/ bool has_separate_cache; // should be enabled if either 2 caches below are enabled 
    /**/ bool has_separate_inst_cache;
    /**/ bool has_separate_data_cache;
    /**/ bool instruction_cache_cannot_disable;
    /**/ bool data_cache_cannot_disable;
    /**/ bool has_alignment_fault_checking;
    /**/ bool has_write_buffer;
    /**/ bool write_buffer_cannot_disable;
    bool backwards_compat_support_26_bits; // "all non-T variants of ARM architecture version 4 and above can optionally implement the 26-bit address space." (A8-2)
    bool only_26_bits; // ARMv1, ARMv2, and ARMv2a
    bool no_26_bits; // ARMv3G
    /**/ bool no_clock_constraint; // basically means it'll execute as fast as the host machine can run without clock delays for accuracy reasons
    /**/ bool is_abort_model_early;
    /**/ bool is_abort_model_late;
    bool is_little_endian;
    bool is_big_endian;
    bool only_little_endian; // TODO
    bool only_big_endian; // TODO
    bool has_system_protection_bit; // disabled if no MMU
    bool has_rom_protection_bit; // disabled if no MMU
    bool has_F_bit_enabled_cp15; // implementation defined
    bool has_branch_prediction;
    bool branch_prediction_cannot_disable;
    bool has_high_vectors;
    /**/ bool has_normal_cache_strategy;
    /**/ bool has_predictable_cache_strategy;
    /**/ bool is_L4_bit_enabled_cp15;
    bool has_debug_hardware;
    bool anti_emulation_detection;
    bool is_vfp_enabled;
    bool is_vfp_double_precision_enabled;
    bool fresh_system;

    // /**/ = "not sure what to do with this, todo"


    // NOTE: MAKE SURE ALL OF THESE MATCH TO THE M BIT (B2-11)
    /**/ u32 unified_cache_size; // make sure it matches with setup_R0_cache()'s list of supported sizes
    /**/ u32 data_cache_size; // both should be the same if unified
    /**/ u32 instruction_cache_size;  // both should be the same if unified
    /**/ u8 data_cache_line_length_bytes; // in 8-64 bytes for all 3
    /**/ u8 instruction_cache_line_length_bytes; // in 8-64 bytes for all 3
    /**/ u8 data_cache_assoc_way; 
    /**/ u8 instruction_cache_assoc_way; 
    /**/ u8 cache_ctype_field; // 0b0000, 0b0001, 0b0010, 0b0110, 0b0111 are supported

    /**/ u8 vfp_version;
    u8 thumb_version; // either 1 or 2, 0 if not supported
    /**/ u8 core_count;
    /**/ u16 clock_speed_mhz; // 0 will mean no clock speed constraints 
    /**/ u64 memsize;
    id::arch arch;
    /**/ id::specific_arch specific_arch;
    id::product_family product_family;
    id::implementor implementor;
    u8 custom_implementor_char;
    id::processor processor;
    u8 variant; // cpu variant, implementation defined
    u16 ppn; // primary part number, implementation defined
    u8 revision; // implementation defined



    SETTINGS default_settings() {
        SETTINGS tmp;

        tmp.is_thumb_enabled = true;
        tmp.is_arm_enabled = true;
        tmp.is_jazelle_enabled = true;
        tmp.is_enhanced_DSP_enabled = true;
        tmp.no_26_bits = true;
        tmp.no_clock_constraint = true;
        tmp.is_little_endian = true;
        tmp.is_big_endian = true;
        tmp.only_big_endian = false;
        tmp.thumb_version = 1;
        tmp.core_count = 1;
        tmp.memsize = util::get_kb(32);
        tmp.arch = id::arch::ARMv4;
        tmp.specific_arch = id::specific_arch::ARMv4T;
        tmp.product_family = id::product_family::ARM7T;
        tmp.processor = id::processor::ARM7TDMI_S;

        tmp.sanitize();

        return tmp;
    }


    void sanitize() {
        // only jazelle 
        if (
            (is_thumb_enabled == false) &&
            (is_arm_enabled == false) &&
            (is_jazelle_enabled == true)
        ) {
            
        }

        if (
            (is_mpu_enabled == true) &&
            (is_mmu_enabled == true)
        ) {

        }

        // i'm not sure if enabling FCSE while MMU or MPU is active is valid, research more

        if (
            (backwards_compat_support_26_bits && only_26_bits) || 
            (backwards_compat_support_26_bits && no_26_bits) || 
            (only_26_bits && no_26_bits)
        ) {
            // only one of them should be enabled, can't have more than 2
        }

        if ((backwards_compat_support_26_bits || only_26_bits || no_26_bits) == false) {
            // at least one should be enabled
        }

        if (
            (is_little_endian && only_big_endian) ||
            (is_big_endian && only_little_endian)
        ) {
            // mismatched endianness constraints
        }

        if (
            (is_mmu_enabled && has_system_protection_bit) ||
            (is_mmu_enabled && has_rom_protection_bit)
        ) {
            // system or rom protection settings shouldn't be enabled without an MMU
        }

        if (
            (is_mpu_enabled && has_system_protection_bit) ||
            (is_mpu_enabled && has_rom_protection_bit)
        ) {
            // system or rom protection settings shouldn't be enabled without an MPU
        }

        if (    
            (has_branch_prediction == false) &&
            (branch_prediction_cannot_disable == true)
        ) {

        }

        if (
            (is_vfp_enabled == false) && 
            (is_vfp_double_precision_enabled == true)
        ) {

        }

        if (
            (thumb_version == 0) && 
            (is_thumb_enabled == true)
        ) {
            // thumb must have a valid version specified
        }

        if (
            (!((thumb_version == 1) || (thumb_version == 2))) &&
            (is_thumb_enabled == true)
        ) {
            // thumb must have a valid version specified
        }

        if (
            ((thumb_version == 1) || (thumb_version == 2)) &&
            (is_thumb_enabled == false)
        ) {
            // thumb setting must be enabled
        }

        if (util::simplify_arch_version(specific_arch) == arch) {
            // the specific arch does not match with the base arch
        }

        if (core_count == 0) {

        }


        // all of the checks above should mostly just set a default correct value instead of crashing completely
    }


    SETTINGS() :
        is_thumb_enabled(false),
        is_arm_enabled(false),
        is_jazelle_enabled(false),
        is_enhanced_DSP_enabled(false),
        is_mpu_enabled(false),
        is_mmu_enabled(false),
        is_fcse_enabled(false),
        has_coprocessor(false),
        has_cache(false),
        cache_cannot_disable(false),
        has_unified_cache(false),
        has_separate_cache(false),
        has_separate_inst_cache(false),
        has_separate_data_cache(false),
        instruction_cache_cannot_disable(false),
        data_cache_cannot_disable(false),
        has_alignment_fault_checking(false),
        has_write_buffer(false),
        write_buffer_cannot_disable(false),
        backwards_compat_support_26_bits(false),
        only_26_bits(false),
        no_26_bits(false),
        no_clock_constraint(false),
        is_abort_model_early(false),
        is_abort_model_late(false),
        is_little_endian(false),
        is_big_endian(false),
        only_little_endian(false),
        only_big_endian(false),
        has_system_protection_bit(false),
        has_rom_protection_bit(false),
        has_F_bit_enabled_cp15(false),
        has_branch_prediction(false),
        branch_prediction_cannot_disable(false),
        has_high_vectors(false),
        has_normal_cache_strategy(false),
        has_predictable_cache_strategy(false),
        is_L4_bit_enabled_cp15(false),
        has_debug_hardware(false),
        anti_emulation_detection(false),
        is_vfp_enabled(false),
        is_vfp_double_precision_enabled(false),
        fresh_system(false),

        unified_cache_size(0),
        data_cache_size(0), 
        instruction_cache_size(0),
        data_cache_line_length_bytes(0),
        instruction_cache_line_length_bytes(0),
        data_cache_assoc_way(0), 
        instruction_cache_assoc_way(0), 
        cache_ctype_field(0),

        vfp_version(0),
        thumb_version(0),
        core_count(0),
        clock_speed_mhz(0),
        memsize(0),
        arch(id::arch::UNKNOWN),
        specific_arch(id::specific_arch::UNKNOWN),
        product_family(id::product_family::UNKNOWN),
        implementor(id::implementor::LLARM),
        custom_implementor_char(constants::implementor::LLARM),
        processor(id::processor::UNKNOWN),
        variant(0),
        ppn(0),
        revision(0)
    {

    }
};


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