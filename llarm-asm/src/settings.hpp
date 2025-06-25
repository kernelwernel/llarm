#pragma once

namespace internal {
    struct settings {
        bool hex;
        bool register_alias;
        bool capitals;
        bool simplify;
        bool remove_nulls;
        bool E_variant;
    };


    inline settings default_settings() {
        return settings { true, true, true, false, true, };
    }
}