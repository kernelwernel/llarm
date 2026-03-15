#include "../interpreter/IR_struct.hpp"
#include "../interpreter/lexer.hpp"

#include <string>

namespace internal::validation::string_arm {
    bool is_arm_instruction_valid(const std::string &code, const u32 PC = 0);
    bool is_arm_instruction_valid(const IR_arm_struct &IR);

    bool is_data_processing_valid(lexemes_t lexemes, const shifter_id shifter_id, const arm_id id);
    bool is_ls_valid(const lexemes_t &lexemes, const shifter_id shifter_id, const arm_id id);
    bool is_ls_misc_valid(lexemes_t lexemes, const shifter_id shifter_id, const arm_id id);
    bool is_ls_coproc_valid(const lexemes_t &lexemes, const shifter_id shifter_id, const arm_id id);

    bool is_B_BL_valid(const lexemes_t& lexemes, const u32 PC);
}