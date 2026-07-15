#!/usr/bin/env bash
# Builds (via the tests/ CMake project) and runs llarm-uart against a kernel image,
# for early-boot visibility debugging (see the comment at the top of llarm-uart.cpp).
set -uo pipefail

DEBUG_DIR="$(cd "$(dirname "$0")" && pwd)"
TESTS_DIR="$(cd "$DEBUG_DIR/.." && pwd)"
BUILD_DIR="$TESTS_DIR/build"

DEFAULT_KERNEL_IMAGE="/home/kernel/rep/linux/linux-6.6.138/arch/arm/boot/Image"
KERNEL_IMAGE="${1:-$DEFAULT_KERNEL_IMAGE}"
MAX_STEPS="${2:-6000000}"

if [ ! -f "$KERNEL_IMAGE" ]; then
    echo "error: kernel image not found at $KERNEL_IMAGE"
    echo "usage: $(basename "$0") [path-to-kernel-Image] [max_steps]"
    exit 1
fi

echo "configuring tests project..."
cmake -S "$TESTS_DIR" -B "$BUILD_DIR" >/dev/null

echo "building llarm-uart..."
if ! cmake --build "$BUILD_DIR" --target llarm-uart --parallel; then
    echo "error: llarm-uart build failed"
    exit 1
fi

BIN="$BUILD_DIR/llarm-uart"
if [ ! -x "$BIN" ]; then
    echo "error: llarm-uart binary missing after build"
    exit 1
fi

echo "running against $KERNEL_IMAGE (max_steps=$MAX_STEPS)..."
"$BIN" "$KERNEL_IMAGE" "$MAX_STEPS"
