
#include "ram.hpp"

#include <vector>

#include <llarm/shared/types.hpp>
#include <llarm/shared/out.hpp>

void RAM::write(const u32 address, std::vector<u8> &data) {
    if (address + data.size() > ram.size()) {
        llarm::out::dev_error("Data exceeds RAM capacity (std::vector)");
    }

    std::move(data.cbegin(), data.cend(), ram.begin() + static_cast<std::ptrdiff_t>(address));
}


void RAM::write(const u32 address, const u64 value, const u8 access_size) {
    if (settings.has_vic && vic.contains(address)) {
        vic.write(address, static_cast<u32>(value));
        return;
    }

    if (settings.has_uart && uart.contains(address)) {
        uart.write(address, static_cast<u32>(value));
        return;
    }

    if (settings.has_timer && timer.contains(address)) {
        timer.write(address, static_cast<u32>(value));
        return;
    }

    switch (access_size) {
        case 1:
            ram.at(address) = (value & 0xFF);
            return;

        case 2:
            ram.at(address)     = static_cast<u8>(value & 0xFF);
            ram.at(address + 1) = static_cast<u8>((value >> 8) & 0xFF);
            return;

        case 4:
            ram.at(address)     = static_cast<u8>(value & 0xFF);
            ram.at(address + 1) = static_cast<u8>((value >> 8)  & 0xFF);
            ram.at(address + 2) = static_cast<u8>((value >> 16) & 0xFF);
            ram.at(address + 3) = static_cast<u8>((value >> 24) & 0xFF);
            return;

        case 8:
            ram.at(address)     = static_cast<u8>(value & 0xFF);
            ram.at(address + 1) = static_cast<u8>((value >> 8)  & 0xFF);
            ram.at(address + 2) = static_cast<u8>((value >> 16) & 0xFF);
            ram.at(address + 3) = static_cast<u8>((value >> 24) & 0xFF);
            ram.at(address + 4) = static_cast<u8>((value >> 32) & 0xFF);
            ram.at(address + 5) = static_cast<u8>((value >> 40) & 0xFF);
            ram.at(address + 6) = static_cast<u8>((value >> 48) & 0xFF);
            ram.at(address + 7) = static_cast<u8>((value >> 56) & 0xFF);
            return;

        default: llarm::out::dev_error("Unsupported data size for RAM write operation");
    }
}


std::vector<u8> RAM::vector_read(const u32 start, const u32 end) const {
    return {ram.cbegin() + static_cast<std::ptrdiff_t>(start), ram.cbegin() + static_cast<std::ptrdiff_t>(end)};
}


u64 RAM::read(const u32 address, const u8 access_size) {
    if (settings.has_vic && vic.contains(address)) {
        return vic.read(address);
    }

    if (settings.has_uart && uart.contains(address)) {
        return uart.read(address);
    }

    if (settings.has_timer && timer.contains(address)) {
        return timer.read(address);
    }

    switch (access_size) {
        case 1: return ram.at(address);
        case 2: return static_cast<u64>(
            static_cast<u16>(ram.at(address)) |
            (static_cast<u16>(ram.at(address + 1)) << 8)
        );

        case 4: return static_cast<u64>(
            static_cast<u32>(ram.at(address)) |
            (static_cast<u32>(ram.at(address + 1)) << 8) |
            (static_cast<u32>(ram.at(address + 2)) << 16) |
            (static_cast<u32>(ram.at(address + 3)) << 24)
        );

        case 8: return (
            static_cast<u64>(ram.at(address)) |
            (static_cast<u64>(ram.at(address + 1)) << 8) |
            (static_cast<u64>(ram.at(address + 2)) << 16) |
            (static_cast<u64>(ram.at(address + 3)) << 24) |
            (static_cast<u64>(ram.at(address + 4)) << 32) |
            (static_cast<u64>(ram.at(address + 5)) << 40) |
            (static_cast<u64>(ram.at(address + 6)) << 48) |
            (static_cast<u64>(ram.at(address + 7)) << 56)
        );

        default: llarm::out::error("Unsupported RAM size fetch for read operation");
    }
}


void RAM::reset() {
    std::fill(ram.begin(), ram.end(), 0);
}