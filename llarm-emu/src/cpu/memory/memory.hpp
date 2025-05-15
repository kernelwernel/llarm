#pragma once

#include "shared/types.hpp"
#include "../../utility.hpp"
#include "../exception.hpp"
#include "mmu.hpp"
#include "mpu.hpp"
#include "ram.hpp"
#include "fcse.hpp"
#include "26_bit_arch.hpp"

#include <bitset>
#include <vector>
#include <map>

struct MEMORY {
private:
    RAM& ram;
    MMU& mmu;
    MPU& mpu;
    FCSE& fcse;
    ARCH_26_BIT& arch_26;
    EXCEPTION& exception;

public:
    void manage_abort(const id::aborts abort_code) {
        switch (abort_code) {
            case id::aborts::NO_ABORT: return;
            case id::aborts::ALIGNMENT:
            case id::aborts::ABORT:
            case id::aborts::ADDRESS_EXCEPTION:
            case id::aborts::TRANSLATION:
            case id::aborts::SECTION_TRANSLATION:
            case id::aborts::PAGE_TRANSLATION:
            case id::aborts::PAGE_DOMAIN:
            case id::aborts::SUB_PAGE_PERMISSION:
            case id::aborts::SECTION_DOMAIN:
            case id::aborts::SECTION_PERMISSION: exception.data_abort(); return;
            case id::aborts::PREFETCH_ABORT: exception.prefetch_abort(); return;
        }
    }

    //data_struct write(const std::vector<u8> &value, u32 address, const u8 bytes) {
    //    if (is_26_bit_address_unsupported(address)) {
//
    //    }
//
    //    fcse.modify_address(address);
//
    //    //if (mmu.is_mmu_enabled()) {
    //    //    address = mmu.translate_address(address);
    //    //}
//
    //    ram.write(value, address);
    //}
//



    template <is_integral T>
    memory_struct<> write(const T value, u32 address, const u8 access_size) {
        
        if (arch_26.is_26_arch_backwards_compatible()) {
            if (
                (arch_26.is_26_arch_address()) && 
                (arch_26.is_26_arch_address_unsupported(address))
            ) {
                return memory_struct<> {
                    true, // has_failed
                    id::aborts::ADDRESS_EXCEPTION, // abort_code
                    0, // new_address
                    0 // value
                };
            }
        }
        
        if (fcse.is_fcse_enabled()) {
            address = fcse.modify_address(address);
        }

        memory_struct<> data = {};

        // not to be confused with mmu and mpu   
        if (mmu.is_mmu_enabled()) {
            data = mmu.write_manager(address, access_size);
        } else if (mpu.is_mpu_enabled()) {
            data = mpu.write_manager(address, access_size); 
        } else {
            data.has_failed = false;
            data.abort_code = id::aborts::NO_ABORT;
            data.value = 0;
            data.new_address = address;
        }

        ram.write<T>(value, data.new_address, access_size);

        return data;
    }








    //std::vector<u8> read(const u32 start, const u32 end) {
    //    // TODO
//
    //    //if (is_26_bit_address_unsupported(address)) {
////
    //    //}
//
    //    return ram.read(start, end);
    //}

    //u8 read(u32 address) {
    //    if (arch_26.is_26_arch_address_unsupported(address)) {
//
    //    }
//
    //    //if (mmu.is_mmu_enabled()) {
    //    //    address = mmu.translate_address(address);
    //    //}
//
    //    return ram.read<u8>(address);
    //}



    // There is no plan B.
    // There is also no plan A.
    // I don't know what I'm doing with my life.
    template <is_integral T>
    memory_struct<T> read(
        u32 address, 
        u8 access_size,
        const id::access_type type = id::access_type::READ
    ) {
        //memory_struct<T> data = {};
//
        //data.has_failed = false;
        //data.abort_code = id::aborts::NO_ABORT;
        //data.value = 0;
        //data.new_address = 0;
//
        //return data; // TEMPORARY


        memory_struct<T> data = {};

        data.has_failed = false;
        data.value = ram.read<T>(address, access_size);
        data.new_address = address;
        data.abort_code = id::aborts::NO_ABORT;

        return data;



        // TODO add if conditions for MMU or MPU



/*
        if (arch_26.is_26_arch_address_unsupported(address)) {

        }

        if constexpr (std::is_same_v<T, u8>) {
            return read(address);
        } else if constexpr (std::is_same_v<T, u16>) {
            return (
                (static_cast<u16>(read<u8>(address + 1)) << 8) | 
                (read<u8>(address))
            );
        } else if constexpr (std::is_same_v<T, u32>) {
            return (
                (static_cast<u32>(read(address + 3)) << 24) | 
                (read<u8>(address + 2) << 16) | 
                (read<u8>(address + 1) << 8) | 
                (read<u8>(address))
            );
        } else if constexpr (std::is_same_v<T, u64>) {
            return (
                (static_cast<u64>(read<u8>(address + 7)) << 56) | 
                (static_cast<u64>(read<u8>(address + 6)) << 48) | 
                (static_cast<u64>(read<u8>(address + 5)) << 40) | 
                (static_cast<u64>(read<u8>(address + 4)) << 32) | 
                (static_cast<u64>(read<u8>(address + 3)) << 24) | 
                (static_cast<u64>(read<u8>(address + 2)) << 16) | 
                (static_cast<u64>(read<u8>(address + 1)) << 8) | 
                (static_cast<u64>(read<u8>(address)))
            );
        }
*/
    }


    void reset() {
        ram.reset();
    }



    MEMORY(
        RAM& ram, 
        MMU& mmu,
        MPU& mpu,
        FCSE& fcse,
        ARCH_26_BIT& arch_26,
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