#pragma once

#include "types.hpp"

#include <bitset>

namespace opcodes {
    [[nodiscard]] bool ADC(const code_t &raw_code) noexcept;
    [[nodiscard]] bool ADD(const code_t &raw_code) noexcept;
    [[nodiscard]] bool AND(const code_t &raw_code) noexcept;
    [[nodiscard]] bool UNDEFINED(const code_t &raw_code) noexcept;
    [[nodiscard]] bool NOP(const code_t &raw_code) noexcept;
    [[nodiscard]] bool B_BL(const code_t &raw_code) noexcept;
    [[nodiscard]] bool BIC(const code_t &raw_code) noexcept;
    [[nodiscard]] bool CDP(const code_t &raw_code) noexcept;
    [[nodiscard]] bool CMN(const code_t &raw_code) noexcept;
    [[nodiscard]] bool CMP(const code_t &raw_code) noexcept;
    [[nodiscard]] bool EOR(const code_t &raw_code) noexcept;
    [[nodiscard]] bool LDC(const code_t &raw_code) noexcept;
    [[nodiscard]] bool LDM(const code_t &raw_code) noexcept;
    [[nodiscard]] bool LDM2(const code_t &raw_code) noexcept;
    [[nodiscard]] bool LDM3(const code_t &raw_code) noexcept;
    [[nodiscard]] bool LDR(const code_t &raw_code) noexcept;
    [[nodiscard]] bool LDRB(const code_t &raw_code) noexcept;
    [[nodiscard]] bool LDRBT(const code_t &raw_code) noexcept;
    [[nodiscard]] bool LDRT(const code_t &raw_code) noexcept;
    [[nodiscard]] bool MCR(const code_t &raw_code) noexcept;
    [[nodiscard]] bool MLA(const code_t &raw_code) noexcept;
    [[nodiscard]] bool MOV(const code_t &raw_code) noexcept;
    [[nodiscard]] bool MRC(const code_t &raw_code) noexcept;
    [[nodiscard]] bool MRS(const code_t &raw_code) noexcept;
    [[nodiscard]] bool MSR_IMM(const code_t &raw_code) noexcept;
    [[nodiscard]] bool MSR_OPR(const code_t &raw_code) noexcept;
    [[nodiscard]] bool MUL(const code_t &raw_code) noexcept;
    [[nodiscard]] bool MVN(const code_t &raw_code) noexcept;
    [[nodiscard]] bool ORR(const code_t &raw_code) noexcept;
    [[nodiscard]] bool RSB(const code_t &raw_code) noexcept;
    [[nodiscard]] bool RSC(const code_t &raw_code) noexcept;
    [[nodiscard]] bool SBC(const code_t &raw_code) noexcept;
    [[nodiscard]] bool STC(const code_t &raw_code) noexcept;
    [[nodiscard]] bool STM1(const code_t &raw_code) noexcept;
    [[nodiscard]] bool STM2(const code_t &raw_code) noexcept;
    [[nodiscard]] bool STR(const code_t &raw_code) noexcept;
    [[nodiscard]] bool STRB(const code_t &raw_code) noexcept;
    [[nodiscard]] bool STRBT(const code_t &raw_code) noexcept;
    [[nodiscard]] bool STRT(const code_t &raw_code) noexcept;
    [[nodiscard]] bool SUB(const code_t &raw_code) noexcept;
    [[nodiscard]] bool SWI(const code_t &raw_code) noexcept;
    [[nodiscard]] bool SWP(const code_t &raw_code) noexcept;
    [[nodiscard]] bool SWPB(const code_t &raw_code) noexcept;
    [[nodiscard]] bool TEQ(const code_t &raw_code) noexcept;
    [[nodiscard]] bool TST(const code_t &raw_code) noexcept;

    namespace v4 {
        [[nodiscard]] bool STRH(const code_t &raw_code) noexcept;
        [[nodiscard]] bool LDRH(const code_t &raw_code) noexcept;
        [[nodiscard]] bool LDRSB(const code_t &raw_code) noexcept;
        [[nodiscard]] bool LDRSH(const code_t &raw_code) noexcept;
    }

    namespace v5 {
        [[nodiscard]] bool BKPT(const code_t &raw_code) noexcept;
        [[nodiscard]] bool BLX1(const code_t &raw_code) noexcept;
        [[nodiscard]] bool BLX2(const code_t &raw_code) noexcept;
        [[nodiscard]] bool CLZ(const code_t &raw_code) noexcept;
    }

    // VERSION 5 BUT SUPPORTS VERSION 4 T VARIANT
    namespace v5v4t {
        [[nodiscard]] bool BX(const code_t &raw_code) noexcept;
    }

    // M variants
    namespace M {
        [[nodiscard]] bool SMLAL(const code_t &raw_code) noexcept;
        [[nodiscard]] bool SMULL(const code_t &raw_code) noexcept;
        [[nodiscard]] bool UMLAL(const code_t &raw_code) noexcept;
        [[nodiscard]] bool UMULL(const code_t &raw_code) noexcept;
    }

    namespace thumb {
        [[nodiscard]] bool ADC(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool ADD1(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool ADD2(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool ADD3(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool ADD4(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool ADD5(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool ADD6(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool ADD7(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool AND(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool ASR1(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool ASR2(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool B1(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool B2(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool BIC(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool BL(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool BX(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool CMN(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool CMP1(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool CMP2(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool CMP3(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool EOR(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool LDMIA(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool LDR1(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool LDR2(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool LDR3(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool LDR4(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool LDRB1(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool LDRB2(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool LDRH1(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool LDRH2(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool LDRSB(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool LDRSH(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool LSL1(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool LSL2(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool LSR1(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool LSR2(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool MOV1(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool MOV2(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool MOV3(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool MUL(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool MVN(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool NOP(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool NEG(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool ORR(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool POP(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool PUSH(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool ROR(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool SBC(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool STMIA(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool STR1(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool STR2(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool STR3(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool STRB1(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool STRB2(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool STRH1(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool STRH2(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool SUB1(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool SUB2(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool SUB3(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool SUB4(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool SWI(const thumbcode_t &raw_code) noexcept;
        [[nodiscard]] bool TST(const thumbcode_t &raw_code) noexcept;

        namespace v5 {
            [[nodiscard]] bool BKPT(const thumbcode_t &raw_code) noexcept;
            [[nodiscard]] bool BLX1(const thumbcode_t &raw_code) noexcept;
            [[nodiscard]] bool BLX2(const thumbcode_t &raw_code) noexcept;
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