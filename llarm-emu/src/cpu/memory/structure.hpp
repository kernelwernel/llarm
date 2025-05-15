#pragma once

#include "../../id.hpp"
#include "shared/types.hpp"

// this is the standard access structure that the MMU, MPU, and raw access types can 
// understand. Think of it as a universal communication format for the purpose of 
// standardisation when accessing memory, whether it's a read or write.

template <typename T = u32>
struct memory_struct {
    bool has_failed;
    id::aborts abort_code;
    u32 new_address;
    T value; // the data in that memory location, specific to read access
};