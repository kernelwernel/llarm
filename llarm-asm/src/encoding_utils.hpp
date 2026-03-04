#include <llarm/shared/types.hpp>

namespace encoders {
    bool is_imm_encodable(const u32 imm);
    void encode_imm(u32 &binary, const u32 immed);
}