#pragma once

#include "../../id.hpp"

#include <llarm/shared/types.hpp>

// this is the standard access structure that the MMU, MPU, and raw access types use. 
// Think of it as a universal communication format for the purpose of uniformly giving 
// the status of a memory access's result, data, and status. 

struct mem_write_struct {
    bool has_failed;
    id::aborts abort_code;
};


struct mem_read_struct {
    bool has_failed;
    id::aborts abort_code;
    u8 access_size;
    u64 value;
};


// specific to the MMU
struct translation_struct {
    bool has_failed;
    id::aborts abort_code;
    u32 physical_address;
    bool is_cacheable;
    bool is_write_bufferable;
};


// specific to the TLB
struct tlb_fetch_struct {
    bool is_found;
    bool is_in_unified_table;
    bool is_in_inst_table;
    bool is_in_data_table;
};