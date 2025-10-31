#include "../generators.hpp"

#include "shared/util.hpp"
#include "shared/out.hpp"

// format: LDM|STM{<cond>}<addressing_mode> <Rn>{!}, <registers>{^}
u32 generators::ls_mul_instruction(const id::arm id, const arguments &args) {
    u32 binary = 0;

    shared::util::modify_bit(binary, 27, true);

    shared::util::swap_bits(binary, 28, 31, args.cond);
    shared::util::swap_bits(binary, 16, 19, args.first_reg);

    switch (id) {
        case id::arm::LDM1: 
            shared::util::modify_bit(binary, 20, true);
            break;

        case id::arm::LDM2: 
            shared::util::modify_bit(binary, 22, true);
            shared::util::modify_bit(binary, 20, true);
            break;

        case id::arm::LDM3: 
            shared::util::modify_bit(binary, 22, true);
            shared::util::modify_bit(binary, 20, true);
            shared::util::modify_bit(binary, 15, true);
            break;

        case id::arm::STM2: 
            shared::util::modify_bit(binary, 22, true);
            break;

        case id::arm::STM1: break; 

        default: shared::out::dev_error("Invalid configuration to load/store multiple instruction pattern generation");
    }

    switch (args.shifter) {
        case shifter_enum::LS_MUL_INC_BEFORE:
            shared::util::modify_bit(binary, 24, true); 
            shared::util::modify_bit(binary, 23, true); 
            break;
        
        case shifter_enum::LS_MUL_DEC_BEFORE:
            shared::util::modify_bit(binary, 24, true); 
            break;

        case shifter_enum::LS_MUL_INC_AFTER: 
            shared::util::modify_bit(binary, 23, true); 
            break;

        case shifter_enum::LS_MUL_DEC_AFTER: break;

        default: shared::out::dev_error("Invalid shifter configuration to load/store multiple instruction pattern generation");
    }

    shared::util::swap_bits(binary, 0, 15, args.reg_list);

    return binary;
}