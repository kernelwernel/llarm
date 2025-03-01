#pragma once

#include "../../types.hpp"
#include "../../utility.hpp"

#include <bitset>
#include <vector>

struct RAM {
private:
    static constexpr u32 default_size = util::get_kb(32); // 32KB

    std::array<u8, default_size> ram;

public:
    void write(const std::vector<u8> &data, const u32 address);
    std::vector<u8> read(const u32 start, const u32 end);

    void write(const T data, const u32 address);
    T read(const u32 address);

    void reset();
};