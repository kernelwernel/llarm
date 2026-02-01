#pragma once

#include "../id/instruction_id.hpp"
#include "../id/cond_id.hpp"
#include "../interpreter/interpreter.hpp"

#include <string>
#include <unordered_map>

using namespace internal;

struct mnemonic_struct {
    sv instruction = "";
    arm_id id = arm_id::UNKNOWN;
    cond_id cond_id = cond_id::UNKNOWN;
    bool has_S = false;
    bool has_Z = false;
    bool has_L = false;
    unsigned char x_char = '\0';
    unsigned char y_char = '\0';
};

namespace internal::mnemonic {
    const std::unordered_map<sv, arm_id> arm_instructions = {
        { "ADC", arm_id::ADC },
        { "ADD", arm_id::ADD },
        { "AND", arm_id::AND },
        { "B", arm_id::B },
        { "BIC", arm_id::BIC },
        { "BKPT", arm_id::BKPT },
        { "BL", arm_id::BL },
        { "BX", arm_id::BX },
        { "CDP", arm_id::CDP },
        { "CDP2", arm_id::CDP2 },
        { "CLZ", arm_id::CLZ },
        { "CMN", arm_id::CMN },
        { "CMP", arm_id::CMP },
        { "EOR", arm_id::EOR },
        { "FABSD", arm_id::FABSD },
        { "FABSS", arm_id::FABSS },
        { "FADDD", arm_id::FADDD },
        { "FADDS", arm_id::FADDS },
        { "FCMPD", arm_id::FCMPD },
        { "FCMPED", arm_id::FCMPED },
        { "FCMPES", arm_id::FCMPES },
        { "FCMPEZD", arm_id::FCMPEZD },
        { "FCMPEZS", arm_id::FCMPEZS },
        { "FCMPS", arm_id::FCMPS },
        { "FCMPZD", arm_id::FCMPZD },
        { "FCMPZS", arm_id::FCMPZS },
        { "FCPYD", arm_id::FCPYD },
        { "FCPYS", arm_id::FCPYS },
        { "FCVTDS", arm_id::FCVTDS },
        { "FCVTSD", arm_id::FCVTSD },
        { "FDIVD", arm_id::FDIVD },
        { "FDIVS", arm_id::FDIVS },
        { "FLDD", arm_id::FLDD },
        { "FLDMD", arm_id::FLDMD },
        { "FLDMS", arm_id::FLDMS },
        { "FLDMX", arm_id::FLDMX },
        { "FLDS", arm_id::FLDS },
        { "FMACD", arm_id::FMACD },
        { "FMACS", arm_id::FMACS },
        { "FMDHR", arm_id::FMDHR },
        { "FMDLR", arm_id::FMDLR },
        { "FMRDH", arm_id::FMRDH },
        { "FMRDL", arm_id::FMRDL },
        { "FMRS", arm_id::FMRS },
        { "FMRX", arm_id::FMRX },
        { "FMSCD", arm_id::FMSCD },
        { "FMSCS", arm_id::FMSCS },
        { "FMSR", arm_id::FMSR },
        { "FMSTAT", arm_id::FMSTAT },
        { "FMULD", arm_id::FMULD },
        { "FMULS", arm_id::FMULS },
        { "FMXR", arm_id::FMXR },
        { "FNEGD", arm_id::FNEGD },
        { "FNEGS", arm_id::FNEGS },
        { "FNMACD", arm_id::FNMACD },
        { "FNMACS", arm_id::FNMACS },
        { "FNMSCD", arm_id::FNMSCD },
        { "FNMSCS", arm_id::FNMSCS },
        { "FNMULD", arm_id::FNMULD },
        { "FNMULS", arm_id::FNMULS },
        { "FSITOD", arm_id::FSITOD },
        { "FSITOS", arm_id::FSITOS },
        { "FSQRTD", arm_id::FSQRTD },
        { "FSQRTS", arm_id::FSQRTS },
        { "FSTD", arm_id::FSTD },
        { "FSTMD", arm_id::FSTMD },
        { "FSTMS", arm_id::FSTMS },
        { "FSTMX", arm_id::FSTMX },
        { "FSTS", arm_id::FSTS },
        { "FSUBD", arm_id::FSUBD },
        { "FSUBS", arm_id::FSUBS },
        { "FTOSID", arm_id::FTOSID },
        { "FTOSIS", arm_id::FTOSIS },
        { "FTOSIZS", arm_id::FTOSIS },
        { "FTOUID", arm_id::FTOUID },
        { "FTOUIZS", arm_id::FTOUIS },
        { "FTOUIS", arm_id::FTOUIS },
        { "FUITOD", arm_id::FUITOD },
        { "FUITOS", arm_id::FUITOS },
        { "LDC", arm_id::LDC },
        { "LDC2", arm_id::LDC2 },
        { "LDR", arm_id::LDR },
        { "LDRD", arm_id::LDRD },
        { "MCR", arm_id::MCR },
        { "MCR2", arm_id::MCR2 },
        { "MCRR", arm_id::MCRR },
        { "MLA", arm_id::MLA },
        { "MOV", arm_id::MOV },
        { "MRC", arm_id::MRC },
        { "MRC2", arm_id::MRC2 },
        { "MRRC", arm_id::MRRC },
        { "MRS", arm_id::MRS },
        { "MUL", arm_id::MUL },
        { "MVN", arm_id::MVN },
        { "ORR", arm_id::ORR },
        { "PLD", arm_id::PLD },
        { "CMNP", arm_id::CMNP },
        { "CMPP", arm_id::CMPP },
        { "TEQP", arm_id::TEQP },
        { "TSTP", arm_id::TSTP },
        { "QADD", arm_id::QADD },
        { "QDADD", arm_id::QDADD },
        { "QDSUB", arm_id::QDSUB },
        { "QSUB", arm_id::QSUB },
        { "RSB", arm_id::RSB },
        { "RSC", arm_id::RSC },
        { "SBC", arm_id::SBC },
        { "SMLAL", arm_id::SMLAL },
        { "SMULL", arm_id::SMULL },
        { "SMLALBB", arm_id::SMLALXY },
        { "SMLALBT", arm_id::SMLALXY },
        { "SMLALTB", arm_id::SMLALXY },
        { "SMLALTT", arm_id::SMLALXY },
        { "SMLAWB", arm_id::SMLAWY },
        { "SMLAWT", arm_id::SMLAWY },
        { "SMLABB", arm_id::SMLAXY },
        { "SMLABT", arm_id::SMLAXY },
        { "SMLATB", arm_id::SMLAXY },
        { "SMLATT", arm_id::SMLAXY },
        { "SMULBB", arm_id::SMULXY },
        { "SMULBT", arm_id::SMULXY },
        { "SMULTB", arm_id::SMULXY },
        { "SMULTT", arm_id::SMULXY },
        { "SMULWB", arm_id::SMULWY },
        { "SMULWT", arm_id::SMULWY },
        { "STC", arm_id::STC },
        { "STC2", arm_id::STC2 },
        { "STR", arm_id::STR }, 
        { "STRD", arm_id::STRD },
        { "SUB", arm_id::SUB },
        { "SWI", arm_id::SWI },
        { "SWP", arm_id::SWP },
        { "TEQ", arm_id::TEQ },
        { "TST", arm_id::TST },
        { "UMLAL", arm_id::UMLAL },
        { "UMULL", arm_id::UMULL }
    };

    std::vector<sv> fetch_candidates(sv mnemonic);
    mnemonic_struct fetch_mnemonic_args(const arm_id id, sv mnemonic);

    mnemonic_struct arm(const std::string &code);

    arm_id MSR(const lexemes_t &lexemes);
    arm_id SWPB(const sv mnemonic);
    arm_id LDR_family(sv mnemonic);
    arm_id STR_family(sv mnemonic);
    arm_id VFP_family(sv mnemonic);
    arm_id PSR_family(const sv mnemonic);
    arm_id STM(const lexemes_t &lexemes);
    arm_id LDM(const lexemes_t &lexemes);
    arm_id BLX(const lexemes_t &lexemes);
}

// TODO: work on the +/- thing before an immediate