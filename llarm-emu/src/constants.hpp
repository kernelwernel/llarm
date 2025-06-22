#pragma once

#include "shared/types.hpp"

namespace constants {

    namespace mode {
        constexpr u8 USER_26 = 0b00000;
        constexpr u8 FIQ_26 = 0b00001;
        constexpr u8 IRQ_26 = 0b00010;
        constexpr u8 SUPERVISOR_26 = 0b00011;
        constexpr u8 USER = 0b10000;
        constexpr u8 SUPERVISOR = 0b10011;
        constexpr u8 ABORT = 0b10111;
        constexpr u8 UNDEFINED = 0b11011;
        constexpr u8 FIQ = 0b10001;
        constexpr u8 IRQ = 0b10010;
        constexpr u8 SYSTEM = 0b11111;
    }

    namespace implementor {
        /* A */ constexpr u8 ARM = 0x41;
        /* B */ constexpr u8 BRCM = 0x42;
        /* L */ constexpr u8 LLARM = 0x4C; // custom
        /* D */ constexpr u8 DEC = 0x44;
        /* M */ constexpr u8 MOTOROLA = 0x4D;
        /* Q */ constexpr u8 QUALCOMM = 0x51;
        /* V */ constexpr u8 MARVELL = 0x56;
        /* i */ constexpr u8 INTEL = 0x69;
        /* C */ constexpr u8 CAVIUM = 0x43;
        /* F */ constexpr u8 FUJITSU = 0x46;
        /* I */ constexpr u8 INFINEON = 0x49;
        /* N */ constexpr u8 NVIDIA = 0x4e;
        /* P */ constexpr u8 APM = 0x50;
        /* S */ constexpr u8 SAMSUNG = 0x53;
        /* T */ constexpr u8 TI = 0x54;
        /* a */ constexpr u8 APPLE = 0x61;
        /* f */ constexpr u8 FARADAY = 0x66;
        /* À */ constexpr u8 AMPERE = 0xc0;
    }

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
}