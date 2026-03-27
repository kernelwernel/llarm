#include "bin_shifters.hpp"
#include "bin_arm.hpp"
#include "../id/shifter_id.hpp"
#include "../id/instruction_id.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>

using namespace internal;

shifter_id ident::bin_shifters::load_store(const u32 code) {
    using namespace llarm::util;

    if (
        (bit_fetch(code, 27) != false) || 
        (bit_fetch(code, 26) != true)
    ) {
        return shifter_id::UNKNOWN;
    }

    const u8 shift_type = static_cast<u8>(
        (bit_fetch(code, 25) << 2) |
        (bit_fetch(code, 24) << 1) |
        (bit_fetch(code, 21))
    );

    const u8 shift_case = llarm::util::bit_range<u8>(code, 5, 6);
    const u8 shift_imm = llarm::util::bit_range<u8>(code, 7, 11);

    // forgive me with the level of indentation, hopefully nobody sees this...

    switch (shift_type) {
        case 0b010: return shifter_id::LS_IMM;
        case 0b011: return shifter_id::LS_IMM_PRE;
        case 0b000: return shifter_id::LS_IMM_POST;
        case 0b110: 
            if (llarm::util::bit_range(code, 4, 11) == 0) {
                return shifter_id::LS_REG;
            } else if (bit_fetch(code, 4) == 0) {
                switch (shift_case) {
                    case 0b00: return shifter_id::LS_SCALED_LSL;
                    case 0b01: return shifter_id::LS_SCALED_LSR;
                    case 0b10: return shifter_id::LS_SCALED_ASR;
                    case 0b11:
                        if (shift_imm == 0) {
                            return shifter_id::LS_SCALED_RRX;
                        }

                        return shifter_id::LS_SCALED_ROR;
                }
            }

            break;

        case 0b111: 
            if (llarm::util::bit_range(code, 4, 11) == 0) {
                return shifter_id::LS_REG_PRE;
            } else if (bit_fetch(code, 4) == 0) {
                switch (shift_case) {
                    case 0b00: return shifter_id::LS_SCALED_PRE_LSL;
                    case 0b01: return shifter_id::LS_SCALED_PRE_LSR;
                    case 0b10: return shifter_id::LS_SCALED_PRE_ASR;
                    case 0b11:
                        if (shift_imm == 0) {
                            return shifter_id::LS_SCALED_PRE_RRX;
                        }

                        return shifter_id::LS_SCALED_PRE_ROR;
                }
            }

            break;

        case 0b100: 
            if (llarm::util::bit_range(code, 4, 11) == 0) {
                return shifter_id::LS_REG_POST;
            } else if (bit_fetch(code, 4) == 0) {
                switch (shift_case) {
                    case 0b00: return shifter_id::LS_SCALED_POST_LSL;
                    case 0b01: return shifter_id::LS_SCALED_POST_LSR;
                    case 0b10: return shifter_id::LS_SCALED_POST_ASR;
                    case 0b11:
                        if (shift_imm == 0) {
                            return shifter_id::LS_SCALED_POST_RRX;
                        }

                        return shifter_id::LS_SCALED_POST_ROR;
                }
            }
            
            break;
    }

    return shifter_id::UNKNOWN;
}


shifter_id ident::bin_shifters::data_processing(const u32 code) {
    using namespace llarm::util;

    if ((bit_fetch(code, 27) != false) || (bit_fetch(code, 26) != false)) {
        return shifter_id::UNKNOWN;
    }

    const bool I = bit_fetch(code, 25);

    if (I) {
        return shifter_id::DATA_IMM;
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
        return shifter_id::DATA_RRX;
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
            return shifter_id::DATA_REG;
        }

        const u8 bytecode = static_cast<u8>((bit_fetch(code, 6) << 1) | bit_fetch(code, 5));
        
        switch (bytecode) {
            case 0b00: return shifter_id::DATA_IMM_LSL;
            case 0b01: return shifter_id::DATA_IMM_LSR;
            case 0b10: return shifter_id::DATA_IMM_ASR;
            case 0b11: return shifter_id::DATA_IMM_ROR;
        }
        
        return shifter_id::UNKNOWN;
    }

    // register mode
    if (
        (bit_fetch(code, 7) == false) &&
        (bit_fetch(code, 4) == true)
    ) {
        const u8 bytecode = static_cast<u8>((bit_fetch(code, 6) << 1) | bit_fetch(code, 5));

        switch (bytecode) {
            case 0b00: return shifter_id::DATA_REG_LSL;
            case 0b01: return shifter_id::DATA_REG_LSR;
            case 0b10: return shifter_id::DATA_REG_ASR;
            case 0b11: return shifter_id::DATA_REG_ROR;
        }
    }

    return shifter_id::UNKNOWN;
}


shifter_id ident::bin_shifters::load_store_multiple(const u32 code) {
    using namespace llarm::util;

    if (
        (bit_fetch(code, 27) != true) || 
        (bit_fetch(code, 26) != false) ||
        (bit_fetch(code, 25) != false)
    ) {
        return shifter_id::UNKNOWN;
    }
    
    const u8 shift_type = llarm::util::bit_range<u8>(code, 23, 24);

    switch (shift_type) {
        case 0b01: return shifter_id::LS_MUL_INC_AFTER;
        case 0b11: return shifter_id::LS_MUL_INC_BEFORE;
        case 0b00: return shifter_id::LS_MUL_DEC_AFTER;
        case 0b10: return shifter_id::LS_MUL_DEC_BEFORE;
    }

    return shifter_id::UNKNOWN;
}


shifter_id ident::bin_shifters::load_store_misc(const u32 code) {
    using namespace llarm::util;

    if (
        (bit_fetch(code, 27) != false) || 
        (bit_fetch(code, 26) != false) ||
        (bit_fetch(code, 25) != false) ||
        (bit_fetch(code, 7) != true) ||
        (bit_fetch(code, 4) != true)
    ) {
        return shifter_id::UNKNOWN;
    }

    const u8 shift_type = static_cast<u8>((bit_fetch(code, 24) << 2) | (bit_fetch(code, 22) << 1) | bit_fetch(code, 21));

    switch (shift_type) {
        case 0b110: return shifter_id::LS_MISC_IMM;
        case 0b100: return shifter_id::LS_MISC_REG;
        case 0b111: return shifter_id::LS_MISC_IMM_PRE;
        case 0b101: return shifter_id::LS_MISC_REG_PRE;
        case 0b010: return shifter_id::LS_MISC_IMM_POST;
        case 0b000: return shifter_id::LS_MISC_REG_POST;
    }

    return shifter_id::UNKNOWN;
}


shifter_id ident::bin_shifters::load_store_coprocessor(const u32 code) {
    using namespace llarm::util;

    if (
        (bit_fetch(code, 27) != true) ||
        (bit_fetch(code, 26) != true) ||
        (bit_fetch(code, 25) != false)
    ) {
        return shifter_id::UNKNOWN;
    }

    const u8 shift_type = static_cast<u8>((bit_fetch(code, 24) << 1) | (bit_fetch(code, 22)));

    switch (shift_type) {
        case 0b10: return shifter_id::LS_COPROC_IMM;
        case 0b11: return shifter_id::LS_COPROC_IMM_PRE;
        case 0b01: return shifter_id::LS_COPROC_IMM_POST;
        case 0b00: return shifter_id::LS_COPROC_UNINDEXED;
    }

    return shifter_id::UNKNOWN;
}


shifter_id ident::bin_shifters::vfp_single(const u32 code) {
    const u8 Fd = llarm::util::bit_range<u8>(code, 12, 15);
    const u8 Fm = llarm::util::bit_range<u8>(code, 0, 3);

    const bool D = llarm::util::bit_fetch(code, 22);
    const bool M = llarm::util::bit_fetch(code, 5);

    const u8 d_num = static_cast<u8>((Fd << 1) | D);
    const u8 m_num = static_cast<u8>((Fm << 1) | M);

    const u8 d_bank = llarm::util::bit_range<u8>(d_num, 3, 4);
    const u8 m_bank = llarm::util::bit_range<u8>(m_num, 3, 4);

    if (d_bank == 0) {
        return shifter_id::VFP_SINGLE_SCALAR;
    } else if (d_bank != 0 && m_bank == 0) {
        return shifter_id::VFP_SINGLE_MIXED;
    } else if (d_bank != 0 && m_bank != 0) {
        return shifter_id::VFP_SINGLE_VECTOR;
    }

    return shifter_id::UNKNOWN;
}


shifter_id ident::bin_shifters::vfp_single_monadic(const u32 code) {
    const u8 Fd = llarm::util::bit_range<u8>(code, 12, 15);
    const u8 Fm = llarm::util::bit_range<u8>(code, 0, 3);

    const bool D = llarm::util::bit_fetch(code, 22);
    const bool M = llarm::util::bit_fetch(code, 5);

    const u8 d_num = static_cast<u8>((Fd << 1) | D);
    const u8 m_num = static_cast<u8>((Fm << 1) | M);

    const u8 d_bank = llarm::util::bit_range<u8>(d_num, 3, 4);
    const u8 m_bank = llarm::util::bit_range<u8>(m_num, 3, 4);
    
    if (d_bank == 0) {
        return shifter_id::VFP_SINGLE_MONADIC_SCALAR_TO_SCALAR;
    } else if (d_bank != 0 && m_bank == 0) {
        return shifter_id::VFP_SINGLE_MONADIC_SCALAR_TO_VECTOR;
    } else if (d_bank != 0 && m_bank != 0) {
        return shifter_id::VFP_SINGLE_MONADIC_VECTOR_TO_VECTOR;
    }

    return shifter_id::UNKNOWN;
}


shifter_id ident::bin_shifters::vfp_double(const u32 code) {
    const u8 Dd = llarm::util::bit_range<u8>(code, 12, 15);
    //const u8 Dn = llarm::util::bit_range<u8>(code, 16, 19);
    const u8 Dm = llarm::util::bit_range<u8>(code, 0, 3);

    const u8 d_bank = llarm::util::bit_range<u8>(Dd, 2, 3);
    const u8 m_bank = llarm::util::bit_range<u8>(Dm, 2, 3);
    
    if (d_bank == 0) {
        return shifter_id::VFP_DOUBLE_SCALAR;
    } else  if (d_bank != 0 && m_bank == 0) {
        return shifter_id::VFP_DOUBLE_MIXED;
    } else if (d_bank != 0 && m_bank != 0) {
        return shifter_id::VFP_DOUBLE_VECTOR;
    }

    return shifter_id::UNKNOWN;
}


shifter_id ident::bin_shifters::vfp_double_monadic(const u32 code) {
    const u8 Dd = llarm::util::bit_range<u8>(code, 12, 15);
    const u8 Dm = llarm::util::bit_range<u8>(code, 0, 3);

    const u8 d_bank = llarm::util::bit_range<u8>(Dd, 2, 3);
    const u8 m_bank = llarm::util::bit_range<u8>(Dm, 2, 3);

    if (d_bank == 0) {
        return shifter_id::VFP_DOUBLE_MONADIC_SCALAR_TO_SCALAR;
    } else if (d_bank != 0 && m_bank == 0) {
        return shifter_id::VFP_DOUBLE_MONADIC_SCALAR_TO_VECTOR;
    } else if (d_bank != 0 && m_bank != 0) {
        return shifter_id::VFP_DOUBLE_MONADIC_VECTOR_TO_VECTOR;
    }

    return shifter_id::UNKNOWN;
}


shifter_id ident::bin_shifters::vfp_ls_multiple(const u32 code) {
    const u8 bits_23_27 = llarm::util::bit_range<u8>(code, 23, 27);
    const bool bit_21 = llarm::util::bit_fetch(code, 21);
    
    if (bits_23_27 == 0b11001) {
        if (bit_21 == false) {
            return shifter_id::VFP_LS_MUL_UNINDEXED;
        }

        // else if bit_21 == true
        return shifter_id::VFP_LS_MUL_INC;
    }

    if (
        (bits_23_27 == 0b11010) && 
        (bit_21 == true)
    ) {
        return shifter_id::VFP_LS_MUL_DEC;
    }

    return shifter_id::UNKNOWN;
}


shifter_id ident::bin_shifters::identify_shifter(const u32 code) {
    const arm_id instruction = ident::bin_arm::arm(code);

    switch (instruction) {
        case arm_id::ADC:
        case arm_id::ADD:
        case arm_id::AND:
        case arm_id::BIC:
        case arm_id::CMN:
        case arm_id::CMP:
        case arm_id::EOR:
        case arm_id::MOV:
        case arm_id::MVN:
        case arm_id::ORR:
        case arm_id::RSB:
        case arm_id::RSC:
        case arm_id::SBC:
        case arm_id::SUB:
        case arm_id::TEQ:
        case arm_id::TST: return data_processing(code);
        case arm_id::LDR:
        case arm_id::LDRB:
        case arm_id::LDRBT:
        case arm_id::LDRT:
        case arm_id::STR:
        case arm_id::STRB:
        case arm_id::STRBT:
        case arm_id::PLD:
        case arm_id::STRT: return load_store(code);
        case arm_id::LDRH: 
        case arm_id::LDRSB:
        case arm_id::LDRSH:
        case arm_id::LDRD:
        case arm_id::STRD:
        case arm_id::STRH: return load_store_misc(code);
        case arm_id::LDM1:
        case arm_id::LDM2:
        case arm_id::LDM3:
        case arm_id::STM1:
        case arm_id::STM2: return load_store_multiple(code);
        case arm_id::LDC:
        case arm_id::STC: return load_store_coprocessor(code);
        case arm_id::FLDMS:
        case arm_id::FLDMX:
        case arm_id::FSTMD:
        case arm_id::FSTMS:
        case arm_id::FSTMX:
        case arm_id::FLDMD: return vfp_ls_multiple(code);
        case arm_id::UNKNOWN: return shifter_id::UNKNOWN;
        case arm_id::UNDEFINED: return shifter_id::UNKNOWN;
        default: return shifter_id::NONE;
    }
}


// same as the function above but this acts more as a shortcut based on info that's already known
shifter_id ident::bin_shifters::identify_shifter(const shifter_category shift_category, const u32 code) {
    switch (shift_category) {
        case shifter_category::DATA: return data_processing(code);
        case shifter_category::LS: return load_store(code);
        case shifter_category::LS_MUL: return load_store_multiple(code);
        case shifter_category::LS_MISC: return load_store_misc(code);
        case shifter_category::LS_COPROC: return load_store_coprocessor(code);
        case shifter_category::VFP_SINGLE: return vfp_single(code);
        case shifter_category::VFP_SINGLE_MONADIC: return vfp_single_monadic(code);
        case shifter_category::VFP_DOUBLE: return vfp_double(code);
        case shifter_category::VFP_DOUBLE_MONADIC: return vfp_double_monadic(code);
        case shifter_category::VFP_LS_MUL: return vfp_ls_multiple(code);
        default: return shifter_id::UNKNOWN;
    }
}


std::string ident::bin_shifters::code_to_shifter_string(const u32 code) {
    return shifter_id_to_string(identify_shifter(code));
}

std::string ident::bin_shifters::shifter_id_to_string(const shifter_id id) {
    switch (id) {
        case shifter_id::UNKNOWN: return "UNKNOWN";
        case shifter_id::NONE: return "NONE";
        case shifter_id::DATA_IMM: return "DATA_IMM";
        case shifter_id::DATA_RRX: return "DATA_RRX";
        case shifter_id::DATA_REG: return "DATA_REG";
        case shifter_id::DATA_IMM_LSL: return "DATA_IMM_LSL";
        case shifter_id::DATA_IMM_LSR: return "DATA_IMM_LSR";
        case shifter_id::DATA_IMM_ASR: return "DATA_IMM_ASR";
        case shifter_id::DATA_IMM_ROR: return "DATA_IMM_ROR";
        case shifter_id::DATA_REG_LSL: return "DATA_REG_LSL";
        case shifter_id::DATA_REG_LSR: return "DATA_REG_LSR";
        case shifter_id::DATA_REG_ASR: return "DATA_REG_ASR";
        case shifter_id::DATA_REG_ROR: return "DATA_REG_ROR";
        case shifter_id::LS_IMM: return "LS_IMM";
        case shifter_id::LS_IMM_PRE: return "LS_IMM_PRE";
        case shifter_id::LS_IMM_POST: return "LS_IMM_POST";
        case shifter_id::LS_REG: return "LS_REG";
        case shifter_id::LS_REG_PRE: return "LS_REG_PRE";
        case shifter_id::LS_REG_POST: return "LS_REG_POST";
        case shifter_id::LS_SCALED_LSL: return "LS_SCALED_LSL";
        case shifter_id::LS_SCALED_LSR: return "LS_SCALED_LSR";
        case shifter_id::LS_SCALED_ASR: return "LS_SCALED_ASR";
        case shifter_id::LS_SCALED_ROR: return "LS_SCALED_ROR";
        case shifter_id::LS_SCALED_RRX: return "LS_SCALED_RRX";
        case shifter_id::LS_SCALED_PRE_LSL: return "LS_SCALED_PRE_LSL";
        case shifter_id::LS_SCALED_PRE_LSR: return "LS_SCALED_PRE_LSR";
        case shifter_id::LS_SCALED_PRE_ASR: return "LS_SCALED_PRE_ASR";
        case shifter_id::LS_SCALED_PRE_ROR: return "LS_SCALED_PRE_ROR";
        case shifter_id::LS_SCALED_PRE_RRX: return "LS_SCALED_PRE_RRX";
        case shifter_id::LS_SCALED_POST_LSL: return "LS_SCALED_POST_LSL";
        case shifter_id::LS_SCALED_POST_LSR: return "LS_SCALED_POST_LSR";
        case shifter_id::LS_SCALED_POST_ASR: return "LS_SCALED_POST_ASR";
        case shifter_id::LS_SCALED_POST_ROR: return "LS_SCALED_POST_ROR";
        case shifter_id::LS_SCALED_POST_RRX: return "LS_SCALED_POST_RRX";
        case shifter_id::LS_MISC_IMM: return "LS_MISC_IMM";
        case shifter_id::LS_MISC_IMM_PRE: return "LS_MISC_IMM_PRE";
        case shifter_id::LS_MISC_IMM_POST: return "LS_MISC_IMM_POST";
        case shifter_id::LS_MISC_REG: return "LS_MISC_REG";
        case shifter_id::LS_MISC_REG_PRE: return "LS_MISC_REG_PRE";
        case shifter_id::LS_MISC_REG_POST: return "LS_MISC_REG_POST";
        case shifter_id::LS_MUL_INC_AFTER: return "LS_MUL_INC_AFTER";
        case shifter_id::LS_MUL_INC_BEFORE: return "LS_MUL_INC_BEFORE";
        case shifter_id::LS_MUL_DEC_AFTER: return "LS_MUL_DEC_AFTER";
        case shifter_id::LS_MUL_DEC_BEFORE: return "LS_MUL_DEC_BEFORE";
        case shifter_id::LS_COPROC_IMM: return "LS_COPROC_IMM";
        case shifter_id::LS_COPROC_IMM_PRE: return "LS_COPROC_IMM_PRE";
        case shifter_id::LS_COPROC_IMM_POST: return "LS_COPROC_IMM_POST";
        case shifter_id::LS_COPROC_UNINDEXED: return "LS_COPROC_UNINDEXED";
        case shifter_id::VFP_SINGLE: return "VFP_SINGLE";
        case shifter_id::VFP_SINGLE_SCALAR: return "VFP_SINGLE_SCALAR";
        case shifter_id::VFP_SINGLE_MIXED: return "VFP_SINGLE_MIXED";
        case shifter_id::VFP_SINGLE_VECTOR: return "VFP_SINGLE_VECTOR";
        case shifter_id::VFP_SINGLE_MONADIC: return "VFP_SINGLE_MONADIC";
        case shifter_id::VFP_SINGLE_MONADIC_SCALAR_TO_SCALAR: return "VFP_SINGLE_MONADIC_SCALAR_TO_SCALAR";
        case shifter_id::VFP_SINGLE_MONADIC_SCALAR_TO_VECTOR: return "VFP_SINGLE_MONADIC_SCALAR_TO_VECTOR";
        case shifter_id::VFP_SINGLE_MONADIC_VECTOR_TO_VECTOR: return "VFP_SINGLE_MONADIC_VECTOR_TO_VECTOR";
        case shifter_id::VFP_DOUBLE: return "VFP_DOUBLE";
        case shifter_id::VFP_DOUBLE_SCALAR: return "VFP_DOUBLE_SCALAR";
        case shifter_id::VFP_DOUBLE_MIXED: return "VFP_DOUBLE_MIXED";
        case shifter_id::VFP_DOUBLE_VECTOR: return "VFP_DOUBLE_VECTOR";
        case shifter_id::VFP_DOUBLE_MONADIC: return "VFP_DOUBLE_MONADIC";
        case shifter_id::VFP_DOUBLE_MONADIC_SCALAR_TO_SCALAR: return "VFP_DOUBLE_MONADIC_SCALAR_TO_SCALAR";
        case shifter_id::VFP_DOUBLE_MONADIC_SCALAR_TO_VECTOR: return "VFP_DOUBLE_MONADIC_SCALAR_TO_VECTOR";
        case shifter_id::VFP_DOUBLE_MONADIC_VECTOR_TO_VECTOR: return "VFP_DOUBLE_MONADIC_VECTOR_TO_VECTOR";
        case shifter_id::VFP_LS_MUL: return "VFP_LS_MUL";
        case shifter_id::VFP_LS_MUL_UNINDEXED: return "VFP_LS_MUL_UNINDEXED";
        case shifter_id::VFP_LS_MUL_INC: return "VFP_LS_MUL_INC";
        case shifter_id::VFP_LS_MUL_DEC: return "VFP_LS_MUL_DEC";
        case shifter_id::VFP_LS_MUL_SPECIAL: return "VFP_LS_MUL_SPECIAL";
    }

    return "UNKNOWN";
}