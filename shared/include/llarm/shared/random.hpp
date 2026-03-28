#pragma once

#include "types.hpp"

constexpr u64 golden_ratio = 0x9e3779b97f4a7c15ULL;

namespace llarm {
    struct random {
        u64 seed;
        u64 bit_cache = 0;
        u8  bit_cache_count = 0;

        static u64 generate_seed();

        random(const u64 seed_arg = generate_seed());

        u64 generate();
        u64 generate_range(const u64 start, const u64 end);
        u64 generate_index_range(const u32 start, const u32 end);
        bool generate_bit();
    };
}