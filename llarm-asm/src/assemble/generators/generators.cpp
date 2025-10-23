#include "generators.hpp"
#include "shared/util.hpp"
#include "shared/out.hpp"

using namespace internal;

bool generators::is_imm_encodable(const u32 imm) {
    // 1 byte immeds are always encodable
    if ((imm & 0xFFFFFF00) == 0) {
        return true;
    }

    // try every possible rotation
    for (u8 rot = 0; rot < 32; rot += 2) {
        const u32 rotated = std::rotr(imm, rot);

        if ((rotated & 0xFFFFFF00) == 0) {
            return true;
        }
    }

    return false;
}


void encode_imm(u32 &binary, const u32 immed) {
    for (u32 rot = 0; rot < 16; ++rot) {
        u32 rotated = std::rotr(immed, rot * 2);
        if ((rotated & 0xFFFFFF00) == 0) {
            shared::util::swap_bits(binary, 8, 11, static_cast<u8>(rotated));
            shared::util::swap_bits(binary, 0, 7, static_cast<u8>(immed));
        }
    }
}


u32 generators::mul(const arguments &args) {
    u32 binary = 0;

    if (args.has_S()) {
        shared::util::modify_bit(binary, 20, true);
    }

    shared::util::swap_bits(binary, 28, 31, args.cond);
    shared::util::swap_bits(binary, 16, 19, args.first_reg);
    shared::util::swap_bits(binary, 0, 3, args.second_reg);
    shared::util::swap_bits(binary, 8, 11, args.third_reg);

    return binary;
}


u32 generators::swp(const arguments &args) {
    u32 binary = 0;

    shared::util::modify_bit(binary, 24, true);
    shared::util::modify_bit(binary, 7, true);
    shared::util::modify_bit(binary, 4, true);

    shared::util::swap_bits(binary, 28, 31, args.cond);
    shared::util::swap_bits(binary, 12, 15, args.first_reg);
    shared::util::swap_bits(binary, 0, 3, args.second_reg);
    shared::util::swap_bits(binary, 16, 19, args.third_reg);

    return binary;
}


u32 generators::swpb(const arguments &args) {
    u32 binary = 0;

    shared::util::modify_bit(binary, 24, true);
    shared::util::modify_bit(binary, 22, true);
    shared::util::modify_bit(binary, 7, true);
    shared::util::modify_bit(binary, 4, true);

    shared::util::swap_bits(binary, 28, 31, args.cond);
    shared::util::swap_bits(binary, 12, 15, args.first_reg);
    shared::util::swap_bits(binary, 0, 3, args.second_reg);
    shared::util::swap_bits(binary, 16, 19, args.third_reg);

    return binary;
}


u32 generators::mla(const arguments &args) {
    u32 binary = 0;

    shared::util::modify_bit(binary, 21, true);
    shared::util::modify_bit(binary, 7, true);
    shared::util::modify_bit(binary, 4, true);

    if (args.has_S()) {
        shared::util::modify_bit(binary, 20, true);
    }

    shared::util::swap_bits(binary, 28, 31, args.cond);
    shared::util::swap_bits(binary, 16, 19, args.first_reg);
    shared::util::swap_bits(binary, 0, 3, args.second_reg);
    shared::util::swap_bits(binary, 8, 11, args.third_reg);
    shared::util::swap_bits(binary, 12, 15, args.fourth_reg);

    return binary;
}


u32 generators::mrs(const arguments &args) {
    u32 binary = 0;

    shared::util::modify_bit(binary, 24, true);

    if (args.has_spsr()) {
        shared::util::modify_bit(binary, 22, true);
    }

    shared::util::swap_bits(binary, 28, 31, args.cond);
    shared::util::swap_bits(binary, 12, 15, args.first_reg);
    shared::util::swap_bits(binary, 16, 19, 0b1111);

    return binary;
}


u32 generators::msr_imm(const arguments &args) {
    u32 binary = 0;

    shared::util::modify_bit(binary, 25, true);
    shared::util::modify_bit(binary, 24, true);
    shared::util::modify_bit(binary, 21, true);

    if (args.has_spsr()) {
        shared::util::modify_bit(binary, 22, true);
    }

    shared::util::swap_bits(binary, 28, 31, args.cond);
    shared::util::swap_bits(binary, 16, 19, args.PSR_field_mask);
    shared::util::swap_bits(binary, 12, 15, 0b1111);

    encode_imm(binary, args.first_int);

    return binary;
}


u32 generators::msr_reg(const arguments &args) {
    u32 binary = 0;

    shared::util::modify_bit(binary, 24, true);
    shared::util::modify_bit(binary, 21, true);

    if (args.has_spsr()) {
        shared::util::modify_bit(binary, 22, true);
    }

    shared::util::swap_bits(binary, 28, 31, args.cond);
    shared::util::swap_bits(binary, 16, 19, args.PSR_field_mask);
    shared::util::swap_bits(binary, 12, 15, 0b1111);
    shared::util::swap_bits(binary, 0, 3, args.first_reg);

    return binary;
}


u32 generators::swi(const arguments &args) {
    u32 binary = 0;

    shared::util::swap_bits(binary, 28, 31, args.cond);
    shared::util::swap_bits(binary, 24, 27, 0b1111);
    shared::util::swap_bits(binary, 0, 23, args.first_int);

    return binary;
}


u32 generators::clz(const arguments &args) {
    u32 binary = 0;

    shared::util::modify_bit(binary, 24, true);
    shared::util::modify_bit(binary, 22, true);
    shared::util::modify_bit(binary, 21, true);
    shared::util::modify_bit(binary, 4, true);

    shared::util::swap_bits(binary, 28, 31, args.cond);
    shared::util::swap_bits(binary, 16, 19, 0b1111);
    shared::util::swap_bits(binary, 12, 15, args.first_reg);
    shared::util::swap_bits(binary, 8, 11, 0b1111);
    shared::util::swap_bits(binary, 0, 3, args.second_reg);

    return binary;
}


u32 generators::mcr(const arguments &args) {
    u32 binary = 0;

    shared::util::modify_bit(binary, 27, true);
    shared::util::modify_bit(binary, 26, true);
    shared::util::modify_bit(binary, 25, true);
    shared::util::modify_bit(binary, 4, true);

    shared::util::swap_bits(binary, 28, 31, args.cond);
    shared::util::swap_bits(binary, 8, 11, args.coproc);
    shared::util::swap_bits(binary, 21, 23, args.first_int);
    shared::util::swap_bits(binary, 12, 15, args.first_reg);
    shared::util::swap_bits(binary, 16, 19, args.first_CR_reg);
    shared::util::swap_bits(binary, 0, 3, args.second_CR_reg);
    shared::util::swap_bits(binary, 5, 7, args.second_int);

    return binary;
}


u32 generators::mrc(const arguments &args) {
    u32 binary = mcr(args);

    shared::util::modify_bit(binary, 20, true);

    return binary;
}


u32 generators::cdp(const arguments &args) {
    u32 binary = 0;

    shared::util::modify_bit(binary, 27, true);
    shared::util::modify_bit(binary, 26, true);
    shared::util::modify_bit(binary, 25, true);

    shared::util::swap_bits(binary, 28, 31, args.cond);
    shared::util::swap_bits(binary, 8, 11, args.coproc);
    shared::util::swap_bits(binary, 20, 23, args.first_int);
    shared::util::swap_bits(binary, 12, 15, args.first_CR_reg);
    shared::util::swap_bits(binary, 16, 19, args.second_CR_reg);
    shared::util::swap_bits(binary, 0, 3, args.third_CR_reg);
    shared::util::swap_bits(binary, 5, 7, args.second_int);

    return binary;
}


u32 generators::b(const arguments &args) {
    u32 binary = 0;

    shared::util::modify_bit(binary, 27, true);
    shared::util::modify_bit(binary, 25, true);

    // TODO

    return binary;
}


u32 generators::bl(const arguments &args) {
    u32 binary = b(args);

    shared::util::modify_bit(binary, 24, true);

    // TODO

    return binary;
}


u32 generators::bkpt(const arguments &args) {
    u32 binary = 0b1110'0001'0010'0000'0000'0000'0111'0000;

    const u16 immed = args.first_int;

    const u16 top_bits = shared::util::bit_range<u16>(immed, 4, 16);
    const u8 bottom_bits = shared::util::bit_range<u8>(immed, 0, 3);

    shared::util::swap_bits(binary, 8, 19, top_bits);
    shared::util::swap_bits(binary, 0, 3, bottom_bits);

    return binary;
}


u32 generators::blx2(const arguments &args) {
    u32 binary = bx(args);

    shared::util::modify_bit(binary, 5, true);

    return binary;
}


u32 generators::bx(const arguments &args) {
    u32 binary = 0b0000'0001'0010'1111'1111'1111'0001'0000;

    shared::util::swap_bits(binary, 28, 31, args.cond);
    shared::util::swap_bits(binary, 0, 3, args.first_reg);

    return binary;
}


u32 generators::mcrr(const arguments &args) {
    u32 binary = 0b0000'1100'0100'0000'0000'0000'0000'0000;

    shared::util::swap_bits(binary, 28, 31, args.cond);
    shared::util::swap_bits(binary, 8, 11, args.coproc);
    shared::util::swap_bits(binary, 4, 7, args.first_int);
    shared::util::swap_bits(binary, 12, 15, args.first_reg);
    shared::util::swap_bits(binary, 16, 19, args.second_reg);
    shared::util::swap_bits(binary, 0, 3, args.first_CR_reg);

    return binary;
}


u32 generators::mrrc(const arguments &args) {
    u32 binary = mcrr(args);

    shared::util::modify_bit(binary, 20, true);

    return binary;
}


u32 generators::q_instructions(const id::arm id, const arguments &args) {
    u32 binary = 0b0000'0001'0000'0000'0000'0000'0101'0000;

    shared::util::swap_bits(binary, 28, 31, args.cond);
    shared::util::swap_bits(binary, 12, 15, args.first_reg);
    shared::util::swap_bits(binary, 0, 3, args.second_reg);
    shared::util::swap_bits(binary, 16, 19, args.third_reg);

    u8 opcode = 0;

    switch (id) {
        case id::arm::QADD: opcode = 0b00; break;
        case id::arm::QDADD: opcode = 0b10; break;
        case id::arm::QSUB: opcode = 0b01; break;
        case id::arm::QDSUB: opcode = 0b11; break;
        default: shared::out::dev_error("Invalid configuration to DSP Q instruction pattern generation");
    }

    shared::util::swap_bits(binary, 21, 22, opcode);    

    return binary;
}


u32 generators::mul_instructions(const id::arm id, const arguments &args) {
    u32 binary = 0b0000'0000'1000'0000'0000'0000'1001'0000;

    if (args.has_S()) {
        shared::util::modify_bit(binary, 20, true);
    }

    shared::util::swap_bits(binary, 28, 31, args.cond);
    shared::util::swap_bits(binary, 12, 15, args.first_reg);
    shared::util::swap_bits(binary, 16, 19, args.second_reg);
    shared::util::swap_bits(binary, 0, 3, args.third_reg);
    shared::util::swap_bits(binary, 8, 11, args.fourth_reg);

    u8 opcode = 0;

    switch (id) {
        case id::arm::SMLAL: opcode = 0b11; break;
        case id::arm::SMULL: opcode = 0b10; break;
        case id::arm::UMLAL: opcode = 0b01; break;
        case id::arm::UMULL: opcode = 0b00; break;
        default: shared::out::dev_error("Invalid configuration to u64 multiply instruction pattern generation");
    }

    shared::util::swap_bits(binary, 21, 22, opcode);

    return binary;
}


u32 generators::dsp_mul_instructions(const id::arm id, const arguments &args) {
    u32 binary = 0;

    shared::util::modify_bit(binary, 7, true);
    shared::util::modify_bit(binary, 24, true);

    shared::util::swap_bits(binary, 28, 31, args.cond);

    switch (id) {
        case id::arm::SMLALXY:
            shared::util::swap_bits(binary, 12, 15, args.first_reg);
            shared::util::swap_bits(binary, 16, 19, args.second_reg);
            shared::util::swap_bits(binary, 0, 3, args.third_reg);
            shared::util::swap_bits(binary, 8, 11, args.fourth_reg);
            break;

        case id::arm::SMLAXY: 
        case id::arm::SMLAWY: 
            shared::util::swap_bits(binary, 12, 15, args.fourth_reg);
            // no break on purpose

        case id::arm::SMULXY: 
        case id::arm::SMULWY: 
            shared::util::swap_bits(binary, 16, 19, args.first_reg);
            shared::util::swap_bits(binary, 0, 3, args.second_reg);
            shared::util::swap_bits(binary, 8, 11, args.third_reg);
            break;

        default: shared::out::dev_error("Invalid configuration to u64 multiply instruction pattern generation");
    }

    u8 bits_22_21 = 0;
    bool has_x = false;
    bool has_y = false;

    switch (id) {
        case id::arm::SMLAXY: 
            has_x = true;
            has_y = true;
            break;

        case id::arm::SMLALXY: 
            bits_22_21 = 0b10;
            has_x = true;
            has_y = true;
            break;

        case id::arm::SMLAWY: 
            bits_22_21 = 0b01;
            has_y = true;
            break;

        case id::arm::SMULXY: 
            bits_22_21 = 0b11;
            has_x = true;
            has_y = true;
            break;

        case id::arm::SMULWY: 
            bits_22_21 = 0b01;
            has_y = true;
            shared::util::modify_bit(binary, 5, true);
            break;

        default: shared::out::dev_error("Invalid configuration to u64 multiply instruction pattern generation");
    }

    if (has_y && args.has_y()) {
        shared::util::modify_bit(binary, 6, true);
    }

    if (has_x && args.has_x()) {
        shared::util::modify_bit(binary, 5, true);
    }

    shared::util::swap_bits(binary, 21, 22, bits_22_21);

    return binary;
}


u32 generators::arm(const id::arm id, const arguments &args) {
    switch (id) {
        case id::arm::UNKNOWN: return 0;
        case id::arm::UNDEFINED:  return 0;
        case id::arm::NOP: return 0;
        case id::arm::ADC: return data_instruction(id::arm::ADC, args);
        case id::arm::ADD: return data_instruction(id::arm::ADD, args);
        case id::arm::AND: return data_instruction(id::arm::AND, args);
        case id::arm::BIC: return data_instruction(id::arm::BIC, args);
        case id::arm::CMN: return data_instruction(id::arm::CMN, args);
        case id::arm::CMP: return data_instruction(id::arm::CMP, args);
        case id::arm::EOR: return data_instruction(id::arm::EOR, args);
        case id::arm::MOV: return data_instruction(id::arm::MOV, args);
        case id::arm::MVN: return data_instruction(id::arm::MVN, args);
        case id::arm::ORR: return data_instruction(id::arm::ORR, args);
        case id::arm::RSB: return data_instruction(id::arm::RSB, args);
        case id::arm::RSC: return data_instruction(id::arm::RSC, args);
        case id::arm::SBC: return data_instruction(id::arm::SBC, args);
        case id::arm::SUB: return data_instruction(id::arm::SUB, args);
        case id::arm::TEQ: return data_instruction(id::arm::TEQ, args);
        case id::arm::TST: return data_instruction(id::arm::TST, args);
        case id::arm::CMNP: return data_instruction(id::arm::CMNP, args);
        case id::arm::CMPP: return data_instruction(id::arm::CMPP, args);
        case id::arm::TEQP: return data_instruction(id::arm::TEQP, args);
        case id::arm::TSTP: return data_instruction(id::arm::TSTP, args);
        case id::arm::LDR: return ls_instruction(id::arm::LDR, args);
        case id::arm::STR: return ls_instruction(id::arm::STR, args);
        case id::arm::LDRB: return ls_instruction(id::arm::LDRB, args);
        case id::arm::LDRT: return ls_instruction(id::arm::LDRT, args);
        case id::arm::STRB: return ls_instruction(id::arm::STRB, args);
        case id::arm::STRT: return ls_instruction(id::arm::STRT, args);
        case id::arm::LDRBT: return ls_instruction(id::arm::LDRBT, args);
        case id::arm::STRBT: return ls_instruction(id::arm::STRBT, args);
        case id::arm::PLD: return ls_instruction(id::arm::PLD, args);
        case id::arm::STRH: return ls_misc_instruction(id::arm::STRH, args);
        case id::arm::LDRH: return ls_misc_instruction(id::arm::LDRH, args);
        case id::arm::LDRSB: return ls_misc_instruction(id::arm::LDRSB, args);
        case id::arm::LDRSH: return ls_misc_instruction(id::arm::LDRSH, args);
        case id::arm::LDRD: return ls_misc_instruction(id::arm::LDRD, args);
        case id::arm::STRD: return ls_misc_instruction(id::arm::STRD, args);
        case id::arm::LDM1: return ls_mul_instruction(id::arm::LDM1, args);
        case id::arm::LDM2: return ls_mul_instruction(id::arm::LDM2, args);
        case id::arm::LDM3: return ls_mul_instruction(id::arm::LDM3, args);
        case id::arm::STM1: return ls_mul_instruction(id::arm::STM1, args);
        case id::arm::STM2: return ls_mul_instruction(id::arm::STM2, args);
        case id::arm::LDC: return ls_coproc_instruction(id::arm::LDC, args);
        case id::arm::STC: return ls_coproc_instruction(id::arm::STC, args);
        case id::arm::B: return b(args);
        case id::arm::BL: return bl(args);
        case id::arm::CDP: return cdp(args);
        case id::arm::MCR: return mcr(args);
        case id::arm::MLA: return mla(args);
        case id::arm::MRC: return mrc(args);
        case id::arm::MRS: return mrs(args);
        case id::arm::MSR_IMM: return msr_imm(args);
        case id::arm::MSR_REG: return msr_reg(args);
        case id::arm::MUL: return mul(args);
        case id::arm::SWI: return swi(args);
        case id::arm::SWP: return swp(args); 
        case id::arm::SWPB: return swpb(args);
        case id::arm::BKPT: return bkpt(args);
        case id::arm::BLX1: //  
        case id::arm::BLX2: return blx2(args);
        case id::arm::CLZ: return clz(args);
        case id::arm::BX: return bx(args);
        case id::arm::SMLAL: return mul_instructions(id::arm::SMLAL, args);
        case id::arm::SMULL: return mul_instructions(id::arm::SMULL, args);
        case id::arm::UMLAL: return mul_instructions(id::arm::UMLAL, args);
        case id::arm::UMULL: return mul_instructions(id::arm::UMULL, args);
        case id::arm::MCRR: return mcrr(args);
        case id::arm::MRRC: return mrrc(args);
        case id::arm::QADD: return q_instructions(id::arm::QADD, args);
        case id::arm::QDADD: return q_instructions(id::arm::QDADD, args);
        case id::arm::QDSUB: return q_instructions(id::arm::QDSUB, args);
        case id::arm::QSUB: return q_instructions(id::arm::QSUB, args);
        case id::arm::SMLAXY: return dsp_mul_instructions(id::arm::SMLAXY, args);
        case id::arm::SMLALXY: return dsp_mul_instructions(id::arm::SMLALXY, args);
        case id::arm::SMLAWY: return dsp_mul_instructions(id::arm::SMLAWY, args);
        case id::arm::SMULXY: return dsp_mul_instructions(id::arm::SMULXY, args);
        case id::arm::SMULWY: return dsp_mul_instructions(id::arm::SMULWY, args);

        case id::arm::FABSD: // D D
        case id::arm::FABSS: // S S
        case id::arm::FADDD: // D D D
        case id::arm::FADDS: // S S S
        case id::arm::FCMPD: // D D
        case id::arm::FCMPED: // D D
        case id::arm::FCMPES: // S S
        case id::arm::FCMPEZD: // D
        case id::arm::FCMPEZS: // S
        case id::arm::FCMPS: // S S
        case id::arm::FCMPZD: // D
        case id::arm::FCMPZS: // S
        case id::arm::FCPYD: // D D
        case id::arm::FCPYS: // S S
        case id::arm::FCVTDS: // D S
        case id::arm::FCVTSD: // S D
        case id::arm::FDIVD: // D D D
        case id::arm::FDIVS: // S S S 
        case id::arm::FLDD: //  
        case id::arm::FLDMD: //  
        case id::arm::FLDMS: //  
        case id::arm::FLDMX: //  
        case id::arm::FLDS: //  
        case id::arm::FMACD: //  
        case id::arm::FMACS: //  
        case id::arm::FMDHR: //  
        case id::arm::FMDLR: //  
        case id::arm::FMRDH: //  
        case id::arm::FMRDL: //  
        case id::arm::FMRS: //  
        case id::arm::FMRX: //  
        case id::arm::FMSCD: //  
        case id::arm::FMSCS: //  
        case id::arm::FMSR: //  
        case id::arm::FMSTAT: //  
        case id::arm::FMULD: //  
        case id::arm::FMULS: //  
        case id::arm::FMXR: //  
        case id::arm::FNEGD: //  
        case id::arm::FNEGS: //  
        case id::arm::FNMACD: //  
        case id::arm::FNMACS: //  
        case id::arm::FNMSCD: //  
        case id::arm::FNMSCS: //  
        case id::arm::FNMULD: //  
        case id::arm::FNMULS: //  
        case id::arm::FSITOD: //  
        case id::arm::FSITOS: //  
        case id::arm::FSQRTD: //  
        case id::arm::FSQRTS: //  
        case id::arm::FSTD: //  
        case id::arm::FSTMD: //  
        case id::arm::FSTMS: //  
        case id::arm::FSTMX: //  
        case id::arm::FSTS: //  
        case id::arm::FSUBD: //  
        case id::arm::FSUBS: //  
        case id::arm::FTOSID: //  
        case id::arm::FTOSIS: //  
        case id::arm::FTOUID: //  
        case id::arm::FTOUIS: //  
        case id::arm::FUITOD: //  
        case id::arm::FUITOS: // 
        case id::arm::CDP2: // 
        case id::arm::LDC2: // 
        case id::arm::MCR2: // 
        case id::arm::MRC2: // 
        case id::arm::STC2: // 
    }
}