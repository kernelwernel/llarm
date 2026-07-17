// this is basically the same as run_kernel.sh in the previous directory,
// but this program is specifically meant to enable the UARTEN bit to
// produce kernel log outputs to stdout. 

#include <llarm/llarm-emu.hpp>
#include "src/settings.hpp"

#include <cstdio>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <kernel-image>\n", argv[0]);
        return 1;
    }

    std::setvbuf(stdout, nullptr, _IOLBF, 0);

    const SETTINGS settings = image_settings();
    llarm::emu::cpu_headless emu(argv[1], settings);

    // UARTCR: UARTEN (bit 0) + TXE (bit 8) + RXE (bit 9), see uart.hpp's OFFSET_UARTCR
    emu.write_physical_mem<u32>(settings.uart_base + 0x030, 0x301);

    emu.run();

    return 0;
}
