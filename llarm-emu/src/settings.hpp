#pragma once

#include "id.hpp"
#include "constants.hpp"
#include "utility.hpp"

#include <llarm/shared/types.hpp>

struct SETTINGS {
    bool is_thumb_enabled = false;
    bool is_arm_enabled = false;
    bool is_jazelle_enabled = false;
    bool is_enhanced_DSP_enabled = false;
    bool is_arch_version_inst_check_enabled = false;
    bool is_mpu_separate = false;
    bool is_mpu_enabled = false; // not to be confused with both
    bool is_mmu_enabled = false; // not to be confused with both
    bool has_tlb = false;
    bool is_tlb_separate = false;
    bool is_tlb_unified = false;
    /**/ bool has_random_replacement_tlb_strategy = false;
    /**/ bool is_fcse_enabled = false;
    bool has_coprocessor = false;
    /**/ bool has_cache = false;
    /**/ bool cache_cannot_disable = false;
    /**/ bool has_unified_cache = false;
    /**/ bool has_separate_cache = false; // should be enabled if either 2 caches below are enabled
    /**/ bool has_separate_inst_cache = false;
    /**/ bool has_separate_data_cache = false;
    /**/ bool instruction_cache_cannot_disable = false;
    /**/ bool data_cache_cannot_disable = false;
    /**/ bool has_alignment_fault_checking = false;
    /**/ bool has_write_buffer = false;
    /**/ bool write_buffer_cannot_disable = false;
    bool backwards_compat_support_26_bits = false; // "all non-T variants of ARM architecture version 4 and above can optionally implement the 26-bit address space." (A8-2)
    bool only_26_bits = false; // ARMv1, ARMv2, and ARMv2a
    bool no_26_bits = false; // ARMv3G
    /**/ bool no_clock_constraint = false; // basically means it'll execute as fast as the host machine can run without clock delays for accuracy reasons
    /**/ bool is_abort_model_early = false;
    /**/ bool is_abort_model_late = false;
    bool is_little_endian = false;
    bool is_big_endian = false;
    bool only_little_endian = false; // TODO
    bool only_big_endian = false; // TODO
    bool has_system_protection_bit = false; // disabled if no MMU
    bool has_rom_protection_bit = false; // disabled if no MMU
    bool has_F_bit_enabled_cp15 = false; // implementation defined
    bool has_branch_prediction = false;
    bool branch_prediction_cannot_disable = false;
    bool has_high_vectors = false;
    /**/ bool has_random_replacement_cache_strategy = false;
    /**/ bool has_round_robin_replacement_cache_strategy = false;
    /**/ bool is_L4_bit_enabled_cp15 = false;
    bool has_debug_hardware = false;
    bool anti_emulation_detection = false;
    bool is_vfp_enabled = false;
    bool is_vfp_single_precision_enabled = false;
    bool is_vfp_double_precision_enabled = false;
    bool is_multiply_enabled = false;
    bool fresh_system = false;
    bool has_vic = false;

    // /**/ = "not sure what to do with this, todo"


    // NOTE: MAKE SURE ALL OF THESE MATCH TO THE M BIT (B2-11)
    /**/ u32 unified_cache_size = 0; // make sure it matches with setup_R0_cache()'s list of supported sizes
    /**/ u32 data_cache_size = 0; // both should be the same if unified
    /**/ u32 instruction_cache_size = 0;  // both should be the same if unified
    /**/ u8 data_cache_line_length_bytes = 0; // in 8-64 bytes for all 3
    /**/ u8 instruction_cache_line_length_bytes = 0; // in 8-64 bytes for all 3
    /**/ u8 data_cache_assoc_way = 0;
    /**/ u8 instruction_cache_assoc_way = 0;
    /**/ u8 cache_ctype_field = 0; // 0b0000, 0b0001, 0b0010, 0b0110, 0b0111 are supported
    /**/ id::cache_type cache_type = id::cache_type::UNKNOWN;

    /**/ u16 unified_tlb_table_size = 0;
    /**/ u16 inst_tlb_table_size = 0;
    /**/ u16 data_tlb_table_size = 0;
    /**/ id::tlb_type tlb_type = id::tlb_type::UNKNOWN;

    id::vic_type vic_type = id::vic_type::NONE;
    /**/ u32 vic_base = 0; // PL190/PL192: register base address

    /**/ id::vfp_version vfp_version = id::vfp_version::UNKNOWN;
    /**/ id::vfp_format vfp_format = id::vfp_format::NON_STANDARD;
    id::thumb_version thumb_version = id::thumb_version::NO_THUMB; // either 1 or 2, 0 if not supported
    /**/ u8 core_count = 0;
    /**/ u16 clock_speed_mhz = 0; // 0 will mean no clock speed constraints
    /**/ u64 memsize = 0;
    id::arch arch = id::arch::UNKNOWN;
    /**/ id::specific_arch specific_arch = id::specific_arch::UNKNOWN;
    id::product_family product_family = id::product_family::UNKNOWN;
    id::implementor implementor = id::implementor::LLARM;
    u8 custom_implementor_char = constants::implementor::LLARM;
    id::processor processor = id::processor::UNKNOWN;
    u8 variant = 0; // cpu variant, implementation defined
    u16 ppn = 0; // primary part number, implementation defined
    u8 revision = 0; // implementation defined
    u8 vfp_variant = 0;
    u16 vfp_ppn = 0;
    u8 vfp_revision = 0;
    u8 vfp_load_multiple_value = 0;
    u64 tlb_seed = 0;

    constexpr void sanitize() const {
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

        if (is_tlb_separate && is_tlb_unified) {

        }

        if (has_tlb && (is_tlb_separate == false && is_tlb_unified == false)) {

        }

        if (is_mmu_enabled && (is_tlb_separate == false && is_tlb_unified == false)) {
            
        }

        // i'm not sure if enabling FCSE while MMU or MPU is active is valid, research more TODO

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
            (thumb_version == id::thumb_version::NO_THUMB) && 
            (is_thumb_enabled == true)
        ) {
            // thumb must have a valid version specified
        }

        if (
            (!((thumb_version == id::thumb_version::THUMB1) || (thumb_version == id::thumb_version::THUMB2))) &&
            (is_thumb_enabled == true)
        ) {
            // thumb must have a valid version specified
        }

        if (
            ((thumb_version == id::thumb_version::THUMB1) || (thumb_version == id::thumb_version::THUMB2)) &&
            (is_thumb_enabled == false)
        ) {
            // thumb setting must be enabled
        }

        if (util::simplify_arch_version(specific_arch) == arch) {
            // the specific arch does not match with the base arch
        }

        if (core_count == 0) {
            // core count must be at least 1
        }

        if (arch == id::arch::ARMv2 && is_multiply_enabled) {
            // ARMv2 has no support for multiplications
        }

        if (has_vic && vic_type != id::vic_type::NONE) {
            
        }

        if (has_cache && cache_type == id::cache_type::UNKNOWN) {

        }

        // all of the checks above should mostly just set a default correct value instead of crashing completely
    }

    constexpr SETTINGS() = default;
};


constexpr SETTINGS default_settings() {
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
    tmp.is_multiply_enabled = true;
    tmp.is_abort_model_early = true;
    tmp.thumb_version = id::thumb_version::THUMB1;
    tmp.core_count = 1;
    tmp.memsize = util::get_kb(32);
    tmp.arch = id::arch::ARMv4;
    tmp.specific_arch = id::specific_arch::ARMv4T;
    tmp.product_family = id::product_family::ARM7T;
    tmp.processor = id::processor::ARM7TDMI_S;
    tmp.has_round_robin_replacement_cache_strategy = true;
    tmp.ppn = 0x7;

    tmp.sanitize();

    return tmp;
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