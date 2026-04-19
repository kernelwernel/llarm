#pragma once

#include "../../settings.hpp"
#include "../coprocessor/coprocessor.hpp"

#include <llarm/shared/types.hpp>


struct FCSE {
    COPROCESSOR& coprocessor;
    SETTINGS& settings;

    bool is_fcse_enabled() const;

    u32 modify_address(const u32 address) const;

    FCSE(
        COPROCESSOR& coprocessor, 
        SETTINGS& settings
    ) : coprocessor(coprocessor), 
        settings(settings) 
    {

    }
};