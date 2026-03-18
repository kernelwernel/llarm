#include "../../instructions/instructions.hpp"
#include "../../core/registers.hpp"

#include <llarm/shared/out.hpp>
#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>

/**
 * start_address = Rn
 * end_address = Rn + (Number_Of_Set_Bits_In(register_list) * 4) - 4
 * address = start_address
 * for i = 0 to 7
 *    if register_list[i] == 1
 *       Ri = Memory[address,4]
 *       address = address + 4
 * assert end_address == address - 4
 * Rn = Rn + (Number_Of_Set_Bits_In(register_list) * 4)
 */
void INSTRUCTIONS::thumb::load::LDMIA(const u16 code) {
    const u8 register_list = llarm::util::bit_range<u8>(code, 0, 7);
    const u32 Rn = reg.read(code, 8, 10);
    const id::reg Rn_id = reg.thumb_fetch_reg_id(code, 8, 10);

    const u32 start_address = Rn;
    const u32 end_address = (Rn + (llarm::util::popcount(register_list) * 4) - 4);

    u32 address = start_address;

    std::vector<id::reg> reg_vec = operation.register_list(register_list);

    for (const id::reg reg_id : reg_vec) {
        const mem_read_struct access = memory.read(address, 4);

        if (access.has_failed) {
            memory.manage_abort(access.abort_code);
            return;
        }

        reg.write(reg_id, static_cast<u32>(access.value));

        address += 4;
    }

    if (end_address != (address - 4)) {
        llarm::out::dev_error("assertation failed in thumb LDMIA instruction");
    }

    reg.write(Rn_id, (Rn + (llarm::util::popcount(register_list) * 4)));
}


/**
 * address = Rn + (immed_5 * 4)
 * if address[1:0] == 0b00
 *    data = Memory[address,4]
 * else
 *    data = UNPREDICTABLE
 * Rd = data
 */
void INSTRUCTIONS::thumb::load::LDR1(const u16 code) {
    const u8 immed_5 = llarm::util::bit_range<u8>(code, 6, 10);
    const u32 Rn = reg.read(code, 3, 5);
    const id::reg Rd_id = reg.thumb_fetch_reg_id(code, 0, 2);

    const u32 address = (Rn + (immed_5 * 4));

    u32 value = 0;

    if ((address & 0b11) != 0b00) {
        llarm::out::unpredictable("unpredictable alignment in LDR1 instruction");
        reg.write(Rd_id, 0);
        return;
    }

    const mem_read_struct access = memory.read(address, 4);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return;
    }

    reg.write(Rd_id, static_cast<u32>(access.value));
}


/**
 * address = Rn + Rm
 * if address[1:0] == 0b00
 *    data = Memory[address,4]
 * else
 *    data = UNPREDICTABLE
 * Rd = data
 */
void INSTRUCTIONS::thumb::load::LDR2(const u16 code) {
    const id::reg Rd_id = reg.thumb_fetch_reg_id(code, 0, 2);
    const u32 Rn = reg.read(code, 3, 5);
    const u32 Rm = reg.read(code, 6, 8);

    const u32 address = (Rn + Rm);

    if ((address & 0b11) != 0b00) {
        llarm::out::unpredictable("unpredictable alignment in LDR2 instruction");
        reg.write(Rd_id, 0);
        return;
    }

    const mem_read_struct access = memory.read(address, 4);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return;
    }

    reg.write(Rd_id, static_cast<u32>(access.value));
}


/**
 * address = (PC[31:2] << 2) + (immed_8 * 4)
 * Rd = Memory[address, 4]
 */
void INSTRUCTIONS::thumb::load::LDR3(const u16 code) {
    const u8 immed_8 = llarm::util::bit_range<u8>(code, 0, 7);
    const id::reg Rd_id = reg.thumb_fetch_reg_id(code, 8, 10);

    // lord have mercy
    const u32 address = (llarm::util::bit_range(reg.read(id::reg::PC), 2, 31) << 2) + (immed_8 * 4);

    const mem_read_struct access = memory.read(address, 4);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return;
    }

    reg.write(Rd_id, static_cast<u32>(access.value));
}


/**
 * address = SP + (immed_8 * 4)
 * if address[1:0] == 0b00
 *    data = Memory[address,4]
 * else
 *    data = UNPREDICTABLE
 * Rd = data
 */
void INSTRUCTIONS::thumb::load::LDR4(const u16 code) {
    const u8 immed_8 = llarm::util::bit_range<u8>(code, 0, 7);
    const id::reg Rd_id = reg.thumb_fetch_reg_id(code, 8, 10);

    const u32 address = reg.read(id::reg::SP) + (immed_8 * 4);

    if ((address & 0b11) != 0b00) {
        llarm::out::unpredictable("unpredictable alignment in LDR4 instruction");
        reg.write(Rd_id, 0);
        return;
    }

    const mem_read_struct access = memory.read(address, 4);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return;
    }

    reg.write(Rd_id, static_cast<u32>(access.value));
}


/**
 * address = Rn + immed_5
 * Rd = Memory[address,1]
 */
void INSTRUCTIONS::thumb::load::LDRB1(const u16 code) {
    const id::reg Rd_id = reg.thumb_fetch_reg_id(code, 0, 2);
    const u32 Rn = reg.read(code, 3, 5);
    const u8 immed_5 = llarm::util::bit_range<u8>(code, 6, 10);

    const u32 address = Rn + immed_5;

    const mem_read_struct access = memory.read(address, 1);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return;
    }

    reg.write(Rd_id, static_cast<u32>(access.value));
}


/**
 * address = Rn + Rm
 * Rd = Memory[address,1]
 */
void INSTRUCTIONS::thumb::load::LDRB2(const u16 code) {
    const id::reg Rd_id = reg.thumb_fetch_reg_id(code, 0, 2);
    const u32 Rn = reg.read(code, 3, 5);
    const u32 Rm = reg.read(code, 6, 8);

    const u32 address = Rn + Rm;

    const mem_read_struct access = memory.read(address, 1);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return;
    }

    reg.write(Rd_id, static_cast<u32>(access.value));
}


/**
 * address = Rn + (immed_5 * 2)
 * if address[0] == 0
 *    data = Memory[address,2]
 * else
 *    data = UNPREDICTABLE
 * Rd = data
 */
void INSTRUCTIONS::thumb::load::LDRH1(const u16 code) {
    const id::reg Rd_id = reg.thumb_fetch_reg_id(code, 0, 2);
    const u32 Rn = reg.read(code, 3, 5);
    const u8 immed_5 = llarm::util::bit_range<u8>(code, 6, 10);

    const u32 address = (Rn + (immed_5 * 2));

    if ((address & 1) != 0) {
        llarm::out::unpredictable("unpredictable alignment in LDRH1 instruction");
        reg.write(Rd_id, 0);
        return;
    }

    const mem_read_struct access = memory.read(address, 2);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return;
    }

    reg.write(Rd_id, static_cast<u32>(access.value));
}


/**
 * address = Rn + Rm
 * if address[0] == 0
 *    data = Memory[address,2]
 * else
 *    data = UNPREDICTABLE
 * Rd = data
 */
void INSTRUCTIONS::thumb::load::LDRH2(const u16 code) {
    const id::reg Rd_id = reg.thumb_fetch_reg_id(code, 0, 2);
    const u32 Rn = reg.read(code, 3, 5);
    const u32 Rm = reg.read(code, 6, 8);

    const u32 address = (Rn + Rm);

    if ((address & 1) != 0) {
        llarm::out::unpredictable("unpredictable alignment in LDRH2 instruction");
        reg.write(Rd_id, 0);
        return;
    }

    const mem_read_struct access = memory.read(address, 2);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return;
    }

    reg.write(Rd_id, static_cast<u32>(access.value));
}


/**
 * address = Rn + Rm
 * Rd = SignExtend(Memory[address,1])
 */
void INSTRUCTIONS::thumb::load::LDRSB(const u16 code) {
    const id::reg Rd_id = reg.thumb_fetch_reg_id(code, 0, 2);
    const u32 Rn = reg.read(code, 3, 5);
    const u32 Rm = reg.read(code, 6, 8);

    const u32 address = (Rn + Rm);

    const mem_read_struct access = memory.read(address, 1);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return;
    }

    reg.write(Rd_id, u32(operation.sign_extend(static_cast<u32>(access.value))));
}


/**
 * address = Rn + Rm
 * if address[0] == 0
 *    data = Memory[address,2]
 * else
 *    data = UNPREDICTABLE
 * Rd = SignExtend(data)
 */
void INSTRUCTIONS::thumb::load::LDRSH(const u16 code) {
    const id::reg Rd_id = reg.thumb_fetch_reg_id(code, 0, 2);
    const u32 Rn = reg.read(code, 3, 5);
    const u32 Rm = reg.read(code, 6, 8);

    const u32 address = (Rn + Rm);

    if ((address & 1) != 0) {
        llarm::out::unpredictable("unpredictable alignment in LDRSH instruction");
        reg.write(Rd_id, 0);
        return;
    }

    const mem_read_struct access = memory.read(address, 2);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return;
    }

    reg.write(Rd_id, u32(operation.sign_extend(static_cast<u32>(access.value))));
}


/**
 * start_address = SP
 * end_address = SP + 4*(R + Number_Of_Set_Bits_In(register_list))
 * address = start_address
 * 
 * for i = 0 to 7
 *    if register_list[i] == 1 then
 *       Ri = Memory[address,4]
 *       address = address + 4
 * 
 * if R == 1 then
 *    value = Memory[address,4]
 *    PC = value AND 0xFFFFFFFE
 *    if (architecture version 5 or above) then
 *       T Bit = value[0]
 *    address = address + 4
 *
 * assert end_address = address
 * SP = end_address
 */
void INSTRUCTIONS::thumb::load::POP(const u16 code) {
    const u8 register_list = llarm::util::bit_range<u8>(code, 0, 7);
    const bool R = llarm::util::bit_fetch(code, 8);

    const u32 SP = reg.read(id::reg::SP);

    const u32 start_address = SP;
    const u32 end_address = SP + static_cast<u32>(4 * (R + llarm::util::popcount(register_list)));

    u32 address = start_address;

    std::vector<id::reg> reg_vec = operation.register_list(register_list);

    for (const id::reg reg_id : reg_vec) {
        const mem_read_struct access = memory.read(address, 4);

        if (access.has_failed) {
            memory.manage_abort(access.abort_code);
            return;
        }

        reg.write(reg_id, static_cast<u32>(access.value));
        address += 4;
    }

    if (R == 1) {
        const mem_read_struct access = memory.read(address, 4);

        if (access.has_failed) {
            memory.manage_abort(access.abort_code);
            return;
        }

        const u32 value = static_cast<u32>(access.value);

        reg.write(id::reg::PC, value & 0xFFFFFFFE);

        if (settings.arch >= id::arch::ARMv5) {
            reg.write(id::cpsr::T, (value & 1));
        }

        address += 4;
    }

    if (end_address != address) {
        llarm::out::dev_error("assertation failed in thumb POP instruction");
    }

    reg.write(id::reg::SP, end_address);
}