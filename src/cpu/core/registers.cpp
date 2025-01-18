#include <iostream>

#include "constants.hpp"
#include "id.hpp"
#include "utility.hpp"
#include "out.hpp"
#include "cpu/core/registers.hpp"


[[nodiscard]] id::mode REGISTERS::read_mode() {
    if (coprocessor.is_26_bit_arch_program()) { // 26-bit mode arch
        switch (read_cpsr(id::cpsr::M)) {
            case constants::mode::USER_26: return id::mode::USER_26;
            case constants::mode::FIQ_26: return id::mode::FIQ_26;
            case constants::mode::IRQ_26: return id::mode::IRQ_26;
            case constants::mode::SUPERVISOR_26: return id::mode::SUPERVISOR_26;
            default: 
                out::error("No known enum value for read_mode()");
        }
    } else { // 32-bit mode arch
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
}


[[nodiscard]] bool REGISTERS::is_priviledged() {
    const id::mode mode = read_mode();

    return (!(
        (mode == id::mode::USER) ||
        (mode == id::mode::USER_26)
    ));
}

[[nodiscard]] bool REGISTERS::is_exception() {
    const id::mode mode = read_mode();
    
    return (!(
        (mode == id::mode::USER) || 
        (mode == id::mode::USER_26) || 
        (mode == id::mode::SYSTEM)
    ))
}

[[nodiscard]] u8 REGISTERS::read_cpsr(const id::cpsr cpsr_macro) {
    if (coprocessor.is_26_bit_arch_program()) { // 26-bit
        switch (cpsr_macro) {
            case id::cpsr::M: return (CPSR & 0b11);
            case id::cpsr::N: return (CPSR & (1 << 31));
            case id::cpsr::Z: return (CPSR & (1 << 30));
            case id::cpsr::C: return (CPSR & (1 << 29));
            case id::cpsr::V: return (CPSR & (1 << 28));
            case id::cpsr::I: return (CPSR & (1 << 27));
            case id::cpsr::F: return (CPSR & (1 << 26));
            default:
                out::error("No known enum value for read_cpsr() (26-bit)");
        }
    } else {
        switch (cpsr_macro) {
            case id::cpsr::M: return (CPSR & 0b11111);
            case id::cpsr::T: return (CPSR & (1 << 5));
            case id::cpsr::F: return (CPSR & (1 << 6));
            case id::cpsr::I: return (CPSR & (1 << 7));
            case id::cpsr::A: return (CPSR & (1 << 8));
            case id::cpsr::E: return (CPSR & (1 << 9));
            //case id::cpsr::IT: return 0; TODO: think of a good exception here 
            case id::cpsr::GE: return ((CPSR >> 16) & 0b1111);
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
}


void REGISTERS::write_cpsr(const id::reg reg_id) {
    CPSR = read(reg_id);
}


void REGISTERS::write_cpsr(const id::cpsr cpsr_macro, const u8 value) {

    // 26-bit mode uses bits in R15 as its version of the 32-bit mode CPSR, we're knee deep in some real funky shit here.
    if (coprocessor.is_26_bit_arch_program()) [[unlikely]] {
        u32 R15_copy = read(id::reg::R15);

        switch (cpsr_macro) {
            case id::cpsr::M: 
                // it's not possible to go back to a 32-bit mode from a 26-bit mode
                switch (value) {
                    case constants::mode::ABORT:
                    case constants::mode::USER:
                    case constants::mode::SUPERVISOR:
                    case constants::mode::UNDEFINED:
                    case constants::mode::FIQ:
                    case constants::mode::IRQ:
                    case constants::mode::SYSTEM: out::warning("No 32-bit mode switch from 26-bit architecture is valid, the mode bits will be treated in 26-bit mode which may be unpredictable");   
                    default: break;
                }

                util::modify_bit_range(R15_copy, 0, 1, value); break;
            case id::cpsr::N: util::modify_bit(R15_copy, 31, value); break;
            case id::cpsr::Z: util::modify_bit(R15_copy, 30, value); break;
            case id::cpsr::C: util::modify_bit(R15_copy, 29, value); break;
            case id::cpsr::V: util::modify_bit(R15_copy, 28, value); break;
            case id::cpsr::I: util::modify_bit(R15_copy, 27, value); break;
            case id::cpsr::F: util::modify_bit(R15_copy, 26, value); break;
            default: out::error("No known enum value for write_cpsr() (26-bit)");
        }

        write(id::reg::R15, R15_copy);
        return;
    } else {
        static constinit u32 GE_mask = (0b1111 << 16);
        static constinit u32 DNM_mask = (0b1111 << 20);

        switch (cpsr_macro) {
            case id::cpsr::M: util::modify_bit_range(CPSR, 0, 4, value); return;
            case id::cpsr::T: 
                if (value == true) {
                    globals.instruction_set = id::instruction_sets::THUMB;
                } else if (value == false) {
                    globals.instruction_set = id::instruction_sets::ARM;
                }
                CPSR |= (value << 5); 
                return;
            case id::cpsr::F: CPSR |= (value << 6); return;
            case id::cpsr::I: CPSR |= (value << 7); return;
            case id::cpsr::A: CPSR |= (value << 8); return;
            case id::cpsr::E: CPSR |= (value << 9); return;
            case id::cpsr::IT: return; // TODO: think of a good exception
            case id::cpsr::GE: 
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
}



























[[nodiscard]] u32 REGISTERS::read(const id::reg register_id) {
    access_check(register_id);

    switch (register_id) {
        case id::reg::R0: return R0;
        case id::reg::R1: return R1;
        case id::reg::R2: return R2;
        case id::reg::R3: return R3;
        case id::reg::R4: return R4;
        case id::reg::R5: return R5;
        case id::reg::R6: return R6;
        case id::reg::R7: return R7;
        case id::reg::R15: return R15;
        case id::reg::PC: return read_PC(); // R15 and PC are the same, except for 26-bit arch 
        case id::reg::CPSR: 
            if (coprocessor.is_only_26_bit_arch()) {
                out::error("CPSR does not exist in pure 26-bit architecture");
            }
            return CPSR;
        default: break;
    }

    const id::mode mode = read_mode();

    if (register_id == id::reg::SPSR) {
        switch (mode) {
            case id::mode::FIQ: 
            case id::mode::FIQ_26: return SPSR_fiq;
            case id::mode::IRQ:
            case id::mode::IRQ_26: return SPSR_irq; 
            case id::mode::SUPERVISOR:
            case id::mode::SUPERVISOR_26: return SPSR_svc; 
            case id::mode::ABORT: return SPSR_abt; 
            case id::mode::UNDEFINED: return SPSR_und; 
            default: // TODO add error or warning idk
        }
    }

    switch (mode) {
        case id::mode::SYSTEM:
            if (static_cast<u8>(settings.arch) < 4) {
                break; // maybe add a warning/error, idk
            }
        case id::mode::USER:
        case id::mode::USER_26:
            switch (register_id) {
                case id::reg::R8:  return R8;
                case id::reg::R9:  return R9;
                case id::reg::R10: return R10;
                case id::reg::R11: return R11;
                case id::reg::R12: return R12;
                case id::reg::R13: return R13;
                case id::reg::R14: return R14;
                default: break;
            }
            break;
    
        case id::mode::FIQ:
        case id::mode::FIQ_26:
            switch (register_id) {
                case id::reg::R8_fiq:  return R8_fiq;
                case id::reg::R9_fiq:  return R9_fiq;
                case id::reg::R10_fiq: return R10_fiq;
                case id::reg::R11_fiq: return R11_fiq;
                case id::reg::R12_fiq: return R12_fiq;
                case id::reg::R13_fiq: return R13_fiq;
                case id::reg::R14_fiq: return R14_fiq;
                case id::reg::SPSR_fiq: return SPSR_fiq;
            }
            break;
        
        case id::mode::IRQ:
        case id::mode::IRQ_26:
            switch (register_id) {
                case id::reg::R8:  return R8;
                case id::reg::R9:  return R9;
                case id::reg::R10: return R10;
                case id::reg::R11: return R11;
                case id::reg::R12: return R12;
                case id::reg::R13_irq:  return R13_irq;
                case id::reg::R14_irq:  return R14_irq;
                case id::reg::SPSR_irq: return SPSR_irq; 
                default: break;
            }
            break;

        case id::mode::SUPERVISOR:
        case id::mode::SUPERVISOR_26:
            switch (register_id) {
                case id::reg::R8:  return R8;
                case id::reg::R9:  return R9;
                case id::reg::R10: return R10;
                case id::reg::R11: return R11;
                case id::reg::R12: return R12;
                case id::reg::R13_svc:  return R13_svc;
                case id::reg::R14_svc:  return R14_svc;
                case id::reg::SPSR_svc: return SPSR_svc; 
                default: break;
            }
            break;

        case id::mode::ABORT:
            switch (register_id) {
                case id::reg::R8:  return R8;
                case id::reg::R9:  return R9;
                case id::reg::R10: return R10;
                case id::reg::R11: return R11;
                case id::reg::R12: return R12;
                case id::reg::R13_abt:  return R13_abt;
                case id::reg::R14_abt:  return R14_abt;
                case id::reg::SPSR_abt: return SPSR_abt; 
                default: break;
            }
            break;

        case id::mode::UNDEFINED:
            switch (register_id) {
                case id::reg::R8:  return R8;
                case id::reg::R9:  return R9;
                case id::reg::R10: return R10;
                case id::reg::R11: return R11;
                case id::reg::R12: return R12;
                case id::reg::R13_und:  return R13_und;
                case id::reg::R14_und:  return R14_und;
                case id::reg::SPSR_und: return SPSR_und; 
                default: break;
            }
            break;
    }

    out::error("Couldn't read register in read()");
};













void access_check(const id::reg register_id) {
    if (coprocessor.no_26_bit_arch_support()) {
        return;
    }

    if (coprocessor.is_only_26_bit_arch()) {
        switch (register_id) {
            case id::reg::CPSR: out::error("CPSR does not exist in pure 26-bit architecture");
            case id::reg::SPSR: out::error("SPSR does not exist in pure 26-bit architecture");
            case id::reg::SPSR_svc: out::error("SPSR_svc does not exist in pure 26-bit architecture");
            case id::reg::SPSR_abt: out::error("SPSR_abt does not exist in pure 26-bit architecture");
            case id::reg::SPSR_und: out::error("SPSR_und does not exist in pure 26-bit architecture");
            case id::reg::SPSR_irq: out::error("SPSR_irq does not exist in pure 26-bit architecture");
            case id::reg::SPSR_fiq: out::error("SPSR_fiq does not exist in pure 26-bit architecture");
        }
    }

    if (coprocessor.is_26_bit_arch_program() && coprocessor.is_26_bit_arch_backwards_support()) {
        switch (register_id) {
            case id::reg::R13_abt:
            case id::reg::R14_abt:
            case id::reg::SPSR_abt: out::error("SPSR_abt register does not exist in 26-bit architecure mode (read)"); break;
            case id::reg::R13_und:
            case id::reg::R14_und:
            case id::reg::SPSR_und: out::error("SPSR_und register does not exist in 26-bit architecure mode (read)"); break;
            default: break;
        }
    }

}































void REGISTERS::write(const id::reg register_id, const u32 value) {
    access_check(register_id);

    switch (register_id) {
        case id::reg::R0: R0 = value; return;
        case id::reg::R1: R1 = value; return;
        case id::reg::R2: R2 = value; return;
        case id::reg::R3: R3 = value; return;
        case id::reg::R4: R4 = value; return;
        case id::reg::R5: R5 = value; return;
        case id::reg::R6: R6 = value; return;
        case id::reg::R7: R7 = value; return;
        case id::reg::R15: R15 = value; return;
        case id::reg::PC: write_PC(value); return;
        case id::reg::CPSR: 
            if (coprocessor.is_only_26_bit_arch()) {
                out::error("CPSR does not exist in pure 26-bit architecture");
            }
            return CPSR;
        default: break;
    }

    const id::mode mode = read_mode();

    if (register_id == id::reg::SPSR) {
        switch (mode) {
            case id::mode::FIQ:
            case id::mode::FIQ_26: SPSR_fiq = value; return;
            case id::mode::IRQ:
            case id::mode::IRQ_26: SPSR_irq = value; return;
            case id::mode::SUPERVISOR:
            case id::mode::SUPERVISOR_26: SPSR_svc = value; return;
            case id::mode::ABORT: SPSR_abt = value; return;
            case id::mode::UNDEFINED: SPSR_und = value; return;
            default: // TODO add error or warning idk
        }
    }

    switch (mode) {
        case id::mode::SYSTEM:
            if (static_cast<u8>(settings.arch) < 4) {
                break; // maybe add a warning/error, idk
            }
        case id::mode::USER:
        case id::mode::USER_26:
            switch (register_id) {
                case id::reg::R8:  R8 = value; return;
                case id::reg::R9:  R9 = value; return;
                case id::reg::R10: R10 = value; return;
                case id::reg::R11: R11 = value; return;
                case id::reg::R12: R12 = value; return;
                case id::reg::R13: R13 = value; return;
                case id::reg::R14: R14 = value; return;
                default: break;
            }
            break;
    
        case id::mode::FIQ:
        case id::mode::FIQ_26:
            switch (register_id) {
                case id::reg::R8_fiq:  R8_fiq = value; return;
                case id::reg::R9_fiq:  R9_fiq = value; return;
                case id::reg::R10_fiq: R10_fiq = value; return;
                case id::reg::R11_fiq: R11_fiq = value; return;
                case id::reg::R12_fiq: R12_fiq = value; return;
                case id::reg::R13_fiq: R13_fiq = value; return;
                case id::reg::R14_fiq: R14_fiq = value; return;
                case id::reg::SPSR_fiq: SPSR_fiq = value; return;
            }
            break;
        
        case id::mode::IRQ:
        case id::mode::IRQ_26:
            switch (register_id) {
                case id::reg::R8:  R8 = value; return;
                case id::reg::R9:  R9 = value; return;
                case id::reg::R10: R10 = value; return;
                case id::reg::R11: R11 = value; return;
                case id::reg::R12: R12 = value; return;
                case id::reg::R13_irq:  R13_irq = value; return;
                case id::reg::R14_irq:  R14_irq = value; return;
                case id::reg::SPSR_irq: SPSR_irq = value; return; 
                default: break;
            }
            break;

        case id::mode::SUPERVISOR:
        case id::mode::SUPERVISOR_26:
            switch (register_id) {
                case id::reg::R8:  R8 = value; return;
                case id::reg::R9:  R9 = value; return;
                case id::reg::R10: R10 = value; return;
                case id::reg::R11: R11 = value; return;
                case id::reg::R12: R12 = value; return;
                case id::reg::R13_svc:  R13_svc = value; return;
                case id::reg::R14_svc:  R14_svc = value; return;
                case id::reg::SPSR_svc: SPSR_svc = value; return; 
                default: break;
            }
            break;

        case id::mode::ABORT:
            switch (register_id) {
                case id::reg::R8:  R8 = value; return;
                case id::reg::R9:  R9 = value; return;
                case id::reg::R10: R10 = value; return;
                case id::reg::R11: R11 = value; return;
                case id::reg::R12: R12 = value; return;
                case id::reg::R13_abt:  R13_abt = value; return;
                case id::reg::R14_abt:  R14_abt = value; return;
                case id::reg::SPSR_abt: SPSR_abt = value; return; 
                default: break;
            }
            break;

        case id::mode::UNDEFINED:
            switch (register_id) {
                case id::reg::R8:  R8 = value; return;
                case id::reg::R9:  R9 = value; return;
                case id::reg::R10: R10 = value; return;
                case id::reg::R11: R11 = value; return;
                case id::reg::R12: R12 = value; return;
                case id::reg::R13_und:  R13_und = value; return;
                case id::reg::R14_und:  R14_und = value; return;
                case id::reg::SPSR_und: SPSR_und = value; return; 
                default: break;
            }
            break;
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
        case 15: return id::reg::R15;
        default: break;
    }

    out::error("Couldn't find suitable match for register identification in identifier()");
}

[[nodiscard]] id::reg REGISTERS::fetch_reg_id(const arm_code_t &code, const u8 start, const u8 end) noexcept {
    const u8 Rd_bits = util::bit_fetcher<u8>(code.to_ulong(), start, end);
    
    id::reg reg_id = fetch_reg_id(Rd_bits);

    // if the start and end indexes are 16 and 19 while in 26-bit mode,
    // only the 26:2 range of R15 is read. Otherwise if it's 0 and 3, 
    // R15 will be read as 31:0 as if it's in 32-bit arch mode.
    // The whole point is to convert to a PC ID instead of an R15 ID
    // because the PC ID has more responsibilities to manage in 26-bit mode.
    if (
        (coprocessor.is_26_bit_arch_program()) &&
        (reg_id == id::reg::R15) &&
        ((start == 16) && (end == 19))
    ) {
        reg_id = id::reg::PC;
    }

    return reg_id;
}

[[nodiscard]] id::reg REGISTERS::fetch_reg_id(const thumb_code_t &code, const u8 start, const u8 end) noexcept {
    const u8 Rd_bits = util::bit_fetcher<u8>(code.to_ulong(), start, end);
    return fetch_reg_id(Rd_bits);
}

[[nodiscard]] u32 REGISTERS::read(const arm_code_t &code, const u8 start, const u8 end) noexcept {
    id::reg reg_id = fetch_reg_id(code, start, end);
    return read(reg_id);
}

[[nodiscard]] u32 REGISTERS::read(const thumb_code_t &code, const u8 start, const u8 end) noexcept {
    const id::reg reg_id = fetch_reg_id(code, start, end);
    return read(reg_id);
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

void REGISTERS::arm_increment_PC() {
    PC += 4;
}