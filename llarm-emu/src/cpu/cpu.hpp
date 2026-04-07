#pragma once

#include "../settings.hpp"
#include "memory/ram.hpp"
#include "core/core.hpp"

#include <llarm/llarm-asm.hpp>
#include <llarm/shared/types.hpp>

struct CPU {
public:
    SETTINGS settings;
    RAM ram;
    CORE core;

public:
    CPU(const std::vector<u8> &binary);

    void run(const bool is_headless = false);
};