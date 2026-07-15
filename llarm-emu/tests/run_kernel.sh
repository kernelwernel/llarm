#!/usr/bin/env bash
# Builds llarm-emu (if needed) and runs a Linux kernel Image on it standalone,
# with no Unicorn/comparison involved - just LLARM executing the kernel boot.
set -uo pipefail

TESTS_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$(cd "$TESTS_DIR/../.." && pwd)"
BUILD_DIR="$REPO_ROOT/build"

DEFAULT_KERNEL_IMAGE="/home/kernel/rep/linux/linux-6.6.138/arch/arm/boot/Image"
KERNEL_IMAGE="${1:-$DEFAULT_KERNEL_IMAGE}"
VERBOSE="${VERBOSE:-0}"
TIMEOUT="${TIMEOUT:-300}"
BUILD_TYPE="${BUILD_TYPE:-Release}"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
RESET='\033[0m'

if [ ! -f "$KERNEL_IMAGE" ]; then
    echo "error: kernel image not found at $KERNEL_IMAGE"
    echo "usage: $(basename "$0") [path-to-uncompressed-kernel-Image]"
    exit 1
fi

echo "llarm-emu standalone kernel run"
echo "==============================="
echo "kernel image: $KERNEL_IMAGE"

echo "configuring main llarm build (${BUILD_TYPE})..."
cmake -S "$REPO_ROOT" -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE="$BUILD_TYPE" >/dev/null

echo "building llarm-emu..."
if ! cmake --build "$BUILD_DIR" --target llarm-emu-lib llarm-emu-bin --parallel >/tmp/llarm-emu-build.log 2>&1; then
    echo -e "${RED}FAIL${RESET} (llarm-emu build error), see /tmp/llarm-emu-build.log"
    exit 1
fi

EMU_BIN="$BUILD_DIR/llarm-emu/llarm-emu"
if [ ! -x "$EMU_BIN" ]; then
    echo -e "${RED}error${RESET}: llarm-emu binary missing after build"
    exit 1
fi

EMU_ARGS=(--run --linux)
[ "$VERBOSE" = "1" ] && EMU_ARGS+=(--verbose)
EMU_ARGS+=("$KERNEL_IMAGE")

LOG_FILE="$(mktemp)"
echo "running (timeout ${TIMEOUT}s)..."

timeout "$TIMEOUT" "$EMU_BIN" "${EMU_ARGS[@]}" 2>&1 | tee "$LOG_FILE"
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
    echo -e "${GREEN}DONE${RESET} (llarm-emu exited cleanly)"
    rm -f "$LOG_FILE"
    exit 0
fi
