#pragma once

#include "shared/types.hpp"
#include "shared/util.hpp"

#include "../shifter_id.hpp"


enum class vfp_special_regs : u8 {
    NONE,
    FPSID,
    FPSCR,
    FPEXC
};

struct arguments {
    u32 first_int;
    u32 second_int;
    u32 third_int;
    u32 PC;
    u16 reg_list;
    u8 flags;
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
    shifter_enum shifter;
    vfp_special_regs vfp_special_reg;

    bool has_S() const { return (flags & 1); }
    bool has_Z() const { return llarm::util::bit_fetch(flags, 1); }
    bool has_minus() const { return llarm::util::bit_fetch(flags, 2); }
    bool has_spsr() const { return llarm::util::bit_fetch(flags, 3); }
    bool has_x() const { return llarm::util::bit_fetch(flags, 4); }
    bool has_y() const { return llarm::util::bit_fetch(flags, 5); }
    bool has_preindex() const { return llarm::util::bit_fetch(flags, 6); }
};


namespace args {
    
}