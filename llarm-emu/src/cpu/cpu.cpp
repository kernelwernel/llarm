#include "cpu.hpp"

#include "../settings.hpp"
#include "memory/ram.hpp"
#include "core/core.hpp"

#include <llarm/llarm-asm.hpp>
#include <llarm/shared/types.hpp>


void CPU::initialise(const std::vector<u8> &binary) {

}

CPU::CPU(const std::vector<u8> &binary) :
    core(binary, settings, ram),
    settings(default_settings()), 
    ram()
{

}