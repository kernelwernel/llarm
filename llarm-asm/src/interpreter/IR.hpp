#include "shared/types.hpp"

enum class reg_type : u8 {
    REGULAR,
    SINGLE,
    DOUBLE,
    COPROC,
    CR
};

struct REG {
    reg_type type;
    u8 number; // 0~31
};

struct IMM {
    u32 number;
    u8 msb;
    bool is_constant;
    bool is_multiple_of_4;
};