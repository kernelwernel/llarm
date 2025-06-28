#pragma once

#include "../../id.hpp"
#include "../../utility.hpp"
#include "../../settings.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"


struct VFP_REG {
private:
    SETTINGS& settings;

private:
    // maybe i could do something hacky with unions here, but whatever
    u64 D0; // S0 and S1
    u64 D1; // S2 and S3
    u64 D2; // S4 and S5
    u64 D3; // S6 and S7
    u64 D4; // S8 and S9
    u64 D5; // S10 and S11
    u64 D6; // S12 and S13
    u64 D7; // S14 and S15
    u64 D8; // S16 and S17
    u64 D9; // S18 and S19
    u64 D10; // S20 and S21
    u64 D11; // S22 and S23 
    u64 D12; // S24 and S25
    u64 D13; // S26 and S27
    u64 D14; // S28 and S29
    u64 D15; // S30 and S31

    u32 FPSID;
    u32 FPSCR;
    u32 FPEXC;

public:
    void write(const id::vfp_reg vfp_reg_id, const u64 value);

    u64 read(const id::vfp_reg vfp_reg_id);

    void reset() {
        write(id::vfp_reg::FPEXC_EN, false);
        D0 = 0;
        D1 = 0;
        D2 = 0;
        D3 = 0;
        D4 = 0;
        D5 = 0;
        D6 = 0;
        D7 = 0;
        D8 = 0;
        D9 = 0;
        D10 = 0;
        D11 = 0;
        D12 = 0;
        D13 = 0;
        D14 = 0;
        D15 = 0;
    }

    void setup();

    VFP_REG(SETTINGS& settings) : settings(settings) {

    }
};