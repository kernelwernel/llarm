#include "types.hpp"
#include "cpu/core/cycle/fetch.hpp"

[[nodiscard]] code_t FETCH::converter(const std::vector<u8> &raw_code) const {
    u32 result = 0;
    result |= raw_code[0];
    result |= raw_code[1] << 8;
    result |= raw_code[2] << 16;
    result |= raw_code[3] << 24;
    return code_t(result);
}

[[nodiscard]] thumbcode_t FETCH::thumb_converter(const std::vector<u8> &raw_code) const {
    u32 result = 0;
    result |= raw_code[0];
    result |= raw_code[1] << 8;
    return thumbcode_t(result);
}

FETCH::FETCH(
    INSTRUCTION_SET& inst_set,
    REGISTERS& reg,
    MEMORY& memory
) : inst_set(inst_set), reg(reg), memory(memory) {

}

[[nodiscard]] code_t FETCH::fetch() const {
    std::vector<u8> raw_code = ram.read(reg.PC, reg.PC + 4);
    return converter(raw_code);
}

[[nodiscard]] thumbcode_t FETCH::thumb_fetch() const {
    std::vector<u8> raw_code = ram.read(reg.PC, reg.PC + 2);
    return thumb_converter(raw_code);
}