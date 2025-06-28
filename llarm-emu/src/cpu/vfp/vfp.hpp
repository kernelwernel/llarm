#pragma once

#include "../../id.hpp"
#include "../../utility.hpp"

#include "registers.hpp"
#include "exception.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"


struct VFP {
private:
    VFP_REG& vfp_reg;
    VFP_EXCEPTION& vfp_exception;

public:
    VFP(
        VFP_REG& vfp_reg, 
        VFP_EXCEPTION& vfp_exception
    ) : vfp_reg(vfp_reg),
        vfp_exception(vfp_exception)
    {

    }
};