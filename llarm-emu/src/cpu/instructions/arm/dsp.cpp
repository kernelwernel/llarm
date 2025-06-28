#include "../instructions.hpp"

#include "addressing_modes/addressing_modes.hpp"

#include "shared/out.hpp"
#include "shared/types.hpp"
#include "shared/util.hpp"

/**
 * if ConditionPassed(cond) then
 *    if (Rd is even-numbered) then
 *       if (address[2:0] == 0b000) and (Rd is not R14) then
 *          Rd = Memory[address,4]
 *          R(d+1) = Memory[address+4,4]
 *       else
 *          UNPREDICTABLE
 *    else
 *       UNDEFINED
 */
void INSTRUCTIONS::arm::dsp::LDRD(const u32 code) {
    const u8 Rd_bits = shared::util::bit_range(code, 12, 15);

    // is even
    if (Rd_bits & 1) {
        exception.undefined();
        return;
    }

    const u32 address = address_mode.load_store_misc(code);

    if (
        (shared::util::bit_range(address, 0, 2) == 0b000) &&
        (Rd_bits != 14)
    ) {
        // this will cover both the lower and high 4 bytes
        const mem_read_struct access = memory.read(address, 8);

        if (access.has_failed) {
            memory.manage_abort(access.abort_code);
            return;
        }

        reg.write(Rd_bits, shared::util::bit_range(access.value, 0, 31));
        reg.write(Rd_bits + 1, shared::util::bit_range(access.value, 32, 63));
    } else {
        shared::out::unpredictable("LDRD has unpredictable arguments");
    }
}


/**
 * 
 */
void INSTRUCTIONS::arm::dsp::MCRR(const u32 code) {
    // TODO
}


/**
 * 
 */
void INSTRUCTIONS::arm::dsp::MRRC(const u32 code) {
    // TODO
}


/**
 * // No change occurs to programmer’s model state, but where
 * // appropriate, the memory system is signalled that memory accesses
 * // to the specified address are likely in the near future.
 */
void INSTRUCTIONS::arm::dsp::PLD(const u32 code) {
    return; // TODO, this might change 
}


/**
 * if ConditionPassed(cond) then
 *    Rd = SignedSat(Rm + Rn, 32)
 *    if SignedDoesSat(Rm + Rn, 32) then
 *       Q Flag = 1
 */
void INSTRUCTIONS::arm::dsp::QADD(const u32 code) {
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rn = reg.read(code, 16, 19);

    reg.write(code, 12, 15, operation.signed_sat(Rm + Rn, 32));
    if (operation.signed_does_sat(Rm + Rn, 32)) {
        reg.write(id::cpsr::Q, true);
    }
}


/**
 * if ConditionPassed(cond) then
 *    Rd = SignedSat(Rm + SignedSat(Rn*2, 32), 32)
 *    if SignedDoesSat(Rm + SignedSat(Rn*2, 32), 32) or
 *       SignedDoesSat(Rn*2, 32) then
 *       Q Flag = 1
 */
void INSTRUCTIONS::arm::dsp::QDADD(const u32 code) {
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rn = reg.read(code, 16, 19);

    const u32 result = (Rm + operation.signed_sat(Rn * 2, 32));

    reg.write(code, 12, 15, operation.signed_sat(result, 32));

    if (
        (operation.signed_does_sat(result, 32)) ||
        (operation.signed_does_sat(Rn * 2, 32))
    ) {
        reg.write(id::cpsr::Q, true);
    }
}


/**
 * if ConditionPassed(cond) then
 *    Rd = SignedSat(Rm - SignedSat(Rn*2, 32), 32)
 *    if SignedDoesSat(Rm - SignedSat(Rn*2, 32), 32) or
 *       SignedDoesSat(Rn*2, 32) then
 *       Q Flag = 1
 */
void INSTRUCTIONS::arm::dsp::QDSUB(const u32 code) {
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rn = reg.read(code, 16, 19);

    const u32 result = (Rm - operation.signed_sat(Rn * 2, 32));

    reg.write(code, 12, 15, operation.signed_sat(result, 32));

    if (
        (operation.signed_does_sat(result, 32)) ||
        (operation.signed_does_sat(Rn * 2, 32))
    ) {
        reg.write(id::cpsr::Q, true);
    }
}


/**
 * if ConditionPassed(cond) then
 *    Rd = SignedSat(Rm - Rn, 32)
 *    if SignedDoesSat(Rm - Rn, 32) then
 *       Q Flag = 1
 */
void INSTRUCTIONS::arm::dsp::QSUB(const u32 code) {
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rn = reg.read(code, 16, 19);

    reg.write(code, 12, 15, operation.signed_sat(Rm - Rn, 32));

    if (operation.signed_does_sat(Rm - Rn, 32)) {
        reg.write(id::cpsr::Q, true);
    }
}


/**
 * if ConditionPassed(cond) then
 *    if (x == 0) then
 *       operand1 = SignExtend(Rm[15:0])
 *    else // x == 1
 *       operand1 = SignExtend(Rm[31:16])
 * 
 *    if (y == 0) then
 *       operand2 = SignExtend(Rs[15:0])
 *    else // y == 1
 *       operand2 = SignExtend(Rs[31:16])
 *    
 *    Rd = (operand1 * operand2) + Rn
 *    if OverflowFrom((operand1 * operand2) + Rn) then
 *       Q Flag = 1
 */
void INSTRUCTIONS::arm::dsp::SMLAXY(const u32 code) {
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rs = reg.read(code, 8, 11);
    const u32 Rn = reg.read(code, 12, 15);

    const bool X = shared::util::bit_fetch(code, 5);
    const bool Y = shared::util::bit_fetch(code, 6);

    u32 operand1 = 0;
    u32 operand2 = 0;

    if (X == false) {
        operand1 = operation.sign_extend(shared::util::bit_range(Rm, 0, 15), 15);
    } else {
        operand1 = operation.sign_extend(shared::util::bit_range(Rm, 16, 31), 31);
    }

    if (Y == false) {
        operand2 = operation.sign_extend(shared::util::bit_range(Rs, 0, 15), 15);   
    } else {
        operand2 = operation.sign_extend(shared::util::bit_range(Rs, 16, 31), 31);
    }

    const u32 result = (operand1 * operand2);

    reg.write(code, 16, 19, result + Rn);

    if (operation.overflow_add(result, Rn)) {
        reg.write(id::cpsr::Q, true);
    }
}


/**
 * if ConditionPassed(cond) then
 *    if (x == 0) then
 *       operand1 = SignExtend(Rm[15:0])
 *    else // x == 1
 *       operand1 = SignExtend(Rm[31:16])
 *
 *    if (y == 0) then
 *       operand2 = SignExtend(Rs[15:0])
 *    else // y == 1
 *       operand2 = SignExtend(Rs[31:16])
 *
 *    RdLo = RdLo + (operand1 * operand2)
 *    RdHi = RdHi + (if (operand1*operand2) < 0 then 0xFFFFFFFF else 0)
 *                + CarryFrom(RdLo + (operand1 * operand2))
 */
void INSTRUCTIONS::arm::dsp::SMLALXY(const u32 code) {
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rs = reg.read(code, 8, 11);

    const bool X = shared::util::bit_fetch(code, 5);
    const bool Y = shared::util::bit_fetch(code, 6);

    u32 operand1 = 0;
    u32 operand2 = 0;    

    if (X == false) {
        operand1 = operation.sign_extend(shared::util::bit_range(Rm, 0, 15), 15);
    } else {
        operand1 = operation.sign_extend(shared::util::bit_range(Rm, 16, 31), 31);
    }

    if (Y == false) {
        operand2 = operation.sign_extend(shared::util::bit_range(Rs, 0, 15), 15);
    } else {
        operand2 = operation.sign_extend(shared::util::bit_range(Rs, 16, 31), 31);
    }

    const id::reg RdLo_id = reg.fetch_reg_id(code, 21, 15);
    const id::reg RdHi_id = reg.fetch_reg_id(code, 16, 19);

    const u32 result = (operand1 * operand2);

    u32 tmp = 0; 

    if (result < 0) {
        tmp = 0xFFFFFFFF;
    }

    reg.write(RdLo_id, (reg.read(RdLo_id) + result));

    const u32 RdHi = reg.read(RdHi_id);
    reg.write(RdHi_id, (RdHi + tmp + operation.carry_add(reg.read(RdLo_id), result)));
}


/**
 * if ConditionPassed(cond) then
 *    if (y == 0) then
 *       operand2 = SignExtend(Rs[15:0])
 *    else // y == 1
 *       operand2 = SignExtend(Rs[31:16])
 *    Rd = (Rm * operand2)[47:16] + Rn // Signed multiplication
 *    if OverflowFrom((Rm * operand2)[47:16] + Rn) then
 *       Q Flag = 1
 */
void INSTRUCTIONS::arm::dsp::SMLAWY(const u32 code) {
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rs = reg.read(code, 8, 11);
    const u32 Rn = reg.read(code, 12, 15);
    const u32 Rd = reg.read(code, 16, 19);

    const bool Y = shared::util::bit_fetch(code, 6);

    // not sure why the docs call it operand2 instead of just operand, 
    // where's the first one then? i have no idea.
    u32 operand2 = 0;

    if (Y == false) {
        operand2 = operation.sign_extend(shared::util::bit_range(Rs, 0, 15), 15);
    } else {
        operand2 = operation.sign_extend(shared::util::bit_range(Rs, 16, 31), 31);
    }

    const u32 result = shared::util::bit_range<u32>(static_cast<u64>(Rm) * operand2, 16, 47);

    reg.write(code, 16, 19, result + Rn);

    if (operation.overflow_add(result, Rn)) {
        reg.write(id::cpsr::Q, true);
    }
}


/**
 * if ConditionPassed(cond) then
 *    if (x == 0) then
 *       operand1 = SignExtend(Rm[15:0])
 *    else // x == 1
 *       operand1 = SignExtend(Rm[31:16])
 *    
 *    if (y == 0) then
 *       operand2 = SignExtend(Rs[15:0])
 *    else // y == 1
 *       operand2 = SignExtend(Rs[31:16])
 *
 *    Rd = operand1 * operand2
 */
void INSTRUCTIONS::arm::dsp::SMULXY(const u32 code) {
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rs = reg.read(code, 8, 11);
    const u32 Rd = reg.read(code, 16, 19);

    const bool Y = shared::util::bit_fetch(code, 6);
    const bool X = shared::util::bit_fetch(code, 5);

    u32 operand1 = 0;
    u32 operand2 = 0;

    if (X == false) {
        operand1 = operation.sign_extend(shared::util::bit_range(Rm, 0, 15), 15);
    } else {
        operand1 = operation.sign_extend(shared::util::bit_range(Rm, 16, 31), 31);
    }

    if (Y == false) {
        operand2 = operation.sign_extend(shared::util::bit_range(Rs, 0, 15), 15);
    } else {
        operand2 = operation.sign_extend(shared::util::bit_range(Rs, 16, 31), 31);
    }

    reg.write(code, 16, 19, operand1 * operand2);
}


/**
 * if ConditionPassed(cond) then
 *    if (y == 0) then
 *       operand2 = SignExtend(Rs[15:0])
 *    else // y == 1
 *       operand2 = SignExtend(Rs[31:16])
 *    Rd = (Rm * operand2)[47:16] // Signed multiplication
 */
void INSTRUCTIONS::arm::dsp::SMULWY(const u32 code) {
    const u32 Rm = reg.read(code, 0, 3);
    const u32 Rs = reg.read(code, 8, 11);
    const u32 Rd = reg.read(code, 16, 19);

    const bool Y = shared::util::bit_fetch(code, 6);

    // same as SMLAWY, where tf is operand1 in the docs? i'm not on drugs am i?
    u32 operand2 = 0;

    if (Y == false) {
        operand2 = operation.sign_extend(shared::util::bit_range(Rs, 0, 15), 15);
    } else {
        operand2 = operation.sign_extend(shared::util::bit_range(Rs, 16, 31), 31);
    }

    reg.write(code, 16, 19, shared::util::bit_range<u32>(static_cast<u64>(Rm * operand2), 16, 47));
}


/*
 * if ConditionPassed(cond) then
 *    if (Rd is even-numbered) then
 *       if (address[2:0] == 0b000) and (Rd is not R14) then
 *          Memory[address,4] = Rd
 *          Memory[address+4,4] = R(d+1)
 *       else
 *          UNPREDICTABLE
 *    else
 *       UNDEFINED
 */
void INSTRUCTIONS::arm::dsp::STRD(const u32 code) {
    const u8 Rd_bits = shared::util::bit_range(code, 12, 15);

    // is odd
    if (Rd_bits & 1) {
        exception.undefined();
        return;
    }

    const u32 address = address_mode.load_store_misc(code);

    if (
        (shared::util::bit_range(address, 0, 2) == 0b000) &&
        (Rd_bits != 14)
    ) {
        const u64 value = (static_cast<u64>(reg.read(Rd_bits + 1)) << 32) | reg.read(Rd_bits);
        const mem_write_struct access = memory.write(value, address, 8);

        if (access.has_failed) {
            memory.manage_abort(access.abort_code);
            return;
        }
    } else {
        shared::out::unpredictable("LDRD has unpredictable arguments");
    }
}