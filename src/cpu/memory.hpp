#pragma once

#include "types.hpp"
#include "cpu/ram.hpp"
#include "cpu/coprocessor.hpp"

#include <bitset>
#include <vector>
#include <cmath>
#include <map>

struct MEMORY {
private:
    RAM& ram;
    COPROCESSOR& coprocessor;

    // page/block sizes
    constexpr u32 tiny  = std::pow(2, 10); // 1KB
    constexpr u32 small = std::pow(2, 12); // 4KB
    constexpr u32 large = std::pow(2, 16); // 64KB

    // section size
    constexpr u32 section = std::pow(2, 20); // 1MB

    // protection unit
    struct PU {

    };


public:


    /*
     * MMU NOTES:
     *
     * - For caches and write buffers which are not allowed to be enabled while the MMU is disabled, 
     *   the values of the C and B bits for a memory access are irrelevant.
     *
     * - For caches and write buffers which are allowed to be enabled while the MMU is disabled, a
     *   data access is treated as uncachable and unbufferable (C == 0, B == 0). An instruction fetch is
     *   treated as uncachable (C == 0) in a system with a unified TLB, and as cachable (C == 1) in a
     *   system with a separate instruction TLB.
     * 
     * - when the MMU is disabled, no aborts are generated
     * 
     * - Before the MMU is enabled, suitable translation tables must be set up 
     *   in memory and all relevant CP15 registers must be programmed.
     * 
     * 
     * 
     * MEMORY SIZES:
     * - Sections are comprised of 1MB blocks of memory.
     * 
     * - Three different page sizes are supported:
     *   - Tiny pages: Consist of 1KB blocks of memory.
     *   - Small pages: Consist of 4KB blocks of memory.
     *   - Large pages: Consist of 64KB blocks of memory.
     * 
     * CP15 reg 2 is the translation table base register:
     *  - the first-level page table must reside on a 16KB boundary.
     *  - bits 31:14 are significant, 13:0 should be 0
     * 
     * 
     */


    void write(const std::vector<u8> &data, const u32 address) {
        if (is_access_permission_invalid()) {
            // TODO: FIND AN ERROR MESSAGE
        }

        ram.write(data, address);
    }

    void write(const u8 data, const u32 address) {
        if (is_access_permission_invalid()) {
            // TODO: FIND AN ERROR MESSAGE
        }

        ram.write(data, address);
    }

    void write(const u16 data, const u32 address) {
        if (is_access_permission_invalid()) {
            // TODO: FIND AN ERROR MESSAGE
        }

        ram.write(data, address);
    }

    void write(const u32 data, const u32 address) {
        if (is_access_permission_invalid()) {
            // TODO: FIND AN ERROR MESSAGE
        }

        ram.write(data, address);
    }

    std::vector<u8> read(const u32 start, const u32 end) {
        if (is_access_permission_invalid()) {
            // TODO: FIND AN ERROR MESSAGE
        }

        return ram.read(start, end);
    }

    u8 read(const u32 address) {
        if (is_access_permission_invalid()) {
            // TODO: FIND AN ERROR MESSAGE
        }

        return ram.read(address);
    }

    void reset() {
        ram.reset();
    }

    bool is_access_permission_invalid() {
        if (coprocessor.read(id::cp15::R1_M) == false) {
            return false;
        }

        // TODO: CONTINUE WITH THE CHECK
        return true;
    }

    MEMORY(
        const std::vector<u8> &binary, 
        RAM& ram, 
        COPROCESSOR& coprocessor
    ) : ram(ram), coprocessor(coprocessor) {
        ram.write(binary, 0); // write the entire machine code into RAM
    }


};