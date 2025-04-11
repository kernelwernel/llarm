#include "shared/types.hpp"
#include "../../instruction_set.hpp"
#include "execute.hpp"
#include "decode.hpp"

void EXECUTE::loader() {
    for (const auto &inst : inst_set.arm_table) {
        arm_map[inst.first] = inst.second;
    }

    for (const auto &inst : inst_set.thumb_table) {
        thumb_map[inst.first] = inst.second;
    }

    //for (const auto &inst : inst_set.jazelle_table) {
    //    INSTRUCTION_SET::jazelle_struct data = inst.second;
    //    jazelle_map[inst.first] = data.function;
    //}
}

void EXECUTE::arm_execute(const arm_decode_struct &instruction) const {
    arm_map.at(instruction.id)(instruction.code);
    //.function(code.second, reg);
}

void EXECUTE::thumb_execute(const thumb_decode_struct &instruction) const {
    thumb_map.at(instruction.id)(instruction.code);
}

//void EXECUTE::jazelle_execute(const jazelle_decoded_t &code) const {
//    jazelle_map.at(code.first)(code.second, reg);
//}

EXECUTE::EXECUTE(INSTRUCTION_SET& inst_set) : inst_set(inst_set) {
    loader();
}