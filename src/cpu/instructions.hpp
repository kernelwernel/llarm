#pragma once

#include "types.hpp"
#include "core/registers.hpp"

struct instructions {
    namespace math {
        void ADC(const code_t&, REGISTERS&); // TODO, NOTE: MUST TEST CARRY AND OVERFLOW
        void ADD(const code_t&, REGISTERS&); // same
        void RSB(const code_t&, REGISTERS&); // TODO
        void RSC(const code_t&, REGISTERS&); // TODO
        void SBC(const code_t&, REGISTERS&); // TODO
        void SUB(const code_t&, REGISTERS&); // TODO
    }
    namespace compare {
        void CMN(const code_t&, REGISTERS&);  // TODO
    }
    namespace logic {
        void AND(const code_t&, REGISTERS&); // TODO
        void CMN(const code_t&, REGISTERS&); // TODO
        void CMP(const code_t&, REGISTERS&); // TODO
        void CLZ(const code_t&, REGISTERS&); // (test if this works, manually)
        void EOR(const code_t&, REGISTERS&); // TODO
        void ORR(const code_t&, REGISTERS&); // TODO
        void TEQ(const code_t&, REGISTERS&); // TODO
        void TST(const code_t&, REGISTERS&); // TODO
    }
    namespace movement {
        void MOV(const code_t&, REGISTERS&); // TODO
        void MVN(const code_t&, REGISTERS&); // TODO
    }
    namespace multiply {
        void MLA(const code_t&, REGISTERS&); // TODO
        void MUL(const code_t&, REGISTERS&); // TODO
        void SMLAL(const code_t&, REGISTERS&); // TODO
        void SMULL(const code_t&, REGISTERS&); // TODO
        void UMLAL(const code_t&, REGISTERS&); // TODO
        void UMULL(const code_t&, REGISTERS&); // TODO
    }
    namespace branching {
        void B(const code_t&, REGISTERS&); // TODO
        void BL(const code_t&, REGISTERS&); // TODO
        void BX(const code_t&, REGISTERS&); // TODO
    }
    namespace coprocessor {
        void CDP(const code_t&, REGISTERS&); // TODO
        void LDC(const code_t&, REGISTERS&); // TODO
        void MCR(const code_t&, REGISTERS&); // TODO
        void MRC(const code_t&, REGISTERS&); // TODO
        void STC(const code_t&, REGISTERS&); // TODO
    }
    namespace misc {
        void NOP([[maybe_unused]] const code_t&, [[maybe_unused]] REGISTERS&) noexcept;
        void SWI(const code_t&, REGISTERS&); // TODO
    }
    namespace load {
        void LDM1(const code_t&, REGISTERS&); // TODO
        void LDM2(const code_t&, REGISTERS&); // TODO
        void LDM3(const code_t&, REGISTERS&); // TODO
        void LDR(const code_t&, REGISTERS&); // TODO
        void LDRB(const code_t&, REGISTERS&); // TODO
        void LDRBT(const code_t&, REGISTERS&); // TODO
        void LDRH(const code_t&, REGISTERS&); // TODO
        void LDRSB(const code_t&, REGISTERS&); // TODO
        void LDRSH(const code_t&, REGISTERS&); // TODO
        void LDRT(const code_t&, REGISTERS&); // TODO
    }
    namespace store {
        void STM1(const code_t&, REGISTERS&); // TODO
        void STM2(const code_t&, REGISTERS&); // TODO
        void STR(const code_t&, REGISTERS&); // TODO
        void STRB(const code_t&, REGISTERS&); // TODO
        void STRBT(const code_t&, REGISTERS&); // TODO
        void STRH(const code_t&, REGISTERS&); // TODO
        void STRT(const code_t&, REGISTERS&); // TODO
        void SWP(const code_t&, REGISTERS&); // TODO
        void SWPB(const code_t&, REGISTERS&); // TODO
    }
    namespace status {
        void MRS(const code_t&, REGISTERS&);// TODO
        void MSR(const code_t&, REGISTERS&);// TODO
    }








    namespace thumb {
        namespace math {
            void ADC(const thumbcode_t&, REGISTERS&);
            void ADD1(const thumbcode_t&, REGISTERS&);
            void ADD2(const thumbcode_t&, REGISTERS&);
            void ADD3(const thumbcode_t&, REGISTERS&);
            void ADD4(const thumbcode_t&, REGISTERS&);
            void ADD5(const thumbcode_t&, REGISTERS&);
            void ADD6(const thumbcode_t&, REGISTERS&);
            void ADD7(const thumbcode_t&, REGISTERS&);
            void SBC(const thumbcode_t&, REGISTERS&); // NOTE: BORROW_SUB (TRIPLE) AND OVERFLOW_SUB (TRIPLE) MIGHT HAVE WRONG IMPL
            void SUB1(const thumbcode_t&, REGISTERS&);
            void SUB2(const thumbcode_t&, REGISTERS&);
            void SUB3(const thumbcode_t&, REGISTERS&);
            void SUB4(const thumbcode_t&, REGISTERS&);
            void MUL(const thumbcode_t&, REGISTERS&);
        }
        namespace logic {
            void AND(const thumbcode_t&, REGISTERS&);
            void ASR1(const thumbcode_t&, REGISTERS&); // NOTE: ARITHMETIC_SHIFT_RIGHT IMPLEMENTATION MIGHT BE WRONG
            void ASR2(const thumbcode_t&, REGISTERS&); // NOTE: ARITHMETIC_SHIFT_RIGHT IMPLEMENTATION MIGHT BE WRONG
            void BIC(const thumbcode_t&, REGISTERS&);
            void EOR(const thumbcode_t&, REGISTERS&);
            void LSL1(const thumbcode_t&, REGISTERS&);
            void LSL2(const thumbcode_t&, REGISTERS&);
            void LSR1(const thumbcode_t&, REGISTERS&);
            void LSR2(const thumbcode_t&, REGISTERS&);
            void NEG(const thumbcode_t&, REGISTERS&); // NOTE: OVERFLOW_SUB MIGHT LEAD TO ERROR
            void ORR(const thumbcode_t&, REGISTERS&);
            void ROR(const thumbcode_t&, REGISTERS&);
            void TST(const thumbcode_t&, REGISTERS&);
        }
        namespace compare {
            void CMN(const thumbcode_t&, REGISTERS&); // NOTE: BORROW_FROM MIGHT LEAD TO ERROR
            void CMP1(const thumbcode_t&, REGISTERS&); // NOTE: OVERFLOW_SUB MIGHT LEAD TO ERROR
            void CMP2(const thumbcode_t&, REGISTERS&); // NOTE: OVERFLOW_SUB MIGHT LEAD TO ERROR
            void CMP3(const thumbcode_t&, REGISTERS&);
        }
        namespace movement {
            void MOV1(const thumbcode_t&, REGISTERS&);
            void MOV2(const thumbcode_t&, REGISTERS&);
            void MOV3(const thumbcode_t&, REGISTERS&);
            void MVN(const thumbcode_t&, REGISTERS&);
        }
        namespace branching {
            void B1(const thumbcode_t&, REGISTERS&);
            void B2(const thumbcode_t&, REGISTERS&);
            void BL(const thumbcode_t&, REGISTERS&); // TODO
            void BLX1(const thumbcode_t&, REGISTERS&); // TODO
            void BLX2(const thumbcode_t&, REGISTERS&); // TODO
            void BX(const thumbcode_t&, REGISTERS&);
        }
        namespace misc {
            void NOP([[maybe_unused]] const thumbcode_t&, [[maybe_unused]] REGISTERS&) noexcept;
            void BKPT(const thumbcode_t&, REGISTERS&); // TODO
            void SWI(const thumbcode_t&, REGISTERS&); // TODO
        }
        namespace load {
            void LDMIA(const thumbcode_t&, REGISTERS&); // TODO
            void LDR1(const thumbcode_t&, REGISTERS&); // TODO
            void LDR2(const thumbcode_t&, REGISTERS&); // TODO
            void LDR3(const thumbcode_t&, REGISTERS&); // TODO
            void LDR4(const thumbcode_t&, REGISTERS&); // TODO
            void LDRB1(const thumbcode_t&, REGISTERS&); // TODO
            void LDRB2(const thumbcode_t&, REGISTERS&); // TODO
            void LDRH1(const thumbcode_t&, REGISTERS&); // TODO
            void LDRH2(const thumbcode_t&, REGISTERS&); // TODO
            void LDRSB(const thumbcode_t&, REGISTERS&); // TODO
            void LDRSH(const thumbcode_t&, REGISTERS&); // TODO
            void POP(const thumbcode_t&, REGISTERS&); // TODO
        }
        namespace store {
            void STMIA(const thumbcode_t&, REGISTERS&); // TODO
            void STR1(const thumbcode_t&, REGISTERS&); // TODO
            void STR2(const thumbcode_t&, REGISTERS&); // TODO
            void STR3(const thumbcode_t&, REGISTERS&); // TODO
            void STRB1(const thumbcode_t&, REGISTERS&); // TODO
            void STRH1(const thumbcode_t&, REGISTERS&); // TODO
            void STRH2(const thumbcode_t&, REGISTERS&); // TODO
            void PUSH(const thumbcode_t&, REGISTERS&); // TODO
        }
    }

    //instructions()
}