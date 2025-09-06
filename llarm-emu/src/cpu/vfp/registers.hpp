#pragma once

#include "../../id.hpp"
#include "../../settings.hpp"

#include "shared/types.hpp"


struct VFP_REG {
private:
    SETTINGS& settings;

private:
    // maybe i could do something hacky with unions here, but whatever
    u64 D0 = 0; // S0 and S1
    u64 D1 = 0; // S2 and S3
    u64 D2 = 0; // S4 and S5
    u64 D3 = 0; // S6 and S7
    u64 D4 = 0; // S8 and S9
    u64 D5 = 0; // S10 and S11
    u64 D6 = 0; // S12 and S13
    u64 D7 = 0; // S14 and S15
    u64 D8 = 0; // S16 and S17
    u64 D9 = 0; // S18 and S19
    u64 D10 = 0; // S20 and S21
    u64 D11 = 0; // S22 and S23 
    u64 D12 = 0; // S24 and S25
    u64 D13 = 0; // S26 and S27
    u64 D14 = 0; // S28 and S29
    u64 D15 = 0; // S30 and S31

    u32 FPSID = 0;
    u32 FPSCR = 0;
    u32 FPEXC = 0;

public:
    void write(const id::vfp_reg vfp_reg_id, const u64 value);
    void write_single(const u32 code, const u8 start, const u8 end, const u64 value, const u8 bottom_bit);
    void write_double(const u32 code, const u8 start, const u8 end, const u64 value);
    u64 read(const id::vfp_reg vfp_reg_id);
    u32 read_single(const u32 code, const u8 start, const u8 end, const u8 bottom_bit);
    u64 read_double(const u32 code, const u8 start, const u8 end);
    double read_double_IEEE(const u32 code, const u8 start, const u8 end);
    float read_single_IEEE(const u32 code, const u8 start, const u8 end, const u8 bottom_bit);
    double read_double_IEEE(const id::vfp_reg vfp_reg_id);
    float read_single_IEEE(const id::vfp_reg vfp_reg_id);

    id::vfp_reg fetch_single_reg_id(const u8 reg_bits);
    id::vfp_reg fetch_double_reg_id(const u8 reg_bits);
    id::vfp_reg fetch_single_reg_id(const u32 code, const u8 start, const u8 end);
    id::vfp_reg fetch_double_reg_id(const u32 code, const u8 start, const u8 end);

    bool is_single_nan(const u32 code, const u8 start, const u8 end, const u8 bottom_bit);
    bool is_double_nan(const u32 code, const u8 start, const u8 end);

    u8 fetch_vec_len();

    void reset();

    void setup();

    VFP_REG(SETTINGS& settings) : settings(settings) {

    }
};