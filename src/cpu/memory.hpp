#pragma once

#include "types.hpp"
#include "cpu/ram.hpp"
#include "cpu/coprocessor.hpp"
#include "utility.hpp"
#include "mmu.hpp"

#include <bitset>
#include <vector>
#include <cmath>
#include <map>

struct MEMORY {
private:
    RAM& ram;
    COPROCESSOR& coprocessor;
    MMU& mmu;


    // this is specific to the 26-bit architecture
    bool is_address_invalid(const u32 address) {
        if (settings.no_26_bits) {
            return false;
        }
    
        // 26-bit architecture cannot have an address above (2^26)-1
        if (coprocessor.is_26_bit_arch_address()) {
            if (address > (std::pow(2, 26) - 1)) {
                // TODO: "ADDRESS EXCEPTION" HERE
                return false;
            }
        }

        return true;
    }




public:



    void write(const std::vector<u8> &data, u32 address, const u8 bytes) {
        if (is_address_invalid(address)) {

        }

        if (mmu.is_mmu_enabled()) {
            address = mmu.translate_address(address);
        }

        ram.write(data, address);
    }

    void write(const u8 data, u32 address, const u8 bytes) {
        if (is_address_invalid(address)) {

        }

        if (mmu.is_mmu_enabled()) {
            address = mmu.translate_address(address);
        }

        ram.write(data, address);
    }

    void write(const u16 data, u32 address, const u8 bytes) {
        if (is_address_invalid(address)) {

        }

        if (mmu.is_mmu_enabled()) {
            address = mmu.translate_address(address);
        }

        ram.write(data, address);
    }

    void write(const u32 data, u32 address, const u8 bytes) {
        if (is_address_invalid(address)) {

        }

        if (mmu.is_mmu_enabled()) {
            address = mmu.translate_address(address);
        }

        ram.write(data, address);
    }

    std::vector<u8> read(const u32 start, const u32 end) {
        // TODO

        //if (is_address_invalid(address)) {
//
        //}

        return ram.read(start, end);
    }

    u8 read(u32 address) {
        if (is_address_invalid(address)) {

        }

        if (mmu.is_mmu_enabled()) {
            address = mmu.translate_address(address);
        }

        return ram.read(address);
    }


    // lord have mercy
    template <is_integral T>
    T read(u32 address) {
        if (is_address_invalid(address)) {

        }
        if constexpr (std::is_same_v<T, u8>) {
            return read(address);
        } else if constexpr (std::is_same_v<T, u16>) {
            return (
                (static_cast<u16>(read(address + 1)) << 8) | 
                (read(address))
            );
        } else if constexpr (std::is_same_v<T, u32>) {
            return (
                (static_cast<u32>(read(address + 3)) << 24) | 
                (read(address + 2) << 16) | 
                (read(address + 1) << 8) | 
                (read(address))
            );
        } else if constexpr (std::is_same_v<T, u64>) {
            return (
                (static_cast<u64>(read(address + 7)) << 56) | 
                (read(address + 6) << 48) | 
                (read(address + 5) << 40) | 
                (read(address + 4) << 32) | 
                (read(address + 3) << 24) | 
                (read(address + 2) << 16) | 
                (read(address + 1) << 8) | 
                (read(address))
            );
        }
    }





// TODO, MAYBE ALL OF THESE CAN REPLACE MOST OF THE FUNCTIONS ABOVE

    u8 byte_read(const u32 address) {

    }

    u16 halfword_read(const u32 address) {
        
    }

    u32 word_read(const u32 address) {
        
    }





    void reset() {
        ram.reset();
    }



    MEMORY(
        const std::vector<u8> &binary, 
        RAM& ram, 
        COPROCESSOR& coprocessor,
        MMU& mmu
    ) : ram(ram), coprocessor(coprocessor), mmu(mmu) {
        ram.write(binary, 0); // write the entire machine code into RAM
    }


};