#pragma once

#include "core/registers.hpp"
#include "memory/memory.hpp"
#include "instructions/instructions.hpp"

#include <map>
#include <variant>

struct INSTRUCTION_SET {
private:
    //REGISTERS& reg;
    //MEMORY& memory;
    //COPROCESSOR& coprocessor;
    //SETTINGS& settings;
    INSTRUCTIONS& instructions;


public:
    struct arm_struct {
        std::function<bool(const arm_code_t&)> opcode;
        std::function<void(const arm_code_t&)> function;
    };

    struct thumb_struct {
        std::function<bool(const thumb_code_t&)> opcode;
        std::function<void(const thumb_code_t&)> function;
    };

    struct jazelle_struct {
        u8 opcode;
        std::function<void(const jazelle_code_t)> function;
    };

private:
    using arm_table_t = std::map<id::arm_instruction, arm_struct>;
    using thumb_table_t = std::map<id::thumb_instruction, thumb_struct>;
    using jazelle_table_t = std::map<id::jazelle_instruction, jazelle_struct>;

public:
    arm_table_t arm_table;
    thumb_table_t thumb_table;
    jazelle_table_t jazelle_table;

    //void add_arm_instruction(const arm_struct &instruction) {
    //    // this is definitely NOT gonna compile
    //    // 
    //    // auto last_instruction = arm_table.crbegin();
    //    // const u8 last_id = last_instruction->first;
// //
    //    // arm_table.emplace((last_id + 1), instruction);
    //}
    //
    //void add_thumb_instruction() {
    //    
    //}
//
    //void add_jazelle_instruction() {
    //    
    //}

    INSTRUCTION_SET(
        //REGISTERS& reg, 
        //MEMORY& memory, 
        //COPROCESSOR& coprocessor, 
        //SETTINGS& settings, 
        INSTRUCTIONS& instructions
    );
};