#include "../../utility.hpp"
#include "../coprocessor/coprocessor.hpp"
#include "../globals.hpp"
#include "ram.hpp"
#include <llarm/shared/out.hpp>
#include "structures.hpp"

#include "mmu.hpp"

#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>

/**
 * SMALL LEXICON FOR ANYBODY READING THIS:
 *   B = bufferability
 *   C = cachability
 *   AP = access permission
 */


id::first_level MMU::get_first_level_id(const u32 entry) {
    switch (entry & 0b11) {
        case 0b00: return id::first_level::FAULT;
        case 0b01: return id::first_level::COARSE;
        case 0b10: return id::first_level::SECTION;
        case 0b11: return id::first_level::FINE;
        default: llarm::out::error("Something went horribly wrong, todo"); // dev error TODO
    }
}


id::second_level MMU::get_second_level_id(const u32 entry) {
    switch (entry & 0b11) {
        case 0b00: return id::second_level::FAULT;
        case 0b01: return id::second_level::LARGE;
        case 0b10: return id::second_level::SMALL;
        case 0b11: return id::second_level::TINY;
        default: llarm::out::error("Something went horribly wrong, todo"); // dev error TODO
    }
}


id::access_domain MMU::fetch_domain(const u8 raw_domain_bits) {
    u8 cp_domain_bits = 0;

    switch (raw_domain_bits) {
        case 0:  cp_domain_bits = static_cast<u8>(coprocessor.read(id::cp15::R3_MMU_D0));  break;
        case 1:  cp_domain_bits = static_cast<u8>(coprocessor.read(id::cp15::R3_MMU_D1));  break;
        case 2:  cp_domain_bits = static_cast<u8>(coprocessor.read(id::cp15::R3_MMU_D2));  break;
        case 3:  cp_domain_bits = static_cast<u8>(coprocessor.read(id::cp15::R3_MMU_D3));  break;
        case 4:  cp_domain_bits = static_cast<u8>(coprocessor.read(id::cp15::R3_MMU_D4));  break;
        case 5:  cp_domain_bits = static_cast<u8>(coprocessor.read(id::cp15::R3_MMU_D5));  break;
        case 6:  cp_domain_bits = static_cast<u8>(coprocessor.read(id::cp15::R3_MMU_D6));  break;
        case 7:  cp_domain_bits = static_cast<u8>(coprocessor.read(id::cp15::R3_MMU_D7));  break;
        case 8:  cp_domain_bits = static_cast<u8>(coprocessor.read(id::cp15::R3_MMU_D8));  break;
        case 9:  cp_domain_bits = static_cast<u8>(coprocessor.read(id::cp15::R3_MMU_D9));  break;
        case 10: cp_domain_bits = static_cast<u8>(coprocessor.read(id::cp15::R3_MMU_D10)); break;
        case 11: cp_domain_bits = static_cast<u8>(coprocessor.read(id::cp15::R3_MMU_D11)); break;
        case 12: cp_domain_bits = static_cast<u8>(coprocessor.read(id::cp15::R3_MMU_D12)); break;
        case 13: cp_domain_bits = static_cast<u8>(coprocessor.read(id::cp15::R3_MMU_D13)); break;
        case 14: cp_domain_bits = static_cast<u8>(coprocessor.read(id::cp15::R3_MMU_D14)); break;
        case 15: cp_domain_bits = static_cast<u8>(coprocessor.read(id::cp15::R3_MMU_D15)); break;
    }

    switch (cp_domain_bits) {
        case 0b00: return id::access_domain::NO_ACCESS;
        case 0b01: return id::access_domain::CLIENT;
        case 0b10: return id::access_domain::RESERVED;
        case 0b11: return id::access_domain::MANAGER;
        default: llarm::out::dev_error("Unknown coprocessor domain bits provided");
    }
}


u8 MMU::fetch_subpage_AP(const u8 subpage, const u32 entry) {
    switch (subpage) {
        case 0: return llarm::util::bit_range<u8>(entry, 4, 5);
        case 1: return llarm::util::bit_range<u8>(entry, 6, 7);
        case 2: return llarm::util::bit_range<u8>(entry, 8, 9);
        case 3: return llarm::util::bit_range<u8>(entry, 10, 11);
        default: llarm::out::dev_error("Failure to deduce subpage index for page descriptor"); 
    }
}


translation_struct MMU::first_section(const u32 entry, const u32 address, const u8 access_size, const id::access_type access_type) {
    const u8 domain_bits = llarm::util::bit_range<u8>(entry, 5, 8);
    const id::access_domain domain = fetch_domain(domain_bits);

    const u8 AP = llarm::util::bit_range<u8>(entry, 10, 11);

    const id::aborts abort_code = check_block_access(AP, access_type, domain, id::memory_type::SECTION);

    const bool has_failed = (abort_code != id::aborts::NO_ABORT);

    if (has_failed) {
        manage_abort(abort_code, address, domain_bits);
        return translation_struct {
            /* has_failed */ true,
            /* abort_code */ abort_code,
            /* physical_address */ 0
        };
    }

    // const bool B = llarm::util::bit_fetch(entry, 2); // TODO DO SOMETHING WITH THESE
    // const bool C = llarm::util::bit_fetch(entry, 3); // TODO DO SOMETHING WITH THESE
    
    const u32 section_base_address = 0;

    const u32 section_index = llarm::util::bit_range(address, 0, 12); 
    const u32 physical_address = (section_base_address << 20) | section_index;

    return translation_struct {
        /* has_failed */ false,
        /* abort_code */ id::aborts::NO_ABORT,
        /* physical_address */ physical_address
    };
}


// B3-9
u32 MMU::first_coarse(const u32 entry, const u32 address) {
    const u32 page_table_base_address = llarm::util::bit_range(entry, 10, 31);

    const u8 second_level_index = llarm::util::bit_range<u8>(address, 12, 19);
    
    const u32 second_level_descriptor_address = (
        (page_table_base_address << 10) |
        (static_cast<u32>(second_level_index) << 2)
    );

    return second_level_descriptor_address;
}


// B3-10
u32 MMU::first_fine(const u32 entry, const u32 address) {
    const u32 page_table_base_address = llarm::util::bit_range(entry, 12, 31);

    const u8 second_level_index = llarm::util::bit_range<u8>(address, 10, 19);
    
    const u32 second_level_descriptor_address = (
        (page_table_base_address << 12) |
        (u32(second_level_index) << 2)
    );

    return second_level_descriptor_address;
}


bool MMU::is_AP_invalid(const u8 raw_AP_bits, const id::access_type access_type) {
    // since all the AP bits that aren't 0 WITH privileged permissions 
    // are all read/write, we're doing a small shortcut here to avoid
    // the costlier option of further investigating if the access is valid.
    if ((raw_AP_bits != 0) && globals.is_privileged) {
        return true;
    }

    // the AP == 0 is added because the S and R bits are irrelevant if the AP is anything other than 00
    const bool S = (coprocessor.read(id::cp15::R1_S) & (raw_AP_bits == 0b00));
    const bool R = (coprocessor.read(id::cp15::R1_R) & (raw_AP_bits == 0b00)); 
    const bool privileged = globals.is_privileged;


    const id::access_perm AP_id = [=]() -> id::access_perm {
        // fetching the access permission depends entirely on the AP, S, R, and mode.
        // so instead of creating a labyrinth of convoluted if conditions, i'm adding
        // all of those to a concatenated u8 byte. Not only because that's faster
        // and switch-friendly, but also because it's much easier to handle that way.
        // the full table is situated in B3-16 which should make more sense to you.
        const u8 bytecode = static_cast<u8>(
            (!privileged) | // is user
            (privileged << 1) | // is privileged
            (R << 2) |
            (S << 3) |
            (raw_AP_bits << 4)
        );
        
        constexpr u8 AP00_USER = 0b000001; // AP = 00, user
        constexpr u8 AP00_PRIV = 0b000010; // AP = 00, priv
        constexpr u8 AP00_USER_S = 0b001001; // AP = 00, user, S
        constexpr u8 AP00_PRIV_S = 0b001010; // AP = 00, priv, S
        constexpr u8 AP00_USER_R = 0b000101; // AP = 00, user, R
        constexpr u8 AP00_PRIV_R = 0b000110; // AP = 00, priv, R
        constexpr u8 AP00_USER_S_R = 0b001101; // AP = 00, user, S, R
        constexpr u8 AP00_PRIV_S_R = 0b001110; // AP = 00, priv, S, R
        constexpr u8 AP01_USER = 0b0101; // AP = 01, user
        constexpr u8 AP01_PRIV = 0b0110; // AP = 01, priv
        constexpr u8 AP10_USER = 0b1001; // AP = 10, user
        constexpr u8 AP10_PRIV = 0b1010; // AP = 10, priv
        constexpr u8 AP11_USER = 0b1101; // AP = 11, user
        constexpr u8 AP11_PRIV = 0b1110; // AP = 11, priv

        switch (bytecode) {
            case AP00_USER: return id::access_perm::NO_ACCESS; // AP = 00, user
            case AP00_PRIV: return id::access_perm::NO_ACCESS; // AP = 00, priv
            case AP00_USER_S: return id::access_perm::NO_ACCESS; // AP = 00, user, S
            case AP00_PRIV_S: return id::access_perm::READ_ONLY; // AP = 00, priv, S
            case AP00_USER_R: return id::access_perm::READ_ONLY; // AP = 00, user, R
            case AP00_PRIV_R: return id::access_perm::READ_ONLY; // AP = 00, priv, R
            case AP00_USER_S_R: return id::access_perm::UNPREDICTABLE; // AP = 00, user, S, R
            case AP00_PRIV_S_R: return id::access_perm::UNPREDICTABLE; // AP = 00, priv, S, R
            default:
                // this section is the same as above, but without the S and R bits 
                // because they're irrelevant after this point when AP != 0b00
                const u8 access_bytecode = static_cast<u8>(
                    (!privileged) |
                    (privileged << 1) |
                    (raw_AP_bits << 2)
                );

                switch (access_bytecode) {
                    case AP01_USER: return id::access_perm::NO_ACCESS;  // AP = 01, user
                    case AP01_PRIV: return id::access_perm::READ_WRITE; // AP = 01, priv
                    case AP10_USER: return id::access_perm::READ_ONLY;  // AP = 10, user
                    case AP10_PRIV: return id::access_perm::READ_WRITE; // AP = 10, priv
                    case AP11_USER: return id::access_perm::READ_WRITE; // AP = 11, user
                    case AP11_PRIV: return id::access_perm::READ_WRITE; // AP = 11, priv
                    default: llarm::out::error("something went horribly wrong here...");
                }
        }
    }();

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
        case id::access_perm::UNPREDICTABLE: 
            llarm::out::unpredictable("MMU access permission ID is unpredictable");
            return true;
    }
}


id::aborts MMU::check_block_access(
    const u8 AP,
    const id::access_type access_type, 
    const id::access_domain domain,
    const id::memory_type memory_type
) {
    const bool section_access = (memory_type == id::memory_type::SECTION);

    switch (domain) {
        case id::access_domain::MANAGER: return id::aborts::NO_ABORT;
        case id::access_domain::CLIENT: {
            if (is_AP_invalid(AP, access_type)) {
                // section
                if (section_access) {
                    return id::aborts::SECTION_PERMISSION;
                }
                
                // page
                return id::aborts::SUB_PAGE_PERMISSION;
            }

            return id::aborts::NO_ABORT;
        }

        case id::access_domain::RESERVED: 
            llarm::out::unpredictable("Reserved access domain encountered, defaulting to no access");
            [[fallthrough]];
        
        case id::access_domain::NO_ACCESS: {
            // section
            if (section_access) {
                return id::aborts::SECTION_DOMAIN;
            }

            // page
            return id::aborts::PAGE_DOMAIN;
        }
    }
}


translation_struct MMU::second_large(
    const u32 entry, 
    const u32 address, 
    const u8 access_size, 
    const id::access_type access_type, 
    const u8 domain_bits
) {
    const u16 page_index = llarm::util::bit_range<u16>(address, 0, 15);
    
    // the subpages are 1KB each
    const u8 subpage_index = static_cast<u8>(page_index / util::get_kb(16));
    
    const u8 AP = subpage_index;
    const id::access_domain domain = fetch_domain(domain_bits);
    const id::aborts AP_abort = check_block_access(AP, access_type, domain, id::memory_type::PAGE);
    const bool AP_failed = (AP_abort != id::aborts::NO_ABORT);
    
    if (AP_failed) {
        manage_abort(AP_abort, address, domain_bits);
        return translation_struct {
            /* has_failed */ true,
            /* abort_code */ AP_abort,
            /* physical_address */ 0
        };
    }

    if (alignment.is_disabled()) {
        const u32 end_address = (address + access_size); 
        
        const bool subpage_crossed = (subpage_index != (end_address / util::get_kb(16)));

        if (subpage_crossed) {
            // same as above but for the second AP this time, assuming a subpage-crossing occurred
            const u8 second_AP = subpage_index + 1;
            const id::aborts second_AP_abort = check_block_access(second_AP, access_type, domain, id::memory_type::PAGE);
            const bool second_AP_failed = (second_AP_abort != id::aborts::NO_ABORT);
        
            if (second_AP_failed) {
                manage_abort(second_AP_abort, address, domain_bits);
                return translation_struct {
                    /* has_failed */ true,
                    /* abort_code */ second_AP_abort,
                    /* physical_address */ 0
                };
            }
        }
    }

    const u32 large_page_base_address = llarm::util::bit_range(entry, 16, 31);

    const u32 physical_address = ((large_page_base_address << 16) | page_index);

    return translation_struct {
        /* has_failed */ false,
        /* abort_code */ id::aborts::NO_ABORT,
        /* physical_address */ physical_address
    };
}


translation_struct MMU::second_small(
    const u32 entry, 
    const u32 address, 
    const u8 access_size, 
    const id::access_type access_type, 
    const u8 domain_bits
) {
    const u16 page_index = llarm::util::bit_range<u16>(address, 0, 11);
    
    // the subpages are 1KB each
    const u8 subpage_index = static_cast<u8>(page_index / util::get_kb(1));
    
    const u8 AP = subpage_index;
    const id::access_domain domain = fetch_domain(domain_bits);
    const id::aborts AP_abort = check_block_access(AP, access_type, domain, id::memory_type::PAGE);
    const bool AP_failed = (AP_abort != id::aborts::NO_ABORT);
    
    if (AP_failed) {
        manage_abort(AP_abort, address, domain_bits);
        return translation_struct {
            /* has_failed */ true,
            /* abort_code */ AP_abort,
            /* physical_address */ 0
        };
    }

    if (alignment.is_disabled()) {
        const u32 end_address = (address + access_size); 
        const bool subpage_crossed = (subpage_index != (end_address / util::get_kb(1)));

        if (subpage_crossed) {
            // same as above but for the second AP this time, assuming a subpage-crossing occurred
            const u8 second_AP = subpage_index + 1;
            const id::aborts second_AP_abort = check_block_access(second_AP, access_type, domain, id::memory_type::PAGE);
            const bool second_AP_failed = (second_AP_abort != id::aborts::NO_ABORT);
        
            if (second_AP_failed) {
                manage_abort(second_AP_abort, address, domain_bits);
                return translation_struct {
                    /* has_failed */ true,
                    /* abort_code */ second_AP_abort,
                    /* physical_address */ 0
                };
            }
        }
    }

    // const bool C = llarm::util::bit_fetch(entry, 3); // TODO: DO SOMETHING WITH THESE
    // const bool B = llarm::util::bit_fetch(entry, 2); // TODO: DO SOMETHING WITH THESE

    const u32 small_page_base_address = llarm::util::bit_range(entry, 12, 31);

    const u32 physical_address = ((small_page_base_address << 12) | page_index);

    return translation_struct {
        /* has_failed */ false,
        /* abort_code */ id::aborts::NO_ABORT,
        /* physical_address */ physical_address
    };
}


translation_struct MMU::second_tiny(
    const u32 entry, 
    const u32 address, 
    const u8 access_size, 
    const id::access_type access_type, 
    const u8 domain_bits
) {
    const u8 AP = llarm::util::bit_range<u8>(entry, 4, 5);

    const id::access_domain domain = fetch_domain(domain_bits);
    const id::aborts abort_code = check_block_access(AP, access_type, domain, id::memory_type::PAGE);
    
    const bool access_failed = (abort_code != id::aborts::NO_ABORT);

    if (access_failed) {
        manage_abort(abort_code, address, domain_bits);
        return translation_struct {
            /* has_failed */ true,
            /* abort_code */ abort_code,
            /* physical_address */ 0
        };
    }
    
    // const bool C = llarm::util::bit_fetch(entry, 3); // TODO: DO SOMETHING WITH THESE
    // const bool B = llarm::util::bit_fetch(entry, 2); // TODO: DO SOMETHING WITH THESE

    const u32 tiny_page_base_address = llarm::util::bit_range(entry, 10, 31);
    
    const u16 page_index = llarm::util::bit_range<u16>(address, 0, 9);
    const u32 physical_address = ((tiny_page_base_address << 10) | page_index);

    return translation_struct {
        /* has_failed */ false,
        /* abort_code */ id::aborts::NO_ABORT,
        /* physical_address */ physical_address
    };
}


bool MMU::is_mmu_enabled() {
    return (
        (coprocessor.read(id::cp15::R1_M) == true) &&
        (settings.is_mmu_enabled)
    );
}


translation_struct MMU::page_walk(const u32 address, const id::access_type access_type, const u8 access_size) {
    if (
        (alignment.is_enabled()) && 
        (access_type != id::access_type::INSTRUCTION_FETCH)
    ) {
        if (alignment.is_aligned(address, access_size) == false) {
            manage_abort(id::aborts::ALIGNMENT, address);
            return translation_struct {
                /* has_failed */ true,
                /* abort_code */ id::aborts::ALIGNMENT,
                /* physical_address */ 0
            };
        }
    }

    const u32 translation_base = coprocessor.read(id::cp15::R2_MMU_TRANSLATION_BASE); // TODO: optimise this with direct register access
    const u32 table_index = llarm::util::bit_range(address, 20, 31);

    const u32 first_level_descriptor_address = ((translation_base << 14) | (table_index << 2));

    const u32 first_level_descriptor = static_cast<u32>(ram.read(first_level_descriptor_address, 4));

    // TODO EXTERNAL ABORT MANAGEMENT HERE

    u32 second_key = 0;

    const id::first_level first_level_id = get_first_level_id(first_level_descriptor);

    switch (first_level_id) {
        case id::first_level::COARSE: second_key = first_coarse(first_level_descriptor, address); break;
        case id::first_level::FINE: second_key = first_fine(first_level_descriptor, address); break;
        case id::first_level::SECTION: return first_section(first_level_descriptor, address, access_size, access_type);
        case id::first_level::FAULT: 
            manage_abort(id::aborts::SECTION_TRANSLATION, address);
            return translation_struct {
                /* has_failed */ true,
                /* abort_code */ id::aborts::SECTION_TRANSLATION,
                /* physical_address */ 0
            };
    };

    const u32 second_level_descriptor = static_cast<u32>(ram.read(second_key, 4));

    const id::second_level entry_id = get_second_level_id(second_level_descriptor);

    const u8 domain_bits = llarm::util::bit_range<u8>(first_level_descriptor, 5, 8);

    switch (entry_id) {
        case id::second_level::LARGE: return second_large(second_level_descriptor, address, access_size, access_type, domain_bits);
        case id::second_level::SMALL: return second_small(second_level_descriptor, address, access_size, access_type, domain_bits);
        case id::second_level::TINY: return second_tiny(second_level_descriptor, address, access_size, access_type, domain_bits);
        case id::second_level::FAULT:
            manage_abort(id::aborts::PAGE_TRANSLATION, address, domain_bits);
            return translation_struct {
                /* has_failed */ true,
                /* abort_code */ id::aborts::PAGE_TRANSLATION,
                /* physical_address */ 0
            };
    }
}


translation_struct MMU::translate_address(const u32 address, const id::access_type access_type, const u8 access_size) {
    const tlb_fetch_struct tlb_fetch = tlb.is_translation_cached(address);

    if (tlb_fetch.is_found) { // TLB hit
        return translation_struct {
            /* has_failed */ false,
            /* abort_code */ id::aborts::NO_ABORT,
            /* physical_address */ tlb.fetch(address, tlb_fetch)
        };
    } 
    
    // TLB miss
    translation_struct translation = page_walk(address, access_type, access_size);

    const bool tlb_is_absent = (
        settings.has_tlb == false ||
        (
            (settings.is_tlb_unified == false) && 
            (settings.is_tlb_separate == false)
        )
    );

    if (tlb_is_absent || translation.has_failed) {
        return translation;
    }

    // a TLB store can now be made. If it already exists then it'll just replace the old physical address.
    tlb.insert(address, translation.physical_address, settings.tlb_type);

    return translation;
}


mem_write_struct MMU::write(const u32 address, const u64 value, const u8 access_size) {
    const translation_struct translation = translate_address(address, id::access_type::WRITE, access_size);

    if (translation.has_failed) {
        return mem_write_struct {
            /* has_failed */ true,
            /* abort_code */ translation.abort_code
        };
    }

    ram.write(value, translation.physical_address, access_size);

    return mem_write_struct {
        /* has_failed */ false,
        /* abort_code */ id::aborts::NO_ABORT
    };
}


mem_read_struct MMU::read(const u32 address, const u8 access_size) {
    const translation_struct translation = translate_address(address, id::access_type::READ, access_size);
    
    if (translation.has_failed) {
        return mem_read_struct {
            /* has_failed  */ true,
            /* abort_code  */ translation.abort_code,
            /* access_size */ access_size,
            /* value       */ 0
        };
    }

    const u64 value = ram.read(translation.physical_address, access_size);

    return mem_read_struct {
        /* has_failed  */ false,
        /* abort_code  */ id::aborts::NO_ABORT,
        /* access_size */ access_size,
        /* value       */ value
    };
}


void MMU::manage_abort(const id::aborts abort, const u32 virtual_address, const u8 domain_bits) {
    if (abort == id::aborts::NO_ABORT) {
        llarm::out::error("Invalid abort in MMU provided");
        return;
    }

    coprocessor.write(id::cp15::R5_MMU_DOMAIN, domain_bits);

    const u8 status = [=]() -> u8 {
        switch (abort) {
            case id::aborts::ALIGNMENT: return 0b0001;
            case id::aborts::VECTOR: return 0b0000;
            case id::aborts::TERMINAL: return 0b0010;
            case id::aborts::SECTION_TRANSLATION: return 0b0101;
            case id::aborts::PAGE_TRANSLATION: return 0b0111;
            case id::aborts::PAGE_DOMAIN: return 0b1011;
            case id::aborts::SUB_PAGE_PERMISSION: return 0b1111;
            case id::aborts::SECTION_DOMAIN: return 0b1001;
            case id::aborts::SECTION_PERMISSION: return 0b1101;
            default: llarm::out::warning("non-MMU abort provided in MMU"); return 0;
        }
    }();

    coprocessor.write(id::cp15::R5_MMU_STATUS, status);

    coprocessor.write(id::cp15::R6_MMU_FAR, virtual_address);
}


void MMU::reset() {
    tlb.flush();
    coprocessor.write(id::cp15::R2_MMU, 0);
    coprocessor.write(id::cp15::R3_MMU, 0);
    coprocessor.write(id::cp15::R5_MMU, 0);
    coprocessor.write(id::cp15::R6_MMU, 0);
    coprocessor.write(id::cp15::R10_MMU, 0);
}



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
     * - Before the MMU is enabled, suitable translation tables must be set up 
     *   in memory and all relevant CP15 registers must be programmed.
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


    coase = 256 entries
    fine = 1024 entries
     */