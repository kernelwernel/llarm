#include "../generators.hpp"
#include "../../../encoding_utils.hpp"

#include <llarm/shared/util.hpp>


u32 generators::mul(const operand_struct& args) {
    u32 binary = 0;

    if (args.has_S) {
        llarm::util::modify_bit(binary, 20, true);
    }

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 16, 19, args.first_reg);
    llarm::util::swap_bits(binary, 0, 3, args.second_reg);
    llarm::util::swap_bits(binary, 8, 11, args.third_reg);

    return binary;
}


u32 generators::swp(const operand_struct& args) {
    u32 binary = 0;

    llarm::util::modify_bit(binary, 24, true);
    llarm::util::modify_bit(binary, 7, true);
    llarm::util::modify_bit(binary, 4, true);

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 12, 15, args.first_reg);
    llarm::util::swap_bits(binary, 0, 3, args.second_reg);
    llarm::util::swap_bits(binary, 16, 19, args.third_reg);

    return binary;
}


u32 generators::swpb(const operand_struct& args) {
    u32 binary = 0;

    llarm::util::modify_bit(binary, 24, true);
    llarm::util::modify_bit(binary, 22, true);
    llarm::util::modify_bit(binary, 7, true);
    llarm::util::modify_bit(binary, 4, true);

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 12, 15, args.first_reg);
    llarm::util::swap_bits(binary, 0, 3, args.second_reg);
    llarm::util::swap_bits(binary, 16, 19, args.third_reg);

    return binary;
}


u32 generators::mla(const operand_struct& args) {
    u32 binary = 0;

    llarm::util::modify_bit(binary, 21, true);
    llarm::util::modify_bit(binary, 7, true);
    llarm::util::modify_bit(binary, 4, true);

    if (args.has_S) {
        llarm::util::modify_bit(binary, 20, true);
    }

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 16, 19, args.first_reg);
    llarm::util::swap_bits(binary, 0, 3, args.second_reg);
    llarm::util::swap_bits(binary, 8, 11, args.third_reg);
    llarm::util::swap_bits(binary, 12, 15, args.fourth_reg);

    return binary;
}


u32 generators::mrs(const operand_struct& args) {
    u32 binary = 0;

    llarm::util::modify_bit(binary, 24, true);

    if (args.has_spsr) {
        llarm::util::modify_bit(binary, 22, true);
    }

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 12, 15, args.first_reg);
    llarm::util::swap_bits(binary, 16, 19, 0b1111);

    return binary;
}


u32 generators::msr_imm(const operand_struct& args) {
    u32 binary = 0;

    llarm::util::modify_bit(binary, 25, true);
    llarm::util::modify_bit(binary, 24, true);
    llarm::util::modify_bit(binary, 21, true);

    if (args.has_spsr) {
        llarm::util::modify_bit(binary, 22, true);
    }

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 16, 19, args.PSR_field_mask);
    llarm::util::swap_bits(binary, 12, 15, 0b1111);

    encoders::encode_imm(binary, args.first_int);

    return binary;
}


u32 generators::msr_reg(const operand_struct& args) {
    u32 binary = 0;

    llarm::util::modify_bit(binary, 24, true);
    llarm::util::modify_bit(binary, 21, true);

    if (args.has_spsr) {
        llarm::util::modify_bit(binary, 22, true);
    }

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 16, 19, args.PSR_field_mask);
    llarm::util::swap_bits(binary, 12, 15, 0b1111);
    llarm::util::swap_bits(binary, 0, 3, args.first_reg);

    return binary;
}


u32 generators::swi(const operand_struct& args) {
    u32 binary = 0;

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 24, 27, 0b1111);
    llarm::util::swap_bits(binary, 0, 23, args.first_int);

    return binary;
}


u32 generators::clz(const operand_struct& args) {
    u32 binary = 0;

    llarm::util::modify_bit(binary, 24, true);
    llarm::util::modify_bit(binary, 22, true);
    llarm::util::modify_bit(binary, 21, true);
    llarm::util::modify_bit(binary, 4, true);

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 16, 19, 0b1111);
    llarm::util::swap_bits(binary, 12, 15, args.first_reg);
    llarm::util::swap_bits(binary, 8, 11, 0b1111);
    llarm::util::swap_bits(binary, 0, 3, args.second_reg);

    return binary;
}


u32 generators::mcr(const operand_struct& args) {
    u32 binary = 0;

    llarm::util::modify_bit(binary, 27, true);
    llarm::util::modify_bit(binary, 26, true);
    llarm::util::modify_bit(binary, 25, true);
    llarm::util::modify_bit(binary, 4, true);

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 8, 11, args.coproc);
    llarm::util::swap_bits(binary, 21, 23, args.first_int);
    llarm::util::swap_bits(binary, 12, 15, args.first_reg);
    llarm::util::swap_bits(binary, 16, 19, args.first_CR_reg);
    llarm::util::swap_bits(binary, 0, 3, args.second_CR_reg);
    llarm::util::swap_bits(binary, 5, 7, args.second_int);

    return binary;
}


u32 generators::mrc(const operand_struct& args) {
    u32 binary = mcr(args);

    llarm::util::modify_bit(binary, 20, true);

    return binary;
}


u32 generators::cdp(const operand_struct& args) {
    u32 binary = 0;

    llarm::util::modify_bit(binary, 27, true);
    llarm::util::modify_bit(binary, 26, true);
    llarm::util::modify_bit(binary, 25, true);

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 8, 11, args.coproc);
    llarm::util::swap_bits(binary, 20, 23, args.first_int);
    llarm::util::swap_bits(binary, 12, 15, args.first_CR_reg);
    llarm::util::swap_bits(binary, 16, 19, args.second_CR_reg);
    llarm::util::swap_bits(binary, 0, 3, args.third_CR_reg);
    llarm::util::swap_bits(binary, 5, 7, args.second_int);

    return binary;
}


u32 generators::b(const operand_struct& args) {
    u32 binary = 0;

    llarm::util::modify_bit(binary, 27, true);
    llarm::util::modify_bit(binary, 25, true);

    const u32 immed = args.first_int - (args.PC + 8);
    const i32 offset = static_cast<i32>(immed >> 2);
    const u32 target = offset & 0x00FFFFFF;

    llarm::util::swap_bits(binary, 0, 23, target);

    return binary;
}


u32 generators::bl(const operand_struct& args) {
    u32 binary = b(args);

    llarm::util::modify_bit(binary, 24, true);

    return binary;
}


u32 generators::bkpt(const operand_struct& args) {
    u32 binary = 0b1110'0001'0010'0000'0000'0000'0111'0000;

    const u16 immed = static_cast<u16>(args.first_int);

    const u16 top_bits = llarm::util::bit_range<u16>(immed, 4, 16);
    const u8 bottom_bits = llarm::util::bit_range<u8>(immed, 0, 3);

    llarm::util::swap_bits(binary, 8, 19, top_bits);
    llarm::util::swap_bits(binary, 0, 3, bottom_bits);

    return binary;
}


u32 generators::blx1(const operand_struct& args) {
    u32 binary = 0b1111'1010'0000'0000'0000'0000'0000'0000;

    const u32 offset = args.first_int - (args.PC + 8);

    const u32 immed_24 = (offset >> 2) & 0x00FFFFFF;
    const bool H = (offset >> 1) & 1;

    llarm::util::modify_bit(binary, 24, H);
    llarm::util::swap_bits(binary, 0, 23, immed_24);

    return binary;
}


u32 generators::blx2(const operand_struct& args) {
    u32 binary = bx(args);

    llarm::util::modify_bit(binary, 5, true);

    return binary;
}


u32 generators::bx(const operand_struct& args) {
    u32 binary = 0b0000'0001'0010'1111'1111'1111'0001'0000;

    llarm::util::swap_bits(binary, 28, 31, args.cond);
    llarm::util::swap_bits(binary, 0, 3, args.first_reg);

    return binary;
}


u32 generators::mcrr(const operand_struct& args, const bool is_mcrr2) {
    u32 binary = 0b0000'1100'0100'0000'0000'0000'0000'0000;

    llarm::util::swap_bits(binary, 28, 31, (is_mcrr2 ? 0b1111 : args.cond));

    llarm::util::swap_bits(binary, 8, 11, args.coproc);
    llarm::util::swap_bits(binary, 4, 7, args.first_int);
    llarm::util::swap_bits(binary, 12, 15, args.first_reg);
    llarm::util::swap_bits(binary, 16, 19, args.second_reg);
    llarm::util::swap_bits(binary, 0, 3, args.first_CR_reg);

    return binary;
}


u32 generators::mrrc(const operand_struct& args, const bool is_mrrc2) {
    u32 binary = mcrr(args, is_mrrc2);

    llarm::util::modify_bit(binary, 20, true);

    return binary;
}


u32 generators::cpy(const operand_struct& args) {
    u32 binary = 0;

    llarm::util::swap_bits(binary, 28, 31, args.cond);

    llarm::util::swap_bits(binary, 20, 27, 0b0001'1010);

    llarm::util::swap_bits(binary, 12, 15, args.first_reg); // Rd
    llarm::util::swap_bits(binary, 0, 3, args.second_reg); // Rm

    return binary;
}


u32 generators::srs(const operand_struct& args) {
    u32 binary = 0;

    llarm::util::swap_bits(binary, 16, 31, 0b1111'1000'0100'1101);
    llarm::util::swap_bits(binary, 8, 11, 0b0101);
    llarm::util::swap_bits(binary, 0, 4, args.first_int); // mode

    llarm::util::modify_bit(binary, 21, args.has_preindex);

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
        default: llarm::out::dev_error("Impossible shifter operand for SRS assembly");
    }

    return binary;
}


u32 generators::strex(const operand_struct& args) {
    u32 binary = 0;

    llarm::util::swap_bits(binary, 28, 31, args.cond);

    llarm::util::swap_bits(binary, 20, 27, 0b0001'1000);
    llarm::util::swap_bits(binary, 4, 7, 0b1001);

    llarm::util::swap_bits(binary, 12, 15, args.first_reg); // Rd
    llarm::util::swap_bits(binary, 0, 3, args.second_reg); // Rm
    llarm::util::swap_bits(binary, 16, 19, args.third_reg); // Rn

    return binary;
}


u32 generators::usad8(const operand_struct& args) {
    u32 binary = 0b0000'0111'1000'0000'1111'0000'0001'0000;

    llarm::util::swap_bits(binary, 16, 19, args.first_reg); // Rd
    llarm::util::swap_bits(binary, 0, 3, args.second_reg); // Rm
    llarm::util::swap_bits(binary, 8, 11, args.third_reg); // Rs

    llarm::util::swap_bits(binary, 28, 31, args.cond);

    return binary;
}


u32 generators::usada8(const operand_struct& args) {
    u32 binary = 0b0000'0111'1000'0000'0000'0000'0001'0000;

    llarm::util::swap_bits(binary, 16, 19, args.first_reg); // Rd
    llarm::util::swap_bits(binary, 0, 3, args.second_reg); // Rm
    llarm::util::swap_bits(binary, 8, 11, args.third_reg); // Rs
    llarm::util::swap_bits(binary, 12, 15, args.fourth_reg); // Rn

    llarm::util::swap_bits(binary, 28, 31, args.cond);

    return binary;
}


u32 generators::setend(const operand_struct& args) {
    u32 binary = 0b1111'0001'0000'0001'0000'0000'0000'0000;

    bool E_bit = false;

    switch (args.endianness) {
        using enum endianness_enum;
        case LITTLE: break;
        case BIG: E_bit = true; break;
        case UNKNOWN: llarm::out::dev_error("Impossible endianness argument for SETEND instruction assembly");
            break;
    }

    llarm::util::modify_bit(binary, 9, E_bit);

    return binary;
}


u32 generators::rfe(const operand_struct& args) {
    u32 binary = 0b1111'1000'0001'0000'0000'1010'0000'0000;

    llarm::util::swap_bits(binary, 16, 19, args.first_reg); // Rn
    llarm::util::modify_bit(binary, 21, args.has_preindex);

    switch (args.shifter) {
        case shifter_id::LS_MUL_INC_AFTER:
            llarm::util::modify_bit(binary, 23, true); 
            break;

        case shifter_id::LS_MUL_INC_BEFORE:
            llarm::util::modify_bit(binary, 24, true); 
            llarm::util::modify_bit(binary, 23, true); 
            break;

        case shifter_id::LS_MUL_DEC_BEFORE:
            llarm::util::modify_bit(binary, 24, true); 
            break;

        case shifter_id::LS_MUL_DEC_AFTER: break;
        default: llarm::out::dev_error("Impossible addressing mode argument for RFE instruction assembly");
    }

    return binary;
}


u32 generators::ldrex(const operand_struct& args) {
    u32 binary = 0;

    llarm::util::swap_bits(binary, 28, 31, args.cond);

    llarm::util::swap_bits(binary, 20, 27, 0b0001'1001);
    llarm::util::swap_bits(binary, 4, 7, 0b1001);

    llarm::util::swap_bits(binary, 12, 15, args.first_reg); // Rd
    llarm::util::swap_bits(binary, 16, 19, args.second_reg); // Rn

    return binary;
}


u32 generators::usat(const operand_struct& args) {
    u32 binary = 0;

    llarm::util::swap_bits(binary, 28, 31, args.cond);

    llarm::util::swap_bits(binary, 21, 27, 0b011'0111);
    llarm::util::modify_bit(binary, 4, true);

    llarm::util::swap_bits(binary, 12, 15, args.first_reg); // Rd
    llarm::util::swap_bits(binary, 0, 3, args.second_reg); // Rm

    llarm::util::swap_bits(binary, 16, 20, args.first_int);

    if (args.shifter == shifter_id::NONE) {
        return binary;
    }

    bool sh_bit = false;

    if (args.shifter == shifter_id::USAT_ASR) {
        sh_bit = true;
    } else if (args.shifter == shifter_id::USAT_LSL) {
        sh_bit = false;
    } else {
        llarm::out::error("Invalid shifter operand for USAT instruction assembly");
    }

    llarm::util::modify_bit(binary, 6, sh_bit);
    llarm::util::swap_bits(binary, 7, 11, args.second_int);

    return binary;
}


u32 generators::usat16(const operand_struct& args) {
    u32 binary = 0;

    llarm::util::swap_bits(binary, 28, 31, args.cond);

    llarm::util::swap_bits(binary, 20, 27, 0b0110'1110);
    llarm::util::swap_bits(binary, 4, 7, 0b0011);

    llarm::util::swap_bits(binary, 12, 15, args.first_reg); // Rd
    llarm::util::swap_bits(binary, 0, 3, args.second_reg); // Rm

    llarm::util::swap_bits(binary, 16, 19, args.first_int);

    return binary;
}


u32 generators::cps(const operand_struct& args) {
    u32 binary = 0;

    llarm::util::swap_bits(binary, 24, 31, 0b1111'0001);

    u8 imod = 0;
    bool mmod = false;

    switch (args.effect) {
        case effect_enum::UNKNOWN: llarm::out::error("Invalid effect argument in CPS instruction assembly");
        case effect_enum::NONE:
            mmod = true;
            break;
        case effect_enum::IE:
            imod = 0b10;
            mmod = (args.first_int != 0);
            break;
        case effect_enum::ID:
            imod = 0b11;
            mmod = (args.first_int != 0);
            break;
    }

    llarm::util::swap_bits(binary, 18, 19, imod);
    llarm::util::modify_bit(binary, 17, mmod);

    llarm::util::modify_bit(binary, 8, args.a_flag);
    llarm::util::modify_bit(binary, 7, args.i_flag);
    llarm::util::modify_bit(binary, 6, args.f_flag);

    if (mmod) {
        llarm::util::swap_bits(binary, 0, 4, args.first_int);
    }

    return binary;
}