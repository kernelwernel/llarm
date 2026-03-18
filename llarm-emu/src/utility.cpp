#include "utility.hpp"

#include <iostream>
#include <limits>

#include <llarm/shared/out.hpp>
#include <llarm/shared/types.hpp>


void util::modify_vfp_bit(u64 &original, const u8 index, const bool value) {
    if (index > 63) {
        llarm::out::dev_error("Index for modify_vfp_bit() must be between 0 and 63");
    }

    if (value) {
        original |= (1U << index);
    } else {
        original &= ~(1U << index);
    }
}



void util::swap_bits_vfp(u64 &original, const u8 start, const u8 end, const u32 value) {
    if (start >= 64 || end >= 64 || start >= end) {
        llarm::out::dev_error("util::swap_bits_vfp has impossible arguments");
        return;
    }

    const u8 num_bits = static_cast<u8>(end - start + 1);
    const u32 mask = static_cast<u8>((1 << num_bits) - 1);
    original &= ~(mask << start);
    original |= (value & mask) << start;
}


// these are for development and debug purposes, ignore this section
[[maybe_unused]] void util::dev::pause() {
    std::cout << "press enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}