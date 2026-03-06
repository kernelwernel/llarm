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
    };

    inline settings default_dis_settings() {
        return settings { true, true, true, false, true, false, true, true, true, true, false };
    }
}