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
    void write(const std::vector<u8> &data, const u32 address) {
        std::move(data.cbegin(), data.cend(), ram.begin() + address);
    }

    void write(const u8 data, const u32 address) {
        ram.at(address) = data;
    }

    void write(const u16 data, const u32 address) {
        ram.at(address) = data & 0x00FF;
        ram.at(address + 1) = data & 0xFF00;
    }

    void write(const u32 data, const u32 address) {
        ram.at(address)     = data & 0x000000FF;
        ram.at(address + 1) = data & 0x0000FF00;
        ram.at(address + 2) = data & 0x00FF0000;
        ram.at(address + 3) = data & 0xFF000000;
    }

    std::vector<u8> read(const u32 start, const u32 end) {
        return std::vector<u8>(ram.cbegin() + start, ram.cbegin() + end);
    }

    u8 read(const u32 address) {
        return ram.at(address);
    }

    void reset() {
        ram.fill(0);
    }
};