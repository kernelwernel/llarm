#pragma once

#include "../../settings.hpp"
#include "structures.hpp"

#include "shared/types.hpp"

#include <unordered_map>


struct TLB {
private:
    SETTINGS& settings;

private:
    std::unordered_map<u32, u32> unified_table;
    std::unordered_map<u32, u32> inst_table;
    std::unordered_map<u32, u32> data_table;

public:
    // read B3-27 for more context
    u32 W_unified;
    u32 W_inst;
    u32 W_data;

public:
    void invalidate(const u32 virtual_address, const id::tlb_type tlb_type);

    void flush();

    u32 fetch(const u32 virtual_address, const tlb_fetch_struct tlb_fetch);

    tlb_fetch_struct is_translation_cached(const u32 virtual_address);

    bool is_type_invalid(const id::tlb_type tlb_type);

    void function(const u8 opcode_2, const u8 CRm, const u32 data);

    TLB(SETTINGS& settings);
};