#include "types.hpp"
#include "utility.hpp"
#include "globals.hpp"
#include "logs.hpp"

// memory protection unit
struct MPU {
private:
    GLOBALS& globals;
    COPROCESSOR& coprocessor;

public:
    u64 get_size(const u8 raw_size_bits) {
        case 0b01011: return util::get_kb(4); // 4KB
        case 0b01100: return util::get_kb(8); // 8KB
        case 0b01101: return util::get_kb(16); // 16KB
        case 0b01110: return util::get_kb(32); // 32KB
        case 0b01111: return util::get_kb(64); // 64KB
        case 0b10000: return util::get_kb(128); // 128KB
        case 0b10001: return util::get_kb(256); // 256KB
        case 0b10010: return util::get_kb(512); // 512KB
        case 0b10011: return util::get_mb(1); // 1MB
        case 0b10100: return util::get_mb(2); // 2MB
        case 0b10101: return util::get_mb(4); // 4MB
        case 0b10110: return util::get_mb(8); // 8MB
        case 0b10111: return util::get_mb(16); // 16MB
        case 0b11000: return util::get_mb(32); // 32MB
        case 0b11001: return util::get_mb(64); // 64MB
        case 0b11010: return util::get_mb(128); // 128MB
        case 0b11011: return util::get_mb(256); // 256MB
        case 0b11100: return util::get_mb(512); // 512MB
        case 0b11101: return util::get_gb(1); // 1GB
        case 0b11110: return util::get_gb(2); // 2GB
        case 0b11111: return util::get_gb(4); // 4GB
    };

    id::access_perm get_access_perm(const u8 AP) {
        if (globals.is_privileged) {
            if (AP == 0b00) {
                return id::access_perm::NO_ACCESS
            }

            return id::access_perm::READ_WRITE;
        } else {
            switch (AP) {
                case 0b00: return id::access_perm::NO_ACCESS;
                case 0b01: return id::access_perm::NO_ACCESS;
                case 0b10: return id::access_perm::READ_ONLY;
                case 0b11: return id::access_perm::READ_WRITE;
            }
        }

        out::error("something went horribly wrong here...") // TODO
    }


    u32 region_0_start = 0;
    u32 region_1_start = 0;
    u32 region_2_start = 0;
    u32 region_3_start = 0;
    u32 region_4_start = 0;
    u32 region_5_start = 0;
    u32 region_6_start = 0;
    u32 region_7_start = 0;
    u32 region_0_end = 0;
    u32 region_1_end = 0;
    u32 region_2_end = 0;
    u32 region_3_end = 0;
    u32 region_4_end = 0;
    u32 region_5_end = 0;
    u32 region_6_end = 0;
    u32 region_7_end = 0;
    bool region_0_enabled = false;
    bool region_1_enabled = false;
    bool region_2_enabled = false;
    bool region_3_enabled = false;
    bool region_4_enabled = false;
    bool region_5_enabled = false;
    bool region_6_enabled = false;
    bool region_7_enabled = false;


    /*
    enum : u8 {
        REGION_0_PRIORITY = 0,
        REGION_1_PRIORITY,
        REGION_2_PRIORITY,
        REGION_3_PRIORITY,
        REGION_4_PRIORITY,
        REGION_5_PRIORITY,
        REGION_6_PRIORITY,
        REGION_7_PRIORITY
    };
    */

    bool is_mpu_access_valid(const u32 address, const id::access_type access_type) {
        if (globals.mpu_address_changes) {
            region_0_start = coprocessor.read(id::cp::CP15_R6_PU_0_BASE_ADDRESS);
            region_1_start = coprocessor.read(id::cp::CP15_R6_PU_1_BASE_ADDRESS);
            region_2_start = coprocessor.read(id::cp::CP15_R6_PU_2_BASE_ADDRESS);
            region_3_start = coprocessor.read(id::cp::CP15_R6_PU_3_BASE_ADDRESS);
            region_4_start = coprocessor.read(id::cp::CP15_R6_PU_4_BASE_ADDRESS);
            region_5_start = coprocessor.read(id::cp::CP15_R6_PU_5_BASE_ADDRESS);
            region_6_start = coprocessor.read(id::cp::CP15_R6_PU_6_BASE_ADDRESS);
            region_7_start = coprocessor.read(id::cp::CP15_R6_PU_7_BASE_ADDRESS);
            region_0_end = region_0_start + get_size(coprocessor.read(id::cp::CP15_R6_PU_0_SIZE));
            region_1_end = region_1_start + get_size(coprocessor.read(id::cp::CP15_R6_PU_1_SIZE));
            region_2_end = region_2_start + get_size(coprocessor.read(id::cp::CP15_R6_PU_2_SIZE));
            region_3_end = region_3_start + get_size(coprocessor.read(id::cp::CP15_R6_PU_3_SIZE));
            region_4_end = region_4_start + get_size(coprocessor.read(id::cp::CP15_R6_PU_4_SIZE));
            region_5_end = region_5_start + get_size(coprocessor.read(id::cp::CP15_R6_PU_5_SIZE));
            region_6_end = region_6_start + get_size(coprocessor.read(id::cp::CP15_R6_PU_6_SIZE));
            region_7_end = region_7_start + get_size(coprocessor.read(id::cp::CP15_R6_PU_7_SIZE));
            region_0_enabled = coprocessor.read(id::cp::CP15_R6_PU_0_E);
            region_1_enabled = coprocessor.read(id::cp::CP15_R6_PU_1_E);
            region_2_enabled = coprocessor.read(id::cp::CP15_R6_PU_2_E);
            region_3_enabled = coprocessor.read(id::cp::CP15_R6_PU_3_E);
            region_4_enabled = coprocessor.read(id::cp::CP15_R6_PU_4_E);
            region_5_enabled = coprocessor.read(id::cp::CP15_R6_PU_5_E);
            region_6_enabled = coprocessor.read(id::cp::CP15_R6_PU_6_E);
            region_7_enabled = coprocessor.read(id::cp::CP15_R6_PU_7_E);

            globals.mpu_address_change = false;
        }

        id::cp AP_region_id;

        if      (address >= region_7_start && address <= region_7_end && region_7_enabled) { AP_region_id = id::cp::CP15_R5_PU_AP7; } 
        else if (address >= region_6_start && address <= region_6_end && region_6_enabled) { AP_region_id = id::cp::CP15_R5_PU_AP6; }
        else if (address >= region_5_start && address <= region_5_end && region_5_enabled) { AP_region_id = id::cp::CP15_R5_PU_AP5; }
        else if (address >= region_4_start && address <= region_4_end && region_4_enabled) { AP_region_id = id::cp::CP15_R5_PU_AP4; }
        else if (address >= region_3_start && address <= region_3_end && region_3_enabled) { AP_region_id = id::cp::CP15_R5_PU_AP3; }
        else if (address >= region_2_start && address <= region_2_end && region_2_enabled) { AP_region_id = id::cp::CP15_R5_PU_AP2; }
        else if (address >= region_1_start && address <= region_1_end && region_1_enabled) { AP_region_id = id::cp::CP15_R5_PU_AP1; }
        else if (address >= region_0_start && address <= region_0_end && region_0_enabled) { AP_region_id = id::cp::CP15_R5_PU_AP0; }
        else {
            // abort
            return false;
        }

        const u8 AP_bits = coprocessor.read(AP_region_id);
        const id::access_perm AP_perm = get_access_perm(AP_bits);

        switch (AP_perm) {
            case id::access_perm::READ_WRITE: 
                return (
                    (access_type == id::access_type::READ_WRITE) ||
                    (access_type == id::access_type::READ) ||
                    (access_type == id::access_type::WRITE)
                );
                break;
            case id::access_perm::READ_ONLY:
                return (
                    (access_type == id::access_type::READ_WRITE) ||
                    (access_type == id::access_type::READ)
                );
                break;
            case id::access_perm::NO_ACCESS: return false;
        }

        return false;
    }


    // try to scan from most priority to least, rather than upwards
    
    // if the access is outside of any region, do an abort (doesn't say which tho) 

    // alignment checking is also allowed, implement this TODO

    // extra thing: region 0 could be set to 4GB, as a backup if all other regions fail

    void setup_R6_PU() {
        // The starting address of a region must be a multiple 
        // of its size. For example, a 4KB region (size 0x1000)
        // can start at address 0x12345000, but an 8KB region 
        // (size 0x2000) or larger can not.

        // 

        if ((address % size) != 0) {
            // error

        }

        // Some implementations (typically those with separate 
        // instruction and data caches) provide two separate sets
        // of eight protection regions, with one set being used 
        // for instruction fetches and the other set for data accesses.

        // if the address doesn't lie in any protection region, a memory access abort is made 
    }


    MPU(GLOBALS& globals, COPROCESSOR& coprocessor) : globals(globals), coprocessor(coprocessor) {
        
    }
};