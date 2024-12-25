#include "id.hpp"
#include "cpu/opcodes.hpp"
#include "cpu/instruction_set.hpp"
#include "cpu/instructions.hpp"
#include "cpu/core/registers.hpp"
#include "cpu/memory.hpp"



INSTRUCTION_SET::INSTRUCTION_SET(REGISTERS& reg, MEMORY& memory) : reg(reg), memory(memory) {
    arm_table = {
        { id::instruction::NOP, { opcodes::NOP, instructions::misc::NOP } }
    };

    thumb_table = {
        // math
        { id::instruction::T_ADC,   { opcodes::thumb::ADC,   instructions::thumb::math::ADC } },
        { id::instruction::T_ADD1,  { opcodes::thumb::ADD1,  instructions::thumb::math::ADD1 } },
        { id::instruction::T_ADD2,  { opcodes::thumb::ADD2,  instructions::thumb::math::ADD2 } },
        { id::instruction::T_ADD3,  { opcodes::thumb::ADD3,  instructions::thumb::math::ADD3 } },
        { id::instruction::T_ADD4,  { opcodes::thumb::ADD4,  instructions::thumb::math::ADD4 } },
        { id::instruction::T_ADD5,  { opcodes::thumb::ADD5,  instructions::thumb::math::ADD5 } },
        { id::instruction::T_ADD6,  { opcodes::thumb::ADD6,  instructions::thumb::math::ADD6 } },
        { id::instruction::T_ADD7,  { opcodes::thumb::ADD7,  instructions::thumb::math::ADD7 } },
        { id::instruction::T_SBC,   { opcodes::thumb::SBC,   instructions::thumb::math::SBC } },
        { id::instruction::T_SUB1,  { opcodes::thumb::SUB1,  instructions::thumb::math::SUB1 } },
        { id::instruction::T_SUB2,  { opcodes::thumb::SUB2,  instructions::thumb::math::SUB2 } },
        { id::instruction::T_SUB3,  { opcodes::thumb::SUB3,  instructions::thumb::math::SUB3 } },
        { id::instruction::T_SUB4,  { opcodes::thumb::SUB4,  instructions::thumb::math::SUB4 } },
        { id::instruction::T_MUL,   { opcodes::thumb::MUL,   instructions::thumb::math::MUL } },

        // logic
        { id::instruction::T_AND,   { opcodes::thumb::AND,   instructions::thumb::logic::AND } },
        { id::instruction::T_ASR1,  { opcodes::thumb::ASR1,  instructions::thumb::logic::ASR1 } },
        { id::instruction::T_ASR2,  { opcodes::thumb::ASR2,  instructions::thumb::logic::ASR2 } },
        { id::instruction::T_BIC,   { opcodes::thumb::BIC,   instructions::thumb::logic::BIC } },
        { id::instruction::T_EOR,   { opcodes::thumb::EOR,   instructions::thumb::logic::EOR } },
        { id::instruction::T_LSL1,  { opcodes::thumb::LSL1,  instructions::thumb::logic::LSL1 } },
        { id::instruction::T_LSL2,  { opcodes::thumb::LSL2,  instructions::thumb::logic::LSL2 } },
        { id::instruction::T_LSR1,  { opcodes::thumb::LSR1,  instructions::thumb::logic::LSR1 } },
        { id::instruction::T_LSR2,  { opcodes::thumb::LSR2,  instructions::thumb::logic::LSR2 } },
        { id::instruction::T_NEG,   { opcodes::thumb::NEG,   instructions::thumb::logic::NEG } },
        { id::instruction::T_ORR,   { opcodes::thumb::ORR,   instructions::thumb::logic::ORR } },
        { id::instruction::T_ROR,   { opcodes::thumb::ROR,   instructions::thumb::logic::ROR } },
        { id::instruction::T_TST,   { opcodes::thumb::TST,   instructions::thumb::logic::TST } },

        // comparison
        { id::instruction::T_CMN,   { opcodes::thumb::CMN,   instructions::thumb::compare::CMN } },
        { id::instruction::T_CMP1,  { opcodes::thumb::CMP1,  instructions::thumb::compare::CMP1 } },
        { id::instruction::T_CMP2,  { opcodes::thumb::CMP2,  instructions::thumb::compare::CMP2 } },
        { id::instruction::T_CMP3,  { opcodes::thumb::CMP3,  instructions::thumb:: compare::CMP3} },

        // movement
        { id::instruction::T_MOV1,  { opcodes::thumb::MOV1,  instructions::thumb::movement::MOV1 } },
        { id::instruction::T_MOV2,  { opcodes::thumb::MOV2,  instructions::thumb::movement::MOV2 } },
        { id::instruction::T_MOV3,  { opcodes::thumb::MOV3,  instructions::thumb::movement::MOV3 } },
        { id::instruction::T_MVN,   { opcodes::thumb::MVN,   instructions::thumb::movement::MVN } },

        // branching
        { id::instruction::T_B1,    { opcodes::thumb::B1,    instructions::thumb::branching::B1 } },
        { id::instruction::T_B2,    { opcodes::thumb::B2,    instructions::thumb::branching::B2 } },
        { id::instruction::T_BL,    { opcodes::thumb::BL,    instructions::thumb::branching::BL } },
        { id::instruction::T_BX,    { opcodes::thumb::BX,    instructions::thumb::branching::BX } },

        // misc
        { id::instruction::T_NOP,   { opcodes::thumb::NOP,   instructions::thumb::misc::NOP } },
        { id::instruction::T_SWI,   { opcodes::thumb::SWI,   instructions::thumb::misc::SWI } },

        // load
        { id::instruction::T_LDMIA, { opcodes::thumb::LDMIA, instructions::thumb::load::LDMIA } },
        { id::instruction::T_LDR1,  { opcodes::thumb::LDR1,  instructions::thumb::load::LDR1 } },
        { id::instruction::T_LDR2,  { opcodes::thumb::LDR2,  instructions::thumb::load::LDR2 } },
        { id::instruction::T_LDR3,  { opcodes::thumb::LDR3,  instructions::thumb::load::LDR3 } },
        { id::instruction::T_LDR4,  { opcodes::thumb::LDR4,  instructions::thumb::load::LDR4 } },
        { id::instruction::T_LDRB1, { opcodes::thumb::LDRB1, instructions::thumb::load::LDRB1 } },
        { id::instruction::T_LDRB2, { opcodes::thumb::LDRB2, instructions::thumb::load::LDRB2 } },
        { id::instruction::T_LDRH1, { opcodes::thumb::LDRH1, instructions::thumb::load::LDRH1 } },
        { id::instruction::T_LDRH2, { opcodes::thumb::LDRH2, instructions::thumb::load::LDRH2 } },
        { id::instruction::T_LDRSB, { opcodes::thumb::LDRSB, instructions::thumb::load::LDRSB } },
        { id::instruction::T_LDRSH, { opcodes::thumb::LDRSH, instructions::thumb::load::LDRSH } },
        { id::instruction::T_POP,   { opcodes::thumb::POP,   instructions::thumb::load::POP } },
    
        // store
        { id::instruction::T_STMIA, { opcodes::thumb::STMIA, instructions::thumb::store::STMIA } },
        { id::instruction::T_STR1,  { opcodes::thumb::STR1,  instructions::thumb::store::STR1 } },
        { id::instruction::T_STR2,  { opcodes::thumb::STR2,  instructions::thumb::store::STR2 } },
        { id::instruction::T_STR3,  { opcodes::thumb::STR3,  instructions::thumb::store::STR3 } },
        { id::instruction::T_STRB1, { opcodes::thumb::STRB1, instructions::thumb::store::STRB1 } },
        { id::instruction::T_STRH1, { opcodes::thumb::STRH1, instructions::thumb::store::STRH1 } },
        { id::instruction::T_STRH2, { opcodes::thumb::STRH2, instructions::thumb::store::STRH2 } },
        { id::instruction::T_PUSH,  { opcodes::thumb::PUSH,  instructions::thumb::store::PUSH } }

        // { id::instruction::T_BKPT,    { opcodes::thumb::, instructions::thumb:: } },
        // { id::instruction::T_BLX1,    { opcodes::thumb::BLX1, instructions::thumb:: } },
        // { id::instruction::T_BLX2,    { opcodes::thumb::, instructions::thumb:: } }
    };
}