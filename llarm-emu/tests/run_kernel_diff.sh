#!/usr/bin/env bash
# Builds llarm-difftest (if needed) and runs it against a Linux kernel Image,
# comparing every instruction step's register/memory state between llarm-emu
# and Unicorn (QEMU's ARM926EJ-S core) looking for divergence.
set -uo pipefail

TESTS_DIR="$(cd "$(dirname "$0")" && pwd)"
DIFF_DIR="$TESTS_DIR/diff"
BUILD_DIR="$DIFF_DIR/build"
REPO_ROOT="$(cd "$TESTS_DIR/../.." && pwd)"
MAIN_BUILD_DIR="$REPO_ROOT/build"

DEFAULT_KERNEL_IMAGE="/home/kernel/rep/linux/linux-6.6.138/arch/arm/boot/Image"
KERNEL_IMAGE="${1:-$DEFAULT_KERNEL_IMAGE}"
VERBOSE="${VERBOSE:-0}"
TIMEOUT="${TIMEOUT:-300}"
# rebuild+install llarm-emu and link the difftest against that installed copy,
# instead of llarm-difftest embedding its own separate build of the library
USE_INSTALLED_LLARM_EMU="${USE_INSTALLED_LLARM_EMU:-1}"
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

echo "llarm-emu vs unicorn kernel divergence test"
echo "============================================"
echo "kernel image: $KERNEL_IMAGE"

CMAKE_EXTRA_ARGS=()

if [ "$USE_INSTALLED_LLARM_EMU" = "1" ]; then
    echo "configuring main llarm build (${BUILD_TYPE})..."
    cmake -S "$REPO_ROOT" -B "$MAIN_BUILD_DIR" -DCMAKE_BUILD_TYPE="$BUILD_TYPE" >/dev/null

    echo "recompiling llarm-emu..."
    if ! cmake --build "$MAIN_BUILD_DIR" --target llarm-emu-lib llarm-emu-bin --parallel >/tmp/llarm-emu-build.log 2>&1; then
        echo -e "${RED}FAIL${RESET} (llarm-emu build error), see /tmp/llarm-emu-build.log"
        exit 1
    fi

    find "$MAIN_BUILD_DIR" -maxdepth 2 \( -name 'libllarm-emu.so' -o -name 'llarm-emu' \) -exec touch {} +

    # Only the install step needs elevated privileges (writing into /usr/local).
    # Run this script as your normal user - it escalates just this one command.
    echo "installing llarm-emu..."
    if cmake --install "$MAIN_BUILD_DIR" >/tmp/llarm-emu-install.log 2>&1; then
        :
    elif command -v sudo >/dev/null 2>&1 && sudo cmake --install "$MAIN_BUILD_DIR" >/tmp/llarm-emu-install.log 2>&1; then
        :
    elif command -v doas >/dev/null 2>&1 && doas cmake --install "$MAIN_BUILD_DIR" >/tmp/llarm-emu-install.log 2>&1; then
        :
    else
        echo -e "${RED}FAIL${RESET} (llarm-emu install error), see /tmp/llarm-emu-install.log"
        exit 1
    fi

    # Verify the copy actually landed (belt-and-braces: the mtime tie above could in
    # principle recur, or an unprivileged install silently no-op instead of failing).
    # Note: a byte-for-byte compare against the build-tree .so would false-positive
    # here, since cmake rewrites the installed copy's RPATH in place on install.
    if ! grep -q "^-- Installing: .*libllarm-emu\.so$" /tmp/llarm-emu-install.log; then
        echo -e "${RED}FAIL${RESET}: libllarm-emu.so was not (re)installed, see /tmp/llarm-emu-install.log"
        exit 1
    fi

    CMAKE_EXTRA_ARGS+=("-DLLARM_USE_SYSTEM_PACKAGES=ON")
fi

echo "configuring llarm-difftest build (${BUILD_TYPE})..."
cmake -S "$DIFF_DIR" -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE="$BUILD_TYPE" "${CMAKE_EXTRA_ARGS[@]}" >/dev/null

echo "building llarm-difftest..."
if ! cmake --build "$BUILD_DIR" --parallel >/tmp/llarm-difftest-build.log 2>&1; then
    echo -e "${RED}FAIL${RESET} (build error), see /tmp/llarm-difftest-build.log"
    exit 1
fi

DIFFTEST_BIN="$BUILD_DIR/llarm-difftest"
if [ ! -x "$DIFFTEST_BIN" ]; then
    echo -e "${RED}error${RESET}: llarm-difftest binary missing after build (is unicorn installed?)"
    exit 1
fi

DIFFTEST_ARGS=()
[ "$VERBOSE" = "1" ] && DIFFTEST_ARGS+=("-v")
DIFFTEST_ARGS+=("$KERNEL_IMAGE")

LOG_FILE="$(mktemp)"
echo "running (timeout ${TIMEOUT}s)..."

timeout "$TIMEOUT" "$DIFFTEST_BIN" "${DIFFTEST_ARGS[@]}" 2>&1 | tee "$LOG_FILE"
RC="${PIPESTATUS[0]}"

echo ""
if [ "$RC" -eq 124 ]; then
    echo -e "${YELLOW}TIMEOUT${RESET} after ${TIMEOUT}s with no divergence detected (this can be normal for long kernel boots)"
    echo "last state:"
    tail -n 20 "$LOG_FILE"
    rm -f "$LOG_FILE"
    exit 0
elif grep -q "DIVERGENCE" "$LOG_FILE"; then
    rm -f "$LOG_FILE"
    exit 1
elif [ "$RC" -ne 0 ]; then
    echo -e "${RED}FAIL${RESET} (exit code $RC)"
    rm -f "$LOG_FILE"
    exit "$RC"
else
    echo -e "${GREEN}PASS${RESET} (no divergence found)"
    rm -f "$LOG_FILE"
    exit 0
fi