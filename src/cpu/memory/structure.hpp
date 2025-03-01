#pragma once

#include "../../id.hpp"
#include "../../types.hpp"

// this is the standard access structure that both the MMU, MPU, and raw access types can understand. 
// think of it as a universal format for the purpose of standardisation.

struct memory_struct {
    bool is_successful;
    id::aborts abort_code;
    u32 value; // the data in that memory location, specific to read access
    u32 new_address;
};