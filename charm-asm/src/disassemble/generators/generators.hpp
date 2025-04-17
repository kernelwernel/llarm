#pragma once

#include "../../instruction_id.hpp"

#include <charm/internal/shared/types.hpp>

#include <functional>
#include <string>
#include <map>

// the generation mechanism was benchmarked here:
// https://quick-bench.com/q/No_nYrHbcGwK5JTFl-qJtJ0ncc0

namespace internal::generators {
    namespace thumb {
        namespace math {
            std::string ADC(const u16 code); 
            std::string ADD1(const u16);
            std::string ADD2(const u16);
            std::string ADD3(const u16);
            std::string ADD4(const u16);
            std::string ADD5(const u16);
            std::string ADD6(const u16);
            std::string ADD7(const u16);
            std::string SBC(const u16);
            std::string SUB1(const u16);
            std::string SUB2(const u16);
            std::string SUB3(const u16);
            std::string SUB4(const u16);
            std::string MUL(const u16);
        }

        namespace logic {
            std::string AND(const u16);
            std::string ASR1(const u16);
            std::string ASR2(const u16);
            std::string BIC(const u16);
            std::string EOR(const u16);
            std::string LSL1(const u16);
            std::string LSL2(const u16);
            std::string LSR1(const u16);
            std::string LSR2(const u16);
            std::string NEG(const u16);
            std::string ORR(const u16);
            std::string ROR(const u16);
            std::string TST(const u16);
        }

        namespace comparison {
            std::string CMN(const u16);
            std::string CMP1(const u16);
            std::string CMP2(const u16);
            std::string CMP3(const u16);
        }

        namespace movement {
            std::string MOV1(const u16);
            std::string MOV2(const u16);
            std::string MOV3(const u16);
            std::string MVN(const u16);
        }

        namespace branching {
            std::string B1(const u16, const u32 PC);
            std::string B2(const u16, const u32 PC);
            std::string BL(const u16, const u32 PC);
            std::string BX(const u16);
            std::string BLX1(const u16, const u32 PC);
            std::string BLX2(const u16);
        }

        namespace misc {
            std::string SWI(const u16);
            std::string BKPT(const u16);
        }

        namespace load {
            std::string LDMIA(const u16);
            std::string LDR1(const u16);
            std::string LDR2(const u16);
            std::string LDR3(const u16);
            std::string LDR4(const u16);
            std::string LDRB1(const u16);
            std::string LDRB2(const u16);
            std::string LDRH1(const u16);
            std::string LDRH2(const u16);
            std::string LDRSB(const u16);
            std::string LDRSH(const u16);
            std::string POP(const u16);
        }

        namespace store {
            std::string STMIA(const u16);
            std::string STR1(const u16);
            std::string STR2(const u16);
            std::string STR3(const u16);
            std::string STRB1(const u16);
            std::string STRB2(const u16);
            std::string STRH1(const u16);
            std::string STRH2(const u16);
            std::string PUSH(const u16);
        }
    }
}