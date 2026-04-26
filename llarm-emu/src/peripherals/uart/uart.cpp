#include "uart.hpp"

#include <llarm/shared/util.hpp>

#include <cstdio>


bool UART::contains(const u32 address) const {
    return (address >= base) && (address <= (base + PL011_RANGE_ADDR));
}


bool UART::irq_pending() const {
    return (ris & imsc) != 0;
}


u8 UART::tx_trigger_level() const {
    // TXIFLSEL = ifls[2:0]; trigger fires when TX FIFO size <= threshold
    switch (ifls & 0x7U) {
        case 0: return TX_FIFO_DEPTH / 8;          // 1/8 full  = 4
        case 1: return TX_FIFO_DEPTH / 4;          // 1/4 full  = 8
        case 2: return TX_FIFO_DEPTH / 2;          // 1/2 full  = 16 (default)
        case 3: return (TX_FIFO_DEPTH * 3U) / 4U;  // 3/4 full  = 24
        case 4: return (TX_FIFO_DEPTH * 7U) / 8U;  // 7/8 full  = 28
        default: return TX_FIFO_DEPTH / 2;
    }
}


u8 UART::rx_trigger_level() const {
    // RXIFLSEL = ifls[5:3]; trigger fires when RX FIFO size >= threshold
    switch ((ifls >> 3U) & 0x7U) {
        case 0: return RX_FIFO_DEPTH / 8;          // 1/8 full  = 4
        case 1: return RX_FIFO_DEPTH / 4;          // 1/4 full  = 8
        case 2: return RX_FIFO_DEPTH / 2;          // 1/2 full  = 16 (default)
        case 3: return (RX_FIFO_DEPTH * 3U) / 4U;  // 3/4 full  = 24
        case 4: return (RX_FIFO_DEPTH * 7U) / 8U;  // 7/8 full  = 28
        default: return RX_FIFO_DEPTH / 2;
    }
}


void UART::update_tx_interrupt() {
    if (!llarm::util::bit_fetch(cr, UARTCR_BIT_UARTEN)) {
        llarm::util::modify_bit(ris, UART_INT_TX, false);
        return;
    }

    const bool fifo_enabled = llarm::util::bit_fetch(lcr_h, UARTLCR_H_BIT_FEN);
    const u8 threshold = fifo_enabled ? tx_trigger_level() : static_cast<u8>(0);
    const bool triggered = static_cast<u8>(tx_fifo.size()) <= threshold;

    llarm::util::modify_bit(ris, UART_INT_TX, triggered);
}


void UART::update_rx_interrupt() {
    if (!llarm::util::bit_fetch(cr, UARTCR_BIT_UARTEN)) {
        llarm::util::modify_bit(ris, UART_INT_RX, false);
        return;
    }

    const bool fifo_enabled = llarm::util::bit_fetch(lcr_h, UARTLCR_H_BIT_FEN);
    const u8 threshold = fifo_enabled ? rx_trigger_level() : static_cast<u8>(1);
    const bool triggered = static_cast<u8>(rx_fifo.size()) >= threshold;

    llarm::util::modify_bit(ris, UART_INT_RX, triggered);
}


u32 UART::flag_register() const {
    const bool fifo_enabled = llarm::util::bit_fetch(lcr_h, UARTLCR_H_BIT_FEN);
    const u8 tx_max = static_cast<u8>(fifo_enabled ? TX_FIFO_DEPTH : 1U);
    const u8 rx_max = static_cast<u8>(fifo_enabled ? RX_FIFO_DEPTH : 1U);
    const u8 tx_sz = static_cast<u8>(tx_fifo.size());
    const u8 rx_sz = static_cast<u8>(rx_fifo.size());

    u32 fr = 0;
    llarm::util::modify_bit(fr, UARTFR_BIT_TXFE, tx_sz == 0);
    llarm::util::modify_bit(fr, UARTFR_BIT_TXFF, tx_sz >= tx_max);
    llarm::util::modify_bit(fr, UARTFR_BIT_RXFE, rx_sz == 0);
    llarm::util::modify_bit(fr, UARTFR_BIT_RXFF, rx_sz >= rx_max);
    llarm::util::modify_bit(fr, UARTFR_BIT_BUSY, !tx_fifo.empty());

    return fr;
}


u32 UART::read(const u32 address) {
    const u32 offset = address - base;

    switch (offset) {
        case OFFSET_UARTDR: {
            if (rx_fifo.empty()) {
                return 0;
            }

            const u16 entry = rx_fifo.front();

            rx_fifo.pop();
            rsr = (entry >> 8U) & 0xFU;            
            update_rx_interrupt();

            return entry;
        }

        case OFFSET_UARTRSR: return rsr;
        case OFFSET_UARTFR: return flag_register();
        case OFFSET_UARTILPR: return ilpr;
        case OFFSET_UARTIBRD: return ibrd;
        case OFFSET_UARTFBRD: return fbrd;
        case OFFSET_UARTLCR_H: return lcr_h;
        case OFFSET_UARTCR: return cr;
        case OFFSET_UARTIFLS: return ifls;
        case OFFSET_UARTIMSC: return imsc;
        case OFFSET_UARTRIS: return ris;
        case OFFSET_UARTMIS: return ris & imsc;
        case OFFSET_UARTICR: return 0;  // write-only
        case OFFSET_UARTDMACR: return dmacr;

        case OFFSET_UART_PERIPHID0: return UART_PERIPHID0;
        case OFFSET_UART_PERIPHID1: return UART_PERIPHID1;
        case OFFSET_UART_PERIPHID2: return UART_PERIPHID2;
        case OFFSET_UART_PERIPHID3: return UART_PERIPHID3;
        case OFFSET_UART_PCELLID0: return UART_PCELLID0;
        case OFFSET_UART_PCELLID1: return UART_PCELLID1;
        case OFFSET_UART_PCELLID2: return UART_PCELLID2;
        case OFFSET_UART_PCELLID3: return UART_PCELLID3;

        default: return 0;
    }
}


void UART::write(const u32 address, const u32 value) {
    const u32 offset = address - base;

    switch (offset) {
        case OFFSET_UARTDR: {
            if (!llarm::util::bit_fetch(cr, UARTCR_BIT_UARTEN)) {
                return;
            }

            if (!llarm::util::bit_fetch(cr, UARTCR_BIT_TXE)) {
                return;
            }

            const bool fifo_enabled = llarm::util::bit_fetch(lcr_h, UARTLCR_H_BIT_FEN);
            const auto tx_max = static_cast<u8>(fifo_enabled ? TX_FIFO_DEPTH : 1U);
            
            if (static_cast<u8>(tx_fifo.size()) < tx_max) {
                const auto byte = static_cast<u8>(value & 0xFFU);
                tx_fifo.push(byte);
                std::putchar(byte);
            }

            update_tx_interrupt();
            return;
        }

        case OFFSET_UARTRSR: // UARTECR on write: any write clears all error bits
            rsr = 0;
            return;

        case OFFSET_UARTFR: return; // read-only

        case OFFSET_UARTILPR: ilpr = value & 0xFFU; return;
        case OFFSET_UARTIBRD: ibrd = value & 0xFFFFU; return;
        case OFFSET_UARTFBRD: fbrd = value & 0x3FU; return;

        case OFFSET_UARTLCR_H: {
            const bool was_fen = llarm::util::bit_fetch(lcr_h, UARTLCR_H_BIT_FEN);

            lcr_h = value & 0xFFU;

            if (was_fen && !llarm::util::bit_fetch(lcr_h, UARTLCR_H_BIT_FEN)) {
                // FIFOs disabled: flush both
                while (!tx_fifo.empty()) { tx_fifo.pop(); }
                while (!rx_fifo.empty()) { rx_fifo.pop(); }
            }

            update_tx_interrupt();
            update_rx_interrupt();
            return;
        }

        case OFFSET_UARTCR: {
            cr = value & 0xFFFFU;
            update_tx_interrupt();
            update_rx_interrupt();
            return;
        }

        case OFFSET_UARTIFLS: {
            ifls = value & 0x3FU;
            update_tx_interrupt();
            update_rx_interrupt();
            return;
        }

        case OFFSET_UARTIMSC: imsc = value & 0x7FFU; return;
        case OFFSET_UARTRIS: return; // read-only
        case OFFSET_UARTMIS: return; // read-only

        case OFFSET_UARTICR:
            ris &= ~(value & 0x7FFU);
            return;

        case OFFSET_UARTDMACR: dmacr = value & 0x7U; return;

        default: return;
    }
}


void UART::receive(const u8 data, const u8 error_flags) {
    const bool fifo_enabled = llarm::util::bit_fetch(lcr_h, UARTLCR_H_BIT_FEN);
    const auto rx_max = static_cast<u8>(fifo_enabled ? RX_FIFO_DEPTH : 1U);

    if (static_cast<u8>(rx_fifo.size()) >= rx_max) {
        // overrun: set OE in RSR and assert overrun interrupt
        llarm::util::modify_bit(rsr, UARTRSR_BIT_OE, true);
        llarm::util::modify_bit(ris, UART_INT_OE, true);
        return;
    }

    const auto entry = static_cast<u16>(((error_flags & 0xFU) << 8U) | data);
    rx_fifo.push(entry);
    update_rx_interrupt();
}


bool UART::transmit(u8& data) {
    if (tx_fifo.empty()) {
        return false;
    }

    data = tx_fifo.front();
    tx_fifo.pop();
    update_tx_interrupt();

    return true;
}