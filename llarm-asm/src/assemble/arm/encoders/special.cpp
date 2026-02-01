#include "../generators.hpp"
#include "shared/util.hpp"


u32 generators::mul(const operand_struct &args) {
    u32 binary = 0;

    if (args.has_S) {
        llarm::util::modify_bit(binary, 20, true);
    }

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 16, 19, args.first_reg);
    llarm::util::swap_bits(binary, 0, 3, args.second_reg);
    llarm::util::swap_bits(binary, 8, 11, args.third_reg);

    return binary;
}


u32 generators::swp(const operand_struct &args) {
    u32 binary = 0;

    llarm::util::modify_bit(binary, 24, true);
    llarm::util::modify_bit(binary, 7, true);
    llarm::util::modify_bit(binary, 4, true);

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 12, 15, args.first_reg);
    llarm::util::swap_bits(binary, 0, 3, args.second_reg);
    llarm::util::swap_bits(binary, 16, 19, args.third_reg);

    return binary;
}


u32 generators::swpb(const operand_struct &args) {
    u32 binary = 0;

    llarm::util::modify_bit(binary, 24, true);
    llarm::util::modify_bit(binary, 22, true);
    llarm::util::modify_bit(binary, 7, true);
    llarm::util::modify_bit(binary, 4, true);

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 12, 15, args.first_reg);
    llarm::util::swap_bits(binary, 0, 3, args.second_reg);
    llarm::util::swap_bits(binary, 16, 19, args.third_reg);

    return binary;
}


u32 generators::mla(const operand_struct &args) {
    u32 binary = 0;

    llarm::util::modify_bit(binary, 21, true);
    llarm::util::modify_bit(binary, 7, true);
    llarm::util::modify_bit(binary, 4, true);

    if (args.has_S) {
        llarm::util::modify_bit(binary, 20, true);
    }

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 16, 19, args.first_reg);
    llarm::util::swap_bits(binary, 0, 3, args.second_reg);
    llarm::util::swap_bits(binary, 8, 11, args.third_reg);
    llarm::util::swap_bits(binary, 12, 15, args.fourth_reg);

    return binary;
}


u32 generators::mrs(const operand_struct &args) {
    u32 binary = 0;

    llarm::util::modify_bit(binary, 24, true);

    if (args.has_spsr) {
        llarm::util::modify_bit(binary, 22, true);
    }

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 12, 15, args.first_reg);
    llarm::util::swap_bits(binary, 16, 19, 0b1111);

    return binary;
}


u32 generators::msr_imm(const operand_struct &args) {
    u32 binary = 0;

    llarm::util::modify_bit(binary, 25, true);
    llarm::util::modify_bit(binary, 24, true);
    llarm::util::modify_bit(binary, 21, true);

    if (args.has_spsr) {
        llarm::util::modify_bit(binary, 22, true);
    }

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 16, 19, args.PSR_field_mask);
    llarm::util::swap_bits(binary, 12, 15, 0b1111);

    encode_imm(binary, args.first_int);

    return binary;
}


u32 generators::msr_reg(const operand_struct &args) {
    u32 binary = 0;

    llarm::util::modify_bit(binary, 24, true);
    llarm::util::modify_bit(binary, 21, true);

    if (args.has_spsr) {
        llarm::util::modify_bit(binary, 22, true);
    }

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 16, 19, args.PSR_field_mask);
    llarm::util::swap_bits(binary, 12, 15, 0b1111);
    llarm::util::swap_bits(binary, 0, 3, args.first_reg);

    return binary;
}


u32 generators::swi(const operand_struct &args) {
    u32 binary = 0;

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 24, 27, 0b1111);
    llarm::util::swap_bits(binary, 0, 23, args.first_int);

    return binary;
}


u32 generators::clz(const operand_struct &args) {
    u32 binary = 0;

    llarm::util::modify_bit(binary, 24, true);
    llarm::util::modify_bit(binary, 22, true);
    llarm::util::modify_bit(binary, 21, true);
    llarm::util::modify_bit(binary, 4, true);

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 16, 19, 0b1111);
    llarm::util::swap_bits(binary, 12, 15, args.first_reg);
    llarm::util::swap_bits(binary, 8, 11, 0b1111);
    llarm::util::swap_bits(binary, 0, 3, args.second_reg);

    return binary;
}


u32 generators::mcr(const operand_struct &args) {
    u32 binary = 0;

    llarm::util::modify_bit(binary, 27, true);
    llarm::util::modify_bit(binary, 26, true);
    llarm::util::modify_bit(binary, 25, true);
    llarm::util::modify_bit(binary, 4, true);

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 8, 11, args.coproc);
    llarm::util::swap_bits(binary, 21, 23, args.first_int);
    llarm::util::swap_bits(binary, 12, 15, args.first_reg);
    llarm::util::swap_bits(binary, 16, 19, args.first_CR_reg);
    llarm::util::swap_bits(binary, 0, 3, args.second_CR_reg);
    llarm::util::swap_bits(binary, 5, 7, args.second_int);

    return binary;
}


u32 generators::mrc(const operand_struct &args) {
    u32 binary = mcr(args);

    llarm::util::modify_bit(binary, 20, true);

    return binary;
}


u32 generators::cdp(const operand_struct &args) {
    u32 binary = 0;

    llarm::util::modify_bit(binary, 27, true);
    llarm::util::modify_bit(binary, 26, true);
    llarm::util::modify_bit(binary, 25, true);

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 8, 11, args.coproc);
    llarm::util::swap_bits(binary, 20, 23, args.first_int);
    llarm::util::swap_bits(binary, 12, 15, args.first_CR_reg);
    llarm::util::swap_bits(binary, 16, 19, args.second_CR_reg);
    llarm::util::swap_bits(binary, 0, 3, args.third_CR_reg);
    llarm::util::swap_bits(binary, 5, 7, args.second_int);

    return binary;
}


u32 generators::b(const operand_struct &args) {
    u32 binary = 0;

    llarm::util::modify_bit(binary, 27, true);
    llarm::util::modify_bit(binary, 25, true);

    const u32 immed = args.first_int - (args.PC + 8);
    const i32 offset = (immed >> 2);
    const u32 target = offset & 0x00FFFFFF;

    llarm::util::swap_bits(binary, 0, 23, target);

    return binary;
}


u32 generators::bl(const operand_struct &args) {
    u32 binary = b(args);

    llarm::util::modify_bit(binary, 24, true);

    return binary;
}


u32 generators::bkpt(const operand_struct &args) {
    u32 binary = 0b1110'0001'0010'0000'0000'0000'0111'0000;

    const u16 immed = args.first_int;

    const u16 top_bits = llarm::util::bit_range<u16>(immed, 4, 16);
    const u8 bottom_bits = llarm::util::bit_range<u8>(immed, 0, 3);

    llarm::util::swap_bits(binary, 8, 19, top_bits);
    llarm::util::swap_bits(binary, 0, 3, bottom_bits);

    return binary;
}


u32 generators::blx1(const operand_struct &args) {
    u32 binary = 0b1111'1010'0000'0000'0000'0000'0000'0000;

    const i32 offset = args.first_int - (args.PC + 8);

    const i32 immed_24 = (offset >> 2) & 0x00FFFFFF;
    const bool H = (offset >> 1) & 1;

    llarm::util::modify_bit(binary, 24, H);
    llarm::util::swap_bits(binary, 0, 23, immed_24);

    return binary;
}


u32 generators::blx2(const operand_struct &args) {
    u32 binary = bx(args);

    llarm::util::modify_bit(binary, 5, true);

    return binary;
}


u32 generators::bx(const operand_struct &args) {
    u32 binary = 0b0000'0001'0010'1111'1111'1111'0001'0000;

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 0, 3, args.first_reg);

    return binary;
}


u32 generators::mcrr(const operand_struct &args) {
    u32 binary = 0b0000'1100'0100'0000'0000'0000'0000'0000;

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 8, 11, args.coproc);
    llarm::util::swap_bits(binary, 4, 7, args.first_int);
    llarm::util::swap_bits(binary, 12, 15, args.first_reg);
    llarm::util::swap_bits(binary, 16, 19, args.second_reg);
    llarm::util::swap_bits(binary, 0, 3, args.first_CR_reg);

    return binary;
}


u32 generators::mrrc(const operand_struct &args) {
    u32 binary = mcrr(args);

    llarm::util::modify_bit(binary, 20, true);

    return binary;
}