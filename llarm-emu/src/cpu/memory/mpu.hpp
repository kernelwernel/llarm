#pragma once

#include "../globals.hpp"
#include "../coprocessor/coprocessor.hpp"
#include "structure.hpp"
#include "ram.hpp"

#include "shared/types.hpp"

// memory protection unit
struct MPU {
private:
    GLOBALS& globals;
    COPROCESSOR& coprocessor;
    SETTINGS& settings;
    RAM& ram;
    
private:
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

public:
    u64 get_size(const u8 raw_size_bits);

    id::access_perm get_access_perm(const u8 AP);

    bool is_mpu_enabled();
    
    id::aborts is_access_valid(const u32 address, const u8 access_size, const id::access_type access_type);

    mem_write_struct write(const u32 address, const u32 value, const u8 access_size);

    mem_read_struct read(const u32 address, const u8 access_size);

    // try to scan from most priority to least, rather than upwards
    
    // if the access is outside of any region, do an abort (doesn't say which tho) 

    // alignment checking is also allowed, implement this TODO

    // extra thing: region 0 could be set to 4GB, as a backup if all other regions fail

    void setup_R6_PU();

    void reset();

    MPU(
        GLOBALS& globals, 
        COPROCESSOR& coprocessor,
        SETTINGS& settings,
        RAM& ram
    ) : globals(globals), 
        coprocessor(coprocessor),
        settings(settings),
        ram(ram)
    {
        
    }
};