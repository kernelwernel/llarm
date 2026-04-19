#pragma once

#include <vector>

#include <llarm/shared/string_view.hpp>
#include <llarm/shared/types.hpp>
#include <llarm/shared/util.hpp>

// rhs = right hand side

// the value 255 is designated as a wildcard during the interpreter's matching phase.
static constexpr u8 WILDCARD = 255; 

enum class token_enum : u8 {
    UNKNOWN,
    REG,
    REG_THUMB,
    REG_LIST,
    REG_LIST_START, // "{"
    REG_LIST_END, // "}"
    HASHTAG,
    IMMED,
    MUL_OP, // "*"
    MIN_OP, // "-"
    PSR,
    MEM_START, // "["
    MEM_END, // "]"
    LSL,
    LSR,
    ASR,
    ROR,
    RRX,
    SHIFT,
    PRE_INDEX, // '!'
    CARET, // '^'
    COMMENT, // '@' and '<'
    OPTION // specific to address mode 5
};

enum class reg_type : u8 {
    UNKNOWN_REG, // there is a conflict with token_enum::UNKNOWN when doing "using enum reg_type", so this is a fix
    REGULAR,
    SINGLE,
    DOUBLE,
    COPROC,
    CR,
    FPSID,
    FPSCR,
    FPEXC,
    FP_WILDCARD
};

struct REG {
    reg_type type;
    u8 number; // 0~31, 255 = wildcard
    bool is_thumb_supported;
    bool is_malformed;
    bool is_invalid;

    constexpr bool operator==(const REG& rhs) const {
        if (is_invalid || is_malformed || rhs.is_invalid || rhs.is_malformed) {
            return false;
        }

        u8 tmp_num = 0;

        if (rhs.number == WILDCARD) {
            tmp_num = WILDCARD;
        } else {
            tmp_num = number;
        }

        if (type == reg_type::FP_WILDCARD) {
            return (
                (rhs.type == reg_type::FPSID) ||
                (rhs.type == reg_type::FPSCR) ||
                (rhs.type == reg_type::FPEXC)
            );
        }

        return (
            type == rhs.type && 
            tmp_num == rhs.number &&
            is_thumb_supported == rhs.is_thumb_supported
        );
    }
};

struct IMM {
    u64 number;
    u8 msb; // most significant bit index, this is useful since there's a limit in some cases
    u8 divisor_constraint; // some immeds can only be a multiple of that number, default is 1
    u8 start_value;
    u8 end_value;
    bool has_msb_comparison; // means that the msb will be analysed instead of the number during comparison
    bool is_rotateable; // important distinction for instructions with data processing address modes
    bool is_negative;
    bool is_malformed;
    bool is_invalid;

    constexpr bool operator==(const IMM& rhs) const {
        // the rhs is considered as the immed "matcher" that was
        // pre-set for comparison, it's not the raw immed itself

        if (is_invalid || is_malformed || rhs.is_invalid || rhs.is_malformed) {
            return false;
        }

        if (start_value != 0 || end_value != 0) {
            return (rhs.number >= start_value && rhs.number <= end_value);
        }

        // this will be optimised easily. Cases like 1, 2, and 4 will be provided and are 
        // the only realistic setting for the divisor (https://godbolt.org/z/s7cdqzPa8)
        if (divisor_constraint != 1 && divisor_constraint != 0) {
            if ((number % rhs.divisor_constraint) != 0) {
                return false;
            }
        }

        if (rhs.has_msb_comparison) {
            return (msb <= rhs.msb);
        }

        if (is_rotateable != rhs.is_rotateable) {
            return false;
        }

        if (is_negative != rhs.is_negative) {
            return false;
        }

        return (number == rhs.number);
    }

//    constexpr IMM() : 
//        number(0), 
//        msb(0), 
//        divisor_constraint(1), 
//        start_value(0),
//        end_value(0),
//        has_msb_comparison(false),
//        is_rotateable(false),
//        is_negative(false),
//        is_malformed(false),
//        is_invalid(false)
//    {
//
//    }

//    constexpr IMM(    
//        const u64 number,
//        const u8 msb,
//        const u8 divisor_constraint,
//        const u8 start_value,
//        const u8 end_value,
//        const bool has_msb_comparison,
//        const bool is_rotateable,
//        const bool is_negative,
//        const bool is_malformed,
//        const bool is_invalid
//    ) : 
//        number(number), 
//        msb(msb), 
//        divisor_constraint(divisor_constraint), 
//        start_value(start_value),
//        end_value(end_value),
//        has_msb_comparison(has_msb_comparison),
//        is_rotateable(is_rotateable),
//        is_negative(is_negative),
//        is_malformed(is_malformed),
//        is_invalid(is_invalid)
//    {
//
//    }
};

struct PSR {
    enum psr_bitset : u8 {
        IS_CPSR,
        IS_SPSR,
        C,
        X,
        S,
        F,
        MALFORMED,
        INVALID
    };

    u8 flags; // this will save memory space instead of having bool variables for each element, 
              // the whole struct is now 1 byte instead of 8

    bool has_C() const { return llarm::util::bit_fetch(flags, C); }
    bool has_X() const { return llarm::util::bit_fetch(flags, X); }
    bool has_S() const { return llarm::util::bit_fetch(flags, S); }
    bool has_F() const { return llarm::util::bit_fetch(flags, F); }
    bool is_cpsr() const { return llarm::util::bit_fetch(flags, IS_CPSR); }
    bool is_spsr() const { return llarm::util::bit_fetch(flags, IS_SPSR); }
    bool is_malformed() const { return llarm::util::bit_fetch(flags, MALFORMED); }
    bool is_invalid() const { return llarm::util::bit_fetch(flags, INVALID); }

    constexpr void set_C(const bool value = true) { llarm::util::modify_bit(flags, C, value); }
    constexpr void set_X(const bool value = true) { llarm::util::modify_bit(flags, X, value); }
    constexpr void set_S(const bool value = true) { llarm::util::modify_bit(flags, S, value); }
    constexpr void set_F(const bool value = true) { llarm::util::modify_bit(flags, F, value); }
    constexpr void set_cpsr(const bool value = true) { llarm::util::modify_bit(flags, IS_CPSR, value); }
    constexpr void set_spsr(const bool value = true) { llarm::util::modify_bit(flags, IS_SPSR, value); }
    constexpr void set_malformed(const bool value = true) { llarm::util::modify_bit(flags, MALFORMED, value); }
    constexpr void set_invalid(const bool value = true) { llarm::util::modify_bit(flags, INVALID, value); }

    bool operator==(const PSR& rhs) const {
        if (is_invalid() || is_malformed() || rhs.is_invalid() || rhs.is_malformed()) {
            return false;
        }

        const bool rhs_has_fields = ((rhs.has_C() + rhs.has_X() + rhs.has_S() + rhs.has_F()) != 0);
        const bool lhs_has_fields = ((has_C() + has_X() + has_S() + has_F()) != 0);

        if (rhs_has_fields != lhs_has_fields) {
            return false;
        }

        return (
            is_cpsr() == rhs.is_cpsr() &&
            is_spsr() == rhs.is_spsr()
        );
    }
};

struct REG_LIST {
    reg_type type = reg_type::UNKNOWN_REG;
    u8 reg_count = 0;
    bool is_r15_excluded = false;
    bool must_have_r15 = false;
    bool is_thumb_supported = false;
    bool is_thumb_optional_pc = false;
    bool is_thumb_optional_lr = false;
    bool is_malformed = false;
    bool is_invalid = false;
    bool is_empty = false;
    u32 list = 0;

    constexpr bool operator==(const REG_LIST& rhs) const {
        if (is_invalid || is_malformed || rhs.is_invalid || rhs.is_malformed) {
            return false;
        }

        if (type != rhs.type) {
            return false;
        }

        const bool is_r15_set = llarm::util::bit_fetch(list, 15);

        if ((must_have_r15 || rhs.must_have_r15) && (is_r15_set == false)) {
            return false;
        }

        if ((is_r15_excluded || rhs.is_r15_excluded) && is_r15_set) {
            return false;
        }

        if (is_empty != rhs.is_empty) {
            return false;
        }

        if (is_thumb_supported != rhs.is_thumb_supported) {
            return false;
        }

        return true;
    }
};

struct OPTION {
    u8 number;
    bool is_malformed;
    bool is_invalid;

    constexpr bool operator==(const OPTION& rhs) const {
        return ((is_invalid || is_malformed || rhs.is_invalid || rhs.is_malformed) == false);
    }
};


using raw_tokens_t = std::vector<sv>;

namespace tokens {
    raw_tokens_t tokenize(const sv instruction);
}