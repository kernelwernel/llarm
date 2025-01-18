#include "ram.hpp"
#include "coprocessor.hpp"

struct MMU {
private:
    RAM& ram;
    COPROCESSOR& coprocessor;

    // page/block sizes
    constexpr u32 tiny_page = util::get_kb(1); // 1KB
    constexpr u32 small_page = util::get_kb(4); // 4KB
    constexpr u32 large_page = util::get_kb(64); // 64KB

    // section size
    constexpr u32 section = util::get_mb(1); // 1MB

    // protection unit
    struct PU {

    };

    // translation lookaside buffer
    struct TLB {
        std::map<> first_level_table {};
        std::map<> second_level_table {};
    };

    bool is_access_permission_invalid(const u32 address) {
        // is the MMU disabled?
        if (coprocessor.read(id::cp::CP15_R1_M) == false) {
            return false;
        }
    
        // 26-bit architecture cannot have an address above (2^26)-1
        if (coprocessor.is_26_bit_arch_address()) {
            if (address > (std::pow(2, 26) - 1)) {
                // TODO: "ADDRESS EXCEPTION" HERE
                return false;
            }
        }

        // TODO: CONTINUE WITH THE CHECK
        return true;
    }

public:
    // TODO: optimise this whole shit with carb::bitset
    u32 translate_address(const u32 address) {
        const u32 translation_base = coprocessor.read(id::cp::CP15_R2_MMU_TRANSLATION_BASE); // TODO: optimise this with direct register access
        const u32 table_index = (util::trim(address, 0, 20) >> 19);

        const u32 first_level_descriptor_address = ((translation_base << 14) & (table_index << 2));

    
        // first level fetch

        // SECTION
        auto section = [=]() -> u32 {
            u32 first_Level_descriptor = 0;
            first_level_descriptor = (1 << 1);

            // B 


            // C

            const u32 section_base_address = 0;

            const u32 section_index = util::trim(address, 12, 0); 

            const u32 physical_address = (section_base_address << 20) & section_index;

            return physical_address;
        };
    

    /*
    enum class first_level_descriptor : u8 {
        FAULT, 
        COARSE_PAGE_TABLE, 
        SECTION,
        FINE_PAGE_TABLE,
    };

    enum class second_level_descriptor : u8 {
        FAULT, 
        LARGE,
        SMALL,
        TINY
    };
    */


    }

    auto table_walk();


    MMU(RAM& ram, COPROCESSOR& coprocessor) : ram(ram), coprocessor(coprocessor) {
        
    }
};