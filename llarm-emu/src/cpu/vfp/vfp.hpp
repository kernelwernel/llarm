#pragma once

#include "../../id.hpp"

#include "registers.hpp"
#include "exception.hpp"

#include "shared/types.hpp"


struct VFP {
private:
    VFP_REG& vfp_reg;
    VFP_EXCEPTION& vfp_exception;

public:
    // these may not be needed, delete later if appropriate
    //
    //void write(const id::vfp_reg vfp_reg_id, const u64 value) {
    //    vfp_reg.write(vfp_reg_id, value);
    //}
//
    //u64 read(const id::vfp_reg vfp_reg_id) {
    //    return vfp_reg.read(vfp_reg_id);
    //}


    VFP(
        VFP_REG& vfp_reg, 
        VFP_EXCEPTION& vfp_exception
    ) : vfp_reg(vfp_reg),
        vfp_exception(vfp_exception)
    {

    }
};