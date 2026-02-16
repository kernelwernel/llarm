#include "tlb.hpp"

#include "structures.hpp"
#include "../../id.hpp"

#include <llarm/shared/out.hpp>

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
        llarm::out::unpredictable("Invalid TLB type mismatch between settings and implementation for TLB entry invalidation, defaulting to entry invalidation in all TLB types");
        unified_table.erase(virtual_address);
        inst_table.erase(virtual_address);
        data_table.erase(virtual_address);
        return;
    }

    switch (tlb_type) {
        case id::tlb_type::UNIFIED: unified_table.erase(virtual_address); return;
        case id::tlb_type::SEPARATE: llarm::out::dev_error("Unsupported TLB invalidation");
        case id::tlb_type::SEPARATE_INST: inst_table.erase(virtual_address); return;
        case id::tlb_type::SEPARATE_DATA: data_table.erase(virtual_address); return; 
    }
}


void TLB::auto_replace(const id::tlb_type tlb_type, const u32 virtual_address, const u32 physical_address) {
    // random replacement strategy, i guess different strategies could be added in the future

    auto generate_index = [this, tlb_type]() -> u16 {
        const u64 r = random.generate();
        u16 tlb_size = 0;

        switch (tlb_type) {
            case id::tlb_type::UNIFIED: tlb_size = settings.unified_tlb_table_size; break;
            case id::tlb_type::SEPARATE: llarm::out::dev_error("Unsupported TLB invalidation for auto replacement");
            case id::tlb_type::SEPARATE_INST: tlb_size = settings.inst_tlb_table_size; break;
            case id::tlb_type::SEPARATE_DATA: tlb_size = settings.data_tlb_table_size; break;
        }

        const u32 range = tlb_size + 1;

        return static_cast<u16>(r % range);
    };

    const bool already_exists = is_translation_cached(virtual_address).is_found;

    // this will work by deleting the previous entry in the TLB that occupied that random index,
    // and then it'll insert that new entry. It's pretty simple, but if the virtual address being
    // inserted already exists in the TLB, then that specific entry will be replaced instead of
    // replacing a random index. This prevents duplicate entries for the same virtual address. 

    switch (tlb_type) {
        case id::tlb_type::UNIFIED: {
            if (already_exists) {
                invalidate(virtual_address, tlb_type);
            } else {
                const u32 unified_key = unified_table.at(generate_index());
                unified_table.erase(unified_key);
            }

            unified_table.insert({ virtual_address, physical_address });
            return;
        }

        case id::tlb_type::SEPARATE: llarm::out::dev_error("Unsupported TLB invalidation for auto replacement");

        case id::tlb_type::SEPARATE_INST: {
            if (already_exists) {
                invalidate(virtual_address, tlb_type);
            } else {
                const u32 inst_key = inst_table.at(generate_index());
                inst_table.erase(inst_key);
            }

            inst_table.insert({ virtual_address, physical_address });
            return;
        }

        case id::tlb_type::SEPARATE_DATA: {
            if (already_exists) {
                invalidate(virtual_address, tlb_type);
            } else {
                const u32 data_key = data_table.at(generate_index());
                data_table.erase(data_key);
            }

            data_table.insert({ virtual_address, physical_address });
            return;
        }
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

    llarm::out::dev_error("Impossible TLB entry fetch");
}


void TLB::insert(const u32 virtual_address, const u32 physical_address, const id::tlb_type tlb_type) {
    switch (tlb_type) {
        case id::tlb_type::UNIFIED: 
            if (unified_table.size() == settings.unified_tlb_table_size) {
                auto_replace(id::tlb_type::UNIFIED, virtual_address, physical_address);
            }
            return;

        case id::tlb_type::SEPARATE: llarm::out::dev_error("Unsupported TLB invalidation for insertion");
        case id::tlb_type::SEPARATE_INST:
            if (inst_table.size() == settings.inst_tlb_table_size) {
                auto_replace(id::tlb_type::SEPARATE_INST, virtual_address, physical_address);
            }
            return;

        case id::tlb_type::SEPARATE_DATA:
            if (data_table.size() == settings.data_tlb_table_size) {
                auto_replace(id::tlb_type::SEPARATE_DATA, virtual_address, physical_address);
            }
            return;
    }
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

    llarm::out::dev_error("Invalid configuration for TLB type");
}


// might look noobish calling a function as "function", 
// but this is what the ARM docs call it (see page B3-26)
void TLB::function(const u8 opcode_2, const u8 CRm, const u32 virtual_address) {
    const u8 bytecode = static_cast<u8>((opcode_2 << 3) | CRm);

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
            llarm::out::unpredictable("Unknown TLB function");
            return;
    }
}


TLB::TLB(SETTINGS& settings) : 
    settings(settings),
    random(settings.tlb_seed)
{
    unified_table.reserve(settings.unified_tlb_table_size);
    inst_table.reserve(settings.inst_tlb_table_size);
    data_table.reserve(settings.data_tlb_table_size);

    if (settings.is_mmu_enabled == false) {
        return;
    }

    // read B3-27 for more context
    if (settings.is_tlb_unified) {
        W_unified = static_cast<u32>(std::ceil(std::log2(settings.unified_tlb_table_size)));
    } else if (settings.is_tlb_separate) {
        W_inst = static_cast<u32>(std::ceil(std::log2(settings.inst_tlb_table_size)));
        W_data = static_cast<u32>(std::ceil(std::log2(settings.data_tlb_table_size)));
    }
}