#pragma once

#include "../exception.hpp"
#include "mmu.hpp"
#include "mpu.hpp"
#include "ram.hpp"
#include "fcse.hpp"
#include "26_bit_arch.hpp"

#include "shared/types.hpp"

struct MEMORY {
private:
    RAM& ram;
    MMU& mmu;
    MPU& mpu;
    FCSE& fcse;
    ARCH_26& arch_26;
    EXCEPTION& exception;

public:
    void manage_abort(const id::aborts abort_code);

    mem_write_struct write(const u64 &value, u32 address, const u8 access_size);

    mem_read_struct read(
        u32 address, 
        u8 access_size,
        const id::access_type type = id::access_type::READ
    );

    void reset();

    MEMORY(
        RAM& ram, 
        MMU& mmu,
        MPU& mpu,
        FCSE& fcse,
        ARCH_26& arch_26,
        EXCEPTION& exception
    ) : ram(ram), 
        mmu(mmu), 
        mpu(mpu),
        fcse(fcse),
        arch_26(arch_26),
        exception(exception)
    {

    }
};