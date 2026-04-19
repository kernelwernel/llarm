#include "../generators.hpp"
#include "../../../encoding_utils.hpp"

#include <llarm/shared/util.hpp>
#include <llarm/shared/out.hpp>

// format: <opcode>{<cond>}{S} <Rd>, <Rn>, <shifter_operand>
u32 generators::data_instruction(const arm_id id, const operand_struct& args) {
    u32 binary = 0;

    llarm::util::swap_bits(binary, 28, 31, args.cond);

    const bool is_26_bit_instruction = [=]() -> bool {
        switch (id) {
            case arm_id::CMNP: 
            case arm_id::CMPP: 
            case arm_id::TEQP: 
            case arm_id::TSTP: return true;   
            default: return false;
        }
    }();

    if (is_26_bit_instruction) {
        llarm::util::modify_bit(binary, 24, true);
        llarm::util::modify_bit(binary, 20, true);
        llarm::util::swap_bits(binary, 12, 15, 0b1111);
        llarm::util::swap_bits(binary, 16, 19, args.first_reg);

        u8 opcode = 0;

        switch (id) {
            case arm_id::CMNP: opcode = 0b11; break;
            case arm_id::CMPP: opcode = 0b10; break;
            case arm_id::TEQP: opcode = 0b01; break;
            case arm_id::TSTP: opcode = 0b00; break;
            default: break; // impossible to be otherwise, but whatever
        }

        llarm::util::swap_bits(binary, 21, 22, opcode);
    } else {
        if (args.has_S) {
            llarm::util::modify_bit(binary, 20, true);
        }

        bool Rd_present = true;
        bool Rn_present = true;
        u8 opcode = 0;

        // bits 26 and 27 are 0 for all instructions below, so they're ignored

        switch (id) {
            case arm_id::ADC: opcode = 0b0101; break;
            case arm_id::ADD: opcode = 0b0100; break;
            case arm_id::AND: opcode = 0b0000; break;
            case arm_id::BIC: opcode = 0b1110; break;
            case arm_id::EOR: opcode = 0b0001; break;
            case arm_id::ORR: opcode = 0b1100; break;
            case arm_id::RSB: opcode = 0b0011; break;
            case arm_id::SBC: opcode = 0b0110; break;
            case arm_id::RSC: opcode = 0b0111; break;
            case arm_id::SUB: opcode = 0b0010; break;

            case arm_id::TST: 
                opcode = 0b1000;
                Rd_present = false;
                break;

            case arm_id::TEQ: 
                opcode = 0b1001;
                Rd_present = false;
                break;

            case arm_id::CMP:
                opcode = 0b1010;
                Rd_present = false;
                break;

            case arm_id::CMN:
                opcode = 0b1011;
                Rd_present = false;
                break;

            case arm_id::MOV: 
                opcode = 0b1101;
                Rn_present = false;
                break;

            case arm_id::MVN: 
                opcode = 0b1111;
                Rn_present = false;
                break;

            default: llarm::out::dev_error("Invalid configuration to data instruction pattern generation");
        }

        llarm::util::swap_bits(binary, 21, 24, opcode);

        if (Rd_present) {
            llarm::util::swap_bits(binary, 12, 15, args.first_reg);
        }

        if (Rn_present) {
            llarm::util::swap_bits(binary, 16, 19, args.second_reg);
        }
    }

    auto check_immed = [](const u32 immed) -> void {
        if (immed > 31) {
            llarm::out::dev_error("Unencodable immediate shifted argument to data instruction pattern generation, immediate is too big");
        }
    };

    switch (args.shifter) {
        case shifter_id::DATA_REG: llarm::util::swap_bits(binary, 0, 3, args.third_reg); break;
        case shifter_id::DATA_RRX:
            llarm::util::modify_bit(binary, 5, true);
            llarm::util::modify_bit(binary, 6, true);
            llarm::util::swap_bits(binary, 0, 3, args.third_reg);
            break;

        case shifter_id::DATA_IMM_LSL:
            check_immed(args.first_int);
        
            llarm::util::swap_bits(binary, 0, 3, args.third_reg);
            llarm::util::swap_bits(binary, 7, 11, static_cast<u8>(args.first_int));
            break;

        case shifter_id::DATA_IMM_LSR:
            check_immed(args.first_int);

            llarm::util::modify_bit(binary, 5, true);
            llarm::util::swap_bits(binary, 0, 3, args.third_reg);
            llarm::util::swap_bits(binary, 7, 11, static_cast<u8>(args.first_int));
            break;

        case shifter_id::DATA_IMM_ASR:
            check_immed(args.first_int);

            llarm::util::modify_bit(binary, 6, true);
            llarm::util::swap_bits(binary, 0, 3, args.third_reg);
            llarm::util::swap_bits(binary, 7, 11, static_cast<u8>(args.first_int));
            break;

        case shifter_id::DATA_IMM_ROR:
            check_immed(args.first_int);

            llarm::util::modify_bit(binary, 5, true);
            llarm::util::modify_bit(binary, 6, true);
            llarm::util::swap_bits(binary, 0, 3, static_cast<u8>(args.third_reg));
            llarm::util::swap_bits(binary, 7, 11, static_cast<u8>(args.first_int));
            break;

        case shifter_id::DATA_REG_LSL:
            llarm::util::modify_bit(binary, 4, true);
            llarm::util::swap_bits(binary, 0, 3, static_cast<u8>(args.third_reg));
            llarm::util::swap_bits(binary, 8, 11, static_cast<u8>(args.fourth_reg));
            break;

        case shifter_id::DATA_REG_LSR:
            llarm::util::modify_bit(binary, 4, true);
            llarm::util::modify_bit(binary, 5, true);
            llarm::util::swap_bits(binary, 0, 3, static_cast<u8>(args.third_reg));
            llarm::util::swap_bits(binary, 8, 11, static_cast<u8>(args.fourth_reg));
            break;

        case shifter_id::DATA_REG_ASR:
            llarm::util::modify_bit(binary, 4, true);
            llarm::util::modify_bit(binary, 6, true);
            llarm::util::swap_bits(binary, 0, 3, static_cast<u8>(args.third_reg));
            llarm::util::swap_bits(binary, 8, 11, static_cast<u8>(args.fourth_reg));
            break;

        case shifter_id::DATA_REG_ROR:
            llarm::util::modify_bit(binary, 4, true);
            llarm::util::modify_bit(binary, 5, true);
            llarm::util::modify_bit(binary, 6, true);
            llarm::util::swap_bits(binary, 0, 3, static_cast<u8>(args.third_reg));
            llarm::util::swap_bits(binary, 8, 11, static_cast<u8>(args.fourth_reg));
            break;

        case shifter_id::DATA_IMM: {
            llarm::util::modify_bit(binary, 25, true); 

            const u32 immed = args.first_int;

            if (encoders::is_imm_encodable(immed) == false) {
                llarm::out::dev_error("Unencodable immediate argument to data instruction pattern generation");
            }

            encoders::encode_imm(binary, immed);

            break;
        }

        default: llarm::out::dev_error("Invalid shifter configuration to data instruction pattern generation");
    }

    return binary;
}