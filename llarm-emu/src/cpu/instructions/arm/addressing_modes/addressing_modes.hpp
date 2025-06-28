#pragma once

#include "../../../core/registers.hpp"
#include "../../operation.hpp"

#include "shared/types.hpp"

struct data_struct {
    u32 value;
    bool carry;
};


struct address_struct {
    u32 start;
    u32 end;
};


struct ADDRESSING_MODE {
private:
    REGISTERS& reg;
    OPERATION& operation;

private:
    data_struct data_process_immediate_mode(const u32);
    data_struct data_process_register(const u32);
    data_struct data_process_logical_shift_left_immediate(const u32);
    data_struct data_process_logical_shift_right_immediate(const u32);
    data_struct data_process_arithmetic_shift_right_immediate(const u32);
    data_struct data_process_rotate_right_immediate(const u32);
    data_struct data_process_logical_shift_left_register(const u32);
    data_struct data_process_logical_shift_right_register(const u32);
    data_struct data_process_arithmetic_shift_right_register(const u32);
    data_struct data_process_rotate_right_register(const u32);
    data_struct data_process_rotate_right_extend(const u32);

    u32 ls_imm(const u32);
    u32 ls_reg(const u32);
    u32 ls_scaled_reg(const u32);
    u32 ls_imm_pre(const u32);
    u32 ls_reg_pre(const u32);
    u32 ls_scaled_reg_pre(const u32);
    u32 ls_imm_post(const u32);
    u32 ls_reg_post(const u32);
    u32 ls_scaled_reg_post(const u32);

    u32 ls_misc_imm(const u32);
    u32 ls_misc_reg(const u32);
    u32 ls_misc_imm_pre(const u32);
    u32 ls_misc_reg_pre(const u32);
    u32 ls_misc_imm_post(const u32);
    u32 ls_misc_reg_post(const u32);
    
    address_struct ls_mul_inc_after(const u32);
    address_struct ls_mul_inc_before(const u32);
    address_struct ls_mul_dec_after(const u32);
    address_struct ls_mul_dec_before(const u32);

    address_struct ls_coproc_imm(const u32);
    address_struct ls_coproc_imm_pre(const u32);
    address_struct ls_coproc_imm_post(const u32);
    address_struct ls_coproc_unindexed(const u32);


public:
    data_struct data_processing(const u32);

    u32 load_store(const u32);

    u32 load_store_misc(const u32);

    address_struct load_store_multiple(const u32);

    address_struct load_store_coprocessor(const u32);


    ADDRESSING_MODE(
        REGISTERS& reg, 
        OPERATION& operation
    ) : reg(reg),
        operation(operation) 
    {

    }
};