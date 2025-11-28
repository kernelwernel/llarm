#include "../generators.hpp"

#include "shared/util.hpp"
#include "shared/out.hpp"

// format: LDR|STR{<cond>}{B}{T} <Rd>, <addressing_mode>
u32 generators::ls_instruction(const id::arm id, const arguments &args) {
    u32 binary = 0;

    if (id == id::arm::PLD) {
        binary = 0b1111'0101'0101'0000'1111'0000'0000'0000;
    } else {
        llarm::util::swap_bits(binary, 28, 31, args.cond);
        llarm::util::swap_bits(binary, 12, 15, args.first_reg);

        // all instructions in this shifter have bit 26 as true
        llarm::util::modify_bit(binary, 26, true);

        switch (id) {
            case id::arm::LDR: 
                llarm::util::modify_bit(binary, 20, true);
                break;

            case id::arm::LDRB: 
                llarm::util::modify_bit(binary, 22, true);
                llarm::util::modify_bit(binary, 20, true);
                break;
                
            case id::arm::LDRT: 
                llarm::util::modify_bit(binary, 21, true);
                llarm::util::modify_bit(binary, 20, true);
                break;
                
            case id::arm::LDRBT: 
                llarm::util::modify_bit(binary, 22, true);
                llarm::util::modify_bit(binary, 21, true);
                llarm::util::modify_bit(binary, 20, true);
                break;

            case id::arm::STR: 
                // bit 26 is already true, so nothing happens here
                break;

            case id::arm::STRB: 
                llarm::util::modify_bit(binary, 22, true);
                break;

            case id::arm::STRT: 
                llarm::util::modify_bit(binary, 21, true);
                break;

            case id::arm::STRBT: 
                llarm::util::modify_bit(binary, 22, true);
                llarm::util::modify_bit(binary, 21, true);
                break;

            default: llarm::out::dev_error("Invalid configuration to load/store instruction pattern generation");
        }
    }

    bool is_scaled = false;
    const bool has_positive = (args.has_minus() == false);

    switch (args.shifter) {
        case shifter_enum::LS_IMM:
            if (has_positive) { 
                llarm::util::modify_bit(binary, 23, true);
            }

            llarm::util::modify_bit(binary, 24, true);
            llarm::util::swap_bits(binary, 16, 19, args.second_reg);
            break;

        case shifter_enum::LS_IMM_PRE:
        case shifter_enum::LS_IMM_POST:
        case shifter_enum::LS_REG:
            if (has_positive) { 
                llarm::util::modify_bit(binary, 23, true);
            }

            llarm::util::modify_bit(binary, 25, true);
            llarm::util::modify_bit(binary, 24, true);
    
            llarm::util::swap_bits(binary, 16, 19, args.second_reg);
            llarm::util::swap_bits(binary, 0, 3, args.third_reg);
            break;

        case shifter_enum::LS_REG_PRE:
            if (has_positive) { 
                llarm::util::modify_bit(binary, 23, true);
            }

            llarm::util::modify_bit(binary, 25, true);
            llarm::util::modify_bit(binary, 24, true);
            llarm::util::modify_bit(binary, 21, true);

            llarm::util::swap_bits(binary, 16, 19, args.second_reg);
            llarm::util::swap_bits(binary, 0, 3, args.third_reg);
            break;

        case shifter_enum::LS_REG_POST: 
            if (has_positive) { 
                llarm::util::modify_bit(binary, 23, true);
            }

            llarm::util::modify_bit(binary, 25, true);

            llarm::util::swap_bits(binary, 16, 19, args.second_reg);
            llarm::util::swap_bits(binary, 0, 3, args.third_reg);
            break;

        case shifter_enum::LS_SCALED_LSL:
        case shifter_enum::LS_SCALED_LSR:
        case shifter_enum::LS_SCALED_ASR:
        case shifter_enum::LS_SCALED_ROR:
        case shifter_enum::LS_SCALED_RRX: 
            llarm::util::modify_bit(binary, 25, true);
            llarm::util::modify_bit(binary, 24, true);
            is_scaled = true; 
            break;

        case shifter_enum::LS_SCALED_PRE_LSL:
        case shifter_enum::LS_SCALED_PRE_LSR:
        case shifter_enum::LS_SCALED_PRE_ASR:
        case shifter_enum::LS_SCALED_PRE_ROR:
        case shifter_enum::LS_SCALED_PRE_RRX: 
            llarm::util::modify_bit(binary, 25, true);
            llarm::util::modify_bit(binary, 24, true);
            llarm::util::modify_bit(binary, 21, true);
            is_scaled = true; 
            break;

        case shifter_enum::LS_SCALED_POST_LSL:
        case shifter_enum::LS_SCALED_POST_LSR:
        case shifter_enum::LS_SCALED_POST_ASR:
        case shifter_enum::LS_SCALED_POST_ROR:
        case shifter_enum::LS_SCALED_POST_RRX: 
            llarm::util::modify_bit(binary, 25, true);
            is_scaled = true; 
            break;
    
        default: llarm::out::dev_error("Invalid shifter configuration to load/store instruction pattern generation");
    }

    auto check_immed_range = [](const u32 immed, const u8 start, const u8 end) -> void {
        if (immed > end || immed < start) {
            llarm::out::dev_error("Unencodable immediate shifted argument to load/store instruction pattern generation, immediate is too big");
        }
    };

    switch (args.shifter) {
        case shifter_enum::LS_SCALED_LSL:
        case shifter_enum::LS_SCALED_PRE_LSL:
        case shifter_enum::LS_SCALED_POST_LSL: 
            check_immed_range(args.first_int, 0, 31);
            llarm::util::swap_bits(binary, 7, 11, static_cast<u8>(args.first_int));
            // LSL is 0b00, so nothing is changed
            break;

        case shifter_enum::LS_SCALED_LSR:
        case shifter_enum::LS_SCALED_PRE_LSR:
        case shifter_enum::LS_SCALED_POST_LSR:
            check_immed_range(args.first_int, 1, 32);
            llarm::util::swap_bits(binary, 7, 11, static_cast<u8>(args.first_int));
            llarm::util::modify_bit(binary, 5, true);
            break;

        case shifter_enum::LS_SCALED_ASR:
        case shifter_enum::LS_SCALED_PRE_ASR:
        case shifter_enum::LS_SCALED_POST_ASR:
            check_immed_range(args.first_int, 1, 32);
            llarm::util::swap_bits(binary, 7, 11, static_cast<u8>(args.first_int));
            llarm::util::modify_bit(binary, 6, true);
            break;

        case shifter_enum::LS_SCALED_ROR:
        case shifter_enum::LS_SCALED_PRE_ROR:
        case shifter_enum::LS_SCALED_POST_ROR: 
            check_immed_range(args.first_int, 1, 31);
            llarm::util::swap_bits(binary, 7, 11, static_cast<u8>(args.first_int));
            // no break on purpose

        case shifter_enum::LS_SCALED_RRX: 
        case shifter_enum::LS_SCALED_PRE_RRX: 
        case shifter_enum::LS_SCALED_POST_RRX: 
            llarm::util::modify_bit(binary, 5, true);
            llarm::util::modify_bit(binary, 6, true);
            break;
    
        default: break;
    }

    if (is_scaled == true) {
        llarm::util::swap_bits(binary, 16, 19, args.second_reg);
        llarm::util::swap_bits(binary, 0, 3, args.third_reg);

        if (args.has_minus() == false) {
            llarm::util::modify_bit(binary, 23, true);
        }
    }

    return binary;
}
