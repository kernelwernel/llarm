#pragma once

/*
 * IDEAS ON HOW TO HANDLE EXCEPTIONS:
 *
 * 1. use a goto label
 * 2. use C++ signals
 * 3. use a std::variant return type for all exception-prone functions
 * 4. return a 0 as a NULL, then analyse after the function has returned
 */

#include "../../id.hpp"
#include "registers.hpp"
#include "../coprocessor/coprocessor.hpp"

#include <map>

#include <llarm/shared/types.hpp>

struct EXCEPTION {
private:
    REGISTERS& reg;
    COPROCESSOR& coprocessor;

public:
    struct exception_struct {
        u8 mode; 
        u32 normal_address;
        u32 high_vector_address;
    };

    std::map<id::exception_mode, exception_struct> table;

    void reset();
    void undefined();
    void swi();
    void prefetch_abort();
    void data_abort();
    void irq();
    void fiq();

    // not sure if this "address exception" also applies to 32-bit
    void address_exception_26(const u32 faulty_address);


    EXCEPTION(
        REGISTERS& reg, 
        COPROCESSOR& coprocessor
    );
};

