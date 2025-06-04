#pragma once

#include "../../id.hpp"

#include "shared/types.hpp"

// this is the standard access structure that the MMU, MPU, and raw access types use. 
// Think of it as a universal communication format for the purpose of uniformly giving 
// the status of a memory access's result, data, and status. 

struct mem_write_struct {
    bool has_failed;
    id::aborts abort_code;
    //u8 access_size;
};


struct mem_read_struct {
    bool has_failed;
    id::aborts abort_code;
    u32 new_address;
    u8 access_size;
    u64 value; // the data in that memory location, specific to read access
};