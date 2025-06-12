#pragma once

#include "../../settings.hpp"
#include "../coprocessor/coprocessor.hpp"


struct ALIGNMENT {
private:
    COPROCESSOR& coprocessor;
    SETTINGS& settings;

public:
    bool is_enabled();
    bool is_disabled();

    bool is_aligned(const u32 value, const u8 access_size);

public:
    ALIGNMENT(COPROCESSOR& coprocessor, SETTINGS& settings) : coprocessor(coprocessor), settings(settings) {
    
    }
};
        