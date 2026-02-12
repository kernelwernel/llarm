#include "../id/instruction_id.hpp"
#include "../id/shifter_id.hpp"

#include <llarm/shared/types.hpp>

namespace internal::validation::u32_arm {
    bool check_shifter(const u32 code,const shifter_category category);
    bool check_PLD(const u32 code);
    bool check_vfp_reglist(const u32 code, const arm_id id);
    bool check_move_system_reg(const u32 code);
    bool check_B_BL(const u32 code);
    bool check_BLX1(const u32 code);

    bool is_arm_instruction_valid(const u32 code);
}