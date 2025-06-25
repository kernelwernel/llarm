#pragma once

#include "../../settings.hpp"

#include "shared/types.hpp"

#include <map>


struct TLB {
private:
    SETTINGS& settings;

public:
    // holds section translations and pointers to second level table indexes
    std::map<u32, u32> first_level {};
    std::map<u32, u32> second_level_coarse {}; // holds large and small page translations (256)
    std::map<u32, u32> second_level_fine {}; // holds large, small, and tiny page translations (B3-7) (1024)

    std::map<u32, u32> first_level_inst {};
    std::map<u32, u32> second_level_coarse_inst {};
    std::map<u32, u32> second_level_fine_inst {};

    std::map<u32, u32> first_level_data {};
    std::map<u32, u32> second_level_coarse_data {};
    std::map<u32, u32> second_level_fine_data {};

private:
    void invalidate(const u32 virtual_address, const u32 translation_base, const id::tlb_type tlb_type);

public:
    void flush();

    void table_walk();

    void function(const u8 opcode_2, const u8 CRm, const u32 data, const u32 translation_base);

    TLB(SETTINGS& settings) : settings(settings) {

    }
};