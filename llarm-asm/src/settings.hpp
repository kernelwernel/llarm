#pragma once

namespace internal {
    struct settings {
        bool hex;
        bool register_alias;
        bool capitals;
        bool simplify;
        bool remove_nulls;
        bool gcc_convention;
        bool cond_always_suffix;
        bool explicit_operands;
        bool strict_compliance;
        bool equivalent_alias;
        bool explicit_rotation;
        bool extra_space;
    };

    inline settings default_dis_settings() {

        bool hex;
        bool register_alias;
        bool capitals;
        bool simplify;
        bool remove_nulls;
        bool gcc_convention;
        bool cond_always_suffix;
        bool explicit_operands;
        bool strict_compliance;
        bool equivalent_alias;
        bool explicit_rotation;
        bool extra_space;

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
            false // extra_space
        };
    }
}