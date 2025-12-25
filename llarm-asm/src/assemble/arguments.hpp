#pragma once

#include "../interpreter/IR.hpp"
#include "llarm-asm/src/interpreter/lexer.hpp"
#include "shared/types.hpp"

#include "../id/shifter_id.hpp"

using enum token_enum;


enum class vfp_special_reg_enum : u8 {
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
    unsigned char x_char;
    unsigned char y_char;

    bool has_S;
    bool has_Z;
    bool has_L;
    bool has_minus;
    bool has_spsr;
    bool has_preindex;
};


namespace args {
    arguments IR_to_args(const IR_arm_struct &IR);

    void reg(u8 &reg_count, u8 &CR_reg_count, arguments &arg, const lexeme &lexeme);
    void imm(u8 &int_count, arguments &arg, const lexeme &lexeme);
    void psr(arguments &arg, const lexeme &lexeme);
    void reg_list(arguments &arg, const lexeme &lexeme);


    //arguments thumb_IR_to_args(const IR_thumb_struct &IR) {
    //    
    //}
}