#pragma once

#include "../../interpreter/IR_struct.hpp"
#include "src/interpreter/operand_struct.hpp"

#include <llarm/shared/types.hpp>

namespace internal::generators {
    u16 imm8(u16 opcode, const operand_struct& operands);
    u16 Rd_Rm(u16 opcode, const operand_struct& operands);
    u16 Rd_imm8(u16 opcode, const operand_struct& operands);
    u16 Rd_Rm_imm3(u16 opcode, const operand_struct& operands);
    u16 Rd_Rm_imm5(u16 opcode, const operand_struct& operands);
    u16 reglist(u16 opcode, const operand_struct& operands);
    u16 Rd_Rn_Rm(u16 opcode, const operand_struct& operands);
    u16 Rm_special(u16 opcode, const operand_struct& operands);
    u16 Rn_preindex_reglist(u16 opcode, const operand_struct& operands);
    u16 Rd_Rn_imm5_2(u16 opcode, const operand_struct& operands);
    u16 Rd_Rn_imm5_4(u16 opcode, const operand_struct& operands);
    u16 Rd_special_imm8_4(u16 opcode, const operand_struct& operands);
    u16 Rd_Rm_special(u16 opcode, const operand_struct& operands);
    u16 SP_imm7_4(u16 opcode, const operand_struct& operands);

    u16 B1(const operand_struct& operands, const u32 PC);
    u16 B2(const operand_struct& operands, const u32 PC);
    u32 BL_BLX1(const operand_struct& operands, const u32 PC, const thumb_id id);

    u32 thumb(const IR_thumb_struct& IR);
}