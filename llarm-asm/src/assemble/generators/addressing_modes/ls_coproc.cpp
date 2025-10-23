#include "../generators.hpp"

#include "shared/util.hpp"
#include "shared/out.hpp"

// format: <opcode>{<cond>}{L} <coproc>, <CRd>,<addressing_mode>
u32 generators::ls_coproc_instruction(const id::arm id, const arguments &args) {
    u32 binary = 0;

    // all coprocessor instructions
    shared::util::modify_bit(binary, 27, true);
    shared::util::modify_bit(binary, 26, true);

    shared::util::swap_bits(binary, 28, 31, args.cond);
    shared::util::swap_bits(binary, 16, 19, args.first_reg);
    shared::util::swap_bits(binary, 12, 15, args.first_CR_reg);
    shared::util::swap_bits(binary, 8, 11, args.coproc);
    shared::util::swap_bits(binary, 0, 7, args.first_int);

    constexpr u8 P = 24;
    constexpr u8 U = 23;
    constexpr u8 N = 22;
    constexpr u8 W = 21;
    constexpr u8 L = 20;

    if (args.has_minus() == false) {
        shared::util::modify_bit(binary, U, true);
    }

    switch (id) {
        case id::arm::LDC:
            shared::util::modify_bit(binary, L, true);
            // no break on purpose

        case id::arm::STC:
            shared::util::modify_bit(binary, 27, true);
            shared::util::modify_bit(binary, 26, true);
            break;

        default: shared::out::dev_error("Invalid configuration to load/store coprocessor instruction pattern generation");
    }

    switch (args.shifter) {
        case shifter_enum::LS_COPROC_IMM:
            shared::util::swap_bits(binary, 0, 7, args.first_int);
            shared::util::modify_bit(binary, P, true);
            break;

        case shifter_enum::LS_COPROC_IMM_PRE:
            shared::util::swap_bits(binary, 0, 7, args.first_int);
            shared::util::modify_bit(binary, P, true);
            shared::util::modify_bit(binary, W, true);
            break;

        case shifter_enum::LS_COPROC_IMM_POST:
            shared::util::modify_bit(binary, W, true);
            break;

        case shifter_enum::LS_COPROC_UNINDEXED: 
            shared::util::modify_bit(binary, U, true);
            break;

        default: shared::out::dev_error("Invalid shifter configuration to load/store coprocessor instruction pattern generation");
    }

    return binary;
}