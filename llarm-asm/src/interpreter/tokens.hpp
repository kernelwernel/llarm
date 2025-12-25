#pragma once

#include <vector>

#include "shared/string_view.hpp"
#include "shared/types.hpp"
#include "shared/util.hpp"

// rhs = right hand side

// the value 255 is designated as a wildcard during the interpreter's matching phase.
static constexpr u8 WILDCARD = 255; 

enum class token_enum : u8 {
    UNKNOWN,
    REG,
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
    UNKNOWN,
    REGULAR,
    SINGLE,
    DOUBLE,
    COPROC,
    CR,
    FPSID,
    FPSCR,
    FPEXC
};

struct REG {
    reg_type type;
    u8 number; // 0~31, 255 = wildcard
    bool is_thumb_supported;
    bool is_malformed;
    bool is_invalid;

    constexpr bool operator==(const REG& rhs) const { // rhs = left hand side
        if (is_invalid || is_malformed || rhs.is_invalid || rhs.is_malformed) {
            return false;
        }

        u8 tmp_num = 0;

        if (rhs.number == WILDCARD) {
            tmp_num = WILDCARD;
        } else {
            tmp_num = number;
        }

        return (
            type == rhs.type && 
            tmp_num == rhs.number &&
            is_thumb_supported == rhs.is_thumb_supported
        );
    }
};

struct IMM {
    i64 number;
    u8 msb; // most significant bit index, this is useful since there's a limit in some cases
    u8 divisor_constraint; // some immeds can only be a multiple of that number, default is 1
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

        // this will be optimised easily. Cases like 1, 2, and 4 will be provided and are 
        // the only realistic setting for the divisor (https://godbolt.org/z/s7cdqzPa8)
        if ((number % rhs.divisor_constraint) != 0) {
            return false;
        }

        if (rhs.has_msb_comparison) {
            return (msb <= rhs.msb);
        }

        if (is_rotateable != rhs.is_rotateable) {
            return false;
        }

        return (number == rhs.number);
    }
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

    void set_C(const bool value = true) { llarm::util::modify_bit(flags, C, value); }
    void set_X(const bool value = true) { llarm::util::modify_bit(flags, X, value); }
    void set_S(const bool value = true) { llarm::util::modify_bit(flags, S, value); }
    void set_F(const bool value = true) { llarm::util::modify_bit(flags, F, value); }
    void set_cpsr(const bool value = true) { llarm::util::modify_bit(flags, IS_CPSR, value); }
    void set_spsr(const bool value = true) { llarm::util::modify_bit(flags, IS_SPSR, value); }
    void set_malformed(const bool value = true) { llarm::util::modify_bit(flags, MALFORMED, value); }
    void set_invalid(const bool value = true) { llarm::util::modify_bit(flags, INVALID, value); }

    constexpr bool operator==(const PSR& rhs) const {
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
    reg_type type;
    u8 reg_count;
    bool is_r15_excluded;
    bool must_have_r15;
    bool is_thumb_supported;
    bool is_malformed;
    bool is_invalid;
    bool is_empty;
    u32 list;

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
using tokens_t = std::vector<token_enum>;

namespace tokens {
    raw_tokens_t tokenize(const sv code);
}