#include "types.hpp"
#include "cpu/core/cycle/fetch.hpp"

FETCH::FETCH(
    INSTRUCTION_SET& inst_set,
    REGISTERS& reg,
    MEMORY& memory
) : inst_set(inst_set), reg(reg), memory(memory) {

}

[[nodiscard]] arm_code_t FETCH::arm_fetch() const {
    const arm_code_t tmp(memory.read<u32>(reg.PC, id::access_type::INSTRUCTION_FETCH));
    return tmp;
}

[[nodiscard]] thumb_code_t FETCH::thumb_fetch() const {
    const thumb_code_t tmp(memory.read<u16>(reg.PC, id::access_type::INSTRUCTION_FETCH));
    return tmp;
}

[[nodiscard]] jazelle_code_t FETCH::jazelle_fetch() const {
    return memory.read(reg.PC);
}