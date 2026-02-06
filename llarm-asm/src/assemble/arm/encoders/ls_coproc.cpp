#include "../generators.hpp"

#include <llarm/shared/util.hpp>
#include <llarm/shared/out.hpp>

// format: <opcode>{<cond>}{L} <coproc>, <CRd>,<addressing_mode>
u32 generators::ls_coproc_instruction(const arm_id id, const operand_struct &args) {
    u32 binary = 0;

    // all coprocessor instructions
    llarm::util::modify_bit(binary, 27, true);
    llarm::util::modify_bit(binary, 26, true);

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 16, 19, args.first_reg);
    llarm::util::swap_bits(binary, 12, 15, args.first_CR_reg);
    llarm::util::swap_bits(binary, 8, 11, args.coproc);
    llarm::util::swap_bits(binary, 0, 7, args.first_int);

    constexpr u8 P = 24;
    constexpr u8 U = 23;
    constexpr u8 N = 22;
    constexpr u8 W = 21;
    constexpr u8 L = 20;

    if (args.has_minus == false) {
        llarm::util::modify_bit(binary, U, true);
    }

    switch (id) {
        case arm_id::LDC2:
        case arm_id::LDC:
            if (args.has_L) {
                llarm::util::modify_bit(binary, N, true);
            }

            llarm::util::modify_bit(binary, L, true);
            [[fallthrough]]; // no break on purpose

        case arm_id::STC2:
        case arm_id::STC:
            llarm::util::modify_bit(binary, 27, true);
            llarm::util::modify_bit(binary, 26, true);
            break;

        default: llarm::out::dev_error("Invalid configuration to load/store coprocessor instruction pattern generation");
    }

    switch (args.shifter) {
        case shifter_id::LS_COPROC_IMM:
            llarm::util::swap_bits(binary, 0, 7, args.first_int);
            llarm::util::modify_bit(binary, P, true);
            break;

        case shifter_id::LS_COPROC_IMM_PRE:
            llarm::util::swap_bits(binary, 0, 7, args.first_int);
            llarm::util::modify_bit(binary, P, true);
            llarm::util::modify_bit(binary, W, true);
            break;

        case shifter_id::LS_COPROC_IMM_POST:
            llarm::util::modify_bit(binary, W, true);
            break;

        case shifter_id::LS_COPROC_UNINDEXED: 
            llarm::util::modify_bit(binary, U, true);
            break;

        default: llarm::out::dev_error("Invalid shifter configuration to load/store coprocessor instruction pattern generation");
    }

    return binary;
}