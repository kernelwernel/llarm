#include "cache.hpp"


void CACHE::set_parameters() {
    DATA_LINELEN = u8(1 << (coprocessor.read(id::cp15::R0_CACHE_DSIZE_LEN) + 3));
    INST_LINELEN = u8(1 << (coprocessor.read(id::cp15::R0_CACHE_ISIZE_LEN) + 3));
    DATA_MULTIPLIER = u8(2 + coprocessor.read(id::cp15::R0_CACHE_DSIZE_M));
    INST_MULTIPLIER = u8(2 + coprocessor.read(id::cp15::R0_CACHE_ISIZE_M));
    DATA_ASSOCIATIVITY = u16(DATA_MULTIPLIER << (coprocessor.read(id::cp15::R0_CACHE_DSIZE_ASSOC) - 1));
    INST_ASSOCIATIVITY = u16(INST_MULTIPLIER << (coprocessor.read(id::cp15::R0_CACHE_ISIZE_ASSOC) - 1));
    DATA_NSETS = (1 << (
        coprocessor.read(id::cp15::R0_CACHE_DSIZE_SIZE) 
        + 6 
        - (coprocessor.read(id::cp15::R0_CACHE_DSIZE_ASSOC) 
        - (coprocessor.read(id::cp15::R0_CACHE_DSIZE_LEN)))
    ));
    INST_NSETS = (1 << (
        coprocessor.read(id::cp15::R0_CACHE_ISIZE_SIZE) 
        + 6 
        - (coprocessor.read(id::cp15::R0_CACHE_ISIZE_ASSOC) 
        - (coprocessor.read(id::cp15::R0_CACHE_ISIZE_LEN)))
    ));
    DATA_CACHE_SIZE = u32(DATA_MULTIPLIER << (coprocessor.read(id::cp15::R0_CACHE_DSIZE_SIZE) + 8)); // in bytess
    INST_CACHE_SIZE = u32(INST_MULTIPLIER << (coprocessor.read(id::cp15::R0_CACHE_ISIZE_SIZE) + 8)); // in bytes
}


void CACHE::flush_data_cache() {

}

void CACHE::flush_inst_cache() {
    
}

void CACHE::invalidate_data_entry(const u32 address) {

}

void CACHE::invalidate_inst_entry(const u32 address) {
    
}
