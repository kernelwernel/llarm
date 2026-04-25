#pragma once

#include "../coprocessor/cp15.hpp"
#include "../../ram/ram.hpp"

#include <llarm/shared/types.hpp>
#include <array>
#include <vector>

struct CACHE {
    SETTINGS& settings;
    CP15& cp15;
    RAM& ram;
    bool& is_halted;

    u8 DATA_LINELEN = 8;  // min value from formula: 1 << (len+3), len is 2-bit
    u8 DATA_MULTIPLIER = 0;
    u16 DATA_ASSOCIATIVITY = 0;
    u32 DATA_NSETS = 0;
    u32 DATA_CACHE_SIZE = 0;
    u8 DATA_W = 0;  // bits needed to index a way (ceil(log2(DATA_ASSOCIATIVITY)))

    u8 INST_LINELEN = 8;  // same formula as DATA_LINELEN
    u8 INST_MULTIPLIER = 0;
    u16 INST_ASSOCIATIVITY = 0;
    u32 INST_NSETS = 0;
    u32 INST_CACHE_SIZE = 0;
    u8 INST_W = 0;  // bits needed to index a way (ceil(log2(INST_ASSOCIATIVITY)))

    struct address_breakdown {
        u32 linelen;
        u32 nsets;
        u32 associativity;
        u32 set;
        u32 tag;

        address_breakdown(
            const u32 virtual_address, 
            const u32 linelen, 
            const u32 nsets, 
            const u32 associativity
        ) : linelen(linelen), 
            nsets(nsets), 
            associativity(associativity),
            set((virtual_address / linelen) % nsets),
            tag(virtual_address / (static_cast<u32>(linelen) * nsets))
        {

        }
    };

    struct index_breakdown {
        u32 set;
        u32 way;

        index_breakdown(
            const u32 data, 
            const u32 linelen, 
            const u32 nsets, 
            const u32 associativity
        ) {
            u32 linelen_bits = 0;
            for (u32 l = linelen >> 1; l > 0; l >>= 1) {
                ++linelen_bits; 
            }

            u32 way_bits = 0;
            for (u32 a = associativity - 1; a > 0; a >>= 1) {
                ++way_bits; 
            }

            set = (data >> linelen_bits) & (nsets - 1);
            way = way_bits > 0 ? (data >> (32 - way_bits)) : 0;
        }
    };

    index_breakdown inst_index(const u32 index) const;
    index_breakdown data_index(const u32 index) const;

    struct cache_line {
        u32 tag = 0;
        bool valid = false;
        bool dirty = false;
        std::array<u8, 64> data = {};  // max LINELEN is 64 bytes (len is 2-bit: 8/16/32/64)
    };

    // flat 2D layout: index as lines[set * ASSOCIATIVITY + way]
    // inst_lines is empty when is_unified: instruction fetches use data_lines instead
    std::vector<cache_line> data_lines;
    std::vector<cache_line> inst_lines;

    cache_line& data_line(const u32 set, const u32 way);
    cache_line& inst_line(const u32 set, const u32 way);

    address_breakdown inst_breakdown(const u32 virtual_address) const;
    address_breakdown data_breakdown(const u32 virtual_address) const;

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

    // flushers/invalidators
    void flush_data_cache();
    void flush_inst_cache();
    void invalidate_data_entry(const u32 address);
    void invalidate_inst_entry(const u32 address);
    void invalidate_data_entry_index(const u32 index);
    void invalidate_inst_entry_index(const u32 index);
    void clean_data_entry(const u32 address);
    void clean_data_entry_index(const u32 index);
    void clean_invalidate_data_entry(const u32 address);
    void clean_invalidate_data_entry_index(const u32 index);

    void reset();

    // meant for MMU
    void write(
        const u32 virtual_address,
        const u32 physical_address,
        const u32 value,
        const u8 size,
        const bool is_write_bufferable
    );

    // overload of the above, mainly meant for MPU and RAM 
    void write(
        const u32 physical_address,
        const u32 value,
        const u8 size,
        const bool is_write_bufferable
    );

    u32 read(const u32 virtual_address, const u32 physical_address, const bool is_write_bufferable);
    u32 read(const u32 physical_address, const bool is_write_bufferable);

    u32 fetch_inst(const u32 virtual_address, const u32 physical_address);
    u32 fetch_inst(const u32 physical_address);

    // shared cache utilities for read/write/function
    u32 data_lock_base() const;
    u32 inst_lock_base() const;
    u32 find_victim_way(const u32 set);
    u32 find_victim_way_inst(const u32 set);
    void evict_if_dirty(cache_line& victim, const u32 set);
    void fill_line(cache_line& victim, const u32 line_base);
    void fill_line_inst(cache_line& victim, const u32 line_base);
    u32 read_line(const cache_line& line, const u32 pos) const;
    u32 read_line_inst(const cache_line& line, const u32 pos) const;

    void function(const u8 CRm, const u8 opcode_2, const u32 data = 0);

    CACHE(
        SETTINGS& settings,
        CP15& cp15,
        RAM& ram,
        bool& is_halted
    ) : settings(settings),
        cp15(cp15),
        ram(ram),
        is_halted(is_halted)
    {
        if (settings.cache_type != id::cache_type::UNKNOWN) { 
            set_parameters();
        }
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