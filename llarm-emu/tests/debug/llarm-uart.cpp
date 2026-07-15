// this is basically the same as run_kernel.sh in the previous directory,
// but this program is specifically meant to enable the UARTEN bit to 
// produce kernel log outputs to stdout. That's basically it.

#include <llarm/llarm-emu.hpp>
#include "src/settings.hpp"

#include <cstdio>
#include <cstdlib>

static void wait_for_execution(llarm::emu::cpu_blockstep& emu) {
    emu.wait_for_execution();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <kernel-image> [max_steps]\n", argv[0]);
        return 1;
    }

    const u32 max_steps = (argc >= 3) ? static_cast<u32>(atol(argv[2])) : 6000000U;

    const SETTINGS settings = image_settings();
    llarm::emu::cpu_blockstep emu(argv[1], settings);

    emu.run();
    while (!emu.cpu.core.execution_done.load(std::memory_order_acquire)) {}

    // UARTCR: UARTEN (bit 0) + TXE (bit 8) + RXE (bit 9) - see uart.hpp's OFFSET_UARTCR
    emu.write_physical_mem<u32>(settings.uart_base + 0x030, 0x301);

    for (u32 step = 0; step < max_steps; step++) {
        emu.next_instruction();
        wait_for_execution(emu);
    }

    fprintf(stderr, "\ndone\n");
    return 0;
}
