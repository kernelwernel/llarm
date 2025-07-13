#include "../instructions.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"


/**
 * if ConditionPassed(cond) then
 *    for i = 0 to vec_len-1
 *       Dd[i] = abs(Dm[i])
 */
void INSTRUCTIONS::arm::vfp::FABSD(const u32 code) {
    for (u8 i = 0; i < vfp_reg.fetch_vec_len() - 1; i++) {
        
    }
}


void INSTRUCTIONS::arm::vfp::FABSS(const u32 code) {

}

void INSTRUCTIONS::arm::vfp::FADDD(const u32 code) {

}

void INSTRUCTIONS::arm::vfp::FADDS(const u32 code) {

}

void INSTRUCTIONS::arm::vfp::FCMPD(const u32 code) {

}

void INSTRUCTIONS::arm::vfp::FCMPED(const u32 code) {

}

void INSTRUCTIONS::arm::vfp::FCMPES(const u32 code) {

}

void INSTRUCTIONS::arm::vfp::FCMPEZD(const u32 code) {

}

void INSTRUCTIONS::arm::vfp::FCMPEZS(const u32 code) {

}

void INSTRUCTIONS::arm::vfp::FCMPS(const u32 code) {

}

void INSTRUCTIONS::arm::vfp::FCMPZD(const u32 code) {

}

void INSTRUCTIONS::arm::vfp::FCMPZS(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FCPYD(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FCPYS(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FCVTDS(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FCVTSD(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FDIVD(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FDIVS(const u32 code) {


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
    const u8 offset = shared::util::bit_range(code, 0, 7);

    if (shared::util::bit_fetch(code, 23) == 1) {
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

void INSTRUCTIONS::arm::vfp::FLDMD(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FLDMS(const u32 code) {


}

void INSTRUCTIONS::arm::vfp::FLDMX(const u32 code) {


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
    const bool U = shared::util::bit_fetch(code, 23);
    u32 address = 0;

    const u32 Rn = reg.read(code, 16, 19);
    const u8 offset = shared::util::bit_range(code, 0, 7);

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

    vfp_reg.write_single(code, 12, 15, access.value, 22);
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
    reg.write(code, 12, 15, shared::util::bit_range(Dn, 32, 63));
}


/**
 * if ConditionPassed(cond) then
 *    Rd = Dn[31:0]
 */
void INSTRUCTIONS::arm::vfp::FMRDL(const u32 code) {
    const u64 Dn = vfp_reg.read_double(code, 16, 19);
    reg.write(code, 12, 15, shared::util::bit_range(Dn, 0, 31));
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
    const u8 reg_id = shared::util::bit_range(code, 16, 19);

    id::vfp_reg id = id::vfp_reg::UNKNOWN;

    switch (reg_id) {
        case 0b0000: id = id::vfp_reg::FPSID; break;
        case 0b0001: id = id::vfp_reg::FPSCR; break;
        case 0b1000: id = id::vfp_reg::FPEXC; break;
        default: 
            shared::out::warning("No known VFP system register for FMRX, defaulting to FPSCR");
            id = id::vfp_reg::FPSCR;
    }

    reg.write(code, 12, 15, vfp_reg.read(id));
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
    reg.write(id::cpsr::N, vfp_reg.read(id::vfp_reg::FPSCR_N));
    reg.write(id::cpsr::Z, vfp_reg.read(id::vfp_reg::FPSCR_Z));
    reg.write(id::cpsr::C, vfp_reg.read(id::vfp_reg::FPSCR_C));
    reg.write(id::cpsr::V, vfp_reg.read(id::vfp_reg::FPSCR_V));
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
    const u8 reg_id = shared::util::bit_range(code, 16, 19);

    id::vfp_reg id = id::vfp_reg::UNKNOWN;

    switch (reg_id) {
        case 0b0000: id = id::vfp_reg::FPSID; break;
        case 0b0001: id = id::vfp_reg::FPSCR; break;
        case 0b1000: id = id::vfp_reg::FPEXC; break;
        default: 
            shared::out::warning("No known VFP system register for FMXR, defaulting to FPSCR");
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
    const u8 offset = shared::util::bit_range(code, 0, 7);

    if (shared::util::bit_fetch(code, 23)) {
        address = Rn + offset * 4;
    } else {
        address = Rn - offset * 4;
    }

    const u64 Dd = vfp_reg.read_double(code, 12, 15);

    const u32 low_Dd = shared::util::bit_range(Dd, 0, 31);
    const u32 high_Dd = shared::util::bit_range(Dd, 32, 63);

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