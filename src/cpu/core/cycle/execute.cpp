#include "types.hpp"
#include "cpu/instruction_set.hpp"
#include "cpu/core/cycle/execute.hpp"
#include "cpu/core/cycle/decode.hpp"

void EXECUTE::loader() {
    for (const auto &inst : inst_set.arm_table) {
        INSTRUCTION_SET::arm_struct data = inst.second;
        arm_map[inst.first] = data.function;
    }

    for (const auto &inst : inst_set.thumb_table) {
        INSTRUCTION_SET::thumb_struct data = inst.second;
        thumb_map[inst.first] = data.function;
    }
}

void EXECUTE::execute(const decoded_t &code) const {
    arm_map.at(code.first)(code.second, reg);
}

void EXECUTE::thumb_execute(const thumb_decoded_t &code) const {
    thumb_map.at(code.first)(code.second, reg);
}

EXECUTE::EXECUTE(
    INSTRUCTION_SET& inst_set,
    REGISTERS& reg
) : inst_set(inst_set), reg(reg) {
    loader();
}