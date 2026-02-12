#pragma once

#include "src/assemble/assemble.hpp"
#include "src/settings.hpp"
#include "src/id/instruction_id.hpp"
#include "src/identifiers/u32_shifters.hpp"
#include "src/identifiers/u32_arm.hpp"
#include "src/identifiers/u16_thumb.hpp"
#include "src/identifiers/string_arm.hpp"
#include "src/identifiers/string_thumb.hpp"
#include "src/identifiers/string_shifters.hpp"
#include "src/disassemble/disassemble.hpp"
#include "src/validation/u32_arm.hpp"
#include "src/validation/string_arm.hpp"
#include "src/validation/string_thumb.hpp"
#include "src/validation/u16_thumb.hpp"
#include "src/settings.hpp"


namespace llarm::as {
    // setting aliases, ignore these
    using settings = internal::settings;
    using default_func = settings(*)();
    inline default_func default_settings = &internal::default_dis_settings;

    // alternatives in case it's under C++17
    using arm_id = internal::arm_id;
    using thumb_id = internal::thumb_id;
    using shifter_id = internal::shifter_id;
    using shifter_category = internal::shifter_category;

    //enum class arm : internal::id::arm {};
    //enum class thumb : internal::id::thumb {};

    inline arm_id identify_arm(const u32 raw_code) {
        return internal::ident::u32_arm::arm(raw_code);
    }

    inline arm_id identify_arm(const std::string &code) {
        return internal::ident::string_arm::arm(code);
    }

    inline thumb_id identify_thumb(const u16 raw_code) {
        return internal::ident::u16_thumb::thumb(raw_code);
    }

    inline thumb_id identify_thumb(const std::string &code) {
        return internal::ident::string_thumb::thumb(code);
    }

    inline shifter_id identify_shifter(const u32 raw_code) {
        return internal::ident::u32_shifters::identify_shifter(raw_code);
    }

    inline shifter_id identify_shifter(const std::string &code) {
        return internal::ident::string_shifters::identify_shifter(code);
    }

    inline shifter_id identify_shifter(const shifter_category category, const u32 raw_code) {
        return internal::ident::u32_shifters::identify_shifter(category, raw_code);
    }

    //inline u32 generate_arm(const id::arm code, const params params) {
    //    
    //}

    inline std::string disassemble_arm(
        const u32 code, 
        const u32 PC = 0, 
        const settings settings = default_settings()
    ) {
        return internal::disassemble::arm(code, PC, settings);
    }

    inline std::string disassemble_thumb(
        const u16 code,
        const u32 PC = 0,
        const settings settings = default_settings()
    ) {
        return internal::disassemble::thumb(code, PC, settings);
    }

    inline u32 assemble_arm(const std::string &code, const u32 PC = 0) {
        return internal::assemble::arm(code, PC);
    }

    inline bool is_arm_instruction_valid(const u32 code) {
        return internal::validation::u32_arm::is_arm_instruction_valid(code);
    }

    inline bool is_arm_instruction_valid(const std::string &code) {
        return internal::validation::string_arm::is_arm_instruction_valid(code);
    }

    inline bool is_thumb_instruction_valid(const u16 code) {
        return internal::validation::u16_thumb::is_thumb_instruction_valid(code);
    }

    inline bool is_thumb_instruction_valid(const std::string &code) {
        return internal::validation::string_thumb::is_thumb_instruction_valid(code);
    }


    inline std::string thumb_id_to_string(const thumb_id id) {
        using namespace internal;
        switch (id) {
            case thumb_id::UNKNOWN: return "UNDEFINED";
            case thumb_id::UNDEFINED: return "UNDEFINED";
            case thumb_id::ADC: return "ADC";
            case thumb_id::ADD1: return "ADD1";
            case thumb_id::ADD2: return "ADD2";
            case thumb_id::ADD3: return "ADD3";
            case thumb_id::ADD4: return "ADD4";
            case thumb_id::ADD5: return "ADD5";
            case thumb_id::ADD6: return "ADD6";
            case thumb_id::ADD7: return "ADD7";
            case thumb_id::SBC: return "SBC";
            case thumb_id::SUB1: return "SUB1";
            case thumb_id::SUB2: return "SUB2";
            case thumb_id::SUB3: return "SUB3";
            case thumb_id::SUB4: return "SUB4";
            case thumb_id::MUL: return "MUL";
            case thumb_id::AND: return "AND";
            case thumb_id::ASR1: return "ASR1";
            case thumb_id::ASR2: return "ASR2";
            case thumb_id::BIC: return "BIC";
            case thumb_id::EOR: return "EOR";
            case thumb_id::LSL1: return "LSL1";
            case thumb_id::LSL2: return "LSL2";
            case thumb_id::LSR1: return "LSR1";
            case thumb_id::LSR2: return "LSR2";
            case thumb_id::NEG: return "NEG";
            case thumb_id::ORR: return "ORR";
            case thumb_id::ROR: return "ROR";
            case thumb_id::TST: return "TST";
            case thumb_id::CMN: return "CMN";
            case thumb_id::CMP1: return "CMP1";
            case thumb_id::CMP2: return "CMP2";
            case thumb_id::CMP3: return "CMP3";
            case thumb_id::MOV1: return "MOV1";
            case thumb_id::MOV2: return "MOV2";
            case thumb_id::MOV3: return "MOV3";
            case thumb_id::MVN: return "MVN";
            case thumb_id::B1: return "B1";
            case thumb_id::B2: return "B2";
            case thumb_id::BL: return "BL";
            case thumb_id::BLX1: return "BLX1";
            case thumb_id::BLX2: return "BLX2";
            case thumb_id::BX: return "BX";
            case thumb_id::NOP: return "NOP";
            case thumb_id::BKPT: return "BKPT";
            case thumb_id::SWI: return "SWI";
            case thumb_id::LDMIA: return "LDMIA";
            case thumb_id::LDR1: return "LDR1";
            case thumb_id::LDR2: return "LDR2";
            case thumb_id::LDR3: return "LDR3";
            case thumb_id::LDR4: return "LDR4";
            case thumb_id::LDRB1: return "LDRB1";
            case thumb_id::LDRB2: return "LDRB2";
            case thumb_id::LDRH1: return "LDRH1";
            case thumb_id::LDRH2: return "LDRH2";
            case thumb_id::LDRSB: return "LDRSB";
            case thumb_id::LDRSH: return "LDRSH";
            case thumb_id::POP: return "POP";
            case thumb_id::PUSH: return "PUSH";
            case thumb_id::STMIA: return "STMIA";
            case thumb_id::STR1: return "STR1";
            case thumb_id::STR2: return "STR2";
            case thumb_id::STR3: return "STR3";
            case thumb_id::STRB1: return "STRB1";
            case thumb_id::STRB2: return "STRB2";
            case thumb_id::STRH1: return "STRH1";
            case thumb_id::STRH2: return "STRH2";
        }
    }


    inline std::string arm_id_to_string(const arm_id id) {
        using namespace internal;

        switch (id) {
            case arm_id::UNKNOWN: return "UNKNOWN";
            case arm_id::ADC: return "ADC"; 
            case arm_id::ADD: return "ADD"; 
            case arm_id::AND: return "AND"; 
            case arm_id::UNDEFINED: return "UNDEFINED"; 
            case arm_id::NOP: return "NOP"; 
            case arm_id::B: return "B"; 
            case arm_id::BL: return "BL"; 
            case arm_id::BIC: return "BIC"; 
            case arm_id::CDP: return "CDP"; 
            case arm_id::CMN: return "CMN"; 
            case arm_id::CMP: return "CMP"; 
            case arm_id::EOR: return "EOR"; 
            case arm_id::LDC: return "LDC"; 
            case arm_id::LDM1: return "LDM1"; 
            case arm_id::LDM2: return "LDM2"; 
            case arm_id::LDM3: return "LDM3"; 
            case arm_id::LDR: return "LDR"; 
            case arm_id::LDRB: return "LDRB"; 
            case arm_id::LDRBT: return "LDRBT"; 
            case arm_id::LDRT: return "LDRT"; 
            case arm_id::MCR: return "MCR"; 
            case arm_id::MLA: return "MLA"; 
            case arm_id::MOV: return "MOV"; 
            case arm_id::MRC: return "MRC"; 
            case arm_id::MRS: return "MRS"; 
            case arm_id::MSR_IMM: return "MSR_IMM"; 
            case arm_id::MSR_REG: return "MSR_REG"; 
            case arm_id::MUL: return "MUL"; 
            case arm_id::MVN: return "MVN"; 
            case arm_id::ORR: return "ORR"; 
            case arm_id::RSB: return "RSB"; 
            case arm_id::RSC: return "RSC"; 
            case arm_id::SBC: return "SBC"; 
            case arm_id::STC: return "STC"; 
            case arm_id::STM1: return "STM1"; 
            case arm_id::STM2: return "STM2"; 
            case arm_id::STR: return "STR"; 
            case arm_id::STRB: return "STRB"; 
            case arm_id::STRBT: return "STRBT"; 
            case arm_id::STRT: return "STRT"; 
            case arm_id::SUB: return "SUB"; 
            case arm_id::SWI: return "SWI"; 
            case arm_id::SWP: return "SWP"; 
            case arm_id::SWPB: return "SWPB"; 
            case arm_id::TEQ: return "TEQ"; 
            case arm_id::TST: return "TST"; 
            case arm_id::CMNP: return "CMNP";
            case arm_id::CMPP: return "CMPP";
            case arm_id::TEQP: return "TEQP";
            case arm_id::TSTP: return "TSTP";
            case arm_id::STRH: return "STRH"; 
            case arm_id::LDRH: return "LDRH"; 
            case arm_id::LDRSB: return "LDRSB"; 
            case arm_id::LDRSH: return "LDRSH"; 
            case arm_id::BKPT: return "BKPT"; 
            case arm_id::BLX1: return "BLX1"; 
            case arm_id::BLX2: return "BLX2"; 
            case arm_id::CLZ: return "CLZ"; 
            case arm_id::BX: return "BX"; 
            case arm_id::SMLAL: return "SMLAL"; 
            case arm_id::SMULL: return "SMULL"; 
            case arm_id::UMLAL: return "UMLAL"; 
            case arm_id::UMULL: return "UMULL"; 
            case arm_id::LDRD: return "LDRD"; 
            case arm_id::MCRR: return "MCRR"; 
            case arm_id::MRRC: return "MRRC"; 
            case arm_id::PLD: return "PLD"; 
            case arm_id::QADD: return "QADD"; 
            case arm_id::QDADD: return "QDADD"; 
            case arm_id::QDSUB: return "QDSUB"; 
            case arm_id::QSUB: return "QSUB"; 
            case arm_id::SMLAXY: return "SMLA<x><y>"; 
            case arm_id::SMLALXY: return "SMLAL<x><y>";
            case arm_id::SMLAWY: return "SMLAW<y>"; 
            case arm_id::SMULXY: return "SMUL<x><y>"; 
            case arm_id::SMULWY: return "SMULW<y>"; 
            case arm_id::STRD: return "STRD"; 
            case arm_id::FABSD: return "FABSD"; 
            case arm_id::FABSS: return "FABSS"; 
            case arm_id::FADDD: return "FADDD"; 
            case arm_id::FADDS: return "FADDS"; 
            case arm_id::FCMPD: return "FCMPD"; 
            case arm_id::FCMPED: return "FCMPED"; 
            case arm_id::FCMPES: return "FCMPES"; 
            case arm_id::FCMPEZD: return "FCMPEZD"; 
            case arm_id::FCMPEZS: return "FCMPEZS"; 
            case arm_id::FCMPS: return "FCMPS"; 
            case arm_id::FCMPZD: return "FCMPZD"; 
            case arm_id::FCMPZS: return "FCMPZS"; 
            case arm_id::FCPYD: return "FCPYD"; 
            case arm_id::FCPYS: return "FCPYS"; 
            case arm_id::FCVTDS: return "FCVTDS"; 
            case arm_id::FCVTSD: return "FCVTSD"; 
            case arm_id::FDIVD: return "FDIVD"; 
            case arm_id::FDIVS: return "FDIVS"; 
            case arm_id::FLDD: return "FLDD"; 
            case arm_id::FLDMD: return "FLDMD"; 
            case arm_id::FLDMS: return "FLDMS"; 
            case arm_id::FLDMX: return "FLDMX"; 
            case arm_id::FLDS: return "FLDS"; 
            case arm_id::FMACD: return "FMACD"; 
            case arm_id::FMACS: return "FMACS"; 
            case arm_id::FMDHR: return "FMDHR"; 
            case arm_id::FMDLR: return "FMDLR"; 
            case arm_id::FMRDH: return "FMRDH"; 
            case arm_id::FMRDL: return "FMRDL"; 
            case arm_id::FMRS: return "FMRS"; 
            case arm_id::FMRX: return "FMRX"; 
            case arm_id::FMSCD: return "FMSCD"; 
            case arm_id::FMSCS: return "FMSCS"; 
            case arm_id::FMSR: return "FMSR"; 
            case arm_id::FMSTAT: return "FMSTAT"; 
            case arm_id::FMULD: return "FMULD"; 
            case arm_id::FMULS: return "FMULS"; 
            case arm_id::FMXR: return "FMXR"; 
            case arm_id::FNEGD: return "FNEGD"; 
            case arm_id::FNEGS: return "FNEGS"; 
            case arm_id::FNMACD: return "FNMACD"; 
            case arm_id::FNMACS: return "FNMACS"; 
            case arm_id::FNMSCD: return "FNMSCD"; 
            case arm_id::FNMSCS: return "FNMSCS"; 
            case arm_id::FNMULD: return "FNMULD"; 
            case arm_id::FNMULS: return "FNMULS"; 
            case arm_id::FSITOD: return "FSITOD"; 
            case arm_id::FSITOS: return "FSITOS"; 
            case arm_id::FSQRTD: return "FSQRTD"; 
            case arm_id::FSQRTS: return "FSQRTS"; 
            case arm_id::FSTD: return "FSTD"; 
            case arm_id::FSTMD: return "FSTMD"; 
            case arm_id::FSTMS: return "FSTMS"; 
            case arm_id::FSTMX: return "FSTMX"; 
            case arm_id::FSTS: return "FSTS"; 
            case arm_id::FSUBD: return "FSUBD"; 
            case arm_id::FSUBS: return "FSUBS"; 
            case arm_id::FTOSID: return "FTOSID"; 
            case arm_id::FTOSIS: return "FTOSIS"; 
            case arm_id::FTOUID: return "FTOUID"; 
            case arm_id::FTOUIS: return "FTOUIS"; 
            case arm_id::FUITOD: return "FUITOD"; 
            case arm_id::FUITOS: return "FUITOS";
            case arm_id::CDP2: return "CDP2";
            case arm_id::LDC2: return "LDC2";
            case arm_id::MCR2: return "MCR2";
            case arm_id::MRC2: return "MRC2";
            case arm_id::STC2: return "STC2";
        }
    }
}