#pragma once

//#include <llarm/internal/llarm-asm/src/identifiers/identifiers.hpp>
//#include <llarm/internal/llarm-asm/src/opcodes/opcodes.hpp>
//#include <llarm/internal/llarm-asm/src/instruction_id.hpp>
//#include <llarm/internal/llarm-asm/src/instruction_table.hpp>

#include "llarm-asm/src/settings.hpp"
#include "src/identifiers/identifiers.hpp"
#include "src/instruction_id.hpp"
#include "src/disassemble/disassemble.hpp"
#include "src/settings.hpp"


namespace llarm {
    namespace as {
        // setting aliases
        using settings = internal::settings;
        using default_func = settings(*)();
        inline default_func default_settings = &internal::default_settings;


        namespace id {
            // alternatives in case it's under C++17
            using arm = internal::id::arm;
            using thumb = internal::id::thumb;

            //enum class arm : internal::id::arm {};
            //enum class thumb : internal::id::thumb {};
        }


        namespace identify {
            inline id::arm arm(const u32 raw_code, const settings &settings = default_settings()) {
                return internal::identifiers::arm(raw_code, settings);
            }

            inline id::thumb thumb(const u16 raw_code) {
                return internal::identifiers::thumb(raw_code);
            }
        }

        namespace generate {
            struct params {
                u8 cond;
                u8 Rd;
                u8 Rn;
            };

            inline u32 arm(const id::arm code, const params params) {
                
            }
        }

        namespace disassemble {
            inline std::string arm(
                const u32 code, 
                const u32 PC = 0, 
                const settings settings = default_settings()
            ) {
                return internal::disassemble::arm(code, PC, settings);
            }

            inline std::string thumb(
                const u16 code,
                const u32 PC = 0,
                const settings settings = default_settings()
            ) {
                return internal::disassemble::thumb(code, PC, settings);
            }
        }

        namespace assemble {
            inline u32 arm(const std::string code) {

            }
        }

        inline std::string thumb_id_to_string(const id::thumb id) {
            switch (id) {
                case id::thumb::UNDEFINED: return "UNDEFINED";
                case id::thumb::ADC: return "ADC";
                case id::thumb::ADD1: return "ADD1";
                case id::thumb::ADD2: return "ADD2";
                case id::thumb::ADD3: return "ADD3";
                case id::thumb::ADD4: return "ADD4";
                case id::thumb::ADD5: return "ADD5";
                case id::thumb::ADD6: return "ADD6";
                case id::thumb::ADD7: return "ADD7";
                case id::thumb::SBC: return "SBC";
                case id::thumb::SUB1: return "SUB1";
                case id::thumb::SUB2: return "SUB2";
                case id::thumb::SUB3: return "SUB3";
                case id::thumb::SUB4: return "SUB4";
                case id::thumb::MUL: return "MUL";
                case id::thumb::AND: return "AND";
                case id::thumb::ASR1: return "ASR1";
                case id::thumb::ASR2: return "ASR2";
                case id::thumb::BIC: return "BIC";
                case id::thumb::EOR: return "EOR";
                case id::thumb::LSL1: return "LSL1";
                case id::thumb::LSL2: return "LSL2";
                case id::thumb::LSR1: return "LSR1";
                case id::thumb::LSR2: return "LSR2";
                case id::thumb::NEG: return "NEG";
                case id::thumb::ORR: return "ORR";
                case id::thumb::ROR: return "ROR";
                case id::thumb::TST: return "TST";
                case id::thumb::CMN: return "CMN";
                case id::thumb::CMP1: return "CMP1";
                case id::thumb::CMP2: return "CMP2";
                case id::thumb::CMP3: return "CMP3";
                case id::thumb::MOV1: return "MOV1";
                case id::thumb::MOV2: return "MOV2";
                case id::thumb::MOV3: return "MOV3";
                case id::thumb::MVN: return "MVN";
                case id::thumb::B1: return "B1";
                case id::thumb::B2: return "B2";
                case id::thumb::BL: return "BL";
                case id::thumb::BLX1: return "BLX1";
                case id::thumb::BLX2: return "BLX2";
                case id::thumb::BX: return "BX";
                case id::thumb::NOP: return "NOP";
                case id::thumb::BKPT: return "BKPT";
                case id::thumb::SWI: return "SWI";
                case id::thumb::LDMIA: return "LDMIA";
                case id::thumb::LDR1: return "LDR1";
                case id::thumb::LDR2: return "LDR2";
                case id::thumb::LDR3: return "LDR3";
                case id::thumb::LDR4: return "LDR4";
                case id::thumb::LDRB1: return "LDRB1";
                case id::thumb::LDRB2: return "LDRB2";
                case id::thumb::LDRH1: return "LDRH1";
                case id::thumb::LDRH2: return "LDRH2";
                case id::thumb::LDRSB: return "LDRSB";
                case id::thumb::LDRSH: return "LDRSH";
                case id::thumb::POP: return "POP";
                case id::thumb::PUSH: return "PUSH";
                case id::thumb::STMIA: return "STMIA";
                case id::thumb::STR1: return "STR1";
                case id::thumb::STR2: return "STR2";
                case id::thumb::STR3: return "STR3";
                case id::thumb::STRB1: return "STRB1";
                case id::thumb::STRB2: return "STRB2";
                case id::thumb::STRH1: return "STRH1";
                case id::thumb::STRH2: return "STRH2";
            }
        }


        inline std::string arm_id_to_string(const id::arm id) {
            switch (id) {
                case id::arm::UNKNOWN: return "UNKNOWN";
                case id::arm::ADC: return "ADC"; 
                case id::arm::ADD: return "ADD"; 
                case id::arm::AND: return "AND"; 
                case id::arm::UNDEFINED: return "UNDEFINED"; 
                case id::arm::NOP: return "NOP"; 
                case id::arm::B: return "B"; 
                case id::arm::BL: return "BL"; 
                case id::arm::BIC: return "BIC"; 
                case id::arm::CDP: return "CDP"; 
                case id::arm::CMN: return "CMN"; 
                case id::arm::CMP: return "CMP"; 
                case id::arm::EOR: return "EOR"; 
                case id::arm::LDC: return "LDC"; 
                case id::arm::LDM1: return "LDM1"; 
                case id::arm::LDM2: return "LDM2"; 
                case id::arm::LDM3: return "LDM3"; 
                case id::arm::LDR: return "LDR"; 
                case id::arm::LDRB: return "LDRB"; 
                case id::arm::LDRBT: return "LDRBT"; 
                case id::arm::LDRT: return "LDRT"; 
                case id::arm::MCR: return "MCR"; 
                case id::arm::MLA: return "MLA"; 
                case id::arm::MOV: return "MOV"; 
                case id::arm::MRC: return "MRC"; 
                case id::arm::MRS: return "MRS"; 
                case id::arm::MSR_IMM: return "MSR_IMM"; 
                case id::arm::MSR_REG: return "MSR_REG"; 
                case id::arm::MUL: return "MUL"; 
                case id::arm::MVN: return "MVN"; 
                case id::arm::ORR: return "ORR"; 
                case id::arm::RSB: return "RSB"; 
                case id::arm::RSC: return "RSC"; 
                case id::arm::SBC: return "SBC"; 
                case id::arm::STC: return "STC"; 
                case id::arm::STM1: return "STM1"; 
                case id::arm::STM2: return "STM2"; 
                case id::arm::STR: return "STR"; 
                case id::arm::STRB: return "STRB"; 
                case id::arm::STRBT: return "STRBT"; 
                case id::arm::STRT: return "STRT"; 
                case id::arm::SUB: return "SUB"; 
                case id::arm::SWI: return "SWI"; 
                case id::arm::SWP: return "SWP"; 
                case id::arm::SWPB: return "SWPB"; 
                case id::arm::TEQ: return "TEQ"; 
                case id::arm::TST: return "TST"; 
                case id::arm::PSR: return "PSR"; 
                case id::arm::STRH: return "STRH"; 
                case id::arm::LDRH: return "LDRH"; 
                case id::arm::LDRSB: return "LDRSB"; 
                case id::arm::LDRSH: return "LDRSH"; 
                case id::arm::BKPT: return "BKPT"; 
                case id::arm::BLX1: return "BLX1"; 
                case id::arm::BLX2: return "BLX2"; 
                case id::arm::CLZ: return "CLZ"; 
                case id::arm::BX: return "BX"; 
                case id::arm::SMLAL: return "SMLAL"; 
                case id::arm::SMULL: return "SMULL"; 
                case id::arm::UMLAL: return "UMLAL"; 
                case id::arm::UMULL: return "UMULL"; 
                case id::arm::LDRD: return "LDRD"; 
                case id::arm::MCRR: return "MCRR"; 
                case id::arm::MRRC: return "MRRC"; 
                case id::arm::PLD: return "PLD"; 
                case id::arm::QADD: return "QADD"; 
                case id::arm::QDADD: return "QDADD"; 
                case id::arm::QDSUB: return "QDSUB"; 
                case id::arm::QSUB: return "QSUB"; 
                case id::arm::SMLAXY: return "SMLA<x><y>"; 
                case id::arm::SMLALXY: return "SMLAL<x><y>";
                case id::arm::SMLAWY: return "SMLAW<y>"; 
                case id::arm::SMULXY: return "SMUL<x><y>"; 
                case id::arm::SMULWY: return "SMULW<y>"; 
                case id::arm::STRD: return "STRD"; 
                case id::arm::FABSD: return "FABSD"; 
                case id::arm::FABSS: return "FABSS"; 
                case id::arm::FADDD: return "FADDD"; 
                case id::arm::FADDS: return "FADDS"; 
                case id::arm::FCMPD: return "FCMPD"; 
                case id::arm::FCMPED: return "FCMPED"; 
                case id::arm::FCMPES: return "FCMPES"; 
                case id::arm::FCMPEZD: return "FCMPEZD"; 
                case id::arm::FCMPEZS: return "FCMPEZS"; 
                case id::arm::FCMPS: return "FCMPS"; 
                case id::arm::FCMPZD: return "FCMPZD"; 
                case id::arm::FCMPZS: return "FCMPZS"; 
                case id::arm::FCPYD: return "FCPYD"; 
                case id::arm::FCPYS: return "FCPYS"; 
                case id::arm::FCVTDS: return "FCVTDS"; 
                case id::arm::FCVTSD: return "FCVTSD"; 
                case id::arm::FDIVD: return "FDIVD"; 
                case id::arm::FDIVS: return "FDIVS"; 
                case id::arm::FLDD: return "FLDD"; 
                case id::arm::FLDMD: return "FLDMD"; 
                case id::arm::FLDMS: return "FLDMS"; 
                case id::arm::FLDMX: return "FLDMX"; 
                case id::arm::FLDS: return "FLDS"; 
                case id::arm::FMACD: return "FMACD"; 
                case id::arm::FMACS: return "FMACS"; 
                case id::arm::FMDHR: return "FMDHR"; 
                case id::arm::FMDLR: return "FMDLR"; 
                case id::arm::FMRDH: return "FMRDH"; 
                case id::arm::FMRDL: return "FMRDL"; 
                case id::arm::FMRS: return "FMRS"; 
                case id::arm::FMRX: return "FMRX"; 
                case id::arm::FMSCD: return "FMSCD"; 
                case id::arm::FMSCS: return "FMSCS"; 
                case id::arm::FMSR: return "FMSR"; 
                case id::arm::FMSTAT: return "FMSTAT"; 
                case id::arm::FMULD: return "FMULD"; 
                case id::arm::FMULS: return "FMULS"; 
                case id::arm::FMXR: return "FMXR"; 
                case id::arm::FNEGD: return "FNEGD"; 
                case id::arm::FNEGS: return "FNEGS"; 
                case id::arm::FNMACD: return "FNMACD"; 
                case id::arm::FNMACS: return "FNMACS"; 
                case id::arm::FNMSCD: return "FNMSCD"; 
                case id::arm::FNMSCS: return "FNMSCS"; 
                case id::arm::FNMULD: return "FNMULD"; 
                case id::arm::FNMULS: return "FNMULS"; 
                case id::arm::FSITOD: return "FSITOD"; 
                case id::arm::FSITOS: return "FSITOS"; 
                case id::arm::FSQRTD: return "FSQRTD"; 
                case id::arm::FSQRTS: return "FSQRTS"; 
                case id::arm::FSTD: return "FSTD"; 
                case id::arm::FSTMD: return "FSTMD"; 
                case id::arm::FSTMS: return "FSTMS"; 
                case id::arm::FSTMX: return "FSTMX"; 
                case id::arm::FSTS: return "FSTS"; 
                case id::arm::FSUBD: return "FSUBD"; 
                case id::arm::FSUBS: return "FSUBS"; 
                case id::arm::FTOSID: return "FTOSID"; 
                case id::arm::FTOSIS: return "FTOSIS"; 
                case id::arm::FTOUID: return "FTOUID"; 
                case id::arm::FTOUIS: return "FTOUIS"; 
                case id::arm::FUITOD: return "FUITOD"; 
                case id::arm::FUITOS: return "FUITOS";
                case id::arm::CDP2: return "CDP2";
                case id::arm::LDC2: return "LDC2";
                case id::arm::MCR2: return "MCR2";
                case id::arm::MRC2: return "MRC2";
                case id::arm::STC2: return "STC2";
            }
        }
    }
}
