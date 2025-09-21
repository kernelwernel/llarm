#include "../params.hpp"
#include "patterns.hpp"
#include "../random.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"


#include <llarm-asm/llarm-asm.hpp>


u32 patterns::logic_arithmetic(const param_struct params) {
    const u16 shifter = random::generate<u16>(0, 11);

    const bool I = random::generate_bit();
    const bool S = random::generate_bit();

    u8 Rn = 0;
    u8 Rd = 0;

    if (params.random_regs) {
        Rn = random::generate<u8>(16, 19);
        Rd = random::generate<u8>(12, 15);
    }

    u32 instruction = 0;

    shared::util::swap_bits(instruction, 28, 31, params.cond);
    shared::util::swap_bits(instruction, 16, 19, Rn);
    shared::util::swap_bits(instruction, 12, 15, Rd);
    shared::util::swap_bits(instruction, 0, 11, shifter);
    shared::util::modify_bit(instruction, 25, I);
    shared::util::modify_bit(instruction, 20, S);

    return instruction;
}


u32 patterns::memory(const param_struct params) {

}


u32 patterns::load_store(const param_struct params, const u8 bits_27_25) {
    const u16 reg_list = random::generate<u16>(0, 15);

    const bool I = random::generate_bit();
    const bool S = random::generate_bit();

    u8 Rn = 0;

    if (params.random_regs) {
        Rn = random::generate<u8>(16, 19);
    }

    u32 instruction = 0;

    shared::util::swap_bits(instruction, 28, 31, params.cond);
    shared::util::swap_bits(instruction, 16, 19, Rn);
    shared::util::swap_bits(instruction, 0, 15, reg_list);
    shared::util::modify_bit(instruction, 25, I);
    shared::util::modify_bit(instruction, 20, S);

    return instruction;
}