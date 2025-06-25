#include "id.hpp"
#include "utility.hpp"

#include "settings.hpp"

void SETTINGS::sanitize() {
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

    if (is_mmu_tlb_separate && is_mmu_tlb_unified) {

    }

    if (is_mmu_enabled && (is_mmu_tlb_separate == false && is_mmu_tlb_unified == false)) {
        
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

    // all of the checks above should mostly just set a default correct value instead of crashing completely
}


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
    tmp.is_multiply_enabled = true;
    tmp.thumb_version = id::thumb_version::THUMB1;
    tmp.core_count = 1;
    tmp.memsize = util::get_kb(32);
    tmp.arch = id::arch::ARMv4;
    tmp.specific_arch = id::specific_arch::ARMv4T;
    tmp.product_family = id::product_family::ARM7T;
    tmp.processor = id::processor::ARM7TDMI_S;

    tmp.sanitize();

    return tmp;
}