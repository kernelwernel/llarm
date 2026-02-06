
#include "u32_arm.hpp"
#include "../id/shifter_id.hpp"
#include "../identifiers/u32_arm.hpp"
#include "../identifiers/u32_shifters.hpp"

#include <llarm/shared/util.hpp>
#include <llarm/shared/types.hpp>

using namespace internal;

bool u32_arm::check_shifter(const u32 code, const shifter_category category) {
    const shifter_id shifter = ident::u32_shifters::identify_shifter(category, code);

    return (shifter != shifter_id::UNKNOWN);
};


// PLD instruction only has 3 LS shifters supported
bool u32_arm::check_PLD(const u32 code) {
    const shifter_id shifter = ident::u32_shifters::identify_shifter(shifter_category::LS, code);

    switch (shifter) {
        case shifter_id::LS_IMM: 
        case shifter_id::LS_REG:
        case shifter_id::LS_SCALED_ASR:
        case shifter_id::LS_SCALED_LSL:
        case shifter_id::LS_SCALED_LSR:
        case shifter_id::LS_SCALED_ROR:
        case shifter_id::LS_SCALED_RRX: return true;
        default: return false;
    }
};


// offset must be at least 0 and be an even number, and must have a valid reglist config
bool u32_arm::check_vfp_reglist(const u32 code, const arm_id id) {
    const u8 offset = llarm::util::bit_range<u8>(code, 0, 7);

    if (offset == 0 || offset & 1) {
        return false;
    }

    const u8 Dd = llarm::util::bit_range<u8>(code, 12, 15);

    switch (id) {
        case arm_id::FLDMD: 
        case arm_id::FSTMD: {
            if (((offset >> 1) + Dd) > 15) {
                return false;
            }
            break;
        }

        case arm_id::FLDMX:
        case arm_id::FSTMX: {
            if ((((offset >> 1) - 1) + Dd) > 15) {
                return false;
            }
            break;
        }
            
        case arm_id::FLDMS:
        case arm_id::FSTMS: {
            const bool D = (Dd & 1);
            const u8 Fd = llarm::util::bit_range<u8>(Dd, 1, 4);
            const u8 Sd = static_cast<u8>((Fd << 1) | D);

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
    const u8 reg = llarm::util::bit_range<u8>(code, 16, 19);

    switch (reg) {
        case 0b0000: // FPSID
        case 0b0001: // FPSCR
        case 0b1000: // FPEXC
            return true;
        default: return false; 
    } 
};


bool u32_arm::is_arm_instruction_valid(const u32 code) {
    const arm_id id = ident::u32_arm::arm(code);

    // TODO make check for branching isntructions like B, BL, BLX etc

    switch (id) {
        case arm_id::UNKNOWN: return false;
        case arm_id::UNDEFINED: return false;
        case arm_id::NOP: return false;
        case arm_id::ADC: return check_shifter(code, shifter_category::DATA);
        case arm_id::ADD: return check_shifter(code, shifter_category::DATA);
        case arm_id::RSB: return check_shifter(code, shifter_category::DATA);
        case arm_id::BIC: return check_shifter(code, shifter_category::DATA);
        case arm_id::RSC: return check_shifter(code, shifter_category::DATA);
        case arm_id::SBC: return check_shifter(code, shifter_category::DATA);
        case arm_id::SUB: return check_shifter(code, shifter_category::DATA);
        case arm_id::CMN: return check_shifter(code, shifter_category::DATA);
        case arm_id::AND: return check_shifter(code, shifter_category::DATA);
        case arm_id::CMP: return check_shifter(code, shifter_category::DATA);
        case arm_id::EOR: return check_shifter(code, shifter_category::DATA);
        case arm_id::ORR: return check_shifter(code, shifter_category::DATA);
        case arm_id::TEQ: return check_shifter(code, shifter_category::DATA);
        case arm_id::TST: return check_shifter(code, shifter_category::DATA);
        case arm_id::MOV: return check_shifter(code, shifter_category::DATA);
        case arm_id::MVN: return check_shifter(code, shifter_category::DATA);
        case arm_id::CMNP: return check_shifter(code, shifter_category::DATA);
        case arm_id::CMPP: return check_shifter(code, shifter_category::DATA);
        case arm_id::TEQP: return check_shifter(code, shifter_category::DATA);
        case arm_id::TSTP: return check_shifter(code, shifter_category::DATA);
        case arm_id::LDR: return check_shifter(code, shifter_category::LS);
        case arm_id::LDRB: return check_shifter(code, shifter_category::LS);
        case arm_id::LDRBT: return check_shifter(code, shifter_category::LS);
        case arm_id::LDRT: return check_shifter(code, shifter_category::LS);
        case arm_id::STR: return check_shifter(code, shifter_category::LS);
        case arm_id::STRB: return check_shifter(code, shifter_category::LS);
        case arm_id::STRBT: return check_shifter(code, shifter_category::LS);
        case arm_id::STRT: return check_shifter(code, shifter_category::LS);
        case arm_id::LDRH: return check_shifter(code, shifter_category::LS_MISC);
        case arm_id::LDRSB: return check_shifter(code, shifter_category::LS_MISC);
        case arm_id::LDRSH: return check_shifter(code, shifter_category::LS_MISC);
        case arm_id::STRH: return check_shifter(code, shifter_category::LS_MISC);
        case arm_id::LDM1: return check_shifter(code, shifter_category::LS_MUL);
        case arm_id::LDM2: return check_shifter(code, shifter_category::LS_MUL);
        case arm_id::LDM3: return check_shifter(code, shifter_category::LS_MUL);
        case arm_id::STM1: return check_shifter(code, shifter_category::LS_MUL);
        case arm_id::STM2: return check_shifter(code, shifter_category::LS_MUL);
        case arm_id::LDC: return check_shifter(code, shifter_category::LS_COPROC);
        case arm_id::STC: return check_shifter(code, shifter_category::LS_COPROC);
        case arm_id::LDC2: return check_shifter(code, shifter_category::LS_COPROC);
        case arm_id::STC2: return check_shifter(code, shifter_category::LS_COPROC);
        case arm_id::PLD: return check_PLD(code);
        case arm_id::FLDMS: return check_vfp_reglist(code, id);
        case arm_id::FLDMX: return check_vfp_reglist(code, id);
        case arm_id::FMRX: return check_move_system_reg(code);
        case arm_id::FMXR: return check_move_system_reg(code);
        case arm_id::FSTMS: return check_vfp_reglist(code, id);
        case arm_id::FSTMX: return check_vfp_reglist(code, id);
        case arm_id::FLDMD: return check_vfp_reglist(code, id);
        case arm_id::FSTMD: return check_vfp_reglist(code, id);
        default: return true;
    }
}