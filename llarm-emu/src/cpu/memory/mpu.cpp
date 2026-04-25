#include "../../utility.hpp"
#include "../core/globals.hpp"
#include "../coprocessor/coprocessor.hpp"
#include "structures.hpp"
#include "mpu.hpp"

#include <llarm/shared/out.hpp>
#include <llarm/shared/types.hpp>


u64 MPU::get_size(const u8 raw_size_bits) const {
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


id::access_perm MPU::get_access_perm(const u8 AP) const {
    if (globals.is_privileged) {
        if (AP == 0b00) {
            return id::access_perm::NO_ACCESS;
        }

        return id::access_perm::READ_WRITE;
    }

    switch (AP) {
        case 0b00: return id::access_perm::NO_ACCESS;
        case 0b01: return id::access_perm::NO_ACCESS;
        case 0b10: return id::access_perm::READ_ONLY;
        case 0b11: return id::access_perm::READ_WRITE;
    }

    llarm::out::dev_error("Unknown access permission bits (MPU)");
}

bool MPU::is_mpu_enabled() const {
    return (
        (coprocessor.read(id::cp15::R1_M) == true) &&
        (settings.is_mpu_enabled)
    );
}


MPU::mpu_access_result MPU::check_access(const u32 address, const u8 access_size, const id::access_type access_type) {
    if (globals.mpu_address_change) {
        if (settings.is_mpu_separate) {
            if (globals.mpu_inst_address_change) {
                region_inst_0_start = coprocessor.read(id::cp15::R6_PU_INST_0_BASE_ADDRESS);
                region_inst_1_start = coprocessor.read(id::cp15::R6_PU_INST_1_BASE_ADDRESS);
                region_inst_2_start = coprocessor.read(id::cp15::R6_PU_INST_2_BASE_ADDRESS);
                region_inst_3_start = coprocessor.read(id::cp15::R6_PU_INST_3_BASE_ADDRESS);
                region_inst_4_start = coprocessor.read(id::cp15::R6_PU_INST_4_BASE_ADDRESS);
                region_inst_5_start = coprocessor.read(id::cp15::R6_PU_INST_5_BASE_ADDRESS);
                region_inst_6_start = coprocessor.read(id::cp15::R6_PU_INST_6_BASE_ADDRESS);
                region_inst_7_start = coprocessor.read(id::cp15::R6_PU_INST_7_BASE_ADDRESS);
                region_inst_0_end = region_inst_0_start + static_cast<u32>(get_size(static_cast<u8>(coprocessor.read(id::cp15::R6_PU_INST_0_SIZE))));
                region_inst_1_end = region_inst_1_start + static_cast<u32>(get_size(static_cast<u8>(coprocessor.read(id::cp15::R6_PU_INST_1_SIZE))));
                region_inst_2_end = region_inst_2_start + static_cast<u32>(get_size(static_cast<u8>(coprocessor.read(id::cp15::R6_PU_INST_2_SIZE))));
                region_inst_3_end = region_inst_3_start + static_cast<u32>(get_size(static_cast<u8>(coprocessor.read(id::cp15::R6_PU_INST_3_SIZE))));
                region_inst_4_end = region_inst_4_start + static_cast<u32>(get_size(static_cast<u8>(coprocessor.read(id::cp15::R6_PU_INST_4_SIZE))));
                region_inst_5_end = region_inst_5_start + static_cast<u32>(get_size(static_cast<u8>(coprocessor.read(id::cp15::R6_PU_INST_5_SIZE))));
                region_inst_6_end = region_inst_6_start + static_cast<u32>(get_size(static_cast<u8>(coprocessor.read(id::cp15::R6_PU_INST_6_SIZE))));
                region_inst_7_end = region_inst_7_start + static_cast<u32>(get_size(static_cast<u8>(coprocessor.read(id::cp15::R6_PU_INST_7_SIZE))));
                region_inst_0_enabled = coprocessor.read(id::cp15::R6_PU_INST_0_E);
                region_inst_1_enabled = coprocessor.read(id::cp15::R6_PU_INST_1_E);
                region_inst_2_enabled = coprocessor.read(id::cp15::R6_PU_INST_2_E);
                region_inst_3_enabled = coprocessor.read(id::cp15::R6_PU_INST_3_E);
                region_inst_4_enabled = coprocessor.read(id::cp15::R6_PU_INST_4_E);
                region_inst_5_enabled = coprocessor.read(id::cp15::R6_PU_INST_5_E);
                region_inst_6_enabled = coprocessor.read(id::cp15::R6_PU_INST_6_E);
                region_inst_7_enabled = coprocessor.read(id::cp15::R6_PU_INST_7_E);
            } else {
                region_data_0_start = coprocessor.read(id::cp15::R6_PU_DATA_0_BASE_ADDRESS);
                region_data_1_start = coprocessor.read(id::cp15::R6_PU_DATA_1_BASE_ADDRESS);
                region_data_2_start = coprocessor.read(id::cp15::R6_PU_DATA_2_BASE_ADDRESS);
                region_data_3_start = coprocessor.read(id::cp15::R6_PU_DATA_3_BASE_ADDRESS);
                region_data_4_start = coprocessor.read(id::cp15::R6_PU_DATA_4_BASE_ADDRESS);
                region_data_5_start = coprocessor.read(id::cp15::R6_PU_DATA_5_BASE_ADDRESS);
                region_data_6_start = coprocessor.read(id::cp15::R6_PU_DATA_6_BASE_ADDRESS);
                region_data_7_start = coprocessor.read(id::cp15::R6_PU_DATA_7_BASE_ADDRESS);
                region_data_0_end = region_data_0_start + static_cast<u32>(get_size(static_cast<u8>(coprocessor.read(id::cp15::R6_PU_DATA_0_SIZE))));
                region_data_1_end = region_data_1_start + static_cast<u32>(get_size(static_cast<u8>(coprocessor.read(id::cp15::R6_PU_DATA_1_SIZE))));
                region_data_2_end = region_data_2_start + static_cast<u32>(get_size(static_cast<u8>(coprocessor.read(id::cp15::R6_PU_DATA_2_SIZE))));
                region_data_3_end = region_data_3_start + static_cast<u32>(get_size(static_cast<u8>(coprocessor.read(id::cp15::R6_PU_DATA_3_SIZE))));
                region_data_4_end = region_data_4_start + static_cast<u32>(get_size(static_cast<u8>(coprocessor.read(id::cp15::R6_PU_DATA_4_SIZE))));
                region_data_5_end = region_data_5_start + static_cast<u32>(get_size(static_cast<u8>(coprocessor.read(id::cp15::R6_PU_DATA_5_SIZE))));
                region_data_6_end = region_data_6_start + static_cast<u32>(get_size(static_cast<u8>(coprocessor.read(id::cp15::R6_PU_DATA_6_SIZE))));
                region_data_7_end = region_data_7_start + static_cast<u32>(get_size(static_cast<u8>(coprocessor.read(id::cp15::R6_PU_DATA_7_SIZE))));
                region_data_0_enabled = coprocessor.read(id::cp15::R6_PU_DATA_0_E);
                region_data_1_enabled = coprocessor.read(id::cp15::R6_PU_DATA_1_E);
                region_data_2_enabled = coprocessor.read(id::cp15::R6_PU_DATA_2_E);
                region_data_3_enabled = coprocessor.read(id::cp15::R6_PU_DATA_3_E);
                region_data_4_enabled = coprocessor.read(id::cp15::R6_PU_DATA_4_E);
                region_data_5_enabled = coprocessor.read(id::cp15::R6_PU_DATA_5_E);
                region_data_6_enabled = coprocessor.read(id::cp15::R6_PU_DATA_6_E);
                region_data_7_enabled = coprocessor.read(id::cp15::R6_PU_DATA_7_E);
            }
        } else {
            region_0_start = coprocessor.read(id::cp15::R6_PU_0_BASE_ADDRESS);
            region_1_start = coprocessor.read(id::cp15::R6_PU_1_BASE_ADDRESS);
            region_2_start = coprocessor.read(id::cp15::R6_PU_2_BASE_ADDRESS);
            region_3_start = coprocessor.read(id::cp15::R6_PU_3_BASE_ADDRESS);
            region_4_start = coprocessor.read(id::cp15::R6_PU_4_BASE_ADDRESS);
            region_5_start = coprocessor.read(id::cp15::R6_PU_5_BASE_ADDRESS);
            region_6_start = coprocessor.read(id::cp15::R6_PU_6_BASE_ADDRESS);
            region_7_start = coprocessor.read(id::cp15::R6_PU_7_BASE_ADDRESS);
            region_0_end = region_0_start + static_cast<u32>(get_size(static_cast<u8>(coprocessor.read(id::cp15::R6_PU_0_SIZE))));
            region_1_end = region_1_start + static_cast<u32>(get_size(static_cast<u8>(coprocessor.read(id::cp15::R6_PU_1_SIZE))));
            region_2_end = region_2_start + static_cast<u32>(get_size(static_cast<u8>(coprocessor.read(id::cp15::R6_PU_2_SIZE))));
            region_3_end = region_3_start + static_cast<u32>(get_size(static_cast<u8>(coprocessor.read(id::cp15::R6_PU_3_SIZE))));
            region_4_end = region_4_start + static_cast<u32>(get_size(static_cast<u8>(coprocessor.read(id::cp15::R6_PU_4_SIZE))));
            region_5_end = region_5_start + static_cast<u32>(get_size(static_cast<u8>(coprocessor.read(id::cp15::R6_PU_5_SIZE))));
            region_6_end = region_6_start + static_cast<u32>(get_size(static_cast<u8>(coprocessor.read(id::cp15::R6_PU_6_SIZE))));
            region_7_end = region_7_start + static_cast<u32>(get_size(static_cast<u8>(coprocessor.read(id::cp15::R6_PU_7_SIZE))));
            region_0_enabled = coprocessor.read(id::cp15::R6_PU_0_E);
            region_1_enabled = coprocessor.read(id::cp15::R6_PU_1_E);
            region_2_enabled = coprocessor.read(id::cp15::R6_PU_2_E);
            region_3_enabled = coprocessor.read(id::cp15::R6_PU_3_E);
            region_4_enabled = coprocessor.read(id::cp15::R6_PU_4_E);
            region_5_enabled = coprocessor.read(id::cp15::R6_PU_5_E);
            region_6_enabled = coprocessor.read(id::cp15::R6_PU_6_E);
            region_7_enabled = coprocessor.read(id::cp15::R6_PU_7_E);
        }

        globals.mpu_address_change = false;
    }

    id::cp15 AP_region_id = id::cp15::UNKNOWN;
    u8 matched_region = 0;
    const u32 address_start = address;
    const u32 address_end = address + access_size;

    // this section is really fucking bad, rewrite this to something cleaner TODO
    if (settings.is_mpu_separate) {
        if (access_type == id::access_type::INSTRUCTION_FETCH) {
            if      (region_inst_7_enabled && (address_start >= region_inst_7_start && address_end <= region_inst_7_end)) { AP_region_id = id::cp15::R5_PU_INST_AP7; matched_region = 7; }
            else if (region_inst_6_enabled && (address_start >= region_inst_6_start && address_end <= region_inst_6_end)) { AP_region_id = id::cp15::R5_PU_INST_AP6; matched_region = 6; }
            else if (region_inst_5_enabled && (address_start >= region_inst_5_start && address_end <= region_inst_5_end)) { AP_region_id = id::cp15::R5_PU_INST_AP5; matched_region = 5; }
            else if (region_inst_4_enabled && (address_start >= region_inst_4_start && address_end <= region_inst_4_end)) { AP_region_id = id::cp15::R5_PU_INST_AP4; matched_region = 4; }
            else if (region_inst_3_enabled && (address_start >= region_inst_3_start && address_end <= region_inst_3_end)) { AP_region_id = id::cp15::R5_PU_INST_AP3; matched_region = 3; }
            else if (region_inst_2_enabled && (address_start >= region_inst_2_start && address_end <= region_inst_2_end)) { AP_region_id = id::cp15::R5_PU_INST_AP2; matched_region = 2; }
            else if (region_inst_1_enabled && (address_start >= region_inst_1_start && address_end <= region_inst_1_end)) { AP_region_id = id::cp15::R5_PU_INST_AP1; matched_region = 1; }
            else if (region_inst_0_enabled && (address_start >= region_inst_0_start && address_end <= region_inst_0_end)) { AP_region_id = id::cp15::R5_PU_INST_AP0; matched_region = 0; }
            else { 
                return { 
                    /* has_failed */ FAILED, 
                    /* abort_code */ id::aborts::PREFETCH_ABORT,
                    /* region_index */ 0 
                };
            }
        } else {
            if      (region_data_7_enabled && (address_start >= region_data_7_start && address_end <= region_data_7_end)) { AP_region_id = id::cp15::R5_PU_DATA_AP7; matched_region = 7; }
            else if (region_data_6_enabled && (address_start >= region_data_6_start && address_end <= region_data_6_end)) { AP_region_id = id::cp15::R5_PU_DATA_AP6; matched_region = 6; }
            else if (region_data_5_enabled && (address_start >= region_data_5_start && address_end <= region_data_5_end)) { AP_region_id = id::cp15::R5_PU_DATA_AP5; matched_region = 5; }
            else if (region_data_4_enabled && (address_start >= region_data_4_start && address_end <= region_data_4_end)) { AP_region_id = id::cp15::R5_PU_DATA_AP4; matched_region = 4; }
            else if (region_data_3_enabled && (address_start >= region_data_3_start && address_end <= region_data_3_end)) { AP_region_id = id::cp15::R5_PU_DATA_AP3; matched_region = 3; }
            else if (region_data_2_enabled && (address_start >= region_data_2_start && address_end <= region_data_2_end)) { AP_region_id = id::cp15::R5_PU_DATA_AP2; matched_region = 2; }
            else if (region_data_1_enabled && (address_start >= region_data_1_start && address_end <= region_data_1_end)) { AP_region_id = id::cp15::R5_PU_DATA_AP1; matched_region = 1; }
            else if (region_data_0_enabled && (address_start >= region_data_0_start && address_end <= region_data_0_end)) { AP_region_id = id::cp15::R5_PU_DATA_AP0; matched_region = 0; }
            else { 
                return { 
                    /* has_failed */ FAILED, 
                    /* abort_code */ id::aborts::ABORT, 
                    /* region_index */ 0 
                }; 
            }
        }
    } else {
        if      (region_7_enabled && (address_start >= region_7_start && address_end <= region_7_end)) { AP_region_id = id::cp15::R5_PU_AP7; matched_region = 7; }
        else if (region_6_enabled && (address_start >= region_6_start && address_end <= region_6_end)) { AP_region_id = id::cp15::R5_PU_AP6; matched_region = 6; }
        else if (region_5_enabled && (address_start >= region_5_start && address_end <= region_5_end)) { AP_region_id = id::cp15::R5_PU_AP5; matched_region = 5; }
        else if (region_4_enabled && (address_start >= region_4_start && address_end <= region_4_end)) { AP_region_id = id::cp15::R5_PU_AP4; matched_region = 4; }
        else if (region_3_enabled && (address_start >= region_3_start && address_end <= region_3_end)) { AP_region_id = id::cp15::R5_PU_AP3; matched_region = 3; }
        else if (region_2_enabled && (address_start >= region_2_start && address_end <= region_2_end)) { AP_region_id = id::cp15::R5_PU_AP2; matched_region = 2; }
        else if (region_1_enabled && (address_start >= region_1_start && address_end <= region_1_end)) { AP_region_id = id::cp15::R5_PU_AP1; matched_region = 1; }
        else if (region_0_enabled && (address_start >= region_0_start && address_end <= region_0_end)) { AP_region_id = id::cp15::R5_PU_AP0; matched_region = 0; }
        else {
            if (access_type == id::access_type::INSTRUCTION_FETCH) {
                return { 
                    /* has_failed */ FAILED, 
                    /* abort_code */ id::aborts::PREFETCH_ABORT, 
                    /* region_index */ 0 
                };
            }

            return { 
                /* has_failed */ FAILED, 
                /* abort_code */ id::aborts::ABORT, 
                /* region_index */ 0 
            };
        }
    }

    const u8 AP_bits = static_cast<u8>(coprocessor.read(AP_region_id));
    const id::access_perm AP_id = get_access_perm(AP_bits);

    switch (AP_id) {
        case id::access_perm::READ_WRITE:
            if (
                (access_type != id::access_type::INSTRUCTION_FETCH) &&
                (access_type != id::access_type::READ_WRITE) &&
                (access_type != id::access_type::READ) &&
                (access_type != id::access_type::WRITE)
            ) {
                return { 
                    /* has_failed */ FAILED, 
                    /* abort_code */ id::aborts::ABORT, 
                    /* region_index */ 0 
                };
            }
            break;

        case id::access_perm::READ_ONLY:
            if (
                (access_type != id::access_type::INSTRUCTION_FETCH) &&
                (access_type != id::access_type::READ_WRITE) && // this overlaps with the read permission, so this is valid
                (access_type != id::access_type::READ)
            ) {
                return { 
                    /* has_failed */ FAILED, 
                    /* abort_code */ id::aborts::ABORT, 
                    /* region_index */ 0 
                };
            }
            break;

        case id::access_perm::UNPREDICTABLE:
            llarm::out::unpredictable("MPU access perm is unpredictable");
            [[fallthrough]];

        case id::access_perm::NO_ACCESS:
            if (access_type == id::access_type::INSTRUCTION_FETCH) {
                return {
                    /* has_failed */ FAILED,
                    /* abort_code */ id::aborts::PREFETCH_ABORT,
                    /* region_index */ 0
                };
            }

            return {
                /* has_failed */ FAILED,
                /* abort_code */ id::aborts::ABORT,
                /* region_index */ 0
            };
    }

    return { 
        /* has_failed */ SUCCESS,
        /* abort_code */ id::aborts::NO_ABORT, 
        /* region_index */ matched_region 
    };
}


mem_write_struct MPU::write(const u32 physical_address, const u64 value, const u8 access_size) {
    const mpu_access_result result = check_access(physical_address, access_size, id::access_type::WRITE);

    if (result.has_failed) {
        return mem_write_struct {
            /* has_failed  */ true,
            /* abort_code  */ result.abort_code
        };
    }

    if (settings.has_cache && coprocessor.read(id::cp15::R1_C)) {
        const u8 region = result.region_index;
        bool is_cacheable = false;
        bool is_write_bufferable = false;

        if (settings.is_mpu_separate) {
            is_cacheable = coprocessor.read(CACHEABLE_DATA.at(region));
            is_write_bufferable = coprocessor.read(BUFFERABLE_DATA.at(region));
        } else {
            is_cacheable = coprocessor.read(CACHEABLE.at(region));
            is_write_bufferable = coprocessor.read(BUFFERABLE.at(region));
        }

        if (is_cacheable) {
            cache.write(physical_address, physical_address, static_cast<u32>(value), access_size, is_write_bufferable);
            return mem_write_struct {
                /* has_failed  */ false,
                /* abort_code  */ id::aborts::NO_ABORT
            };
        }
    }

    ram.write(physical_address, value, access_size);

    return mem_write_struct {
        /* has_failed  */ false,
        /* abort_code  */ id::aborts::NO_ABORT
    };
}


mem_read_struct MPU::read(const u32 address, const u8 access_size, const id::access_type access_type) {
    const mpu_access_result result = check_access(address, access_size, access_type);

    if (result.has_failed) {
        return mem_read_struct {
            /* has_failed  */ true,
            /* abort_code  */ result.abort_code,
            /* access_size */ access_size,
            /* value       */ 0
        };
    }

    if (settings.has_cache) {
        const u8 region = result.region_index;
        bool is_cacheable = false;
        bool is_write_bufferable = false;

        if (settings.is_mpu_separate) {
            if (access_type == id::access_type::INSTRUCTION_FETCH) {
                is_cacheable = coprocessor.read(CACHEABLE_INST.at(region));
                is_write_bufferable = false;
            } else {
                is_cacheable = coprocessor.read(CACHEABLE_DATA.at(region));
                is_write_bufferable = coprocessor.read(BUFFERABLE_DATA.at(region));
            }
        } else {
            is_cacheable = coprocessor.read(CACHEABLE.at(region));
            is_write_bufferable = coprocessor.read(BUFFERABLE.at(region));
        }

        if (access_type == id::access_type::INSTRUCTION_FETCH) {
            const bool inst_cache_on = settings.has_unified_cache
                ? coprocessor.read(id::cp15::R1_C)
                : coprocessor.read(id::cp15::R1_I);

            if (is_cacheable && inst_cache_on) {
                return mem_read_struct {
                    /* has_failed  */ false,
                    /* abort_code  */ id::aborts::NO_ABORT,
                    /* access_size */ access_size,
                    /* value       */ cache.fetch_inst(address, address)
                };
            }
        } else {
            if (is_cacheable && coprocessor.read(id::cp15::R1_C)) {
                return mem_read_struct {
                    /* has_failed  */ false,
                    /* abort_code  */ id::aborts::NO_ABORT,
                    /* access_size */ access_size,
                    /* value       */ cache.read(address, address, is_write_bufferable)
                };
            }
        }
    }

    const u64 data = ram.read(address, access_size);

    return mem_read_struct {
        /* has_failed  */ false,
        /* abort_code  */ id::aborts::NO_ABORT,
        /* access_size */ access_size,
        /* value       */ data
    };
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

    region_inst_0_start = 0;
    region_inst_1_start = 0;
    region_inst_2_start = 0;
    region_inst_3_start = 0;
    region_inst_4_start = 0;
    region_inst_5_start = 0;
    region_inst_6_start = 0;
    region_inst_7_start = 0;
    region_inst_0_end = 0;
    region_inst_1_end = 0;
    region_inst_2_end = 0;
    region_inst_3_end = 0;
    region_inst_4_end = 0;
    region_inst_5_end = 0;
    region_inst_6_end = 0;
    region_inst_7_end = 0;
    region_inst_0_enabled = false;
    region_inst_1_enabled = false;
    region_inst_2_enabled = false;
    region_inst_3_enabled = false;
    region_inst_4_enabled = false;
    region_inst_5_enabled = false;
    region_inst_6_enabled = false;
    region_inst_7_enabled = false;

    region_data_0_start = 0;
    region_data_1_start = 0;
    region_data_2_start = 0;
    region_data_3_start = 0;
    region_data_4_start = 0;
    region_data_5_start = 0;
    region_data_6_start = 0;
    region_data_7_start = 0;
    region_data_0_end = 0;
    region_data_1_end = 0;
    region_data_2_end = 0;
    region_data_3_end = 0;
    region_data_4_end = 0;
    region_data_5_end = 0;
    region_data_6_end = 0;
    region_data_7_end = 0;
    region_data_0_enabled = false;
    region_data_1_enabled = false;
    region_data_2_enabled = false;
    region_data_3_enabled = false;
    region_data_4_enabled = false;
    region_data_5_enabled = false;
    region_data_6_enabled = false;
    region_data_7_enabled = false;

    coprocessor.write(id::cp15::R6_PU_0, 0);
    coprocessor.write(id::cp15::R6_PU_1, 0);
    coprocessor.write(id::cp15::R6_PU_2, 0);
    coprocessor.write(id::cp15::R6_PU_3, 0);
    coprocessor.write(id::cp15::R6_PU_4, 0);
    coprocessor.write(id::cp15::R6_PU_5, 0);
    coprocessor.write(id::cp15::R6_PU_6, 0);
    coprocessor.write(id::cp15::R6_PU_7, 0);

    coprocessor.write(id::cp15::R6_PU_INST_0, 0);
    coprocessor.write(id::cp15::R6_PU_INST_1, 0);
    coprocessor.write(id::cp15::R6_PU_INST_2, 0);
    coprocessor.write(id::cp15::R6_PU_INST_3, 0);
    coprocessor.write(id::cp15::R6_PU_INST_4, 0);
    coprocessor.write(id::cp15::R6_PU_INST_5, 0);
    coprocessor.write(id::cp15::R6_PU_INST_6, 0);
    coprocessor.write(id::cp15::R6_PU_INST_7, 0);

    coprocessor.write(id::cp15::R6_PU_DATA_0, 0);
    coprocessor.write(id::cp15::R6_PU_DATA_1, 0);
    coprocessor.write(id::cp15::R6_PU_DATA_2, 0);
    coprocessor.write(id::cp15::R6_PU_DATA_3, 0);
    coprocessor.write(id::cp15::R6_PU_DATA_4, 0);
    coprocessor.write(id::cp15::R6_PU_DATA_5, 0);
    coprocessor.write(id::cp15::R6_PU_DATA_6, 0);
    coprocessor.write(id::cp15::R6_PU_DATA_7, 0);
}
