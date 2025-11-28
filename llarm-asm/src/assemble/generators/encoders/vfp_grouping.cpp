#include "../generators.hpp"
#include "shared/out.hpp"

u32 generators::vfp_Dd_Dm_instructions(const id::arm id, const arguments &args) {
    u32 binary = [=]() -> u32 {
        switch (id) {
            case id::arm::FABSD:  return 0b0000'1110'1011'0000'0000'1011'1100'0000;
            case id::arm::FCMPD:  return 0b0000'1110'1011'0100'0000'1011'0100'0000;
            case id::arm::FCMPED: return 0b0000'1110'1011'0100'0000'1011'1100'0000;
            case id::arm::FCPYD:  return 0b0000'1110'1011'0000'0000'1011'0100'0000;
            case id::arm::FSQRTD: return 0b0000'1110'1011'0001'0000'1011'1100'0000;
            case id::arm::FNEGD:  return 0b0000'1110'1011'0001'0000'1011'0100'0000;
            default: llarm::out::dev_error("Invalid configuration to vfp Dd Dm instruction pattern generation");
        }
    }();

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 12, 15, args.first_reg);
    llarm::util::swap_bits(binary, 0, 3, args.second_reg);

    return binary;
}


u32 generators::vfp_Dd_Dn_Dm_instructions(const id::arm id, const arguments &args) {
    u32 binary = [=]() -> u32 {
        switch (id) {
            case id::arm::FADDD:  return 0b0000'1110'0011'0000'0000'1011'0000'0000;
            case id::arm::FDIVD:  return 0b0000'1110'1000'0000'0000'1011'0000'0000;
            case id::arm::FMACD:  return 0b0000'1110'0000'0000'0000'1011'0000'0000;
            case id::arm::FMSCD:  return 0b0000'1110'0001'0000'0000'1011'0000'0000;
            case id::arm::FMULD:  return 0b0000'1110'0010'0000'0000'1011'0000'0000;
            case id::arm::FNMACD: return 0b0000'1110'0000'0000'0000'1011'0100'0000;
            case id::arm::FNMSCD: return 0b0000'1110'0001'0000'0000'1011'0100'0000;
            case id::arm::FNMULD: return 0b0000'1110'0010'0000'0000'1011'0100'0000;
            case id::arm::FSUBD:  return 0b0000'1110'0011'0000'0000'1011'0100'0000;
            default: llarm::out::dev_error("Invalid configuration to vfp Dd Dn Dm instruction pattern generation");
        }
    }();

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 12, 15, args.first_reg);
    llarm::util::swap_bits(binary, 16, 19, args.second_reg);
    llarm::util::swap_bits(binary, 0, 3, args.third_reg);

    return binary;
}


u32 generators::vfp_Sd_Sm_instructions(const id::arm id, const arguments &args) {
    u32 binary = [=]() -> u32 {
        switch (id) {
            case id::arm::FABSS:  return 0b0000'1110'1011'0000'0000'1010'1100'0000; 
            case id::arm::FCMPES: return 0b0000'1110'1011'0100'0000'1010'1100'0000; 
            case id::arm::FCMPS:  return 0b0000'1110'1011'0100'0000'1010'0100'0000; 
            case id::arm::FCPYS:  return 0b0000'1110'1011'0000'0000'1010'0100'0000; 
            case id::arm::FNEGS:  return 0b0000'1110'1011'0001'0000'1010'0100'0000; 
            case id::arm::FSITOS: return 0b0000'1110'1011'1000'0000'1010'1100'0000;  
            case id::arm::FSQRTS: return 0b0000'1110'1011'0001'0000'1010'1100'0000; 
            case id::arm::FTOSIS: return 0b0000'1110'1011'1101'0000'1010'0100'0000;
            case id::arm::FTOUIS: return 0b0000'1110'1011'1100'0000'1010'0100'0000;
            case id::arm::FUITOS: return 0b0000'1110'1011'1000'0000'1010'0100'0000; 
            default: llarm::out::dev_error("Invalid configuration to vfp Dd Dn Dm instruction pattern generation");
        }
    }();

    if (args.has_Z()) {
        llarm::util::modify_bit(binary, 7, true);
    }

    llarm::util::swap_bits(binary, 28, 31, args.cond);

    const bool D = (args.first_reg & 1);
    const bool M = (args.second_reg & 1);

    const u8 Fd = llarm::util::bit_range(args.first_reg, 1, 4);
    const u8 Fm = llarm::util::bit_range(args.second_reg, 1, 4);

    llarm::util::modify_bit(binary, 22, D);
    llarm::util::modify_bit(binary, 5, M);

    llarm::util::swap_bits(binary, 0, 3, Fm);
    llarm::util::swap_bits(binary, 12, 15, Fd);

    return binary;
}


u32 generators::vfp_Sd_Sn_Sm_instructions(const id::arm id, const arguments &args) {
    u32 binary = [=]() -> u32 {
        switch (id) {
            case id::arm::FADDS:  return 0b0000'1110'0011'0000'0000'1010'0000'0000;
            case id::arm::FDIVS:  return 0b0000'1110'1000'0000'0000'1010'0000'0000;
            case id::arm::FMACS:  return 0b0000'1110'0000'0000'0000'1010'0000'0000;
            case id::arm::FMSCS:  return 0b0000'1110'0001'0000'0000'1010'0000'0000;
            case id::arm::FMULS:  return 0b0000'1110'0010'0000'0000'1010'0000'0000;
            case id::arm::FNMACS: return 0b0000'1110'0000'0000'0000'1010'0100'0000;
            case id::arm::FNMSCS: return 0b0000'1110'0001'0000'0000'1010'0100'0000;
            case id::arm::FNMULS: return 0b0000'1110'0010'0000'0000'1010'0100'0000;
            case id::arm::FSUBS:  return 0b0000'1110'0011'0000'0000'1010'0100'0000;
            default: llarm::out::dev_error("Invalid configuration to vfp Dd Dn Dm instruction pattern generation");
        }
    }();

    llarm::util::swap_bits(binary, 28, 31, args.cond);

    const bool D = (args.first_reg & 1);
    const bool N = (args.second_reg & 1);
    const bool M = (args.third_reg & 1);

    const u8 Fd = llarm::util::bit_range(args.first_reg, 1, 4);
    const u8 Fn = llarm::util::bit_range(args.second_reg, 1, 4);
    const u8 Fm = llarm::util::bit_range(args.third_reg, 1, 4);

    llarm::util::modify_bit(binary, 22, D);
    llarm::util::modify_bit(binary, 7, N);
    llarm::util::modify_bit(binary, 5, M);

    llarm::util::swap_bits(binary, 12, 15, Fd);
    llarm::util::swap_bits(binary, 16, 19, Fn);
    llarm::util::swap_bits(binary, 0, 3, Fm);

    return binary;
}


u32 generators::vfp_Dd_Sm_instructions(const id::arm id, const arguments &args) {
    u32 binary = [=]() -> u32 {
        switch (id) {
            case id::arm::FCVTDS: return 0b0000'1110'1011'0111'0000'1010'1100'0000;
            case id::arm::FSITOD: return 0b0000'1110'1011'1000'0000'1011'1100'0000;
            case id::arm::FUITOD: return 0b0000'1110'1011'1000'0000'1011'0100'0000;
            default: llarm::out::dev_error("Invalid configuration to vfp Dd Dn Dm instruction pattern generation");
        }
    }();

    llarm::util::swap_bits(binary, 28, 31, args.cond);

    const bool M = (args.second_reg & 1);

    const u8 Fm = llarm::util::bit_range(args.second_reg, 1, 4);

    llarm::util::modify_bit(binary, 5, M);

    llarm::util::swap_bits(binary, 0, 3, Fm);
    llarm::util::swap_bits(binary, 12, 15, args.first_reg);

    return binary;
}


u32 generators::vfp_Sd_Dm_instructions(const id::arm id, const arguments &args) {
    u32 binary = [=]() -> u32 {
        switch (id) {
            case id::arm::FCVTSD: return 0b0000'1110'1011'0111'0000'1011'1100'0000;
            case id::arm::FTOSID: return 0b0000'1110'1011'1101'0000'1011'0100'0000;
            case id::arm::FTOUID: return 0b0000'1110'1011'1100'0000'1011'0100'0000;
            default: llarm::out::dev_error("Invalid configuration to vfp Dd Dn Dm instruction pattern generation");
        }
    }();

    if (id == id::arm::FTOSID || id == id::arm::FTOUID) {
        if (args.has_Z()) {
            llarm::util::modify_bit(binary, 7, true);
        }
    }

    llarm::util::swap_bits(binary, 28, 31, args.cond);

    const bool D = (args.first_reg & 1);

    const u8 Fm = llarm::util::bit_range(args.first_reg, 1, 4);

    llarm::util::modify_bit(binary, 22, D);

    llarm::util::swap_bits(binary, 12, 15, Fm);
    llarm::util::swap_bits(binary, 0, 3, args.second_reg);

    return binary;
}