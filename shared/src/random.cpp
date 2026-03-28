#include "../include/llarm/shared/random.hpp"

#include <chrono>

using namespace llarm;


random::random(const u64 seed_arg) {
    (void)seed_arg; // temporary
}


u64 random::generate_seed() {
    // https://softwareengineering.stackexchange.com/questions/402542/where-do-magic-hashing-constants-like-0x9e3779b9-and-0x9e3779b1-come-from

    u64 counter = golden_ratio;
    const u64 time = static_cast<u64>(std::chrono::steady_clock::now().time_since_epoch().count());

    counter += golden_ratio;

    return (time ^ counter);
}


u64 random::generate() {
    u64 x = seed;

    x += golden_ratio;
    seed = x;

    // these magic numbers are just statistical variation values by 
    // the splitmix64 implementation, look them up for more details
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return (x ^ (x >> 31));
}


bool random::generate_bit() {
    if (bit_cache_count == 0) {
        bit_cache = generate();
        bit_cache_count = 64;
    }
    return (bit_cache >> --bit_cache_count) & 1;
}


u64 random::generate_index_range(const u32 start, const u32 end) {
    if (start >= end) {
        throw std::invalid_argument("start index cannot be higher or equal to the end index");
    }

    const u64 mask = (1ULL << (end - start + 1)) - 1;
    return ((generate() >> start) & mask);
}


u64 random::generate_range(const u64 start, const u64 end) {
    const u64 x = generate();

    for (u8 i = 0; i < 64; i++) {

    }

    (void)start;
    (void)end;
    (void)x;

    //return static_cast<u16>(r % range);
    return 0; // TODO FINISH THIS FUNCTION
}