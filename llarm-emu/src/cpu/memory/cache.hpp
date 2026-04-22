#pragma once

#include "../coprocessor/coprocessor.hpp"
#include "../../ram/ram.hpp"

#include <llarm/shared/types.hpp>
#include <array>
#include <vector>

struct CACHE {
    SETTINGS& settings;
    COPROCESSOR& coprocessor;
    RAM& ram;

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

    struct cache_line {
        u32 tag = 0;
        bool valid = false;
        bool dirty = false;
        std::array<u8, 64> data = {};  // max LINELEN is 64 bytes (len is 2-bit: 8/16/32/64)
    };

    bool is_unified = false;

    // flat 2D layout: index as lines[set * ASSOCIATIVITY + way]
    // inst_lines is empty when is_unified: instruction fetches use data_lines instead
    std::vector<cache_line> data_lines;
    std::vector<cache_line> inst_lines;

    cache_line& data_line(const u32 set, const u32 way) {
        return data_lines[(set * DATA_ASSOCIATIVITY) + way];
    }

    cache_line& inst_line(const u32 set, const u32 way) {
        if (is_unified) {
            return data_lines[(set * DATA_ASSOCIATIVITY) + way];
        }

        return inst_lines[(set * INST_ASSOCIATIVITY) + way];
    }


    
    
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

    void reset();

    void write_cache(const u32 address, const u32 value, const u8 size);

    u32 read_cache(const u32 address);

    void function(const u8 CRm, const u8 opcode_2, const u32 data = 0);

    CACHE(
        SETTINGS& settings, 
        COPROCESSOR& coprocessor,
        RAM& ram
    ) : settings(settings), 
        coprocessor(coprocessor),
        ram(ram) 
    {
        set_parameters();
    }
};



/* CACHE NOTES:

- a cache line MUST be a power of 2
- the cache set is basically the **row** of the cache structure
- while the cache line is the column
- a "block" is a cache line that contains the data, basically the cache line itself
  - can be 128 or 256 bits 


CACHE WRITE POLICIES:
- write-through: after writing to the cache, the data copy in the ram is also updated with the new write data.
- write-back: when updating the cache, the data copy is NOT updated. The RAM data is only updated when the data in cache is destroyed or evicted
    - it also has a concept called a dirty bit: if a cache line is modified after been fetched from ram, 
      the "dirty bit" will be set to 1 to signify that this is an active cache line. If it's 0, that means
      the cache can evict this line when it's full and needs to replace it with new data because it already
      matches what's in main memory. In the case of evicting a dirty bit cache line, this will signify to
      the cache that it needs to update the RAM when evicting this cache line. So if there's no dirty bit, 
      there's no RAM update. If there is a dirty bit, update the RAM. Simple.

*/