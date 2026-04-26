#pragma once

#include "../vic/vic.hpp"
#include "../peripherals/uart/uart.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/out.hpp>

#include <vector>
#include <array>


struct RAM {
    SETTINGS& settings;
    VIC& vic;
    UART& uart;

    std::vector<u8> ram;

    void write(const u32 address, std::vector<u8> &data);

    template <std::size_t N>
    void write(const u32 address, std::array<u8, N> &data) {
        if (address + N > ram.size()) {
            llarm::out::dev_error("Data exceeds RAM capacity (std::array)");
        }

        std::move(data.cbegin(), data.cend(), ram.begin() + address);
    }

    void write(const u32 address, const u64 value, const u8 access_size);

    std::vector<u8> vector_read(const u32 start, const u32 end) const;

    u64 read(const u32 address, const u8 access_size);

    void reset();

    RAM(std::vector<u8> &data, SETTINGS& settings, VIC& vic, UART& uart)
        : settings(settings), vic(vic), uart(uart), ram(settings.memsize, 0) {
        write(0, data);
    }
};