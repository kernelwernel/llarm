#include "../generators.hpp"

#include "shared/util.hpp"
#include "shared/out.hpp"

// format: LDM|STM{<cond>}<addressing_mode> <Rn>{!}, <registers>{^}
u32 generators::ls_mul_instruction(const arm_id id, const operand_struct &args) {
    u32 binary = 0;

    llarm::util::modify_bit(binary, 27, true);

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 16, 19, args.first_reg);

    switch (id) {
        case arm_id::LDM1: 
            llarm::util::modify_bit(binary, 20, true);
            break;

        case arm_id::LDM2: 
            llarm::util::modify_bit(binary, 22, true);
            llarm::util::modify_bit(binary, 20, true);
            break;

        case arm_id::LDM3: 
            llarm::util::modify_bit(binary, 22, true);
            llarm::util::modify_bit(binary, 20, true);
            llarm::util::modify_bit(binary, 15, true);
            break;

        case arm_id::STM2: 
            llarm::util::modify_bit(binary, 22, true);
            break;

        case arm_id::STM1: break; 

        default: llarm::out::dev_error("Invalid configuration to load/store multiple instruction pattern generation");
    }

    switch (args.shifter) {
        case shifter_id::LS_MUL_INC_BEFORE:
            llarm::util::modify_bit(binary, 24, true); 
            llarm::util::modify_bit(binary, 23, true); 
            break;
        
        case shifter_id::LS_MUL_DEC_BEFORE:
            llarm::util::modify_bit(binary, 24, true); 
            break;

        case shifter_id::LS_MUL_INC_AFTER: 
            llarm::util::modify_bit(binary, 23, true); 
            break;

        case shifter_id::LS_MUL_DEC_AFTER: break;

        default: llarm::out::dev_error("Invalid shifter configuration to load/store multiple instruction pattern generation");
    }

    llarm::util::swap_bits(binary, 0, 15, args.reg_list);

    return binary;
}