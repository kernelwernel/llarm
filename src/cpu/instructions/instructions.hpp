#pragma once

#include "types.hpp"
#include "core/registers.hpp"

struct instructions {
    namespace arm {
        namespace math {
            void ADC(const arm_code_t&, REGISTERS&); // TODO, NOTE: MUST TEST CARRY AND OVERFLOW
            void ADD(const arm_code_t&, REGISTERS&); // same
            void RSB(const arm_code_t&, REGISTERS&); // TODO
            void RSC(const arm_code_t&, REGISTERS&); // TODO
            void SBC(const arm_code_t&, REGISTERS&); // TODO
            void SUB(const arm_code_t&, REGISTERS&); // TODO
        }
        namespace compare {
            void CMN(const arm_code_t&, REGISTERS&);  // TODO
        }
        namespace logic {
            void AND(const arm_code_t&, REGISTERS&); // TODO
            void CMN(const arm_code_t&, REGISTERS&); // TODO
            void CMP(const arm_code_t&, REGISTERS&); // TODO
            void CLZ(const arm_code_t&, REGISTERS&); // (test if this works, manually)
            void EOR(const arm_code_t&, REGISTERS&); // TODO
            void ORR(const arm_code_t&, REGISTERS&); // TODO
            void TEQ(const arm_code_t&, REGISTERS&); // TODO
            void TST(const arm_code_t&, REGISTERS&); // TODO
        }
        namespace movement {
            void MOV(const arm_code_t&, REGISTERS&); // TODO
            void MVN(const arm_code_t&, REGISTERS&); // TODO
        }
        namespace multiply {
            void MLA(const arm_code_t&, REGISTERS&); // TODO
            void MUL(const arm_code_t&, REGISTERS&); // TODO
            void SMLAL(const arm_code_t&, REGISTERS&); // TODO
            void SMULL(const arm_code_t&, REGISTERS&); // TODO
            void UMLAL(const arm_code_t&, REGISTERS&); // TODO
            void UMULL(const arm_code_t&, REGISTERS&); // TODO
        }
        namespace branching {
            void B(const arm_code_t&, REGISTERS&); // TODO
            void BL(const arm_code_t&, REGISTERS&); // TODO
            void BX(const arm_code_t&, REGISTERS&); // TODO
        }
        namespace coprocessor {
            void CDP(const arm_code_t&, REGISTERS&); // TODO
            void LDC(const arm_code_t&, REGISTERS&); // TODO
            void MCR(const arm_code_t&, REGISTERS&); // TODO
            void MRC(const arm_code_t&, REGISTERS&); // TODO
            void STC(const arm_code_t&, REGISTERS&); // TODO
        }
        namespace misc {
            void NOP([[maybe_unused]] const arm_code_t&, [[maybe_unused]] REGISTERS&) noexcept;
            void PSR(const arm_code_t&, [[maybe_unused]] REGISTERS&) noexcept;
            void SWI(const arm_code_t&, REGISTERS&); // TODO
        }
        namespace load {
            void LDM1(const arm_code_t&, REGISTERS&); // TODO
            void LDM2(const arm_code_t&, REGISTERS&); // TODO
            void LDM3(const arm_code_t&, REGISTERS&); // TODO
            void LDR(const arm_code_t&, REGISTERS&); // TODO
            void LDRB(const arm_code_t&, REGISTERS&); // TODO
            void LDRBT(const arm_code_t&, REGISTERS&); // TODO
            void LDRH(const arm_code_t&, REGISTERS&); // TODO
            void LDRSB(const arm_code_t&, REGISTERS&); // TODO
            void LDRSH(const arm_code_t&, REGISTERS&); // TODO
            void LDRT(const arm_code_t&, REGISTERS&); // TODO
        }
        namespace store {
            void STM1(const arm_code_t&, REGISTERS&); // TODO
            void STM2(const arm_code_t&, REGISTERS&); // TODO
            void STR(const arm_code_t&, REGISTERS&); // TODO
            void STRB(const arm_code_t&, REGISTERS&); // TODO
            void STRBT(const arm_code_t&, REGISTERS&); // TODO
            void STRH(const arm_code_t&, REGISTERS&); // TODO
            void STRT(const arm_code_t&, REGISTERS&); // TODO
            void SWP(const arm_code_t&, REGISTERS&); // TODO
            void SWPB(const arm_code_t&, REGISTERS&); // TODO
        }
        namespace status {
            void MRS(const arm_code_t&, REGISTERS&);// TODO
            void MSR(const arm_code_t&, REGISTERS&);// TODO
        }
        namespace DSP {
            void LDRD(const arm_code_t&, REGISTERS&); // TODO
            void MCRR(const arm_code_t&, REGISTERS&); // TODO
            void MRRC(const arm_code_t&, REGISTERS&); // TODO
            void PLD(const arm_code_t&, REGISTERS&); // TODO
            void QADD(const arm_code_t&, REGISTERS&); // TODO
            void QDADD(const arm_code_t&, REGISTERS&); // TODO
            void QDSUB(const arm_code_t&, REGISTERS&); // TODO
            void QSUB(const arm_code_t&, REGISTERS&); // TODO
            void SMLA(const arm_code_t&, REGISTERS&); // TODO
            void SMLAL(const arm_code_t&, REGISTERS&); // TODO
            void SMLAW(const arm_code_t&, REGISTERS&); // TODO
            void SMUL(const arm_code_t&, REGISTERS&); // TODO
            void SMULW(const arm_code_t&, REGISTERS&); // TODO
            void STRD(const arm_code_t&, REGISTERS&); // TODO
        }
    }








    namespace thumb {
        namespace math {
            void ADC(const thumb_code_t&, REGISTERS&);
            void ADD1(const thumb_code_t&, REGISTERS&);
            void ADD2(const thumb_code_t&, REGISTERS&);
            void ADD3(const thumb_code_t&, REGISTERS&);
            void ADD4(const thumb_code_t&, REGISTERS&);
            void ADD5(const thumb_code_t&, REGISTERS&);
            void ADD6(const thumb_code_t&, REGISTERS&);
            void ADD7(const thumb_code_t&, REGISTERS&);
            void SBC(const thumb_code_t&, REGISTERS&); // NOTE: BORROW_SUB (TRIPLE) AND OVERFLOW_SUB (TRIPLE) MIGHT HAVE WRONG IMPL
            void SUB1(const thumb_code_t&, REGISTERS&);
            void SUB2(const thumb_code_t&, REGISTERS&);
            void SUB3(const thumb_code_t&, REGISTERS&);
            void SUB4(const thumb_code_t&, REGISTERS&);
            void MUL(const thumb_code_t&, REGISTERS&);
        }
        namespace logic {
            void AND(const thumb_code_t&, REGISTERS&);
            void ASR1(const thumb_code_t&, REGISTERS&); // NOTE: ARITHMETIC_SHIFT_RIGHT IMPLEMENTATION MIGHT BE WRONG
            void ASR2(const thumb_code_t&, REGISTERS&); // NOTE: ARITHMETIC_SHIFT_RIGHT IMPLEMENTATION MIGHT BE WRONG
            void BIC(const thumb_code_t&, REGISTERS&);
            void EOR(const thumb_code_t&, REGISTERS&);
            void LSL1(const thumb_code_t&, REGISTERS&);
            void LSL2(const thumb_code_t&, REGISTERS&);
            void LSR1(const thumb_code_t&, REGISTERS&);
            void LSR2(const thumb_code_t&, REGISTERS&);
            void NEG(const thumb_code_t&, REGISTERS&); // NOTE: OVERFLOW_SUB MIGHT LEAD TO ERROR
            void ORR(const thumb_code_t&, REGISTERS&);
            void ROR(const thumb_code_t&, REGISTERS&);
            void TST(const thumb_code_t&, REGISTERS&);
        }
        namespace compare {
            void CMN(const thumb_code_t&, REGISTERS&); // NOTE: BORROW_FROM MIGHT LEAD TO ERROR
            void CMP1(const thumb_code_t&, REGISTERS&); // NOTE: OVERFLOW_SUB MIGHT LEAD TO ERROR
            void CMP2(const thumb_code_t&, REGISTERS&); // NOTE: OVERFLOW_SUB MIGHT LEAD TO ERROR
            void CMP3(const thumb_code_t&, REGISTERS&);
        }
        namespace movement {
            void MOV1(const thumb_code_t&, REGISTERS&);
            void MOV2(const thumb_code_t&, REGISTERS&);
            void MOV3(const thumb_code_t&, REGISTERS&);
            void MVN(const thumb_code_t&, REGISTERS&);
        }
        namespace branching {
            void B1(const thumb_code_t&, REGISTERS&);
            void B2(const thumb_code_t&, REGISTERS&);
            void BL(const thumb_code_t&, REGISTERS&);
            void BLX1(const thumb_code_t&, REGISTERS&); // (v5, idk if thumb2)
            void BLX2(const thumb_code_t&, REGISTERS&); // (v5, idk if thumb2), and double check
            void BX(const thumb_code_t&, REGISTERS&); // double check
        }
        namespace misc {
            void NOP([[maybe_unused]] const thumb_code_t&, [[maybe_unused]] REGISTERS&) noexcept;
            void BKPT(const thumb_code_t&, REGISTERS&); // (v5)
            void SWI(const thumb_code_t&, REGISTERS&); // TODO
        }
        namespace load {
            void LDMIA(const thumb_code_t&, REGISTERS&); // TODO
            void LDR1(const thumb_code_t&, REGISTERS&); // TODO
            void LDR2(const thumb_code_t&, REGISTERS&); // TODO
            void LDR3(const thumb_code_t&, REGISTERS&); // TODO
            void LDR4(const thumb_code_t&, REGISTERS&); // TODO
            void LDRB1(const thumb_code_t&, REGISTERS&); // TODO
            void LDRB2(const thumb_code_t&, REGISTERS&); // TODO
            void LDRH1(const thumb_code_t&, REGISTERS&); // TODO
            void LDRH2(const thumb_code_t&, REGISTERS&); // TODO
            void LDRSB(const thumb_code_t&, REGISTERS&); // TODO
            void LDRSH(const thumb_code_t&, REGISTERS&); // TODO
            void POP(const thumb_code_t&, REGISTERS&); // TODO
        }
        namespace store {
            void STMIA(const thumb_code_t&, REGISTERS&); // TODO
            void STR1(const thumb_code_t&, REGISTERS&); // TODO
            void STR2(const thumb_code_t&, REGISTERS&); // TODO
            void STR3(const thumb_code_t&, REGISTERS&); // TODO
            void STRB1(const thumb_code_t&, REGISTERS&); // TODO
            void STRB2(const thumb_code_t&, REGISTERS&); // TODO
            void STRH1(const thumb_code_t&, REGISTERS&); // TODO
            void STRH2(const thumb_code_t&, REGISTERS&); // TODO
            void PUSH(const thumb_code_t&, REGISTERS&); // TODO
        }
    }


    namespace jazelle {
        
    }

    //instructions()
}