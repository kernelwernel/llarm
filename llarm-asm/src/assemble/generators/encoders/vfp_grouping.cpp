#include "../generators.hpp"
#include "shared/out.hpp"

u32 generators::vfp_Dd_Dm_instructions(const arm_id id, const arguments &args) {
    u32 binary = [=]() -> u32 {
        switch (id) {
            case arm_id::FABSD:  return 0b0000'1110'1011'0000'0000'1011'1100'0000;
            case arm_id::FCMPD:  return 0b0000'1110'1011'0100'0000'1011'0100'0000;
            case arm_id::FCMPED: return 0b0000'1110'1011'0100'0000'1011'1100'0000;
            case arm_id::FCPYD:  return 0b0000'1110'1011'0000'0000'1011'0100'0000;
            case arm_id::FSQRTD: return 0b0000'1110'1011'0001'0000'1011'1100'0000;
            case arm_id::FNEGD:  return 0b0000'1110'1011'0001'0000'1011'0100'0000;
            default: llarm::out::dev_error("Invalid configuration to vfp Dd Dm instruction pattern generation");
        }
    }();

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 12, 15, args.first_reg);
    llarm::util::swap_bits(binary, 0, 3, args.second_reg);

    return binary;
}


u32 generators::vfp_Dd_Dn_Dm_instructions(const arm_id id, const arguments &args) {
    u32 binary = [=]() -> u32 {
        switch (id) {
            case arm_id::FADDD:  return 0b0000'1110'0011'0000'0000'1011'0000'0000;
            case arm_id::FDIVD:  return 0b0000'1110'1000'0000'0000'1011'0000'0000;
            case arm_id::FMACD:  return 0b0000'1110'0000'0000'0000'1011'0000'0000;
            case arm_id::FMSCD:  return 0b0000'1110'0001'0000'0000'1011'0000'0000;
            case arm_id::FMULD:  return 0b0000'1110'0010'0000'0000'1011'0000'0000;
            case arm_id::FNMACD: return 0b0000'1110'0000'0000'0000'1011'0100'0000;
            case arm_id::FNMSCD: return 0b0000'1110'0001'0000'0000'1011'0100'0000;
            case arm_id::FNMULD: return 0b0000'1110'0010'0000'0000'1011'0100'0000;
            case arm_id::FSUBD:  return 0b0000'1110'0011'0000'0000'1011'0100'0000;
            default: llarm::out::dev_error("Invalid configuration to vfp Dd Dn Dm instruction pattern generation");
        }
    }();

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 12, 15, args.first_reg);
    llarm::util::swap_bits(binary, 16, 19, args.second_reg);
    llarm::util::swap_bits(binary, 0, 3, args.third_reg);

    return binary;
}


u32 generators::vfp_Sd_Sm_instructions(const arm_id id, const arguments &args) {
    u32 binary = [=]() -> u32 {
        switch (id) {
            case arm_id::FABSS:  return 0b0000'1110'1011'0000'0000'1010'1100'0000; 
            case arm_id::FCMPES: return 0b0000'1110'1011'0100'0000'1010'1100'0000; 
            case arm_id::FCMPS:  return 0b0000'1110'1011'0100'0000'1010'0100'0000; 
            case arm_id::FCPYS:  return 0b0000'1110'1011'0000'0000'1010'0100'0000; 
            case arm_id::FNEGS:  return 0b0000'1110'1011'0001'0000'1010'0100'0000; 
            case arm_id::FSITOS: return 0b0000'1110'1011'1000'0000'1010'1100'0000;  
            case arm_id::FSQRTS: return 0b0000'1110'1011'0001'0000'1010'1100'0000; 
            case arm_id::FTOSIS: return 0b0000'1110'1011'1101'0000'1010'0100'0000;
            case arm_id::FTOUIS: return 0b0000'1110'1011'1100'0000'1010'0100'0000;
            case arm_id::FUITOS: return 0b0000'1110'1011'1000'0000'1010'0100'0000; 
            default: llarm::out::dev_error("Invalid configuration to vfp Dd Dn Dm instruction pattern generation");
        }
    }();

    if (args.has_Z) {
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


u32 generators::vfp_Sd_Sn_Sm_instructions(const arm_id id, const arguments &args) {
    u32 binary = [=]() -> u32 {
        switch (id) {
            case arm_id::FADDS:  return 0b0000'1110'0011'0000'0000'1010'0000'0000;
            case arm_id::FDIVS:  return 0b0000'1110'1000'0000'0000'1010'0000'0000;
            case arm_id::FMACS:  return 0b0000'1110'0000'0000'0000'1010'0000'0000;
            case arm_id::FMSCS:  return 0b0000'1110'0001'0000'0000'1010'0000'0000;
            case arm_id::FMULS:  return 0b0000'1110'0010'0000'0000'1010'0000'0000;
            case arm_id::FNMACS: return 0b0000'1110'0000'0000'0000'1010'0100'0000;
            case arm_id::FNMSCS: return 0b0000'1110'0001'0000'0000'1010'0100'0000;
            case arm_id::FNMULS: return 0b0000'1110'0010'0000'0000'1010'0100'0000;
            case arm_id::FSUBS:  return 0b0000'1110'0011'0000'0000'1010'0100'0000;
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


u32 generators::vfp_Dd_Sm_instructions(const arm_id id, const arguments &args) {
    u32 binary = [=]() -> u32 {
        switch (id) {
            case arm_id::FCVTDS: return 0b0000'1110'1011'0111'0000'1010'1100'0000;
            case arm_id::FSITOD: return 0b0000'1110'1011'1000'0000'1011'1100'0000;
            case arm_id::FUITOD: return 0b0000'1110'1011'1000'0000'1011'0100'0000;
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


u32 generators::vfp_Sd_Dm_instructions(const arm_id id, const arguments &args) {
    u32 binary = [=]() -> u32 {
        switch (id) {
            case arm_id::FCVTSD: return 0b0000'1110'1011'0111'0000'1011'1100'0000;
            case arm_id::FTOSID: return 0b0000'1110'1011'1101'0000'1011'0100'0000;
            case arm_id::FTOUID: return 0b0000'1110'1011'1100'0000'1011'0100'0000;
            default: llarm::out::dev_error("Invalid configuration to vfp Dd Dn Dm instruction pattern generation");
        }
    }();

    if (id == arm_id::FTOSID || id == arm_id::FTOUID) {
        if (args.has_Z) {
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