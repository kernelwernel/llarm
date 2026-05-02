#include "../generators.hpp"
#include <llarm/shared/out.hpp>
#include <llarm/shared/util.hpp>

u32 generators::q_instructions(const arm_id id, const operand_struct& args) {
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


u32 generators::mul_instructions(const arm_id id, const operand_struct& args) {
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


u32 generators::dsp_mul_instructions(const arm_id id, const operand_struct& args) {
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
            [[fallthrough]];

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


u32 generators::saturate_instructions(const arm_id id, const operand_struct& args) {
    u8 bits_27_20 = 0;
    u8 bits_4_7 = 0;

    switch (id) {
        case arm_id::USUB16: bits_27_20 = 0b0110'0101; bits_4_7 = 0b0111; break;
        case arm_id::USUB8: bits_27_20 = 0b0110'0101; bits_4_7 = 0b1111; break;
        case arm_id::USUBADDX: bits_27_20 = 0b0110'0101; bits_4_7 = 0b0101; break;
        case arm_id::UADD16: bits_27_20 = 0b0110'0101; bits_4_7 = 0b0001; break;
        case arm_id::UADD8: bits_27_20 = 0b0110'0101; bits_4_7 = 0b1001; break;
        case arm_id::UADDSUBX: bits_27_20 = 0b0110'0101; bits_4_7 = 0b0011; break;
        case arm_id::UHADD16: bits_27_20 = 0b0110'0111; bits_4_7 = 0b0001; break;
        case arm_id::UHADD8: bits_27_20 = 0b0110'0111; bits_4_7 = 0b1001; break;
        case arm_id::UHADDSUBX: bits_27_20 = 0b0110'0111; bits_4_7 = 0b0011; break;
        case arm_id::UHSUB16: bits_27_20 = 0b0110'0111; bits_4_7 = 0b0111; break;
        case arm_id::UHSUB8: bits_27_20 = 0b0110'0111; bits_4_7 = 0b1111; break;
        case arm_id::UHSUBADDX: bits_27_20 = 0b0110'0111; bits_4_7 = 0b0101; break;
        case arm_id::UQADD16: bits_27_20 = 0b0110'0110; bits_4_7 = 0b0001; break;
        case arm_id::UQADD8: bits_27_20 = 0b0110'0110; bits_4_7 = 0b1001; break;
        case arm_id::UQADDSUBX: bits_27_20 = 0b0110'0110; bits_4_7 = 0b0011; break;
        case arm_id::UQSUB16: bits_27_20 = 0b0110'0110; bits_4_7 = 0b0111; break;
        case arm_id::UQSUB8: bits_27_20 = 0b0110'0110; bits_4_7 = 0b1111; break;
        case arm_id::UQSUBADDX: bits_27_20 = 0b0110'0110; bits_4_7 = 0b0101; break;
        case arm_id::QADD16: bits_27_20 = 0b0110'0010; bits_4_7 = 0b0001; break;
        case arm_id::QADD8: bits_27_20 = 0b0110'0010; bits_4_7 = 0b1001; break;
        case arm_id::QADDSUBX: bits_27_20 = 0b0110'0010; bits_4_7 = 0b0011; break;
        case arm_id::QSUB16: bits_27_20 = 0b0110'0010; bits_4_7 = 0b0111; break;
        case arm_id::QSUB8: bits_27_20 = 0b0110'0010; bits_4_7 = 0b1111; break;
        case arm_id::QSUBADDX: bits_27_20 = 0b0110'0010; bits_4_7 = 0b0101; break;
        case arm_id::SADD16: bits_27_20 = 0b0110'0001; bits_4_7 = 0b0001; break;
        case arm_id::SADD8: bits_27_20 = 0b0110'0001; bits_4_7 = 0b1001; break;
        case arm_id::SADDSUBX: bits_27_20 = 0b0110'0001; bits_4_7 = 0b0011; break;
        case arm_id::SEL: bits_27_20 = 0b0110'1000; bits_4_7 = 0b1011; break;
        case arm_id::SHADD16: bits_27_20 = 0b0110'0011; bits_4_7 = 0b0001; break;
        case arm_id::SHADD8: bits_27_20 = 0b0110'0011; bits_4_7 = 0b1001; break;
        case arm_id::SHADDSUBX: bits_27_20 = 0b0110'0011; bits_4_7 = 0b0011; break;
        case arm_id::SHSUB16: bits_27_20 = 0b0110'0011; bits_4_7 = 0b0111; break;
        case arm_id::SHSUB8: bits_27_20 = 0b0110'0011; bits_4_7 = 0b1111; break;
        case arm_id::SHSUBADDX: bits_27_20 = 0b0110'0011; bits_4_7 = 0b0101; break;
        case arm_id::SSUB16: bits_27_20 = 0b0110'0001; bits_4_7 = 0b0111; break;
        case arm_id::SSUB8: bits_27_20 = 0b0110'0001; bits_4_7 = 0b1111; break;
        case arm_id::SSUBADDX: bits_27_20 = 0b0110'0001; bits_4_7 = 0b0101; break;
        default: llarm::out::dev_error("Invalid configuration to saturate instruction pattern generation");
    }

    u32 binary = 0;

    llarm::util::swap_bits(binary, 20, 27, bits_27_20);
    llarm::util::swap_bits(binary, 20, 27, bits_4_7);

    llarm::util::swap_bits(binary, 12, 15, args.first_reg); // Rd
    llarm::util::swap_bits(binary, 16, 19, args.second_reg); // Rn
    llarm::util::swap_bits(binary, 0, 3, args.third_reg); // Rm

    llarm::util::swap_bits(binary, 28, 31, args.cond);

    return binary;
}


u32 generators::ssat_instruction(const arm_id id, const operand_struct& args) {
    if (id == arm_id::SSAT16) {
        u32 binary = 0b0000'0110'1010'0000'0000'1111'0011'0000;
        llarm::util::swap_bits(binary, 28, 31, args.cond);
        llarm::util::swap_bits(binary, 16, 19, args.first_int - 1); // sat_imm
        llarm::util::swap_bits(binary, 12, 15, args.first_reg);     // Rd
        llarm::util::swap_bits(binary, 0, 3, args.second_reg);      // Rm
        return binary;
    }

    u32 binary = 0b0000'0110'1010'0000'0000'0000'0001'0000;
    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 16, 20, args.first_int - 1);                   // sat_imm
    llarm::util::swap_bits(binary, 12, 15, args.first_reg);                        // Rd
    llarm::util::swap_bits(binary, 7, 11, args.second_int);                        // shift_imm
    llarm::util::modify_bit(binary, 6, args.shifter == shifter_id::USAT_ASR);     // sh
    llarm::util::swap_bits(binary, 0, 3, args.second_reg);                         // Rm
    return binary;
}


u32 generators::pkh_instruction(const arm_id id, const operand_struct& args) {
    // Fixed bits: 27-25=011, 23=1, 5=0, 4=1; bit 6 (T) = 1 for PKHTB
    u32 binary = 0;

    llarm::util::swap_bits(binary, 20, 27, 0b0110'1000);
    llarm::util::modify_bit(binary, 4, true);

    llarm::util::modify_bit(binary, 6, id == arm_id::PKHTB);

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 16, 19, args.second_reg); // Rn
    llarm::util::swap_bits(binary, 12, 15, args.first_reg); // Rd
    llarm::util::swap_bits(binary, 7, 11, args.first_int); // shift_imm
    llarm::util::swap_bits(binary, 0, 3, args.third_reg); // Rm

    return binary;
}


u32 generators::signed_mul_instructions(const arm_id id, const operand_struct& args) {
    u32 binary = 0;

    u8 bits_20_27 = 0;
    u8 bits_4_7 = 0;

    switch (id) {
        case arm_id::SMMLS: bits_20_27 = 0b0111'0101; bits_4_7 = 0b1101; break;
        case arm_id::SMMLA: bits_20_27 = 0b0111'0101; bits_4_7 = 0b0001; break;
        case arm_id::SMLSD: bits_20_27 = 0b0111'0000; bits_4_7 = 0b0101; break;
        case arm_id::SMLAD: bits_20_27 = 0b0111'0000; bits_4_7 = 0b0001; break;
        default: llarm::out::dev_error("Invalid configuration to signed multiply instruction pattern generation");
    }

    llarm::util::swap_bits(binary, 28, 31, args.cond);

    llarm::util::swap_bits(binary, 20, 27, bits_20_27);
    llarm::util::swap_bits(binary, 4, 7, bits_4_7);

    llarm::util::swap_bits(binary, 16, 19, args.first_reg); // Rd
    llarm::util::swap_bits(binary, 0, 3, args.second_reg); // Rm
    llarm::util::swap_bits(binary, 8, 11, args.third_reg); // Rs
    llarm::util::swap_bits(binary, 12, 15, args.fourth_reg); // Rn

    if (id == arm_id::SMMLS || id == arm_id::SMMLA) {
        llarm::util::modify_bit(binary, 5, args.has_R);
    } else if (id == arm_id::SMLSD || id == arm_id::SMLAD) {
        llarm::util::modify_bit(binary, 5, args.has_X);
    }

    return binary;
}


u32 generators::signed_mul_1111_instructions(const arm_id id, const operand_struct& args) {
    u32 binary = 0;

    u8 bits_20_27 = 0;
    u8 bits_4_7 = 0;

    switch (id) {
        case arm_id::SMUSD: bits_20_27 = 0b0111'0000; bits_4_7 = 0b0101; break;
        case arm_id::SMUAD: bits_20_27 = 0b0111'0000; bits_4_7 = 0b0001; break;
        case arm_id::SMMUL: bits_20_27 = 0b0111'0101; bits_4_7 = 0b0001; break;
        default: llarm::out::dev_error("Invalid configuration to signed multiply instruction pattern generation");
    }

    llarm::util::swap_bits(binary, 28, 31, args.cond);

    llarm::util::swap_bits(binary, 20, 27, bits_20_27);
    llarm::util::swap_bits(binary, 4, 7, bits_4_7);

    llarm::util::swap_bits(binary, 16, 19, args.first_reg); // Rd
    llarm::util::swap_bits(binary, 0, 3, args.second_reg); // Rm
    llarm::util::swap_bits(binary, 8, 11, args.third_reg); // Rs
    llarm::util::swap_bits(binary, 12, 15, 0b1111);

    llarm::util::modify_bit(binary, 5, (args.has_X || args.has_R));

    return binary;
}


u32 generators::sign_extend_rotate_instructions(const arm_id id, const operand_struct& args) {
    u32 binary = 0;

    u8 bits_20_27 = 0;
    u8 bits_4_7 = 0;

    switch (id) {
        case arm_id::SXTAB: bits_20_27 = 0b0110'1010; bits_4_7 = 0b0111; break;
        case arm_id::SXTAB16: bits_20_27 = 0b0110'1000; bits_4_7 = 0b0111; break;
        case arm_id::SXTAH: bits_20_27 = 0b0110'1011; bits_4_7 = 0b0111; break;
        case arm_id::UXTAB: bits_20_27 = 0b0110'1110; bits_4_7 = 0b0111; break;
        case arm_id::UXTAB16: bits_20_27 = 0b0110'1100; bits_4_7 = 0b0111; break;
        case arm_id::UXTAH: bits_20_27 = 0b0110'1111; bits_4_7 = 0b0111; break;
        default: llarm::out::dev_error("Invalid configuration to sign extend rotate instruction pattern generation");
    }

    llarm::util::swap_bits(binary, 28, 31, args.cond);

    llarm::util::swap_bits(binary, 20, 27, bits_20_27);
    llarm::util::swap_bits(binary, 4, 7, bits_4_7);

    llarm::util::swap_bits(binary, 12, 15, args.first_reg); // Rd
    llarm::util::swap_bits(binary, 16, 19, args.second_reg); // Rn
    llarm::util::swap_bits(binary, 0, 3, args.third_reg); // Rm

    u8 bits_10_11 = 0;

    switch (args.first_int) {
        case 0: bits_10_11 = 0b00; break;
        case 8: bits_10_11 = 0b01; break;
        case 16: bits_10_11 = 0b10; break;
        case 24: bits_10_11 = 0b11; break;
    }

    llarm::util::swap_bits(binary, 10, 11, bits_10_11);

    return binary;
}


u32 generators::sign_extend_rotate_no_Rn_instructions(const arm_id id, const operand_struct& args) {
    u32 binary = 0;

    u16 bits_16_27 = 0;

    switch (id) {
        case arm_id::SXTB: bits_16_27 = 0b0110'1010'1111; break;
        case arm_id::SXTB16: bits_16_27 = 0b0110'1000'1111; break;
        case arm_id::SXTH: bits_16_27 = 0b0110'1011'1111; break;
        case arm_id::UXTB: bits_16_27 = 0b0110'1110'1111; break;
        case arm_id::UXTB16: bits_16_27 = 0b0110'1100'1111; break;
        case arm_id::UXTH: bits_16_27 = 0b0110'1111'1111; break;
        default: llarm::out::dev_error("Invalid configuration to signed multiply no Rn instruction pattern generation");
    }

    llarm::util::swap_bits(binary, 28, 31, args.cond);

    llarm::util::swap_bits(binary, 16, 27, bits_16_27);
    llarm::util::swap_bits(binary, 4, 7, 0b0111); // all instructions have the same pattern here

    llarm::util::swap_bits(binary, 12, 15, args.first_reg); // Rd
    llarm::util::swap_bits(binary, 0, 3, args.second_reg); // Rm

    u8 bits_10_11 = 0;

    switch (args.first_int) {
        case 0: bits_10_11 = 0b00; break;
        case 8: bits_10_11 = 0b01; break;
        case 16: bits_10_11 = 0b10; break;
        case 24: bits_10_11 = 0b11; break;
    }

    llarm::util::swap_bits(binary, 10, 11, bits_10_11);

    return binary;
}


u32 generators::rev_instructions(const arm_id id, const operand_struct& args) {
    u32 binary = 0;

    u16 bits_20_27 = 0;
    u16 bits_4_7 = 0;

    switch (id) {
        case arm_id::REV: bits_20_27 = 0b0110'1011; bits_4_7 = 0b0011; break;
        case arm_id::REV16: bits_20_27 = 0b0110'1011; bits_4_7 = 0b1011; break;
        case arm_id::REVSH: bits_20_27 = 0b0110'1111; bits_4_7 = 0b1011; break;
        default: llarm::out::dev_error("Invalid configuration to rev instruction pattern generation");
    }

    llarm::util::swap_bits(binary, 28, 31, args.cond);

    llarm::util::swap_bits(binary, 20, 27, bits_20_27);
    llarm::util::swap_bits(binary, 4, 7, bits_4_7);

    llarm::util::swap_bits(binary, 12, 15, args.first_reg); // Rd
    llarm::util::swap_bits(binary, 0, 3, args.second_reg); // Rm

    return binary;
}


u32 generators::mul_high_low_instructions(const arm_id id, const operand_struct& args) {
    u32 binary = 0;

    u16 bits_20_27 = 0;
    u16 bits_4_7 = 0;

    switch (id) {
        case arm_id::SMLALD: bits_20_27 = 0b0111'0100; bits_4_7 = 0001; break;
        case arm_id::SMLSLD: bits_20_27 = 0b0111'0100; bits_4_7 = 0b0101; break;
        case arm_id::UMAAL: bits_20_27 = 0b0000'0100; bits_4_7 = 0b1001; break;
        default: llarm::out::dev_error("Invalid configuration to multiple high low instruction pattern generation");
    }

    llarm::util::swap_bits(binary, 20, 27, bits_20_27);
    llarm::util::swap_bits(binary, 4, 7, bits_4_7);

    llarm::util::swap_bits(binary, 28, 31, args.cond);

    llarm::util::swap_bits(binary, 12, 15, args.first_reg);
    llarm::util::swap_bits(binary, 16, 19, args.second_reg);
    llarm::util::swap_bits(binary, 0, 3, args.third_reg);
    llarm::util::swap_bits(binary, 8, 11, args.fourth_reg);

    return binary;
}
