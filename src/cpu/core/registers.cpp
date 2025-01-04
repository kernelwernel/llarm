#include <iostream>

#include "constants.hpp"
#include "id.hpp"
#include "utility.hpp"
#include "out.hpp"
#include "cpu/core/registers.hpp"


[[nodiscard]] id::mode REGISTERS::read_mode() {
    switch (read_cpsr(id::cpsr::M)) {
        case constants::mode::USER: return id::mode::USER;
        case constants::mode::SUPERVISOR: return id::mode::SUPERVISOR;
        case constants::mode::ABORT: return id::mode::ABORT;
        case constants::mode::UNDEFINED: return id::mode::UNDEFINED;
        case constants::mode::FIQ: return id::mode::FIQ;
        case constants::mode::IRQ: return id::mode::IRQ;
        case constants::mode::SYSTEM: return id::mode::SYSTEM;
        default:
            out::error("No known enum value for read_mode()");
    }
}


[[nodiscard]] bool REGISTERS::is_priviledged() {
    return (read_mode() != id::mode::USER);
}


[[nodiscard]] u8 REGISTERS::read_cpsr(const id::cpsr cpsr_macro) {
    switch (cpsr_macro) {
        case id::cpsr::M: return (CPSR & 0b11111);
        case id::cpsr::T: return (CPSR & (1 << 5));
        case id::cpsr::F: return (CPSR & (1 << 6));
        case id::cpsr::I: return (CPSR & (1 << 7));
        case id::cpsr::A: return (CPSR & (1 << 8));
        case id::cpsr::E: return (CPSR & (1 << 9));
        //case id::cpsr::IT: return 0; TODO: think of a good exception here 
        case id::cpsr::GRE: return ((CPSR >> 16) & 0b1111);
        case id::cpsr::DNM: return ((CPSR >> 20) & 0b1111);
        case id::cpsr::J: return (CPSR & (1 << 24));
        case id::cpsr::Q: return (CPSR & (1 << 27));
        case id::cpsr::V: return (CPSR & (1 << 28));
        case id::cpsr::C: return (CPSR & (1 << 29));
        case id::cpsr::Z: return (CPSR & (1 << 30));
        case id::cpsr::N: return (CPSR & (1 << 31));
        default:
            out::error("No known enum value for read_cpsr()");
    }
}


void REGISTERS::write_cpsr(const id::reg reg_id) {
    switch (reg_id) {
        case id::reg::SPSR_abt: CPSR = read(id::reg::SPSR_abt); return;
        case id::reg::SPSR_fiq: CPSR = read(id::reg::SPSR_fiq); return;
        case id::reg::SPSR_irq: CPSR = read(id::reg::SPSR_irq); return;
        case id::reg::SPSR_svc: CPSR = read(id::reg::SPSR_svc); return;
        case id::reg::SPSR_und: CPSR = read(id::reg::SPSR_und); return;
        case id::reg::CURRENT_SPSR: CPSR = read(id::reg::CURRENT_SPSR); return;
        default:
            out::error("No valid id::reg enum value for write_cpsr()");
    }
}


void REGISTERS::write_cpsr(const id::cpsr cpsr_macro, const u8 value) {
    static constinit u32 M_mask = 0b11111;
    static constinit u32 GE_mask = (0b1111 << 16);
    static constinit u32 DNM_mask = (0b1111 << 20);
    
    switch (cpsr_macro) {
        case id::cpsr::M:
            CPSR &= ~M_mask; // clear the first 5 bits
            CPSR |= (value & M_mask); // set the first 5 bits with the new value
            return;
        case id::cpsr::T: CPSR |= (value << 5); return;
        case id::cpsr::F: CPSR |= (value << 6); return;
        case id::cpsr::I: CPSR |= (value << 7); return;
        case id::cpsr::A: CPSR |= (value << 8); return;
        case id::cpsr::E: CPSR |= (value << 9); return;
        case id::cpsr::IT: return; // TODO: think of a good exception
        case id::cpsr::GRE: 
            CPSR &= ~GE_mask;
            CPSR |= (value & GE_mask); 
            return;
        case id::cpsr::DNM:
            CPSR &= ~DNM_mask;
            CPSR |= (value & DNM_mask); 
            return;
        case id::cpsr::J: CPSR |= (value << 24); return;
        case id::cpsr::Q: CPSR |= (value << 27); return;
        case id::cpsr::V: CPSR |= (value << 28); return;
        case id::cpsr::C: CPSR |= (value << 29); return;
        case id::cpsr::Z: CPSR |= (value << 30); return;
        case id::cpsr::N: CPSR |= (value << 31); return;
        default:
            out::error("No known enum value for write_cpsr()");
    }
}

[[nodiscard]] u32 REGISTERS::read(const id::reg register_id) {
    switch (register_id) {
        case id::reg::R0: return R0;
        case id::reg::R1: return R1;
        case id::reg::R2: return R2;
        case id::reg::R3: return R3;
        case id::reg::R4: return R4;
        case id::reg::R5: return R5;
        case id::reg::R6: return R6;
        case id::reg::R7: return R7;
        case id::reg::PC: return PC;
        case id::reg::CPSR: return CPSR;
        default: break;
    }

    const id::mode mode = read_mode();

    if (mode == id::mode::FIQ) {
        switch (register_id) {
            case id::reg::R8:
            case id::reg::R8_fiq:  return R8_fiq;
            case id::reg::R9:
            case id::reg::R9_fiq:  return R9_fiq;
            case id::reg::R10:
            case id::reg::R10_fiq: return R10_fiq;
            case id::reg::R11:
            case id::reg::R11_fiq: return R11_fiq;
            case id::reg::R12:
            case id::reg::R12_fiq: return R12_fiq;
            case id::reg::R13:
            case id::reg::R13_fiq: return R13_fiq;
            case id::reg::R14:
            case id::reg::R14_fiq: return R14_fiq;
            case id::reg::CURRENT_SPSR:
            case id::reg::SPSR_fiq: return SPSR_fiq;
            default: break;
        }
    }

    switch (register_id) {
        case id::reg::R8:  return R8;
        case id::reg::R9:  return R9;
        case id::reg::R10: return R10;
        case id::reg::R11: return R11;
        case id::reg::R12: return R12;
        default: break;
    }

    switch (mode) {
        case id::mode::USER:
        case id::mode::SYSTEM:
            switch (register_id) {
                case id::reg::R13: return R13;
                case id::reg::R14: return R14;
                default: break;
            }
            break;

        case id::mode::SUPERVISOR:
            switch (register_id) {
                case id::reg::R13:
                case id::reg::R13_svc:  return R13_svc;
                case id::reg::R14:
                case id::reg::R14_svc:  return R14_svc;
                case id::reg::CURRENT_SPSR:
                case id::reg::SPSR_svc: return SPSR_svc; 
                default: break;
            }
            break;

        case id::mode::ABORT:
            switch (register_id) {
                case id::reg::R13:
                case id::reg::R13_abt:  return R13_abt;
                case id::reg::R14:
                case id::reg::R14_abt:  return R14_abt;
                case id::reg::CURRENT_SPSR:
                case id::reg::SPSR_abt: return SPSR_abt;
                default: break;
            }
            break;

        case id::mode::UNDEFINED:
            switch (register_id) {
                case id::reg::R13:
                case id::reg::R13_und:  return R13_und;
                case id::reg::R14:
                case id::reg::R14_und:  return R14_und;
                case id::reg::CURRENT_SPSR:
                case id::reg::SPSR_und: return SPSR_und; 
                default: break;
            }
            break;

        case id::mode::IRQ:
            switch (register_id) {
                case id::reg::R13:
                case id::reg::R13_irq:  return R13_irq;
                case id::reg::R14:
                case id::reg::R14_irq:  return R14_irq;
                case id::reg::CURRENT_SPSR:
                case id::reg::SPSR_irq: return SPSR_irq; 
                default: break;
            }
            break;
        default: break;
    }

    out::error("Couldn't read register in read()");
};


void REGISTERS::write(const id::reg register_id, const u32 value) {
    switch (register_id) {
        case id::reg::R0: R0 = value; return;
        case id::reg::R1: R1 = value; return;
        case id::reg::R2: R2 = value; return;
        case id::reg::R3: R3 = value; return;
        case id::reg::R4: R4 = value; return;
        case id::reg::R5: R5 = value; return;
        case id::reg::R6: R6 = value; return;
        case id::reg::R7: R7 = value; return;
        case id::reg::PC: PC = value; return;
        [[unlikely]] case id::reg::CPSR: CPSR = value; return;
        default: break;
    }

    const id::mode mode = read_mode();

    if (mode == id::mode::FIQ) {
        switch (register_id) {
            case id::reg::R8:
            case id::reg::R8_fiq: R8_fiq = value; return;
            case id::reg::R9:
            case id::reg::R9_fiq: R9_fiq = value; return;
            case id::reg::R10:
            case id::reg::R10_fiq: R10_fiq = value; return;
            case id::reg::R11:
            case id::reg::R11_fiq: R11_fiq = value; return;
            case id::reg::R12:
            case id::reg::R12_fiq: R12_fiq = value; return;
            case id::reg::R13:
            case id::reg::R13_fiq: R13_fiq = value; return;
            case id::reg::R14:
            case id::reg::R14_fiq: R14_fiq = value; return;
            default: break;
        }
    }

    switch (register_id) {
        case id::reg::R8: R8 = value; return;
        case id::reg::R9: R9 = value; return;
        case id::reg::R10: R10 = value; return;
        case id::reg::R11: R11 = value; return;
        case id::reg::R12: R12 = value; return;
        default: break;
    }

    switch (mode) {
        case id::mode::USER:
        case id::mode::SYSTEM:
            switch (register_id) {
                case id::reg::R13: R13 = value; return;
                case id::reg::R14: R14 = value; return;
                default: break;
            }
            break;

        case id::mode::SUPERVISOR:
            switch (register_id) {
                case id::reg::R13:
                case id::reg::R13_svc: R13_svc = value; return;
                case id::reg::R14:
                case id::reg::R14_svc: R14_svc = value; return;
                case id::reg::SPSR_svc: SPSR_svc = value; return;
                default: break;
            }
            break;

        case id::mode::ABORT:
            switch (register_id) {
                case id::reg::R13:
                case id::reg::R13_abt: R13_abt = value; return;
                case id::reg::R14:
                case id::reg::R14_abt: R14_abt = value; return;
                case id::reg::SPSR_abt: SPSR_abt = value; return;
                default: break;
            }
            break;

        case id::mode::UNDEFINED:
            switch (register_id) {
                case id::reg::R13:
                case id::reg::R13_und: R13_und = value; return;
                case id::reg::R14:
                case id::reg::R14_und: R14_und = value; return;
                case id::reg::SPSR_und: SPSR_und = value; return;
                default: break;
            }
            break;

        case id::mode::IRQ:
            switch (register_id) {
                case id::reg::R13:
                case id::reg::R13_irq: R13_irq = value; return;
                case id::reg::R14:
                case id::reg::R14_irq: R14_irq = value; return;
                case id::reg::SPSR_irq: SPSR_irq = value; return;
                default: break;
            }
            break;
        default: break;
    }
}

[[nodiscard]] id::reg REGISTERS::fetch_reg_id(const u8 value) noexcept {
    switch (value) {
        case 0: return id::reg::R0;
        case 1: return id::reg::R1;
        case 2: return id::reg::R2;
        case 3: return id::reg::R3;
        case 4: return id::reg::R4;
        case 5: return id::reg::R5;
        case 6: return id::reg::R6;
        case 7: return id::reg::R7;
        case 8: return id::reg::R8;
        case 9: return id::reg::R9;
        case 10: return id::reg::R10;
        case 11: return id::reg::R11;
        case 12: return id::reg::R12;
        case 13: return id::reg::R13;
        case 14: return id::reg::R14;
        case 15: return id::reg::PC;
        default: break;
    }

    out::error("Couldn't find suitable match for register identification in identifier()");
}

[[nodiscard]] id::reg REGISTERS::fetch_reg_id(const arm_code_t &code, const u8 start, const u8 end) noexcept {
    const u8 Rd_bits = util::bit_fetcher<u8>(code.to_ulong(), start, end);
    return fetch_reg_id(Rd_bits);
}

[[nodiscard]] id::reg REGISTERS::fetch_reg_id(const thumb_code_t &code, const u8 start, const u8 end) noexcept {
    const u8 Rd_bits = util::bit_fetcher<u8>(code.to_ulong(), start, end);
    return fetch_reg_id(Rd_bits);
}

[[nodiscard]] u32 REGISTERS::read(const arm_code_t &code, const u8 start, const u8 end) noexcept {
    return read(fetch_reg_id(code, start, end));
}

[[nodiscard]] u32 REGISTERS::read(const thumb_code_t &code, const u8 start, const u8 end) noexcept {
    return read(fetch_reg_id(code, start, end));
}

[[nodiscard]] u32 REGISTERS::read(const u8 reg_bits) noexcept {
    return read(fetch_reg_id(reg_bits));
}


[[nodiscard]] id::cond REGISTERS::fetch_cond_id(const u8 cond) {
    switch (cond) {
        case constants::cond::EQ: return id::cond::EQ;
        case constants::cond::NE: return id::cond::NE;
        case constants::cond::CS: return id::cond::CS;
        case constants::cond::CC: return id::cond::CC;
        case constants::cond::MI: return id::cond::MI;
        case constants::cond::PL: return id::cond::PL;
        case constants::cond::VS: return id::cond::VS;
        case constants::cond::VC: return id::cond::VC;
        case constants::cond::HI: return id::cond::HI;
        case constants::cond::LS: return id::cond::LS;
        case constants::cond::GE: return id::cond::GE;
        case constants::cond::LT: return id::cond::LT;
        case constants::cond::GT: return id::cond::GT;
        case constants::cond::LE: return id::cond::LE;
        case constants::cond::AL: return id::cond::AL;
        case constants::cond::NV: return id::cond::NV;
    }

    out::error("No match found with conditon constant in fetch_cond_id()");
}


[[nodiscard]] id::cond REGISTERS::fetch_cond_id(const arm_code_t &code) {
    switch ((code.to_ulong() & 0xF0000000) >> 28) {
        case constants::cond::EQ: return id::cond::EQ;
        case constants::cond::NE: return id::cond::NE;
        case constants::cond::CS: return id::cond::CS;
        case constants::cond::CC: return id::cond::CC;
        case constants::cond::MI: return id::cond::MI;
        case constants::cond::PL: return id::cond::PL;
        case constants::cond::VS: return id::cond::VS;
        case constants::cond::VC: return id::cond::VC;
        case constants::cond::HI: return id::cond::HI;
        case constants::cond::LS: return id::cond::LS;
        case constants::cond::GE: return id::cond::GE;
        case constants::cond::LT: return id::cond::LT;
        case constants::cond::GT: return id::cond::GT;
        case constants::cond::LE: return id::cond::LE;
        case constants::cond::AL: return id::cond::AL;
        case constants::cond::NV: return id::cond::NV;
    }

    out::error("No match found with conditon constant in fetch_cond_id()");
}


[[nodiscard]] id::mode REGISTERS::fetch_mode_id(const constants::mode mode) {
    switch (mode) {
        case constants::mode::USER: return id::mode::USER;
        case constants::mode::FIQ: return id::mode::FIQ;
        case constants::mode::IRQ: return id::mode::IRQ;
        case constants::mode::SUPERVISOR: return id::mode::SUPERVISOR;
        case constants::mode::ABORT: return id::mode::ABORT;
        case constants::mode::UNDEFINED: return id::mode::UNDEFINED;
        case constants::mode::SYSTEM: return id::mode::SYSTEM;
    };
}



[[nodiscard]] bool REGISTERS::check_cond(const id::cond cond) {
    switch (cond) {
        case id::cond::EQ: return (read_cpsr(id::cpsr::Z) == 1);
        case id::cond::NE: return (read_cpsr(id::cpsr::Z) == 0);
        case id::cond::CS: return (read_cpsr(id::cpsr::C) == 1);
        case id::cond::CC: return (read_cpsr(id::cpsr::C) == 0);
        case id::cond::MI: return (read_cpsr(id::cpsr::N) == 1);
        case id::cond::PL: return (read_cpsr(id::cpsr::N) == 0);
        case id::cond::VS: return (read_cpsr(id::cpsr::V) == 1);
        case id::cond::VC: return (read_cpsr(id::cpsr::V) == 0);
        case id::cond::HI: 
            return (
                (read_cpsr(id::cpsr::C) == 1) && 
                (read_cpsr(id::cpsr::Z) == 0)
            );
        case id::cond::LS:
            return (
                (read_cpsr(id::cpsr::C) == 0) ||
                (read_cpsr(id::cpsr::Z) == 1)
            );
        case id::cond::GE:
            return (
                (read_cpsr(id::cpsr::N)) == 
                (read_cpsr(id::cpsr::V))
            );
        case id::cond::LT:
            return (
                (read_cpsr(id::cpsr::N)) != 
                (read_cpsr(id::cpsr::V))
            );
        case id::cond::GT:
            return (
                (read_cpsr(id::cpsr::Z) == 0) &&
                (
                    (read_cpsr(id::cpsr::N)) == 
                    (read_cpsr(id::cpsr::V))
                )
            );
        case id::cond::LE:
            return (
                (read_cpsr(id::cpsr::Z) == 1) ||
                (
                    (read_cpsr(id::cpsr::N)) != 
                    (read_cpsr(id::cpsr::V))
                )
            );
        case id::cond::AL: return true;
        case id::cond::NV: return true;
    }
}

void REGISTERS::thumb_increment_PC() {
    PC += 2;
}

void REGISTERS::increment_PC() {
    PC += 4;
}