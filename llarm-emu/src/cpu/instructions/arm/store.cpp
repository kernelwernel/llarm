#include "../instructions.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"


/**
 * if ConditionPassed(cond) then
 *     address = start_address
 *     for i = 0 to 15
 *         if register_list[i] == 1
 *             Memory[address,4] = Ri
 *             address = address + 4
 *     assert end_address == address - 4
 */
void INSTRUCTIONS::arm::store::STM1(const arm_code_t &code) {
    const address_struct addresses = address_mode.load_store_multiple(code);

    u32 address = addresses.start;

    const u16 list = shared::util::bit_range(code, 0, 15);

    std::vector<id::reg> reg_list = operation.register_list(list);

    for (const auto reg_id : reg_list) {
        const memory_struct access = memory.write(reg.read(reg_id), address, 4);

        if (access.has_failed) {
            memory.manage_abort(access.abort_code);
            return;
        }

        address += 4;
    }

    // TODO assert
}


/**
 * if ConditionPassed(cond) then
 *     address = start_address
 *     for i = 0 to 15
 *         if register_list[i] == 1
 *             Memory[address,4] = Ri_usr
 *             address = address + 4
 *     assert end_address == address - 4
 */
void INSTRUCTIONS::arm::store::STM2(const arm_code_t &code) {
    const address_struct addresses = address_mode.load_store_multiple(code);

    u32 address = addresses.start;

    const u16 list = shared::util::bit_range(code, 0, 15);

    std::vector<id::reg> reg_list = operation.register_list(list);

    for (const auto reg_id : reg_list) {
        const u32 value = reg.read(reg_id);
        const memory_struct access = memory.write(value, address, 4);

        if (access.has_failed) {
            memory.manage_abort(access.abort_code);
            return;
        }

        address += 4;
    }
}


/**
 * if ConditionPassed(cond) then
 *     Memory[address,4] = Rd
 */
void INSTRUCTIONS::arm::store::STR(const arm_code_t &code) {
    const u32 address = address_mode.load_store(code); 

    const u32 value = reg.read(code, 12, 15);

    const memory_struct access = memory.write(value, address, 4);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return;
    }
}


/**
 * if ConditionPassed(cond) then
 *     Memory[address,1] = Rd[7:0]
 */
void INSTRUCTIONS::arm::store::STRB(const arm_code_t &code) {
    const u32 address = address_mode.load_store(code); 

    const u32 Rd = reg.read(code, 12, 15);
    const u8 value = shared::util::bit_range(Rd, 0, 7);

    const memory_struct access = memory.write(value, address, 1);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return;
    }
}


/**
 * if ConditionPassed(cond) then
 *     Memory[address,1] = Rd[7:0]
 */
void INSTRUCTIONS::arm::store::STRBT(const arm_code_t &code) {
    const u32 address = address_mode.load_store(code); 

    const u32 Rd = reg.read(code, 12, 15);
    const u8 value = shared::util::bit_range(Rd, 0, 7);

    const memory_struct access = memory.write(value, address, 1);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return;
    }
}


/**
 * if ConditionPassed(cond) then
 *     if address[0] == 0
 *         data = Rd[15:0]
 *     else // address[0] == 1
 *         data = UNPREDICTABLE
 *     Memory[address,2] = data
 */
void INSTRUCTIONS::arm::store::STRH(const arm_code_t &code) {
    const u32 address = address_mode.load_store_misc(code);

    u32 data = 0;

    if ((address & 1) == 0) {
        const u32 Rd = reg.read(code, 12, 15);
        data = shared::util::bit_range(Rd, 0, 15);
    } else {
        // TODO UNPREDICTABLE
    }

    const memory_struct access = memory.write(data, address, 2);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return;
    }
}


/**
 * if ConditionPassed(cond) then
 *     Memory[address,4] = Rd
 */
void INSTRUCTIONS::arm::store::STRT(const arm_code_t &code) {
    const u32 address = address_mode.load_store(code);

    const u32 Rd = reg.read(code, 12, 15);

    const memory_struct access = memory.write(Rd, address, 4);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return;
    }
}


/**
 * if ConditionPassed(cond) then
 *     if Rn[1:0] == 0b00 then
 *         temp = Memory[Rn,4]
 *     else if Rn[1:0] == 0b01 then
 *         temp = Memory[Rn,4] Rotate_Right 8
 *     else if Rn[1:0] == 0b10 then
 *         temp = Memory[Rn,4] Rotate_Right 16
 *     else // Rn[1:0] == 0b11
 *         temp = Memory[Rn,4] Rotate_Right 24
 *     Memory[Rn,4] = Rm
 *     Rd = temp
 */
void INSTRUCTIONS::arm::store::SWP(const arm_code_t &code) {
    const u32 Rn = reg.read(code, 16, 19);

    const u8 type = shared::util::bit_range(Rn, 0, 1);

    u8 rotate = 0;

    switch (type) {
        case 0b00: break;
        case 0b01: rotate = 8; break;
        case 0b10: rotate = 16; break;
        case 0b11: rotate = 24; break;
    }

    const memory_struct read_access = memory.read<u32>(Rn, 4);

    if (read_access.has_failed) {
        memory.manage_abort(read_access.abort_code);
        return;
    }

    const u32 Rm = reg.read(code, 0, 3);
    
    const memory_struct write_access = memory.write<u32>(Rm, Rn, 4);
    
    if (write_access.has_failed) {
        memory.manage_abort(write_access.abort_code);
        return;
    }

    const u32 temp = std::rotr(read_access.value, rotate);
    reg.write(code, 12, 15, temp);
}

/**
 * if ConditionPassed(cond) then
 *     temp = Memory[Rn,1]
 *     Memory[Rn,1] = Rm[7:0]
 *     Rd = temp
 */
void INSTRUCTIONS::arm::store::SWPB(const arm_code_t &code) {
    const u32 Rn = reg.read(code, 16, 19);

    const memory_struct read_access = memory.read<u32>(Rn, 1);

    if (read_access.has_failed) {
        memory.manage_abort(read_access.abort_code);
        return;
    }

    const u32 temp = read_access.value;

    const u32 Rm = reg.read(code, 0, 3);
    const u8 value = shared::util::bit_range(Rm, 0, 7);

    const memory_struct write_access = memory.write(value, Rn, 1);

    if (write_access.has_failed) {
        memory.manage_abort(write_access.abort_code);
        return;
    }
 
    reg.write(code, 12, 15, temp);
}