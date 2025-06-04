#include "../../settings.hpp"
#include "../../id.hpp"
#include "../coprocessor/coprocessor.hpp"

#include "26_bit_arch.hpp"


bool ARCH_26::is_26_arch_address_unsupported(const u32 address) {
    // 26-bit architecture cannot have an address above (2^26)-1
    if (is_26_arch_address()) {
        if (address > ((1 << 26) - 1)) {
            return false;
        }
    }

    return true;
}

bool ARCH_26::is_26_arch_program() {
    if (settings.no_26_bits) {
        return false;
    } else if (settings.only_26_bits) {
        return true;
    }

    return (coprocessor.read(id::cp15::R1_P) == false);
}

bool ARCH_26::is_26_arch_address() {
    if (settings.no_26_bits) {
        return false;
    } else if (settings.only_26_bits) {
        return true;
    }

    return (coprocessor.read(id::cp15::R1_D) == false);
}

bool ARCH_26::is_fully_26_arch() {
    return (is_26_arch_address() && is_26_arch_program());
}

bool ARCH_26::is_only_26_arch() {
    return settings.only_26_bits;
}

bool ARCH_26::is_26_arch_backwards_compatible() {
    return settings.backwards_compat_support_26_bits;
}

bool ARCH_26::no_26_arch_support() {
    return settings.no_26_bits;
}