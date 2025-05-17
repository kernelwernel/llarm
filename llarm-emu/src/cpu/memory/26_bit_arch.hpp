#pragma once

#include "../coprocessor/coprocessor.hpp"
#include "../../settings.hpp"

struct ARCH_26 {
private:
    COPROCESSOR& coprocessor;
    SETTINGS& settings;

public:
    bool is_26_arch_address_unsupported(const u32 address);
    bool is_26_arch_program();
    bool is_26_arch_address();
    bool is_fully_26_arch();
    bool is_only_26_arch();
    bool is_26_arch_backwards_compatible();
    bool no_26_arch_support();

    ARCH_26(
        COPROCESSOR& coprocessor,
        SETTINGS& settings
    ) : coprocessor(coprocessor),
        settings(settings)
    {

    }
};