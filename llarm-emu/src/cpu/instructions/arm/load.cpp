#include "addressing_modes/addressing_modes.hpp"

#include "../../../id.hpp"
#include "../../core/registers.hpp"
#include "../instructions.hpp"

#include <llarm/shared/out.hpp>
#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>


// TODO, ADD CHECK FOR L4 BIT
/**
 * if ConditionPassed(cond) then
 *   address = start_address
 * 
 *   for i = 0 to 14
 *     if register_list[i] == 1 then
 *       Ri = Memory[address,4]
 *       address = address + 4
 * 
 *   if register_list[15] == 1 then
 *     value = Memory[address,4]
 *     if (architecture version 5 or above) then
 *       pc = value AND 0xFFFFFFFE
 *       T Bit = value[0]
 *     else
 *       pc = value AND 0xFFFFFFFC
 *     address = address + 4
 *   assert end_address = address - 4
 */
void INSTRUCTIONS::arm::load::LDM1(const u32 code) {
    const u16 list = llarm::util::bit_range<u16>(code, 0, 15);

    const address_struct addresses = address_mode.load_store_multiple(code);

    u32 address = addresses.start;

    const std::vector<id::reg> reg_list = operation.register_list(list);

    for (const auto reg_id : reg_list) {
        const mem_read_struct access = memory.read(address, 4);
    
        if (access.has_failed) {
            memory.manage_abort(access.abort_code);
            return;
        }

        reg.write(reg_id, llarm::util::bit_range<u32>(access.value, 0, 31));
        address += 4;
    }

    if (llarm::util::bit_fetch(list, 15) == true) {
        const mem_read_struct access = memory.read(address, 4);
    
        if (access.has_failed) {
            memory.manage_abort(access.abort_code);
            return;
        }

        const u32 value = llarm::util::bit_range<u32>(access.value, 0, 31);

        if (settings.arch >= id::arch::ARMv5) {
            reg.write(id::reg::PC, (value & 0xFFFFFFFE));
            reg.write(id::cpsr::T, (value & 1));
        } else {
            reg.write(id::reg::PC, (value & 0xFFFFFFFC));
        }

        address += 4;
    }

    if (addresses.end != address - 4) {
        llarm::out::error("LDM1 assert failed");
    }
}


// TODO, ADD CHECK FOR L4 BIT
/**
 * if ConditionPassed(cond) then
 *     if address[1:0] == 0b00 then
 *         value = Memory[address,4]
 *     else if address[1:0] == 0b01 then
 *         value = Memory[address,4] Rotate_Right 8
 *     else if address[1:0] == 0b10 then
 *         value = Memory[address,4] Rotate_Right 16
 *     else // address[1:0] == 0b11
 *         value = Memory[address,4] Rotate_Right 24
 *     
 *     if (Rd is R15) then
 *         if (architecture version 5 or above) then
 *             PC = value AND 0xFFFFFFFE
 *             T Bit = value[0]
 *         else
 *             PC = value AND 0xFFFFFFFC
 *     else
 *         Rd = value
 */
void INSTRUCTIONS::arm::load::LDR(const u32 code) {
    const u32 address = address_mode.load_store(code);

    const u8 type = llarm::util::bit_range<u8>(address, 0, 1);

    const mem_read_struct access = memory.read(address, 4);
    
    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return;
    }

    const u32 data = llarm::util::bit_range<u32>(access.value, 0, 31);

    u32 value = 0;

    switch (type) {
        case 0b00: value = data; break;
        case 0b01: value = llarm::util::rotr(data, 8); break;
        case 0b10: value = llarm::util::rotr(data, 16); break;
        case 0b11: value = llarm::util::rotr(data, 24); break;
    }

    if (reg.fetch_reg_id(code, 12, 15) == id::reg::R15) {
        if (settings.arch >= id::arch::ARMv5) {
            reg.write(id::reg::PC, (value & 0xFFFFFFFE));
            reg.write(id::cpsr::T, (value & 1));
        } else {
            reg.write(id::reg::PC, (value & 0xFFFFFFFC));
        }
    } else {
        reg.write(code, 12, 15, value);
    }
}


/**
 * if ConditionPassed(cond) then
 *     Rd = Memory[address,1]
 */
void INSTRUCTIONS::arm::load::LDRB(const u32 code) {
    const u32 address = address_mode.load_store(code);

    const mem_read_struct access = memory.read(address, 1);
    
    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return;
    }

    reg.write(code, 12, 15, llarm::util::bit_range<u32>(access.value, 0, 7));
}


/**
 * if ConditionPassed(cond) then
 *     Rd = Memory[address,1]
 */
void INSTRUCTIONS::arm::load::LDRBT(const u32 code) {
    const u32 address = address_mode.load_store(code);

    const mem_read_struct access = memory.read(address, 1);
    
    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return;
    }

    reg.write(code, 12, 15, llarm::util::bit_range<u32>(access.value, 0, 31));
}


/**
 * if ConditionPassed(cond) then
 *     if address[0] == 0
 *         data = Memory[address,2]
 *     else // address[0] == 1
 *         data = UNPREDICTABLE
 *     Rd = data
 */
void INSTRUCTIONS::arm::load::LDRH(const u32 code) {
    const u32 address = address_mode.load_store_misc(code);

    u16 data = 0;

    if ((address & 1) == 0) {
        const mem_read_struct access = memory.read(address, 2);
        
        if (access.has_failed) {
            memory.manage_abort(access.abort_code);
            return;
        }

        data = llarm::util::bit_range<u16>(access.value, 0, 15);
    } else {
        llarm::out::unpredictable("LDRH data assignment");
    }

    reg.write(code, 12, 15, data);
}


/**
 * if ConditionPassed(cond) then
 *     data = Memory[address,1]
 *     Rd = SignExtend(data)
 */
void INSTRUCTIONS::arm::load::LDRSB(const u32 code) {
    const u32 address = address_mode.load_store_misc(code);

    const mem_read_struct access = memory.read(address, 1);
        
    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return;
    }

    const u8 value = llarm::util::bit_range<u8>(access.value, 0, 7);

    reg.write(code, 12, 15, static_cast<u32>(operation.sign_extend(value, 7)));
}


/**
 * if ConditionPassed(cond) then
 *     if address[0] == 0
 *         data = Memory[address,2]
 *     else // address[0] == 1
 *         data = UNPREDICTABLE
 *     Rd = SignExtend(data)
 */
void INSTRUCTIONS::arm::load::LDRSH(const u32 code) {
    const u32 address = address_mode.load_store_misc(code);

    u16 data = 0;

    if ((address & 1) == 0) {
        const mem_read_struct access = memory.read(address, 2);

        if (access.has_failed) {
            memory.manage_abort(access.abort_code);
            return;
        }

        data = llarm::util::bit_range<u16>(access.value, 0, 15);
    } else {
        llarm::out::unpredictable("LDRSH data assignment");
    }

    reg.write(code, 12, 15, static_cast<u32>(operation.sign_extend(data, 15)));
}


/**
 * if ConditionPassed(cond) then
 *     if address[1:0] == 0b00
 *         Rd = Memory[address,4]
 *     else if address[1:0] == 0b01
 *         Rd = Memory[address,4] Rotate_Right 8
 *     else if address[1:0] == 0b10
 *         Rd = Memory[address,4] Rotate_Right 16
 *     else // address[1:0] == 0b11
 *         Rd = Memory[address,4] Rotate_Right 24
 */
void INSTRUCTIONS::arm::load::LDRT(const u32 code) {
    const u32 address = address_mode.load_store(code);
    
    const mem_read_struct access = memory.read(address, 4);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return;
    }

    const u32 data = llarm::util::bit_range(access.value, 0, 31);

    u32 value = 0;

    const u8 type = llarm::util::bit_range<u8>(address, 0, 1);

    switch (type) {
        case 0b00: value = data; break;
        case 0b01: value = llarm::util::rotr(data, 8); break;
        case 0b10: value = llarm::util::rotr(data, 16); break;
        case 0b11: value = llarm::util::rotr(data, 24); break;
    }

    reg.write(code, 12, 15, value);
}


/**
 * if ConditionPassed(cond) then
 *     address = start_address
 *     for i = 0 to 14
 *         if register_list[i] == 1
 *             Ri_usr = Memory[address,4]
 *             address = address + 4
 *     assert end_address == address - 4
 */
void INSTRUCTIONS::arm::load::LDM2(const u32 code) {
    const address_struct addresses = address_mode.load_store_multiple(code);

    u32 address = addresses.start;

    const u16 list = llarm::util::bit_range<u16>(code, 0, 14);

    std::vector<id::reg> reg_list = operation.register_list(list);

    for (const auto reg_id : reg_list) {
        const mem_read_struct access = memory.read(address, 4);

        if (access.has_failed) {
            memory.manage_abort(access.abort_code);
            return;
        }
    
        reg.write(reg_id, llarm::util::bit_range(access.value, 0, 31));
        address += 4;
    }

    if (addresses.end != address - 4) {
        llarm::out::error("LDM2 assert failed");
    }
}


/**
 * if ConditionPassed(cond) then
 *     address = start_address
 *     
 *     for i = 0 to 14
 *         if register_list[i] == 1 then
 *             Ri = Memory[address,4]
 *             address = address + 4
 * 
 *     CPSR = SPSR
 * 
 *     value = Memory[address,4]
 *     if (architecture version 4T, 5 or above) and (T Bit == 1) then
 *         pc = value AND 0xFFFFFFFE
 *     else
 *         pc = value AND 0xFFFFFFFC
 *     address = address + 4
 *     
 *     assert end_address = address - 4
 */
void INSTRUCTIONS::arm::load::LDM3(const u32 code) {
    const address_struct addresses = address_mode.load_store_multiple(code);

    u32 address = addresses.start;

    const u16 list = llarm::util::bit_range<u16>(code, 0, 14);

    std::vector<id::reg> reg_list = operation.register_list(list);

    for (const auto reg_id : reg_list) {
        const mem_read_struct access = memory.read(address, 4);

        if (access.has_failed) {
            memory.manage_abort(access.abort_code);
            return;
        }
    
        reg.write(reg_id, llarm::util::bit_range(access.value, 0, 31));
        address += 4;
    }

    reg.write(id::reg::CPSR, id::reg::SPSR);

    const mem_read_struct access = memory.read(address, 4);

    if (access.has_failed) {
        memory.manage_abort(access.abort_code);
        return;
    }

    const u32 value = llarm::util::bit_range(access.value, 0, 31);

    if (
        (settings.specific_arch >= id::specific_arch::ARMv4T) &&
        (reg.read(id::cpsr::T) == true)
    ) {
        reg.write(id::reg::PC, (value & 0xFFFFFFFE));
    } else {
        reg.write(id::reg::PC, (value & 0xFFFFFFFC));
    }

    address += 4;

    if (addresses.end != address - 4) {
        llarm::out::error("LDM3 assert failed");
    }
}