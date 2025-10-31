#include "../generators.hpp"
#include "shared/out.hpp"

u32 generators::q_instructions(const id::arm id, const arguments &args) {
    u32 binary = 0b0000'0001'0000'0000'0000'0000'0101'0000;

    shared::util::swap_bits(binary, 28, 31, args.cond);
    shared::util::swap_bits(binary, 12, 15, args.first_reg);
    shared::util::swap_bits(binary, 0, 3, args.second_reg);
    shared::util::swap_bits(binary, 16, 19, args.third_reg);

    u8 opcode = 0;

    switch (id) {
        case id::arm::QADD: opcode = 0b00; break;
        case id::arm::QDADD: opcode = 0b10; break;
        case id::arm::QSUB: opcode = 0b01; break;
        case id::arm::QDSUB: opcode = 0b11; break;
        default: shared::out::dev_error("Invalid configuration to DSP Q instruction pattern generation");
    }

    shared::util::swap_bits(binary, 21, 22, opcode);    

    return binary;
}


u32 generators::mul_instructions(const id::arm id, const arguments &args) {
    u32 binary = 0b0000'0000'1000'0000'0000'0000'1001'0000;

    if (args.has_S()) {
        shared::util::modify_bit(binary, 20, true);
    }

    shared::util::swap_bits(binary, 28, 31, args.cond);
    shared::util::swap_bits(binary, 12, 15, args.first_reg);
    shared::util::swap_bits(binary, 16, 19, args.second_reg);
    shared::util::swap_bits(binary, 0, 3, args.third_reg);
    shared::util::swap_bits(binary, 8, 11, args.fourth_reg);

    u8 opcode = 0;

    switch (id) {
        case id::arm::SMLAL: opcode = 0b11; break;
        case id::arm::SMULL: opcode = 0b10; break;
        case id::arm::UMLAL: opcode = 0b01; break;
        case id::arm::UMULL: opcode = 0b00; break;
        default: shared::out::dev_error("Invalid configuration to u64 multiply instruction pattern generation");
    }

    shared::util::swap_bits(binary, 21, 22, opcode);

    return binary;
}


u32 generators::dsp_mul_instructions(const id::arm id, const arguments &args) {
    u32 binary = 0;

    shared::util::modify_bit(binary, 7, true);
    shared::util::modify_bit(binary, 24, true);

    shared::util::swap_bits(binary, 28, 31, args.cond);

    switch (id) {
        case id::arm::SMLALXY:
            shared::util::swap_bits(binary, 12, 15, args.first_reg);
            shared::util::swap_bits(binary, 16, 19, args.second_reg);
            shared::util::swap_bits(binary, 0, 3, args.third_reg);
            shared::util::swap_bits(binary, 8, 11, args.fourth_reg);
            break;

        case id::arm::SMLAXY: 
        case id::arm::SMLAWY: 
            shared::util::swap_bits(binary, 12, 15, args.fourth_reg);
            // no break on purpose

        case id::arm::SMULXY: 
        case id::arm::SMULWY: 
            shared::util::swap_bits(binary, 16, 19, args.first_reg);
            shared::util::swap_bits(binary, 0, 3, args.second_reg);
            shared::util::swap_bits(binary, 8, 11, args.third_reg);
            break;

        default: shared::out::dev_error("Invalid configuration to u64 multiply instruction pattern generation");
    }

    u8 bits_22_21 = 0;
    bool has_x = false;
    bool has_y = false;

    switch (id) {
        case id::arm::SMLAXY: 
            has_x = true;
            has_y = true;
            break;

        case id::arm::SMLALXY: 
            bits_22_21 = 0b10;
            has_x = true;
            has_y = true;
            break;

        case id::arm::SMLAWY: 
            bits_22_21 = 0b01;
            has_y = true;
            break;

        case id::arm::SMULXY: 
            bits_22_21 = 0b11;
            has_x = true;
            has_y = true;
            break;

        case id::arm::SMULWY: 
            bits_22_21 = 0b01;
            has_y = true;
            shared::util::modify_bit(binary, 5, true);
            break;

        default: shared::out::dev_error("Invalid configuration to u64 multiply instruction pattern generation");
    }

    if (has_y && args.has_y()) {
        shared::util::modify_bit(binary, 6, true);
    }

    if (has_x && args.has_x()) {
        shared::util::modify_bit(binary, 5, true);
    }

    shared::util::swap_bits(binary, 21, 22, bits_22_21);

    return binary;
}