#include "operands.hpp"
#include "../identifiers/string_shifters.hpp"
#include "../interpreter/mnemonic_arm.hpp"
#include "../interpreter/lexer.hpp"

#include <llarm/shared/out.hpp>

operand_struct operands::lex_to_operands_arm(const lexemes_t &lexemes, const mnemonic_struct_arm &mnemonic) {
    operand_struct arg;

    u8 reg_iteration = 1;
    u8 CR_reg_iteration = 1;
    u8 int_iteration = 1;

    // it should be noted that all instructions that contain things like reglists, and PSRs 
    // only have those argument types appear once, unlike immeds or regs. That's why they 
    // don't have an iteration mechanism where repeating argument types are organised in 
    // enumerated orders (first, second, third, etc...). So if a reglist appears, it's 
    // guaranteed that it won't appear again.

    for (const auto &lexeme : lexemes) {
        switch (lexeme.token_type) {
            case UNKNOWN: llarm::out::dev_error("Invalid lexeme for converting IR to assembly");
            case REG_LIST: reg_list(arg, lexeme); continue;
            case REG: reg(reg_iteration, CR_reg_iteration, arg, lexeme); continue;
            case IMMED: imm(int_iteration, arg, lexeme); continue;
            case OPTION: imm(int_iteration, arg, lexeme); continue;
            case PSR: psr(arg, lexeme); continue;
            case PRE_INDEX: arg.has_preindex = true; continue;
            case REG_LIST_START: continue;
            case REG_LIST_END: continue;
            case HASHTAG: continue;
            case MUL_OP: continue;
            case MIN_OP: continue;
            case MEM_START: continue;
            case MEM_END: continue;
            case LSL:
            case LSR:
            case ASR:
            case ROR:
            case RRX:
            case SHIFT:
            case CARET:
            case COMMENT: continue;
        }
    }

    // this is where the mnemonic analysis will begin

    arg.cond = [&]() -> u8 {
        switch (mnemonic.cond_id) {
            case cond_id::UNKNOWN: llarm::out::dev_error("Invalid cond id value for IR argument translation");
            case cond_id::NONE: return 0b1111;
            case cond_id::EQ: return 0b0000;
            case cond_id::NE: return 0b0001;
            case cond_id::CS: return 0b0010;
            case cond_id::HS: return 0b0010;
            case cond_id::CC: return 0b0011;
            case cond_id::LO: return 0b0011;
            case cond_id::MI: return 0b0100;
            case cond_id::PL: return 0b0101;
            case cond_id::VS: return 0b0110;
            case cond_id::VC: return 0b0111;
            case cond_id::HI: return 0b1000;
            case cond_id::LS: return 0b1001;
            case cond_id::GE: return 0b1010;
            case cond_id::LT: return 0b1011;
            case cond_id::GT: return 0b1100;
            case cond_id::LE: return 0b1101;
            case cond_id::AL: return 0b1110;
        }

        // reference: A3-6
    }();

    arg.has_S = mnemonic.has_S;
    arg.has_Z = mnemonic.has_Z;
    arg.has_L = mnemonic.has_L;
    arg.x_char = mnemonic.x_char;
    arg.y_char = mnemonic.y_char;

    // finishing touches with shifter analysis (if there's any to begin with)
    arg.shifter = ident::string_shifters::identify_shifter(lexemes, mnemonic);

    return arg;
}

operand_struct operands::lex_to_operands_thumb(const lexemes_t &lexemes, const mnemonic_struct_thumb &mnemonic) {
    d
}


void operands::reg(u8 &reg_iteration, u8 &CR_reg_iteration, operand_struct &arg, const lexeme &lexeme) {
    using enum reg_type;

    // I wish the reg_iteration and CR_reg_iteration could be static variables here,
    // but I couldn't find a reliable way to operate them in this context.

    const reg_type type = lexeme.data.reg.type;

    switch (type) {
        case FPSID: arg.vfp_special_reg = vfp_special_reg_enum::FPSID; break;
        case FPSCR: arg.vfp_special_reg = vfp_special_reg_enum::FPSCR; break;
        case FPEXC: arg.vfp_special_reg = vfp_special_reg_enum::FPEXC; break;
        case COPROC: arg.coproc = lexeme.data.reg.number; break;
        case CR: 
            switch (CR_reg_iteration) {
                case 1: arg.first_CR_reg = lexeme.data.reg.number; break;
                case 2: arg.second_CR_reg = lexeme.data.reg.number; break;
                case 3: arg.third_CR_reg = lexeme.data.reg.number; break;
            }

            CR_reg_iteration++;
            break;

        default:
            switch (reg_iteration) {
                case 1: arg.first_reg = lexeme.data.reg.number; break;
                case 2: arg.second_reg = lexeme.data.reg.number; break;
                case 3: arg.third_reg = lexeme.data.reg.number; break;
                case 4: arg.fourth_reg = lexeme.data.reg.number; break;
            }

            reg_iteration++;
    }
}


void operands::imm(u8 &int_iteration, operand_struct &arg, const lexeme &lexeme) {
    const u32 number = [&]() -> u32 {
        if (lexeme.token_type == OPTION) {
            return static_cast<u32>(lexeme.data.option.number);   
        }

        // this is most likely the case
        return static_cast<u32>(lexeme.data.imm.number);
    }();

    switch (int_iteration) {
        case 1: arg.first_int = number; break;
        case 2: arg.second_int = number; break;
        case 3: arg.third_int = number; break;
    }

    if (lexeme.data.imm.is_negative) {
        arg.has_minus = true;
    }

    int_iteration++;
}


void operands::psr(operand_struct &arg, const lexeme &lexeme) {
    arg.has_spsr = lexeme.data.psr.is_spsr();

    const bool C = lexeme.data.psr.has_C();
    const bool X = lexeme.data.psr.has_X();
    const bool S = lexeme.data.psr.has_S();
    const bool F = lexeme.data.psr.has_F();

    if ((C + X + S + F) == 0) {
        return;
    }

    // we know that at least one field flag is set after this point

    u8 fields = 0;
    
    // read A4-62 for more information
    llarm::util::modify_bit(fields, 0, C);
    llarm::util::modify_bit(fields, 1, X);
    llarm::util::modify_bit(fields, 2, S);
    llarm::util::modify_bit(fields, 3, F);

    arg.PSR_field_mask = fields;

    return;
}


void operands::reg_list(operand_struct &arg, const lexeme &lexeme) {
    arg.reg_list = lexeme.data.reg_list.list;
}