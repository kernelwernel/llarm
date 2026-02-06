#pragma once

#include <llarm/shared/types.hpp>

struct settings_struct {
    bool fixed_register_choice; // every register will be set to R0
    bool random_register_choice; 

    bool no_cond_limitation; // every condition is passed
    bool occasional_cond_switch; // blobs of specific conds will be applied for maybe 5 or 10 instructions
    u8 cond_switch_frequency;
    bool random_conds; 
};