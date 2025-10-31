#pragma once

#include "../instruction_id.hpp"
#include "interpreter.hpp"

#include <string>
#include <unordered_map>

namespace internal::string_arm {
    using namespace internal;

    using interpreter::tokens;
    using interpreter::tokens_t;
    using interpreter::lexeme_struct;
    using interpreter::lexemes_t;

    const std::unordered_map<std::string_view, id::arm> arm_instructions = {
        { "ADC", id::arm::ADC },
        { "ADD", id::arm::ADD },
        { "AND", id::arm::AND },
        { "B", id::arm::B },
        { "BIC", id::arm::BIC },
        { "BKPT", id::arm::BKPT },
        { "BL", id::arm::BL },
        { "BX", id::arm::BX },
        { "CDP", id::arm::CDP },
        { "CDP2", id::arm::CDP2 },
        { "CLZ", id::arm::CLZ },
        { "CMN", id::arm::CMN },
        { "CMP", id::arm::CMP },
        { "EOR", id::arm::EOR },
        { "FABSD", id::arm::FABSD },
        { "FABSS", id::arm::FABSS },
        { "FADDD", id::arm::FADDD },
        { "FADDS", id::arm::FADDS },
        { "FCMPD", id::arm::FCMPD },
        { "FCMPED", id::arm::FCMPED },
        { "FCMPES", id::arm::FCMPES },
        { "FCMPEZD", id::arm::FCMPEZD },
        { "FCMPEZS", id::arm::FCMPEZS },
        { "FCMPS", id::arm::FCMPS },
        { "FCMPZD", id::arm::FCMPZD },
        { "FCMPZS", id::arm::FCMPZS },
        { "FCPYD", id::arm::FCPYD },
        { "FCPYS", id::arm::FCPYS },
        { "FCVTDS", id::arm::FCVTDS },
        { "FCVTSD", id::arm::FCVTSD },
        { "FDIVD", id::arm::FDIVD },
        { "FDIVS", id::arm::FDIVS },
        { "FLDD", id::arm::FLDD },
        { "FLDMD", id::arm::FLDMD },
        { "FLDMS", id::arm::FLDMS },
        { "FLDMX", id::arm::FLDMX },
        { "FLDS", id::arm::FLDS },
        { "FMACD", id::arm::FMACD },
        { "FMACS", id::arm::FMACS },
        { "FMDHR", id::arm::FMDHR },
        { "FMDLR", id::arm::FMDLR },
        { "FMRDH", id::arm::FMRDH },
        { "FMRDL", id::arm::FMRDL },
        { "FMRS", id::arm::FMRS },
        { "FMRX", id::arm::FMRX },
        { "FMSCD", id::arm::FMSCD },
        { "FMSCS", id::arm::FMSCS },
        { "FMSR", id::arm::FMSR },
        { "FMSTAT", id::arm::FMSTAT },
        { "FMULD", id::arm::FMULD },
        { "FMULS", id::arm::FMULS },
        { "FMXR", id::arm::FMXR },
        { "FNEGD", id::arm::FNEGD },
        { "FNEGS", id::arm::FNEGS },
        { "FNMACD", id::arm::FNMACD },
        { "FNMACS", id::arm::FNMACS },
        { "FNMSCD", id::arm::FNMSCD },
        { "FNMSCS", id::arm::FNMSCS },
        { "FNMULD", id::arm::FNMULD },
        { "FNMULS", id::arm::FNMULS },
        { "FSITOD", id::arm::FSITOD },
        { "FSITOS", id::arm::FSITOS },
        { "FSQRTD", id::arm::FSQRTD },
        { "FSQRTS", id::arm::FSQRTS },
        { "FSTD", id::arm::FSTD },
        { "FSTMD", id::arm::FSTMD },
        { "FSTMS", id::arm::FSTMS },
        { "FSTMX", id::arm::FSTMX },
        { "FSTS", id::arm::FSTS },
        { "FSUBD", id::arm::FSUBD },
        { "FSUBS", id::arm::FSUBS },
        { "FTOSID", id::arm::FTOSID },
        { "FTOSIS", id::arm::FTOSIS },
        { "FTOSIZS", id::arm::FTOSIS },
        { "FTOUID", id::arm::FTOUID },
        { "FTOUIZS", id::arm::FTOUIS },
        { "FTOUIS", id::arm::FTOUIS },
        { "FUITOD", id::arm::FUITOD },
        { "FUITOS", id::arm::FUITOS },
        { "LDC", id::arm::LDC },
        { "LDC2", id::arm::LDC2 },
        { "LDR", id::arm::LDR },
        { "LDRD", id::arm::LDRD },
        { "MCR", id::arm::MCR },
        { "MCR2", id::arm::MCR2 },
        { "MCRR", id::arm::MCRR },
        { "MLA", id::arm::MLA },
        { "MOV", id::arm::MOV },
        { "MRC", id::arm::MRC },
        { "MRC2", id::arm::MRC2 },
        { "MRRC", id::arm::MRRC },
        { "MRS", id::arm::MRS },
        { "MUL", id::arm::MUL },
        { "MVN", id::arm::MVN },
        { "ORR", id::arm::ORR },
        { "PLD", id::arm::PLD },
        { "CMNP", id::arm::CMNP },
        { "CMPP", id::arm::CMPP },
        { "TEQP", id::arm::TEQP },
        { "TSTP", id::arm::TSTP },
        { "QADD", id::arm::QADD },
        { "QDADD", id::arm::QDADD },
        { "QDSUB", id::arm::QDSUB },
        { "QSUB", id::arm::QSUB },
        { "RSB", id::arm::RSB },
        { "RSC", id::arm::RSC },
        { "SBC", id::arm::SBC },
        { "SMLAL", id::arm::SMLAL },
        { "SMULL", id::arm::SMULL },
        { "SMLALBB", id::arm::SMLALXY },
        { "SMLALBT", id::arm::SMLALXY },
        { "SMLALTB", id::arm::SMLALXY },
        { "SMLALTT", id::arm::SMLALXY },
        { "SMLAWB", id::arm::SMLAWY },
        { "SMLAWT", id::arm::SMLAWY },
        { "SMLABB", id::arm::SMLAXY },
        { "SMLABT", id::arm::SMLAXY },
        { "SMLATB", id::arm::SMLAXY },
        { "SMLATT", id::arm::SMLAXY },
        { "SMULBB", id::arm::SMULXY },
        { "SMULBT", id::arm::SMULXY },
        { "SMULTB", id::arm::SMULXY },
        { "SMULTT", id::arm::SMULXY },
        { "SMULWB", id::arm::SMULWY },
        { "SMULWT", id::arm::SMULWY },
        { "STC", id::arm::STC },
        { "STC2", id::arm::STC2 },
        { "STR", id::arm::STR }, 
        { "STRD", id::arm::STRD },
        { "SUB", id::arm::SUB },
        { "SWI", id::arm::SWI },
        { "SWP", id::arm::SWP },
        { "TEQ", id::arm::TEQ },
        { "TST", id::arm::TST },
        { "UMLAL", id::arm::UMLAL },
        { "UMULL", id::arm::UMULL }
    };

    std::vector<std::string_view> fetch_candidates(std::string_view mnemonic);

    id::arm arm(const std::string &code);

    id::arm MSR(const lexemes_t &lexemes);
    id::arm SWPB(const std::string_view mnemonic);
    id::arm LDR_family(std::string_view mnemonic);
    id::arm STR_family(std::string_view mnemonic);
    id::arm VFP_family(std::string_view mnemonic);
    id::arm PSR_family(const std::string_view mnemonic);
    id::arm STM(const lexemes_t &lexemes);
    id::arm LDM(const lexemes_t &lexemes);
    id::arm BLX(const lexemes_t &lexemes);
}

// TODO: work on the +/- thing before an immediate