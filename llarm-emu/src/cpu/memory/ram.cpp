
#include "../globals.hpp"

#include "ram.hpp"

#include <vector>
#include <array>

#include "shared/types.hpp"
#include "shared/out.hpp"

void RAM::write(const std::vector<u8> &data, const u32 address) {
    if (address + data.size() > ram.size()) {
        llarm::out::dev_error("Data exceeds RAM capacity (std::vector)");
    }

    std::copy(data.cbegin(), data.cend(), ram.begin() + address);
}


void RAM::write(const u64 &value, const u32 address, const u8 access_size) {
    switch (access_size) {
        case 1: ram.at(address) = value; return;
        case 2: 
            ram.at(address)     = (value & 0x00FF);
            ram.at(address + 1) = (value & 0xFF00);
            return;

        case 4: 
            ram.at(address)     = (value & 0x000000FF);
            ram.at(address + 1) = (value & 0x0000FF00);
            ram.at(address + 2) = (value & 0x00FF0000);
            ram.at(address + 3) = (value & 0xFF000000);
            return;
        
        case 8: 
            ram.at(address)     = (value & 0x00000000000000FF);
            ram.at(address + 1) = (value & 0x000000000000FF00);
            ram.at(address + 2) = (value & 0x0000000000FF0000);
            ram.at(address + 3) = (value & 0x00000000FF000000);
            ram.at(address + 4) = (value & 0x000000FF00000000);
            ram.at(address + 5) = (value & 0x0000FF0000000000);
            ram.at(address + 6) = (value & 0x00FF000000000000);
            ram.at(address + 7) = (value & 0xFF00000000000000);
            return;

        default: llarm::out::dev_error("Unsupported data size for RAM write operation");
    }
}


std::vector<u8> RAM::vector_read(const u32 start, const u32 end) {
    return std::vector<u8>(ram.cbegin() + start, ram.cbegin() + end);
}


u64 RAM::read(const u32 address, const u8 access_size) {
    switch (access_size) {
        case 1: return ram.at(address);
        case 2: return (
            (static_cast<u16>(ram.at(address)) << 8) | 
            (ram.at(address + 1))
        );

        case 4: return (
            (static_cast<u32>(ram.at(address)) << 24) | 
            (ram.at(address + 1) << 16) |
            (ram.at(address + 2) << 8) |
            (ram.at(address + 3))
        );

        case 8: return (
            (static_cast<u64>(ram.at(address)) << 56) | 
            (static_cast<u64>(ram.at(address + 1)) << 48) |
            (static_cast<u64>(ram.at(address + 2)) << 40) |
            (static_cast<u64>(ram.at(address + 3)) << 32) |
            (static_cast<u64>(ram.at(address + 4)) << 24) |
            (static_cast<u64>(ram.at(address + 5)) << 16) |
            (static_cast<u64>(ram.at(address + 6)) << 8) |
            (static_cast<u64>(ram.at(address + 7)))
        );

        default: llarm::out::error("Unsupported RAM size fetch for read operation");
    }
}


void RAM::reset() {
    ram.fill(0);
}

RAM::RAM(GLOBALS& globals) : globals(globals) {};