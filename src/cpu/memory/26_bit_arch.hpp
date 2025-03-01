#pragma once

#include "../coprocessor/coprocessor.hpp"
#include "../../settings.hpp"
#include "../../id.hpp"

struct ARCH_26_BIT {
private:
    COPROCESSOR& coprocessor;
    SETTINGS& settings;

public:
    // this is specific to the 26-bit architecture
    bool is_26_arch_address_unsupported(const u32 address) {
        // 26-bit architecture cannot have an address above (2^26)-1
        if (is_26_arch_address()) {
            if (address > ((1 << 26) - 1)) {
                return false;
            }
        }

        return true;
    }

    bool is_26_arch_program() {
        if (settings.no_26_bits) {
            return false;
        } else if (settings.only_26_bits) {
            return true;
        }

        return (coprocessor.read(id::cp::CP15_R1_P) == false);
    }

    bool is_26_arch_address() {
        if (settings.no_26_bits) {
            return false;
        } else if (settings.only_26_bits) {
            return true;
        }

        return (coprocessor.read(id::cp::CP15_R1_D) == false);
    }

    bool is_fully_26_arch() {
        return (is_26_arch_address() && is_26_arch_program());
    }

    bool is_only_26_arch() {
        return settings.only_26_bits;
    }

    bool has_26_arch_backwards_compatible() {
        return settings.backwards_compat_support_26_bits;
    }

    bool no_26_arch_support() {
        return settings.no_26_bits;
    }


    ARCH_26_BIT(
        COPROCESSOR& coprocessor,
        SETTINGS& settings
    ) : coprocessor(coprocessor),
        settings(settings)
    {

    }
};