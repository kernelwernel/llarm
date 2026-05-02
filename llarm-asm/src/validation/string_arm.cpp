#include "string_arm.hpp"
#include "../identifiers/string_shifters.hpp"
#include "../interpreter/interpreter.hpp"
#include "../interpreter/IR.hpp"
#include "../interpreter/tokens.hpp"
#include "../id/shifter_id.hpp"
#include "../id/instruction_id.hpp"
#include "../encoding_utils.hpp"

using namespace internal;


bool validation::string_arm::is_arm_instruction_valid(const std::string& code, const u32 PC) {
    return is_arm_instruction_valid(IR::generate(code, PC));
}


bool validation::string_arm::is_arm_instruction_valid(const IR_arm_struct& IR) {
    using namespace interpreter;
    using enum token_enum;
    using enum reg_type;

    const lexemes_t& lexemes = IR.lexemes;

    switch (IR.mnemonic.id) {
        case arm_id::UNKNOWN: return false;
        case arm_id::UNDEFINED: return false;
        case arm_id::NOP: return false;

        // addressing mode 1: data processing
        case arm_id::ADC: 
        case arm_id::ADD:
        case arm_id::RSB:
        case arm_id::BIC:
        case arm_id::SUB:
        case arm_id::CMN:
        case arm_id::AND:
        case arm_id::CMP:
        case arm_id::RSC:
        case arm_id::SBC:
        case arm_id::EOR:
        case arm_id::ORR:
        case arm_id::TEQ:
        case arm_id::TST:
        case arm_id::MOV:
        case arm_id::MVN:
        case arm_id::CMNP:
        case arm_id::CMPP:
        case arm_id::TEQP:
        case arm_id::TSTP: return is_data_processing_valid(lexemes, IR.shifter_id, IR.mnemonic.id);

        // addressing mode 2: load store
        case arm_id::LDR:
        case arm_id::LDRB:
        case arm_id::LDRBT:
        case arm_id::LDRT:
        case arm_id::STR:
        case arm_id::STRB:
        case arm_id::STRBT:
        case arm_id::STRT: return is_ls_valid(lexemes, IR.shifter_id, IR.mnemonic.id);

        // addressing mode 3: load store misc
        case arm_id::STRH:
        case arm_id::LDRH:
        case arm_id::LDRSB:
        case arm_id::LDRSH:
        case arm_id::STRD:
        case arm_id::LDRD: return is_ls_misc_valid(lexemes, IR.shifter_id, IR.mnemonic.id);

        // addressing mode 4: load store multiple
        case arm_id::STM1: 
        case arm_id::LDM1: return (
            verify_lexemes(make_lexemes(reg(), reg_list()), lexemes) ||
            verify_lexemes(make_lexemes(reg(), token(PRE_INDEX), reg_list()), lexemes)
        );
        case arm_id::LDM2: return verify_lexemes(make_lexemes(reg(), reg_list_must_exclude_PC(), token(CARET)), lexemes);
        case arm_id::LDM3: return (
            verify_lexemes(make_lexemes(reg(), reg_list_must_include_PC(), token(CARET)), lexemes) ||
            verify_lexemes(make_lexemes(reg(), token(PRE_INDEX), reg_list_must_include_PC(), token(CARET)), lexemes)
        );
        case arm_id::STM2: return verify_lexemes(make_lexemes(reg(), reg_list(), token(CARET)), lexemes);

        // addressing mode 5: load store coprocessor
        case arm_id::STC:
        case arm_id::STC2:
        case arm_id::LDC:
        case arm_id::LDC2: return is_ls_coproc_valid(lexemes, IR.shifter_id);

        case arm_id::B:
        case arm_id::BL: return is_B_BL_valid(lexemes, IR.PC);

        case arm_id::SWI: return verify_lexemes(make_lexemes(immed(24)), lexemes);

        case arm_id::MCR2: 
        case arm_id::MCR: 
        case arm_id::MRC2:
        case arm_id::MRC:
            return (
                (verify_lexemes(make_lexemes(reg(COPROC), immed(2), reg(), reg(CR), reg(CR), immed(2)), lexemes)) || 
                (verify_lexemes(make_lexemes(reg(COPROC), immed(2), reg(), reg(CR), reg(CR)), lexemes))
            );

        case arm_id::SWP:
        case arm_id::SWPB:
            return (verify_lexemes(make_lexemes(reg(), reg(), token(MEM_START), reg(), token(MEM_END)), lexemes));

        case arm_id::QADD:
        case arm_id::QDADD:
        case arm_id::QDSUB:
        case arm_id::QSUB:
        case arm_id::SMULXY:
        case arm_id::SMULWY:
        case arm_id::MUL: return verify_lexemes(make_lexemes(reg(), reg(), reg()), lexemes);

        case arm_id::MLA:
        case arm_id::SMLAL:
        case arm_id::SMULL:
        case arm_id::UMLAL:
        case arm_id::SMLAXY:
        case arm_id::SMLALXY:
        case arm_id::SMLAWY:
        case arm_id::UMULL: return verify_lexemes(make_lexemes(reg(), reg(), reg(), reg()), lexemes);

        case arm_id::MRS: 
            return (
                (verify_lexemes(make_lexemes(reg(), psr(CPSR)), lexemes)) ||
                (verify_lexemes(make_lexemes(reg(), psr(SPSR)), lexemes))
            );

        case arm_id::MSR_IMM: // both these instructions are already verified in the identification process
        case arm_id::MSR_REG: return true; 
        case arm_id::BKPT: return verify_lexemes(make_lexemes(immed(16)), lexemes);
        case arm_id::BLX1:
        case arm_id::BX: return verify_lexemes(make_lexemes(reg()), lexemes);
        case arm_id::BLX2: return verify_lexemes(make_lexemes(reg()), lexemes);
        case arm_id::CLZ: return verify_lexemes(make_lexemes(reg(), reg()), lexemes);
        case arm_id::CDP2:
        case arm_id::CDP: return verify_lexemes(make_lexemes(reg(COPROC), immed(2), reg(CR), reg(CR), reg(CR), immed(2)), lexemes);
        case arm_id::MCRR:
        case arm_id::MRRC: return verify_lexemes(make_lexemes(reg(COPROC), immed(3), reg(), reg(), reg(CR)), lexemes);
        
        case arm_id::PLD: return (ident::string_shifters::identify_shifter(lexemes, IR.mnemonic) != shifter_id::UNKNOWN);

        case arm_id::FADDD: 
        case arm_id::FDIVD: 
        case arm_id::FMACD: 
        case arm_id::FMSCD: 
        case arm_id::FMULD: 
        case arm_id::FNMACD: 
        case arm_id::FNMSCD: 
        case arm_id::FNMULD: 
        case arm_id::FSUBD: return verify_lexemes(make_lexemes(reg(DOUBLE), reg(DOUBLE), reg(DOUBLE)), lexemes);
        
        case arm_id::FTOSIS: 
        case arm_id::FTOUIS: 
        case arm_id::FUITOS: 
        case arm_id::FSITOS: 
        case arm_id::FSQRTS: 
        case arm_id::FNEGS: 
        case arm_id::FCPYS: 
        case arm_id::FCMPS: 
        case arm_id::FABSS: 
        case arm_id::FCMPES: return verify_lexemes(make_lexemes(reg(SINGLE), reg(SINGLE)), lexemes);
        
        case arm_id::FABSD: 
        case arm_id::FCMPD: 
        case arm_id::FCMPED: 
        case arm_id::FCPYD: 
        case arm_id::FNEGD: 
        case arm_id::FSQRTD: return verify_lexemes(make_lexemes(reg(DOUBLE), reg(DOUBLE)), lexemes);
        
        case arm_id::FADDS:
        case arm_id::FDIVS:
        case arm_id::FMACS:
        case arm_id::FMSCS:
        case arm_id::FMULS:
        case arm_id::FNMACS:
        case arm_id::FNMSCS:
        case arm_id::FNMULS:
        case arm_id::FSUBS: return verify_lexemes(make_lexemes(reg(SINGLE), reg(SINGLE), reg(SINGLE)), lexemes);
        
        case arm_id::FTOSID:
        case arm_id::FCVTSD:
        case arm_id::FTOUID: return verify_lexemes(make_lexemes(reg(SINGLE), reg(DOUBLE)), lexemes);
        
        case arm_id::FCVTDS:
        case arm_id::FUITOD:
        case arm_id::FSITOD: return verify_lexemes(make_lexemes(reg(DOUBLE), reg(SINGLE)), lexemes);

        case arm_id::FCMPEZS:
        case arm_id::FCMPZS: return verify_lexemes(make_lexemes(reg(SINGLE)), lexemes);

        case arm_id::FCMPEZD:
        case arm_id::FCMPZD: return verify_lexemes(make_lexemes(reg(DOUBLE)), lexemes);

        case arm_id::FLDMS:
            return (
                (verify_lexemes(make_lexemes(reg(), token(PRE_INDEX), reg_list_single()), lexemes)) ||
                (verify_lexemes(make_lexemes(reg(), reg_list_single()), lexemes))
            );
        
        case arm_id::FMRS: return verify_lexemes(make_lexemes(reg(), reg(SINGLE)), lexemes);
        case arm_id::FMRX: return verify_lexemes(make_lexemes(reg(), reg(FP_WILDCARD)), lexemes);
        case arm_id::FMSR: return verify_lexemes(make_lexemes(reg(SINGLE), reg()), lexemes);
        case arm_id::FMSTAT: return true; // no arguments, so no room for errors
        case arm_id::FMXR: return verify_lexemes(make_lexemes(reg(FP_WILDCARD), reg()), lexemes);
        case arm_id::FSTMS:
            return (
                (verify_lexemes(make_lexemes(reg(), token(PRE_INDEX), reg_list_single()), lexemes)) ||
                (verify_lexemes(make_lexemes(reg(), reg_list_single()), lexemes))
            );

        case arm_id::FLDS:
        case arm_id::FSTS: 
            return (
                (verify_lexemes(make_lexemes(reg(SINGLE), token(MEM_START), reg(), token(MEM_END)), lexemes)) ||
                (verify_lexemes(make_lexemes(reg(SINGLE), token(MEM_START), reg(), token(HASHTAG), immed(7, 4), token(MEM_END)), lexemes))
            );

        case arm_id::FLDMD: 
        case arm_id::FSTMX:
        case arm_id::FLDMX:
        case arm_id::FSTMD: 
            return (
                (verify_lexemes(make_lexemes(reg(), token(PRE_INDEX), reg_list_double()), lexemes)) ||
                (verify_lexemes(make_lexemes(reg(), reg_list_double()), lexemes))
            );
            
        case arm_id::FMDHR: return verify_lexemes(make_lexemes(reg(DOUBLE), reg()), lexemes);
        case arm_id::FMDLR: return verify_lexemes(make_lexemes(reg(DOUBLE), reg()), lexemes);
        case arm_id::FMRDL: return verify_lexemes(make_lexemes(reg(), reg(DOUBLE)), lexemes);
        case arm_id::FMRDH: return verify_lexemes(make_lexemes(reg(), reg(DOUBLE)), lexemes);
        case arm_id::FSTD: 
        case arm_id::FLDD: 
            return (
                (verify_lexemes(make_lexemes(reg(DOUBLE), token(MEM_START), reg(), token(MEM_END)), lexemes)) ||
                (verify_lexemes(make_lexemes(reg(DOUBLE), token(MEM_START), reg(), token(HASHTAG), immed(7, 4), token(MEM_END)), lexemes))
            );

        case arm_id::CPS: // TODO
        case arm_id::CPY: // TODO
        case arm_id::LDREX: // TODO
        case arm_id::MCRR2: // TODO
        case arm_id::MRRC2: // TODO
        case arm_id::PKHBT: // TODO
        case arm_id::PKHTB: // TODO
        case arm_id::QADD16: // TODO
        case arm_id::QADD8: // TODO
        case arm_id::QADDSUBX: // TODO
        case arm_id::QSUB16: // TODO
        case arm_id::QSUB8: // TODO
        case arm_id::QSUBADDX: // TODO
        case arm_id::REV: // TODO
        case arm_id::REV16: // TODO
        case arm_id::REVSH: // TODO
        case arm_id::RFE: // TODO
        case arm_id::SADD16: // TODO
        case arm_id::SADD8: // TODO
        case arm_id::SADDSUBX: // TODO
        case arm_id::SEL: // TODO
        case arm_id::SETEND: // TODO
        case arm_id::SHADD16: // TODO
        case arm_id::SHADD8: // TODO
        case arm_id::SHADDSUBX: // TODO
        case arm_id::SHSUB16: // TODO
        case arm_id::SHSUB8: // TODO
        case arm_id::SHSUBADDX: // TODO
        case arm_id::SMLAD: // TODO
        case arm_id::SMLALD: // TODO
        case arm_id::SMLSD: // TODO
        case arm_id::SMLSLD: // TODO
        case arm_id::SMMLA: // TODO
        case arm_id::SMMLS: // TODO
        case arm_id::SMMUL: // TODO
        case arm_id::SMUAD: // TODO
        case arm_id::SMUSD: // TODO
        case arm_id::SRS: // TODO
        case arm_id::SSAT: // TODO
        case arm_id::SSAT16: // TODO
        case arm_id::SSUB16: // TODO
        case arm_id::SSUB8: // TODO
        case arm_id::SSUBADDX: // TODO
        case arm_id::STREX: // TODO
        case arm_id::SXTAB: // TODO
        case arm_id::SXTAB16: // TODO
        case arm_id::SXTAH: // TODO
        case arm_id::SXTB: // TODO
        case arm_id::SXTB16: // TODO
        case arm_id::SXTH: // TODO
        case arm_id::UADD16: // TODO
        case arm_id::UADD8: // TODO
        case arm_id::UADDSUBX: // TODO
        case arm_id::UHADD16: // TODO
        case arm_id::UHADD8: // TODO
        case arm_id::UHADDSUBX: // TODO
        case arm_id::UHSUB16: // TODO
        case arm_id::UHSUB8: // TODO
        case arm_id::UHSUBADDX: // TODO
        case arm_id::UMAAL: // TODO
        case arm_id::UQADD16: // TODO
        case arm_id::UQADD8: // TODO
        case arm_id::UQADDSUBX: // TODO
        case arm_id::UQSUB16: // TODO
        case arm_id::UQSUB8: // TODO
        case arm_id::UQSUBADDX: // TODO
        case arm_id::USAD8: // TODO
        case arm_id::USADA8: // TODO
        case arm_id::USAT: // TODO
        case arm_id::USAT16: // TODO
        case arm_id::USUB16: // TODO
        case arm_id::USUB8: // TODO
        case arm_id::USUBADDX: // TODO
        case arm_id::UXTAB: // TODO
        case arm_id::UXTAB16: // TODO
        case arm_id::UXTAH: // TODO
        case arm_id::UXTB: // TODO
        case arm_id::UXTB16: // TODO
        case arm_id::UXTH: // TODO
            return true;
    }
}


bool validation::string_arm::is_data_processing_valid(lexemes_t lexemes, const shifter_id shifter_id, const arm_id id) {
    using namespace interpreter;
    using enum token_enum;

    // this is because CMN is an exception where it has 1 register instead of the usual 2 for this addressing mode
    const u8 removal_count = (id == arm_id::CMN ? 1 : 2);
    lexemes.erase(lexemes.begin(), lexemes.begin() + removal_count);

    // lexemes should remove the first non-addressing mode registers, it's easier to analyse this way
    
    switch (shifter_id) {
        case shifter_id::DATA_IMM: return verify_lexemes(make_lexemes(token(HASHTAG), immed_rotate()), lexemes);
        case shifter_id::DATA_RRX: return verify_lexemes(make_lexemes(reg(), token(RRX)), lexemes);
        case shifter_id::DATA_REG: return verify_lexemes(make_lexemes(reg()), lexemes);
        case shifter_id::DATA_IMM_LSL: return verify_lexemes(make_lexemes(reg(), token(LSL), token(HASHTAG), immed_range(0, 31)), lexemes);
        case shifter_id::DATA_IMM_LSR: return verify_lexemes(make_lexemes(reg(), token(LSR), token(HASHTAG), immed_range(1, 32)), lexemes);
        case shifter_id::DATA_IMM_ASR: return verify_lexemes(make_lexemes(reg(), token(ASR), token(HASHTAG), immed_range(1, 32)), lexemes);
        case shifter_id::DATA_IMM_ROR: return verify_lexemes(make_lexemes(reg(), token(ROR), token(HASHTAG), immed_range(1, 31)), lexemes);
        case shifter_id::DATA_REG_LSL: return verify_lexemes(make_lexemes(reg(), token(LSL), reg()), lexemes);
        case shifter_id::DATA_REG_LSR: return verify_lexemes(make_lexemes(reg(), token(LSR), reg()), lexemes);
        case shifter_id::DATA_REG_ASR: return verify_lexemes(make_lexemes(reg(), token(ASR), reg()), lexemes);
        case shifter_id::DATA_REG_ROR: return verify_lexemes(make_lexemes(reg(), token(ROR), reg()), lexemes);
        default: return false;
    }
}


bool validation::string_arm::is_ls_valid(const lexemes_t& lexemes, const shifter_id shifter_id, const arm_id id) {
    using namespace interpreter;
    using enum token_enum;

    if (id == arm_id::PLD) {
        switch (shifter_id) {
            case shifter_id::LS_IMM:
            case shifter_id::LS_REG:
            case shifter_id::LS_SCALED_LSL:
            case shifter_id::LS_SCALED_LSR:
            case shifter_id::LS_SCALED_ASR:
            case shifter_id::LS_SCALED_ROR:
            case shifter_id::LS_SCALED_RRX: break;
            default: return false;
        }
    }

    switch (shifter_id) {
        case shifter_id::LS_IMM: return verify_lexemes(make_lexemes(reg(), token(MEM_START), reg(), token(HASHTAG), immed(11), token(MEM_END)), lexemes);
        case shifter_id::LS_IMM_PRE: return verify_lexemes(make_lexemes(reg(), token(MEM_START), reg(), token(HASHTAG), immed(11), token(MEM_END), token(PRE_INDEX)), lexemes);
        case shifter_id::LS_IMM_POST: return verify_lexemes(make_lexemes(reg(), token(MEM_START), reg(), token(MEM_END), token(HASHTAG), immed(11)), lexemes);
        case shifter_id::LS_REG: return verify_lexemes(make_lexemes(reg(), token(MEM_START), reg(), reg(), token(MEM_END)), lexemes);
        case shifter_id::LS_REG_PRE: return verify_lexemes(make_lexemes(reg(), token(MEM_START), reg(), reg(), token(MEM_END), token(PRE_INDEX)), lexemes);
        case shifter_id::LS_REG_POST: return verify_lexemes(make_lexemes(reg(), token(MEM_START), reg(), token(MEM_END), reg()), lexemes);
        case shifter_id::LS_SCALED_LSL: return verify_lexemes(make_lexemes(reg(), token(MEM_START), reg(), reg(), token(LSL), token(HASHTAG), immed_range(0, 31), token(MEM_END)), lexemes);
        case shifter_id::LS_SCALED_LSR: return verify_lexemes(make_lexemes(reg(), token(MEM_START), reg(), reg(), token(LSR), token(HASHTAG), immed_range(1, 32), token(MEM_END)), lexemes);
        case shifter_id::LS_SCALED_ASR: return verify_lexemes(make_lexemes(reg(), token(MEM_START), reg(), reg(), token(ASR), token(HASHTAG), immed_range(1, 32), token(MEM_END)), lexemes);
        case shifter_id::LS_SCALED_ROR: return verify_lexemes(make_lexemes(reg(), token(MEM_START), reg(), reg(), token(ROR), token(HASHTAG), immed_range(1, 31), token(MEM_END)), lexemes);
        case shifter_id::LS_SCALED_RRX: return verify_lexemes(make_lexemes(reg(), token(MEM_START), reg(), reg(), token(RRX), token(MEM_END)), lexemes);
        case shifter_id::LS_SCALED_PRE_LSL: return verify_lexemes(make_lexemes(reg(), token(MEM_START), reg(), reg(), token(LSL), token(HASHTAG), immed_range(0, 31), token(MEM_END), token(PRE_INDEX)), lexemes);
        case shifter_id::LS_SCALED_PRE_LSR: return verify_lexemes(make_lexemes(reg(), token(MEM_START), reg(), reg(), token(LSR), token(HASHTAG), immed_range(1, 32), token(MEM_END), token(PRE_INDEX)), lexemes);
        case shifter_id::LS_SCALED_PRE_ASR: return verify_lexemes(make_lexemes(reg(), token(MEM_START), reg(), reg(), token(ASR), token(HASHTAG), immed_range(1, 32), token(MEM_END), token(PRE_INDEX)), lexemes);
        case shifter_id::LS_SCALED_PRE_ROR: return verify_lexemes(make_lexemes(reg(), token(MEM_START), reg(), reg(), token(ROR), token(HASHTAG), immed_range(1, 31), token(MEM_END), token(PRE_INDEX)), lexemes);
        case shifter_id::LS_SCALED_PRE_RRX: return verify_lexemes(make_lexemes(reg(), token(MEM_START), reg(), reg(), token(RRX), token(MEM_END), token(PRE_INDEX)), lexemes);
        case shifter_id::LS_SCALED_POST_LSL: return verify_lexemes(make_lexemes(reg(), token(MEM_START), reg(), token(MEM_END), reg(), token(HASHTAG), immed_range(0, 31)), lexemes);
        case shifter_id::LS_SCALED_POST_LSR: return verify_lexemes(make_lexemes(reg(), token(MEM_START), reg(), token(MEM_END), reg(), token(HASHTAG), immed_range(1, 32)), lexemes);
        case shifter_id::LS_SCALED_POST_ASR: return verify_lexemes(make_lexemes(reg(), token(MEM_START), reg(), token(MEM_END), reg(), token(HASHTAG), immed_range(1, 32)), lexemes);
        case shifter_id::LS_SCALED_POST_ROR: return verify_lexemes(make_lexemes(reg(), token(MEM_START), reg(), token(MEM_END), reg(), token(HASHTAG), immed_range(1, 31)), lexemes);
        case shifter_id::LS_SCALED_POST_RRX: return verify_lexemes(make_lexemes(reg(), token(MEM_START), reg(), token(MEM_END), reg(), token(RRX)), lexemes);
        default: return false;
    }
}


bool validation::string_arm::is_ls_misc_valid(lexemes_t lexemes, const shifter_id shifter_id, const arm_id id) {
    using namespace interpreter;
    using enum token_enum;

    // LDRD and STRD are both supposed to be structured like LDR|STR{<cond>}H|SH|SB|D <Rd>, <addressing_mode>
    // but Rd is followed by Rd + 1. So it becomes R0, R1, <addressing_mode> instead of just R0, <addressing_mode>
    if (id == arm_id::STRD || id == arm_id::LDRD) {
        if (
            (lexemes.at(0).token_type != token_enum::REG) ||
            (lexemes.at(1).token_type != token_enum::REG)
        ) {
            return false;
        }

        const u8 first_reg = lexemes.at(0).data.reg.number;
        const u8 second_reg = lexemes.at(1).data.reg.number;

        if (first_reg != second_reg + 1) {
            return false;
        }

        lexemes.erase(lexemes.begin(), lexemes.begin() + 1);
    }

    switch (shifter_id) {
        case shifter_id::LS_MISC_IMM: return verify_lexemes(make_lexemes(reg(), token(MEM_START), reg(), token(HASHTAG), immed(7), token(MEM_END)), lexemes);
        case shifter_id::LS_MISC_IMM_PRE: return verify_lexemes(make_lexemes(reg(), token(MEM_START), reg(), token(HASHTAG), immed(7), token(MEM_END), token(PRE_INDEX)), lexemes);
        case shifter_id::LS_MISC_IMM_POST: return verify_lexemes(make_lexemes(reg(), token(MEM_START), reg(), token(MEM_END), token(HASHTAG), immed(7)), lexemes);
        case shifter_id::LS_MISC_REG: return verify_lexemes(make_lexemes(reg(), token(MEM_START), reg(), reg(), token(MEM_END)), lexemes);
        case shifter_id::LS_MISC_REG_PRE: return verify_lexemes(make_lexemes(reg(), token(MEM_START), reg(), reg(), token(MEM_END), token(PRE_INDEX)), lexemes);
        case shifter_id::LS_MISC_REG_POST: return verify_lexemes(make_lexemes(reg(), token(MEM_START), reg(), token(MEM_END), reg()), lexemes);
        default: return false;
    }
}


bool validation::string_arm::is_ls_coproc_valid(const lexemes_t& lexemes, const shifter_id shifter_id) {
    using namespace interpreter;
    using enum token_enum;

    switch (shifter_id) {
        case shifter_id::LS_COPROC_IMM: return verify_lexemes(make_lexemes(reg(reg_type::COPROC), reg(reg_type::CR), token(MEM_START), reg(), token(HASHTAG), immed(7, 4), token(MEM_END)), lexemes);
        case shifter_id::LS_COPROC_IMM_PRE: return verify_lexemes(make_lexemes(reg(reg_type::COPROC), reg(reg_type::CR), token(MEM_START), reg(), token(HASHTAG), immed(7, 4), token(MEM_END), token(PRE_INDEX)), lexemes);
        case shifter_id::LS_COPROC_IMM_POST: return verify_lexemes(make_lexemes(reg(reg_type::COPROC), reg(reg_type::CR), token(MEM_START), reg(), token(MEM_END), token(HASHTAG), immed(7, 4)), lexemes);
        case shifter_id::LS_COPROC_UNINDEXED: return verify_lexemes(make_lexemes(reg(reg_type::COPROC), reg(reg_type::CR), token(MEM_START), reg(), option()), lexemes);
        default: return false;
    }
}


bool validation::string_arm::is_B_BL_valid(const lexemes_t& lexemes, const u32 PC) {
    if (lexemes.at(0).token_type != token_enum::IMMED) {
        return false;
    }

    const u32 address = static_cast<u32>(lexemes.at(0).data.imm.number);
    return encoders::is_branch_target_valid(PC, address);
}