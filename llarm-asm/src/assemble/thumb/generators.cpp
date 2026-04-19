#include "generators.hpp"
#include <llarm/shared/out.hpp>
#include <llarm/shared/util.hpp>
#include <llarm/shared/types.hpp>

using namespace internal;

u16 generators::imm8(u16 opcode, const operand_struct& operands) {
    llarm::util::swap_bits(opcode, 0, 7, static_cast<u8>(operands.first_int));
    return opcode;
}


u16 generators::Rd_Rm(u16 opcode, const operand_struct& operands) {
    llarm::util::swap_bits(opcode, 0, 2, operands.first_reg);
    llarm::util::swap_bits(opcode, 3, 5, operands.second_reg);
    return opcode;
}


u16 generators::Rd_Rm_imm3(u16 opcode, const operand_struct& operands) {
    llarm::util::swap_bits(opcode, 0, 2, operands.first_reg);
    llarm::util::swap_bits(opcode, 3, 5, operands.second_reg);
    llarm::util::swap_bits(opcode, 6, 8, operands.first_int);
    return opcode;
}


u16 generators::Rd_Rm_imm5(u16 opcode, const operand_struct& operands) {
    llarm::util::swap_bits(opcode, 0, 2, operands.first_reg);
    llarm::util::swap_bits(opcode, 3, 5, operands.second_reg);
    llarm::util::swap_bits(opcode, 6, 10, operands.first_int);
    return opcode;
}


u16 generators::Rd_imm8(u16 opcode, const operand_struct& operands) {
    llarm::util::swap_bits(opcode, 8, 10, operands.first_reg);
    llarm::util::swap_bits(opcode, 0, 7, operands.first_int);
    return opcode;
}


u16 generators::reglist(u16 opcode, const operand_struct& operands) {
    const u8 reglist = llarm::util::bit_range<u8>(operands.reg_list, 0, 7);
    const bool R = llarm::util::bit_fetch(operands.reg_list, 15);

    llarm::util::swap_bits(opcode, 0, 7, reglist);
    llarm::util::modify_bit(opcode, 8, R);

    return opcode;
}


u16 generators::Rd_Rn_Rm(u16 opcode, const operand_struct& operands) {
    llarm::util::swap_bits(opcode, 0, 2, operands.first_reg);
    llarm::util::swap_bits(opcode, 3, 5, operands.second_reg);
    llarm::util::swap_bits(opcode, 6, 8, operands.third_reg);
    return opcode;
}


u16 generators::Rm_special(u16 opcode, const operand_struct& operands) {
    llarm::util::swap_bits(opcode, 3, 6, operands.first_reg);
    return opcode;
}


u16 generators::Rn_preindex_reglist(u16 opcode, const operand_struct& operands) {
    llarm::util::swap_bits(opcode, 0, 7, operands.reg_list);
    llarm::util::swap_bits(opcode, 10, 8, operands.first_reg);
    return opcode;
}


u16 generators::Rd_Rn_imm5_2(u16 opcode, const operand_struct& operands) {
    llarm::util::swap_bits(opcode, 0, 2, operands.first_reg);
    llarm::util::swap_bits(opcode, 3, 5, operands.second_reg);
    llarm::util::swap_bits(opcode, 6, 10, (operands.first_int >> 1)); // imm5 must be divided by 2 by design
    return opcode;
}

u16 generators::Rd_Rn_imm5_4(u16 opcode, const operand_struct& operands) {
    llarm::util::swap_bits(opcode, 0, 2, operands.first_reg);
    llarm::util::swap_bits(opcode, 3, 5, operands.second_reg);
    llarm::util::swap_bits(opcode, 6, 10, (operands.first_int >> 2)); // same as above but by 4
    return opcode;
}


u16 generators::Rd_special_imm8_4(u16 opcode, const operand_struct& operands) {
    llarm::util::swap_bits(opcode, 8, 10, operands.first_reg);
    llarm::util::swap_bits(opcode, 0, 7, (operands.first_int >> 2));
    return opcode;
}


u16 generators::SP_imm7_4(u16 opcode, const operand_struct& operands) {
    llarm::util::swap_bits(opcode, 0, 6, (operands.first_int >> 2));
    return opcode;
}


u16 generators::Rd_Rm_special(u16 opcode, const operand_struct& operands) {
    const u8 Rd_bits = llarm::util::bit_range<u8>(operands.first_reg, 0, 2);
    const u8 Rm_bits = llarm::util::bit_range<u8>(operands.second_reg, 0, 2);

    const bool H1 = llarm::util::bit_fetch(operands.first_reg, 3);
    const bool H2 = llarm::util::bit_fetch(operands.second_reg, 3);

    llarm::util::swap_bits(opcode, 0, 2, Rd_bits);
    llarm::util::swap_bits(opcode, 3, 5, Rm_bits);

    llarm::util::modify_bit(opcode, 7, H1);
    llarm::util::modify_bit(opcode, 6, H2);

    return opcode;
}


u16 generators::B1(const operand_struct& operands, const u32 PC) {
    u16 binary = 0b1101'0000'0000'0000;

    llarm::util::swap_bits(binary, 8, 11, operands.cond);

    const u32 target_address = operands.first_int;

    const u32 base_address = PC + 4;
    const i32 byte_offset = static_cast<i32>(target_address - base_address);
    
    if (byte_offset < -256 || byte_offset > 254) {
        llarm::out::error("B1 thumb instruction byte offset is out of range");
    }
    
    if ((byte_offset & 1) != 0) {
        llarm::out::error("B1 thumb instruction byte offset is not aligned");
    }
    
    const i8 signed_immed_8 = static_cast<i8>(byte_offset >> 1);
    
    llarm::util::swap_bits(binary, 0, 7, static_cast<u8>(signed_immed_8));
    
    return binary;
}


u16 generators::B2(const operand_struct& operands, const u32 PC) {
    u16 binary = 0b1110'0000'0000'0000;
    
    const u32 target_address = operands.first_int;

    const u32 base_address = PC + 4;
    
    const i32 byte_offset = static_cast<i32>(target_address - base_address);

    if ((byte_offset & 1) != 0) {
        llarm::out::error("B2 thumb instruction byte offset is not aligned");
    }

    if (byte_offset < -2048 || byte_offset > 2046) {
        llarm::out::error("B2 thumb instruction byte offset is out of range");
    }

    const i16 signed_immed_11 = static_cast<i16>(byte_offset / 2);
    llarm::util::swap_bits(binary, 0, 10, static_cast<u16>(signed_immed_11) & 0x7FF);

    return binary;
}


u32 generators::BL_BLX1(const operand_struct& operands, const u32 PC, const thumb_id id) {
    const u32 target_address = [&]() -> u32 {
        u32 addr = operands.first_int;
        // BLX: force bit[1] of target to match bit[1] of base address
        if (id == thumb_id::BLX1) {
            const u32 base_address = PC + 4;
            addr = (addr & ~0b10U) | (base_address & 0b10);
        }
        return addr;
    }();

    const u32 base_address = PC + 4;
    const i32 offset = static_cast<i32>(target_address - base_address);

    // range check: -2^22 <= offset <= +2^22 - 2
    if (offset < -(1 << 22) || offset > (1 << 22) - 2) {
        llarm::out::dev_error("BL/BLX1 thumb instruction byte offset is out of range");
    }

    if ((offset & 1) != 0) {
        llarm::out::dev_error("BL/BLX1 thumb instruction byte offset is not aligned");
    }

    // first halfword: H=10, upper offset bits [22:12]
    u16 first = 0b1111'0000'0000'0000;  // H=10, shared between BL and BLX1
    llarm::util::swap_bits(first, 0, 10, (static_cast<u32>(offset) >> 12) & 0x7FF);

    // second halfword: H=11 for BL, H=01 for BLX1, lower offset bits [11:1]
    u16 second = [&]() -> u16 {
        if (id == thumb_id::BL) {
            return 0b1111'1000'0000'0000;  // H=11
        }

        if (id == thumb_id::BLX1) { 
            return 0b1110'1000'0000'0000;  // H=01
        }

        llarm::out::dev_error("Invalid instruction id in BL_BLX1");
    }();

    llarm::util::swap_bits(second, 0, 10, (static_cast<u32>(offset) >> 1) & 0x7FF);

    return static_cast<u32>((first << 16) | second);
}


u32 generators::thumb(const IR_thumb_struct& IR) {
    const thumb_id id = IR.mnemonic.id;
    const operand_struct& operands = IR.operands;
    
    // the raw binary in the parameters are the opcodes themselves.
    // they're not complete (especially at the tail end) because
    // the operands will fill those spaces during the assembly process.
    // So they're basically opcode templates to build on top of.
    
    switch (id) {
        case thumb_id::UNKNOWN: return 0;
        case thumb_id::UNDEFINED: return 0;
        case thumb_id::NOP: return 0;
        case thumb_id::ADC: return Rd_Rm(0b0100'0001'0100'0000, operands);
        case thumb_id::SBC: return Rd_Rm(0b0100'0001'1000'0000, operands);
        case thumb_id::MUL: return Rd_Rm(0b0100'0011'0100'0000, operands);
        case thumb_id::AND: return Rd_Rm(0b0100'0000'0000'0000, operands);
        case thumb_id::ASR2: return Rd_Rm(0b0100'0001'0000'0000, operands);
        case thumb_id::BIC: return Rd_Rm(0b0100'0011'1000'0000, operands);
        case thumb_id::EOR: return Rd_Rm(0b0100'0000'0100'0000, operands);
        case thumb_id::LSL2: return Rd_Rm(0b0100'0000'1000'0000, operands);
        case thumb_id::LSR2: return Rd_Rm(0b0100'0000'1100'0000, operands);
        case thumb_id::NEG: return Rd_Rm(0b0100'0010'0100'0000, operands);
        case thumb_id::ORR: return Rd_Rm(0b0100'0011'0000'0000, operands);
        case thumb_id::ROR: return Rd_Rm(0b0100'0001'1100'0000, operands);
        case thumb_id::TST: return Rd_Rm(0b0100'0010'0000'0000, operands);
        case thumb_id::CMN: return Rd_Rm(0b0100'0010'1100'0000, operands);
        case thumb_id::CMP2: return Rd_Rm(0b0100'0010'1000'0000, operands);
        case thumb_id::MOV2: return Rd_Rm(0b0001'1100'0000'0000, operands);
        case thumb_id::MVN: return Rd_Rm(0b0100'0011'1100'0000, operands);
        case thumb_id::BKPT: return imm8(0b1011'1110'0000'0000, operands);
        case thumb_id::SWI: return imm8(0b1101'1111'0000'0000, operands);
        case thumb_id::LDR2: return Rd_Rn_Rm(0b0101'1000'0000'0000, operands);
        case thumb_id::LDRB2: return Rd_Rn_Rm(0b0101'1100'0000'0000, operands);
        case thumb_id::LDRH2: return Rd_Rn_Rm(0b0101'1010'0000'0000, operands);
        case thumb_id::LDRSB: return Rd_Rn_Rm(0b0101'0110'0000'0000, operands);
        case thumb_id::LDRSH: return Rd_Rn_Rm(0b0101'1110'0000'0000, operands);
        case thumb_id::STR2: return Rd_Rn_Rm(0b0101'0000'0000'0000, operands);
        case thumb_id::STRB2: return Rd_Rn_Rm(0b0101'0100'0000'0000, operands);
        case thumb_id::STRH2: return Rd_Rn_Rm(0b0101'0010'0000'0000, operands); 
        case thumb_id::MOV1: return Rd_imm8(0b0010'0000'0000'0000, operands);
        case thumb_id::CMP1: return Rd_imm8(0b0010'1000'0000'0000, operands);
        case thumb_id::ADD2: return Rd_imm8(0b0011'0000'0000'0000, operands);
        case thumb_id::SUB2: return Rd_imm8(0b0011'1000'0000'0000, operands);
        case thumb_id::ADD1: return Rd_Rm_imm3(0b0001'1100'0000'0000, operands);
        case thumb_id::SUB1: return Rd_Rm_imm3(0b0001'1110'0000'0000, operands);
        case thumb_id::ASR1: return Rd_Rm_imm5(0b0001'0000'0000'0000, operands);
        case thumb_id::LSL1: return Rd_Rm_imm5(0b0000'0000'0000'0000, operands);
        case thumb_id::LSR1: return Rd_Rm_imm5(0b0000'1000'0000'0000, operands);
        case thumb_id::POP: return reglist(0b1011'1100'0000'0000, operands);
        case thumb_id::PUSH: return reglist(0b1011'0100'0000'0000, operands);
        case thumb_id::ADD3: return Rd_Rn_Rm(0b0001'1000'0000'0000, operands);
        case thumb_id::SUB3: return Rd_Rn_Rm(0b0001'1010'0000'0000, operands);
        case thumb_id::LDMIA: return Rn_preindex_reglist(0b1100'1000'0000'0000, operands);
        case thumb_id::STMIA: return Rn_preindex_reglist(0b1100'0000'0000'0000, operands);
        case thumb_id::LDR1: return Rd_Rn_imm5_4(0b0110'1000'0000'0000, operands);
        case thumb_id::STR1: return Rd_Rn_imm5_4(0b0110'0000'0000'0000, operands);
        case thumb_id::LDRB1: return Rd_Rm_imm5(0b0111'1000'0000'0000, operands);
        case thumb_id::STRB1: return Rd_Rm_imm5(0b0111'0000'0000'0000, operands);
        case thumb_id::LDRH1: return Rd_Rn_imm5_2(0b1000'1000'0000'0000, operands);
        case thumb_id::STRH1: return Rd_Rn_imm5_2(0b1000'0000'0000'0000, operands);
        case thumb_id::LDR4: return Rd_special_imm8_4(0b1001'1000'0000'0000, operands);
        case thumb_id::STR3: return Rd_special_imm8_4(0b1001'0000'0000'0000, operands);
        case thumb_id::LDR3: return Rd_special_imm8_4(0b0100'1000'0000'0000, operands);
        case thumb_id::CMP3: return Rd_Rm_special(0b0100'0101'0000'0000, operands);
        case thumb_id::ADD4: return Rd_Rm_special(0b0100'0100'0000'0000, operands);
        case thumb_id::MOV3: return Rd_Rm_special(0b0100'0110'0000'0000, operands);
        case thumb_id::ADD5: return Rd_special_imm8_4(0b1010'0000'0000'0000, operands);
        case thumb_id::ADD6: return Rd_special_imm8_4(0b1010'1000'0000'0000, operands);
        case thumb_id::ADD7: return SP_imm7_4(0b1011'0000'0000'0000, operands);
        case thumb_id::SUB4: return SP_imm7_4(0b1011'0000'1000'0000, operands);
        case thumb_id::B1: return B1(operands, IR.PC);
        case thumb_id::B2: return B2(operands, IR.PC);
        case thumb_id::BL: return BL_BLX1(operands, IR.PC, id);
        case thumb_id::BLX1: return BL_BLX1(operands, IR.PC, id);
        case thumb_id::BL_BLX1_PREFIX: return BL_BLX1(operands, IR.PC, id);
        case thumb_id::BLX2: return Rm_special(0b0100'0111'1000'0000, operands);
        case thumb_id::BX: return Rm_special(0b0100'0111'0000'0000, operands);
    }

    return 0;
}