#pragma once

#include "../core/globals.hpp"
#include "../coprocessor/coprocessor.hpp"
#include "structures.hpp"
#include "../../ram/ram.hpp"
#include "fcse.hpp"
#include "cache.hpp"

#include <llarm/shared/types.hpp>

// memory protection unit
struct MPU {
    GLOBALS& globals;
    COPROCESSOR& coprocessor;
    SETTINGS& settings;
    RAM& ram;
    FCSE& fcse;
    CACHE& cache;

    u32 region_0_start = 0;
    u32 region_1_start = 0;
    u32 region_2_start = 0;
    u32 region_3_start = 0;
    u32 region_4_start = 0;
    u32 region_5_start = 0;
    u32 region_6_start = 0;
    u32 region_7_start = 0;
    u32 region_0_end = 0;
    u32 region_1_end = 0;
    u32 region_2_end = 0;
    u32 region_3_end = 0;
    u32 region_4_end = 0;
    u32 region_5_end = 0;
    u32 region_6_end = 0;
    u32 region_7_end = 0;
    bool region_0_enabled = false;
    bool region_1_enabled = false;
    bool region_2_enabled = false;
    bool region_3_enabled = false;
    bool region_4_enabled = false;
    bool region_5_enabled = false;
    bool region_6_enabled = false;
    bool region_7_enabled = false;

    u32 region_inst_0_start = 0;
    u32 region_inst_1_start = 0;
    u32 region_inst_2_start = 0;
    u32 region_inst_3_start = 0;
    u32 region_inst_4_start = 0;
    u32 region_inst_5_start = 0;
    u32 region_inst_6_start = 0;
    u32 region_inst_7_start = 0;
    u32 region_inst_0_end = 0;
    u32 region_inst_1_end = 0;
    u32 region_inst_2_end = 0;
    u32 region_inst_3_end = 0;
    u32 region_inst_4_end = 0;
    u32 region_inst_5_end = 0;
    u32 region_inst_6_end = 0;
    u32 region_inst_7_end = 0;
    bool region_inst_0_enabled = false;
    bool region_inst_1_enabled = false;
    bool region_inst_2_enabled = false;
    bool region_inst_3_enabled = false;
    bool region_inst_4_enabled = false;
    bool region_inst_5_enabled = false;
    bool region_inst_6_enabled = false;
    bool region_inst_7_enabled = false;

    u32 region_data_0_start = 0;
    u32 region_data_1_start = 0;
    u32 region_data_2_start = 0;
    u32 region_data_3_start = 0;
    u32 region_data_4_start = 0;
    u32 region_data_5_start = 0;
    u32 region_data_6_start = 0;
    u32 region_data_7_start = 0;
    u32 region_data_0_end = 0;
    u32 region_data_1_end = 0;
    u32 region_data_2_end = 0;
    u32 region_data_3_end = 0;
    u32 region_data_4_end = 0;
    u32 region_data_5_end = 0;
    u32 region_data_6_end = 0;
    u32 region_data_7_end = 0;
    bool region_data_0_enabled = false;
    bool region_data_1_enabled = false;
    bool region_data_2_enabled = false;
    bool region_data_3_enabled = false;
    bool region_data_4_enabled = false;
    bool region_data_5_enabled = false;
    bool region_data_6_enabled = false;
    bool region_data_7_enabled = false;

    // per-region cacheable bit IDs indexed by region number
    static constexpr std::array<id::cp15, 8> CACHEABLE = {
        id::cp15::R2_PU_C0, 
        id::cp15::R2_PU_C1, 
        id::cp15::R2_PU_C2, 
        id::cp15::R2_PU_C3,
        id::cp15::R2_PU_C4, 
        id::cp15::R2_PU_C5, 
        id::cp15::R2_PU_C6, 
        id::cp15::R2_PU_C7
    };

    static constexpr std::array<id::cp15, 8> CACHEABLE_INST = {
        id::cp15::R2_PU_INST_C0, 
        id::cp15::R2_PU_INST_C1, 
        id::cp15::R2_PU_INST_C2, 
        id::cp15::R2_PU_INST_C3,
        id::cp15::R2_PU_INST_C4, 
        id::cp15::R2_PU_INST_C5, 
        id::cp15::R2_PU_INST_C6, 
        id::cp15::R2_PU_INST_C7
    };

    static constexpr std::array<id::cp15, 8> CACHEABLE_DATA = {
        id::cp15::R2_PU_DATA_C0, 
        id::cp15::R2_PU_DATA_C1, 
        id::cp15::R2_PU_DATA_C2, 
        id::cp15::R2_PU_DATA_C3,
        id::cp15::R2_PU_DATA_C4, 
        id::cp15::R2_PU_DATA_C5, 
        id::cp15::R2_PU_DATA_C6, 
        id::cp15::R2_PU_DATA_C7
    };

    static constexpr std::array<id::cp15, 8> BUFFERABLE = {
        id::cp15::R3_PU_B0, 
        id::cp15::R3_PU_B1, 
        id::cp15::R3_PU_B2, 
        id::cp15::R3_PU_B3,
        id::cp15::R3_PU_B4, 
        id::cp15::R3_PU_B5, 
        id::cp15::R3_PU_B6, 
        id::cp15::R3_PU_B7
    };

    static constexpr std::array<id::cp15, 8> BUFFERABLE_INST = {
        id::cp15::R3_PU_INST_B0, 
        id::cp15::R3_PU_INST_B1, 
        id::cp15::R3_PU_INST_B2, 
        id::cp15::R3_PU_INST_B3,
        id::cp15::R3_PU_INST_B4, 
        id::cp15::R3_PU_INST_B5, 
        id::cp15::R3_PU_INST_B6, 
        id::cp15::R3_PU_INST_B7
    };

    static constexpr std::array<id::cp15, 8> BUFFERABLE_DATA = {
        id::cp15::R3_PU_DATA_B0, 
        id::cp15::R3_PU_DATA_B1, 
        id::cp15::R3_PU_DATA_B2, 
        id::cp15::R3_PU_DATA_B3,
        id::cp15::R3_PU_DATA_B4, 
        id::cp15::R3_PU_DATA_B5, 
        id::cp15::R3_PU_DATA_B6, 
        id::cp15::R3_PU_DATA_B7
    };

    static constexpr bool FAILED = true;
    static constexpr bool SUCCESS = false;

    struct mpu_access_result {
        bool has_failed = false;
        id::aborts abort_code = id::aborts::NO_ABORT;
        u8 region_index = 0;
    };

    u64 get_size(const u8 raw_size_bits) const;

    id::access_perm get_access_perm(const u8 AP) const;

    bool is_mpu_enabled() const;

    mpu_access_result check_access(const u32 physical_address, const u8 access_size, const id::access_type access_type);

    mem_write_struct write(const u32 physical_address, const u64 value, const u8 access_size);

    mem_read_struct read(const u32 physical_address, const u8 access_size, const id::access_type access_type = id::access_type::READ);

    void reset();

    MPU(
        GLOBALS& globals,
        COPROCESSOR& coprocessor,
        SETTINGS& settings,
        RAM& ram,
        FCSE& fcse,
        CACHE& cache
    ) : globals(globals),
        coprocessor(coprocessor),
        settings(settings),
        ram(ram),
        fcse(fcse),
        cache(cache)
    {

    }
};
