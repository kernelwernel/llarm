#include "cpu.hpp"

#include "../settings.hpp"
#include "memory/ram.hpp"
#include "core/core.hpp"

#include <llarm/llarm-asm.hpp>
#include <llarm/shared/types.hpp>


CPU::CPU(const std::vector<u8> &binary) :
    settings(default_settings()),
    ram(binary),
    core(settings, ram)
{

}

void CPU::run(const bool is_headless) {
    core.initialise(is_headless);
}