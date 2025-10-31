#include "../generators.hpp"

#include "shared/util.hpp"
#include "shared/out.hpp"

u32 generators::vfp_mul_instructions(const id::arm id, const arguments &args) {
    u32 binary = 0;

    u8 bits_11_8 = 0;
    u8 bits_27_20 = 0;

    shared::util::swap_bits(binary, 28, 31, args.cond);

    switch (id) {
        case id::arm::FSTS:
            bits_27_20 = 0b1101'0000;
            bits_11_8 = 0b1010;
            break;
        case id::arm::FLDS:
            bits_27_20 = 0b1101'0001;
            bits_11_8 = 0b1010;
            break;
        case id::arm::FSTMS:
            bits_27_20 = 0b1100'0000;
            bits_11_8 = 0b1010;
            break;
        case id::arm::FLDMS:
            bits_27_20 = 0b1100'0001;
            bits_11_8 = 0b1010;
            break;
        case id::arm::FSTD:
            bits_27_20 = 0b1101'0000;
            bits_11_8 = 0b1011;
            break;
        case id::arm::FLDD:
            bits_27_20 = 0b1101'0001;
            bits_11_8 = 0b1011;
            break;
        case id::arm::FSTMX:
        case id::arm::FSTMD:
            bits_27_20 = 0b1100'0000;
            bits_11_8 = 0b1011;
            break;
        case id::arm::FLDMX:
        case id::arm::FLDMD:
            bits_27_20 = 0b1100'0001;
            bits_11_8 = 0b1011;
            break;
        default: shared::out::dev_error("Invalid configuration to vfp load/store instruction pattern generation");
    }

    struct reglist {
        u8 Dd;
        u8 raw_offset;
        u8 offset;
    };

    auto process_reglist = [](const u16 raw_reglist) -> reglist {
        const u8 Dd = shared::util::get_lsb_index(raw_reglist);
        const u8 raw_offset = shared::util::popcount(raw_reglist);
        const u8 offset = (raw_offset * 2) + 1;

        return reglist { Dd, raw_offset, offset };
    };

    switch (id) {
        //<Sd>, [<Rn>{, #+/-(<offset>*4)}]
        case id::arm::FSTS: 
        case id::arm::FLDS: {
            const bool D = (args.first_reg & 1);
            const u8 Fd = shared::util::bit_range(args.first_reg, 1, 4);

            shared::util::swap_bits(binary, 12, 15, Fd);
            shared::util::swap_bits(binary, 16, 19, args.second_reg);
            shared::util::swap_bits(binary, 0, 7, args.first_int);

            shared::util::modify_bit(binary, 22, true);

            if (args.has_minus()) {
                shared::util::modify_bit(binary, 23, true);
            }

            break;
        }

        // <Dd>, [<Rn>{, #+/-(<offset>*4)}]
        case id::arm::FSTD: 
        case id::arm::FLDD: {
            shared::util::swap_bits(binary, 12, 15, args.first_reg);
            shared::util::swap_bits(binary, 16, 19, args.second_reg);
            shared::util::swap_bits(binary, 0, 7, args.first_int);

            if (args.has_minus()) {
                shared::util::modify_bit(binary, 23, true);
            }

            break;
        }

        
        // F<LD|ST>M<addressing_mode><X|S|D>{<cond>} <Rn>{!}, <registers>
        case id::arm::FSTMX: 
        case id::arm::FSTMS: 
        case id::arm::FSTMD: 
        case id::arm::FLDMX: 
        case id::arm::FLDMS: 
        case id::arm::FLDMD: {
            switch (args.shifter) {
                case shifter_enum::VFP_LS_MUL_UNINDEXED: 
                    shared::util::modify_bit(binary, 23, true);
                    break;

                case shifter_enum::VFP_LS_MUL_INC: 
                    shared::util::modify_bit(binary, 23, true);
                    shared::util::modify_bit(binary, 21, true);
                    break;

                case shifter_enum::VFP_LS_MUL_DEC: 
                    shared::util::modify_bit(binary, 24, true);
                    shared::util::modify_bit(binary, 21, true);
                    break;

                case shifter_enum::VFP_LS_MUL_SPECIAL: break;
                default: break;
            }

            if (args.has_minus()) {
                shared::util::modify_bit(binary, 23, true);
            }

            const reglist data = process_reglist(args.reg_list);

            if (id == id::arm::FSTMS || id == id::arm::FLDMS) {
                const bool D = (data.Dd & 1);
                const u8 Fd = shared::util::bit_range<u8>(data.Dd, 1, 4);
                
                shared::util::modify_bit(binary, 22, D);
                shared::util::swap_bits(binary, 12, 15, Fd);
                shared::util::swap_bits(binary, 12, 15, data.raw_offset);
            } else {
                shared::util::swap_bits(binary, 0, 7, data.offset);
                shared::util::swap_bits(binary, 12, 15, data.Dd);
            }

            shared::util::swap_bits(binary, 16, 19, args.first_reg);
            break;
        }

        default: shared::out::dev_error("Invalid configuration to vfp load/store instruction pattern generation");
    }

    return binary;
}