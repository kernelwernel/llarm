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

public:

private:
    data_struct data_process_immediate_mode(const arm_code_t&);
    data_struct data_process_register(const arm_code_t&);
    data_struct data_process_logical_shift_left_immediate(const arm_code_t&);
    data_struct data_process_logical_shift_right_immediate(const arm_code_t&);
    data_struct data_process_arithmetic_shift_right_immediate(const arm_code_t&);
    data_struct data_process_rotate_right_immediate(const arm_code_t&);
    data_struct data_process_logical_shift_left_register(const arm_code_t&);
    data_struct data_process_logical_shift_right_register(const arm_code_t&);
    data_struct data_process_arithmetic_shift_right_register(const arm_code_t&);
    data_struct data_process_rotate_right_register(const arm_code_t&);
    data_struct data_process_rotate_right_extend(const arm_code_t&);

    u32 ls_imm(const arm_code_t&);
    u32 ls_reg(const arm_code_t&);
    u32 ls_scaled_reg(const arm_code_t&);
    u32 ls_imm_pre(const arm_code_t&);
    u32 ls_reg_pre(const arm_code_t&);
    u32 ls_scaled_reg_pre(const arm_code_t&);
    u32 ls_imm_post(const arm_code_t&);
    u32 ls_reg_post(const arm_code_t&);
    u32 ls_scaled_reg_post(const arm_code_t&);

    u32 ls_misc_imm(const arm_code_t&);
    u32 ls_misc_reg(const arm_code_t&);
    u32 ls_misc_imm_pre(const arm_code_t&);
    u32 ls_misc_reg_pre(const arm_code_t&);
    u32 ls_misc_imm_post(const arm_code_t&);
    u32 ls_misc_reg_post(const arm_code_t&);
    
    address_struct ls_mul_inc_after(const arm_code_t&);
    address_struct ls_mul_inc_before(const arm_code_t&);
    address_struct ls_mul_dec_after(const arm_code_t&);
    address_struct ls_mul_dec_before(const arm_code_t&);

    //address_struct ls_coproc_imm(const arm_code_t&);
    //address_struct ls_coproc_imm_pre(const arm_code_t&);
    //address_struct ls_coproc_imm_post(const arm_code_t&);
    //address_struct ls_coproc_unindexed(const arm_code_t&);


public:
    data_struct data_processing(const arm_code_t&);

    u32 load_store(const arm_code_t&);

    u32 load_store_misc(const arm_code_t&);

    address_struct load_store_multiple(const arm_code_t&);

    //address_struct load_store_coprocessor(const arm_code_t&);


    ADDRESSING_MODE(
        REGISTERS& reg, 
        OPERATION& operation
    ) : reg(reg),
        operation(operation) 
    {

    }
};