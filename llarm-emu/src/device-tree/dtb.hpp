#pragma once

#include "../ram/ram.hpp"

#include <llarm/shared/types.hpp>

#include <array>

struct DTB {
    static const std::array<u8, 1385> data;

    void load(RAM& ram, const u32 address) const;
};
