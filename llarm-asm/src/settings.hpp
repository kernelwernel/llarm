#pragma once

#include <llarm/shared/types.hpp>

namespace internal {
    struct settings {
        bool hex = false;
        bool register_alias = false;
        bool capitals = false;
        bool simplify = false;
        bool remove_nulls = false;
        bool gcc_convention = false;
        bool cond_always_suffix = false;
        bool explicit_operands = false;
        bool strict_compliance = false;
        bool equivalent_alias = false;
        bool explicit_rotation = false;
        bool extra_space = false;
        u8 arm_version = 9;
    };

    inline settings default_dis_settings() {
        return settings { 
            true, // hex 
            true, // register alias 
            true, // capitals
            false, // simplify
            true, // remove_nulls
            false, //gcc_convention 
            true, // cond_always_suffix true, 
            true, // explicit_operands
            true, // strict_compliance
            false, // equivalent_alias
            false, // explicit_rotation
            false, // extra_space
            9 // arm_version
        };
    }
}