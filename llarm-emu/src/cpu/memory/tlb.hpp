#pragma once

#include "../../settings.hpp"
#include "structures.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/random.hpp>



struct TLB {
    SETTINGS& settings;

    llarm::random random;

    llarm::unordered_map<u32, tlb_entry_struct> unified_table;
    llarm::unordered_map<u32, tlb_entry_struct> inst_table;
    llarm::unordered_map<u32, tlb_entry_struct> data_table;

    // read B3-27 for more context
    u32 W_unified;
    u32 W_inst;
    u32 W_data;

    void invalidate(const u32 virtual_address, const id::tlb_type tlb_type);

    void auto_replace(const id::tlb_type tlb_type, const u32 virtual_address, const u32 physical_address, const bool is_cacheable, const bool is_write_bufferable);

    void flush();

    tlb_entry_struct fetch(const u32 virtual_address, const tlb_fetch_struct tlb_fetch);

    void insert(const u32 virtual_address, const u32 physical_address, const id::tlb_type tlb_type, const bool is_cacheable, const bool is_write_bufferable);

    tlb_fetch_struct is_translation_cached(const u32 virtual_address) const;

    bool is_type_invalid(const id::tlb_type tlb_type) const;

    void function(const u8 opcode_2, const u8 CRm, const u32 virtual_address);

    TLB(SETTINGS& settings);
};