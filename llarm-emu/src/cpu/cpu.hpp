#pragma once

#include "../settings.hpp"
#include "memory/ram.hpp"
#include "core/core.hpp"

#include <llarm/llarm-asm.hpp>
#include <llarm/shared/types.hpp>

struct CPU {
public:
    CORE core;

    SETTINGS settings;
    RAM ram;

public:
    void initialise(const std::vector<u8> &binary);

public:
    CPU(const std::vector<u8> &binary);
};