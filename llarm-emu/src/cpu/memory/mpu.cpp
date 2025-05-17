#pragma once

#include "shared/types.hpp"
#include "../../utility.hpp"
#include "../core/globals.hpp"
#include "../coprocessor/coprocessor.hpp"
#include "structure.hpp"
#include "mpu.hpp"

u64 MPU::get_size(const u8 raw_size_bits) {
    switch (raw_size_bits) {
        case 0b01011: return util::get_kb(4); // 4KB
        case 0b01100: return util::get_kb(8); // 8KB
        case 0b01101: return util::get_kb(16); // 16KB
        case 0b01110: return util::get_kb(32); // 32KB
        case 0b01111: return util::get_kb(64); // 64KB
        case 0b10000: return util::get_kb(128); // 128KB
        case 0b10001: return util::get_kb(256); // 256KB
        case 0b10010: return util::get_kb(512); // 512KB
        case 0b10011: return util::get_mb(1); // 1MB
        case 0b10100: return util::get_mb(2); // 2MB
        case 0b10101: return util::get_mb(4); // 4MB
        case 0b10110: return util::get_mb(8); // 8MB
        case 0b10111: return util::get_mb(16); // 16MB
        case 0b11000: return util::get_mb(32); // 32MB
        case 0b11001: return util::get_mb(64); // 64MB
        case 0b11010: return util::get_mb(128); // 128MB
        case 0b11011: return util::get_mb(256); // 256MB
        case 0b11100: return util::get_mb(512); // 512MB
        case 0b11101: return util::get_gb(1); // 1GB
        case 0b11110: return util::get_gb(2); // 2GB
        case 0b11111: return util::get_gb(4); // 4GB
        default: return 0; // idk what to put here, research the docs TODO
    }
};


id::access_perm MPU::get_access_perm(const u8 AP) {
    if (globals.is_privileged) {
        if (AP == 0b00) {
            return id::access_perm::NO_ACCESS;
        }

        return id::access_perm::READ_WRITE;
    } else {
        switch (AP) {
            case 0b00: return id::access_perm::NO_ACCESS;
            case 0b01: return id::access_perm::NO_ACCESS;
            case 0b10: return id::access_perm::READ_ONLY;
            case 0b11: return id::access_perm::READ_WRITE;
        }
    }

    shared::out::error("something went horribly wrong here..."); // TODO
}

bool MPU::is_mpu_enabled() {
    return (
        (coprocessor.read(id::cp::CP15_R1_M) == true) &&
        (settings.is_mpu_enabled)
    );
}


memory_struct<> MPU::is_access_valid(const u32 address, const id::access_type access_type) {
    memory_struct<> data = {};

    // these are irrelevant
    data.value = 0;
    data.new_address = address;

    if (globals.mpu_address_change) {
        region_0_start = coprocessor.read(id::cp::CP15_R6_PU_0_BASE_ADDRESS);
        region_1_start = coprocessor.read(id::cp::CP15_R6_PU_1_BASE_ADDRESS);
        region_2_start = coprocessor.read(id::cp::CP15_R6_PU_2_BASE_ADDRESS);
        region_3_start = coprocessor.read(id::cp::CP15_R6_PU_3_BASE_ADDRESS);
        region_4_start = coprocessor.read(id::cp::CP15_R6_PU_4_BASE_ADDRESS);
        region_5_start = coprocessor.read(id::cp::CP15_R6_PU_5_BASE_ADDRESS);
        region_6_start = coprocessor.read(id::cp::CP15_R6_PU_6_BASE_ADDRESS);
        region_7_start = coprocessor.read(id::cp::CP15_R6_PU_7_BASE_ADDRESS);
        region_0_end = region_0_start + get_size(coprocessor.read(id::cp::CP15_R6_PU_0_SIZE));
        region_1_end = region_1_start + get_size(coprocessor.read(id::cp::CP15_R6_PU_1_SIZE));
        region_2_end = region_2_start + get_size(coprocessor.read(id::cp::CP15_R6_PU_2_SIZE));
        region_3_end = region_3_start + get_size(coprocessor.read(id::cp::CP15_R6_PU_3_SIZE));
        region_4_end = region_4_start + get_size(coprocessor.read(id::cp::CP15_R6_PU_4_SIZE));
        region_5_end = region_5_start + get_size(coprocessor.read(id::cp::CP15_R6_PU_5_SIZE));
        region_6_end = region_6_start + get_size(coprocessor.read(id::cp::CP15_R6_PU_6_SIZE));
        region_7_end = region_7_start + get_size(coprocessor.read(id::cp::CP15_R6_PU_7_SIZE));
        region_0_enabled = coprocessor.read(id::cp::CP15_R6_PU_0_E);
        region_1_enabled = coprocessor.read(id::cp::CP15_R6_PU_1_E);
        region_2_enabled = coprocessor.read(id::cp::CP15_R6_PU_2_E);
        region_3_enabled = coprocessor.read(id::cp::CP15_R6_PU_3_E);
        region_4_enabled = coprocessor.read(id::cp::CP15_R6_PU_4_E);
        region_5_enabled = coprocessor.read(id::cp::CP15_R6_PU_5_E);
        region_6_enabled = coprocessor.read(id::cp::CP15_R6_PU_6_E);
        region_7_enabled = coprocessor.read(id::cp::CP15_R6_PU_7_E);

        globals.mpu_address_change = false;
    }

    id::cp AP_region_id;

    if      (address >= region_7_start && address <= region_7_end && region_7_enabled) { AP_region_id = id::cp::CP15_R5_PU_AP7; } 
    else if (address >= region_6_start && address <= region_6_end && region_6_enabled) { AP_region_id = id::cp::CP15_R5_PU_AP6; }
    else if (address >= region_5_start && address <= region_5_end && region_5_enabled) { AP_region_id = id::cp::CP15_R5_PU_AP5; }
    else if (address >= region_4_start && address <= region_4_end && region_4_enabled) { AP_region_id = id::cp::CP15_R5_PU_AP4; }
    else if (address >= region_3_start && address <= region_3_end && region_3_enabled) { AP_region_id = id::cp::CP15_R5_PU_AP3; }
    else if (address >= region_2_start && address <= region_2_end && region_2_enabled) { AP_region_id = id::cp::CP15_R5_PU_AP2; }
    else if (address >= region_1_start && address <= region_1_end && region_1_enabled) { AP_region_id = id::cp::CP15_R5_PU_AP1; }
    else if (address >= region_0_start && address <= region_0_end && region_0_enabled) { AP_region_id = id::cp::CP15_R5_PU_AP0; }
    else {
        // at this point, an abort is performed 
        data.has_failed = true;

        if (access_type == id::access_type::INSTRUCTION_FETCH) {
            data.abort_code = id::aborts::PREFETCH_ABORT;
        } else {
            data.abort_code = id::aborts::ABORT;
        }

        return data;
    }

    const u8 AP_bits = coprocessor.read(AP_region_id);
    const id::access_perm AP_id = get_access_perm(AP_bits);

    switch (AP_id) {
        case id::access_perm::READ_WRITE: 
            data.has_failed = (!(
                (access_type == id::access_type::INSTRUCTION_FETCH) ||
                (access_type == id::access_type::READ_WRITE) ||
                (access_type == id::access_type::READ) ||
                (access_type == id::access_type::WRITE)
            ));
            break;

        case id::access_perm::READ_ONLY:
            data.has_failed = (!(
                (access_type == id::access_type::INSTRUCTION_FETCH) ||
                (access_type == id::access_type::READ_WRITE) || // this overlaps with the read permission, so this is valid
                (access_type == id::access_type::READ)
            ));
            break;

        case id::access_perm::UNPREDICTABLE: // TODO add an unpredictable log here
        case id::access_perm::NO_ACCESS: 
            data.has_failed = true;
            if (access_type == id::access_type::INSTRUCTION_FETCH) {
                data.abort_code = id::aborts::PREFETCH_ABORT;
            } else {
                data.abort_code = id::aborts::ABORT;
            }
            return data;
    }

    data.abort_code = id::aborts::NO_ABORT;

    return data;
}


memory_struct<> MPU::write_manager(const u32 address, const u8 access_size) {
    memory_struct<> data = {};

    const memory_struct<> mpu_access = is_access_valid(address, id::access_type::WRITE);

    if (mpu_access.has_failed) {
        data.has_failed = true;
        data.abort_code = id::aborts::ABORT;
        data.value = 0;
        data.new_address = address;
    } else {
        data.has_failed = false;
        data.abort_code = id::aborts::NO_ABORT;
        data.value = 0;
        data.new_address = address;
    }

    return data;
}


// try to scan from most priority to least, rather than upwards

// if the access is outside of any region, do an abort (doesn't say which tho) 

// alignment checking is also allowed, implement this TODO

// extra thing: region 0 could be set to 4GB, as a backup if all other regions fail

void MPU::setup_R6_PU() {
    // The starting address of a region must be a multiple 
    // of its size. For example, a 4KB region (size 0x1000)
    // can start at address 0x12345000, but an 8KB region 
    // (size 0x2000) or larger can not.

    // 

    //if ((address % size) != 0) {
        // unpredictable

    //}

    // Some implementations (typically those with separate 
    // instruction and data caches) provide two separate sets
    // of eight protection regions, with one set being used 
    // for instruction fetches and the other set for data accesses.

    // if the address doesn't lie in any protection region, a memory access abort is made 
}

void MPU::reset() {
    region_0_start = 0;
    region_1_start = 0;
    region_2_start = 0;
    region_3_start = 0;
    region_4_start = 0;
    region_5_start = 0;
    region_6_start = 0;
    region_7_start = 0;
    region_0_end = 0;
    region_1_end = 0;
    region_2_end = 0;
    region_3_end = 0;
    region_4_end = 0;
    region_5_end = 0;
    region_6_end = 0;
    region_7_end = 0;
    region_0_enabled = false;
    region_1_enabled = false;
    region_2_enabled = false;
    region_3_enabled = false;
    region_4_enabled = false;
    region_5_enabled = false;
    region_6_enabled = false;
    region_7_enabled = false;

    coprocessor.write(id::cp::CP15_R6_PU_0, 0);
    coprocessor.write(id::cp::CP15_R6_PU_1, 0);
    coprocessor.write(id::cp::CP15_R6_PU_2, 0);
    coprocessor.write(id::cp::CP15_R6_PU_3, 0);
    coprocessor.write(id::cp::CP15_R6_PU_4, 0);
    coprocessor.write(id::cp::CP15_R6_PU_5, 0);
    coprocessor.write(id::cp::CP15_R6_PU_6, 0);
    coprocessor.write(id::cp::CP15_R6_PU_7, 0);
}