#include "cache.hpp"


void CACHE::set_parameters() {
    is_unified = !settings.has_separate_cache;

    // present in both unified and separate caches
    DATA_LINELEN = static_cast<u8>(1 << (coprocessor.read(id::cp15::R0_CACHE_DSIZE_LEN) + 3));
    DATA_MULTIPLIER = static_cast<u8>(2 + coprocessor.read(id::cp15::R0_CACHE_DSIZE_M));
    DATA_ASSOCIATIVITY = static_cast<u16>(DATA_MULTIPLIER << (coprocessor.read(id::cp15::R0_CACHE_DSIZE_ASSOC) - 1));
    DATA_NSETS = (1 << (
        coprocessor.read(id::cp15::R0_CACHE_DSIZE_SIZE)
        + 6
        - coprocessor.read(id::cp15::R0_CACHE_DSIZE_ASSOC)
        - coprocessor.read(id::cp15::R0_CACHE_DSIZE_LEN)
    ));
    DATA_CACHE_SIZE = static_cast<u32>(DATA_MULTIPLIER << (coprocessor.read(id::cp15::R0_CACHE_DSIZE_SIZE) + 8));
    data_lines.assign(static_cast<size_t>(DATA_NSETS) * DATA_ASSOCIATIVITY, cache_line{});

    // only for separate
    if (settings.has_separate_cache) {
        INST_LINELEN = static_cast<u8>(1 << (coprocessor.read(id::cp15::R0_CACHE_ISIZE_LEN) + 3));
        INST_MULTIPLIER = static_cast<u8>(2 + coprocessor.read(id::cp15::R0_CACHE_ISIZE_M));
        INST_ASSOCIATIVITY = static_cast<u16>(INST_MULTIPLIER << (coprocessor.read(id::cp15::R0_CACHE_ISIZE_ASSOC) - 1));
        INST_NSETS = (1 << (
            coprocessor.read(id::cp15::R0_CACHE_ISIZE_SIZE) 
            + 6 
            - coprocessor.read(id::cp15::R0_CACHE_ISIZE_ASSOC) 
            - coprocessor.read(id::cp15::R0_CACHE_ISIZE_LEN)
        ));
        INST_CACHE_SIZE = static_cast<u32>(INST_MULTIPLIER << (coprocessor.read(id::cp15::R0_CACHE_ISIZE_SIZE) + 8));

        inst_lines.assign(static_cast<size_t>(INST_NSETS) * INST_ASSOCIATIVITY, cache_line{});
    }
}


void CACHE::flush_data_cache() {
    for (auto& line : data_lines) {
        line.valid = false;
        line.dirty = false;
    }
}

void CACHE::flush_inst_cache() {
    if (is_unified) {
        for (auto& line : data_lines) {
            line.valid = false;
            line.dirty = false;
        }
        return;
    }

    for (auto& line : inst_lines) {
        line.valid = false;
    }
}

void CACHE::invalidate_data_entry(const u32 address) {
    // TODO
}

void CACHE::invalidate_inst_entry(const u32 address) {
    // TODO
}

void CACHE::reset() {
    data_lines.clear();
    inst_lines.clear();
}

void CACHE::write_cache(const u32 address, const u32 value, const u8 size) {
    // TODO
}

u32 CACHE::read_cache(const u32 address) {
    (void)address; // TODO
    return 0;
}


void CACHE::function(const u8 CRm, const u8 opcode_2, const u32 data) {
    (void)data; // TODO

    // these are just combinations of the CRm and opcode_2 merged 
    // together to create an integral value to run a switch on. 

    constexpr u8 WAIT_FOR_INTERRUPT = 04; // c0, opcode2 = 4 
    constexpr u8 INVALIDATE_ENTIRE_INST_CACHE = 50; // c5, opcode2 = 0 
    constexpr u8 INVALIDATE_INST_CACHE_VIRTUAL = 51; // c5, opcode2 = 1 
    constexpr u8 INVALIDATE_INST_CACHE_INDEX = 52; // c5, opcode2 = 2 
    constexpr u8 FLUSH_PREFETCH_BUFFER = 54; // c5, opcode2 = 4 
    constexpr u8 FLUSH_ENTIRE_BRANCH_TARGET_CACHE = 56; // c5, opcode2 = 6 
    constexpr u8 FLUSH_BRANCH_TARGET_CACHE = 57; // c5, opcode2 = 7 
    constexpr u8 INVALIDATE_ENTIRE_DATA_CACHE = 60; // c6, opcode2 = 0 
    constexpr u8 INVALIDATE_DATA_CACHE_VIRTUAL = 61; // c6, opcode2 = 1 
    constexpr u8 INVALDIATE_DATA_CACHE_INDEX = 62; // c6, opcode_2 = 2
    constexpr u8 INVALIDATE_ENTIRE_UNIFIED_CACHE = 70; // c7, opcode_2 = 0
    constexpr u8 INVALIDATE_UNIFIED_CACHE_LINE_VIRTUAL = 71; // c7, opcode_2 = 1
    constexpr u8 INVALIDATE_UNIFIED_CACHE_LINE_INDEX = 72; // c7, opcode_2 = 2
    constexpr u8 WAIT_FOR_INTERRUPT_ALTERNATIVE = 82; // c8, opcode_2 = 2
    constexpr u8 CLEAN_DATA_CACHE_LINE_VIRTUAL = 101; // c10, opcode_2 = 1
    constexpr u8 CLEAN_DATA_CACHE_LINE_INDEX = 102; // c10, opcode_2 = 2
    constexpr u8 DRAIN_WRITE_BUFFER = 104; // c10, opcode_2 = 4
    constexpr u8 CLEAN_UNIFIED_CACHE_LINE_VIRTUAL = 111; // c11, opcode_2 = 1
    constexpr u8 CLEAN_UNIFIED_CACHE_LINE_INDEX = 112; // c11, opcode_2 = 2
    constexpr u8 PREFETCH_INSTRUCTION_CACHE_LINE = 131; // c13, opcode_2 = 1
    constexpr u8 CLEAN_INVALIDATE_DATA_CACHE_LINE_VIRTUAL = 141; // c14, opcode_2 = 1
    constexpr u8 CLEAN_INVALIDATE_DATA_CACHE_LINE_INDEX = 142; // c14, opcode_2 = 2
    constexpr u8 CLEAN_INVALIDATE_UNIFIED_CACHE_LINE_VIRTUAL= 151; // c15, opcode_2 = 1
    constexpr u8 CLEAN_INVALIDATE_UNIFIED_CACHE_LINE_INDEX = 152; // c15, opcode_2 = 2

    // this only works assuming CRm is 0-15 while opcode_2 is 0-9, creating a unique key
    const u8 function_key = static_cast<u8>((CRm * 10) + opcode_2);
  
    switch (function_key) {
        case WAIT_FOR_INTERRUPT: // TODO
        case INVALIDATE_ENTIRE_INST_CACHE: // TODO
        case INVALIDATE_INST_CACHE_VIRTUAL: // TODO
        case INVALIDATE_INST_CACHE_INDEX: // TODO
        case FLUSH_PREFETCH_BUFFER: // TODO
        case FLUSH_ENTIRE_BRANCH_TARGET_CACHE: // TODO
        case FLUSH_BRANCH_TARGET_CACHE: // TODO
        case INVALIDATE_ENTIRE_DATA_CACHE: // TODO
        case INVALIDATE_DATA_CACHE_VIRTUAL: // TODO
        case INVALDIATE_DATA_CACHE_INDEX: // TODO
        case INVALIDATE_ENTIRE_UNIFIED_CACHE: // TODO
        case INVALIDATE_UNIFIED_CACHE_LINE_VIRTUAL: // TODO
        case INVALIDATE_UNIFIED_CACHE_LINE_INDEX: // TODO
        case WAIT_FOR_INTERRUPT_ALTERNATIVE: // TODO
        case CLEAN_DATA_CACHE_LINE_VIRTUAL: // TODO
        case CLEAN_DATA_CACHE_LINE_INDEX: // TODO
        case DRAIN_WRITE_BUFFER: // TODO
        case CLEAN_UNIFIED_CACHE_LINE_VIRTUAL: // TODO
        case CLEAN_UNIFIED_CACHE_LINE_INDEX: // TODO
        case PREFETCH_INSTRUCTION_CACHE_LINE: // TODO
        case CLEAN_INVALIDATE_DATA_CACHE_LINE_VIRTUAL: // TODO
        case CLEAN_INVALIDATE_DATA_CACHE_LINE_INDEX: // TODO
        case CLEAN_INVALIDATE_UNIFIED_CACHE_LINE_VIRTUAL: // TODO
        case CLEAN_INVALIDATE_UNIFIED_CACHE_LINE_INDEX: // TODO
        default: break;
    }

    // WARNING: be careful to not forget extra functions when adding more features to the 
    // cache in the future, the default case will disable warnings for missing function keys
}