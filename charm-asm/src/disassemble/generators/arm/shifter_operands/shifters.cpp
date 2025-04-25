#include "shifters.hpp"

#include "../../util.hpp"

#include "shared/types.hpp"
#include "shared/util.hpp"
#include "shared/out.hpp"

using namespace internal;

shifters::mode shifters::identify_data_shifter(const u32 code) {
    if (
        ((code & (1 << 27)) != 0) ||
        ((code & (1 << 26)) != 0) 
    ) {
        shared::out::error("No known data addressing shifter has been found");
    }


    // 32-bit immediate
    if ((code & (1 << 25)) == 1) {
        return shifters::mode::DATA_IMM;
    }

    // code[25] is known to be 0 after this point, so no check for that bit is required

    // rotate right with extend
    if (shared::util::bit_fetcher(code, 4, 11) == 0b110) {
        return shifters::mode::DATA_RRX;
    }


    // register
    if (shared::util::bit_fetcher(code, 4, 11) == 0) {
        return shifters::mode::DATA_REG;
    }


    // immediate shifts
    if ((code & (1 << 4)) == 0) {
        const u8 mode_bits = shared::util::bit_fetcher<u8>(code, 4, 6);

        switch (mode_bits) {
            case 0b000: return shifters::mode::DATA_IMM_LSL;
            case 0b010: return shifters::mode::DATA_IMM_LSR;
            case 0b100: return shifters::mode::DATA_IMM_ASR;
            case 0b110: return shifters::mode::DATA_IMM_ROR;
            default: shared::out::error("No known data immediate addressing shifter has been found");
        }
    }


    // register shifts
    if (
        ((code & (1 << 7)) == 0) &&
        ((code & (1 << 4)) == 1)
    ) {
        const u8 mode_bits = shared::util::bit_fetcher<u8>(code, 4, 7);

        switch (mode_bits) {
            case 0b0001: return shifters::mode::DATA_REG_LSL;
            case 0b0011: return shifters::mode::DATA_REG_LSR;
            case 0b0101: return shifters::mode::DATA_REG_ASR;
            case 0b0111: return shifters::mode::DATA_REG_ROR;
            default: shared::out::error("No known data register addressing shifter has been found");
        }
    }

    shared::out::error("No known data addressing shifter has been found");
}


shifters::mode shifters::identify_ls_shifter(const u32 code) {
    if (
        ((code & (1 << 27)) != 0) ||
        ((code & (1 << 26)) != 1)
    ) {
        shared::out::error("No known load store addressing shifter has been found");
    }

    const bool bit_24 = (code & (1 << 24));
    const bool bit_21 = (code & (1 << 21));

    // immediate offset/index
    if ((code & (1 << 25)) == 0) {
        if (bit_24 && !bit_21) {
            return shifters::mode::LS_IMM;
        }

        if (bit_24 && bit_21) {
            return shifters::mode::LS_IMM_PRE;
        }

        if (!bit_24 && !bit_21) {
            return shifters::mode::LS_IMM_POST;
        }

        shared::out::error("No known load store immediate addressing shifter has been found");
    }


    // register offset/index
    if (shared::util::bit_fetcher(code, 4, 11) == 0) {
        if (bit_24 && !bit_21) {
            return shifters::mode::LS_REG;
        }

        if (bit_24 && bit_21) {
            return shifters::mode::LS_REG_PRE;
        }

        if (!bit_24 && !bit_21) {
            return shifters::mode::LS_REG_POST;
        }

        shared::out::error("No known load store immediate addressing shifter has been found");
    }


    u8 mode_bits = shared::util::bit_fetcher<u8>(code, 4, 6);
    mode_bits |= (bit_21 << 3);
    mode_bits |= (bit_24 << 4);

    if (shared::util::bit_fetcher(code, 7, 11) == 0) {
        mode_bits |= (1 << 5);
    }

    // scaled register offset/index
    if ((code & (1 << 4)) == 0) {
        switch (mode_bits) {
            // 5th bit = whether code[11:7] is empty
            // 4th bit = code[24]
            // 3rd bit = code[21]
            // bits 2-0 = shifter id at code[6:4]
            case 0b010000: return shifters::mode::LS_REG_SCALED_LSL;
            case 0b010010: return shifters::mode::LS_REG_SCALED_LSR;
            case 0b010100: return shifters::mode::LS_REG_SCALED_ASR;
            case 0b010110: return shifters::mode::LS_REG_SCALED_ROR;
            case 0b110110: return shifters::mode::LS_REG_SCALED_RRX;
            case 0b011000: return shifters::mode::LS_REG_SCALED_PRE_LSL;
            case 0b011010: return shifters::mode::LS_REG_SCALED_PRE_LSR;
            case 0b011100: return shifters::mode::LS_REG_SCALED_PRE_ASR;
            case 0b011110: return shifters::mode::LS_REG_SCALED_PRE_ROR;
            case 0b111110: return shifters::mode::LS_REG_SCALED_PRE_RRX;
            case 0b000000: return shifters::mode::LS_REG_SCALED_POST_LSL;
            case 0b000010: return shifters::mode::LS_REG_SCALED_POST_LSR;
            case 0b000100: return shifters::mode::LS_REG_SCALED_POST_ASR;
            case 0b000110: return shifters::mode::LS_REG_SCALED_POST_ROR;
            case 0b100110: return shifters::mode::LS_REG_SCALED_POST_RRX;
            default: shared::out::error("No known load store scaled register addressing shifter has been found");
        }
    }

    shared::out::error("No known load store addressing shifter has been found");
}


shifters::mode shifters::identify_ls_misc_shifter(const u32 code) {
    if (
        ((code & (1 << 7)) != 1) ||
        ((code & (1 << 4)) != 1) ||
        ((code & (1 << 27)) != 0) ||
        ((code & (1 << 26)) != 0) ||
        ((code & (1 << 25)) != 0)
    ) {
        shared::out::error("No known load store misc addressing shifter has been found");
    }

    const bool bit_24 = (code & (1 << 24));
    const bool bit_22 = (code & (1 << 22));
    const bool bit_21 = (code & (1 << 21));

    const u8 mode_bits = static_cast<u8>((bit_24 << 2) | (bit_22 << 1) | bit_21); 

    switch (mode_bits) {
        // immediate offset/index
        case 0b110: return shifters::mode::LS_MISC_IMM;
        case 0b111: return shifters::mode::LS_MISC_IMM_PRE;
        case 0b010: return shifters::mode::LS_MISC_IMM_POST;

        // register offset/index
        case 0b100: return shifters::mode::LS_MISC_REG;
        case 0b101: return shifters::mode::LS_MISC_REG_PRE;
        case 0b000: return shifters::mode::LS_MISC_REG_POST;
        default: shared::out::error("No known load store misc addressing shifter has been found");
    }
}


shifters::mode shifters::identify_ls_mul_shifter(const u32 code) {
    if (
        ((code & (1 << 27)) != 1) ||
        ((code & (1 << 26)) != 0) ||
        ((code & (1 << 25)) != 0)
    ) {
        shared::out::error("No known load store multiple addressing shifter has been found");
    }

    const bool bit_24 = (code & (1 << 24));
    const bool bit_23 = (code & (1 << 23));

    const u8 mode_bits = static_cast<u8>((bit_24 << 1) | bit_23);

    switch (mode_bits) {
        case 0b01: return shifters::mode::LS_MUL_INC_AFTER;
        case 0b11: return shifters::mode::LS_MUL_INC_BEFORE;
        case 0b00: return shifters::mode::LS_MUL_DEC_AFTER;
        case 0b10: return shifters::mode::LS_MUL_DEC_BEFORE;
        default: shared::out::error("No known load store multiple addressing shifter has been found");
    }
}


shifters::mode shifters::identify_ls_coproc_shifter(const u32 code) {
    if (
        ((code & (1 << 27)) != 1) ||
        ((code & (1 << 26)) != 1) ||
        ((code & (1 << 25)) != 0)
    ) {
        shared::out::error("No known load store coprocessor addressing shifter has been found");
    }

    const bool bit_24 = (code & (1 << 24));
    const bool bit_21 = (code & (1 << 21));

    const u8 mode_bits = static_cast<u8>((bit_24 << 1) | bit_21);

    switch (mode_bits) {
        case 0b10: return shifters::mode::LS_COPROC_IMM;
        case 0b11: return shifters::mode::LS_COPROC_IMM_PRE;
        case 0b01: return shifters::mode::LS_COPROC_IMM_POST;
        case 0b00: return shifters::mode::LS_COPROC_UNINDEXED;
        default: shared::out::error("No known load store coprocessor addressing shifter has been found");
    }
}



std::string shifters::shifter_to_string(const mode mode, const u32 code) {
    switch (mode) {
        case shifters::mode::DATA_IMM: return data_imm(code);
        case shifters::mode::DATA_IMM_LSL: return data_imm_pattern(code, "LSL");
        case shifters::mode::DATA_IMM_LSR: return data_imm_pattern(code, "LSR");
        case shifters::mode::DATA_IMM_ASR: return data_imm_pattern(code, "ASR");
        case shifters::mode::DATA_IMM_ROR: return data_imm_pattern(code, "ROR");
        case shifters::mode::DATA_REG: return data_reg(code);
        case shifters::mode::DATA_REG_LSL: return data_reg_pattern(code, "LSL");
        case shifters::mode::DATA_REG_LSR: return data_reg_pattern(code, "LSR");
        case shifters::mode::DATA_REG_ASR: return data_reg_pattern(code, "ASR");
        case shifters::mode::DATA_REG_ROR: return data_reg_pattern(code, "ROR");
        case shifters::mode::DATA_RRX: return data_rrx(code);
        case shifters::mode::LS_IMM: return ls_imm(code);
        case shifters::mode::LS_IMM_PRE: return ls_imm_pre(code);
        case shifters::mode::LS_IMM_POST: return ls_imm_post(code);
        case shifters::mode::LS_REG: return ls_reg(code);
        case shifters::mode::LS_REG_PRE: return ls_reg_pre(code);
        case shifters::mode::LS_REG_POST: return ls_reg_post(code);
        case shifters::mode::LS_REG_SCALED_LSL: return ls_reg_scaled(code, "LSL");
        case shifters::mode::LS_REG_SCALED_LSR: return ls_reg_scaled(code, "LSR");
        case shifters::mode::LS_REG_SCALED_ASR: return ls_reg_scaled(code, "ASR");
        case shifters::mode::LS_REG_SCALED_ROR: return ls_reg_scaled(code, "ROR");
        case shifters::mode::LS_REG_SCALED_RRX: return ls_reg_scaled_rrx(code);
        case shifters::mode::LS_REG_SCALED_PRE_LSL: return ls_reg_scaled_pre(code, "LSL");
        case shifters::mode::LS_REG_SCALED_PRE_LSR: return ls_reg_scaled_pre(code, "LSR");
        case shifters::mode::LS_REG_SCALED_PRE_ASR: return ls_reg_scaled_pre(code, "ASR");
        case shifters::mode::LS_REG_SCALED_PRE_ROR: return ls_reg_scaled_pre(code, "ROR");
        case shifters::mode::LS_REG_SCALED_PRE_RRX: return ls_reg_scaled_pre_rrx(code);
        case shifters::mode::LS_REG_SCALED_POST_LSL: return ls_reg_scaled_post(code, "LSL");
        case shifters::mode::LS_REG_SCALED_POST_LSR: return ls_reg_scaled_post(code, "LSR");
        case shifters::mode::LS_REG_SCALED_POST_ASR: return ls_reg_scaled_post(code, "ASR");
        case shifters::mode::LS_REG_SCALED_POST_ROR: return ls_reg_scaled_post(code, "ROR");
        case shifters::mode::LS_REG_SCALED_POST_RRX: return ls_reg_scaled_post_rrx(code);
        case shifters::mode::LS_MISC_IMM: return ls_misc_imm(code);
        case shifters::mode::LS_MISC_IMM_PRE: return ls_misc_imm_pre(code);
        case shifters::mode::LS_MISC_IMM_POST: return ls_misc_imm_post(code);
        case shifters::mode::LS_MISC_REG: return ls_misc_reg(code);
        case shifters::mode::LS_MISC_REG_PRE: return ls_misc_reg_pre(code);
        case shifters::mode::LS_MISC_REG_POST: return ls_misc_reg_post(code);
        case shifters::mode::LS_MUL_INC_AFTER: return "IA";
        case shifters::mode::LS_MUL_INC_BEFORE: return "IB";
        case shifters::mode::LS_MUL_DEC_AFTER: return "DA";
        case shifters::mode::LS_MUL_DEC_BEFORE: return "DB";
        case shifters::mode::LS_COPROC_IMM: return ls_coproc_imm(code);
        case shifters::mode::LS_COPROC_IMM_PRE: return ls_coproc_imm_pre(code);
        case shifters::mode::LS_COPROC_IMM_POST: return ls_coproc_imm_post(code);
        case shifters::mode::LS_COPROC_UNINDEXED: return ls_coproc_unindexed(code);
    }
}