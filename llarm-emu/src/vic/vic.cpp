#include "vic.hpp"
#include <llarm/shared/util.hpp>


bool VIC::contains(const u32 address) const {
    return (address >= base) && (address <= (base + VIC_RANGE_ADDR));
}


void VIC::raise_irq(const u8 source) {
    if (source >= NUM_SOURCES) {
        return;
    }

    llarm::util::modify_bit(hw_raw, source, true);
}

void VIC::clear_irq(const u8 source) {
    if (source >= NUM_SOURCES) { 
        return;
    }

    llarm::util::modify_bit(hw_raw, source, false);
}


bool VIC::irq_pending() const {
    return (((hw_raw | soft_int) & int_enable & ~int_select) != 0) || daisy_irq_in;
}

bool VIC::fiq_pending() const {
    return (((hw_raw | soft_int) & int_enable & int_select) != 0) || daisy_fiq_in;
}


u32 VIC::read(const u32 address) {
    const u32 offset = address - base;
    const u32 raw    = hw_raw | soft_int;
    const u32 active_irq = raw & int_enable & ~int_select;
    const u32 active_fiq = raw & int_enable &  int_select;

    switch (offset) {
        case OFFSET_VICIRQSTATUS: return active_irq;
        case OFFSET_VICFIQSTATUS: return active_fiq;
        case OFFSET_VICRAWINTR: return raw;
        case OFFSET_VICINTSELECT: return int_select;
        case OFFSET_VICINTENABLE: return int_enable;
        case OFFSET_VICINTENCLEAR: return 0; // write-only
        case OFFSET_VICSOFTINT: return soft_int;
        case OFFSET_VICSOFTINTCLEAR: return 0; // write-only
        case OFFSET_VICPROTECTION: return protection;

        case OFFSET_VICVECTADDR: {
            // Priority arbitration: find highest-priority active vectored IRQ
            // that can preempt the current nesting level, then push the stack.
            const u8 cur = (prio_depth == 0) ? PRIO_NONE : prio_stack.at(prio_depth - 1);
            for (u8 i = 0; i < NUM_SLOTS; i++) {
                // E bit in VICVECTCNT
                if (!llarm::util::bit_fetch(vect_cntl.at(i), 5)) {
                    continue;
                }

                const u8 src = llarm::util::bit_range<u8>(vect_cntl.at(i), 0, 4);
                if (!llarm::util::bit_fetch(active_irq, src)) {
                    continue;
                }

                if (i < cur) {
                    prio_stack.at(prio_depth++) = i;
                    current_vect_addr = vect_addr.at(i);
                    return vect_addr.at(i);
                }

                break; // lower slots have higher index = lower priority, can't preempt either
            }
            return def_vect_addr;
        }

        case OFFSET_VICDEFVECTADDR: return def_vect_addr;

        case OFFSET_VICPERIPHID0: return PERIPH_ID0;
        case OFFSET_VICPERIPHID1: return PERIPH_ID1;
        case OFFSET_VICPERIPHID2: return PERIPH_ID2;
        case OFFSET_VICPERIPHID3: return PERIPH_ID3;
        case OFFSET_VICPCELLID0: return PCELL_ID0;
        case OFFSET_VICPCELLID1: return PCELL_ID1;
        case OFFSET_VICPCELLID2: return PCELL_ID2;
        case OFFSET_VICPCELLID3: return PCELL_ID3;

        case VICITCR:  return itcr;
        case VICITIP1: return itip1;
        case VICITIP2: return itip2;
        case VICITOP1: return itop1;
        case VICITOP2: return itop2;

        default: break;
    }

    if (offset >= OFFSET_VICVECTADDR0 && offset <= OFFSET_VICVECTADDR15) {
        return vect_addr.at((offset - OFFSET_VICVECTADDR0) / 4);
    }

    if (offset >= OFFSET_VICVECTCNTL0 && offset <= OFFSET_VICVECTCNTL15) {
        return vect_cntl.at((offset - OFFSET_VICVECTCNTL0) / 4);
    }

    return 0;
}


void VIC::write(const u32 address, const u32 value) {
    const u32 offset = address - base;

    switch (offset) {
        // read-only registers
        case OFFSET_VICIRQSTATUS:
        case OFFSET_VICFIQSTATUS:
        case OFFSET_VICRAWINTR:
            return;

        case OFFSET_VICINTSELECT:    int_select  = value; return;
        case OFFSET_VICINTENABLE:    int_enable |= value; return;
        case OFFSET_VICINTENCLEAR:   int_enable &= ~value; return;
        case OFFSET_VICSOFTINT:      soft_int   |= value; return;
        case OFFSET_VICSOFTINTCLEAR: soft_int   &= ~value; return;
        case OFFSET_VICPROTECTION:   protection  = llarm::util::bit_range<u32>(value, 0, 0); return;

        case OFFSET_VICVECTADDR:
            // EOI: pop the priority stack
            if (prio_depth > 0) {
                --prio_depth;
                current_vect_addr = (prio_depth > 0)
                    ? vect_addr.at(prio_stack.at(prio_depth - 1))
                    : 0;
            }
            return;

        case OFFSET_VICDEFVECTADDR: def_vect_addr = value; return;

        case VICITCR: itcr = value & 0x1; return;
        case VICITIP1: itip1 = value; return;
        case VICITIP2: itip2 = value; return;
        // VICITOP1/2 are read-only test outputs

        default: break;
    }

    if (offset >= OFFSET_VICVECTADDR0 && offset <= OFFSET_VICVECTADDR15) {
        vect_addr.at((offset - OFFSET_VICVECTADDR0) / 4) = value;
        return;
    }

    if (offset >= OFFSET_VICVECTCNTL0 && offset <= OFFSET_VICVECTCNTL15) {
        vect_cntl.at((offset - OFFSET_VICVECTCNTL0) / 4) = value & 0x3F; // bits[5:0] only
        return;
    }
}
