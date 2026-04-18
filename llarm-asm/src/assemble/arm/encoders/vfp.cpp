#include "../generators.hpp"
#include <llarm/shared/out.hpp>
#include <llarm/shared/util.hpp>

u32 generators::fcmpezd(const operand_struct &args) {
    u32 binary = fcmpzd(args);

    llarm::util::modify_bit(binary, 7, true);

    return binary;
}


u32 generators::fcmpzd(const operand_struct &args) {
    u32 binary = 0b0000'1110'1011'0101'0000'1011'0100'0000;

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 12, 15, args.first_reg);

    return binary;
}


u32 generators::fcmpezs(const operand_struct &args) {
    u32 binary = fcmpzs(args);

    llarm::util::modify_bit(binary, 7, true);

    return binary;
}


u32 generators::fcmpzs(const operand_struct &args) {
    u32 binary = 0b0000'1110'1011'0101'0000'1010'0100'0000;

    const bool D = (args.first_reg & 1);
    const u8 Fd = llarm::util::bit_range<u8>(args.first_reg, 1, 4);

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 12, 15, Fd);

    llarm::util::modify_bit(binary, 22, D);

    return binary;
}


u32 generators::fmdhr(const operand_struct &args) {
    u32 binary = fmdlr(args);

    llarm::util::modify_bit(binary, 21, true);

    return binary;
}


u32 generators::fmdlr(const operand_struct &args) {
    u32 binary = 0b0000'1110'0000'0000'0000'1011'0001'0000;

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 16, 19, args.first_reg);
    llarm::util::swap_bits(binary, 12, 15, args.second_reg);

    return binary;
}




u32 generators::fmrdh(const operand_struct &args) {
    u32 binary = fmrdl(args);

    llarm::util::modify_bit(binary, 21, true);

    return binary;
}


u32 generators::fmrdl(const operand_struct &args) {
    u32 binary = 0b0000'1110'0001'0000'0000'1011'0001'0000;

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 12, 15, args.first_reg);
    llarm::util::swap_bits(binary, 16, 19, args.second_reg);

    return binary;
}


u32 generators::fmrs(const operand_struct &args) {
    u32 binary = 0b0000'1110'0001'0000'0000'1010'0001'0000;

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 12, 15, args.first_reg);

    const bool N = (args.second_reg & 1);
    const u8 Fn = llarm::util::bit_range<u8>(args.second_reg, 1, 4);

    llarm::util::swap_bits(binary, 16, 19, Fn);
    llarm::util::modify_bit(binary, 7, N);

    return binary;
}


u32 generators::fmrx(const operand_struct &args) {
    u32 binary = 0b0000'1110'1111'0000'0000'1010'0001'0000;

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 12, 15, args.first_reg);

    u8 reg = 0;

    switch (args.vfp_special_reg) {
        case vfp_special_reg_enum::UNKNOWN: llarm::out::dev_error("Invalid FMRX special VFP register argument");
        case vfp_special_reg_enum::NONE: break;
        case vfp_special_reg_enum::FPSID: break; // set to 0 already
        case vfp_special_reg_enum::FPSCR: reg = 1; break;
        case vfp_special_reg_enum::FPEXC: reg = 0b1000; break;
    }

    llarm::util::swap_bits(binary, 16, 19, reg);

    return binary;
}


u32 generators::fmsr(const operand_struct &args) {
    u32 binary = 0b0000'1110'0000'0000'0000'1010'0001'0000;

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 12, 15, args.second_reg);

    const bool N = (args.first_reg & 1);
    const u8 Fn = llarm::util::bit_range<u8>(args.first_reg, 1, 4);

    llarm::util::swap_bits(binary, 16, 19, Fn);
    llarm::util::modify_bit(binary, 7, N);

    return binary;
}


u32 generators::fmxr(const operand_struct &args) {
    u32 binary = 0b0000'1110'1110'0000'0000'1010'0001'0000;

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 12, 15, args.first_reg);

    u8 reg = 0;

    switch (args.vfp_special_reg) {
        case vfp_special_reg_enum::UNKNOWN: llarm::out::dev_error("Invalid FMRX special VFP register argument");
        case vfp_special_reg_enum::NONE: break;
        case vfp_special_reg_enum::FPSID: break; // set to 0 already
        case vfp_special_reg_enum::FPSCR: reg = 1; break;
        case vfp_special_reg_enum::FPEXC: reg = 0b1000; break;
    }

    llarm::util::swap_bits(binary, 16, 19, reg);

    return binary;
}


u32 generators::fmstat(const operand_struct &args) {
    u32 binary = 0b0000'1110'1111'0001'1111'1010'0001'0000;

    llarm::util::swap_bits(binary, 28, 31, args.cond);

    return binary;
}