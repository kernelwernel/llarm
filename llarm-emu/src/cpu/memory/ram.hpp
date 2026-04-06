#pragma once

#include "../../utility.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/out.hpp>

#include <vector>
#include <array>


struct RAM {
private:
    static constexpr u32 default_size = util::get_kb(32); // 32KB

#if (LLARM_LOW_MEMORY)
    std::map<u32, u8> ram{};
#else
    std::array<u8, default_size> ram{};
#endif

public:
    void write(const std::vector<u8> &data, const u32 address);

    template <std::size_t N>
    void write(const std::array<u8, N> &data, const u32 address) {
        if (address + N > ram.size()) {
            llarm::out::dev_error("Data exceeds RAM capacity (std::array)");
        }

        std::move(data.cbegin(), data.cend(), ram.begin() + address);
    }

    void write(const u64 value, const u32 address, const u8 access_size);

    std::vector<u8> vector_read(const u32 start, const u32 end);

    u64 read(const u32 address, const u8 access_size);

    void reset();
};