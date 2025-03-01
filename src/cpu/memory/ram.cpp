#include "types.hpp"
#include "cpu/memory.hpp"
#include "cpu/ram.hpp"

#include <bitset>
#include <vector>

void RAM::write(const std::vector<u8> &data, const u32 address) {
    std::move(data.cbegin(), data.cend(), ram.begin() + address);
}

void RAM::write(const u8 data, const u32 address) {
    ram.at(address) = data;
}

void RAM::write(const u16 data, const u32 address) {
    ram.at(address) = data & 0x00FF;
    ram.at(address + 1) = data & 0xFF00;
}

void RAM::write(const u32 data, const u32 address) {
    ram.at(address)     = data & 0x000000FF;
    ram.at(address + 1) = data & 0x0000FF00;
    ram.at(address + 2) = data & 0x00FF0000;
    ram.at(address + 3) = data & 0xFF000000;
}

std::vector<u8> RAM::read(const u32 start, const u32 end) {
    return std::vector<u8>(ram.cbegin() + start, ram.cbegin() + end);
}

u8 RAM::read(const u32 address) {
    return ram.at(address);
}

void RAM::reset() {
    ram.fill(0);
}

RAM::RAM() {
    reset();
}

