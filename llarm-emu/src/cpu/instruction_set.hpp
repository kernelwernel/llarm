#pragma once

#include "instructions/instructions.hpp"

#include <functional>

#include <llarm-asm/llarm-asm.hpp>


struct INSTRUCTION_SET {
private:
    //REGISTERS& reg;
    //MEMORY& memory;
    //COPROCESSOR& coprocessor;
    //SETTINGS& settings;
    INSTRUCTIONS& instructions;

private:
    using arm_table_t     = std::map<llarm::as::id::arm,     std::function<void(const arm_code_t&)>>;
    using thumb_table_t   = std::map<llarm::as::id::thumb,   std::function<void(const thumb_code_t&)>>;
    using jazelle_table_t = std::map<llarm::as::id::jazelle, std::function<void(const u8)>>;

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