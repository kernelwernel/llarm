#pragma once

#include "types.hpp"

#include <bitset>

namespace opcodes {
    namespace arm {
        [[nodiscard]] bool ADC(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool ADD(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool AND(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool UNDEFINED(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool NOP(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool B_BL(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool BIC(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool CDP(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool CMN(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool CMP(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool EOR(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool LDC(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool LDM(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool LDM2(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool LDM3(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool LDR(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool LDRB(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool LDRBT(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool LDRT(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool MCR(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool MLA(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool MOV(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool MRC(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool MRS(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool MSR_IMM(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool MSR_OPR(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool MUL(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool MVN(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool ORR(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool RSB(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool RSC(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool SBC(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool STC(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool STM1(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool STM2(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool STR(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool STRB(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool STRBT(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool STRT(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool SUB(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool SWI(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool SWP(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool SWPB(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool TEQ(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool TST(const arm_code_t &raw_code) noexcept;
        [[nodiscard]] bool PSR(const arm_code_t &raw_code) noexcept;

        namespace v4 {
            [[nodiscard]] bool STRH(const arm_code_t &raw_code) noexcept;
            [[nodiscard]] bool LDRH(const arm_code_t &raw_code) noexcept;
            [[nodiscard]] bool LDRSB(const arm_code_t &raw_code) noexcept;
            [[nodiscard]] bool LDRSH(const arm_code_t &raw_code) noexcept;
        }

        namespace v5 {
            [[nodiscard]] bool BKPT(const arm_code_t &raw_code) noexcept;
            [[nodiscard]] bool BLX1(const arm_code_t &raw_code) noexcept;
            [[nodiscard]] bool BLX2(const arm_code_t &raw_code) noexcept;
            [[nodiscard]] bool CLZ(const arm_code_t &raw_code) noexcept;
        }

        // VERSION 5 BUT SUPPORTS VERSION 4 T VARIANT
        namespace v5v4t {
            [[nodiscard]] bool BX(const arm_code_t &raw_code) noexcept;
        }

        // M variants
        namespace M {
            [[nodiscard]] bool SMLAL(const arm_code_t &raw_code) noexcept;
            [[nodiscard]] bool SMULL(const arm_code_t &raw_code) noexcept;
            [[nodiscard]] bool UMLAL(const arm_code_t &raw_code) noexcept;
            [[nodiscard]] bool UMULL(const arm_code_t &raw_code) noexcept;
        }
    }

    namespace thumb {
        [[nodiscard]] bool ADC(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool ADD1(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool ADD2(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool ADD3(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool ADD4(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool ADD5(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool ADD6(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool ADD7(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool AND(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool ASR1(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool ASR2(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool B1(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool B2(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool BIC(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool BL(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool BX(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool CMN(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool CMP1(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool CMP2(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool CMP3(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool EOR(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool LDMIA(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool LDR1(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool LDR2(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool LDR3(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool LDR4(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool LDRB1(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool LDRB2(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool LDRH1(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool LDRH2(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool LDRSB(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool LDRSH(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool LSL1(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool LSL2(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool LSR1(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool LSR2(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool MOV1(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool MOV2(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool MOV3(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool MUL(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool MVN(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool NOP(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool NEG(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool ORR(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool POP(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool PUSH(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool ROR(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool SBC(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool STMIA(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool STR1(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool STR2(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool STR3(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool STRB1(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool STRB2(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool STRH1(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool STRH2(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool SUB1(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool SUB2(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool SUB3(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool SUB4(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool SWI(const thumb_code_t &raw_code) noexcept;
        [[nodiscard]] bool TST(const thumb_code_t &raw_code) noexcept;

        namespace v5 {
            [[nodiscard]] bool BKPT(const thumb_code_t &raw_code) noexcept;
            [[nodiscard]] bool BLX1(const thumb_code_t &raw_code) noexcept;
            [[nodiscard]] bool BLX2(const thumb_code_t &raw_code) noexcept;
        }
    }
}















/*
THUMB CHECKLIST:
ADC
ADD (all forms)
AND
ASR (both forms)
B (both forms)
BIC
BKP
BL
BLX (both forms
BX
CMN
CMP (all forms)
EOR
LDMIA
LDR (all forms)
LDRB (both forms)
LDRH (both forms)
LDRSB
LDRSH
LSL (both forms)
LSR (both forms)
MOV (all forms)
MUL
MVN
NEG
ORR
POP
PUSH
ROR
SBC
STMIA
STR (all forms)
STRB (both forms)
STRH (both forms)
SUB (all forms)
SWI
TST
*/