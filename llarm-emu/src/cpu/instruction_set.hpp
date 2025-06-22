#pragma once

#include "instructions/instructions.hpp"

#include <functional>

#include <llarm-asm/llarm-asm.hpp>


struct INSTRUCTION_SET {
private:
    //REGISTERS& reg;
    //MEMORY& memory;
    //COPROCESSOR& coprocessor;
    SETTINGS& settings;
    INSTRUCTIONS& instructions;

private:
    using arm_table_t     = std::map<llarm::as::id::arm,     std::function<void(const arm_code_t&)>>;
    using thumb_table_t   = std::map<llarm::as::id::thumb,   std::function<void(const thumb_code_t&)>>;
    using jazelle_table_t = std::map<llarm::as::id::jazelle, std::function<void(const u8)>>;

public:
    arm_table_t arm_table;
    thumb_table_t thumb_table;
    jazelle_table_t jazelle_table;

    void armv2_setup();
    void armv3_setup();
    void armv4_setup();
    void armv5_setup();

    // TODO make instruction adder functions here

    INSTRUCTION_SET(
        //REGISTERS& reg, 
        //MEMORY& memory, 
        //COPROCESSOR& coprocessor, 
        SETTINGS& settings, 
        INSTRUCTIONS& instructions
    );
};