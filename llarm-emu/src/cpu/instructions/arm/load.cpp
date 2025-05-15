#include "shared/types.hpp"
#include "../../../id.hpp"
#include "../../core/registers.hpp"
#include "../instructions.hpp"

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
void INSTRUCTIONS::arm::load::LDM1(const arm_code_t &code) {
    
 //       const u8 register_list = shared::util::bit_range<u8>(code, 0, 7);
 //       const u32 Rn = reg.read(code, 8, 10);
 //       const id::reg Rn_id = reg.fetch_reg_id(code, 8, 10);
 //   
 //       const u32 start_address = Rn;
 //       const u32 end_address = (Rn + (std::popcount(register_list) * 4) - 4);
 //   
 //       u32 address = start_address;
 //   
 //       std::vector<id::reg> reg_vec = operation.register_list(register_list);
 //   
 //       for (const id::reg reg_id : reg_vec) {
 //           const memory_struct access = memory.write(reg.read(reg_id), address, 4);
 //   
 //           if (access.has_failed) {
 //               memory.manage_abort(access.abort_code);
 //               return;
 //           }
 //   
 //           address += 4;
 //       }
 //   
 //       if (end_address != (address - 4)) {
 //           // TODO idk, do an assertation handler
 //       }
 //   
 //       reg.write(Rn_id, (Rn + (std::popcount(register_list) * 4)));
 //   
 //       reg.thumb_increment_PC();
}










void INSTRUCTIONS::arm::load::LDM2(const arm_code_t&) {} // TODO
void INSTRUCTIONS::arm::load::LDM3(const arm_code_t&) {} // TODO
void INSTRUCTIONS::arm::load::LDR(const arm_code_t&) {} // TODO, ADD CHECK FOR L4 BIT
void INSTRUCTIONS::arm::load::LDRB(const arm_code_t&) {} // TODO
void INSTRUCTIONS::arm::load::LDRBT(const arm_code_t&) {} // TODO
void INSTRUCTIONS::arm::load::LDRH(const arm_code_t&) {} // TODO
void INSTRUCTIONS::arm::load::LDRSB(const arm_code_t&) {} // TODO
void INSTRUCTIONS::arm::load::LDRSH(const arm_code_t&) {} // TODO
void INSTRUCTIONS::arm::load::LDRT(const arm_code_t&) {} // TODO