#include "tlb.hpp"

#include "structures.hpp"
#include "../../id.hpp"

#include "shared/out.hpp"

#include <cmath>


void TLB::flush() {
    if (settings.tlb_type == id::tlb_type::UNIFIED) {
        unified_table.clear(); 
        return;
    }

    // flushing a separate TLB type would flush both 
    inst_table.clear(); 
    data_table.clear(); 
}


void TLB::invalidate(const u32 virtual_address, const id::tlb_type tlb_type) {
    if (is_type_invalid(tlb_type)) {
        shared::out::unpredictable("Invalid TLB type mismatch between settings and implementation for TLB entry invalidation, defaulting to entry invalidation in all TLB types");
        unified_table.erase(virtual_address);
        inst_table.erase(virtual_address);
        data_table.erase(virtual_address);
        return;
    } 

    switch (tlb_type) {
        case id::tlb_type::UNIFIED: unified_table.erase(virtual_address); return;
        case id::tlb_type::SEPARATE: shared::out::dev_error("Unsupported TLB invalidation");
        case id::tlb_type::SEPARATE_INST: inst_table.erase(virtual_address); return;
        case id::tlb_type::SEPARATE_DATA: data_table.erase(virtual_address); return; 
    }
}


u32 TLB::fetch(const u32 virtual_address, const tlb_fetch_struct tlb_fetch) {
    if (settings.tlb_type == id::tlb_type::UNIFIED) {
        return unified_table.at(virtual_address);
    }

    if (tlb_fetch.is_in_inst_table) {
        return inst_table.at(virtual_address);
    } else if (tlb_fetch.is_in_data_table) {
        return data_table.at(virtual_address);
    }

    shared::out::dev_error("Impossible TLB entry fetch");
}


tlb_fetch_struct TLB::is_translation_cached(const u32 virtual_address) {
    if (settings.tlb_type == id::tlb_type::UNIFIED) {
        return tlb_fetch_struct {
            /* is_found */ (unified_table.find(virtual_address) != unified_table.end()),
            /* is_in_unified_table */ true,
            /* is_in_inst_table */ false,
            /* is_in_data_table */ false
        };
    }

    // assume it's a separate TLB from this point

    if (inst_table.find(virtual_address) != inst_table.end()) {
        return tlb_fetch_struct {
            /* is_found */ true,
            /* is_in_unified_table */ false,
            /* is_in_inst_table */ true,
            /* is_in_data_table */ false
        };
    } else if (data_table.find(virtual_address) != data_table.end()) {
        return tlb_fetch_struct {
            /* is_found */ true,
            /* is_in_unified_table */ false,
            /* is_in_inst_table */ false,
            /* is_in_data_table */ true
        };
    }

    return tlb_fetch_struct {
        /* is_found */ false,
        /* is_in_unified_table */ false,
        /* is_in_inst_table */ false,
        /* is_in_data_table */ false
    };
}


bool TLB::is_type_invalid(const id::tlb_type tlb_type) {
    if (settings.tlb_type == id::tlb_type::UNIFIED) {
        return tlb_type != id::tlb_type::UNIFIED;
    } else if (settings.tlb_type == id::tlb_type::SEPARATE) {
        return tlb_type == id::tlb_type::UNIFIED;
    }

    shared::out::dev_error("Invalid configuration for TLB type");
}


// might look noobish calling a function as "function", 
// but this is what the ARM docs call it (see page B3-26)
void TLB::function(const u8 opcode_2, const u8 CRm, const u32 virtual_address) {
    const u8 bytecode = ((opcode_2 << 3) | CRm);

    switch (bytecode) {
        // invalidate entire unified TLB or both instruction and data TLBs
        case 0b0000111: 
            flush(); 
            return;

        // invalidate unified single entry
        case 0b0010111: 
            invalidate(virtual_address, id::tlb_type::UNIFIED); 
            return;
            
        // invalidate entire instruction TLB
        case 0b0000101:
            inst_table.clear();
            return;

        // invalidate instruction single entry
        case 0b0010101: 
            invalidate(virtual_address, id::tlb_type::SEPARATE_INST); 
            return;

        // invalidate entire data TLB
        case 0b0000110:
            data_table.clear();
            return;

        // invalidate data single entry
        case 0b0010110: 
            invalidate(virtual_address, id::tlb_type::SEPARATE_DATA); 
            return;

        default: 
            shared::out::unpredictable("Unknown TLB function");
            return;
    }
}


TLB::TLB(SETTINGS& settings) : settings(settings) {
    // read B3-27 for more context
    if (settings.is_tlb_unified) {
        W_unified = static_cast<u32>(std::ceil(std::log2(settings.unified_tlb_entry_size)));
    } else if (settings.is_tlb_separate) {
        W_inst = static_cast<u32>(std::ceil(std::log2(settings.inst_tlb_entry_size)));
        W_data = static_cast<u32>(std::ceil(std::log2(settings.data_tlb_entry_size)));
    }
    
    unified_table.reserve(settings.unified_tlb_entry_size);
    inst_table.reserve(settings.inst_tlb_entry_size);
    data_table.reserve(settings.data_tlb_entry_size);
}