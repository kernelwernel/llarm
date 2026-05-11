#pragma once

#include "../settings.hpp"
#include "../ram/ram.hpp"
#include "../vic/vic.hpp"
#include "../peripherals/uart/uart.hpp"
#include "../peripherals/timer/timer.hpp"
#include "core/core.hpp"

#include <llarm/llarm-asm.hpp>
#include <llarm/shared/types.hpp>

struct CPU {
    SETTINGS settings;
    VIC vic;
    UART uart;
    SP804 timer;
    RAM ram;
    CORE core;

    CPU(std::vector<u8> &binary);

    void run(const bool is_headless = false);
};