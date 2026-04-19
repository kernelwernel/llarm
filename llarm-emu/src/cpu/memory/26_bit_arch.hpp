#pragma once

#include "../../settings.hpp"
#include "../coprocessor/coprocessor.hpp"

struct ARCH_26 {
    COPROCESSOR& coprocessor;
    SETTINGS& settings;

    bool is_26_arch_address_unsupported(const u32 address) const;
    bool is_26_arch_program() const;
    bool is_26_arch_address() const;
    bool is_fully_26_arch() const;
    bool is_only_26_arch() const;
    bool is_26_arch_backwards_compatible() const;
    bool no_26_arch_support() const;

    ARCH_26(
        COPROCESSOR& coprocessor,
        SETTINGS& settings
    ) : coprocessor(coprocessor),
        settings(settings)
    {

    }
};