#include "string_shifters.hpp"
#include "../interpreter/IR.hpp"
#include "../id/shifter_id.hpp"
#include "../id/instruction_id.hpp"
#include "../interpreter/interpreter.hpp"
#include "../interpreter/tokens.hpp"
#include "../interpreter/IR_struct.hpp"

#include <llarm/shared/types.hpp>

using namespace internal;
using enum token_enum;
    
shifter_id ident::string_shifters::data_instruction(const lexemes_t& lexemes) {
    using namespace interpreter;

    if (verify_tokens(make_tokens(REG, REG, HASHTAG, IMMED), lexemes)) {
        return shifter_id::DATA_IMM;
    }

    // alternative to the above, this is for exclusively setting the rotation value
    if (verify_tokens(make_tokens(REG, REG, HASHTAG, IMMED, IMMED), lexemes)) {
        return shifter_id::DATA_IMM;
    }

    if (verify_tokens(make_tokens(REG, REG, REG), lexemes)) {
        return shifter_id::DATA_REG;
    }

    if (verify_tokens(make_tokens(REG, REG, REG, LSL, HASHTAG, IMMED), lexemes)) {
        return shifter_id::DATA_IMM_LSL;
    }

    if (verify_tokens(make_tokens(REG, REG, REG, LSL, REG), lexemes)) {
        return shifter_id::DATA_REG_LSL;
    }

    if (verify_tokens(make_tokens(REG, REG, REG, LSR, HASHTAG, IMMED), lexemes)) {
        return shifter_id::DATA_IMM_LSR;
    }

    if (verify_tokens(make_tokens(REG, REG, REG, LSR, REG), lexemes)) {
        return shifter_id::DATA_REG_LSR;
    }
    
    if (verify_tokens(make_tokens(REG, REG, REG, ASR, HASHTAG, IMMED), lexemes)) {
        return shifter_id::DATA_IMM_ASR;
    }

    if (verify_tokens(make_tokens(REG, REG, REG, ASR, REG), lexemes)) {
        return shifter_id::DATA_REG_ASR;
    }

    if (verify_tokens(make_tokens(REG, REG, REG, ROR, HASHTAG, IMMED), lexemes)) {
        return shifter_id::DATA_IMM_ROR;
    }

    if (verify_tokens(make_tokens(REG, REG, REG, ROR, REG), lexemes)) {
        return shifter_id::DATA_REG_ROR;
    }

    if (verify_tokens(make_tokens(REG, REG, REG, RRX), lexemes)) {
        return shifter_id::DATA_RRX;
    }

    return shifter_id::UNKNOWN;
}


// PLD has an exception to its addressing mode format
shifter_id ident::string_shifters::ls_instruction_PLD(const lexemes_t& lexemes) {
    using namespace interpreter;

    if (verify_tokens(make_tokens(MEM_START, REG, HASHTAG, HASHTAG, IMMED, MEM_END), lexemes)) {
        return shifter_id::LS_IMM;
    }

    if (verify_tokens(make_tokens(MEM_START, REG, REG, MEM_END), lexemes)) {
        return shifter_id::LS_REG;
    }

    if (verify_tokens(make_tokens(MEM_START, REG, REG, SHIFT, HASHTAG, IMMED, MEM_END), lexemes)) {
        const token_enum shift = lexemes.at(4).token_type;

        switch (shift) {
            case LSL: return shifter_id::LS_SCALED_LSL;
            case LSR: return shifter_id::LS_SCALED_LSR;
            case ASR: return shifter_id::LS_SCALED_ASR;
            case ROR: return shifter_id::LS_SCALED_ROR;
            default: return shifter_id::UNKNOWN;
        }
    }

    if (verify_tokens(make_tokens(MEM_START, REG, REG, RRX, MEM_END), lexemes)) {
        return shifter_id::LS_SCALED_RRX;
    }

    return shifter_id::UNKNOWN;
}


shifter_id ident::string_shifters::ls_instruction(const lexemes_t& lexemes) {
    using namespace interpreter;

    if (verify_tokens(make_tokens(REG, MEM_START, REG, HASHTAG, IMMED, MEM_END), lexemes)) {
        return shifter_id::LS_IMM;
    }

    if (verify_tokens(make_tokens(REG, MEM_START, REG, REG, MEM_END), lexemes)) {
        return shifter_id::LS_REG;
    }

    if (verify_tokens(make_tokens(REG, MEM_START, REG, REG, SHIFT, HASHTAG, IMMED, MEM_END), lexemes)) {
        const token_enum shift = lexemes.at(5).token_type;

        switch (shift) {
            case LSL: return shifter_id::LS_SCALED_LSL;
            case LSR: return shifter_id::LS_SCALED_LSR;
            case ASR: return shifter_id::LS_SCALED_ASR;
            case ROR: return shifter_id::LS_SCALED_ROR;
            default: return shifter_id::UNKNOWN;
        }
    }

    if (verify_tokens(make_tokens(REG, MEM_START, REG, REG, RRX, MEM_END), lexemes)) {
        return shifter_id::LS_SCALED_RRX;
    }

    if (verify_tokens(make_tokens(REG, MEM_START, REG, HASHTAG, IMMED, MEM_END, PRE_INDEX), lexemes)) {
        return shifter_id::LS_IMM_PRE;
    }

    if (verify_tokens(make_tokens(REG, MEM_START, REG, REG, MEM_END, PRE_INDEX), lexemes)) {
        return shifter_id::LS_REG_PRE;
    }

    if (verify_tokens(make_tokens(REG, MEM_START, REG, REG, SHIFT, HASHTAG, IMMED, MEM_END, PRE_INDEX), lexemes)) {
        const token_enum shift = lexemes.at(5).token_type;

        switch (shift) {
            case LSL: return shifter_id::LS_SCALED_PRE_LSL;
            case LSR: return shifter_id::LS_SCALED_PRE_LSR;
            case ASR: return shifter_id::LS_SCALED_PRE_ASR;
            case ROR: return shifter_id::LS_SCALED_PRE_ROR;
            default: return shifter_id::UNKNOWN;
        }
    }

    if (verify_tokens(make_tokens(REG, MEM_START, REG, REG, RRX, MEM_END, PRE_INDEX), lexemes)) {
        return shifter_id::LS_SCALED_PRE_RRX;
    }

    if (verify_tokens(make_tokens(REG, MEM_START, REG, MEM_END, HASHTAG, IMMED), lexemes)) {
        return shifter_id::LS_IMM_POST;
    }

    if (verify_tokens(make_tokens(REG, MEM_START, REG, MEM_END, REG), lexemes)) {
        return shifter_id::LS_REG_POST;
    }

    if (verify_tokens(make_tokens(REG, MEM_START, REG, MEM_END, REG, SHIFT, HASHTAG, IMMED), lexemes)) {
        const token_enum shift = lexemes.at(6).token_type;

        switch (shift) {
            case LSL: return shifter_id::LS_SCALED_POST_LSL;
            case LSR: return shifter_id::LS_SCALED_POST_LSR;
            case ASR: return shifter_id::LS_SCALED_POST_ASR;
            case ROR: return shifter_id::LS_SCALED_POST_ROR;
            default: return shifter_id::UNKNOWN;
        }
    }

    if (verify_tokens(make_tokens(REG, MEM_START, REG, MEM_END, REG, RRX), lexemes)) {
        return shifter_id::LS_SCALED_POST_RRX;
    }

    return shifter_id::UNKNOWN;
}


shifter_id ident::string_shifters::ls_misc_instruction(const lexemes_t& lexemes) {
    using namespace interpreter;

    if (verify_tokens(make_tokens(REG, MEM_START, REG, HASHTAG, IMMED, MEM_END), lexemes)) {
        return shifter_id::LS_MISC_IMM;
    }

    if (verify_tokens(make_tokens(REG, MEM_START, REG, REG, MEM_END), lexemes)) {
        return shifter_id::LS_MISC_REG;
    }

    if (verify_tokens(make_tokens(REG, MEM_START, REG, HASHTAG, IMMED, MEM_END, PRE_INDEX), lexemes)) {
        return shifter_id::LS_MISC_IMM_PRE;
    }

    if (verify_tokens(make_tokens(REG, MEM_START, REG, REG, MEM_END, PRE_INDEX), lexemes)) {
        return shifter_id::LS_MISC_REG_PRE;
    }

    if (verify_tokens(make_tokens(REG, MEM_START, REG, MEM_END, HASHTAG, IMMED), lexemes)) {
        return shifter_id::LS_MISC_IMM_POST;
    }

    if (verify_tokens(make_tokens(REG, MEM_START, REG, MEM_END, REG), lexemes)) {
        return shifter_id::LS_MISC_REG_POST;
    }

    return shifter_id::UNKNOWN;
}


shifter_id ident::string_shifters::ls_mul_instruction(const sv mnemonic) {
    const char second_char = mnemonic.at(mnemonic.size() - 1);
    const char first_char = mnemonic.at(mnemonic.size() - 2);

    const u16 addressing_mode = static_cast<u16>(first_char << 8 | second_char);

    constexpr u16 IA = ('I' << 8 | 'A');
    constexpr u16 IB = ('I' << 8 | 'B');
    constexpr u16 DA = ('D' << 8 | 'A');
    constexpr u16 DB = ('D' << 8 | 'B');

    switch (addressing_mode) {
        case IA: return shifter_id::LS_MUL_INC_AFTER;
        case IB: return shifter_id::LS_MUL_INC_BEFORE;
        case DA: return shifter_id::LS_MUL_DEC_AFTER;
        case DB: return shifter_id::LS_MUL_DEC_BEFORE;
    }

    return shifter_id::UNKNOWN;
}


shifter_id ident::string_shifters::ls_coproc_instruction(const lexemes_t& lexemes) {
    using namespace interpreter;

    if (verify_tokens(make_tokens(REG, REG, MEM_START, REG, HASHTAG, IMMED, MUL_OP, IMMED, MEM_END), lexemes)) {
        return shifter_id::LS_COPROC_IMM;
    }

    if (verify_tokens(make_tokens(REG, REG, MEM_START, REG, HASHTAG, IMMED, MUL_OP, IMMED, MEM_END, PRE_INDEX), lexemes)) {
        return shifter_id::LS_COPROC_IMM_PRE;
    }

    if (verify_tokens(make_tokens(REG, REG, MEM_START, REG, MEM_END, HASHTAG, IMMED, MUL_OP, IMMED), lexemes)) {
        return shifter_id::LS_COPROC_IMM_POST;
    }

    if (verify_tokens(make_tokens(REG, REG, MEM_START, REG, MEM_END, OPTION), lexemes)) {
        return shifter_id::LS_COPROC_UNINDEXED;
    }

    return shifter_id::UNKNOWN;
}


shifter_id ident::string_shifters::vfp_mul_instruction(const lexemes_t& lexemes, sv mnemonic) {
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
        if (verify_tokens(make_tokens(REG, PRE_INDEX, REG_LIST), lexemes)) {
            return shifter_id::VFP_LS_MUL_DEC;
        }
    }

    if (addressing_mode == IA) {
        if (verify_tokens(make_tokens(REG, PRE_INDEX, REG_LIST), lexemes)) {
            return shifter_id::VFP_LS_MUL_INC;
        }

        if (verify_tokens(make_tokens(REG, REG_LIST), lexemes)) {
            return shifter_id::VFP_LS_MUL_UNINDEXED;
        }
    }

    return shifter_id::UNKNOWN;
}


shifter_id ident::string_shifters::usat_instruction(const lexemes_t& lexemes) {
    using namespace interpreter;

    // no shifter
    if (lexemes.size() == 4) {
        return shifter_id::NONE;
    }
    
    if (lexemes.size() != 7) {
        return shifter_id::UNKNOWN;
    }

    // potential shifter after this point

    const token_enum shift_token = lexemes.at(4).token_type;

    if (shift_token == token_enum::ASR) {
        return shifter_id::USAT_ASR;
    }

    if (shift_token == token_enum::LSL) {
        return shifter_id::USAT_LSL;
    }

    return shifter_id::UNKNOWN;
}


shifter_id ident::string_shifters::identify_shifter(const lexemes_t& lexemes, const mnemonic_struct_arm& mnemonic) {
    const arm_id id = mnemonic.id;
    const sv instruction = mnemonic.instruction;

    switch (id) {
        case arm_id::UNKNOWN: return shifter_id::UNKNOWN;
        case arm_id::UNDEFINED: return shifter_id::UNKNOWN;
        case arm_id::NOP: return shifter_id::UNKNOWN;
        case arm_id::ADC: return data_instruction(lexemes);
        case arm_id::ADD: return data_instruction(lexemes);
        case arm_id::AND: return data_instruction(lexemes);
        case arm_id::BIC: return data_instruction(lexemes);
        case arm_id::CMN: return data_instruction(lexemes);
        case arm_id::CMP: return data_instruction(lexemes);
        case arm_id::EOR: return data_instruction(lexemes);
        case arm_id::MOV: return data_instruction(lexemes);
        case arm_id::MVN: return data_instruction(lexemes);
        case arm_id::ORR: return data_instruction(lexemes);
        case arm_id::RSB: return data_instruction(lexemes);
        case arm_id::RSC: return data_instruction(lexemes);
        case arm_id::SBC: return data_instruction(lexemes);
        case arm_id::SUB: return data_instruction(lexemes);
        case arm_id::TEQ: return data_instruction(lexemes);
        case arm_id::TST: return data_instruction(lexemes);
        case arm_id::CMNP: return data_instruction(lexemes);
        case arm_id::CMPP: return data_instruction(lexemes);
        case arm_id::TEQP: return data_instruction(lexemes);
        case arm_id::TSTP: return data_instruction(lexemes);
        case arm_id::LDR: return ls_instruction(lexemes);
        case arm_id::LDRB: return ls_instruction(lexemes);
        case arm_id::LDRBT: return ls_instruction(lexemes);
        case arm_id::LDRT: return ls_instruction(lexemes);
        case arm_id::STR: return ls_instruction(lexemes);
        case arm_id::STRB: return ls_instruction(lexemes);
        case arm_id::STRBT: return ls_instruction(lexemes);
        case arm_id::STRT: return ls_instruction(lexemes);
        case arm_id::PLD: return ls_instruction_PLD(lexemes); // exception to addressing mode 2 (LS)
        case arm_id::STRH: return ls_misc_instruction(lexemes);
        case arm_id::LDRH: return ls_misc_instruction(lexemes);
        case arm_id::LDRSB: return ls_misc_instruction(lexemes);
        case arm_id::LDRSH: return ls_misc_instruction(lexemes);
        case arm_id::LDRD: return ls_misc_instruction(lexemes);
        case arm_id::STRD: return ls_misc_instruction(lexemes);
        case arm_id::LDM1: return ls_mul_instruction(instruction);
        case arm_id::LDM2: return ls_mul_instruction(instruction);
        case arm_id::LDM3: return ls_mul_instruction(instruction);
        case arm_id::STM1: return ls_mul_instruction(instruction); 
        case arm_id::STM2: return ls_mul_instruction(instruction);
        case arm_id::STC: return ls_coproc_instruction(lexemes);
        case arm_id::STC2: return ls_coproc_instruction(lexemes);
        case arm_id::LDC: return ls_coproc_instruction(lexemes);
        case arm_id::LDC2: return ls_coproc_instruction(lexemes);
        case arm_id::FLDMD: return vfp_mul_instruction(lexemes, instruction);
        case arm_id::FLDMS: return vfp_mul_instruction(lexemes, instruction);
        case arm_id::FLDMX: return vfp_mul_instruction(lexemes, instruction);
        case arm_id::FSTMD: return vfp_mul_instruction(lexemes, instruction);
        case arm_id::FSTMS: return vfp_mul_instruction(lexemes, instruction);
        case arm_id::FSTMX: return vfp_mul_instruction(lexemes, instruction);
        case arm_id::FABSS: return shifter_id::VFP_SINGLE_MONADIC;
        case arm_id::FCPYS: return shifter_id::VFP_SINGLE_MONADIC;
        case arm_id::FNEGS: return shifter_id::VFP_SINGLE_MONADIC;
        case arm_id::FSQRTS: return shifter_id::VFP_SINGLE_MONADIC;
        case arm_id::FCPYD: return shifter_id::VFP_DOUBLE_MONADIC;
        case arm_id::FABSD: return shifter_id::VFP_DOUBLE_MONADIC;
        case arm_id::FNEGD: return shifter_id::VFP_DOUBLE_MONADIC;
        case arm_id::FSQRTD: return shifter_id::VFP_DOUBLE_MONADIC;
        case arm_id::FADDD: return shifter_id::VFP_DOUBLE;
        case arm_id::FDIVD: return shifter_id::VFP_DOUBLE;
        case arm_id::FSUBD: return shifter_id::VFP_DOUBLE;
        case arm_id::FMULD: return shifter_id::VFP_DOUBLE;
        case arm_id::FNMULD: return shifter_id::VFP_DOUBLE;
        case arm_id::FADDS: return shifter_id::VFP_SINGLE;
        case arm_id::FDIVS: return shifter_id::VFP_SINGLE;
        case arm_id::FMULS: return shifter_id::VFP_SINGLE;
        case arm_id::FNMULS: return shifter_id::VFP_SINGLE;
        case arm_id::FSUBS: return shifter_id::VFP_SINGLE;
        case arm_id::FLDD: return shifter_id::VFP_LS_MUL_SPECIAL;
        case arm_id::FLDS: return shifter_id::VFP_LS_MUL_SPECIAL;
        case arm_id::FSTD: return shifter_id::VFP_LS_MUL_SPECIAL;
        case arm_id::FSTS: return shifter_id::VFP_LS_MUL_SPECIAL;
        case arm_id::USAT: return usat_instruction(lexemes);
        default: return shifter_id::NONE;
    }
}

shifter_id ident::string_shifters::identify_shifter(const IR_arm_struct &&IR) {
    return identify_shifter(IR.lexemes, IR.mnemonic);
}

shifter_id ident::string_shifters::identify_shifter(const std::string& code) {
    return identify_shifter(IR::generate(code));
}