#include "tlb.hpp"

#include "llarm-emu/src/id.hpp"
#include "shared/util.hpp"

void TLB::flush() {
    if (settings.is_mmu_tlb_unified) {
        first_level.clear();
        second_level_coarse.clear();
        second_level_fine.clear();
    } else if (settings.is_mmu_tlb_separate) {
        first_level_inst.clear();
        first_level_data.clear();
        second_level_coarse_inst.clear();
        second_level_coarse_data.clear();
        second_level_fine_inst.clear();
        second_level_fine_data.clear();
    }
}


void TLB::table_walk() {

}


void TLB::invalidate(const u32 virtual_address, const u32 translation_base, const id::tlb_type tlb_type) {
    const u16 table_index = shared::util::bit_range(virtual_address, 20, 31);
    const u32 first_level_address = ((translation_base << 14) | table_index << 2);
    const auto it = first_level.find(first_level_address);

    // check if the entry even exists
    if (it == first_level.end()) {
        return;
    }

    const u32 first_level_descriptor = it->second;

    const u8 descriptor_type_bits = shared::util::bit_range(first_level_descriptor, 0, 1);

    switch (descriptor_type_bits) {
        // section
        case 0b10: 
            switch (tlb_type) {
                case id::tlb_type::UNIFIED: first_level.erase(first_level_address); return;
                case id::tlb_type::SEPARATE_INST: first_level_inst.erase(first_level_address); return;
                case id::tlb_type::SEPARATE_DATA: first_level_data.erase(first_level_address); return;
            }

        // coarse
        case 0b01: {
            const u16 second_level_table_index = shared::util::bit_range(virtual_address, 12, 19);
            const u32 page_table_base_address = shared::util::bit_range(first_level_descriptor, 10, 31);

            const u32 second_level_address = ((page_table_base_address << 10) | (second_level_table_index << 2));
            
            switch (tlb_type) {
                case id::tlb_type::UNIFIED: second_level_coarse.erase(second_level_address); return;
                case id::tlb_type::SEPARATE_INST: second_level_coarse_inst.erase(second_level_address); return;
                case id::tlb_type::SEPARATE_DATA: second_level_coarse_data.erase(second_level_address); return;
            }
        }
        
        // fine
        case 0b11: {
            const u16 second_level_table_index = shared::util::bit_range(virtual_address, 10, 19);
            const u32 page_table_base_address = shared::util::bit_range(first_level_descriptor, 12, 31);

            const u32 second_level_address = ((page_table_base_address << 12) | (second_level_table_index << 2));

            switch (tlb_type) {
                case id::tlb_type::UNIFIED: second_level_fine.erase(second_level_address); return;
                case id::tlb_type::SEPARATE_INST: second_level_fine_inst.erase(second_level_address); return;
                case id::tlb_type::SEPARATE_DATA: second_level_fine_data.erase(second_level_address); return;
            }
        }

        default: return; // not sure what happened
    }
}


// might look noobish calling a function as "function", 
// but this is what the ARM docs call it (see page B3-26)
void TLB::function(const u8 opcode_2, const u8 CRm, const u32 virtual_address, const u32 translation_base) {
    const u8 bytecode = ((opcode_2 << 3) | CRm);

    switch (bytecode) {
        // invalidate entire unified TLB or both instruction and data TLBs
        case 0b0000111: flush(); return;

        // invalidate unified single entry
        case 0b0010111: invalidate(virtual_address, translation_base, id::tlb_type::UNIFIED); return;
            
        // invalidate entire instruction TLB
        case 0b0000101:
            first_level_inst.clear();
            second_level_coarse_inst.clear();
            second_level_fine_inst.clear();
            return;

        // invalidate instruction single entry
        case 0b0010101: invalidate(virtual_address, translation_base, id::tlb_type::SEPARATE_INST); return;

        // invalidate entire data TLB
        case 0b0000110:
            first_level_data.clear();
            second_level_coarse_data.clear();
            second_level_fine_data.clear();
            return;

        // invalidate data single entry
        case 0b0010110: invalidate(virtual_address, translation_base, id::tlb_type::SEPARATE_DATA); return;

        default: return; // TODO UNPREDICTABLE
    }
}