#include "../instruction_id.hpp"
#include "../shifter_id.hpp"

#include "shared/types.hpp"

using namespace internal;


namespace u32_arm {
    bool check_shifter(const u32 code,const shifter_category category);
    bool check_PLD(const u32 code);
    bool check_vfp_reglist(const u32 code, const id::arm id);
    bool check_move_system_reg(const u32 code);
    bool check_B_BL(const u32 code);
    bool check_BLX1(const u32 code);

    bool is_arm_instruction_valid(const u32 code);
}