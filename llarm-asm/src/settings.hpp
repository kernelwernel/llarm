#pragma once

struct settings {
    bool hex;
    bool register_alias;
    bool capitals;
};


inline settings default_settings() {
    return settings { true, true };
}