#include "cpu.hpp"

#include "../settings.hpp"
#include "../ram/ram.hpp"
#include "core/core.hpp"

#include <llarm/llarm-asm.hpp>
#include <llarm/shared/types.hpp>


CPU::CPU(std::vector<u8> &binary) :
    settings(default_settings()),
    vic(settings),
    ram(binary, settings, vic),
    core(settings, ram, vic)
{

}

void CPU::run(const bool is_headless) {
    core.initialise(is_headless);
}