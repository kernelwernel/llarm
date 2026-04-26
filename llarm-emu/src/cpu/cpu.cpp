#include "cpu.hpp"

#include "../settings.hpp"
#include "../ram/ram.hpp"
#include "core/core.hpp"

#include <llarm/llarm-asm.hpp>
#include <llarm/shared/types.hpp>


CPU::CPU(std::vector<u8> &binary) :
    settings(default_settings()),
    vic(settings),
    uart(settings, (settings.uart_base != 0) ? settings.uart_base : 0x10000000U),
    ram(binary, settings, vic, uart),
    core(settings, ram, vic, uart)
{

}

void CPU::run(const bool is_headless) {
    core.initialise(is_headless);
}