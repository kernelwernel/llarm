#include "../generators.hpp"

#include "shared/util.hpp"
#include "shared/out.hpp"

// format: LDR|STR{<cond>}H|SH|SB|D <Rd>, <addressing_mode>
u32 generators::ls_misc_instruction(const arm_id id, const arguments &args) {
    u32 binary = 0;
    
    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 12, 15, args.first_reg);

    switch (id) {
        case arm_id::STRH: llarm::util::swap_bits(binary, 4, 7, 0b1011); break;
        case arm_id::STRD: llarm::util::swap_bits(binary, 4, 7, 0b1111); break;
        case arm_id::LDRD: llarm::util::swap_bits(binary, 4, 7, 0b1101); break;
        case arm_id::LDRH: 
            llarm::util::swap_bits(binary, 4, 7, 0b1011); 
            llarm::util::modify_bit(binary, 20, true);
            break;
        case arm_id::LDRSB: 
            llarm::util::swap_bits(binary, 4, 7, 0b1101); 
            llarm::util::modify_bit(binary, 20, true);
            break;
        case arm_id::LDRSH: 
            llarm::util::swap_bits(binary, 4, 7, 0b1111); 
            llarm::util::modify_bit(binary, 20, true);
            break;
        default: llarm::out::dev_error("Invalid configuration to load/store misc instruction pattern generation");
    }

    // 4th and 7th bits are always 1, so they are ignored

    auto change_immed = [&](const u8 offset_8) -> void {
        const u8 immed_H = llarm::util::bit_range<u8>(args.first_int, 4, 7);
        const u8 immed_L = llarm::util::bit_range<u8>(args.first_int, 0, 3);
        
        llarm::util::swap_bits(binary, 8, 11, immed_H);
        llarm::util::swap_bits(binary, 0, 3, immed_L);
    };

    if (args.has_minus == false) {
        llarm::util::modify_bit(binary, 23, true);
    }

    llarm::util::swap_bits(binary, 16, 19, args.second_reg);

    switch (args.shifter) {
        case shifter_id::LS_MISC_IMM: {
            llarm::util::modify_bit(binary, 24, true);
            llarm::util::modify_bit(binary, 22, true);
            change_immed(args.first_int);
            break;
        }

        case shifter_id::LS_MISC_IMM_PRE:
            llarm::util::modify_bit(binary, 24, true);
            llarm::util::modify_bit(binary, 22, true);
            llarm::util::modify_bit(binary, 21, true);
            change_immed(args.first_int);
            break;

        case shifter_id::LS_MISC_IMM_POST:
            llarm::util::modify_bit(binary, 22, true);
            change_immed(args.first_int);
            break;

        case shifter_id::LS_MISC_REG:
            llarm::util::modify_bit(binary, 24, true);
            llarm::util::swap_bits(binary, 0, 3, args.third_reg);
            break;

        case shifter_id::LS_MISC_REG_PRE:
            llarm::util::modify_bit(binary, 24, true);
            llarm::util::modify_bit(binary, 21, true);
            llarm::util::swap_bits(binary, 0, 3, args.third_reg);
            break;

        case shifter_id::LS_MISC_REG_POST:
            llarm::util::swap_bits(binary, 0, 3, args.third_reg);
            break;

        default: llarm::out::dev_error("Invalid shifter configuration to load/store misc instruction pattern generation");
    }

    return binary;
}