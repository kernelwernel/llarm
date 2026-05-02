#pragma once

#include "../id/shifter_id.hpp"
#include "mnemonic_arm.hpp"

// the IR_struct.hpp and this file are not combined together due to dependency issues
// down the line when an IR must be generated for an instruction. This separated format
// may seem a bit clanky and unnecessary, but it works.

using namespace internal;

enum class vfp_special_reg_enum : u8 {
    UNKNOWN,
    NONE,
    FPSID,
    FPSCR,
    FPEXC
};

enum class endianness_enum : u8 {
    UNKNOWN,
    LITTLE,
    BIG
};

struct operand_struct {
    u32 first_int = 0;
    u32 second_int = 0;
    u32 third_int = 0;
    u32 PC = 0;
    u32 reg_list = 0;
    u8 cond = 0;
    u8 PSR_field_mask = 0;
    u8 first_reg = 0;
    u8 second_reg = 0;
    u8 third_reg = 0;
    u8 fourth_reg = 0;
    u8 coproc = 0;
    u8 first_CR_reg = 0;
    u8 second_CR_reg = 0;
    u8 third_CR_reg = 0;
    shifter_id shifter = shifter_id::UNKNOWN;
    vfp_special_reg_enum vfp_special_reg = vfp_special_reg_enum::UNKNOWN;
    endianness_enum endianness = endianness_enum::UNKNOWN;
    effect_enum effect = effect_enum::UNKNOWN;
    char x_char = '\0';
    char y_char = '\0';

    bool a_flag = false;
    bool i_flag = false;
    bool f_flag = false;

    bool has_S = false;
    bool has_Z = false;
    bool has_L = false;
    bool has_R = false;
    bool has_X = false;
    bool has_minus = false;
    bool has_spsr = false;
    bool has_preindex = false;
};