#include "cache.hpp"
#include "src/id.hpp"


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


u32 CACHE::find_victim_way(const u32 set) {
    for (u32 way = 0; way < DATA_ASSOCIATIVITY; ++way) {
        if (!data_line(set, way).valid) {
            return way;
        }
    }
    return 0;
}


void CACHE::evict_if_dirty(cache_line& victim, const u32 set) {
    if (!victim.dirty) {
        return;
    }

    const u32 base = (((victim.tag * DATA_NSETS) + set) * DATA_LINELEN);
    for (u32 i = 0; i < DATA_LINELEN; ++i) {
        ram.write(base + i, static_cast<u64>(victim.data.at(i)), 1);
    }
}


void CACHE::fill_line(cache_line& victim, const u32 line_base) {
    for (u32 i = 0; i < DATA_LINELEN; ++i) {
        victim.data.at(i) = static_cast<u8>(ram.read(line_base + i, 1));
    }
}


u32 CACHE::read_line(const cache_line& line, const u32 pos) const {
    u32 value = 0;
    for (u8 i = 0; i < 4; ++i) {
        value |= static_cast<u32>(line.data.at((pos + i) % DATA_LINELEN)) << (i * 8);
    }
    return value;
}


void CACHE::write(
    const u32 virtual_address, 
    const u32 physical_address, 
    const u32 value, 
    const u8 size, 
    const bool is_write_bufferable
) {
    // cache access checks, read B5-8 for more information
    if ((settings.cache_type == id::cache_type::WRITE_BACK) && is_write_bufferable) {
        llarm::out::unpredictable("write-back only cache has no bufferability bit");
    }
 
    const u32 offset = virtual_address % DATA_LINELEN;
    const u32 set = (virtual_address / DATA_LINELEN) % DATA_NSETS;
    const u32 tag = virtual_address / (static_cast<u32>(DATA_LINELEN) * DATA_NSETS);

    for (u32 way = 0; way < DATA_ASSOCIATIVITY; ++way) {
        cache_line& line = data_line(set, way);

        if (!(line.valid && line.tag == tag)) {
            continue;
        }

        // cache hit: write bytes into the line
        for (u8 i = 0; i < size; ++i) {
            line.data.at((offset + i) % DATA_LINELEN) = static_cast<u8>((value >> (i * 8)) & 0xFF);
        }

        if (settings.cache_type == id::cache_type::WRITE_BACK) {
            line.dirty = true;
        } else {
            // write-through: propagate to RAM on every write
            ram.write(physical_address, static_cast<u64>(value), size);
        }

        return;
    }

    // cache miss
    if (settings.cache_type == id::cache_type::WRITE_THROUGH) {
        // no write-allocate: bypass cache and write directly to RAM
        ram.write(physical_address, static_cast<u64>(value), size);
        return;
    }

    // write-back miss: write-allocate, bring the line in, then write to it
    cache_line& victim = data_line(set, find_victim_way(set));

    evict_if_dirty(victim, set);
    fill_line(victim, physical_address - offset);

    victim.tag   = tag;
    victim.valid = true;

    for (u8 i = 0; i < size; ++i) {
        victim.data.at((offset + i) % DATA_LINELEN) = static_cast<u8>((value >> (i * 8)) & 0xFF);
    }

    victim.dirty = true;
}


u32 CACHE::read(const u32 virtual_address, const u32 physical_address, const bool is_write_bufferable) {
    // cache access checks, read B5-8 for more information
    if ((settings.cache_type == id::cache_type::WRITE_BACK) && is_write_bufferable) {
        llarm::out::unpredictable("write-back only cache has no bufferability bit");
    }

    const u32 pos = virtual_address % DATA_LINELEN;
    const u32 set = (virtual_address / DATA_LINELEN) % DATA_NSETS;
    const u32 tag = virtual_address / (static_cast<u32>(DATA_LINELEN) * DATA_NSETS);

    // cache hit: valid line with matching tag
    for (u32 way = 0; way < DATA_ASSOCIATIVITY; ++way) {
        cache_line& line = data_line(set, way);

        if (!(line.valid && line.tag == tag)) {
            continue;
        }

        return read_line(line, pos);
    }

    // cache miss: prefer an invalid way, else evict way 0
    cache_line& victim = data_line(set, find_victim_way(set));

    evict_if_dirty(victim, set);
    fill_line(victim, physical_address - pos);

    victim.tag = tag;
    victim.valid = true;
    victim.dirty = false;

    const u32 value = read_line(victim, pos);

    return value;
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
        case DRAIN_WRITE_BUFFER: return; // llarm does not implement a write buffer
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