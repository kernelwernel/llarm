#include "../../instructions/instructions.hpp"
#include "../../core/registers.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>

/**
 * start_address = Rn
 * end_address = Rn + (Number_Of_Set_Bits_In(register_list) * 4) - 4
 * address = start_address
 * for i = 0 to 7
 *    if register_list[i] == 1
 *       Memory[address,4] = Ri
 *       address = address + 4
 * assert end_address == address - 4
 * Rn = Rn + (Number_Of_Set_Bits_In(register_list) * 4)
 */
void INSTRUCTIONS::thumb::store::STMIA(const u16 code) {
    const u8 register_list = llarm::util::bit_range<u8>(code, 0, 7);
    const u32 Rn = reg.read(code, 8, 10);
    const id::reg Rn_id = reg.thumb_fetch_reg_id(code, 8, 10);

    const u32 start_address = Rn;
    const u32 end_address = (Rn + (llarm::util::popcount(register_list) * 4) - 4);

    u32 address = start_address;

    std::vector<id::reg> reg_vec = operation.register_list(register_list);

    for (const id::reg reg_id : reg_vec) {
        const mem_write_struct access = memory.write(reg.read(reg_id), address, 4);

        if (access.has_failed) {
            memory.manage_abort(access.abort_code);
            return;
        }

        address += 4;
    }

    if (end_address != (address - 4)) {
        llarm::out::dev_error("assertation failed in thumb STMIA instruction");
    }

    reg.write(Rn_id, (Rn + (llarm::util::popcount(register_list) * 4)));
}


/**
 * address = Rn + (immed_5 * 4)
 * if address[1:0] == 0b00
 *   Memory[address,4] = Rd
 * else
 *   Memory[address,4] = UNPREDICTABLE
 */
void INSTRUCTIONS::thumb::store::STR1(const u16 code) {
    const u8 immed_5 = llarm::util::bit_range<u8>(code, 6, 10);
    const u32 Rn = reg.read(code, 3, 5);
    const id::reg Rd_id = reg.thumb_fetch_reg_id(code, 0, 2);

    const u32 address = (Rn + (immed_5 * 4));

    u32 value = 0;

    if ((address & 0b11) == 0b00) {
        value = reg.read(Rd_id);
    } else {
        llarm::out::unpredictable("STR1 memory write data");
    }

    const mem_write_struct access = memory.write(value, address, 4);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
    }
}


/**
 * address = Rn + Rm
 * if address[1:0] == 0b00
 *    Memory[address,4] = Rd
 * else
 *    Memory[address,4] = UNPREDICTABLE
 */
void INSTRUCTIONS::thumb::store::STR2(const u16 code) {
    const u32 Rm = reg.read(code, 6, 8);
    const u32 Rn = reg.read(code, 3, 5);
    const id::reg Rd_id = reg.thumb_fetch_reg_id(code, 0, 2);

    const u32 address = (Rn + Rm);

    u32 value = 0;

    if ((address & 0b11) == 0b00) {
        value = reg.read(Rd_id);
    } else {
        llarm::out::unpredictable("STR2 memory write data");
    }
    
    const mem_write_struct access = memory.write(value, address, 4);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
    }
}


/**
 * address = SP + (immed_8 * 4)
 * if address[1:0] == 0b00
 *    Memory[address,4] = Rd
 * else
 *    Memory[address,4] = UNPREDICTABLE
 */
void INSTRUCTIONS::thumb::store::STR3(const u16 code) {
    const u8 immed_8 = llarm::util::bit_range<u8>(code, 0, 7);
    const id::reg Rd_id = reg.thumb_fetch_reg_id(code, 8, 10);

    const u32 address = (reg.read(id::reg::SP) + (immed_8 * 4));

    u32 value = 0;

    if ((address & 0b11) == 0b00) {
        value = reg.read(Rd_id);
    } else {
        llarm::out::unpredictable("STR3 memory write data");
    }

    const mem_write_struct access = memory.write(value, address, 4);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
    }
}


/**
 * address = Rn + immed_5
 * Memory[address,1] = Rd[7:0]
 */
void INSTRUCTIONS::thumb::store::STRB1(const u16 code) {
    const u32 Rd = reg.read(code, 0, 2);
    const u32 Rn = reg.read(code, 3, 5);
    const u8 immed_5 = llarm::util::bit_range<u8>(code, 6, 10);

    const u32 address = (Rn + immed_5);

    const mem_write_struct access = memory.write(llarm::util::bit_range<u8>(Rd, 0, 7), address , 1);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
    }
}


/**
 * address = Rn + Rm
 * Memory[address,1] = Rd[7:0]
 */
void INSTRUCTIONS::thumb::store::STRB2(const u16 code) {
    const u32 Rd = reg.read(code, 0, 2);
    const u32 Rn = reg.read(code, 3, 5);
    const u32 Rm = reg.read(code, 6, 8);

    const u32 address = (Rn + Rm);

    const mem_write_struct access = memory.write(llarm::util::bit_range(Rd, 0, 7), address, 1);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
    }
}


/**
 * address = Rn + (immed_5 * 2)
 * if address[1:0] == 0
 *    Memory[address,2] = Rd[15:0]
 * else
 *    Memory[address,2] = UNPREDICTABLE
 */
void INSTRUCTIONS::thumb::store::STRH1(const u16 code) {
    const u32 Rd = reg.read(code, 0, 2);
    const u32 Rn = reg.read(code, 3, 5);
    const u8 immed_5 = llarm::util::bit_range<u8>(code, 6, 10);

    const u32 address = (Rn + (immed_5 * 2));

    u16 value = 0;

    if ((address & 0b11) == 0) {
        value = llarm::util::bit_range<u16>(Rd, 0, 15);
    } else {
        llarm::out::unpredictable("unpredictable STRH1 memory write data alignment");
    }

    const mem_write_struct access = memory.write(value, address, 2);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
    }
}


/**
 * address = Rn + Rm
 * if address[1:0] == 0
 *    Memory[address,2] = Rd[15:0]
 * else
 *    Memory[address,2] = UNPREDICTABLE
 */
void INSTRUCTIONS::thumb::store::STRH2(const u16 code) {
    const u32 Rd = reg.read(code, 0, 2);
    const u32 Rn = reg.read(code, 3, 5);
    const u32 Rm = reg.read(code, 6, 8);

    const u32 address = (Rn + Rm);

    u16 value = 0;

    if ((address & 0b11) == 0) {
        value = llarm::util::bit_range<u16>(Rd, 0, 15);
    } else {
        llarm::out::unpredictable("unpredictable STRH2 memory write data alignment");
    }

    const mem_write_struct access = memory.write(value, address, 2);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
    }
}


/**
 * start_address = SP - 4*(R + Number_Of_Set_Bits_In(register_list))
 * end_address = SP - 4
 * address = start_address
 * for i = 0 to 7
 *    if register_list[i] == 1
 *       Memory[address,4] = Ri
 *       address = address + 4
 * if R == 1
 *    Memory[address,4] = LR
 *    address = address + 4
 * assert end_address == address - 4
 * SP = SP - 4*(R + Number_Of_Set_Bits_In(register_list))
 */
void INSTRUCTIONS::thumb::store::PUSH(const u16 code) {
    const u8 register_list = llarm::util::bit_range<u8>(code, 0, 7);
    const bool R = llarm::util::bit_fetch(code, 8);

    const u32 SP = reg.read(id::reg::SP);

    const u32 start_address = (SP - static_cast<u32>(4 * (R + llarm::util::popcount(register_list))));
    const u32 end_address = (SP - 4);

    u32 address = start_address;

    std::vector<id::reg> reg_vec = operation.register_list(register_list);

    for (const id::reg reg_id : reg_vec) {
        const mem_write_struct access = memory.write(reg.read(reg_id), address, 4);

        if (access.has_failed) {
            memory.manage_abort(access.abort_code);
            return;
        }

        address += 4;
    }

    if (R == true) {
        const mem_write_struct access = memory.write(reg.read(id::reg::LR), address, 4);

        if (access.has_failed) {
            memory.manage_abort(access.abort_code);
            return;
        }

        address += 4;
    }

    if (end_address != (address - 4)) {
        llarm::out::dev_error("assertation failed in thumb PUSH instruction");
    }

    reg.write(id::reg::SP, (SP - static_cast<u32>(4 * (R + llarm::util::popcount(register_list)))));
}