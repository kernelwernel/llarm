#pragma once

#include <charm/internal/charm-asm/src/identifiers/identifiers.hpp>
#include <charm/internal/charm-asm/src/opcodes/opcodes.hpp>
#include <charm/internal/charm-asm/src/instruction_id.hpp>
#include <charm/internal/charm-asm/src/instruction_table.hpp>

namespace charm {
    namespace assembly {
        namespace id {
            // alternatives in case it's under C++17
            using arm = internal::id::arm;
            using thumb = internal::id::thumb;
            using jazelle = internal::id::jazelle;

            //enum class arm : internal::id::arm {};
            //enum class thumb : internal::id::thumb {};
            //enum class jazelle : internal::id::jazelle {};
        }


        namespace identify {
            static id::arm arm(const arm_code_t &raw_code) {
                return internal::identifiers::arm_identifier(raw_code);
            }

            static id::arm arm(const u32 &raw_code) {
                return internal::identifiers::arm_identifier(raw_code);
            }

            static id::thumb thumb(const thumb_code_t &raw_code) {
                return internal::identifiers::thumb_identifier(raw_code);
            }

            static id::thumb thumb(const u16 &raw_code) {
                return internal::identifiers::thumb_identifier(raw_code);
            }

            static id::jazelle jazelle(const u8 raw_code) {
                return internal::identifiers::jazelle_identifier(raw_code);
            }
        }


        static std::string thumb_id_to_string(const internal::id::thumb id) {
            switch (id) {
                case internal::id::thumb::UNKNOWN: return "UNKNOWN";
                case internal::id::thumb::ADC: return "ADC";
                case internal::id::thumb::ADD1: return "ADD1";
                case internal::id::thumb::ADD2: return "ADD2";
                case internal::id::thumb::ADD3: return "ADD3";
                case internal::id::thumb::ADD4: return "ADD4";
                case internal::id::thumb::ADD5: return "ADD5";
                case internal::id::thumb::ADD6: return "ADD6";
                case internal::id::thumb::ADD7: return "ADD7";
                case internal::id::thumb::SBC: return "SBC";
                case internal::id::thumb::SUB1: return "SUB1";
                case internal::id::thumb::SUB2: return "SUB2";
                case internal::id::thumb::SUB3: return "SUB3";
                case internal::id::thumb::SUB4: return "SUB4";
                case internal::id::thumb::MUL: return "MUL";
                case internal::id::thumb::AND: return "AND";
                case internal::id::thumb::ASR1: return "ASR1";
                case internal::id::thumb::ASR2: return "ASR2";
                case internal::id::thumb::BIC: return "BIC";
                case internal::id::thumb::EOR: return "EOR";
                case internal::id::thumb::LSL1: return "LSL1";
                case internal::id::thumb::LSL2: return "LSL2";
                case internal::id::thumb::LSR1: return "LSR1";
                case internal::id::thumb::LSR2: return "LSR2";
                case internal::id::thumb::NEG: return "NEG";
                case internal::id::thumb::ORR: return "ORR";
                case internal::id::thumb::ROR: return "ROR";
                case internal::id::thumb::TST: return "TST";
                case internal::id::thumb::CMN: return "CMN";
                case internal::id::thumb::CMP1: return "CMP1";
                case internal::id::thumb::CMP2: return "CMP2";
                case internal::id::thumb::CMP3: return "CMP3";
                case internal::id::thumb::MOV1: return "MOV1";
                case internal::id::thumb::MOV2: return "MOV2";
                case internal::id::thumb::MOV3: return "MOV3";
                case internal::id::thumb::MVN: return "MVN";
                case internal::id::thumb::B1: return "B1";
                case internal::id::thumb::B2: return "B2";
                case internal::id::thumb::BL: return "BL";
                case internal::id::thumb::BLX1: return "BLX1";
                case internal::id::thumb::BLX2: return "BLX2";
                case internal::id::thumb::BX: return "BX";
                case internal::id::thumb::NOP: return "NOP";
                case internal::id::thumb::BKPT: return "BKPT";
                case internal::id::thumb::SWI: return "SWI";
                case internal::id::thumb::LDMIA: return "LDMIA";
                case internal::id::thumb::LDR1: return "LDR1";
                case internal::id::thumb::LDR2: return "LDR2";
                case internal::id::thumb::LDR3: return "LDR3";
                case internal::id::thumb::LDR4: return "LDR4";
                case internal::id::thumb::LDRB1: return "LDRB1";
                case internal::id::thumb::LDRB2: return "LDRB2";
                case internal::id::thumb::LDRH1: return "LDRH1";
                case internal::id::thumb::LDRH2: return "LDRH2";
                case internal::id::thumb::LDRSB: return "LDRSB";
                case internal::id::thumb::LDRSH: return "LDRSH";
                case internal::id::thumb::POP: return "POP";
                case internal::id::thumb::PUSH: return "PUSH";
                case internal::id::thumb::STMIA: return "STMIA";
                case internal::id::thumb::STR1: return "STR1";
                case internal::id::thumb::STR2: return "STR2";
                case internal::id::thumb::STR3: return "STR3";
                case internal::id::thumb::STRB1: return "STRB1";
                case internal::id::thumb::STRH1: return "STRH1";
                case internal::id::thumb::STRH2: return "STRH2";
            };
        }
    }

    // shortened alias, can't use charm::asm because "asm" is already a C/C++ keyword
    namespace as = assembly;
}
