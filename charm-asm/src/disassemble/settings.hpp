#pragma once

#include "shared/types.hpp"

struct SETTINGS {


    u8 thumb_version;
    bool is_thumb_2;
    bool is_thumb;
    u8 base_arch;



    SETTINGS default_settings() {
        SETTINGS tmp;

        //tmp.is_thumb_enabled = true;
        //tmp.is_arm_enabled = true;
        //tmp.is_jazelle_enabled = true;
        //tmp.is_enhanced_DSP_enabled = true;
        //tmp.no_26_bits = true;
        //tmp.no_clock_constraint = true;
        //tmp.is_little_endian = true;
        //tmp.is_big_endian = true;
        //tmp.only_big_endian = false;
        //tmp.thumb_version = 1;
        //tmp.core_count = 1;
        //tmp.memsize = util::get_kb(32);
        //tmp.arch = id::arch::ARMv4;
        //tmp.specific_arch = id::specific_arch::ARMv4T;
        //tmp.product_family = id::product_family::ARM7T;
        //tmp.processor = id::processor::ARM7TDMI_S;

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
        implementor(id::implementor::CHARM),
        custom_implementor_char(constants::implementor::CHARM),
        processor(id::processor::UNKNOWN),
        variant(0),
        ppn(0),
        revision(0)
    {

    }
};