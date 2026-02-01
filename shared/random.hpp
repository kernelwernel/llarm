#include "types.hpp"

#include <chrono>

constexpr u64 golden_ratio = 0x9e3779b97f4a7c15ULL;

namespace llarm {
    struct random {
        u64 seed;
        
        random(const u64 seed_arg = 0);

        u64 generate();
        u64 generate_range(const u64 start, const u64 end);
    };
}