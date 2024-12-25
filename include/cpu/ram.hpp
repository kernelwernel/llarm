#pragma once

#include "types.hpp"

#include <bitset>
#include <vector>

struct RAM {
private:
    static constexpr u32 default_size = 32 * 1024; // 32KB

    std::array<u8, default_size> ram;

public:
    void write(const std::vector<u8> &data, const u32 address);
    void write(const u8 data, const u32 address);
    void write(const u16 data, const u32 address);
    void write(const u32 data, const u32 address);

    std::vector<u8> read(const u32 start, const u32 end);
    u8 read(const u32 address);

    void reset();
};