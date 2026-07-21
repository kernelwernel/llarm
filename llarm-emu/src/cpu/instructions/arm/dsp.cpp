#include "../instructions.hpp"
#include "../operation.hpp"

#include "addressing_modes/addressing_modes.hpp"

#include <llarm/shared/out.hpp>
#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>

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
    const u8 Rd_bits = llarm::util::bit_range<u8>(code, 12, 15);

    // is even
    if (Rd_bits & 1) {
        exception.undefined();
        return;
    }

    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);
    const u32 original_Rn = reg.read(Rn_id);

    const u32 address = address_mode.load_store_misc(code);

    const u8 address_low3 = llarm::util::bit_range<u8>(address, 0, 2);
    const bool is_misaligned = (address_low3 != 0b000);

    // ARMv6's Data Access Behavior table (A2-10) formalizes Two-word (LDRD/STRD) alignment
    // faulting: with the A bit set, a word-aligned-but-not-doubleword-aligned address
    // (address_low3 == 0b100) only faults when the U bit (unaligned data access support) is
    // clear; any other misalignment always faults. This rule is ARMv6-specific (prior to
    // ARMv6 this is simply UNPREDICTABLE, which real silicon such as ARM926EJ-S (ARMv5TE)
    // handles by performing both word transfers regardless, per the note below), so it must
    // not apply to earlier architectures.
    if (
        (memory.settings.arch >= id::arch::ARMv6) &&
        (memory.settings.has_alignment_fault_checking) &&
        (coprocessor.read(id::cp15::R1_A))
    ) {
        const bool word_aligned_only = (address_low3 == 0b100);
        const bool permitted = word_aligned_only && coprocessor.read(id::cp15::R1_U);

        if (is_misaligned && !permitted) {
            reg.write(Rn_id, original_Rn);

            if (memory.mmu.is_mmu_enabled()) {
                memory.mmu.manage_abort(id::aborts::ALIGNMENT, address);
            }

            memory.manage_abort(id::aborts::ALIGNMENT);
            return;
        }
    }

    if (is_misaligned || (Rd_bits == 14)) {
        llarm::out::unpredictable("LDRD has unpredictable arguments");
    }

    const mem_read_struct access = memory.read(address, 4);

    if (access.has_failed) {
        reg.write(Rn_id, original_Rn);
        memory.manage_abort(access.abort_code);
        return;
    }

    const mem_read_struct access2 = memory.read(address + 4, 4);

    if (access2.has_failed) {
        reg.write(Rn_id, original_Rn);
        memory.manage_abort(access2.abort_code);
        return;
    }

    reg.write(Rd_bits, llarm::util::bit_range(access.value, 0, 31));
    reg.write(Rd_bits + 1, llarm::util::bit_range(access2.value, 0, 31));
}


/**
 * if ConditionPassed(cond) then
 *    send Rd value to Coprocessor[cp_num]
 *    send Rn value to Coprocessor[cp_num]
 */
void INSTRUCTIONS::arm::dsp::MCRR(const u32 code) {
    const u8 cp_num = llarm::util::bit_range<u8>(code, 8, 11);
    const u8 opcode = llarm::util::bit_range<u8>(code, 4, 7);
    const u8 CRm = llarm::util::bit_range<u8>(code, 0, 3);
    const u32 Rd = reg.read(code, 12, 15);
    const u32 Rn = reg.read(code, 16, 19);

    const u64 value = static_cast<u64>(Rn) << 32 | Rd;
    coprocessor.write(cp_num, 0, CRm, opcode, value);
}


/**
 * if ConditionPassed(cond) then
 *    Rd = first value from Coprocessor[cp_num]
 *    Rn = second value from Coprocessor[cp_num]
 */
void INSTRUCTIONS::arm::dsp::MRRC(const u32 code) {
    const u8 cp_num  = llarm::util::bit_range<u8>(code, 8, 11);
    const u8 opcode  = llarm::util::bit_range<u8>(code, 4, 7);
    const u8 CRm     = llarm::util::bit_range<u8>(code, 0, 3);
    const u8 Rd_bits = llarm::util::bit_range<u8>(code, 12, 15);
    const u8 Rn_bits = llarm::util::bit_range<u8>(code, 16, 19);

    const u64 value = static_cast<u64>(coprocessor.read(cp_num, 0, CRm, opcode));
    reg.write(Rd_bits, static_cast<u32>(value));
    reg.write(Rn_bits, static_cast<u32>(value >> 32));
}


void INSTRUCTIONS::arm::dsp::MCRR2(const u32 code) {
    MCRR(code);
}


void INSTRUCTIONS::arm::dsp::MRRC2(const u32 code) {
    MRRC(code);
}


/**
 * // No change occurs to programmer’s model state, but where
 * // appropriate, the memory system is signalled that memory accesses
 * // to the specified address are likely in the near future.
 */
void INSTRUCTIONS::arm::dsp::PLD(/*const u32 code*/) {
    // TODO, this might change 
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

    reg.write(code, 12, 15, static_cast<u32>(operation::signed_sat(Rm + Rn, 32)));
    if (operation::signed_does_sat(Rm + Rn, 32)) {
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

    const u32 result = (Rm + static_cast<u32>(operation::signed_sat(Rn * 2, 32)));

    reg.write(code, 12, 15, static_cast<u32>(operation::signed_sat(result, 32)));

    if (
        (operation::signed_does_sat(result, 32)) ||
        (operation::signed_does_sat(Rn * 2, 32))
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

    const u32 result = (Rm - static_cast<u32>(operation::signed_sat(Rn * 2, 32)));

    reg.write(code, 12, 15, static_cast<u32>(operation::signed_sat(result, 32)));

    if (
        (operation::signed_does_sat(result, 32)) ||
        (operation::signed_does_sat(Rn * 2, 32))
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

    reg.write(code, 12, 15, static_cast<u32>(operation::signed_sat(Rm - Rn, 32)));

    if (operation::signed_does_sat(Rm - Rn, 32)) {
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

    const bool X = llarm::util::bit_fetch(code, 5);
    const bool Y = llarm::util::bit_fetch(code, 6);

    i32 operand1 = 0;
    i32 operand2 = 0;

    if (X == false) {
        operand1 = operation::sign_extend(llarm::util::bit_range(Rm, 0, 15), 15);
    } else {
        operand1 = operation::sign_extend(llarm::util::bit_range(Rm, 16, 31), 31);
    }

    if (Y == false) {
        operand2 = operation::sign_extend(llarm::util::bit_range(Rs, 0, 15), 15);   
    } else {
        operand2 = operation::sign_extend(llarm::util::bit_range(Rs, 16, 31), 31);
    }

    const i32 result = operand1 * operand2;

    reg.write(code, 16, 19, static_cast<u32>(result) + Rn);

    if (operation::signed_overflow_add(result, static_cast<i32>(Rn))) {
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

    const bool X = llarm::util::bit_fetch(code, 5);
    const bool Y = llarm::util::bit_fetch(code, 6);

    i32 operand1 = 0;
    i32 operand2 = 0;    

    if (X == false) {
        operand1 = operation::sign_extend(llarm::util::bit_range(Rm, 0, 15), 15);
    } else {
        operand1 = operation::sign_extend(llarm::util::bit_range(Rm, 16, 31), 31);
    }

    if (Y == false) {
        operand2 = operation::sign_extend(llarm::util::bit_range(Rs, 0, 15), 15);
    } else {
        operand2 = operation::sign_extend(llarm::util::bit_range(Rs, 16, 31), 31);
    }

    const id::reg RdLo_id = reg.fetch_reg_id(code, 21, 15);
    const id::reg RdHi_id = reg.fetch_reg_id(code, 16, 19);

    const i32 result = (operand1 * operand2);

    u32 tmp = 0; 

    if (result < 0) {
        tmp = 0xFFFFFFFF;
    }

    reg.write(RdLo_id, (reg.read(RdLo_id) + static_cast<u32>(result)));

    const u32 RdHi = reg.read(RdHi_id);
    reg.write(RdHi_id, (RdHi + tmp + operation::carry_add(reg.read(RdLo_id), static_cast<u32>(result))));
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

    const bool Y = llarm::util::bit_fetch(code, 6);

    // not sure why the docs call it operand2 instead of just operand, 
    // where's the first one then? i have no idea.
    i32 operand2 = 0;

    if (Y == false) {
        operand2 = operation::sign_extend(llarm::util::bit_range(Rs, 0, 15), 15);
    } else {
        operand2 = operation::sign_extend(llarm::util::bit_range(Rs, 16, 31), 31);
    }

    const u32 result = llarm::util::bit_range<u32>(static_cast<u64>(Rm) * static_cast<u32>(operand2), 16, 47);

    reg.write(code, 16, 19, result + Rn);

    if (operation::overflow_add(result, Rn)) {
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

    const bool Y = llarm::util::bit_fetch(code, 6);
    const bool X = llarm::util::bit_fetch(code, 5);

    i32 operand1 = 0;
    i32 operand2 = 0;

    if (X == false) {
        operand1 = operation::sign_extend(llarm::util::bit_range(Rm, 0, 15), 15);
    } else {
        operand1 = operation::sign_extend(llarm::util::bit_range(Rm, 16, 31), 31);
    }

    if (Y == false) {
        operand2 = operation::sign_extend(llarm::util::bit_range(Rs, 0, 15), 15);
    } else {
        operand2 = operation::sign_extend(llarm::util::bit_range(Rs, 16, 31), 31);
    }

    reg.write(code, 16, 19, static_cast<u32>(operand1 * operand2));
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

    const bool Y = llarm::util::bit_fetch(code, 6);

    // same as SMLAWY, where tf is operand1 in the docs? i'm not on drugs am i?
    i32 operand2 = 0;

    if (Y == false) {
        operand2 = operation::sign_extend(llarm::util::bit_range(Rs, 0, 15), 15);
    } else {
        operand2 = operation::sign_extend(llarm::util::bit_range(Rs, 16, 31), 31);
    }

    // this is fucking awful
    const i64 product = static_cast<i64>(static_cast<i32>(Rm)) * static_cast<i64>(operand2);
    reg.write(code, 16, 19, llarm::util::bit_range<u32>(static_cast<u64>(product), 16, 47));
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
    const u8 Rd_bits = llarm::util::bit_range<u8>(code, 12, 15);

    // is odd
    if (Rd_bits & 1) {
        exception.undefined();
        return;
    }

    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);
    const u32 original_Rn = reg.read(Rn_id);

    const u32 address = address_mode.load_store_misc(code);

    const u8 address_low3 = llarm::util::bit_range<u8>(address, 0, 2);
    const bool is_misaligned = (address_low3 != 0b000);

    // ARMv6's Data Access Behavior table (A2-10) formalizes Two-word (LDRD/STRD) alignment
    // faulting: with the A bit set, a word-aligned-but-not-doubleword-aligned address
    // (address_low3 == 0b100) only faults when the U bit (unaligned data access support) is
    // clear; any other misalignment always faults. This rule is ARMv6-specific (prior to
    // ARMv6 this is simply UNPREDICTABLE, which real silicon such as ARM926EJ-S (ARMv5TE)
    // handles by performing both word transfers regardless, per the note below), so it must
    // not apply to earlier architectures.
    if (
        (memory.settings.arch >= id::arch::ARMv6) &&
        (memory.settings.has_alignment_fault_checking) &&
        (coprocessor.read(id::cp15::R1_A))
    ) {
        const bool word_aligned_only = (address_low3 == 0b100);
        const bool permitted = word_aligned_only && coprocessor.read(id::cp15::R1_U);

        if (is_misaligned && !permitted) {
            reg.write(Rn_id, original_Rn);

            if (memory.mmu.is_mmu_enabled()) {
                memory.mmu.manage_abort(id::aborts::ALIGNMENT, address);
            }

            memory.manage_abort(id::aborts::ALIGNMENT);
            return;
        }
    }

    if (
        is_misaligned ||
        (Rd_bits == 14)
    ) {
        // architecturally UNPREDICTABLE (doubleword-misaligned address, or Rd == R14),
        // but real ARM926EJ-S silicon still performs both word transfers rather than
        // dropping the access, and guest code (e.g. musl's memcpy/memset, which only
        // guarantees word alignment) relies on that. Warn, but still carry it out.
        llarm::out::unpredictable("STRD has unpredictable arguments");
    }

    const u64 value = reg.read(Rd_bits);
    const u32 value2 = reg.read(Rd_bits + 1);

    const mem_write_struct access = memory.write(address, value, 4);

    if (access.has_failed) {
        reg.write(Rn_id, original_Rn);
        memory.manage_abort(access.abort_code);
        return;
    }

    const mem_write_struct access2 = memory.write(address + 4, value2, 4);

    if (access2.has_failed) {
        reg.write(Rn_id, original_Rn);
        memory.manage_abort(access2.abort_code);
        return;
    }
}