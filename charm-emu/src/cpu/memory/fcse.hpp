#pragma once

#include "../../settings.hpp"
#include "shared/types.hpp"
#include "../../id.hpp"
#include "../coprocessor/coprocessor.hpp"


struct FCSE {
private:
    COPROCESSOR& coprocessor;
    SETTINGS& settings;

public:
    inline bool is_fcse_enabled() {
        return (settings.is_fcse_enabled);
    }

    u32 modify_address(const u32 address) {
        if (util::bit_fetcher(address, 31, 25) != 0) {
            return address;
        }

        const u8 PID = coprocessor.read(id::cp::CP15_R13_PID);
        return (address | PID << 25);
    }

    FCSE(
        COPROCESSOR& coprocessor, 
        SETTINGS& settings
    ) : coprocessor(coprocessor), 
        settings(settings) 
    {

    }
};