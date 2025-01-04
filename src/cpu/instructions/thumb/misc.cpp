#include "cpu/instructions/instructions.hpp"
#include "types.hpp"
#include "utility.hpp"
#include <iostream>

void instructions::thumb::misc::NOP([[maybe_unused]] const thumb_code_t &code, [[maybe_unused]] REGISTERS& reg) noexcept {
    return;
}

// TODO
void instructions::thumb::misc::BKPT(const thumb_code_t &code, REGISTERS& reg) {
    const u8 immed_8 = util::bit_fetcher<u8>(code, 0, 7);
    // CONTINUE
}

// TODO
void instructions::thumb::misc::SWI(const thumb_code_t &code, REGISTERS& reg) {
    const u8 immed_8 = util::bit_fetcher<u8>(code, 0, 7);
    // CONTINUE
}