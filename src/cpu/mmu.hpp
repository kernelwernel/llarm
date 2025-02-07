#include "ram.hpp"
#include "coprocessor.hpp"
#include "types.hpp"
#include "globals.hpp"
#include "utility.hpp"

#include <map>

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
    COPROCESSOR& coprocessor;

    // page/block sizes
    constexpr u32 tiny_page = util::get_kb(1); // 1KB
    constexpr u32 small_page = util::get_kb(4); // 4KB
    constexpr u32 large_page = util::get_kb(64); // 64KB

    // section size
    constexpr u32 section = util::get_mb(1); // 1MB



    // translation lookaside buffers
    
    // holds section translations and pointers to second level table indexes
    std::map<u32, u32> first_level_table {};

    std::map<u32, u32> second_level_table_coarse {}; // holds large and small page translations (256)
    std::map<u32, u32> second_level_table_fine {}; // holds large, small, and tiny page translations (B3-7) (1024)


    bool is_mmu_enabled() {
        return (coprocessor.read(id::cp::CP15_R1_M) == true);
    }


    // specific to is_access_permission_invalid
    consteval u8 make_bytecode(
        const u8 AP_bits, 
        const bool S,
        const bool R,
        const bool is_privileged
    ) {
        return (
            !is_privileged |
            (is_privileged << 1) |
            (R << 2) |
            (S << 3) |
            (AP_bits << 4)
        );
    }



    bool is_access_permission_invalid(const u8 raw_AP_bits, const id::access_type access_type) {
        // since all the AP bits that aren't 0 WITH privileged permissions 
        // are all read/write, we're doing a small shortcut here to avoid
        // the costlier option of further investigating if the access is valid.
        if ((raw_AP_bits != 0) && globals.is_privileged) {
            return true;
        }

        // the AP == 0 is added because the S and R bits are irrelevant if the AP is anything other than 00
        const bool S = (coprocessor.read(id::cp::CP15_R1_S) & (raw_AP_bits == 0b00));
        const bool R = (coprocessor.read(id::cp::CP15_R1_R) & (raw_AP_bits == 0b00)); 

        // fetching the access permission depends entirely on the AP, S, R, and mode.
        // so instead of creating a labyrinth of convoluted if conditions, i'm adding
        // all of those to a concatenated u8 byte. Not only because that's faster
        // and switch-friendly, but also because it's much easier to handle that way.
        // the full table is situation in B3-16 which should make more sense.
        const u8 bytecode = (
            !globals.is_privileged |
            (globals.is_privileged << 1) |
            (R << 2) |
            (S << 3) |
            (raw_AP_bits << 4)
        );
        //make_bytecode(raw_AP_bits, S, R, globals.is_privileged);

        id::access_perm AP_id;

        switch (bytecode) {
            case make_bytecode(0b00, false, false, false): AP_id = id::access_perm::NO_ACCESS; break; // AP = 00, user
            case make_bytecode(0b00, false, false, true):  AP_id = id::access_perm::NO_ACCESS; break; // AP = 00, priv
            case make_bytecode(0b00, true, false, false):  AP_id = id::access_perm::NO_ACCESS; break; // AP = 00, user, S
            case make_bytecode(0b00, true, false, true):   AP_id = id::access_perm::READ_ONLY; break; // AP = 00, priv, S
            case make_bytecode(0b00, false, true, false):  AP_id = id::access_perm::READ_ONLY; break; // AP = 00, user, R
            case make_bytecode(0b00, false, true, true):   AP_id = id::access_perm::READ_ONLY; break; // AP = 00, priv, R
            case make_bytecode(0b00, true, true, false):   AP_id = id::access_perm::UNPREDICTABLE; break; // AP = 00, user, S, R
            case make_bytecode(0b00, true, true, true):    AP_id = id::access_perm::UNPREDICTABLE; break; // AP = 00, priv, S, R
            case make_bytecode(0b01, false, false, false): AP_id = id::access_perm::NO_ACCESS;  break;  // AP = 01, user
            case make_bytecode(0b01, false, false, true):  AP_id = id::access_perm::READ_WRITE; break; // AP = 01, priv
            case make_bytecode(0b10, false, false, false): AP_id = id::access_perm::READ_ONLY;  break;  // AP = 10, user
            case make_bytecode(0b10, false, false, true):  AP_id = id::access_perm::READ_WRITE; break; // AP = 10, priv
            case make_bytecode(0b11, false, false, false): AP_id = id::access_perm::READ_WRITE; break; // AP = 11, user
            case make_bytecode(0b11, false, false, true):  AP_id = id::access_perm::READ_WRITE; break; // AP = 11, priv
            default: out::error("something went horribly wrong here...");
        }

        switch (AP_id) {
            case id::access_perm::READ_WRITE: 
                return (
                    (access_type == id::access_type::READ_WRITE) ||
                    (access_type == id::access_type::READ) ||
                    (access_type == id::access_type::WRITE)
                );
            case id::access_perm::READ_ONLY: 
                return (
                    (access_type == id::access_type::READ_WRITE) ||
                    (access_type == id::access_type::READ)
                );
            case id::access_perm::NO_ACCESS: return false;
            case id::access_perm::UNPREDICTABLE: return true; // TODO: add unpredictability log here
        }
    }




    id::first_level get_first_level_entry_id(const u32 entry) {
        switch (entry & 0b11) {
            case 0b00: return id::first_level::FAULT;
            case 0b01: return id::first_level::COARSE;
            case 0b10: return id::first_level::SECTION;
            case 0b11: return id::first_level::FINE;
        }
    }

    id::second_level get_second_level_entry_id(const u8 entry) {
        switch (entry & 0b11) {
            case 0b00: return id::second_level::FAULT;
            case 0b01: return id::second_level::LARGE;
            case 0b10: return id::second_level::SMALL;
            case 0b11: return id::second_level::TINY;
        }
    }

    u32 first_level_fetch(const u32 key) {
        auto it = first_level_table.find(key);

        if (it != first_level_table.end()) {
            return it->second;
        } else {
            // not found, do a table walk (i think)
        }
    }

    u32 second_level_fetch(const u32 key, const id::first_level first_level_type) {
        switch (first_level_type) {
            case id::first_level::FINE: 
                auto it = second_level_table_fine.find(key);

                if (it != second_level_table_fine.end()) {
                    return it->second;
                } else {
                    // not found, do a table walk (i think)
                }

            case id::first_level::COARSE: 
                auto it = second_level_table_coarse.find(key);

                if (it != second_level_table_coarse.end()) {
                    return it->second;
                } else {
                    // not found, do a table walk (i think)
                }
        }
    }

    id::access_domain fetch_domain(const u8 raw_domain_bits) {
        u8 cp_domain_bits = 0;

        switch (raw_domain_bits) {
            case 0:  cp_domain_bits = coprocessor.read(id::cp::CP15_R3_MMU_D0);  break;
            case 1:  cp_domain_bits = coprocessor.read(id::cp::CP15_R3_MMU_D1);  break;
            case 2:  cp_domain_bits = coprocessor.read(id::cp::CP15_R3_MMU_D2);  break;
            case 3:  cp_domain_bits = coprocessor.read(id::cp::CP15_R3_MMU_D3);  break;
            case 4:  cp_domain_bits = coprocessor.read(id::cp::CP15_R3_MMU_D4);  break;
            case 5:  cp_domain_bits = coprocessor.read(id::cp::CP15_R3_MMU_D5);  break;
            case 6:  cp_domain_bits = coprocessor.read(id::cp::CP15_R3_MMU_D6);  break;
            case 7:  cp_domain_bits = coprocessor.read(id::cp::CP15_R3_MMU_D7);  break;
            case 8:  cp_domain_bits = coprocessor.read(id::cp::CP15_R3_MMU_D8);  break;
            case 9:  cp_domain_bits = coprocessor.read(id::cp::CP15_R3_MMU_D9);  break;
            case 10: cp_domain_bits = coprocessor.read(id::cp::CP15_R3_MMU_D10); break;
            case 11: cp_domain_bits = coprocessor.read(id::cp::CP15_R3_MMU_D11); break;
            case 12: cp_domain_bits = coprocessor.read(id::cp::CP15_R3_MMU_D12); break;
            case 13: cp_domain_bits = coprocessor.read(id::cp::CP15_R3_MMU_D13); break;
            case 14: cp_domain_bits = coprocessor.read(id::cp::CP15_R3_MMU_D14); break;
            case 15: cp_domain_bits = coprocessor.read(id::cp::CP15_R3_MMU_D15); break;
        }

        switch (cp_domain_bits) {
            case 0b00: return id::access_domain::NO_ACCESS;
            case 0b01: return id::access_domain::CLIENT;
            case 0b10: return id::access_domain::RESERVED;
            case 0b11: return id::access_domain::MANAGER;
        }
    }    


    u32 first_section(const u32 entry, const u32 address, const id::access_type access) {
        const u8 raw_domain_bits = (entry & (0b1111 << 5));

        const id::access_domain domain = fetch_domain(raw_domain_bits);

        switch (domain) {
            case id::access_domain::NO_ACCESS: // domain fault    break;
            case id::access_domain::RESERVED: // TODO add warning    break;
            case id::access_domain::MANAGER: break;
            case id::access_domain::CLIENT: 
                const u8 AP = (entry & (0b11 << 10)); 

                if (is_access_permission_invalid(AP, access)) {
                    // TODO: section permission fault
                }
        }
    
        const bool B = (entry & (1 << 2));
        const bool C = (entry & (1 << 3));
        
        const u32 section_base_address = 0;

        const u32 section_index = util::bit_fetcher(address, 0, 12); 
        const u32 physical_address = (section_base_address << 20) | section_index;

        return physical_address;
    }


    // B3-9
    u32 first_coarse(const u32 entry, const u32 address) {
        const u32 page_table_base_address = util::bit_fetcher(entry, 10, 31);

        const u8 second_level_table_index = util::bit_fetcher(address, 12, 19);
        
        const u32 second_level_descriptor_address = (
            (page_table_base_address << 10) |
            (second_level_table_index << 2)
        );

        return second_level_descriptor_address;
    }


    // B3-10
    u32 first_fine(const u32 entry, const u32 address) {
        const u32 page_table_base_address = util::bit_fetcher(entry, 12, 31);

        const u8 second_level_table_index = util::bit_fetcher(address, 10, 19);
        
        const u32 second_level_descriptor_address = (
            (page_table_base_address << 12) |
            (second_level_table_index << 2)
        );

        return second_level_descriptor_address;
    }






















    u32 second_large(const u32 entry, const u32 address, const id::access_type access, const u8 raw_domain_bits) {
        // TODO
        //if (is_access_permission_invalid(AP, access)) {
        //    // TODO: permission fault
        //}

    }


    u32 second_small(const u32 entry, const u32 address, const id::access_type access, const u8 raw_domain_bits) {
        // TODO
        //if (is_access_permission_invalid(AP, access)) {
        //    // TODO: permission fault
        //}
    
        const bool C = (entry & (1 << 3));
        const bool B = (entry & (1 << 2));

        const u8 AP0 = util::bit_fetcher(entry, 4, 5);
        const u8 AP1 = util::bit_fetcher(entry, 6, 7);
        const u8 AP2 = util::bit_fetcher(entry, 8, 9);
        const u8 AP3 = util::bit_fetcher(entry, 10, 11);

        const u32 small_page_base_address = util::bit_fetcher(entry, 12, 31);
        const u16 page_index = util::bit_fetcher(address, 0, 11);

        const u32 physical_address = ((small_page_base_address << 12) | page_index);

        return physical_address;
    }


    u32 second_tiny(const u32 entry, const u32 address, const id::access_type access, const u8 raw_domain_bits) {
        const u8 AP = util::bit_fetcher(entry, 4, 5);

        if (is_access_permission_invalid(AP, access)) {
            // TODO: permission fault
        }

        const bool C = (entry & (1 << 3));
        const bool B = (entry & (1 << 2));

        const u32 tiny_page_base_address = util::bit_fetcher(entry, 10, 31);
        const u16 page_index = util::bit_fetcher(address, 0, 9);

        const u32 physical_address = ((tiny_page_base_address << 10) | page_index);

        return physical_address;
    }

public:
    // translate the virtual address to a physical address
    u32 mmu_translate_address(const u32 address, const id::access_type access_type, const u8 access_byte_size) {
        if (
            (coprocessor.read(id::cp::CP15_R1_A)) && // check if allignment fault is enabled
            (access_type != id::access_type::INSTRUCTION_FETCH)
        ) {
            switch (access_byte_size) {
                case 1: /* byte */ 
                    break; // there are no alignment faults for byte accesses

                case 2: /* halfword */
                    if ((address & 1) != 0) {
                        // alignment fault
                    }
                    break;

                case 4: /* word*/
                    if ((address & 0b11) != 0b00) {
                        // alignment fault
                    }
                    break;

                default: out::error(); // TODO
            }
        }

        const u32 translation_base = coprocessor.read(id::cp::CP15_R2_MMU_TRANSLATION_BASE); // TODO: optimise this with direct register access
        const u32 table_index = util::bit_fetcher(address, 20, 31);

        const u32 first_level_descriptor_address = ((translation_base << 14) | (table_index << 2));

        const u32 first_level_entry = first_level_fetch(first_level_descriptor_address);

        u32 second_key = 0;

        switch (get_first_level_entry_id(first_level_entry)) {
            case id::first_level::FAULT: return 0; // TODO: translation fault
            case id::first_level::COARSE: second_key = first_coarse(first_level_entry); break;
            case id::first_level::FINE: second_key = first_coarse(first_level_entry); break;
            case id::first_level::SECTION: return first_section(first_level_entry, address, access_type);
        };

        const u32 second_level_entry = second_level_fetch(second_key);

        const id::second_level entry_id = get_second_level_entry_id(second_level_entry);

        const u8 raw_domain_bits = 0;

        if (entry_id != id::second_level::FAULT) {
            raw_domain_bits = util::bit_fetcher(first_level_entry, 5, 8);
        }

        switch (entry_id) {
            case id::second_level::FAULT: return 0; // TODO: translation fault
            case id::second_level::LARGE: return second_large(second_level_entry, address, access_type, raw_domain_bits);
            case id::second_level::SMALL: return second_small(second_level_entry, address, access_type, raw_domain_bits);
            case id::second_level::TINY:  return second_tiny(second_level_entry, address, access_type, raw_domain_bits);
        }
    }



    void table_walk();


    void flush_tlb() {
        first_level_table.clear();
        second_level_table.clear();
    }


    MMU(GLOBALS& globals, RAM& ram, COPROCESSOR& coprocessor) : globals(globals), ram(ram), coprocessor(coprocessor) {
        
    }
};



    /*
     * MMU NOTES:
     *
     * - For caches and write buffers which are not allowed to be enabled while the MMU is disabled, 
     *   the values of the C and B bits for a memory access are irrelevant.
     *
     * - For caches and write buffers which are allowed to be enabled while the MMU is disabled, a
     *   data access is treated as uncachable and unbufferable (C == 0, B == 0). An instruction fetch is
     *   treated as uncachable (C == 0) in a system with a unified TLB, and as cachable (C == 1) in a
     *   system with a separate instruction TLB.
     * 
     * - when the MMU is disabled, no aborts are generated
     * 
     * - Before the MMU is enabled, suitable translation tables must be set up 
     *   in memory and all relevant CP15 registers must be programmed.
     * 
     * 
     * PU NOTES:
     *  - virtual addresses are the same as the physical address (except if FCSE is enabled)
     *  - does not have a TLB
     * 
     * 
     * MEMORY SIZES:
     * - Sections are comprised of 1MB blocks of memory.
     * 
     * - Three different page sizes are supported:
     *   - Tiny pages: Consist of 1KB blocks of memory.
     *   - Small pages: Consist of 4KB blocks of memory.
     *   - Large pages: Consist of 64KB blocks of memory.
     * 
     * CP15 reg 2 is the translation table base register:
     *  - the first-level page table must reside on a 16KB boundary.
     *  - bits 31:14 are significant, 13:0 should be 0
     * 
     * 
     * 
     * 
     * 
     * Fine page tables are used to hold large, small and 
     * tiny pages. Coarse page tables can only hold large 
     * and small pages. A coarse page table holds 256 32-bit 
     * entries, making it hold 4KB of data. A fine page table holds 1024 
     * 32-bit entries but with 1KB in size. When bits[1:0] of the Level
     * 1 descriptor are set to 01 this indicates memory access 
     * is to a coarse page. When bits[1:0] of the Level 1 
     * descriptor are set to 11 this indicates memory access 
     * is to a fine page. In both 01 and 11 cases a Level 2 
     * descriptor is required to determine the page type
     * 
     * 
     * 
     * 
     * TRANSLATION PROCESS:
     * 1: look up the address in the TLB
     * 2. if it doesn't have a unified TLB:
     *   2a: if it's an instruction address, fetch from instruction TLB
     *   2b: if it's a data address, fetch from data TLB
     *   2c: else, fetch from the unified TLB
     * 3: if the TLB doesn't have an address hit, do a translation table walk
     * 4: retrieve the translation and access permission information from the translation table
     * 5: when the address is finally retrieved, put that in the TLB
     *   5a: write it by either in a currently unused entry 
     *   5b: or by overwriting an existing entry
     */
