#pragma once

#include "types.hpp"

namespace constants {

    enum class mode : u8 {
        USER_26 = 0b00000,
        FIQ_26 = 0b00001,
        IRQ_26 = 0b00010,
        SUPERVISOR_26 = 0b00011,
        USER = 0b10000,
        SUPERVISOR = 0b10011,
        ABORT = 0b10111,
        UNDEFINED = 0b11011,
        FIQ = 0b10001,
        IRQ = 0b10010,
        SYSTEM = 0b11111
    };

    enum cond : u8 {
        EQ = 0b0000, // equal
        NE = 0b0001, // not equal
        CS = 0b0010, // unsigned higher or same
        CC = 0b0011, // unsigned lower
        MI = 0b0100, // negative
        PL = 0b0101, // positive or zero
        VS = 0b0110, // overflow
        VC = 0b0111, // no overflow 
        HI = 0b1000, // unsigned higher
        LS = 0b1001, // unsigned lower or same
        GE = 0b1010, // greater or equal
        LT = 0b1011, // less than
        GT = 0b1100, // greater than
        LE = 0b1101, // less than or equal
        AL = 0b1110, // always
        NV = 0b1111 // not a real condition
    };

    enum operation : u8 {
        AND = 0b0000, // Rd:= Op1 AND Op2
        EOR = 0b0001, // Rd:= Op1 EOR Op2
        SUB = 0b0010, // Rd:= Op1 - Op2
        RSB = 0b0011, // Rd:= Op2 - Op1
        ADD = 0b0100, // Rd:= Op1 + Op2
        ADC = 0b0101, // Rd:= Op1 + Op2 + C
        SBC = 0b0110, // Rd:= Op1 - Op2 + C - 1
        RSC = 0b0111, // Rd:= Op2 - Op1 + C - 1
        TST = 0b1000, // set condition codes on Op1 AND Op2
        TEQ = 0b1001, // set condition codes on Op1 EOR Op2
        CMP = 0b1010, // set condition codes on Op1 - Op2
        CMN = 0b1011, // set condition codes on Op1 + Op2
        ORR = 0b1100, // Rd:= Op1 OR Op2
        MOV = 0b1101, // Rd:= Op2
        BIC = 0b1110, // Rd:= Op1 AND NOT Op2
        MVN = 0b1111 // Rd:= NOT Op2
    };
}