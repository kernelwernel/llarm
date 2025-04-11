// TODO
#include "../../../../types_extra.hpp"
#include "../../../../id.hpp"
#include "addressing_modes.hpp"

#include "shared/types.hpp"

u32 ADDRESSING_MODE::load_store(const arm_code_t &code) {
    if ((code.test(27) != false) || (code.test(26) != true)) {
        // TODO: error
    }

    // const bool P = code.test(24);
    const bool U = code.test(23);
    // const bool B = code.test(22);
    // const bool W = code.test(21);
    // const bool L = code.test(20);
    const u32 Rn = reg.read(code, 16, 19);
    const u32 Rm = reg.read(code, 0, 3);
    const id::reg Rn_id = reg.fetch_reg_id(code, 16, 19);


    // immediate offset
    if (code.test(25) == false) {
        const u16 offset_12 = util::bit_fetcher<u16>(code, 0, 11);

        /**
         * ===== immediate offset =====
         * 
         * if U == 1 then
         *   address = Rn + offset_12
         * else // U == 0
         *   address = Rn - offset_12
         */
        if (
            (code.test(24) == true) &&
            (code.test(21) == false)
        ) {
            if (U) {
                return (Rn + offset_12);
            } else {
                return (Rn - offset_12);
            }
        }


        /**
         * ===== immediate pre-indexed =====
         * 
         * if U == 1 then
         *   address = Rn + offset_12
         * else // if U == 0
         *   address = Rn - offset_12
         * if ConditionPassed(cond) then
         *   Rn = address
         */
        if (
            (code.test(24) == true) &&
            (code.test(21) == true)
        ) {
            u32 address = 0;

            if (U) {
                address = (Rn + offset_12);
            } else {
                address = (Rn - offset_12);
            }

            if (reg.check_cond(code)) {
                reg.write(Rn_id, address);
            }

            return address;
        }


        /**
         * ===== immediate post-indexed =====
         * 
         * address = Rn
         * if ConditionPassed(cond) then
         *   if U == 1 then
         *     Rn = Rn + offset_12
         *   else // U == 0
         *     Rn = Rn - offset_12
         */
        if (
            (code.test(24) == false) &&
            (code.test(21) == false)
        ) {
            const u32 address = Rn;

            if (reg.check_cond(code)) {
                if (U) {
                    reg.write(Rn_id, (Rn + offset_12));
                } else {
                    reg.write(Rn_id, (Rn - offset_12));
                }
            }

            return address;
        }


        // TODO: ERROR
    }


    if (code.test(25) == true) {
        // register offset
        if (
            (code.test(11) == false) &&
            (code.test(10) == false) &&
            (code.test(9) == false) &&
            (code.test(8) == false) &&
            (code.test(7) == false) &&
            (code.test(6) == false) &&
            (code.test(5) == false) &&
            (code.test(4) == false)
        ) {
            /**
             * ===== register offset =====
             * 
             * if U == 1 then
             *   address = Rn + Rm
             * else // U == 0
             *   address = Rn - Rm
             */
            if (
                (code.test(24) == true) &&
                (code.test(21) == false)
            ) {
                u32 address = 0;

                if (U) {
                    address = (Rn + Rm);
                } else {
                    address = (Rn - Rm);
                }

                if (reg.check_cond(code)) {
                    reg.write(Rn_id, address);
                }

                return address;
            }

            
            /**
             * ===== register pre-indexed =====
             * 
             * if U == 1 then
             *   address = Rn + Rm
             * else // U == 0
             *   address = Rn - Rm
             * if ConditionPassed(cond) then
             *   Rn = address
             */
            if (
                (code.test(24) == true) &&
                (code.test(21) == true)
            ) {
                u32 address = 0;

                if (U) {
                    address = (Rn + Rm);
                } else {
                    address = (Rn - Rm);
                }

                if (reg.check_cond(code)) {
                    reg.write(Rn_id, address);
                }

                return address;
            }


            /**
             * ===== register post-indexed =====
             *
             * address = Rn
             * if ConditionPassed(cond) then
             *   if U == 1 then
             *     Rn = Rn + Rm
             *   else // U == 0
             *     Rn = Rn - Rm
             */
            if (
                (code.test(24) == false) &&
                (code.test(21) == false)
            ) {
                const u32 address = Rn;

                if (reg.check_cond(code)) {
                    if (U) {
                        reg.write(Rn_id, (Rn + Rm));
                    } else {
                        reg.write(Rn_id, (Rn - Rm));
                    }
                }

                return address;
            }
        }



        // scaled register offset
        if (code.test(4) == false) {
            const u8 shift_imm = util::bit_fetcher<u8>(code, 7, 11);
            const u8 shift = util::bit_fetcher<u8>(code, 5, 6);

            /**
             * ===== scaled register offset =====
             * 
             * case shift of
             *   0b00 // LSL
             *     index = Rm Logical_Shift_Left shift_imm
             *   0b01 // LSR
             *     if shift_imm == 0 then // LSR #32
             *       index = 0
             *     else
             *       index = Rm Logical_Shift_Right shift_imm
             *   0b10 // ASR
             *     if shift_imm == 0 then // ASR #32
             *       if Rm[31] == 1 then
             *         index = 0xFFFFFFFF
             *       else
             *         index = 0
             *     else
             *       index = Rm Arithmetic_Shift_Right shift_imm
             *   0b11 // ROR or RRX
             *     if shift_imm == 0 then // RRX
             *       index = (C Flag Logical_Shift_Left 31) OR 
             *               (Rm Logical_Shift_Right 1)
             *     else // ROR
             *       index = Rm Rotate_Right shift_imm
             * endcase
             * 
             * if U == 1 then
             *   address = Rn + index
             * else // U == 0
             *   address = Rn - index
             */
            if (
                (code.test(24) == true) &&
                (code.test(21) == false)
            ) {
                u32 index = 0;
                u32 address = 0;

                switch (shift) {
                    case 0b00: // LSL
                        index = (Rm << shift_imm);
                        break;

                    case 0b01: // LSR
                        if (shift_imm == 0) {
                            index = 0;
                        } else {
                            index = (Rm >> shift_imm);
                        }
                        break;

                    case 0b10: // ASR
                        if (shift_imm == 0) {
                            if ((Rm & (1 << 31)) == 1) {
                                index = 0xFFFFFFFF;
                            } else {
                                index = 0;
                            }
                        } else {
                            index = operation.arithmetic_shift_right(Rm, shift_imm);
                        }
                        break;

                    case 0b11: // ROR or RRX
                        if (shift_imm == 0) { // RRX
                            index = ((reg.read(id::cpsr::C) << 31) | (Rm >> 1));
                        } else { // ROR
                            index = std::rotr(Rm, shift_imm);
                        }
                        break;
                }

                if (U) {
                    address = (Rn + index);
                } else {
                    address = (Rn - index);
                }

                return address;
            }


            /**
             * ===== scaled register pre-indexed =====
             * 
             * case shift of
             *   0b00 // LSL
             *     index = Rm Logical_Shift_Left shift_imm
             *   0b01 // LSR
             *     if shift_imm == 0 then // LSR #32
             *       index = 0
             *     else
             *       index = Rm Logical_Shift_Right shift_imm
             *   0b10 // ASR
             *     if shift_imm == 0 then // ASR #32 
             *       if Rm[31] == 1 then
             *         index = 0xFFFFFFFF
             *       else
             *         index = 0
             *     else
             *       index = Rm Arithmetic_Shift_Right shift_imm
             *   0b11 // ROR or RRX
             *     if shift_imm == 0 then // RRX
             *       index = (C Flag Logical_Shift_Left 31) OR
             *               (Rm Logical_Shift_Right 1)
             *     else // ROR
             *       index = Rm Rotate_Right shift_imm
             * endcase
             * 
             * if U == 1 then
             *   address = Rn + index
             * else // U == 0
             *   address = Rn - index
             * if ConditionPassed(cond) then
             *   Rn = address
             */
            if (
                (code.test(24) == true) &&
                (code.test(21) == true)
            ) {
                u32 index = 0;
                u32 address = 0;

                switch (shift) {
                    case 0b00: // LSL
                        index = (Rm << shift_imm);
                        break;

                    case 0b01: // LSR
                        if (shift_imm == 0) {
                            index = 0;
                        } else {
                            index = (Rm >> shift_imm);
                        }
                        break;

                    case 0b10: // ASR
                        if (shift_imm == 0) {
                            if ((Rm & (1 << 31)) == 1) {
                                index = 0xFFFFFFFF;
                            } else {
                                index = 0;
                            }
                        } else {
                            index = operation.arithmetic_shift_right(Rm, shift_imm);
                        }
                        break;

                    case 0b11: // ROR or RRX
                        if (shift_imm == 0) { // RRX
                            index = ((reg.read(id::cpsr::C) << 31) | (Rm >> 1));
                        } else { // ROR
                            index = std::rotr(Rm, shift_imm);
                        }
                        break;
                }

                if (U) {
                    address = (Rn + index);
                } else {
                    address = (Rn - index);
                }

                if (reg.check_cond(code)) {
                    reg.write(Rn_id, address);
                }

                return address;
            }


            /**
             * ===== scaled register post-indexed =====
             * 
             * address = Rn
             * case shift of
             *   0b00 // LSL
             *     index = Rm Logical_Shift_Left shift_imm
             *   0b01 // LSR
             *     if shift_imm == 0 then // LSR #32
             *       index = 0
             *     else
             *       index = Rm Logical_Shift_Right shift_imm
             *   0b10 // ASR
             *     if shift_imm == 0 then // ASR #32 
             *       if Rm[31] == 1 then
             *         index = 0xFFFFFFFF
             *       else
             *         index = 0
             *     else
             *       index = Rm Arithmetic_Shift_Right shift_imm
             *   0b11 // ROR or RRX
             *     if shift_imm == 0 then // RRX
             *       index = (C Flag Logical_Shift_Left 31) OR
             *               (Rm Logical_Shift_Right 1)
             *     else // ROR
             *       index = Rm Rotate_Right shift_imm
             * endcase
             * 
             * if ConditionPassed(cond) then
             *   if U == 1 then
             *     Rn = Rn + index
             *   else // U == 0
             *     Rn = Rn - index
             */
            if (
                (code.test(24) == false) &&
                (code.test(21) == false)
            ) {
                u32 index = 0;
                u32 address = Rn;

                switch (shift) {
                    case 0b00: // LSL
                        index = (Rm << shift_imm);
                        break;

                    case 0b01: // LSR
                        if (shift_imm == 0) {
                            index = 0;
                        } else {
                            index = (Rm >> shift_imm);
                        }
                        break;

                    case 0b10: // ASR
                        if (shift_imm == 0) {
                            if ((Rm & (1 << 31)) == 1) {
                                index = 0xFFFFFFFF;
                            } else {
                                index = 0;
                            }
                        } else {
                            index = operation.arithmetic_shift_right(Rm, shift_imm);
                        }
                        break;

                    case 0b11: // ROR or RRX
                        if (shift_imm == 0) { // RRX
                            index = ((reg.read(id::cpsr::C) << 31) | (Rm >> 1));
                        } else { // ROR
                            index = std::rotr(Rm, shift_imm);
                        }
                        break;
                }

                if (reg.check_cond(code)) {
                    if (U) {
                        reg.write(Rn_id, Rn + index);
                    } else {
                        reg.write(Rn_id, Rn - index);
                    }
                }

                return address;
            }

            out::error("TODO");
        }

    }

    // TODO: ERROR
    out::error("TODO");
}
