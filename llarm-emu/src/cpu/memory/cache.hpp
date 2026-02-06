#pragma once

#include "../coprocessor/coprocessor.hpp"

#include <llarm/shared/types.hpp>

struct CACHE {
private:
    COPROCESSOR& coprocessor;

private:
    u8 DATA_LINELEN = 0;
    u8 DATA_MULTIPLIER = 0;
    u16 DATA_ASSOCIATIVITY = 0;
    u32 DATA_NSETS = 0;
    u32 DATA_CACHE_SIZE = 0;
    
    u8 INST_LINELEN = 0;
    u8 INST_MULTIPLIER = 0;
    u16 INST_ASSOCIATIVITY = 0;
    u32 INST_NSETS = 0;
    u32 INST_CACHE_SIZE = 0;


    /**
     * The following formulae can be used to determine the values LINELEN, ASSOCIATIVITY
     * and NSETS, defined in Cache size on page B5-4, once the cache absent case (assoc == 0b000, M == 1) has
     * been checked for and eliminated:
     * 
     *    LINELEN = 1 << (len+3)
     *    MULTIPLIER = 2 + M
     *    ASSOCIATIVITY = MULTIPLIER << (assoc-1)
     *    NSETS = 1 << (size + 6 - assoc - len)
     * 
     * Multiplying these together gives the overall cache size as:
     * 
     *    CACHE_SIZE = MULTIPLIER << (size+8) // In bytes
     * 
     * (B2-11)
     */
    void set_parameters();

    void flush_data_cache();

    void flush_inst_cache();

    void invalidate_data_entry(const u32 address);

    void invalidate_inst_entry(const u32 address);

public:
    CACHE(COPROCESSOR& coprocessor) : coprocessor(coprocessor) {
        set_parameters();
    }
};



/* CACHE NOTES:

- a cache line MUST be a power of 2
- a "block" is a cache line that contains the data, basically the cache line itself
  - can be 128 or 256 bits 
 */