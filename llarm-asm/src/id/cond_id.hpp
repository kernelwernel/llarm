#pragma once

#include "shared/types.hpp"

enum class cond_id : u8 {
    UNKNOWN,
    NONE,
    EQ, 
    NE, 
    CS, 
    HS, 
    CC, 
    LO, 
    MI, 
    PL, 
    VS, 
    VC, 
    HI, 
    LS, 
    GE, 
    LT, 
    GT, 
    LE, 
    AL
};