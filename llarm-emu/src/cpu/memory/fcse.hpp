#pragma once

#include "../../settings.hpp"
#include "../coprocessor/coprocessor.hpp"

#include "shared/types.hpp"


struct FCSE {
private:
    COPROCESSOR& coprocessor;
    SETTINGS& settings;

public:
    bool is_fcse_enabled();

    u32 modify_address(const u32 address);

    FCSE(
        COPROCESSOR& coprocessor, 
        SETTINGS& settings
    ) : coprocessor(coprocessor), 
        settings(settings) 
    {

    }
};