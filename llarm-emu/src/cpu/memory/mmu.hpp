#pragma once

#include "../coprocessor/coprocessor.hpp"
#include "../core/globals.hpp"
#include "../../id.hpp"
#include "ram.hpp"
#include "tlb.hpp"
#include "alignment.hpp"
#include "structures.hpp"

#include <llarm/shared/types.hpp>

/**
 * SMALL LEXICON FOR ANYBODY READING THIS:
 *   B = bufferability
 *   C = cachability
 *   AP = access permission
 */
struct MMU {
private:
    GLOBALS& globals;
    RAM& ram;
    ALIGNMENT& alignment;
    COPROCESSOR& coprocessor;
    SETTINGS& settings;
    TLB& tlb;

private:
    id::first_level get_first_level_id(const u32 entry);
    id::second_level get_second_level_id(const u32 entry);
    
    u32 first_level_fetch(const u32 key);
    u32 second_level_fetch(const u32 key, const id::first_level first_level_type);
    
    id::access_domain fetch_domain(const u8 domain_bits);
    u8 fetch_subpage_AP(const u8 subpage, const u32 entry);
    
    bool is_AP_invalid(const u8 raw_AP_bits, const id::access_type access_type);
    id::aborts check_block_access(const u8 AP_bits, const id::access_type access_type, const id::access_domain domain, const id::memory_type memory_type);

    translation_struct first_section(const u32 entry, const u32 address, const u8 access_size, const id::access_type access);
    u32 first_coarse(const u32 entry, const u32 address); // B3-9
    u32 first_fine(const u32 entry, const u32 address); // B3-10

    translation_struct second_large(const u32 entry, const u32 address, const u8 access_size, const id::access_type access, const u8 domain_bits);
    translation_struct second_small(const u32 entry, const u32 address, const u8 access_size, const id::access_type access, const u8 domain_bits);
    translation_struct second_tiny(const u32 entry, const u32 address, const u8 access_size, const id::access_type access, const u8 domain_bits);

public:
    bool is_mmu_enabled();

    translation_struct page_walk(const u32 address, const id::access_type access_type, const u8 access_size);

    translation_struct translate_address(const u32 address, const id::access_type access_type, const u8 access_size);

    mem_write_struct write(const u32 address, const u64 value, const u8 access_size);

    mem_read_struct read(const u32 address, const u8 access_size);

    void manage_abort(const id::aborts abort, const u32 virtual_address, const u8 domain_bits = 0);

    void reset();

    MMU(
        GLOBALS& globals,
        RAM& ram,
        ALIGNMENT& alignment,
        COPROCESSOR& coprocessor,
        SETTINGS& settings,
        TLB& tlb
    ) : globals(globals),
        ram(ram),
        alignment(alignment),
        coprocessor(coprocessor),
        settings(settings),
        tlb(tlb)
    {

    }
};