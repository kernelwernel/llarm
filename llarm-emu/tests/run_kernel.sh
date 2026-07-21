#!/usr/bin/env bash
# Builds llarm-uart (if needed) and runs a Linux kernel Image on it standalone,
# with no Unicorn/comparison involved - just LLARM executing the kernel boot
# with UART output enabled.
set -uo pipefail

TESTS_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="$TESTS_DIR/build"

DEFAULT_KERNEL_IMAGE="/home/kernel/rep/linux/linux-6.6.138/arch/arm/boot/Image"
DEFAULT_INITRD_IMAGE="$TESTS_DIR/../kernels/busybox-rootfs.cpio"
KERNEL_IMAGE="${1:-$DEFAULT_KERNEL_IMAGE}"
INITRD_IMAGE="${2:-$DEFAULT_INITRD_IMAGE}"
TIMEOUT="${TIMEOUT:-300}"
BUILD_TYPE="${BUILD_TYPE:-Release}"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
RESET='\033[0m'

if [ ! -f "$KERNEL_IMAGE" ]; then
    echo "error: kernel image not found at $KERNEL_IMAGE"
    echo "usage: $(basename "$0") [path-to-uncompressed-kernel-Image] [path-to-initrd-cpio]"
    exit 1
fi

if [ -n "$INITRD_IMAGE" ] && [ ! -f "$INITRD_IMAGE" ]; then
    if [ "$INITRD_IMAGE" = "$DEFAULT_INITRD_IMAGE" ]; then
        echo "note: default initrd not found at $INITRD_IMAGE, booting without one"
        INITRD_IMAGE=""
    else
        echo "error: initrd image not found at $INITRD_IMAGE"
        exit 1
    fi
fi

echo "llarm-uart standalone kernel run"
echo "==============================="
echo "kernel image: $KERNEL_IMAGE"
if [ -n "$INITRD_IMAGE" ]; then
    echo "initrd image: $INITRD_IMAGE"
fi

echo "configuring tests project (${BUILD_TYPE})..."
cmake -S "$TESTS_DIR" -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE="$BUILD_TYPE" >/dev/null

echo "building llarm-uart..."
cmake --build "$BUILD_DIR" --target llarm-uart --parallel 2>&1 | tee /tmp/llarm-emu-build.log
BUILD_RC="${PIPESTATUS[0]}"
if [ "$BUILD_RC" -ne 0 ]; then
    echo -e "${RED}FAIL${RESET} (llarm-uart build error), see /tmp/llarm-emu-build.log"
    exit 1
fi

EMU_BIN="$BUILD_DIR/llarm-uart"
if [ ! -x "$EMU_BIN" ]; then
    echo -e "${RED}error${RESET}: llarm-uart binary missing after build"
    exit 1
fi

LOG_FILE="$(mktemp)"
echo "running (timeout ${TIMEOUT}s)..."

timeout --foreground "$TIMEOUT" "$EMU_BIN" "$KERNEL_IMAGE" $INITRD_IMAGE 2>&1 | tee "$LOG_FILE"
RC="${PIPESTATUS[0]}"

echo ""
if [ "$RC" -eq 124 ]; then
    echo -e "${YELLOW}TIMEOUT${RESET} after ${TIMEOUT}s (this can be normal for long/hanging kernel boots)"
    echo "last state:"
    tail -n 20 "$LOG_FILE"
    rm -f "$LOG_FILE"
    exit 0
elif [ "$RC" -ne 0 ]; then
    echo -e "${RED}FAIL${RESET} (exit code $RC)"
    rm -f "$LOG_FILE"
    exit "$RC"
else
    echo -e "${GREEN}DONE${RESET} (llarm-uart exited cleanly)"
    rm -f "$LOG_FILE"
    exit 0
fi
