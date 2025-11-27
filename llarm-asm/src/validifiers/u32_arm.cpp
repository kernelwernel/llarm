
#include "u32_arm.hpp"
#include "../shifter_id.hpp"
#include "../identifiers/u32_arm.hpp"
#include "../identifiers/u32_shifters.hpp"

#include "shared/util.hpp"
#include "shared/types.hpp"

using namespace internal;

bool u32_arm::check_shifter(const u32 code, const shifter_category category) {
    const shifter_enum shifter = ident::u32_shifters::identify_shifter(category, code);

    return (shifter != shifter_enum::UNKNOWN);
};


// PLD instruction only has 3 LS shifters supported
bool u32_arm::check_PLD(const u32 code) {
    const shifter_enum shifter = ident::u32_shifters::identify_shifter(shifter_category::LS, code);

    switch (shifter) {
        case shifter_enum::LS_IMM: 
        case shifter_enum::LS_REG:
        case shifter_enum::LS_SCALED_ASR:
        case shifter_enum::LS_SCALED_LSL:
        case shifter_enum::LS_SCALED_LSR:
        case shifter_enum::LS_SCALED_ROR:
        case shifter_enum::LS_SCALED_RRX: return true;
        default: return false;
    }
};


// offset must be at least 0 and be an even number, and must have a valid reglist config
bool u32_arm::check_vfp_reglist(const u32 code, const id::arm id) {
    const u8 offset = shared::util::bit_range(code, 0, 7);

    if (offset == 0 || offset & 1) {
        return false;
    }

    const u8 Dd = shared::util::bit_range(code, 12, 15);

    switch (id) {
        case id::arm::FLDMD: 
        case id::arm::FSTMD: {
            if (((offset >> 1) + Dd) > 15) {
                return false;
            }
            break;
        }

        case id::arm::FLDMX:
        case id::arm::FSTMX: {
            if ((((offset >> 1) - 1) + Dd) > 15) {
                return false;
            }
            break;
        }
            
        case id::arm::FLDMS:
        case id::arm::FSTMS: {
            const bool D = (Dd & 1);
            const u8 Fd = shared::util::bit_range<u8>(Dd, 1, 4);
            const u8 Sd = ((Fd << 1) | D);

            if ((offset + Sd) > 31) {
                return false;
            }
            break;
        }

        default: return false;
    }

    return true;
};


bool u32_arm::check_move_system_reg(const u32 code) {
    const u8 reg = shared::util::bit_range(code, 16, 19);

    switch (reg) {
        case 0b0000: // FPSID
        case 0b0001: // FPSCR
        case 0b1000: // FPEXC
            return true;
        default: return false; 
    } 
};


bool u32_arm::is_arm_instruction_valid(const u32 code) {
    const id::arm id = ident::u32_arm::arm(code);

    // TODO make check for branching isntructions like B, BL, BLX etc

    switch (id) {
        case id::arm::UNKNOWN: return false;
        case id::arm::UNDEFINED: return false;
        case id::arm::NOP: return false;
        case id::arm::ADC: return check_shifter(code, shifter_category::DATA);
        case id::arm::ADD: return check_shifter(code, shifter_category::DATA);
        case id::arm::RSB: return check_shifter(code, shifter_category::DATA);
        case id::arm::BIC: return check_shifter(code, shifter_category::DATA);
        case id::arm::RSC: return check_shifter(code, shifter_category::DATA);
        case id::arm::SBC: return check_shifter(code, shifter_category::DATA);
        case id::arm::SUB: return check_shifter(code, shifter_category::DATA);
        case id::arm::CMN: return check_shifter(code, shifter_category::DATA);
        case id::arm::AND: return check_shifter(code, shifter_category::DATA);
        case id::arm::CMP: return check_shifter(code, shifter_category::DATA);
        case id::arm::EOR: return check_shifter(code, shifter_category::DATA);
        case id::arm::ORR: return check_shifter(code, shifter_category::DATA);
        case id::arm::TEQ: return check_shifter(code, shifter_category::DATA);
        case id::arm::TST: return check_shifter(code, shifter_category::DATA);
        case id::arm::MOV: return check_shifter(code, shifter_category::DATA);
        case id::arm::MVN: return check_shifter(code, shifter_category::DATA);
        case id::arm::CMNP: return check_shifter(code, shifter_category::DATA);
        case id::arm::CMPP: return check_shifter(code, shifter_category::DATA);
        case id::arm::TEQP: return check_shifter(code, shifter_category::DATA);
        case id::arm::TSTP: return check_shifter(code, shifter_category::DATA);
        case id::arm::LDR: return check_shifter(code, shifter_category::LS);
        case id::arm::LDRB: return check_shifter(code, shifter_category::LS);
        case id::arm::LDRBT: return check_shifter(code, shifter_category::LS);
        case id::arm::LDRT: return check_shifter(code, shifter_category::LS);
        case id::arm::STR: return check_shifter(code, shifter_category::LS);
        case id::arm::STRB: return check_shifter(code, shifter_category::LS);
        case id::arm::STRBT: return check_shifter(code, shifter_category::LS);
        case id::arm::STRT: return check_shifter(code, shifter_category::LS);
        case id::arm::LDRH: return check_shifter(code, shifter_category::LS_MISC);
        case id::arm::LDRSB: return check_shifter(code, shifter_category::LS_MISC);
        case id::arm::LDRSH: return check_shifter(code, shifter_category::LS_MISC);
        case id::arm::STRH: return check_shifter(code, shifter_category::LS_MISC);
        case id::arm::LDM1: return check_shifter(code, shifter_category::LS_MUL);
        case id::arm::LDM2: return check_shifter(code, shifter_category::LS_MUL);
        case id::arm::LDM3: return check_shifter(code, shifter_category::LS_MUL);
        case id::arm::STM1: return check_shifter(code, shifter_category::LS_MUL);
        case id::arm::STM2: return check_shifter(code, shifter_category::LS_MUL);
        case id::arm::LDC: return check_shifter(code, shifter_category::LS_COPROC);
        case id::arm::STC: return check_shifter(code, shifter_category::LS_COPROC);
        case id::arm::LDC2: return check_shifter(code, shifter_category::LS_COPROC);
        case id::arm::STC2: return check_shifter(code, shifter_category::LS_COPROC);
        case id::arm::PLD: return check_PLD(code);
        case id::arm::FLDMS: return check_vfp_reglist(code, id);
        case id::arm::FLDMX: return check_vfp_reglist(code, id);
        case id::arm::FMRX: return check_move_system_reg(code);
        case id::arm::FMXR: return check_move_system_reg(code);
        case id::arm::FSTMS: return check_vfp_reglist(code, id);
        case id::arm::FSTMX: return check_vfp_reglist(code, id);
        case id::arm::FLDMD: return check_vfp_reglist(code, id);
        case id::arm::FSTMD: return check_vfp_reglist(code, id);
        default: return true;
    }
}