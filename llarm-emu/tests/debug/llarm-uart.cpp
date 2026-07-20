// this is basically the same as run_kernel.sh in the previous directory,
// but this program is specifically meant to enable the UARTEN bit to
// produce kernel log outputs to stdout.

#include <llarm/llarm-emu.hpp>
#include "src/settings.hpp"

#include <atomic>
#include <cstdio>
#include <thread>

#if defined(__unix__) || defined(__APPLE__)
    #define LLARM_UART_HAS_RAW_TTY 1
    #include <termios.h>
    #include <unistd.h>
#else
    #define LLARM_UART_HAS_RAW_TTY 0
#endif


#if LLARM_UART_HAS_RAW_TTY
struct raw_tty_guard {
    termios original {};
    bool is_active = false;

    raw_tty_guard() {
        if (isatty(STDIN_FILENO) == 0) {
            return;
        }

        if (tcgetattr(STDIN_FILENO, &original) != 0) {
            return;
        }

        termios raw = original;
        cfmakeraw(&raw);

        if (tcsetattr(STDIN_FILENO, TCSANOW, &raw) == 0) {
            is_active = true;
        }
    }

    ~raw_tty_guard() {
        if (is_active) {
            tcsetattr(STDIN_FILENO, TCSANOW, &original);
        }
    }

    raw_tty_guard(const raw_tty_guard&) = delete;
    raw_tty_guard& operator=(const raw_tty_guard&) = delete;

    raw_tty_guard(raw_tty_guard&& other) noexcept : original(other.original), is_active(other.is_active) {
        other.is_active = false;
    }

    raw_tty_guard& operator=(raw_tty_guard&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        if (is_active) {
            tcsetattr(STDIN_FILENO, TCSANOW, &original);
        }

        original = other.original;
        is_active = other.is_active;
        other.is_active = false;

        return *this;
    }
};
#endif


int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <kernel-image> [initrd-cpio]\n", argv[0]);
        return 1;
    }

    std::setvbuf(stdout, nullptr, _IOLBF, 0);

    const SETTINGS settings = image_settings();
    llarm::emu::cpu_headless emu(argv[1], settings);

    // UARTCR: UARTEN (bit 0) + TXE (bit 8) + RXE (bit 9), see uart.hpp's OFFSET_UARTCR
    emu.write_physical_mem<u32>(settings.uart_base + 0x030, 0x301);

    if (argc >= 3) {
        emu.load_initrd(argv[2]);
    }

#if LLARM_UART_HAS_RAW_TTY
    const raw_tty_guard tty_guard;

    std::atomic<bool> stop_reader = false;

    std::thread stdin_reader([&emu, &stop_reader] {
        int byte = 0;

        while (!stop_reader.load(std::memory_order_relaxed) && (byte = std::getchar()) != EOF) {
            emu.cpu.uart.push_host_input(static_cast<u8>(byte));
        }
    });

    emu.run();

    stop_reader.store(true, std::memory_order_relaxed);
    stdin_reader.detach();
#else
    emu.run();
#endif

    return 0;
}
