#include "../../constants.hpp"
#include "../../id.hpp"
#include "registers.hpp"

#include <llarm/shared/out.hpp>
#include <llarm/shared/util.hpp>

// TODO SYSTEM MODE IS NOT SUPPORTED IN EARLIER VERSIONS
id::mode REGISTERS::read_mode() {
    if (arch_26.is_26_arch_program()) { // 26-bit mode arch
        switch (read(id::cpsr::M)) {
            case constants::mode::USER_26: return id::mode::USER_26;
            case constants::mode::FIQ_26: return id::mode::FIQ_26;
            case constants::mode::IRQ_26: return id::mode::IRQ_26;
            case constants::mode::SUPERVISOR_26: return id::mode::SUPERVISOR_26;
            default: 
                llarm::out::error("No known enum value for read_mode()");
        }
    } else { // 32-bit mode arch
        switch (read(id::cpsr::M)) {
            case constants::mode::USER: return id::mode::USER;
            case constants::mode::SUPERVISOR: return id::mode::SUPERVISOR;
            case constants::mode::ABORT: return id::mode::ABORT;
            case constants::mode::UNDEFINED: return id::mode::UNDEFINED;
            case constants::mode::FIQ: return id::mode::FIQ;
            case constants::mode::IRQ: return id::mode::IRQ;
            case constants::mode::SYSTEM: return id::mode::SYSTEM;
            default: 
                llarm::out::error("No known enum value for read_mode()");
        }
    }
}


bool REGISTERS::is_privileged() {
    const id::mode mode = read_mode();

    return (!(
        (mode == id::mode::USER) ||
        (mode == id::mode::USER_26)
    ));
}

bool REGISTERS::is_exception() {
    const id::mode mode = read_mode();
    
    return (!(
        (mode == id::mode::USER) || 
        (mode == id::mode::USER_26) || 
        (mode == id::mode::SYSTEM)
    ));
}

bool REGISTERS::current_mode_has_SPSR() {
    const id::mode mode = read_mode();

    switch (mode) {
        case id::mode::USER:
        case id::mode::USER_26:
        case id::mode::SUPERVISOR:
        case id::mode::SUPERVISOR_26: return false;
        default: return true;
    }
}


void REGISTERS::write(const id::reg destination_reg_id, const id::reg source_reg_id) {
    write(destination_reg_id, read(source_reg_id));
}

void REGISTERS::write(const id::cpsr cpsr_macro, const u8 value) {

    // 26-bit mode uses bits in R15 as its version of the 32-bit mode CPSR, we're knee deep in some real funky shit here.
    if (arch_26.is_26_arch_program()) [[unlikely]] {
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
                    case constants::mode::SYSTEM: llarm::out::warning("No 32-bit mode switch from 26-bit architecture is valid, the mode bits will be treated in 26-bit mode which may be unpredictable");   
                    default: break;
                }

                llarm::util::swap_bits(R15_copy, 0, 1, value); break;
            case id::cpsr::N: llarm::util::modify_bit(R15_copy, 31, value); break;
            case id::cpsr::Z: llarm::util::modify_bit(R15_copy, 30, value); break;
            case id::cpsr::C: llarm::util::modify_bit(R15_copy, 29, value); break;
            case id::cpsr::V: llarm::util::modify_bit(R15_copy, 28, value); break;
            case id::cpsr::I: llarm::util::modify_bit(R15_copy, 27, value); break;
            case id::cpsr::F: llarm::util::modify_bit(R15_copy, 26, value); break;
            default: llarm::out::error("No known enum value for write() (26-bit)");
        }

        write(id::reg::R15, R15_copy);
        return;
    } else {
        switch (cpsr_macro) {
            case id::cpsr::M: llarm::util::swap_bits(CPSR, 0, 4, value); return;
            case id::cpsr::T: 
                if (value == true) {
                    globals.instruction_set = id::instruction_sets::THUMB;
                } else if (value == false) {
                    globals.instruction_set = id::instruction_sets::ARM;
                }
                llarm::util::modify_bit(CPSR, 5, value);
                return;
            case id::cpsr::F: llarm::util::modify_bit(CPSR, 6, value); return;
            case id::cpsr::I: llarm::util::modify_bit(CPSR, 7, value); return;
            //case id::cpsr::A: llarm::util::modify_bit(CPSR, 8, value); return;
            //case id::cpsr::E: llarm::util::modify_bit(CPSR, 9, value); return;
            //case id::cpsr::IT: return; // TODO: think of a good exception
            //case id::cpsr::GE: llarm::util::swap_bits(CPSR, 16, 19, value); return;
            //case id::cpsr::DNM: llarm::util::swap_bits(CPSR, 20, 23, value); return;
            //case id::cpsr::J: llarm::util::modify_bit(CPSR, 24, value); return;
            case id::cpsr::Q: llarm::util::modify_bit(CPSR, 27, value); return;
            case id::cpsr::V: llarm::util::modify_bit(CPSR, 28, value); return;
            case id::cpsr::C: llarm::util::modify_bit(CPSR, 29, value); return;
            case id::cpsr::Z: llarm::util::modify_bit(CPSR, 30, value); return;
            case id::cpsr::N: llarm::util::modify_bit(CPSR, 31, value); return;
        }
    }
}


void REGISTERS::write(const u32 code, const u8 start, const u8 end, const u32 value) {
    const id::reg id = fetch_reg_id(llarm::util::bit_range(code, start, end));
    write(id, value);
}


void REGISTERS::write(const u8 reg_bits, const u32 value) {
    write(fetch_reg_id(reg_bits), value);
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
        [[likely]] case id::reg::PC: write_PC(value); return;
        case id::reg::CPSR: 
            if (arch_26.is_only_26_arch()) {
                llarm::out::error("CPSR does not exist in pure 26-bit architecture");
            }
            CPSR = value;
            return;
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
            default: llarm::out::error("Invalid SPSR write");
        }
    }

    switch (mode) {
        case id::mode::SYSTEM:
            if (settings.arch < id::arch::ARMv4) {
                llarm::out::error("system mode is only supported from ARMv4 onwards");
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
                default: break;
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


u8 REGISTERS::read(const id::cpsr cpsr_macro) {
    if (arch_26.is_26_arch_program()) { // 26-bit
        switch (cpsr_macro) {
            case id::cpsr::M: return (CPSR & 0b11);
            case id::cpsr::N: return llarm::util::bit_fetch(CPSR, 31);
            case id::cpsr::Z: return llarm::util::bit_fetch(CPSR, 30);
            case id::cpsr::C: return llarm::util::bit_fetch(CPSR, 29);
            case id::cpsr::V: return llarm::util::bit_fetch(CPSR, 28);
            case id::cpsr::I: return llarm::util::bit_fetch(CPSR, 27);
            case id::cpsr::F: return llarm::util::bit_fetch(CPSR, 26);
            default:
                llarm::out::error("No known enum value for read() (26-bit)");
        }
    } else {
        switch (cpsr_macro) {
            case id::cpsr::M: return (CPSR & 0b11111);
            case id::cpsr::T: return llarm::util::bit_fetch(CPSR, 5);
            case id::cpsr::F: return llarm::util::bit_fetch(CPSR, 6);
            case id::cpsr::I: return llarm::util::bit_fetch(CPSR, 7);
            case id::cpsr::Q: return llarm::util::bit_fetch(CPSR, 27);
            case id::cpsr::V: return llarm::util::bit_fetch(CPSR, 28);
            case id::cpsr::C: return llarm::util::bit_fetch(CPSR, 29);
            case id::cpsr::Z: return llarm::util::bit_fetch(CPSR, 30);
            case id::cpsr::N: return llarm::util::bit_fetch(CPSR, 31);
        }
    }
}


u32 REGISTERS::read(const id::reg register_id) {
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
            if (arch_26.is_only_26_arch()) {
                llarm::out::error("CPSR does not exist in pure 26-bit architecture");
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
            default: llarm::out::error("TODO"); // TODO add error or warning idk
        }
    }

    switch (mode) {
        case id::mode::SYSTEM:
            if (settings.arch < id::arch::ARMv4) {
                llarm::out::error("TODO"); // maybe add a warning/error, idk
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
                default: break;
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

    llarm::out::error("Couldn't read register in read() = ", (int)register_id);
};


void REGISTERS::access_check(const id::reg register_id) {
    if (arch_26.no_26_arch_support()) {
        return;
    }

    if (arch_26.is_only_26_arch()) {
        switch (register_id) {
            case id::reg::CPSR: llarm::out::error("CPSR does not exist in pure 26-bit architecture");
            case id::reg::SPSR: llarm::out::error("SPSR does not exist in pure 26-bit architecture");
            case id::reg::SPSR_svc: llarm::out::error("SPSR_svc does not exist in pure 26-bit architecture");
            case id::reg::SPSR_abt: llarm::out::error("SPSR_abt does not exist in pure 26-bit architecture");
            case id::reg::SPSR_und: llarm::out::error("SPSR_und does not exist in pure 26-bit architecture");
            case id::reg::SPSR_irq: llarm::out::error("SPSR_irq does not exist in pure 26-bit architecture");
            case id::reg::SPSR_fiq: llarm::out::error("SPSR_fiq does not exist in pure 26-bit architecture");
            default: break;
        }
    }

    if (arch_26.is_26_arch_program() && arch_26.is_26_arch_backwards_compatible()) {
        switch (register_id) {
            case id::reg::R13_abt:
            case id::reg::R14_abt:
            case id::reg::SPSR_abt: llarm::out::error("SPSR_abt register does not exist in 26-bit architecure mode (read)"); break;
            case id::reg::R13_und:
            case id::reg::R14_und:
            case id::reg::SPSR_und: llarm::out::error("SPSR_und register does not exist in 26-bit architecure mode (read)"); break;
            default: break;
        }
    }
}


id::reg REGISTERS::fetch_reg_id(const u8 value) {
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

    llarm::out::error("Couldn't find suitable match for register identification in identifier()");
}

id::reg REGISTERS::fetch_reg_id(const u32 code, const u8 start, const u8 end) {
    const u8 Rd_bits = llarm::util::bit_range<u8>(code, start, end);

    id::reg reg_id = fetch_reg_id(Rd_bits);

    // if the start and end indexes are 16 and 19 while in 26-bit mode,
    // only the 26:2 range of R15 is read. Otherwise if it's 0 and 3, 
    // R15 will be read as 31:0 as if it's in 32-bit arch mode.
    // The whole point is to convert to a PC ID instead of an R15 ID
    // because the PC ID has more responsibilities to manage in 26-bit mode.
    if (
        (arch_26.is_26_arch_program()) &&
        (reg_id == id::reg::R15) &&
        ((start == 16) && (end == 19))
    ) {
        reg_id = id::reg::PC;
    }

    return reg_id;
}


id::reg REGISTERS::thumb_fetch_reg_id(const u16 code, const u8 start, const u8 end) {
    const u8 Rd_bits = llarm::util::bit_range<u8>(code, start, end);
    return fetch_reg_id(Rd_bits);
}


u32 REGISTERS::read(const u32 code, const u8 start, const u8 end) {
    const id::reg reg_id = fetch_reg_id(code, start, end);
    return read(reg_id);
}


u32 REGISTERS::read(const u8 reg_bits) {
    return read(fetch_reg_id(reg_bits));
}


id::cond REGISTERS::fetch_cond_id(const u8 cond) {
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

    llarm::out::error("No match found with conditon constant in fetch_cond_id()");
}


id::cond REGISTERS::fetch_cond_id(const u32 code) {
    return fetch_cond_id(llarm::util::bit_range<u8>(code, 28, 31));
}


id::mode REGISTERS::fetch_mode_id(const u8 mode) {
    switch (mode) {
        case constants::mode::USER: return id::mode::USER;
        case constants::mode::FIQ: return id::mode::FIQ;
        case constants::mode::IRQ: return id::mode::IRQ;
        case constants::mode::SUPERVISOR: return id::mode::SUPERVISOR;
        case constants::mode::ABORT: return id::mode::ABORT;
        case constants::mode::UNDEFINED: return id::mode::UNDEFINED;
        case constants::mode::SYSTEM: return id::mode::SYSTEM;
        case constants::mode::USER_26: return id::mode::USER_26;
        case constants::mode::FIQ_26: return id::mode::FIQ_26;
        case constants::mode::IRQ_26: return id::mode::IRQ_26;
        case constants::mode::SUPERVISOR_26: return id::mode::SUPERVISOR_26;
        default: llarm::out::error("TODO");
    };
}



bool REGISTERS::is_cond_valid(const id::cond cond) {
    switch (cond) {
        case id::cond::EQ: return (read(id::cpsr::Z) == 1);
        case id::cond::NE: return (read(id::cpsr::Z) == 0);
        case id::cond::CS: return (read(id::cpsr::C) == 1);
        case id::cond::CC: return (read(id::cpsr::C) == 0);
        case id::cond::MI: return (read(id::cpsr::N) == 1);
        case id::cond::PL: return (read(id::cpsr::N) == 0);
        case id::cond::VS: return (read(id::cpsr::V) == 1);
        case id::cond::VC: return (read(id::cpsr::V) == 0);
        case id::cond::HI: 
            return (
                (read(id::cpsr::C) == 1) && 
                (read(id::cpsr::Z) == 0)
            );
        case id::cond::LS:
            return (
                (read(id::cpsr::C) == 0) ||
                (read(id::cpsr::Z) == 1)
            );
        case id::cond::GE:
            return (
                (read(id::cpsr::N)) == 
                (read(id::cpsr::V))
            );
        case id::cond::LT:
            return (
                (read(id::cpsr::N)) != 
                (read(id::cpsr::V))
            );
        case id::cond::GT:
            return (
                (read(id::cpsr::Z) == 0) &&
                (
                    (read(id::cpsr::N)) == 
                    (read(id::cpsr::V))
                )
            );
        case id::cond::LE:
            return (
                (read(id::cpsr::Z) == 1) ||
                (
                    (read(id::cpsr::N)) != 
                    (read(id::cpsr::V))
                )
            );
        case id::cond::AL: return true;
        case id::cond::NV: 
            switch (settings.arch) {
                case id::arch::ARMv1:
                case id::arch::ARMv2: return false;
                case id::arch::ARMv3: 
                case id::arch::ARMv4: 
                    llarm::out::unpredictable("NV condition field for ARMv3 and ARMv4 are unpredictable"); 
                    return true;
        
                default: return true;
            }
        default: llarm::out::error("TODO");
    }
}

void REGISTERS::switch_mode(const id::mode mode) {
    switch (mode) {
        case id::mode::USER:          write(id::cpsr::M, constants::mode::USER); return;
        case id::mode::SUPERVISOR:    write(id::cpsr::M, constants::mode::SUPERVISOR); return;
        case id::mode::ABORT:         write(id::cpsr::M, constants::mode::ABORT); return;
        case id::mode::UNDEFINED:     write(id::cpsr::M, constants::mode::UNDEFINED); return;
        case id::mode::FIQ:           write(id::cpsr::M, constants::mode::FIQ); return;
        case id::mode::IRQ:           write(id::cpsr::M, constants::mode::IRQ); return;
        case id::mode::SYSTEM:        write(id::cpsr::M, constants::mode::SYSTEM); return;
        case id::mode::FIQ_26:        write(id::cpsr::M, constants::mode::FIQ_26); return;
        case id::mode::IRQ_26:        write(id::cpsr::M, constants::mode::IRQ_26); return;
        case id::mode::SUPERVISOR_26: write(id::cpsr::M, constants::mode::SUPERVISOR_26); return;
        case id::mode::USER_26:       write(id::cpsr::M, constants::mode::USER_26); return;
    }
}


bool REGISTERS::is_cond_valid(const u32 code) {
    const id::cond cond_id = fetch_cond_id(code);
    return is_cond_valid(cond_id);
}


void REGISTERS::write_PC(const u32 address) {
    if (arch_26.is_26_arch_address()) {
        // llarm::util::swap_bits(R15, 2, 25, (address & 0x03FFFFFF)); TODO, this is most likely wrong
    } else {
        R15 = address;
    }
}


u32 REGISTERS::read_PC() {
    if (arch_26.is_26_arch_address()) {
        return (llarm::util::bit_range<u32>(R15, 2, 25)); 
    } else {
        return R15; 
    }
}


void REGISTERS::thumb_increment_PC() {
    write(id::reg::PC, (R15 + 2)); // maybe optimise this with direct R15 write
}

void REGISTERS::arm_increment_PC() {
    write(id::reg::PC, (R15 + 4)); // maybe optimise this with direct R15 write
}

void REGISTERS::reset() {
    R0 = 0;
    R1 = 0;
    R2 = 0;
    R3 = 0;
    R4 = 0;
    R5 = 0;
    R6 = 0;
    R7 = 0;
    R8_fiq = 0;
    R9_fiq = 0;
    R10_fiq = 0;
    R11_fiq = 0;
    R12_fiq = 0;
    R13_fiq = 0;
    R14_fiq = 0;
    R13_svc = 0;
    R14_svc = 0;
    R13_abt = 0;
    R14_abt = 0;
    R13_und = 0;
    R14_und = 0;
    R13_irq = 0;
    R14_irq = 0;
    R8 = 0;
    R9 = 0;
    R10 = 0;
    R11 = 0;
    R12 = 0;
    R13 = 0;
    R14 = 0;
    R15 = 0;
    CPSR = 0;
    SPSR_svc = 0;
    SPSR_abt = 0;
    SPSR_und = 0;
    SPSR_irq = 0;
    SPSR_fiq = 0;
}