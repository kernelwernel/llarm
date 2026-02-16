#include "../instructions.hpp"

#include "../../vfp/utils.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>

#include <cmath>

// TODO work on exceptions, this might take a while
// TODO finish all VFP instructions

/**
 * if ConditionPassed(cond) then
 *    for i = 0 to vec_len-1
 *       Dd[i] = abs(Dm[i])
 */
void INSTRUCTIONS::arm::vfp::FABSD(const u32 code) {
    const double_encoding_struct encoding = vfp_addressing_mode.double_precision_monadic(code);

    for (const auto regs : encoding.vec_regs) {
        const double Dm = vfp_reg.read_double(regs.Dm_id);
        
        vfp_reg.write_double(regs.Dd_id, std::abs(Dm));
    }
}


/**
 * if ConditionPassed(cond) then
 *     for i = 0 to vec_len-1
 *         Sd[i] = abs(Sm[i]) 
 */
void INSTRUCTIONS::arm::vfp::FABSS(const u32 code) {
    const single_encoding_struct encoding = vfp_addressing_mode.single_precision_monadic(code);

    for (const auto regs : encoding.vec_regs) {
        const double Sm = vfp_reg.read_double(regs.Sm_id);

        vfp_reg.write_double(regs.Sd_id, std::abs(Sm));
    }
}


/**
 * if ConditionPassed(cond) then
 *     for i = 0 to vec_len-1
 *         Dd[i] = Dn[i] + Dm[i]
 */
 // TODO EXCEPTION
void INSTRUCTIONS::arm::vfp::FADDD(const u32 code) {
    const double_encoding_struct encoding = vfp_addressing_mode.double_precision(code);

    for (const auto regs : encoding.vec_regs) {
        const double result = (vfp_reg.read_double(regs.Dn_id) + vfp_reg.read_double(regs.Dm_id));

        vfp_reg.write(regs.Dd_id, vfp_utils::double_to_u64(result)); 
    }
}


/**
 * if ConditionPassed(cond) then
 *     for i = 0 to vec_len-1
 *         Sd[i] = Sn[i] + Sm[i]
 */
 // TODO EXCEPTION
void INSTRUCTIONS::arm::vfp::FADDS(const u32 code) {
    const single_encoding_struct encoding = vfp_addressing_mode.single_precision(code);

    for (const auto regs : encoding.vec_regs) {
        const float result = (vfp_reg.read_single(regs.Sn_id) + vfp_reg.read_single(regs.Sm_id));

        vfp_reg.write(regs.Sd_id, vfp_utils::single_to_u32(result)); 
    }
}


/**
 * if ConditionPassed(cond) then
 *     if (Dd is a signaling NaN) or (Dm is a signaling NaN) then
 *         raise Invalid Operation exception
 *     FPSCR N flag = if (Dd < Dm) then 1 else 0
 *     FPSCR Z flag = if (Dd == Dm) then 1 else 0
 *     FPSCR C flag = if (Dd < Dm) then 0 else 1
 *     FPSCR V flag = if (Dd and Dm compare as unordered) then 1 else 0
 */
void INSTRUCTIONS::arm::vfp::FCMPD(const u32 code) {
    const double Dd = vfp_reg.read_double_IEEE(code, 12, 15);
    const double Dm = vfp_reg.read_double_IEEE(code, 0, 3);

    if (vfp_utils::is_signaling_nan(Dd) || vfp_utils::is_signaling_nan(Dm)) {
        vfp_exception.invalid_operation();
        return;
    }

    vfp_reg.write(id::vfp_reg::FPSCR_N, (Dd < Dm));
    vfp_reg.write(id::vfp_reg::FPSCR_Z, (Dd == Dm));
    vfp_reg.write(id::vfp_reg::FPSCR_C, !(Dd < Dm));
    vfp_reg.write(id::vfp_reg::FPSCR_V, 0); // TODO
}


/**
 * if ConditionPassed(cond) then
 *     if (Dd is a NaN) or (Dm is a NaN) then
 *         raise Invalid Operation exception
 *     FPSCR N flag = if (Dd < Dm) then 1 else 0
 *     FPSCR Z flag = if (Dd == Dm) then 1 else 0
 *     FPSCR C flag = if (Dd < Dm) then 0 else 1
 *     FPSCR V flag = if (Dd and Dm compare as unordered) then 1 else 0
 */
void INSTRUCTIONS::arm::vfp::FCMPED(const u32 code) {
    const double Dd = vfp_reg.read_double_IEEE(code, 12, 15);
    const double Dm = vfp_reg.read_double_IEEE(code, 0, 3);

    if (std::isnan(Dd) || std::isnan(Dm)) {
        vfp_exception.invalid_operation();
        return;
    }

    vfp_reg.write(id::vfp_reg::FPSCR_N, (Dd < Dm));
    vfp_reg.write(id::vfp_reg::FPSCR_Z, (Dd == Dm));
    vfp_reg.write(id::vfp_reg::FPSCR_C, !(Dd < Dm));
    vfp_reg.write(id::vfp_reg::FPSCR_V, 0); // TODO
}


/**
 * if ConditionPassed(cond) then
 *     if (Sd is a NaN) or (Sm is a NaN) then
 *         raise Invalid Operation exception
 *     FPSCR N flag = if (Sd < Sm) then 1 else 0
 *     FPSCR Z flag = if (Sd == Sm) then 1 else 0
 *     FPSCR C flag = if (Sd < Sm) then 0 else 1
 *     FPSCR V flag = if (Sd and Sm compare as unordered) then 1 else 0
 */
void INSTRUCTIONS::arm::vfp::FCMPES(const u32 code) {
    const float Sd = vfp_reg.read_single_IEEE(code, 12, 15, 22);
    const float Sm = vfp_reg.read_single_IEEE(code, 0, 3, 5);

    if (std::isnan(Sd) || std::isnan(Sm)) {
        vfp_exception.invalid_operation();
        return;
    }

    vfp_reg.write(id::vfp_reg::FPSCR_N, (Sd < Sm));
    vfp_reg.write(id::vfp_reg::FPSCR_Z, (Sd == Sm));
    vfp_reg.write(id::vfp_reg::FPSCR_C, !(Sd < Sm));
    vfp_reg.write(id::vfp_reg::FPSCR_V, 0); // TODO
}


/**
 * if ConditionPassed(cond) then
 *     if (Dd is a NaN) then
 *         raise Invalid Operation exception
 *     FPSCR N flag = if (Dd < 0.0) then 1 else 0
 *     FPSCR Z flag = if (Dd == 0.0) then 1 else 0
 *     FPSCR C flag = if (Dd < 0.0) then 0 else 1
 *     FPSCR V flag = if (Dd is a NaN) then 1 else 0
 */
void INSTRUCTIONS::arm::vfp::FCMPEZD(const u32 code) {
    const double Dd = vfp_reg.read_double_IEEE(code, 12, 15);

    const bool is_Dd_nan = std::isnan(Dd);

    if (is_Dd_nan) {
        vfp_exception.invalid_operation();
        return;
    }

    vfp_reg.write(id::vfp_reg::FPSCR_N, (Dd < 0.0));
    vfp_reg.write(id::vfp_reg::FPSCR_Z, (Dd == 0.0));
    vfp_reg.write(id::vfp_reg::FPSCR_C, !(Dd < 0.0));
    vfp_reg.write(id::vfp_reg::FPSCR_V, is_Dd_nan);
}


/**
 * if ConditionPassed(cond) then
 *     if (Sd is a NaN) then
 *         raise Invalid Operation exception
 *     FPSCR N flag = if (Sd < 0.0) then 1 else 0
 *     FPSCR Z flag = if (Sd == 0.0) then 1 else 0
 *     FPSCR C flag = if (Sd < 0.0) then 0 else 1
 *     FPSCR V flag = if (Sd is a NaN) then 1 else 0
 */
void INSTRUCTIONS::arm::vfp::FCMPEZS(const u32 code) {
    const float Sd = vfp_reg.read_single_IEEE(code, 12, 15, 22);

    const bool is_Sd_nan = std::isnan(Sd);

    if (is_Sd_nan) {
        vfp_exception.invalid_operation();
        return;
    }

    vfp_reg.write(id::vfp_reg::FPSCR_N, (Sd < 0.0f));
    vfp_reg.write(id::vfp_reg::FPSCR_Z, (Sd == 0.0f));
    vfp_reg.write(id::vfp_reg::FPSCR_C, !(Sd < 0.0f));
    vfp_reg.write(id::vfp_reg::FPSCR_V, is_Sd_nan);
}


/**
 * if ConditionPassed(cond) then
 *     if (Sd is a signaling NaN) or (Sm is a signaling NaN) then
 *         raise Invalid Operation exception
 *     FPSCR N flag = if (Sd < Sm) then 1 else 0
 *     FPSCR Z flag = if (Sd == Sm) then 1 else 0
 *     FPSCR C flag = if (Sd < Sm) then 0 else 1
 *     FPSCR V flag = if (Sd and Sm compare as unordered) then 1 else 0
 */
void INSTRUCTIONS::arm::vfp::FCMPS(const u32 code) {
    const float Sd = vfp_reg.read_single_IEEE(code, 12, 15, 22);
    const float Sm = vfp_reg.read_single_IEEE(code, 0, 3, 5);

    if (vfp_utils::is_signaling_nan(Sd) || vfp_utils::is_signaling_nan(Sm)) {
        vfp_exception.invalid_operation();
        return;
    }

    vfp_reg.write(id::vfp_reg::FPSCR_N, (Sd < Sm));
    vfp_reg.write(id::vfp_reg::FPSCR_Z, (Sd == Sm));
    vfp_reg.write(id::vfp_reg::FPSCR_C, !(Sd < Sm));
    vfp_reg.write(id::vfp_reg::FPSCR_V, 0); // TODO
}


/**
 * if ConditionPassed(cond) then
 *     if (Dd is a signaling NaN) then
 *         raise Invalid Operation exception
 *     FPSCR N flag = if (Dd < 0.0) then 1 else 0
 *     FPSCR Z flag = if (Dd == 0.0) then 1 else 0
 *     FPSCR C flag = if (Dd < 0.0) then 0 else 1
 *     FPSCR V flag = if (Dd is a NaN) then 1 else 0
 */
void INSTRUCTIONS::arm::vfp::FCMPZD(const u32 code) {
    const double Dd = vfp_reg.read_double_IEEE(code, 12, 15);

    if (vfp_utils::is_signaling_nan(Dd)) {
        vfp_exception.invalid_operation();
        return;
    }

    vfp_reg.write(id::vfp_reg::FPSCR_N, (Dd < 0.0));
    vfp_reg.write(id::vfp_reg::FPSCR_Z, (Dd == 0.0));
    vfp_reg.write(id::vfp_reg::FPSCR_C, !(Dd < 0.0));
    vfp_reg.write(id::vfp_reg::FPSCR_V, std::isnan(Dd));
}


/**
 * if ConditionPassed(cond) then
 *     if (Sd is a signaling NaN) then
 *         raise Invalid Operation exception
 *     FPSCR N flag = if (Sd < 0.0) then 1 else 0
 *     FPSCR Z flag = if (Sd == 0.0) then 1 else 0
 *     FPSCR C flag = if (Sd < 0.0) then 0 else 1
 *     FPSCR V flag = if (Sd is a NaN) then 1 else 0
 */
void INSTRUCTIONS::arm::vfp::FCMPZS(const u32 code) {
    const float Sd = vfp_reg.read_single_IEEE(code, 12, 15, 22);

    if (vfp_utils::is_signaling_nan(Sd)) {
        vfp_exception.invalid_operation();
        return;
    }

    vfp_reg.write(id::vfp_reg::FPSCR_N, (Sd < 0.0f));
    vfp_reg.write(id::vfp_reg::FPSCR_Z, (Sd == 0.0f));
    vfp_reg.write(id::vfp_reg::FPSCR_C, !(Sd < 0.0f));
    vfp_reg.write(id::vfp_reg::FPSCR_V, std::isnan(Sd));
}


/** 
 * if ConditionPassed(cond) then
 *    for i = 0 to vec_len-1
 *       Dd[i] = Dm[i]
 */
void INSTRUCTIONS::arm::vfp::FCPYD(const u32 code) {
    const double_encoding_struct encoding = vfp_addressing_mode.double_precision_monadic(code);

    for (const auto regs : encoding.vec_regs) {
        vfp_reg.write(regs.Dd_id, vfp_reg.read(regs.Dm_id)); 
    }
}


/**
 * if ConditionPassed(cond) then
 *    for i = 0 to vec_len-1
 *       Sd[i] = Sm[i]
 */
void INSTRUCTIONS::arm::vfp::FCPYS(const u32 code) {
    const single_encoding_struct encoding = vfp_addressing_mode.single_precision_monadic(code);

    for (const auto regs : encoding.vec_regs) {
        vfp_reg.write(regs.Sd_id, vfp_reg.read(regs.Sm_id)); 
    }
}


/**
 * if ConditionPassed(cond) then
 *    Dd = ConvertSingleToDouble(Sm)
 */
 // TODO EXCEPTION 
void INSTRUCTIONS::arm::vfp::FCVTDS(const u32 code) {
    const float Sm = vfp_reg.read_single_IEEE(code, 0, 3, 5);

    /** note: 
     * x86 compilers would optimise this away with the 
     * cvttss2si instruction (even under -O0), which i'm 
     * not sure if that can be called an optimisation 
     * rather than just a basic implementation methodology
     * but anyways, ARM uses the same floating point 
     * standard of the IEEE 754 Standard, so I presume 
     * this is a valid way to implement the instruction
     */
    const double d = static_cast<double>(Sm);

    const u64 ret = vfp_utils::double_to_u64(d);
    vfp_reg.write_double(code, 12, 15, ret);
}


/**
 * if ConditionPassed(cond) then
 *    Sd = ConvertDoubleToSingle(Dm)
 */
 // TODO EXCEPTION
void INSTRUCTIONS::arm::vfp::FCVTSD(const u32 code) {
    const double Dm = vfp_reg.read_double_IEEE(code, 0, 3);

    const float f = static_cast<float>(Dm);
    const u32 ret = vfp_utils::single_to_u32(f);
    vfp_reg.write_single(code, 12, 15, ret, 22);
}


/**
 * if ConditionPassed(cond) then
 *    for i = 0 to vec_len-1
 *       Dd[i] = Dn[i] / Dm[i]
 */
 // TODO EXCEPTION
void INSTRUCTIONS::arm::vfp::FDIVD(const u32 code) {
    const double_encoding_struct encoding = vfp_addressing_mode.double_precision(code);

    for (const auto regs : encoding.vec_regs) {
        const double Dm = vfp_reg.read_double(regs.Dm_id);
        const double Dn = vfp_reg.read_double(regs.Dn_id);

        const double result  = Dn / Dm; 

        vfp_reg.write_double(regs.Dd_id, result);
    }
}


/**
 * if ConditionPassed(cond) then
 *     for i = 0 to vec_len-1
 *         Sd[i] = Sn[i] / Sm[i]
 */
 // TODO EXCEPTION
void INSTRUCTIONS::arm::vfp::FDIVS(const u32 code) {
    const single_encoding_struct encoding = vfp_addressing_mode.single_precision(code);

    for (const auto regs : encoding.vec_regs) {
        const float Sm = vfp_reg.read_single(regs.Sm_id);
        const float Sn = vfp_reg.read_single(regs.Sn_id);

        const float result  = Sn / Sm;

        vfp_reg.write_single(regs.Sd_id, result);
    }
}


/**
 * if ConditionPassed(cond) then
 *    if (U == 1)
 *       address = Rn + offset * 4
 *    else
 *       address = Rn - offset * 4
 *    if (big-endian)
 *       Dd = [Memory[address,4] << 32) OR Memory[address+4,4]
 *    else
 *       Dd = [Memory[address+4,4] << 32) OR Memory[address,4]
 */
void INSTRUCTIONS::arm::vfp::FLDD(const u32 code) {
    u32 address = 0;

    const u32 Rn = reg.read(code, 16, 19);
    const u8 offset = llarm::util::bit_range<u8>(code, 0, 7);

    if (llarm::util::bit_fetch(code, 23) == 1) {
        address = Rn + offset * 4;
    } else {
        address = Rn - offset * 4;
    }

    const mem_read_struct access = memory.read(address, 4);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return;
    }

    const mem_read_struct access2 = memory.read(address + 4, 4);

    if (access2.has_failed) {
        memory.manage_abort(access2.abort_code);
        return;
    }

    const id::vfp_reg Dd_id = vfp_reg.fetch_double_reg_id(code, 12, 15);

    // is big endian
    if (coprocessor.read(id::cp15::R1_B)) {
        vfp_reg.write(Dd_id , (access.value << 32) | static_cast<u32>(access2.value));
    } else {
        vfp_reg.write(Dd_id , (access2.value << 32) | static_cast<u32>(access.value));
    }
}


/**
 * if ConditionPassed(cond) then
 *     address = start_address
 *     for i = 0 to (offset-2)/2
 *         // d is the number of register Dd;
 *         // D(n) is the double-precision register numbered n
 *         if (big-endian)
 *             D(d+i) = (Memory[address,] << 32) OR Memory[address+4,4]
 *         else
 *             D(d+i) = (Memory[address+4,4] << 32) OR Memory[address,4]
 *         address = address + 8
 *     assert end_address = address - 4
 */
void INSTRUCTIONS::arm::vfp::FLDMD(const u32 code) {
    const vfp_address_struct addresses = vfp_addressing_mode.vfp_load_multiple(code);

    u32 address = addresses.start;
    const u8 offset = llarm::util::bit_range<u8>(code, 0, 7);
    const u8 cond = (offset - 2) / 2;

    const u8 d = llarm::util::bit_range<u8>(code, 12, 15);

    for (u8 i = 0; i < cond; i++) {
        const mem_read_struct access = memory.read(address, 4);

        if (access.has_failed) {
            memory.manage_abort(access.abort_code);
            return;
        }

        const mem_read_struct access2 = memory.read(address + 4, 4);

        if (access2.has_failed) {
            memory.manage_abort(access2.abort_code);
            return;
        }

        u64 value = 0;

        // is big endian
        if (coprocessor.read(id::cp15::R1_B)) {
            value = (access.value << 32 | access2.value);
        } else {
            value = (access2.value << 32 | access.value);
        }

        const id::vfp_reg Dd_id = vfp_reg.fetch_double_reg_id(d + i);

        vfp_reg.write(Dd_id, value);

        address += 8;
    }

    if (addresses.end != (address - 4)) {
        llarm::out::error("Assertion failed for FLDMD instruction");
    }
}


/**
 * if ConditionPassed(cond) then
 *     address = start_address
 *     for i = 0 to offset-1
 *         // d is as defined for <registers> above;
 *         // S(n) is the single-precision register numbered n
 *         S(d+i) = Memory[address,4]
 *         address = address + 4
 *     assert end_address = address - 4
 */
void INSTRUCTIONS::arm::vfp::FLDMS(const u32 code) {
    const vfp_address_struct addresses = vfp_addressing_mode.vfp_load_multiple(code);

    u32 address = addresses.start;

    const u8 offset = llarm::util::bit_range<u8>(code, 0, 7);

    const u8 d = llarm::util::bit_range<u8>(code, 12, 15);

    for (u8 i = 0; i < offset - 1; i++) {
        const mem_read_struct access = memory.read(address, 4);

        if (access.has_failed) {
            memory.manage_abort(access.abort_code);
            return;
        }

        const id::vfp_reg Sd_id = vfp_reg.fetch_single_reg_id(d + i);

        vfp_reg.write(Sd_id, access.value);
        address += 4;
    }

    if (addresses.end != (address - 4)) {
        llarm::out::error("Assertion failed for FLDMS instruction");
    }
}


/**
 * if ConditionPassed(cond) then 
 *     // d is the number of register Dd;
 *     // D(n) is the double-precision register numbered n
 *     Load registers D(d) to D(d+(offset-3)/2) from memory words Memory[start_address,4] through to Memory[end_address-4,4]
 */
void INSTRUCTIONS::arm::vfp::FLDMX(const u32 code) {
    const u8 offset = llarm::util::bit_range<u8>(code, 0, 7);

    const u8 d = llarm::util::bit_range<u8>(code, 12, 15);

    const vfp_address_struct addresses = vfp_addressing_mode.vfp_load_multiple(code);

    u32 address = addresses.start;

    for (u8 i = 0; i <= (offset - 3) / 2; i++) {

        const mem_read_struct access = memory.read(address, 4);

        if (access.has_failed) {
            memory.manage_abort(access.abort_code);
            return;
        }
    }

    // TODO
    
}


/**
 * if ConditionPassed(cond) then
 *    if (U == 1)
 *       address = Rn + offset * 4
 *    else
 *       address = Rn - offset * 4
 *    Sd = Memory[address,4]
 */
void INSTRUCTIONS::arm::vfp::FLDS(const u32 code) {
    const bool U = llarm::util::bit_fetch(code, 23);
    u32 address = 0;

    const u32 Rn = reg.read(code, 16, 19);
    const u8 offset = llarm::util::bit_range<u8>(code, 0, 7);

    if (U == 1) {
        address = Rn + offset * 4;
    } else {
        address = Rn - offset * 4;
    }

    const mem_read_struct access = memory.read(address, 4);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return;
    }

    vfp_reg.write_single(code, 12, 15, static_cast<u32>(access.value), 22);
}


void INSTRUCTIONS::arm::vfp::FMACD(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FMACS(const u32 code) {


}


/**
 * if ConditionPassed(cond) then
 *    Dn[63:32] = Rd
 */
void INSTRUCTIONS::arm::vfp::FMDHR(const u32 code) {
    const u32 Rd = reg.read(code, 12, 15);
    const id::vfp_reg Dn_id = vfp_reg.fetch_double_reg_id(code, 16, 19);

    u64 Dn = vfp_reg.read(Dn_id);
    util::swap_bits_vfp(Dn, 32, 63, Rd);
    vfp_reg.write(Dn_id, Dn);
}


/**
 * if ConditionPassed(cond) then
 *    Dn[31:0] = Rd 
 */
void INSTRUCTIONS::arm::vfp::FMDLR(const u32 code) {
    const u32 Rd = reg.read(code, 12, 15);
    const id::vfp_reg Dn_id = vfp_reg.fetch_double_reg_id(code, 16, 19);

    u64 Dn = vfp_reg.read(Dn_id);
    util::swap_bits_vfp(Dn, 0, 31, Rd);
    vfp_reg.write(Dn_id, Dn);
}


/**
 * if ConditionPassed(cond) then
 *    Rd = Dn[63:32]
 */
void INSTRUCTIONS::arm::vfp::FMRDH(const u32 code) {
    const u64 Dn = vfp_reg.read_double(code, 16, 19);
    reg.write(code, 12, 15, llarm::util::bit_range(Dn, 32, 63));
}


/**
 * if ConditionPassed(cond) then
 *    Rd = Dn[31:0]
 */
void INSTRUCTIONS::arm::vfp::FMRDL(const u32 code) {
    const u64 Dn = vfp_reg.read_double(code, 16, 19);
    reg.write(code, 12, 15, llarm::util::bit_range(Dn, 0, 31));
}


/**
 * if ConditionPassed(cond) then
 *    Rd = Sn
 */
void INSTRUCTIONS::arm::vfp::FMRS(const u32 code) {
    const u32 Sn = vfp_reg.read_single(code, 16, 19, 7);
    reg.write(code, 12, 15, Sn);
}


/**
 * if ConditionPassed(cond) then
 *    Rd = reg
 */
void INSTRUCTIONS::arm::vfp::FMRX(const u32 code) {
    const u8 reg_id = llarm::util::bit_range<u8>(code, 16, 19);

    id::vfp_reg id = id::vfp_reg::UNKNOWN;

    switch (reg_id) {
        case 0b0000: id = id::vfp_reg::FPSID; break;
        case 0b0001: id = id::vfp_reg::FPSCR; break;
        case 0b1000: id = id::vfp_reg::FPEXC; break;
        default: 
            llarm::out::warning("No known VFP system register for FMRX, defaulting to FPSCR");
            id = id::vfp_reg::FPSCR;
    }

    reg.write(code, 12, 15, static_cast<u32>(vfp_reg.read(id)));
} 


void INSTRUCTIONS::arm::vfp::FMSCD(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FMSCS(const u32 code) {


}


/**
 * if ConditionPassed(cond) then
 *    Sn = Rd
 */
void INSTRUCTIONS::arm::vfp::FMSR(const u32 code) {
    const u32 Rd = reg.read(code, 12, 15);
    vfp_reg.write_single(code, 16, 19, Rd, 7);
}


/**
 * if ConditionPassed(cond) then
 *    CPSR N Flag = FPSCR N Flag
 *    CPSR Z Flag = FPSCR Z Flag
 *    CPSR C Flag = FPSCR C Flag
 *    CPSR V Flag = FPSCR V Flag
 */
void INSTRUCTIONS::arm::vfp::FMSTAT(const u32 code) {
    reg.write(id::cpsr::N, static_cast<u8>(vfp_reg.read(id::vfp_reg::FPSCR_N)));
    reg.write(id::cpsr::Z, static_cast<u8>(vfp_reg.read(id::vfp_reg::FPSCR_Z)));
    reg.write(id::cpsr::C, static_cast<u8>(vfp_reg.read(id::vfp_reg::FPSCR_C)));
    reg.write(id::cpsr::V, static_cast<u8>(vfp_reg.read(id::vfp_reg::FPSCR_V)));
}


void INSTRUCTIONS::arm::vfp::FMULD(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FMULS(const u32 code) {


}


/**
 * if ConditionPassed(cond) then
 *    reg = Rd
 */
void INSTRUCTIONS::arm::vfp::FMXR(const u32 code) {
    const u8 reg_id = llarm::util::bit_range<u8>(code, 16, 19);

    id::vfp_reg id = id::vfp_reg::UNKNOWN;

    switch (reg_id) {
        case 0b0000: id = id::vfp_reg::FPSID; break;
        case 0b0001: id = id::vfp_reg::FPSCR; break;
        case 0b1000: id = id::vfp_reg::FPEXC; break;
        default: 
            llarm::out::warning("No known VFP system register for FMXR, defaulting to FPSCR");
            id = id::vfp_reg::FPSCR;
    }

    const u32 Rd = reg.read(code, 12, 15);

    vfp_reg.write(id, Rd);
}


void INSTRUCTIONS::arm::vfp::FNEGD(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FNEGS(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FNMACD(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FNMACS(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FNMSCD(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FNMSCS(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FNMULD(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FNMULS(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FSITOD(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FSITOS(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FSQRTD(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FSQRTS(const u32 code) {


}


/**
 * if ConditionPassed(cond) then
 *    if (U == 1)
 *       address = Rn + offset * 4
 *    else
 *       address = Rn - offset * 4
 *    if (big-endian)
 *       Memory[address,4] = Dd[63:32]
 *       Memory[address+4,4] = Dd[31:0]
 *    else
 *       Memory[address,4] = Dd[31:0]
 *       Memory[address+4,4] = Dd[63:32]
 */
void INSTRUCTIONS::arm::vfp::FSTD(const u32 code) {
    u32 address = 0;
    const u32 Rn = reg.read(code, 16, 19);
    const u8 offset = llarm::util::bit_range<u8>(code, 0, 7);

    if (llarm::util::bit_fetch(code, 23)) {
        address = Rn + offset * 4;
    } else {
        address = Rn - offset * 4;
    }

    const u64 Dd = vfp_reg.read_double(code, 12, 15);

    const u32 low_Dd = llarm::util::bit_range(Dd, 0, 31);
    const u32 high_Dd = llarm::util::bit_range(Dd, 32, 63);

    u32 first_access = 0;
    u32 second_access = 0;

    // is big endian
    if (coprocessor.read(id::cp15::R1_B)) {
        first_access = high_Dd;
        second_access = low_Dd;
    } else {
        first_access = low_Dd;
        second_access = high_Dd;
    }

    const mem_write_struct access = memory.write(first_access, address, 4);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return;
    }

    const mem_write_struct access2 = memory.write(second_access, address + 4, 4);

    if (access2.has_failed) {
        memory.manage_abort(access2.abort_code);
        return;
    }    
}

void INSTRUCTIONS::arm::vfp::FSTMD(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FSTMS(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FSTMX(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FSTS(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FSUBD(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FSUBS(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FTOSID(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FTOSIS(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FTOUID(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FTOUIS(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FUITOD(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FUITOS(const u32 code) {


}