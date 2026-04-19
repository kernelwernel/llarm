#pragma once

#include "registers.hpp"

struct VFP_EXCEPTION {

    VFP_REG& vfp_reg;


    void invalid_operation();
    void div_by_zero();
    void overflow();
    void underflow();
    void inexact();

    VFP_EXCEPTION(VFP_REG& vfp_reg) : vfp_reg(vfp_reg) {

    }
};