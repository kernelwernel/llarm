#include "string_shifters.hpp"
#include "llarm-asm/src/interpreter/IR.hpp"
#include "../shifter_id.hpp"
#include "../instruction_id.hpp"

#include "../interpreter/interpreter.hpp"

#include "../interpreter/tokens.hpp"
#include "shared/types.hpp"

using namespace internal;
using enum token_enum;
    
shifter_enum ident::string_shifters::data_instruction(const lexemes_t &lexemes) {
    using namespace interpreter;

    if (verify_tokens({ REG, REG, HASHTAG, IMMED }, lexemes)) {
        return shifter_enum::DATA_IMM;
    }

    // alternative to the above, this is for exclusively setting the rotation value
    if (verify_tokens({ REG, REG, HASHTAG, IMMED, IMMED }, lexemes)) {
        return shifter_enum::DATA_IMM;
    }

    if (verify_tokens({ REG, REG, REG }, lexemes)) {
        return shifter_enum::DATA_REG;
    }

    if (verify_tokens({ REG, REG, REG, LSL, HASHTAG, IMMED }, lexemes)) {
        return shifter_enum::DATA_IMM_LSL;
    }

    if (verify_tokens({ REG, REG, REG, LSL, REG }, lexemes)) {
        return shifter_enum::DATA_REG_LSL;
    }

    if (verify_tokens({ REG, REG, REG, LSR, HASHTAG, IMMED }, lexemes)) {
        return shifter_enum::DATA_IMM_LSR;
    }

    if (verify_tokens({ REG, REG, REG, LSR, REG }, lexemes)) {
        return shifter_enum::DATA_REG_LSR;
    }
    
    if (verify_tokens({ REG, REG, REG, ASR, HASHTAG, IMMED }, lexemes)) {
        return shifter_enum::DATA_IMM_ASR;
    }

    if (verify_tokens({ REG, REG, REG, ASR, REG }, lexemes)) {
        return shifter_enum::DATA_REG_ASR;
    }

    if (verify_tokens({ REG, REG, REG, ROR, HASHTAG, IMMED }, lexemes)) {
        return shifter_enum::DATA_IMM_ROR;
    }

    if (verify_tokens({ REG, REG, REG, ROR, REG }, lexemes)) {
        return shifter_enum::DATA_REG_ROR;
    }

    if (verify_tokens({ REG, REG, REG, RRX }, lexemes)) {
        return shifter_enum::DATA_RRX;
    }

    return shifter_enum::UNKNOWN;
}


// PLD has an exception to its addressing mode format
shifter_enum ident::string_shifters::ls_instruction_PLD(const lexemes_t &lexemes) {
    using namespace interpreter;

    if (verify_tokens({ MEM_START, REG, HASHTAG, HASHTAG, IMMED, MEM_END }, lexemes)) {
        return shifter_enum::LS_IMM;
    }

    if (verify_tokens({ MEM_START, REG, REG, MEM_END }, lexemes)) {
        return shifter_enum::LS_REG;
    }

    if (verify_tokens({ MEM_START, REG, REG, SHIFT, HASHTAG, IMMED, MEM_END }, lexemes)) {
        const token_enum shift = lexemes.at(4).token_type;

        switch (shift) {
            case LSL: return shifter_enum::LS_SCALED_LSL;
            case LSR: return shifter_enum::LS_SCALED_LSR;
            case ASR: return shifter_enum::LS_SCALED_ASR;
            case ROR: return shifter_enum::LS_SCALED_ROR;
            default: return shifter_enum::UNKNOWN;
        }
    }

    if (verify_tokens({ MEM_START, REG, REG, RRX, MEM_END }, lexemes)) {
        return shifter_enum::LS_SCALED_RRX;
    }

    return shifter_enum::UNKNOWN;
}


shifter_enum ident::string_shifters::ls_instruction(const lexemes_t &lexemes) {
    using namespace interpreter;

    if (verify_tokens({ REG, MEM_START, REG, HASHTAG, IMMED, MEM_END }, lexemes)) {
        return shifter_enum::LS_IMM;
    }

    if (verify_tokens({ REG, MEM_START, REG, REG, MEM_END }, lexemes)) {
        return shifter_enum::LS_REG;
    }

    if (verify_tokens({ REG, MEM_START, REG, REG, SHIFT, HASHTAG, IMMED, MEM_END }, lexemes)) {
        const token_enum shift = lexemes.at(5).token_type;

        switch (shift) {
            case LSL: return shifter_enum::LS_SCALED_LSL;
            case LSR: return shifter_enum::LS_SCALED_LSR;
            case ASR: return shifter_enum::LS_SCALED_ASR;
            case ROR: return shifter_enum::LS_SCALED_ROR;
            default: return shifter_enum::UNKNOWN;
        }
    }

    if (verify_tokens({ REG, MEM_START, REG, REG, RRX, MEM_END }, lexemes)) {
        return shifter_enum::LS_SCALED_RRX;
    }

    if (verify_tokens({ REG, MEM_START, REG, HASHTAG, IMMED, MEM_END, PRE_INDEX }, lexemes)) {
        return shifter_enum::LS_IMM_PRE;
    }

    if (verify_tokens({ REG, MEM_START, REG, REG, MEM_END, PRE_INDEX }, lexemes)) {
        return shifter_enum::LS_REG_PRE;
    }

    if (verify_tokens({ REG, MEM_START, REG, REG, SHIFT, HASHTAG, IMMED, MEM_END, PRE_INDEX }, lexemes)) {
        const token_enum shift = lexemes.at(5).token_type;

        switch (shift) {
            case LSL: return shifter_enum::LS_SCALED_PRE_LSL;
            case LSR: return shifter_enum::LS_SCALED_PRE_LSR;
            case ASR: return shifter_enum::LS_SCALED_PRE_ASR;
            case ROR: return shifter_enum::LS_SCALED_PRE_ROR;
            default: return shifter_enum::UNKNOWN;
        }
    }

    if (verify_tokens({ REG, MEM_START, REG, REG, RRX, MEM_END, PRE_INDEX }, lexemes)) {
        return shifter_enum::LS_SCALED_PRE_RRX;
    }

    if (verify_tokens({ REG, MEM_START, REG, MEM_END, HASHTAG, IMMED }, lexemes)) {
        return shifter_enum::LS_IMM_POST;
    }

    if (verify_tokens({ REG, MEM_START, REG, MEM_END, REG }, lexemes)) {
        return shifter_enum::LS_REG_POST;
    }

    if (verify_tokens({ REG, MEM_START, REG, MEM_END, REG, SHIFT, HASHTAG, IMMED }, lexemes)) {
        const token_enum shift = lexemes.at(6).token_type;

        switch (shift) {
            case LSL: return shifter_enum::LS_SCALED_POST_LSL;
            case LSR: return shifter_enum::LS_SCALED_POST_LSR;
            case ASR: return shifter_enum::LS_SCALED_POST_ASR;
            case ROR: return shifter_enum::LS_SCALED_POST_ROR;
            default: return shifter_enum::UNKNOWN;
        }
    }

    if (verify_tokens({ REG, MEM_START, REG, MEM_END, REG, RRX }, lexemes)) {
        return shifter_enum::LS_SCALED_POST_RRX;
    }

    return shifter_enum::UNKNOWN;
}


shifter_enum ident::string_shifters::ls_misc_instruction(const lexemes_t &lexemes) {
    using namespace interpreter;

    if (verify_tokens({ REG, MEM_START, REG, HASHTAG, IMMED, MEM_END }, lexemes)) {
        return shifter_enum::LS_MISC_IMM;
    }

    if (verify_tokens({ REG, MEM_START, REG, REG, MEM_END }, lexemes)) {
        return shifter_enum::LS_MISC_REG;
    }

    if (verify_tokens({ REG, MEM_START, REG, HASHTAG, IMMED, MEM_END, PRE_INDEX }, lexemes)) {
        return shifter_enum::LS_MISC_IMM_PRE;
    }

    if (verify_tokens({ REG, MEM_START, REG, REG, MEM_END, PRE_INDEX }, lexemes)) {
        return shifter_enum::LS_MISC_REG_PRE;
    }

    if (verify_tokens({ REG, MEM_START, REG, MEM_END, HASHTAG, IMMED }, lexemes)) {
        return shifter_enum::LS_MISC_IMM_POST;
    }

    if (verify_tokens({ REG, MEM_START, REG, MEM_END, REG }, lexemes)) {
        return shifter_enum::LS_MISC_REG_POST;
    }

    return shifter_enum::UNKNOWN;
}


shifter_enum ident::string_shifters::ls_mul_instruction(const sv mnemonic) {
    const unsigned char second_char = mnemonic[mnemonic.size() - 1];
    const unsigned char first_char = mnemonic[mnemonic.size() - 2];

    const u16 addressing_mode = (first_char << 8 | second_char);

    constexpr u16 IA = ('I' << 8 | 'A');
    constexpr u16 IB = ('I' << 8 | 'B');
    constexpr u16 DA = ('D' << 8 | 'A');
    constexpr u16 DB = ('D' << 8 | 'B');

    switch (addressing_mode) {
        case IA: return shifter_enum::LS_MUL_INC_AFTER;
        case IB: return shifter_enum::LS_MUL_INC_BEFORE;
        case DA: return shifter_enum::LS_MUL_DEC_AFTER;
        case DB: return shifter_enum::LS_MUL_DEC_BEFORE;
    }

    return shifter_enum::UNKNOWN;
}


shifter_enum ident::string_shifters::ls_coproc_instruction(const lexemes_t &lexemes) {
    using namespace interpreter;

    if (verify_tokens({ REG, REG, MEM_START, REG, HASHTAG, IMMED, MUL_OP, IMMED, MEM_END }, lexemes)) {
        return shifter_enum::LS_COPROC_IMM;
    }

    if (verify_tokens({ REG, REG, MEM_START, REG, HASHTAG, IMMED, MUL_OP, IMMED, MEM_END, PRE_INDEX }, lexemes)) {
        return shifter_enum::LS_COPROC_IMM_PRE;
    }

    if (verify_tokens({ REG, REG, MEM_START, REG, MEM_END, HASHTAG, IMMED, MUL_OP, IMMED }, lexemes)) {
        return shifter_enum::LS_COPROC_IMM_POST;
    }

    if (verify_tokens({ REG, REG, MEM_START, REG, MEM_END, OPTION }, lexemes)) {
        return shifter_enum::LS_COPROC_UNINDEXED;
    }

    return shifter_enum::UNKNOWN;
}


shifter_enum ident::string_shifters::vfp_mul_instruction(const lexemes_t &lexemes, sv mnemonic) {
    using namespace interpreter;
    
    const u16 cond = fetch_last_2_chars(mnemonic);

    if (cond_match(cond)) {
        mnemonic.remove_suffix(2);
    }

    switch (mnemonic.back()) {
        case 'D':
        case 'S':
        case 'X': 
            mnemonic.remove_suffix(1);
    }

    const u16 addressing_mode = fetch_last_2_chars(mnemonic);

    constexpr u16 IA = ('I' << 8 | 'A');
    constexpr u16 DB = ('D' << 8 | 'B');

    if (addressing_mode == DB) {
        if (verify_tokens({ REG, PRE_INDEX, REG_LIST }, lexemes)) {
            return shifter_enum::VFP_LS_MUL_DEC;
        }
    }

    if (addressing_mode == IA) {
        if (verify_tokens({ REG, PRE_INDEX, REG_LIST }, lexemes)) {
            return shifter_enum::VFP_LS_MUL_INC;
        }

        if (verify_tokens({ REG, REG_LIST }, lexemes)) {
            return shifter_enum::VFP_LS_MUL_UNINDEXED;
        }
    }

    return shifter_enum::UNKNOWN;
}


shifter_enum ident::string_shifters::identify_shifter(const IR_arm_struct &IR) {
    const id::arm id = IR.id;
    const lexemes_t lexemes = std::move(IR.lexemes); // maybe the move is not necessary, but whatever
    const sv mnemonic = IR.mnemonic;

    switch (id) {
        case id::arm::UNKNOWN: return shifter_enum::UNKNOWN;
        case id::arm::UNDEFINED: return shifter_enum::UNKNOWN;
        case id::arm::NOP: return shifter_enum::UNKNOWN;
        case id::arm::ADC: return data_instruction(lexemes);
        case id::arm::ADD: return data_instruction(lexemes);
        case id::arm::AND: return data_instruction(lexemes);
        case id::arm::BIC: return data_instruction(lexemes);
        case id::arm::CMN: return data_instruction(lexemes);
        case id::arm::CMP: return data_instruction(lexemes);
        case id::arm::EOR: return data_instruction(lexemes);
        case id::arm::MOV: return data_instruction(lexemes);
        case id::arm::MVN: return data_instruction(lexemes);
        case id::arm::ORR: return data_instruction(lexemes);
        case id::arm::RSB: return data_instruction(lexemes);
        case id::arm::RSC: return data_instruction(lexemes);
        case id::arm::SBC: return data_instruction(lexemes);
        case id::arm::SUB: return data_instruction(lexemes);
        case id::arm::TEQ: return data_instruction(lexemes);
        case id::arm::TST: return data_instruction(lexemes);
        case id::arm::CMNP: return data_instruction(lexemes);
        case id::arm::CMPP: return data_instruction(lexemes);
        case id::arm::TEQP: return data_instruction(lexemes);
        case id::arm::TSTP: return data_instruction(lexemes);
        case id::arm::LDR: return ls_instruction(lexemes);
        case id::arm::LDRB: return ls_instruction(lexemes);
        case id::arm::LDRBT: return ls_instruction(lexemes);
        case id::arm::LDRT: return ls_instruction(lexemes);
        case id::arm::STR: return ls_instruction(lexemes);
        case id::arm::STRB: return ls_instruction(lexemes);
        case id::arm::STRBT: return ls_instruction(lexemes);
        case id::arm::STRT: return ls_instruction(lexemes);
        case id::arm::PLD: return ls_instruction_PLD(lexemes); // exception to addressing mode 2 (LS)
        case id::arm::STRH: return ls_misc_instruction(lexemes);
        case id::arm::LDRH: return ls_misc_instruction(lexemes);
        case id::arm::LDRSB: return ls_misc_instruction(lexemes);
        case id::arm::LDRSH: return ls_misc_instruction(lexemes);
        case id::arm::LDRD: return ls_misc_instruction(lexemes);
        case id::arm::STRD: return ls_misc_instruction(lexemes);
        case id::arm::LDM1: return ls_mul_instruction(mnemonic);
        case id::arm::LDM2: return ls_mul_instruction(mnemonic);
        case id::arm::LDM3: return ls_mul_instruction(mnemonic);
        case id::arm::STM1: return ls_mul_instruction(mnemonic); 
        case id::arm::STM2: return ls_mul_instruction(mnemonic);
        case id::arm::STC: return ls_coproc_instruction(lexemes);
        case id::arm::STC2: return ls_coproc_instruction(lexemes);
        case id::arm::LDC: return ls_coproc_instruction(lexemes);
        case id::arm::LDC2: return ls_coproc_instruction(lexemes);
        case id::arm::FLDMD: return vfp_mul_instruction(lexemes, mnemonic);
        case id::arm::FLDMS: return vfp_mul_instruction(lexemes, mnemonic);
        case id::arm::FLDMX: return vfp_mul_instruction(lexemes, mnemonic);
        case id::arm::FSTMD: return vfp_mul_instruction(lexemes, mnemonic);
        case id::arm::FSTMS: return vfp_mul_instruction(lexemes, mnemonic);
        case id::arm::FSTMX: return vfp_mul_instruction(lexemes, mnemonic);
        case id::arm::FABSS: return shifter_enum::VFP_SINGLE_MONADIC;
        case id::arm::FCPYS: return shifter_enum::VFP_SINGLE_MONADIC;
        case id::arm::FNEGS: return shifter_enum::VFP_SINGLE_MONADIC;
        case id::arm::FSQRTS: return shifter_enum::VFP_SINGLE_MONADIC;
        case id::arm::FCPYD: return shifter_enum::VFP_DOUBLE_MONADIC;
        case id::arm::FABSD: return shifter_enum::VFP_DOUBLE_MONADIC;
        case id::arm::FNEGD: return shifter_enum::VFP_DOUBLE_MONADIC;
        case id::arm::FSQRTD: return shifter_enum::VFP_DOUBLE_MONADIC;
        case id::arm::FADDD: return shifter_enum::VFP_DOUBLE;
        case id::arm::FDIVD: return shifter_enum::VFP_DOUBLE;
        case id::arm::FSUBD: return shifter_enum::VFP_DOUBLE;
        case id::arm::FMULD: return shifter_enum::VFP_DOUBLE;
        case id::arm::FNMULD: return shifter_enum::VFP_DOUBLE;
        case id::arm::FADDS: return shifter_enum::VFP_SINGLE;
        case id::arm::FDIVS: return shifter_enum::VFP_SINGLE;
        case id::arm::FMULS: return shifter_enum::VFP_SINGLE;
        case id::arm::FNMULS: return shifter_enum::VFP_SINGLE;
        case id::arm::FSUBS: return shifter_enum::VFP_SINGLE;
        case id::arm::FLDD: return shifter_enum::VFP_LS_MUL_SPECIAL;
        case id::arm::FLDS: return shifter_enum::VFP_LS_MUL_SPECIAL;
        case id::arm::FSTD: return shifter_enum::VFP_LS_MUL_SPECIAL;
        case id::arm::FSTS: return shifter_enum::VFP_LS_MUL_SPECIAL;
        default: return shifter_enum::NONE;
    }
}

shifter_enum ident::string_shifters::identify_shifter(const std::string &code) {
    return identify_shifter(IR::generate(code));
}