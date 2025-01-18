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


    /**
     * R14_svc[25:2] = address of instruction + 8
     * R14_svc[31:26,1,0] = R15[31:26,1,0]
     * M[1:0] = 0b11 ; Supervisor mode
     * F = unchanged
     * I = 1 ; (normal) interrupts disabled
     * PC = 0x14
     */
    // not sure if this "address exception" also applies to 32-bit
    void address_exception_26(const u32 faulty_address) {
        u32 R15_copy = reg.read(id::reg::R15);

        const u32 new_R15 = util::swap_bits(R15_copy, 2, 26, faulty_address + 8); // TODO: CHECK IF THIS WORKS
    
        reg.write(id::reg::R14_svc, new_R15);

        reg.write_cpsr(id::cpsr::M, 0b11);
        reg.write_cpsr(id::cpsr::I, 1);

        reg.write(id::reg::PC, 0x14);

        return;
    }


    EXCEPTION(
        REGISTERS& reg, 
        COPROCESSOR& coprocessor,
        INSTRUCTION_SET& instruction_set
    );
};