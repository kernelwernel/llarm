#pragma once

#include "../id.hpp"
#include "../settings.hpp"

#include <llarm/shared/types.hpp>

#include <array>

// PL190 / PL192 register offsets (DDI0181)
//   VECTCNTLn: bit[5]=slot enable, bits[4:0]=source select
constexpr u8  CNTL_ENABLE   = 0x20;
constexpr u8  CNTL_SRC_MASK = 0x1F;
constexpr u8  NUM_SLOTS     = 16;
constexpr u8  NUM_SOURCES   = 32;
constexpr u32 VIC_BASE_ADDR = 0xFFFFF000;
constexpr u32 VIC_RANGE_ADDR = 0xFFF;

constexpr u16 OFFSET_VICIRQSTATUS = 0x000;
constexpr u16 OFFSET_VICFIQSTATUS = 0x004;
constexpr u16 OFFSET_VICRAWINTR = 0x008;
constexpr u16 OFFSET_VICINTSELECT = 0x00C;
constexpr u16 OFFSET_VICINTENABLE = 0x010;
constexpr u16 OFFSET_VICINTENCLEAR = 0x014;
constexpr u16 OFFSET_VICSOFTINT = 0x018;
constexpr u16 OFFSET_VICSOFTINTCLEAR = 0x01C;
constexpr u16 OFFSET_VICPROTECTION = 0x020;
constexpr u16 OFFSET_VICVECTADDR = 0x030;
constexpr u16 OFFSET_VICDEFVECTADDR = 0x034;
constexpr u16 OFFSET_VICVECTADDR0 = 0x100;
constexpr u16 OFFSET_VICVECTADDR1 = 0x104;
constexpr u16 OFFSET_VICVECTADDR2 = 0x108;
constexpr u16 OFFSET_VICVECTADDR3 = 0x10C;
constexpr u16 OFFSET_VICVECTADDR4 = 0x110;
constexpr u16 OFFSET_VICVECTADDR5 = 0x114;
constexpr u16 OFFSET_VICVECTADDR6 = 0x118;
constexpr u16 OFFSET_VICVECTADDR7 = 0x11C;
constexpr u16 OFFSET_VICVECTADDR8 = 0x120;
constexpr u16 OFFSET_VICVECTADDR9 = 0x124;
constexpr u16 OFFSET_VICVECTADDR10 = 0x128;
constexpr u16 OFFSET_VICVECTADDR11 = 0x12C; 
constexpr u16 OFFSET_VICVECTADDR12 = 0x130;
constexpr u16 OFFSET_VICVECTADDR13 = 0x134;
constexpr u16 OFFSET_VICVECTADDR14 = 0x138;
constexpr u16 OFFSET_VICVECTADDR15 = 0x13C;
constexpr u16 OFFSET_VICVECTCNTL0 = 0x200;
constexpr u16 OFFSET_VICVECTCNTL1 = 0x204;
constexpr u16 OFFSET_VICVECTCNTL2 = 0x208;
constexpr u16 OFFSET_VICVECTCNTL3 = 0x20C;
constexpr u16 OFFSET_VICVECTCNTL4 = 0x210;
constexpr u16 OFFSET_VICVECTCNTL5 = 0x214;
constexpr u16 OFFSET_VICVECTCNTL6 = 0x218;
constexpr u16 OFFSET_VICVECTCNTL7 = 0x21C;
constexpr u16 OFFSET_VICVECTCNTL8 = 0x220;
constexpr u16 OFFSET_VICVECTCNTL9 = 0x224;
constexpr u16 OFFSET_VICVECTCNTL10 = 0x228;
constexpr u16 OFFSET_VICVECTCNTL11 = 0x22C;
constexpr u16 OFFSET_VICVECTCNTL12 = 0x230;
constexpr u16 OFFSET_VICVECTCNTL13 = 0x234;
constexpr u16 OFFSET_VICVECTCNTL14 = 0x238;
constexpr u16 OFFSET_VICVECTCNTL15 = 0x23C;
constexpr u16 OFFSET_VICPERIPHID0 = 0xFE0;
constexpr u16 OFFSET_VICPERIPHID1 = 0xFE4;
constexpr u16 OFFSET_VICPERIPHID2 = 0xFE8;
constexpr u16 OFFSET_VICPERIPHID3 = 0xFEC;
constexpr u16 OFFSET_VICPCELLID0 = 0xFF0;
constexpr u16 OFFSET_VICPCELLID1 = 0xFF4;
constexpr u16 OFFSET_VICPCELLID2 = 0xFF8;
constexpr u16 OFFSET_VICPCELLID3 = 0xFFC;

constexpr u16 VICITCR  = 0x300;
constexpr u16 VICITIP1 = 0x304;
constexpr u16 VICITIP2 = 0x308;
constexpr u16 VICITOP1 = 0x30C;
constexpr u16 VICITOP2 = 0x310;

constexpr u32 PERIPH_ID0 = 0x90;
constexpr u32 PERIPH_ID1 = 0x11;
constexpr u32 PERIPH_ID2 = 0x04;
constexpr u32 PERIPH_ID3 = 0x00;
constexpr u32 PCELL_ID0  = 0x0D;
constexpr u32 PCELL_ID1  = 0xF0;
constexpr u32 PCELL_ID2  = 0x05;
constexpr u32 PCELL_ID3  = 0xB1;

constexpr u8 PRIO_NONE = NUM_SLOTS; // 16

constexpr bool IS_FORCED = true;

struct VIC {
    SETTINGS& settings;

    id::vic_type type;
    u32 base;

    // polled by the fetch-decode-execute loop after each instruction
    bool irq_pending() const;
    bool fiq_pending() const;

    // true if addr falls within this VIC's 4KB memory-mapped window
    bool contains(const u32 address) const;

    u32  read(const u32 address);
    void write(const u32 address, const u32 value);

    void raise_irq(const u8 source);
    void clear_irq(const u8 source);

    VIC(SETTINGS& settings) : settings(settings) {
        type = settings.vic_type;
        base = (settings.vic_base != 0) ? settings.vic_base : VIC_BASE_ADDR;
    }

    u32 hw_raw = 0; // raw hardware interrupt line states (raise/clear)
    u32 int_enable = 0; // VICINTENABLE
    u32 int_select = 0; // VICINTSELECT
    u32 soft_int = 0; // VICSOFTINT
    u32 protection = 0; // VICPROTECTION
    u32 def_vect_addr = 0; // VICDEFVECTADDR
    std::array<u32, NUM_SLOTS> vect_addr = {0}; // VICVECTADDR0–15
    std::array<u32, NUM_SLOTS> vect_cntl = {0}; // VICVECTCNTL0–15

    // priority queue for interrupts
    std::array<u8, PRIO_NONE> prio_stack = {0};
    u8 prio_depth = 0;
    u32 current_vect_addr = 0;

    u32 itcr = 0; // VICITCR
    u32 itip1 = 0; // VICITIP1
    u32 itip2 = 0; // VICITIP2
    u32 itop1 = 0; // VICITOP1
    u32 itop2 = 0; // VICITOP2

    // daisy chain inputs
    bool daisy_irq_in = false;
    bool daisy_fiq_in = false;
};