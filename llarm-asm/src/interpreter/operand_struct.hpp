#pragma once

#include "../id/shifter_id.hpp"

// the IR_struct.hpp and this file are not combined together due to dependency issues
// down the line when an IR must be generated for an instruction. This separated format
// may seem a bit clanky and unnecessary, but it works.

using namespace internal;

enum class vfp_special_reg_enum : u8 {
    NONE,
    FPSID,
    FPSCR,
    FPEXC
};

struct operand_struct {
    u32 first_int;
    u32 second_int;
    u32 third_int;
    u32 PC;
    u32 reg_list;
    u8 cond;
    u8 PSR_field_mask;
    u8 first_reg;
    u8 second_reg;
    u8 third_reg;
    u8 fourth_reg;
    u8 coproc;
    u8 first_CR_reg;
    u8 second_CR_reg;
    u8 third_CR_reg;
    shifter_id shifter;
    vfp_special_reg_enum vfp_special_reg;
    char x_char;
    char y_char;

    bool has_S;
    bool has_Z;
    bool has_L;
    bool has_minus;
    bool has_spsr;
    bool has_preindex;
};