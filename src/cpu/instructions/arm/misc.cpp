#include "cpu/instructions/instructions.hpp"
#include "types.hpp"
#include "utility.hpp"
#include <iostream>

void instructions::arm::misc::NOP([[maybe_unused]] const arm_code_t &code, [[maybe_unused]] REGISTERS& reg) noexcept {
    return;
}
