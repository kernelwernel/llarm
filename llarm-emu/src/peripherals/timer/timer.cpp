#include "timer.hpp"

#include <llarm/shared/util.hpp>


bool timer_channel::irq_pending() const {
	return (ris & 0x1U) != 0 && llarm::util::bit_fetch(control, TIMERCTRL_BIT_INTENABLE);
}


u32 timer_channel::read(const u8 channel_offset) const {
	switch (channel_offset) {
		case OFFSET_TIMERLOAD:    return load;
		case OFFSET_TIMERVALUE:   return value;
		case OFFSET_TIMERCONTROL: return control;
		case OFFSET_TIMERINTCLR:  return 0;  // write-only
		case OFFSET_TIMERRIS:     return ris & 0x1U;
		case OFFSET_TIMERMIS:     return static_cast<u32>(irq_pending());
		case OFFSET_TIMERBGLOAD:  return bgload;
		default: return 0;
	}
}


void timer_channel::write(const u8 channel_offset, const u32 val) {
	switch (channel_offset) {
		case OFFSET_TIMERLOAD:
			load = val;
			bgload = val;
			value = val;  // immediately restart counter
			prescaler_count = 0;
			return;

		case OFFSET_TIMERVALUE: return;  // read-only

		case OFFSET_TIMERCONTROL:
			control = val & 0xFFU;
			prescaler_count = 0;
			return;

		case OFFSET_TIMERINTCLR:
			ris = 0;
			return;

		case OFFSET_TIMERRIS: return;  // read-only
		case OFFSET_TIMERMIS: return;  // read-only

		case OFFSET_TIMERBGLOAD:
			bgload = val;
			load   = val;
			// does not restart the counter; takes effect on next underflow
			return;

		default: return;
	}
}


void timer_channel::tick() {
	if (!llarm::util::bit_fetch(control, TIMERCTRL_BIT_TIMEREN)) {
		return;
	}

	const bool is_32bit = llarm::util::bit_fetch(control, TIMERCTRL_BIT_TIMERSIZE);
	const bool is_oneshot = llarm::util::bit_fetch(control, TIMERCTRL_BIT_ONESHOT);

	// in one-shot mode, stay halted once the counter has reached zero
	if (is_oneshot && (is_32bit ? (value == 0U) : ((value & 0xFFFFU) == 0U))) {
		return;
	}

	// prescaler: only advance the counter every N ticks
	const u8 pre = static_cast<u8>((control >> TIMERCTRL_PRE_SHIFT) & TIMERCTRL_PRE_MASK);
	const u32 prescale_div = [pre]() -> u32 {
		switch (pre) {
			case 0: return 1;
			case 1: return 16;
			case 2: return 256;
			default: return 1;  // undefined per TRM; treat as div1
		}
	}();

	prescaler_count++;
	if (prescaler_count < prescale_div) {
		return;
	}
	prescaler_count = 0;

	// decrement counter
	if (is_32bit) {
		value--;
	} else {
		// only bits [15:0] participate; upper 16 bits are preserved (TRM 3.2.2)
		const u32 low = (value & 0xFFFFU) - 1U;
		value = (value & 0xFFFF0000U) | (low & 0xFFFFU);
	}

	// underflow: counter just reached zero
	const bool underflowed = is_32bit ? (value == 0U) : ((value & 0xFFFFU) == 0U);

	if (!underflowed) {
		return;
	}

	ris = 1;

	const bool is_periodic = llarm::util::bit_fetch(control, TIMERCTRL_BIT_TIMERMODE);

	if (is_oneshot) {
		// counter halts at zero; retriggered by a new write to TimerXLoad
	} else if (is_periodic) {
		value = load;
	} else {
		// free-running: wrap bits back to maximum
		value = is_32bit ? 0xFFFFFFFFU : (value & 0xFFFF0000U) | 0xFFFFU;
	}
}


bool SP804::contains(const u32 address) const {
	return (address >= base) && (address <= (base + SP804_RANGE_ADDR));
}


bool SP804::irq_pending() const {
	return timer1.irq_pending() || timer2.irq_pending();
}


u32 SP804::read(const u32 address) const {
	const u32 offset = address - base;

	if (offset <= OFFSET_TIMER1BGLOAD) {
		return timer1.read(static_cast<u8>(offset));
	}

	if (offset >= OFFSET_TIMER2LOAD && offset <= OFFSET_TIMER2BGLOAD) {
		return timer2.read(static_cast<u8>(offset - OFFSET_TIMER2LOAD));
	}

	switch (offset) {
		case OFFSET_TIMER_PERIPHID0: return TIMER_PERIPHID0;
		case OFFSET_TIMER_PERIPHID1: return TIMER_PERIPHID1;
		case OFFSET_TIMER_PERIPHID2: return TIMER_PERIPHID2;
		case OFFSET_TIMER_PERIPHID3: return TIMER_PERIPHID3;
		case OFFSET_TIMER_PCELLID0:  return TIMER_PCELLID0;
		case OFFSET_TIMER_PCELLID1:  return TIMER_PCELLID1;
		case OFFSET_TIMER_PCELLID2:  return TIMER_PCELLID2;
		case OFFSET_TIMER_PCELLID3:  return TIMER_PCELLID3;
		default: return 0;
	}
}


void SP804::write(const u32 address, const u32 value) {
	const u32 offset = address - base;

	if (offset <= OFFSET_TIMER1BGLOAD) {
		timer1.write(static_cast<u8>(offset), value);
		return;
	}

	if (offset >= OFFSET_TIMER2LOAD && offset <= OFFSET_TIMER2BGLOAD) {
		timer2.write(static_cast<u8>(offset - OFFSET_TIMER2LOAD), value);
		return;
	}

	// identification registers are read-only; writes are silently ignored
}


void SP804::tick() {
	timer1.tick();
	timer2.tick();
}
