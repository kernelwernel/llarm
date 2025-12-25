#include "../generators.hpp"
#include "shared/out.hpp"

u32 generators::q_instructions(const arm_id id, const arguments &args) {
    u32 binary = 0b0000'0001'0000'0000'0000'0000'0101'0000;

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 12, 15, args.first_reg);
    llarm::util::swap_bits(binary, 0, 3, args.second_reg);
    llarm::util::swap_bits(binary, 16, 19, args.third_reg);

    u8 opcode = 0;

    switch (id) {
        case arm_id::QADD: opcode = 0b00; break;
        case arm_id::QDADD: opcode = 0b10; break;
        case arm_id::QSUB: opcode = 0b01; break;
        case arm_id::QDSUB: opcode = 0b11; break;
        default: llarm::out::dev_error("Invalid configuration to DSP Q instruction pattern generation");
    }

    llarm::util::swap_bits(binary, 21, 22, opcode);    

    return binary;
}


u32 generators::mul_instructions(const arm_id id, const arguments &args) {
    u32 binary = 0b0000'0000'1000'0000'0000'0000'1001'0000;

    if (args.has_S) {
        llarm::util::modify_bit(binary, 20, true);
    }

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 12, 15, args.first_reg);
    llarm::util::swap_bits(binary, 16, 19, args.second_reg);
    llarm::util::swap_bits(binary, 0, 3, args.third_reg);
    llarm::util::swap_bits(binary, 8, 11, args.fourth_reg);

    u8 opcode = 0;

    switch (id) {
        case arm_id::SMLAL: opcode = 0b11; break;
        case arm_id::SMULL: opcode = 0b10; break;
        case arm_id::UMLAL: opcode = 0b01; break;
        case arm_id::UMULL: opcode = 0b00; break;
        default: llarm::out::dev_error("Invalid configuration to u64 multiply instruction pattern generation");
    }

    llarm::util::swap_bits(binary, 21, 22, opcode);

    return binary;
}


u32 generators::dsp_mul_instructions(const arm_id id, const arguments &args) {
    u32 binary = 0;

    llarm::util::modify_bit(binary, 7, true);
    llarm::util::modify_bit(binary, 24, true);

    llarm::util::swap_bits(binary, 28, 31, args.cond);

    switch (id) {
        case arm_id::SMLALXY:
            llarm::util::swap_bits(binary, 12, 15, args.first_reg);
            llarm::util::swap_bits(binary, 16, 19, args.second_reg);
            llarm::util::swap_bits(binary, 0, 3, args.third_reg);
            llarm::util::swap_bits(binary, 8, 11, args.fourth_reg);
            break;

        case arm_id::SMLAXY: 
        case arm_id::SMLAWY: 
            llarm::util::swap_bits(binary, 12, 15, args.fourth_reg);
            // no break on purpose

        case arm_id::SMULXY: 
        case arm_id::SMULWY: 
            llarm::util::swap_bits(binary, 16, 19, args.first_reg);
            llarm::util::swap_bits(binary, 0, 3, args.second_reg);
            llarm::util::swap_bits(binary, 8, 11, args.third_reg);
            break;

        default: llarm::out::dev_error("Invalid configuration to u64 multiply instruction pattern generation");
    }

    u8 bits_22_21 = 0;
    bool has_x = false;
    bool has_y = false;

    switch (id) {
        case arm_id::SMLAXY: 
            has_x = true;
            has_y = true;
            break;

        case arm_id::SMLALXY: 
            bits_22_21 = 0b10;
            has_x = true;
            has_y = true;
            break;

        case arm_id::SMLAWY: 
            bits_22_21 = 0b01;
            has_y = true;
            break;

        case arm_id::SMULXY: 
            bits_22_21 = 0b11;
            has_x = true;
            has_y = true;
            break;

        case arm_id::SMULWY: 
            bits_22_21 = 0b01;
            has_y = true;
            llarm::util::modify_bit(binary, 5, true);
            break;

        default: llarm::out::dev_error("Invalid configuration to u64 multiply instruction pattern generation");
    }

    if (has_y && args.y_char == 'T') {
        llarm::util::modify_bit(binary, 6, true);
    }

    if (has_x && args.x_char == 'T') {
        llarm::util::modify_bit(binary, 5, true);
    }

    llarm::util::swap_bits(binary, 21, 22, bits_22_21);

    return binary;
}