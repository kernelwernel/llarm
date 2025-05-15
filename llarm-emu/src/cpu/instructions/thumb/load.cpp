#include "shared/types.hpp"
#include "../../../utility.hpp"
#include "../../instructions/instructions.hpp"
#include "../../core/registers.hpp"

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
void INSTRUCTIONS::thumb::load::LDMIA(const thumb_code_t &code) {
    const u8 register_list = shared::util::bit_range<u8>(code, 0, 7);
    const u32 Rn = reg.read(code, 8, 10);
    const id::reg Rn_id = reg.fetch_reg_id(code, 8, 10);

    const u32 start_address = Rn;
    const u32 end_address = (Rn + (std::popcount(register_list) * 4) - 4);

    u32 address = start_address;

    std::vector<id::reg> reg_vec = operation.register_list(register_list);

    for (const id::reg reg_id : reg_vec) {
        const memory_struct access = memory.read<u32>(address, 4);

        if (access.has_failed) {
            memory.manage_abort(access.abort_code);
            return;
        }

        reg.write(reg_id, access.value);

        address += 4;
    }

    if (end_address != (address - 4)) {
        // TODO idk, do an assertation handler
    }

    reg.write(Rn_id, (Rn + (std::popcount(register_list) * 4)));

    reg.thumb_increment_PC();
}


/**
 * address = Rn + (immed_5 * 4)
 * if address[1:0] == 0b00
 *    data = Memory[address,4]
 * else
 *    data = UNPREDICTABLE
 * Rd = data
 */
void INSTRUCTIONS::thumb::load::LDR1(const thumb_code_t &code) {
    const u8 immed_5 = shared::util::bit_range<u8>(code, 6, 10);
    const u32 Rn = reg.read(code, 3, 5);
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);

    const u32 address = (Rn + (immed_5 * 4));

    u32 value = 0;

    if ((address & 0b11) == 0b00) {
        const memory_struct access = memory.read<u32>(address, 4);

        if (access.has_failed) {
            memory.manage_abort(access.abort_code);
            return;
        }

        value = access.value;
    } else {
        // UNPREDICTABLE, TODO
    }

    reg.write(Rd_id, value);

    reg.thumb_increment_PC();
}


/**
 * address = Rn + Rm
 * if address[1:0] == 0b00
 *    data = Memory[address,4]
 * else
 *    data = UNPREDICTABLE
 * Rd = data
 */
void INSTRUCTIONS::thumb::load::LDR2(const thumb_code_t &code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);
    const u32 Rn = reg.read(code, 3, 5);
    const u32 Rm = reg.read(code, 6, 8);

    const u32 address = (Rn + Rm);

    u32 value = 0;

    if ((address & 0b11) == 0b00) {
        const memory_struct access = memory.read<u32>(address, 4);

        if (access.has_failed) {
            memory.manage_abort(access.abort_code);
            return;
        }

        value = access.value;
    } else {
        // UNPREDICTABLE, TODO
    }
    
    reg.write(Rd_id, value);

    reg.thumb_increment_PC();
}


/**
 * address = (PC[31:2] << 2) + (immed_8 * 4)
 * Rd = Memory[address, 4]
 */
void INSTRUCTIONS::thumb::load::LDR3(const thumb_code_t &code) {
    const u8 immed_8 = shared::util::bit_range<u8>(code, 0, 7);
    const id::reg Rd_id = reg.fetch_reg_id(code, 8, 10);

    // lord have mercy
    const u32 address = (shared::util::bit_range(reg.read(id::reg::PC), 2, 31) << 2) + (immed_8 * 4);

    const memory_struct access = memory.read<u32>(address, 4);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return;
    }

    reg.write(Rd_id, access.value);

    reg.thumb_increment_PC();
}


/**
 * address = SP + (immed_8 * 4)
 * if address[1:0] == 0b00
 *    data = Memory[address,4]
 * else
 *    data = UNPREDICTABLE
 * Rd = data
 */
void INSTRUCTIONS::thumb::load::LDR4(const thumb_code_t &code) {
    const u8 immed_8 = shared::util::bit_range<u8>(code, 0, 7);
    const id::reg Rd_id = reg.fetch_reg_id(code, 8, 10);

    const u32 address = reg.read(id::reg::SP) + (immed_8 * 4);

    u32 value = 0;

    if ((address & 0b11) == 0b00) {
        const memory_struct access = memory.read<u32>(address, 4);

        if (access.has_failed) {
            memory.manage_abort(access.abort_code);
            return;
        }

        value = access.value;
    } else {
        // UNPREDICTABLE, TODO
    }

    reg.write(Rd_id, value);

    reg.thumb_increment_PC();
}


/**
 * address = Rn + immed_5
 * Rd = Memory[address,1]
 */
void INSTRUCTIONS::thumb::load::LDRB1(const thumb_code_t &code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);
    const u32 Rn = reg.read(code, 3, 5);
    const u8 immed_5 = shared::util::bit_range<u8>(code, 6, 10);

    const u32 address = Rn + immed_5;

    const memory_struct access = memory.read<u8>(address, 1);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return;
    }

    reg.write(Rd_id, access.value);

    reg.thumb_increment_PC();
}


/**
 * address = Rn + Rm
 * Rd = Memory[address,1]
 */
void INSTRUCTIONS::thumb::load::LDRB2(const thumb_code_t &code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);
    const u32 Rn = reg.read(code, 3, 5);
    const u32 Rm = reg.read(code, 6, 8);

    const u32 address = Rn + Rm;

    const memory_struct access = memory.read<u8>(address, 1);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return;
    }

    reg.write(Rd_id, access.value);

    reg.thumb_increment_PC();
}


/**
 * address = Rn + (immed_5 * 2)
 * if address[0] == 0
 *    data = Memory[address,2]
 * else
 *    data = UNPREDICTABLE
 * Rd = data
 */
void INSTRUCTIONS::thumb::load::LDRH1(const thumb_code_t &code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);
    const u32 Rn = reg.read(code, 3, 5);
    const u8 immed_5 = shared::util::bit_range<u8>(code, 6, 10);

    const u32 address = (Rn + (immed_5 * 2));

    u16 value = 0;

    if ((address & 1) == 0) {
        const memory_struct access = memory.read<u16>(address, 2);

        if (access.has_failed) {
            memory.manage_abort(access.abort_code);
            return;
        }

        value = access.value;
    } else {
        // UNPREDICTABLE, TODO
    }

    reg.write(Rd_id, value);

    reg.thumb_increment_PC();
}


/**
 * address = Rn + Rm
 * if address[0] == 0
 *    data = Memory[address,2]
 * else
 *    data = UNPREDICTABLE
 * Rd = data
 */
void INSTRUCTIONS::thumb::load::LDRH2(const thumb_code_t &code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);
    const u32 Rn = reg.read(code, 3, 5);
    const u32 Rm = reg.read(code, 6, 8);

    const u32 address = (Rn + Rm);

    u16 value = 0;

    if ((address & 1) == 0) {
        const memory_struct access = memory.read<u16>(address, 2);

        if (access.has_failed) {
            memory.manage_abort(access.abort_code);
            return;
        }

        value = access.value;
    } else {
        // UNPREDICTABLE, TODO
    }
    
    reg.write(Rd_id, value);

    reg.thumb_increment_PC();
}


/**
 * address = Rn + Rm
 * Rd = SignExtend(Memory[address,1])
 */
void INSTRUCTIONS::thumb::load::LDRSB(const thumb_code_t &code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);
    const u32 Rn = reg.read(code, 3, 5);
    const u32 Rm = reg.read(code, 6, 8);

    const u32 address = (Rn + Rm);

    const memory_struct access = memory.read<u8>(address, 1);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return;
    }

    reg.write(Rd_id, operation.sign_extend(access.value));

    reg.thumb_increment_PC();
}


/**
 * address = Rn + Rm
 * if address[0] == 0
 *    data = Memory[address,2]
 * else
 *    data = UNPREDICTABLE
 * Rd = SignExtend(data)
 */
void INSTRUCTIONS::thumb::load::LDRSH(const thumb_code_t &code) {
    const id::reg Rd_id = reg.fetch_reg_id(code, 0, 2);
    const u32 Rn = reg.read(code, 3, 5);
    const u32 Rm = reg.read(code, 6, 8);

    const u32 address = (Rn + Rm);

    u16 value = 0;

    if ((address & 1) == 0) {
        const memory_struct access = memory.read<u16>(address, 2);

        if (access.has_failed) {
            memory.manage_abort(access.abort_code);
            return;
        }

        value = access.value;
    } else {
        // UNPREDICTABLE, TODO
    }

    reg.write(Rd_id, operation.sign_extend(value));

    reg.thumb_increment_PC();
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
void INSTRUCTIONS::thumb::load::POP(const thumb_code_t &code) {
    const u8 register_list = shared::util::bit_range<u8>(code, 0, 7);
    const bool R = code.test(8);

    const u32 SP = reg.read(id::reg::SP);

    const u32 start_address = SP;
    const u32 end_address = SP + (4 * (R + std::popcount(register_list)));

    u32 address = start_address;

    std::vector<id::reg> reg_vec = operation.register_list(register_list);

    for (const id::reg reg_id : reg_vec) {
        const memory_struct access = memory.read<u32>(address, 4);

        if (access.has_failed) {
            memory.manage_abort(access.abort_code);
            return;
        }

        reg.write(reg_id, access.value);
        address += 4;
    }

    if (R == 1) {
        const memory_struct access = memory.read<u32>(address, 4);

        if (access.has_failed) {
            memory.manage_abort(access.abort_code);
            return;
        }

        const u32 value = access.value;

        reg.write(id::reg::PC, value & 0xFFFFFFFE);

        // "if ARMv5 or above"
        if (static_cast<u8>(settings.arch) >= 5) {
            reg.write(id::cpsr::T, (value & 1));
        }

        address += 4;
    }

    if (end_address != address) {
        // TODO idk, do an assertation handler
    }

    reg.write(id::reg::SP, end_address);

    reg.thumb_increment_PC();
}
