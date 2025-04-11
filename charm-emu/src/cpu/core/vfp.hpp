#pragma once

#include "shared/types.hpp"
#include "../../id.hpp"
#include "../../utility.hpp"
#include "registers.hpp"

struct VFP {
private:
    //REGISTERS& reg;

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
    void write(const id::vfp_reg vfp_reg_id, const u64 value) {
        switch (vfp_reg_id) {
            case id::vfp_reg::S0: 
            case id::vfp_reg::S1: 
            case id::vfp_reg::S2: 
            case id::vfp_reg::S3: 
            case id::vfp_reg::S4: 
            case id::vfp_reg::S5: 
            case id::vfp_reg::S6: 
            case id::vfp_reg::S7: 
            case id::vfp_reg::S8: 
            case id::vfp_reg::S9: 
            case id::vfp_reg::S10: 
            case id::vfp_reg::S11: 
            case id::vfp_reg::S12: 
            case id::vfp_reg::S13: 
            case id::vfp_reg::S14: 
            case id::vfp_reg::S15: 
            case id::vfp_reg::S16: 
            case id::vfp_reg::S17: 
            case id::vfp_reg::S18: 
            case id::vfp_reg::S19: 
            case id::vfp_reg::S20: 
            case id::vfp_reg::S21: 
            case id::vfp_reg::S22: 
            case id::vfp_reg::S23: 
            case id::vfp_reg::S24: 
            case id::vfp_reg::S25: 
            case id::vfp_reg::S26: 
            case id::vfp_reg::S27: 
            case id::vfp_reg::S28: 
            case id::vfp_reg::S29: 
            case id::vfp_reg::S30: 
            case id::vfp_reg::S31: 
            case id::vfp_reg::D0: D0 = value; return; 
            case id::vfp_reg::D1: D1 = value; return; 
            case id::vfp_reg::D2: D2 = value; return; 
            case id::vfp_reg::D3: D3 = value; return; 
            case id::vfp_reg::D4: D4 = value; return; 
            case id::vfp_reg::D5: D5 = value; return; 
            case id::vfp_reg::D6: D6 = value; return; 
            case id::vfp_reg::D7: D7 = value; return; 
            case id::vfp_reg::D8: D8 = value; return; 
            case id::vfp_reg::D9: D9 = value; return; 
            case id::vfp_reg::D10: D10 = value; return; 
            case id::vfp_reg::D11: D11 = value; return; 
            case id::vfp_reg::D12: D12 = value; return; 
            case id::vfp_reg::D13: D13 = value; return; 
            case id::vfp_reg::D14: D14 = value; return; 
            case id::vfp_reg::D15: D15 = value; return; 
            case id::vfp_reg::FPSID: FPSID = (value & util::lower_mask_64); return;
            case id::vfp_reg::FPSID_IMPLEMENTOR:
            case id::vfp_reg::FPSID_SW: util::modify_bit(FPSID, 23, value); return;
            case id::vfp_reg::FPSID_FORMAT:
            case id::vfp_reg::FPSID_SNG: util::modify_bit(FPSID, 20, value); return;
            case id::vfp_reg::FPSID_ARCH:
            case id::vfp_reg::FPSID_PART_NUM:
            case id::vfp_reg::FPSID_VARIANT:
            case id::vfp_reg::FPSID_REVISION:
            case id::vfp_reg::FPSCR: FPSCR = (value & util::lower_mask_64); return;
            case id::vfp_reg::FPSCR_N: util::modify_bit(FPSCR, 31, value); return;
            case id::vfp_reg::FPSCR_Z: util::modify_bit(FPSCR, 30, value); return;
            case id::vfp_reg::FPSCR_C: util::modify_bit(FPSCR, 29, value); return;
            case id::vfp_reg::FPSCR_V: util::modify_bit(FPSCR, 28, value); return;
            case id::vfp_reg::FPSCR_FZ:
            case id::vfp_reg::FPSCR_RMODE:
            case id::vfp_reg::FPSCR_STRIDE:
            case id::vfp_reg::FPSCR_LEN:
            case id::vfp_reg::FPSCR_IXE: util::modify_bit(FPSCR, 12, value); return;
            case id::vfp_reg::FPSCR_UFE: util::modify_bit(FPSCR, 11, value); return;
            case id::vfp_reg::FPSCR_OFE: util::modify_bit(FPSCR, 10, value); return;
            case id::vfp_reg::FPSCR_DZE: util::modify_bit(FPSCR, 9, value); return;
            case id::vfp_reg::FPSCR_IOE: util::modify_bit(FPSCR, 8, value); return;
            case id::vfp_reg::FPSCR_IXC: util::modify_bit(FPSCR, 4, value); return;
            case id::vfp_reg::FPSCR_UFC: util::modify_bit(FPSCR, 3, value); return;
            case id::vfp_reg::FPSCR_OFC: util::modify_bit(FPSCR, 2, value); return;
            case id::vfp_reg::FPSCR_DZC: util::modify_bit(FPSCR, 1, value); return;
            case id::vfp_reg::FPSCR_IOC: util::modify_bit(FPSCR, 0, value); return;
            case id::vfp_reg::FPEXC: FPEXC = (value & util::lower_mask_64); return;
            case id::vfp_reg::FPEXC_EX: util::modify_bit(FPEXC, 31, value); return;
            case id::vfp_reg::FPEXC_EN: util::modify_bit(FPEXC, 30, value); return;
        }
    }

    u64 read(const id::vfp_reg vfp_reg_id) {
        switch (vfp_reg_id) {
            case id::vfp_reg::S0: return (D0 & util::lower_mask_64);
            case id::vfp_reg::S1: return ((D0 & util::upper_mask_64) >> 31);
            case id::vfp_reg::S2: return (D1 & util::lower_mask_64);
            case id::vfp_reg::S3: return ((D1 & util::upper_mask_64) >> 31);
            case id::vfp_reg::S4: return (D2 & util::lower_mask_64);
            case id::vfp_reg::S5: return ((D2 & util::upper_mask_64) >> 31);
            case id::vfp_reg::S6: return (D3 & util::lower_mask_64);
            case id::vfp_reg::S7: return ((D3 & util::upper_mask_64) >> 31); 
            case id::vfp_reg::S8: return (D4 & util::lower_mask_64);
            case id::vfp_reg::S9: return ((D4 & util::upper_mask_64) >> 31); 
            case id::vfp_reg::S10: return (D5 & util::lower_mask_64);
            case id::vfp_reg::S11: return ((D5 & util::upper_mask_64) >> 31); 
            case id::vfp_reg::S12: return (D6 & util::lower_mask_64);
            case id::vfp_reg::S13: return ((D6 & util::upper_mask_64) >> 31);
            case id::vfp_reg::S14: return (D7 & util::lower_mask_64);
            case id::vfp_reg::S15: return ((D7 & util::upper_mask_64) >> 31);
            case id::vfp_reg::S16: return (D8 & util::lower_mask_64);
            case id::vfp_reg::S17: return ((D8 & util::upper_mask_64) >> 31);
            case id::vfp_reg::S18: return (D9 & util::lower_mask_64);
            case id::vfp_reg::S19: return ((D9 & util::upper_mask_64) >> 31);
            case id::vfp_reg::S20: return (D10 & util::lower_mask_64);
            case id::vfp_reg::S21: return ((D10 & util::upper_mask_64) >> 31);
            case id::vfp_reg::S22: return (D11 & util::lower_mask_64);
            case id::vfp_reg::S23: return ((D11 & util::upper_mask_64) >> 31);
            case id::vfp_reg::S24: return (D12 & util::lower_mask_64);
            case id::vfp_reg::S25: return ((D12 & util::upper_mask_64) >> 31);
            case id::vfp_reg::S26: return (D13 & util::lower_mask_64);
            case id::vfp_reg::S27: return ((D13 & util::upper_mask_64) >> 31);
            case id::vfp_reg::S28: return (D14 & util::lower_mask_64);
            case id::vfp_reg::S29: return ((D14 & util::upper_mask_64) >> 31);
            case id::vfp_reg::S30: return (D15 & util::lower_mask_64);
            case id::vfp_reg::S31: return ((D15 & util::upper_mask_64) >> 31);
            case id::vfp_reg::D0: return D0;
            case id::vfp_reg::D1: return D1;
            case id::vfp_reg::D2: return D2;
            case id::vfp_reg::D3: return D3;
            case id::vfp_reg::D4: return D4;
            case id::vfp_reg::D5: return D5;
            case id::vfp_reg::D6: return D6;
            case id::vfp_reg::D7: return D7;
            case id::vfp_reg::D8: return D8;
            case id::vfp_reg::D9: return D9;
            case id::vfp_reg::D10: return D10;
            case id::vfp_reg::D11: return D11; 
            case id::vfp_reg::D12: return D12; 
            case id::vfp_reg::D13: return D13; 
            case id::vfp_reg::D14: return D14;
            case id::vfp_reg::D15: return D15;
            case id::vfp_reg::FPSID: return FPSID;
            case id::vfp_reg::FPSID_IMPLEMENTOR: return util::bit_fetcher(FPSID, 24, 31);
            case id::vfp_reg::FPSID_SW: return (FPSID & (1 << 23));
            case id::vfp_reg::FPSID_FORMAT: return util::bit_fetcher(FPSID, 21, 22);
            case id::vfp_reg::FPSID_SNG: return (FPSID & (1 << 20));
            case id::vfp_reg::FPSID_ARCH: return util::bit_fetcher(FPSID, 16, 19);
            case id::vfp_reg::FPSID_PART_NUM: return util::bit_fetcher(FPSID, 8, 15);
            case id::vfp_reg::FPSID_VARIANT: return util::bit_fetcher(FPSID, 4, 7);
            case id::vfp_reg::FPSID_REVISION: return util::bit_fetcher(FPSID, 0, 3);
            case id::vfp_reg::FPSCR: return FPSCR;
            case id::vfp_reg::FPSCR_N: return (FPSCR & (1 << 31));
            case id::vfp_reg::FPSCR_Z: return (FPSCR & (1 << 30));
            case id::vfp_reg::FPSCR_C: return (FPSCR & (1 << 29));
            case id::vfp_reg::FPSCR_V: return (FPSCR & (1 << 28));
            case id::vfp_reg::FPSCR_FZ: return (FPSCR & (1 << 24));
            case id::vfp_reg::FPSCR_RMODE: return util::bit_fetcher(FPSCR, 22, 23);
            case id::vfp_reg::FPSCR_STRIDE: return util::bit_fetcher(FPSCR, 20, 21);
            case id::vfp_reg::FPSCR_LEN: return util::bit_fetcher(FPSCR, 16, 18);
            case id::vfp_reg::FPSCR_IXE: return (FPSCR & (1 << 12));
            case id::vfp_reg::FPSCR_UFE: return (FPSCR & (1 << 11));
            case id::vfp_reg::FPSCR_OFE: return (FPSCR & (1 << 10));
            case id::vfp_reg::FPSCR_DZE: return (FPSCR & (1 << 9));
            case id::vfp_reg::FPSCR_IOE: return (FPSCR & (1 << 8));
            case id::vfp_reg::FPSCR_IXC: return (FPSCR & (1 << 4));
            case id::vfp_reg::FPSCR_UFC: return (FPSCR & (1 << 3));
            case id::vfp_reg::FPSCR_OFC: return (FPSCR & (1 << 2));
            case id::vfp_reg::FPSCR_DZC: return (FPSCR & (1 << 1));
            case id::vfp_reg::FPSCR_IOC: return (FPSCR & 1);
            case id::vfp_reg::FPEXC: return FPEXC;
            case id::vfp_reg::FPEXC_EX: return (FPEXC & (1 << 31));
            case id::vfp_reg::FPEXC_EN: return (FPEXC & (1 << 30));
        }
    }


    void invalid_operation() {}
    void div_by_zero() {}
    void overflow() {}
    void underflow() {}
    void inexact() {}

    VFP (/*const REGISTERS& reg*/) /* : reg(reg)*/ {

    }
};