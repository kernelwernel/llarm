#pragma once

#include "../../settings.hpp"
#include "shared/types.hpp"
#include "../coprocessor/coprocessor.hpp"


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