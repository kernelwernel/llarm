#pragma once

#include "../../id.hpp"
#include "../../utility.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"


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
        static constexpr u64 low_half = 0x00000000FFFFFFFF;
        static constexpr u64 high_half = 0xFFFFFFFF00000000;

        auto low = [=](u64 &vfp_reg) {
            vfp_reg = (vfp_reg & high_half) | value;
        };

        auto high = [=](u64 &vfp_reg) {
            vfp_reg = (vfp_reg & low_half) | value;
        };

        switch (vfp_reg_id) {
            case id::vfp_reg::S0: low(D0); return;
            case id::vfp_reg::S2: low(D1); return;
            case id::vfp_reg::S4: low(D2); return;
            case id::vfp_reg::S6: low(D3); return;
            case id::vfp_reg::S8: low(D4); return;
            case id::vfp_reg::S10: low(D5); return;
            case id::vfp_reg::S12: low(D6); return;
            case id::vfp_reg::S14: low(D7); return;
            case id::vfp_reg::S16: low(D8); return;
            case id::vfp_reg::S18: low(D9); return;
            case id::vfp_reg::S20: low(D10); return;
            case id::vfp_reg::S22: low(D11); return;
            case id::vfp_reg::S24: low(D12); return;
            case id::vfp_reg::S26: low(D13); return;
            case id::vfp_reg::S28: low(D14); return;
            case id::vfp_reg::S30: low(D15); return;
            case id::vfp_reg::S1: high(D0); return;
            case id::vfp_reg::S3: high(D1); return;
            case id::vfp_reg::S5: high(D2); return;
            case id::vfp_reg::S7: high(D3); return;
            case id::vfp_reg::S9: high(D4); return;
            case id::vfp_reg::S11: high(D5); return;
            case id::vfp_reg::S13: high(D6); return;
            case id::vfp_reg::S15: high(D7); return;
            case id::vfp_reg::S17: high(D8); return;
            case id::vfp_reg::S19: high(D9); return;
            case id::vfp_reg::S21: high(D10); return;
            case id::vfp_reg::S23: high(D11); return;
            case id::vfp_reg::S25: high(D12); return;
            case id::vfp_reg::S27: high(D13); return;
            case id::vfp_reg::S29: high(D14); return;
            case id::vfp_reg::S31: high(D15); return;
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
            case id::vfp_reg::FPSID: FPSID = static_cast<u32>(value); return;
            case id::vfp_reg::FPSID_IMPLEMENTOR:
            case id::vfp_reg::FPSID_SW: util::modify_bit(FPSID, 23, value); return;
            case id::vfp_reg::FPSID_FORMAT:
            case id::vfp_reg::FPSID_SNG: util::modify_bit(FPSID, 20, value); return;
            case id::vfp_reg::FPSID_ARCH:
            case id::vfp_reg::FPSID_PART_NUM:
            case id::vfp_reg::FPSID_VARIANT:
            case id::vfp_reg::FPSID_REVISION:
            case id::vfp_reg::FPSCR: FPSCR = static_cast<u32>(value); return;
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
            case id::vfp_reg::FPEXC: FPEXC = static_cast<u32>(value); return;
            case id::vfp_reg::FPEXC_EX: util::modify_bit(FPEXC, 31, value); return;
            case id::vfp_reg::FPEXC_EN: util::modify_bit(FPEXC, 30, value); return;
        }
    }

    u64 read(const id::vfp_reg vfp_reg_id) {
        static constexpr u64 lower_mask_64 = 0x00000000FFFFFFFF;
        static constexpr u64 upper_mask_64 = 0xFFFFFFFF00000000;

        switch (vfp_reg_id) {
            case id::vfp_reg::S1: return ((D0 & upper_mask_64) >> 31);
            case id::vfp_reg::S3: return ((D1 & upper_mask_64) >> 31);
            case id::vfp_reg::S5: return ((D2 & upper_mask_64) >> 31);
            case id::vfp_reg::S7: return ((D3 & upper_mask_64) >> 31); 
            case id::vfp_reg::S9: return ((D4 & upper_mask_64) >> 31); 
            case id::vfp_reg::S11: return ((D5 & upper_mask_64) >> 31); 
            case id::vfp_reg::S13: return ((D6 & upper_mask_64) >> 31);
            case id::vfp_reg::S15: return ((D7 & upper_mask_64) >> 31);
            case id::vfp_reg::S17: return ((D8 & upper_mask_64) >> 31);
            case id::vfp_reg::S19: return ((D9 & upper_mask_64) >> 31);
            case id::vfp_reg::S21: return ((D10 & upper_mask_64) >> 31);
            case id::vfp_reg::S23: return ((D11 & upper_mask_64) >> 31);
            case id::vfp_reg::S25: return ((D12 & upper_mask_64) >> 31);
            case id::vfp_reg::S27: return ((D13 & upper_mask_64) >> 31);
            case id::vfp_reg::S29: return ((D14 & upper_mask_64) >> 31);
            case id::vfp_reg::S31: return ((D15 & upper_mask_64) >> 31);
            case id::vfp_reg::S0: return (D0 & lower_mask_64);
            case id::vfp_reg::S2: return (D1 & lower_mask_64);
            case id::vfp_reg::S4: return (D2 & lower_mask_64);
            case id::vfp_reg::S6: return (D3 & lower_mask_64);
            case id::vfp_reg::S8: return (D4 & lower_mask_64);
            case id::vfp_reg::S10: return (D5 & lower_mask_64);
            case id::vfp_reg::S12: return (D6 & lower_mask_64);
            case id::vfp_reg::S14: return (D7 & lower_mask_64);
            case id::vfp_reg::S16: return (D8 & lower_mask_64);
            case id::vfp_reg::S18: return (D9 & lower_mask_64);
            case id::vfp_reg::S20: return (D10 & lower_mask_64);
            case id::vfp_reg::S22: return (D11 & lower_mask_64);
            case id::vfp_reg::S24: return (D12 & lower_mask_64);
            case id::vfp_reg::S26: return (D13 & lower_mask_64);
            case id::vfp_reg::S28: return (D14 & lower_mask_64);
            case id::vfp_reg::S30: return (D15 & lower_mask_64);
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
            case id::vfp_reg::FPSID_IMPLEMENTOR: return shared::util::bit_range(FPSID, 24, 31);
            case id::vfp_reg::FPSID_SW: return shared::util::bit_fetch(FPSID, 23);
            case id::vfp_reg::FPSID_FORMAT: return shared::util::bit_range(FPSID, 21, 22);
            case id::vfp_reg::FPSID_SNG: return shared::util::bit_fetch(FPSID, 20);
            case id::vfp_reg::FPSID_ARCH: return shared::util::bit_range(FPSID, 16, 19);
            case id::vfp_reg::FPSID_PART_NUM: return shared::util::bit_range(FPSID, 8, 15);
            case id::vfp_reg::FPSID_VARIANT: return shared::util::bit_range(FPSID, 4, 7);
            case id::vfp_reg::FPSID_REVISION: return shared::util::bit_range(FPSID, 0, 3);
            case id::vfp_reg::FPSCR: return FPSCR;
            case id::vfp_reg::FPSCR_N: return shared::util::bit_fetch(FPSCR, 31);
            case id::vfp_reg::FPSCR_Z: return shared::util::bit_fetch(FPSCR, 30);
            case id::vfp_reg::FPSCR_C: return shared::util::bit_fetch(FPSCR, 29);
            case id::vfp_reg::FPSCR_V: return shared::util::bit_fetch(FPSCR, 28);
            case id::vfp_reg::FPSCR_FZ: return shared::util::bit_fetch(FPSCR, 24);
            case id::vfp_reg::FPSCR_RMODE: return shared::util::bit_range(FPSCR, 22, 23);
            case id::vfp_reg::FPSCR_STRIDE: return shared::util::bit_range(FPSCR, 20, 21);
            case id::vfp_reg::FPSCR_LEN: return shared::util::bit_range(FPSCR, 16, 18);
            case id::vfp_reg::FPSCR_IXE: return shared::util::bit_fetch(FPSCR, 12);
            case id::vfp_reg::FPSCR_UFE: return shared::util::bit_fetch(FPSCR, 11);
            case id::vfp_reg::FPSCR_OFE: return shared::util::bit_fetch(FPSCR, 10);
            case id::vfp_reg::FPSCR_DZE: return shared::util::bit_fetch(FPSCR, 9);
            case id::vfp_reg::FPSCR_IOE: return shared::util::bit_fetch(FPSCR, 8);
            case id::vfp_reg::FPSCR_IXC: return shared::util::bit_fetch(FPSCR, 4);
            case id::vfp_reg::FPSCR_UFC: return shared::util::bit_fetch(FPSCR, 3);
            case id::vfp_reg::FPSCR_OFC: return shared::util::bit_fetch(FPSCR, 2);
            case id::vfp_reg::FPSCR_DZC: return shared::util::bit_fetch(FPSCR, 1);
            case id::vfp_reg::FPSCR_IOC: return (FPSCR & 1);
            case id::vfp_reg::FPEXC: return FPEXC;
            case id::vfp_reg::FPEXC_EX: return shared::util::bit_fetch(FPEXC, 31);
            case id::vfp_reg::FPEXC_EN: return shared::util::bit_fetch(FPEXC, 30);
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