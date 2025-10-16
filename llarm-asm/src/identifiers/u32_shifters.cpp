#include "u32_shifters.hpp"
#include "identifiers.hpp"
#include "../shifter_id.hpp"
#include "../instruction_id.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"

using namespace internal;

shifter_enum u32_shifters::load_store(const u32 code) {
    using namespace shared::util;

    if (
        (bit_fetch(code, 27) != false) || 
        (bit_fetch(code, 26) != true)
    ) {
        return shifter_enum::UNKNOWN;
    }

    const u8 shift_type = (
        (bit_fetch(code, 25) << 2) |
        (bit_fetch(code, 24) << 1) |
        (bit_fetch(code, 21))
    );

    const u8 shift_case = shared::util::bit_range<u8>(code, 5, 6);
    const u8 shift_imm = shared::util::bit_range<u8>(code, 7, 11);

    // forgive me with the level of indentation, hopefully nobody sees this...

    switch (shift_type) {
        case 0b010: return shifter_enum::LS_IMM;
        case 0b011: return shifter_enum::LS_IMM_PRE;
        case 0b000: return shifter_enum::LS_IMM_POST;
        case 0b110: 
            if (shared::util::bit_range(code, 4, 11) == 0) {
                return shifter_enum::LS_REG;
            } else if (bit_fetch(code, 4) == 0) {
                switch (shift_case) {
                    case 0b00: return shifter_enum::LS_SCALED_LSL;
                    case 0b01: return shifter_enum::LS_SCALED_LSR;
                    case 0b10: return shifter_enum::LS_SCALED_ASR;
                    case 0b11:
                        if (shift_imm == 0) {
                            return shifter_enum::LS_SCALED_RRX;
                        }

                        return shifter_enum::LS_SCALED_ROR;
                }
            }

            break;

        case 0b111: 
            if (shared::util::bit_range(code, 4, 11) == 0) {
                return shifter_enum::LS_REG_PRE;
            } else if (bit_fetch(code, 4) == 0) {
                switch (shift_case) {
                    case 0b00: return shifter_enum::LS_SCALED_PRE_LSL;
                    case 0b01: return shifter_enum::LS_SCALED_PRE_LSR;
                    case 0b10: return shifter_enum::LS_SCALED_PRE_ASR;
                    case 0b11:
                        if (shift_imm == 0) {
                            return shifter_enum::LS_SCALED_PRE_RRX;
                        }

                        return shifter_enum::LS_SCALED_PRE_ROR;
                }
            }

            break;

        case 0b100: 
            if (shared::util::bit_range(code, 4, 11) == 0) {
                return shifter_enum::LS_REG_POST;
            } else if (bit_fetch(code, 4) == 0) {
                switch (shift_case) {
                    case 0b00: return shifter_enum::LS_SCALED_POST_LSL;
                    case 0b01: return shifter_enum::LS_SCALED_POST_LSR;
                    case 0b10: return shifter_enum::LS_SCALED_POST_ASR;
                    case 0b11:
                        if (shift_imm == 0) {
                            return shifter_enum::LS_SCALED_POST_RRX;
                        }

                        return shifter_enum::LS_SCALED_POST_ROR;
                }
            }
            
            break;
    }

    return shifter_enum::UNKNOWN;
}


shifter_enum u32_shifters::data_processing(const u32 code) {
    using namespace shared::util;

    if ((bit_fetch(code, 27) != false) || (bit_fetch(code, 26) != false)) {
        return shifter_enum::UNKNOWN;
    }

    const bool I = bit_fetch(code, 25);

    if (I) {
        return shifter_enum::DATA_IMM;
    }

    if (
        (bit_fetch(code, 11) == false) &&
        (bit_fetch(code, 10) == false) &&
        (bit_fetch(code, 9) == false) &&
        (bit_fetch(code, 8) == false) &&
        (bit_fetch(code, 7) == false) &&
        (bit_fetch(code, 6) == true) &&
        (bit_fetch(code, 5) == true) &&
        (bit_fetch(code, 4) == false)
    ) {
        return shifter_enum::DATA_RRX;
    }

    
    // immediate shift mode
    if (bit_fetch(code, 4) == false) {
        if (
            (bit_fetch(code, 11) == false) &&
            (bit_fetch(code, 10) == false) &&
            (bit_fetch(code, 9) == false) &&
            (bit_fetch(code, 8) == false) &&
            (bit_fetch(code, 7) == false) &&
            (bit_fetch(code, 6) == false) &&
            (bit_fetch(code, 5) == false)
        ) {
            return shifter_enum::DATA_REG;
        }

        const u8 bytecode = ((bit_fetch(code, 6) << 1) | bit_fetch(code, 5));
        
        switch (bytecode) {
            case 0b00: return shifter_enum::DATA_IMM_LSL;
            case 0b01: return shifter_enum::DATA_IMM_LSR;
            case 0b10: return shifter_enum::DATA_IMM_ASR;
            case 0b11: return shifter_enum::DATA_IMM_ROR;
        }
        
        return shifter_enum::UNKNOWN;
    }

    // register mode
    if (
        (bit_fetch(code, 7) == false) &&
        (bit_fetch(code, 4) == true)
    ) {
        const u8 bytecode = ((bit_fetch(code, 6) << 1) | bit_fetch(code, 5));

        switch (bytecode) {
            case 0b00: return shifter_enum::DATA_REG_LSL;
            case 0b01: return shifter_enum::DATA_REG_LSR;
            case 0b10: return shifter_enum::DATA_REG_ASR;
            case 0b11: return shifter_enum::DATA_REG_ROR;
        }
    }

    return shifter_enum::UNKNOWN;
}


shifter_enum u32_shifters::load_store_multiple(const u32 code) {
    using namespace shared::util;

    if (
        (bit_fetch(code, 27) != true) || 
        (bit_fetch(code, 26) != false) ||
        (bit_fetch(code, 25) != false)
    ) {
        return shifter_enum::UNKNOWN;
    }
    
    const u8 shift_type = shared::util::bit_range<u8>(code, 23, 24);

    switch (shift_type) {
        case 0b01: return shifter_enum::LS_MUL_INC_AFTER;
        case 0b11: return shifter_enum::LS_MUL_INC_BEFORE;
        case 0b00: return shifter_enum::LS_MUL_DEC_AFTER;
        case 0b10: return shifter_enum::LS_MUL_DEC_BEFORE;
    }

    return shifter_enum::UNKNOWN;
}


shifter_enum u32_shifters::load_store_misc(const u32 code) {
    using namespace shared::util;

    if (
        (bit_fetch(code, 27) != false) || 
        (bit_fetch(code, 26) != false) ||
        (bit_fetch(code, 25) != false) ||
        (bit_fetch(code, 7) != true) ||
        (bit_fetch(code, 4) != true)
    ) {
        return shifter_enum::UNKNOWN;
    }

    const u8 shift_type = ((bit_fetch(code, 24) << 2) | (bit_fetch(code, 22) << 1) | bit_fetch(code, 21));

    switch (shift_type) {
        case 0b110: return shifter_enum::LS_MISC_IMM;
        case 0b100: return shifter_enum::LS_MISC_REG;
        case 0b111: return shifter_enum::LS_MISC_IMM_PRE;
        case 0b101: return shifter_enum::LS_MISC_REG_PRE;
        case 0b010: return shifter_enum::LS_MISC_IMM_POST;
        case 0b000: return shifter_enum::LS_MISC_REG_POST;
    }

    return shifter_enum::UNKNOWN;
}


shifter_enum u32_shifters::load_store_coprocessor(const u32 code) {
    using namespace shared::util;

    if (
        (bit_fetch(code, 27) != true) ||
        (bit_fetch(code, 26) != true) ||
        (bit_fetch(code, 25) != false)
    ) {
        return shifter_enum::UNKNOWN;
    }

    const u8 shift_type = ((bit_fetch(code, 24) << 1) | (bit_fetch(code, 22)));

    switch (shift_type) {
        case 0b10: return shifter_enum::LS_COPROC_IMM;
        case 0b11: return shifter_enum::LS_COPROC_IMM_PRE;
        case 0b01: return shifter_enum::LS_COPROC_IMM_POST;
        case 0b00: return shifter_enum::LS_COPROC_UNINDEXED;
    }

    return shifter_enum::UNKNOWN;
}


shifter_enum u32_shifters::vfp_single(const u32 code) {
    const u8 Fd = shared::util::bit_range<u8>(code, 12, 15);
    const u8 Fm = shared::util::bit_range<u8>(code, 0, 3);

    const bool D = shared::util::bit_fetch(code, 22);
    const bool M = shared::util::bit_fetch(code, 5);

    const u8 d_num = ((Fd << 1) | D);
    const u8 m_num = ((Fm << 1) | M);

    const u8 d_bank = shared::util::bit_range<u8>(d_num, 3, 4);
    const u8 m_bank = shared::util::bit_range<u8>(m_num, 3, 4);

    if (d_bank == 0) {
        return shifter_enum::VFP_SINGLE_SCALAR;
    } else if (d_bank != 0 && m_bank == 0) {
        return shifter_enum::VFP_SINGLE_MIXED;
    } else if (d_bank != 0 && m_bank != 0) {
        return shifter_enum::VFP_SINGLE_VECTOR;
    }

    return shifter_enum::UNKNOWN;
}


shifter_enum u32_shifters::vfp_single_monadic(const u32 code) {
    const u8 Fd = shared::util::bit_range<u8>(code, 12, 15);
    const u8 Fm = shared::util::bit_range<u8>(code, 0, 3);

    const bool D = shared::util::bit_fetch(code, 22);
    const bool M = shared::util::bit_fetch(code, 5);

    const u8 d_num = ((Fd << 1) | D);
    const u8 m_num = ((Fm << 1) | M);

    const u8 d_bank = shared::util::bit_range<u8>(d_num, 3, 4);
    const u8 m_bank = shared::util::bit_range<u8>(m_num, 3, 4);
    
    if (d_bank == 0) {
        return shifter_enum::VFP_SINGLE_MONADIC_SCALAR_TO_SCALAR;
    } else if (d_bank != 0 && m_bank == 0) {
        return shifter_enum::VFP_SINGLE_MONADIC_SCALAR_TO_VECTOR;
    } else if (d_bank != 0 && m_bank != 0) {
        return shifter_enum::VFP_SINGLE_MONADIC_VECTOR_TO_VECTOR;
    }

    return shifter_enum::UNKNOWN;
}


shifter_enum u32_shifters::vfp_double(const u32 code) {
    const u8 Dd = shared::util::bit_range<u8>(code, 12, 15);
    const u8 Dn = shared::util::bit_range<u8>(code, 16, 19);
    const u8 Dm = shared::util::bit_range<u8>(code, 0, 3);

    const u8 d_bank = shared::util::bit_range<u8>(Dd, 2, 3);
    const u8 m_bank = shared::util::bit_range<u8>(Dm, 2, 3);
    
    if (d_bank == 0) {
        return shifter_enum::VFP_DOUBLE_SCALAR;
    } else  if (d_bank != 0 && m_bank == 0) {
        return shifter_enum::VFP_DOUBLE_MIXED;
    } else if (d_bank != 0 && m_bank != 0) {
        return shifter_enum::VFP_DOUBLE_VECTOR;
    }

    return shifter_enum::UNKNOWN;
}


shifter_enum u32_shifters::vfp_double_monadic(const u32 code) {
    const u8 Dd = shared::util::bit_range<u8>(code, 12, 15);
    const u8 Dm = shared::util::bit_range<u8>(code, 0, 3);

    const u8 d_bank = shared::util::bit_range<u8>(Dd, 2, 3);
    const u8 m_bank = shared::util::bit_range<u8>(Dm, 2, 3);

    if (d_bank == 0) {
        return shifter_enum::VFP_DOUBLE_MONADIC_SCALAR_TO_SCALAR;
    } else if (d_bank != 0 && m_bank == 0) {
        return shifter_enum::VFP_DOUBLE_MONADIC_SCALAR_TO_VECTOR;
    } else if (d_bank != 0 && m_bank != 0) {
        return shifter_enum::VFP_DOUBLE_MONADIC_VECTOR_TO_VECTOR;
    }

    return shifter_enum::UNKNOWN;
}


shifter_enum u32_shifters::vfp_ls_multiple(const u32 code) {
    const u8 bits_23_27 = shared::util::bit_range<u8>(code, 23, 27);
    const bool bit_21 = shared::util::bit_fetch(code, 21);
    
    if (bits_23_27 == 0b11001) {
        if (bit_21 == false) {
            return shifter_enum::VFP_LS_MUL_UNINDEXED;
        }

        // else if bit_21 == true
        return shifter_enum::VFP_LS_MUL_INC;
    }

    if (
        (bits_23_27 == 0b11010) && 
        (bit_21 == true)
    ) {
        return shifter_enum::VFP_LS_MUL_DEC;
    }

    return shifter_enum::UNKNOWN;
}


shifter_enum u32_shifters::identify_shifter(const u32 code) {
    const id::arm instruction = identifiers::arm(code);

    switch (instruction) {
        case id::arm::ADC:
        case id::arm::ADD:
        case id::arm::AND:
        case id::arm::BIC:
        case id::arm::CMN:
        case id::arm::CMP:
        case id::arm::EOR:
        case id::arm::MOV:
        case id::arm::MVN:
        case id::arm::ORR:
        case id::arm::RSB:
        case id::arm::RSC:
        case id::arm::SBC:
        case id::arm::SUB:
        case id::arm::TEQ:
        case id::arm::TST: return data_processing(code);
        case id::arm::LDR:
        case id::arm::LDRB:
        case id::arm::LDRBT:
        case id::arm::LDRT:
        case id::arm::STR:
        case id::arm::STRB:
        case id::arm::STRBT:
        case id::arm::PLD:
        case id::arm::STRT: return load_store(code);
        case id::arm::LDRH: 
        case id::arm::LDRSB:
        case id::arm::LDRSH:
        case id::arm::LDRD:
        case id::arm::STRD:
        case id::arm::STRH: return load_store_misc(code);
        case id::arm::LDM1:
        case id::arm::LDM2:
        case id::arm::LDM3:
        case id::arm::STM1:
        case id::arm::STM2: return load_store_multiple(code);
        case id::arm::LDC:
        case id::arm::STC: return load_store_coprocessor(code);
        case id::arm::FLDMS:
        case id::arm::FLDMX:
        case id::arm::FSTMD:
        case id::arm::FSTMS:
        case id::arm::FSTMX:
        case id::arm::FLDMD: return vfp_ls_multiple(code);
        case id::arm::UNKNOWN: return shifter_enum::UNKNOWN;
        case id::arm::UNDEFINED: return shifter_enum::UNKNOWN;
        default: return shifter_enum::NONE;
    }
}


// same as the function above but this acts more as a shortcut based on info that's already known
shifter_enum u32_shifters::identify_shifter(const shift_category shift_category, const u32 code) {
    switch (shift_category) {
        case shift_category::DATA: return data_processing(code);
        case shift_category::LS: return load_store(code);
        case shift_category::LS_MUL: return load_store_multiple(code);
        case shift_category::LS_MISC: return load_store_misc(code);
        case shift_category::LS_COPROC: return load_store_coprocessor(code);
        case shift_category::VFP_SINGLE: return vfp_single(code);
        case shift_category::VFP_SINGLE_MONADIC: return vfp_single_monadic(code);
        case shift_category::VFP_DOUBLE: return vfp_double(code);
        case shift_category::VFP_DOUBLE_MONADIC: return vfp_double_monadic(code);
        case shift_category::VFP_LS_MUL: return vfp_ls_multiple(code);
        default: return shifter_enum::UNKNOWN;
    }
}