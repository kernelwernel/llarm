#pragma once

#include "registers.hpp" // vfp regs
#include "../core/registers.hpp" // traditional regs

#include <vector>

#include <llarm/shared/types.hpp>

struct single_reg_struct {
    id::vfp_reg Sd_id;
    id::vfp_reg Sn_id;
    id::vfp_reg Sm_id;
};

struct double_reg_struct {
    id::vfp_reg Dd_id;
    id::vfp_reg Dn_id;
    id::vfp_reg Dm_id;
};

struct single_encoding_struct {
    u8 vec_len;
    std::vector<single_reg_struct> vec_regs;
};

struct double_encoding_struct {
    u8 vec_len;
    std::vector<double_reg_struct> vec_regs;
};

struct vfp_address_struct {
    u32 start;
    u32 end;
};


struct VFP_ADDRESS_MODE {
private:
    SETTINGS& settings;
    REGISTERS& reg;
    VFP_REG& vfp_reg;

public:
    single_encoding_struct single_precision(const u32 code);
    single_encoding_struct single_precision_monadic(const u32 code);
    double_encoding_struct double_precision(const u32 code);
    double_encoding_struct double_precision_monadic(const u32 code);
    vfp_address_struct vfp_load_multiple(const u32 code);

public:
    VFP_ADDRESS_MODE(SETTINGS& settings, REGISTERS& reg, VFP_REG& vfp_reg) : settings(settings), reg(reg), vfp_reg(vfp_reg) {

    }
};