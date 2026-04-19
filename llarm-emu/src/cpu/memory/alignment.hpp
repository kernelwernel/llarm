#pragma once

#include "../../settings.hpp"
#include "../coprocessor/coprocessor.hpp"


struct ALIGNMENT {
    COPROCESSOR& coprocessor;
    SETTINGS& settings;

    bool is_enabled() const;
    bool is_disabled() const;

    bool is_aligned(const u32 value, const u8 access_size) const;

    ALIGNMENT(COPROCESSOR& coprocessor, SETTINGS& settings) : coprocessor(coprocessor), settings(settings) {
    
    }
};
        