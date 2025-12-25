#include "../generators.hpp"

#include "shared/util.hpp"
#include "shared/out.hpp"

u32 generators::vfp_mul_instructions(const arm_id id, const arguments &args) {
    u32 binary = 0;

    u8 bits_11_8 = 0;
    u8 bits_27_20 = 0;

    llarm::util::swap_bits(binary, 28, 31, args.cond);

    switch (id) {
        case arm_id::FSTS:
            bits_27_20 = 0b1101'0000;
            bits_11_8 = 0b1010;
            break;
        case arm_id::FLDS:
            bits_27_20 = 0b1101'0001;
            bits_11_8 = 0b1010;
            break;
        case arm_id::FSTMS:
            bits_27_20 = 0b1100'0000;
            bits_11_8 = 0b1010;
            break;
        case arm_id::FLDMS:
            bits_27_20 = 0b1100'0001;
            bits_11_8 = 0b1010;
            break;
        case arm_id::FSTD:
            bits_27_20 = 0b1101'0000;
            bits_11_8 = 0b1011;
            break;
        case arm_id::FLDD:
            bits_27_20 = 0b1101'0001;
            bits_11_8 = 0b1011;
            break;
        case arm_id::FSTMX:
        case arm_id::FSTMD:
            bits_27_20 = 0b1100'0000;
            bits_11_8 = 0b1011;
            break;
        case arm_id::FLDMX:
        case arm_id::FLDMD:
            bits_27_20 = 0b1100'0001;
            bits_11_8 = 0b1011;
            break;
        default: llarm::out::dev_error("Invalid configuration to vfp load/store instruction pattern generation");
    }

    struct reglist {
        u8 Dd;
        u8 offset;
    };

    auto process_reglist = [](const u16 raw_reglist) -> reglist {
        const u8 Dd = llarm::util::get_lsb(raw_reglist);
        const u8 offset = llarm::util::popcount(raw_reglist);

        return reglist { Dd, offset };
    };

    switch (id) {
        //<Sd>, [<Rn>{, #+/-(<offset>*4)}]
        case arm_id::FSTS: 
        case arm_id::FLDS: {
            const bool D = (args.first_reg & 1);
            const u8 Fd = llarm::util::bit_range(args.first_reg, 1, 4);

            llarm::util::swap_bits(binary, 12, 15, Fd);
            llarm::util::swap_bits(binary, 16, 19, args.second_reg);
            llarm::util::swap_bits(binary, 0, 7, args.first_int);

            llarm::util::modify_bit(binary, 22, true);

            if (args.has_minus) {
                llarm::util::modify_bit(binary, 23, true);
            }

            break;
        }

        // <Dd>, [<Rn>{, #+/-(<offset>*4)}]
        case arm_id::FSTD: 
        case arm_id::FLDD: {
            llarm::util::swap_bits(binary, 12, 15, args.first_reg);
            llarm::util::swap_bits(binary, 16, 19, args.second_reg);
            llarm::util::swap_bits(binary, 0, 7, args.first_int);

            if (args.has_minus) {
                llarm::util::modify_bit(binary, 23, true);
            }

            break;
        }

        
        // F<LD|ST>M<addressing_mode><X|S|D>{<cond>} <Rn>{!}, <registers>
        case arm_id::FSTMX: 
        case arm_id::FSTMS: 
        case arm_id::FSTMD: 
        case arm_id::FLDMX: 
        case arm_id::FLDMS: 
        case arm_id::FLDMD: {
            switch (args.shifter) {
                case shifter_id::VFP_LS_MUL_UNINDEXED: 
                    llarm::util::modify_bit(binary, 23, true);
                    break;

                case shifter_id::VFP_LS_MUL_INC: 
                    llarm::util::modify_bit(binary, 23, true);
                    llarm::util::modify_bit(binary, 21, true);
                    break;

                case shifter_id::VFP_LS_MUL_DEC: 
                    llarm::util::modify_bit(binary, 24, true);
                    llarm::util::modify_bit(binary, 21, true);
                    break;

                case shifter_id::VFP_LS_MUL_SPECIAL: break;
                default: break;
            }

            if (args.has_minus) {
                llarm::util::modify_bit(binary, 23, true);
            }

            const reglist data = process_reglist(args.reg_list);

            if (id == arm_id::FSTMS || id == arm_id::FLDMS) {
                const bool D = (data.Dd & 1);
                const u8 Fd = llarm::util::bit_range<u8>(data.Dd, 1, 4);
                
                llarm::util::modify_bit(binary, 22, D);
                llarm::util::swap_bits(binary, 12, 15, Fd);
                llarm::util::swap_bits(binary, 0, 7, data.offset);
            } else if (id == arm_id::FSTMX || id == arm_id::FLDMX) {
                llarm::util::swap_bits(binary, 0, 7, (data.offset * 2) + 1);
                llarm::util::swap_bits(binary, 12, 15, data.Dd);
            } else if (id == arm_id::FSTMD || id == arm_id::FLDMD) {
                llarm::util::swap_bits(binary, 0, 7, (data.offset * 2));
                llarm::util::swap_bits(binary, 12, 15, data.Dd);
            }

            llarm::util::swap_bits(binary, 16, 19, args.first_reg);
            break;
        }

        default: llarm::out::dev_error("Invalid configuration to vfp load/store instruction pattern generation");
    }

    return binary;
}