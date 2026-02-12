#pragma once

namespace internal {
    struct settings {
        bool hex;
        bool register_alias;
        bool capitals;
        bool simplify;
        bool remove_nulls;
        bool gcc_convention;
    };


    inline settings default_dis_settings() {
        return settings { true, true, true, false, true, false };
    }
}