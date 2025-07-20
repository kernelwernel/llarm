#include "../../id.hpp"
#include "../../utility.hpp"

#include "registers.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"
#include "shared/out.hpp"

#include <cstring>

void VFP_REG::write(const id::vfp_reg vfp_reg_id, const u64 value) {
    static constexpr u64 low_half = 0x00000000FFFFFFFF;
    static constexpr u64 high_half = 0xFFFFFFFF00000000;

    auto low = [=](u64 &vfp_reg) {
        vfp_reg = (vfp_reg & high_half) | value;
    };

    auto high = [=](u64 &vfp_reg) {
        vfp_reg = (vfp_reg & low_half) | value;
    };

    switch (vfp_reg_id) {
        case id::vfp_reg::UNKNOWN: shared::out::dev_error("Unknown VFP register id provided for write operation");
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
        case id::vfp_reg::FPSID_IMPLEMENTOR: util::swap_bits(FPSID, 24, 31, value); return;
        case id::vfp_reg::FPSID_SW: util::modify_bit(FPSID, 23, value); return;
        case id::vfp_reg::FPSID_FORMAT: util::swap_bits(FPSID, 21, 22, value); return;
        case id::vfp_reg::FPSID_SNG: util::modify_bit(FPSID, 20, value); return;
        case id::vfp_reg::FPSID_ARCH: util::swap_bits(FPSID, 16, 19, value); return;
        case id::vfp_reg::FPSID_PART_NUM: util::swap_bits(FPSID, 8, 15, value); return;
        case id::vfp_reg::FPSID_VARIANT: util::swap_bits(FPSID, 4, 7, value); return;
        case id::vfp_reg::FPSID_REVISION: util::swap_bits(FPSID, 0, 3, value); return;
        case id::vfp_reg::FPSCR: FPSCR = static_cast<u32>(value); return;
        case id::vfp_reg::FPSCR_N: util::modify_bit(FPSCR, 31, value); return;
        case id::vfp_reg::FPSCR_Z: util::modify_bit(FPSCR, 30, value); return;
        case id::vfp_reg::FPSCR_C: util::modify_bit(FPSCR, 29, value); return;
        case id::vfp_reg::FPSCR_V: util::modify_bit(FPSCR, 28, value); return;
        case id::vfp_reg::FPSCR_FZ: util::modify_bit(FPSCR, 24, value); return;
        case id::vfp_reg::FPSCR_RMODE: util::swap_bits(FPSID, 22, 23, value); return;
        case id::vfp_reg::FPSCR_STRIDE: util::swap_bits(FPSID, 20, 21, value); return;
        case id::vfp_reg::FPSCR_LEN: util::swap_bits(FPSID, 16, 18, value); return;
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


u64 VFP_REG::read(const id::vfp_reg vfp_reg_id) {
    static constexpr u64 lower_mask_64 = 0x00000000FFFFFFFF;
    static constexpr u64 upper_mask_64 = 0xFFFFFFFF00000000;

    switch (vfp_reg_id) {
        case id::vfp_reg::UNKNOWN: shared::out::dev_error("Unknown VFP register id provided for read operation");
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


void VFP_REG::write_double(const u32 code, const u8 start, const u8 end, const u64 value) {
    const u8 reg_bits = shared::util::bit_range(code, start, end);
    const id::vfp_reg id = fetch_double_reg_id(reg_bits);
    write(id, value);
}


void VFP_REG::write_single(const u32 code, const u8 start, const u8 end, const u64 value, const u8 bottom_bit) {
    const bool bottom = shared::util::bit_fetch(code, bottom_bit);
    const u8 reg_bits = (shared::util::bit_range(code, start, end) << 1) | bottom;

    const id::vfp_reg id = fetch_single_reg_id(reg_bits);
    write(id, value);
}


u64 VFP_REG::read_double(const u32 code, const u8 start, const u8 end) {
    const u8 reg_bits = shared::util::bit_range(code, start, end);
    const id::vfp_reg id = fetch_double_reg_id(reg_bits);
    return read(id);
}

double VFP_REG::read_double_IEEE(const u32 code, const u8 start, const u8 end) {
    const u64 raw_bytes = read_double(code, start, end);
    double d;

    std::memcpy(&d, &raw_bytes, sizeof(d));

    return d;
}


u32 VFP_REG::read_single(const u32 code, const u8 start, const u8 end, const u8 bottom_bit) {
    const bool bottom = shared::util::bit_fetch(code, bottom_bit);
    const u8 reg_bits = (shared::util::bit_range(code, start, end) << 1) | bottom;
    
    const id::vfp_reg id = fetch_single_reg_id(reg_bits);
    return static_cast<u32>(read(id));
}


float VFP_REG::read_single_IEEE(const u32 code, const u8 start, const u8 end, const u8 bottom_bit) {
    const u32 raw_bytes = read_single(code, start, end, bottom_bit);
    float f;

    std::memcpy(&f, &raw_bytes, sizeof(f));

    return f;
}


void VFP_REG::setup() {
    write(id::vfp_reg::FPEXC_EN, true);
    write(id::vfp_reg::FPEXC_EX, false);

    write(id::vfp_reg::FPSCR, 0);

    write(id::vfp_reg::FPSID_IMPLEMENTOR, settings.custom_implementor_char);
    write(id::vfp_reg::FPSID_SW, false);

    u8 format = 0;

    switch (settings.vfp_format) {
        case id::vfp_format::NON_STANDARD: format = 0b11; break;
        case id::vfp_format::FORMAT_1: format = 0b00; break;
        case id::vfp_format::FORMAT_2: format = 0b01; break;
    }

    write(id::vfp_reg::FPSID_FORMAT, format);

    const bool double_support = settings.is_vfp_double_precision_enabled;
    const bool single_support = settings.is_vfp_single_precision_enabled;

    if (double_support && single_support) {
        write(id::vfp_reg::FPSID_SNG, false);
    } else if (single_support && (double_support == false)) {
        write(id::vfp_reg::FPSID_SNG, true);
    }

    u8 arch_version = 0;

    switch (settings.vfp_version) {
        case id::vfp_version::UNKNOWN: shared::out::dev_error("Unknown VFP arch version supplied");
        case id::vfp_version::VFPv1: arch_version = 0b0000; break;
        case id::vfp_version::VFPv2: arch_version = 0b0001; break;
        case id::vfp_version::VFPv3: arch_version = 0b0010; break; // i'm not exactly sure about this one, TODO
        case id::vfp_version::VFPv3_D16: // TODO
        case id::vfp_version::VFPv3_F16: // TODO
        case id::vfp_version::VFPv4: // TODO
        case id::vfp_version::VFPv4_D16: // TODO
        case id::vfp_version::VFPv5_D16_M: break; // (temporary) TODO
    }

    write(id::vfp_reg::FPSID_ARCH, arch_version);

    write(id::vfp_reg::FPSID_PART_NUM, settings.vfp_ppn);
    write(id::vfp_reg::FPSID_VARIANT, settings.vfp_variant);
    write(id::vfp_reg::FPSID_REVISION, settings.vfp_revision);
}


id::vfp_reg VFP_REG::fetch_single_reg_id(const u8 reg_bits) {
    switch (reg_bits) {
        case 0: return id::vfp_reg::S0;
        case 1: return id::vfp_reg::S1;
        case 2: return id::vfp_reg::S2;
        case 3: return id::vfp_reg::S3;
        case 4: return id::vfp_reg::S4;
        case 5: return id::vfp_reg::S5;
        case 6: return id::vfp_reg::S6;
        case 7: return id::vfp_reg::S7;
        case 8: return id::vfp_reg::S8;
        case 9: return id::vfp_reg::S9;
        case 10: return id::vfp_reg::S10;
        case 11: return id::vfp_reg::S11; 
        case 12: return id::vfp_reg::S12; 
        case 13: return id::vfp_reg::S13; 
        case 14: return id::vfp_reg::S14;
        case 15: return id::vfp_reg::S15;
        case 16: return id::vfp_reg::S16; 
        case 17: return id::vfp_reg::S17; 
        case 18: return id::vfp_reg::S18; 
        case 19: return id::vfp_reg::S19;
        case 20: return id::vfp_reg::S20;
        case 21: return id::vfp_reg::S21;
        case 22: return id::vfp_reg::S22;
        case 23: return id::vfp_reg::S23;
        case 24: return id::vfp_reg::S24;
        case 25: return id::vfp_reg::S25;
        case 26: return id::vfp_reg::S26;
        case 27: return id::vfp_reg::S27;
        case 28: return id::vfp_reg::S28;
        case 29: return id::vfp_reg::S29;
        case 30: return id::vfp_reg::S30;
        case 31: return id::vfp_reg::S31;
        default: shared::out::dev_error("Impossible argument for single_reg_id");
    }
}


id::vfp_reg VFP_REG::fetch_double_reg_id(const u8 reg_bits) {
    switch (reg_bits) {
        case 0: return id::vfp_reg::D0;
        case 1: return id::vfp_reg::D1;
        case 2: return id::vfp_reg::D2;
        case 3: return id::vfp_reg::D3;
        case 4: return id::vfp_reg::D4;
        case 5: return id::vfp_reg::D5;
        case 6: return id::vfp_reg::D6;
        case 7: return id::vfp_reg::D7;
        case 8: return id::vfp_reg::D8;
        case 9: return id::vfp_reg::D9;
        case 10: return id::vfp_reg::D10;
        case 11: return id::vfp_reg::D11; 
        case 12: return id::vfp_reg::D12; 
        case 13: return id::vfp_reg::D13; 
        case 14: return id::vfp_reg::D14;
        case 15: return id::vfp_reg::D15;
        default: shared::out::dev_error("Impossible argument for double_reg_id");
    }
}


id::vfp_reg VFP_REG::fetch_single_reg_id(const u32 code, const u8 start, const u8 end) {
    const u8 reg_bits = shared::util::bit_range(code, start, end);
    return fetch_single_reg_id(reg_bits);
}


id::vfp_reg VFP_REG::fetch_double_reg_id(const u32 code, const u8 start, const u8 end) {
    const u8 reg_bits = shared::util::bit_range(code, start, end);
    return fetch_double_reg_id(reg_bits);
}


u8 VFP_REG::fetch_vec_len() {
    return shared::util::bit_range(FPSCR, 16, 18);
}


void VFP_REG::reset() {
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