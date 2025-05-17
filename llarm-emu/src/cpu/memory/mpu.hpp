#pragma once

#include "shared/types.hpp"
#include "../../utility.hpp"
#include "../core/globals.hpp"
#include "../coprocessor/coprocessor.hpp"
#include "structure.hpp"

// memory protection unit
struct MPU {
private:
    GLOBALS& globals;
    COPROCESSOR& coprocessor;
    SETTINGS& settings;
    
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

public:
    u64 get_size(const u8 raw_size_bits);

    id::access_perm get_access_perm(const u8 AP);

    bool is_mpu_enabled();
    
    memory_struct<> is_access_valid(const u32 address, const id::access_type access_type);

    memory_struct<> write_manager(const u32 address, const u8 access_size);

    // try to scan from most priority to least, rather than upwards
    
    // if the access is outside of any region, do an abort (doesn't say which tho) 

    // alignment checking is also allowed, implement this TODO

    // extra thing: region 0 could be set to 4GB, as a backup if all other regions fail

    void setup_R6_PU();

    void reset();

    MPU(
        GLOBALS& globals, 
        COPROCESSOR& coprocessor,
        SETTINGS& settings
    ) : globals(globals), 
        coprocessor(coprocessor),
        settings(settings)
    {
        
    }
};