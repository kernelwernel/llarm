#pragma once

#include "../../settings.hpp"

#include <llarm/shared/types.hpp>

#include <queue>

// this UART model is based on the PL011, full docs can be seen in the manuals folder

// PL011 UART register offsets (ARM DDI 0183G, r1p5)
constexpr u16 OFFSET_UARTDR    = 0x000;
constexpr u16 OFFSET_UARTRSR   = 0x004;  // UARTECR on write
constexpr u16 OFFSET_UARTFR    = 0x018;
constexpr u16 OFFSET_UARTILPR  = 0x020;
constexpr u16 OFFSET_UARTIBRD  = 0x024;
constexpr u16 OFFSET_UARTFBRD  = 0x028;
constexpr u16 OFFSET_UARTLCR_H = 0x02C;
constexpr u16 OFFSET_UARTCR    = 0x030;
constexpr u16 OFFSET_UARTIFLS  = 0x034;
constexpr u16 OFFSET_UARTIMSC  = 0x038;
constexpr u16 OFFSET_UARTRIS   = 0x03C;
constexpr u16 OFFSET_UARTMIS   = 0x040;
constexpr u16 OFFSET_UARTICR   = 0x044;
constexpr u16 OFFSET_UARTDMACR = 0x048;

constexpr u16 OFFSET_UART_PERIPHID0 = 0xFE0;
constexpr u16 OFFSET_UART_PERIPHID1 = 0xFE4;
constexpr u16 OFFSET_UART_PERIPHID2 = 0xFE8;
constexpr u16 OFFSET_UART_PERIPHID3 = 0xFEC;
constexpr u16 OFFSET_UART_PCELLID0  = 0xFF0;
constexpr u16 OFFSET_UART_PCELLID1  = 0xFF4;
constexpr u16 OFFSET_UART_PCELLID2  = 0xFF8;
constexpr u16 OFFSET_UART_PCELLID3  = 0xFFC;

// UARTFR bit positions
constexpr u8 UARTFR_BIT_TXFE = 7;
constexpr u8 UARTFR_BIT_RXFF = 6;
constexpr u8 UARTFR_BIT_TXFF = 5;
constexpr u8 UARTFR_BIT_RXFE = 4;
constexpr u8 UARTFR_BIT_BUSY = 3;

// UARTCR bit positions
constexpr u8 UARTCR_BIT_RXE    = 9;
constexpr u8 UARTCR_BIT_TXE    = 8;
constexpr u8 UARTCR_BIT_UARTEN = 0;

// UARTLCR_H bit positions
constexpr u8 UARTLCR_H_BIT_FEN = 4;

// UARTRSR bit positions
constexpr u8 UARTRSR_BIT_OE = 3;
constexpr u8 UARTRSR_BIT_BE = 2;
constexpr u8 UARTRSR_BIT_PE = 1;
constexpr u8 UARTRSR_BIT_FE = 0;

// UARTRIS / UARTIMSC / UARTICR interrupt bit positions
constexpr u8 UART_INT_OE = 10;
constexpr u8 UART_INT_BE = 9;
constexpr u8 UART_INT_PE = 8;
constexpr u8 UART_INT_FE = 7;
constexpr u8 UART_INT_RT = 6;
constexpr u8 UART_INT_TX = 5;
constexpr u8 UART_INT_RX = 4;

// UARTDR error bit positions (bits [11:8] of an RX FIFO entry)
constexpr u8 UART_DR_BIT_OE = 11;
constexpr u8 UART_DR_BIT_BE = 10;
constexpr u8 UART_DR_BIT_PE = 9;
constexpr u8 UART_DR_BIT_FE = 8;

// Peripheral identification values (DDI 0183G r1p5)
constexpr u32 UART_PERIPHID0 = 0x11;
constexpr u32 UART_PERIPHID1 = 0x10;
constexpr u32 UART_PERIPHID2 = 0x34;
constexpr u32 UART_PERIPHID3 = 0x00;
constexpr u32 UART_PCELLID0  = 0x0D;
constexpr u32 UART_PCELLID1  = 0xF0;
constexpr u32 UART_PCELLID2  = 0x05;
constexpr u32 UART_PCELLID3  = 0xB1;

constexpr u32 PL011_RANGE_ADDR = 0xFFF;
constexpr u8  TX_FIFO_DEPTH    = 32;
constexpr u8  RX_FIFO_DEPTH    = 32;

struct UART {
    SETTINGS& settings;
    u32 base;

    bool irq_pending() const;
    bool contains(const u32 address) const;

    u32 read(const u32 address);
    void write(const u32 address, const u32 value);

    // inject a byte into the RX FIFO (called by host or external device)
    // error_flags: bits [3:0] map to OE/BE/PE/FE
    void receive(const u8 data, const u8 error_flags = 0);

    // pop one byte from the TX FIFO; returns false if the FIFO is empty
    bool transmit(u8& data);

    UART(SETTINGS& settings, const u32 base)
        : settings(settings), base(base) {}

    // TX FIFO: 32 x 8-bit entries
    std::queue<u8>  tx_fifo;
    // RX FIFO: 32 x 12-bit entries, bits [11:8] = error flags, bits [7:0] = data
    std::queue<u16> rx_fifo;

    // registers with TRM reset values
    u32 rsr = 0x00; // UARTRSR: receive status / error bits
    u32 ilpr = 0x00; // UARTILPR: IrDA low-power counter
    u32 ibrd = 0x0000; // UARTIBRD: integer baud rate divisor
    u32 fbrd = 0x00; // UARTFBRD: fractional baud rate divisor
    u32 lcr_h = 0x00; // UARTLCR_H: line control
    u32 cr = 0x0300; // UARTCR: control register (TXE=1, RXE=1, UARTEN=0)
    u32 ifls = 0x12; // UARTIFLS: interrupt FIFO level select (TX=1/2, RX=1/2)
    u32 imsc = 0x000; // UARTIMSC: interrupt mask
    u32 ris = 0x000; // UARTRIS: raw interrupt status
    u32 dmacr = 0x00; // UARTDMACR: DMA control

    u32 flag_register() const;
    u8 tx_trigger_level() const;
    u8 rx_trigger_level() const;
    void update_tx_interrupt();
    void update_rx_interrupt();
};
