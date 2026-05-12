#pragma once

#include "../../settings.hpp"

#include <llarm/shared/types.hpp>

// this timer model is based on the SP804, full docs can be seen in the manuals folder

// SP804 register offsets, Timer1 (ARM DDI 0271D, r1p0)
constexpr u16 OFFSET_TIMER1LOAD    = 0x000;
constexpr u16 OFFSET_TIMER1VALUE   = 0x004;
constexpr u16 OFFSET_TIMER1CONTROL = 0x008;
constexpr u16 OFFSET_TIMER1INTCLR  = 0x00C;
constexpr u16 OFFSET_TIMER1RIS     = 0x010;
constexpr u16 OFFSET_TIMER1MIS     = 0x014;
constexpr u16 OFFSET_TIMER1BGLOAD  = 0x018;

// SP804 register offsets, Timer2
constexpr u16 OFFSET_TIMER2LOAD    = 0x020;
constexpr u16 OFFSET_TIMER2VALUE   = 0x024;
constexpr u16 OFFSET_TIMER2CONTROL = 0x028;
constexpr u16 OFFSET_TIMER2INTCLR  = 0x02C;
constexpr u16 OFFSET_TIMER2RIS     = 0x030;
constexpr u16 OFFSET_TIMER2MIS     = 0x034;
constexpr u16 OFFSET_TIMER2BGLOAD  = 0x038;

// peripheral/PrimeCell identification register offsets
constexpr u16 OFFSET_TIMER_PERIPHID0 = 0xFE0;
constexpr u16 OFFSET_TIMER_PERIPHID1 = 0xFE4;
constexpr u16 OFFSET_TIMER_PERIPHID2 = 0xFE8;
constexpr u16 OFFSET_TIMER_PERIPHID3 = 0xFEC;
constexpr u16 OFFSET_TIMER_PCELLID0  = 0xFF0;
constexpr u16 OFFSET_TIMER_PCELLID1  = 0xFF4;
constexpr u16 OFFSET_TIMER_PCELLID2  = 0xFF8;
constexpr u16 OFFSET_TIMER_PCELLID3  = 0xFFC;

// per-channel relative offsets (identical layout for both Timer1 and Timer2)
constexpr u8 OFFSET_TIMERLOAD    = 0x00;
constexpr u8 OFFSET_TIMERVALUE   = 0x04;
constexpr u8 OFFSET_TIMERCONTROL = 0x08;
constexpr u8 OFFSET_TIMERINTCLR  = 0x0C;
constexpr u8 OFFSET_TIMERRIS     = 0x10;
constexpr u8 OFFSET_TIMERMIS     = 0x14;
constexpr u8 OFFSET_TIMERBGLOAD  = 0x18;

// TimerXControl bit positions (Table 3-2)
constexpr u8 TIMERCTRL_BIT_TIMEREN   = 7;  // timer enable (default: 0)
constexpr u8 TIMERCTRL_BIT_TIMERMODE = 6;  // 0=free-running, 1=periodic (default: 0)
constexpr u8 TIMERCTRL_BIT_INTENABLE = 5;  // interrupt enable (default: 1)
// bit [4]: reserved
// bits [3:2]: TimerPre prescaler (00=div1, 01=div16, 10=div256; 11=undefined)
constexpr u8 TIMERCTRL_BIT_TIMERSIZE = 1;  // 0=16-bit, 1=32-bit (default: 0)
constexpr u8 TIMERCTRL_BIT_ONESHOT   = 0;  // 0=wrapping, 1=one-shot (default: 0)

constexpr u8 TIMERCTRL_PRE_SHIFT = 2;
constexpr u8 TIMERCTRL_PRE_MASK  = 0x3U;

// peripheral identification values (DDI 0271D r1p0)
constexpr u32 TIMER_PERIPHID0 = 0x04;
constexpr u32 TIMER_PERIPHID1 = 0x18;
constexpr u32 TIMER_PERIPHID2 = 0x14;
constexpr u32 TIMER_PERIPHID3 = 0x00;
constexpr u32 TIMER_PCELLID0 = 0x0D;
constexpr u32 TIMER_PCELLID1 = 0xF0;
constexpr u32 TIMER_PCELLID2 = 0x05;
constexpr u32 TIMER_PCELLID3 = 0xB1;

constexpr u32 SP804_RANGE_ADDR = 0xFFF;

struct timer_channel {
    // registers with TRM reset values
    u32 load    = 0x00000000;  // TimerXLoad
    u32 value   = 0xFFFFFFFF;  // TimerXValue: current counter
    u32 control = 0x20;        // TimerXControl: IntEnable=1
    u32 bgload  = 0x00000000;  // TimerXBGLoad
    u32 ris     = 0x0;         // raw interrupt status (bit [0] only)

    bool irq_pending() const;

    // channel_offset is relative to this channel's register base (0x00-0x18)
    u32 read(u8 channel_offset) const;
    void write(u8 channel_offset, u32 val);

    void tick();

    u32 prescaler_count = 0;
};

struct TIMER {
    SETTINGS& settings;
    u32 base;

    bool irq_pending() const;
    bool contains(const u32 address) const;

    u32 read(const u32 address) const;
    void write(const u32 address, const u32 value);

    // advance both timer counters by one effective clock tick
    void tick();

    TIMER(SETTINGS& settings, const u32 base)
        : settings(settings), base(base) {}

    timer_channel timer1;
    timer_channel timer2;
};
