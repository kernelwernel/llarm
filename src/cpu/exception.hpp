#pragma once

#include "types.hpp"
#include "constants.hpp"
#include "id.hpp"
#include "cpu/core/registers.hpp"
#include "cpu/coprocessor.hpp"
#include "cpu/instruction_set.hpp"
#include <map>

struct EXCEPTION {
private:
    REGISTERS& reg;
    COPROCESSOR& coprocessor;
    INSTRUCTION_SET& instruction_set;

public:
    struct exception_struct {
        constants::mode mode; 
        u32 normal_address;
        u32 high_vector_address;
    };

    std::map<id::exception, exception_struct> table;

    void reset();
    void undefined();
    void swi();
    void prefetch_abort();
    void data_abort();
    void irq();
    void fiq();

    EXCEPTION(
        REGISTERS& reg, 
        COPROCESSOR& coprocessor,
        INSTRUCTION_SET& instruction_set
    );
};