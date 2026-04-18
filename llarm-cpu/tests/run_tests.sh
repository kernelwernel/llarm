#!/usr/bin/env bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
OUT="$SCRIPT_DIR/test_arm"

# Two execution modes:
#
#   MODE 1 => Linux user-mode (preferred, needs arm-linux-gnueabi cross-compiler)
#     Compiler : arm-linux-gnueabi-g++ / arm-linux-gnueabihf-g++
#     Runner   : qemu-arm -cpu arm926
#     Install  : yay -S arm-linux-gnueabihf-gcc && sudo pacman -S qemu-user  (Arch)
#              : sudo apt install g++-arm-linux-gnueabi qemu-user            (Debian/Ubuntu)
#
#   MODE 2 => Bare-metal semihosting (no newlib, works with arm-none-eabi-g++ as shipped)
#     Compiler : arm-none-eabi-g++ -nostdlib, startup.S provides _start + semihosting exit
#     Runner   : qemu-system-arm -M versatilepb (ARM926EJ-S) with semihosting
#     Install  : sudo pacman -S qemu-system-arm  (Arch, already installed if you have qemu)

CXXFLAGS="-march=armv5te -mfloat-abi=soft -DLLARM_CPU_TEST_MIDR -Wall -Wextra"

# MODE 1:

ARM_CXX_LINUX=""
for candidate in arm-linux-gnueabi-g++ arm-linux-gnueabihf-g++; do
    if command -v "$candidate" &>/dev/null; then
        ARM_CXX_LINUX="$candidate"
        break
    fi
done

if [ -n "$ARM_CXX_LINUX" ] && command -v qemu-arm &>/dev/null; then
    echo "Mode     : Linux user-mode (qemu-arm)"
    echo "Compiler : $ARM_CXX_LINUX"
    echo "Building : $OUT"

    # shellcheck disable=SC2086
    "$ARM_CXX_LINUX" $CXXFLAGS -o "$OUT" "$SCRIPT_DIR/test_main.cpp"
    echo "Built OK"
    echo ""
    echo "Running  : qemu-arm -cpu arm926 $OUT"
    echo ""
    qemu-arm -cpu arm926 "$OUT"
    EXIT_CODE=$?

# MODE 2 FALLBACK:

elif command -v arm-none-eabi-g++ &>/dev/null && command -v qemu-system-arm &>/dev/null; then
    echo "Mode     : bare-metal semihosting (qemu-system-arm versatilepb / ARM926EJ-S)"
    echo "Compiler : arm-none-eabi-g++ (no newlib required)"

    OUT="$OUT.elf"
    echo "Building : $OUT"

    # startup.S provides _start (sets SP, calls main, does semihosting SYS_EXIT)
    # test_main.cpp uses SYS_WRITE0 semihosting directly instead of printf
    # -ffreestanding: use GCC's own stdint.h without needing newlib headers
    # shellcheck disable=SC2086
    arm-none-eabi-g++ $CXXFLAGS \
        -ffreestanding -nostdlib -nostartfiles \
        -o "$OUT" \
        "$SCRIPT_DIR/startup.S" \
        "$SCRIPT_DIR/test_main.cpp"

    echo "Built OK"
    echo ""
    echo "Running  : qemu-system-arm -M versatilepb -cpu arm926 -semihosting-config enable=on -kernel $OUT -nographic"
    echo ""
    # qemu-system-arm always exits 1 (its own status, not the guest's),
    # so derive pass/fail from whether "FAILED" appears in the test output.
    # QEMU semihosting output (SYS_WRITE0) goes to stderr, not stdout
    OUTPUT=$(qemu-system-arm \
        -M versatilepb \
        -cpu arm926 \
        -semihosting-config enable=on,target=native \
        -kernel "$OUT" \
        -nographic \
        -monitor none \
        2>&1 >/dev/null | grep -v "^pulseaudio:")
    echo "$OUTPUT"
    if echo "$OUTPUT" | grep -q "FAILED"; then
        EXIT_CODE=1
    else
        EXIT_CODE=0
    fi

else
    echo "ERROR: no usable ARM toolchain+runner found."
    echo ""
    echo "Option A — Linux user-mode:"
    echo "  Arch:          yay -S arm-linux-gnueabihf-gcc && sudo pacman -S qemu-user"
    echo "  Debian/Ubuntu: sudo apt install g++-arm-linux-gnueabi qemu-user"
    echo ""
    echo "Option B — bare-metal semihosting (arm-none-eabi-g++ is already enough):"
    echo "  sudo pacman -S qemu-system-arm  (Arch)"
    echo "  sudo apt install qemu-system-arm (Debian/Ubuntu)"
    exit 1
fi

echo ""
if [ $EXIT_CODE -eq 0 ]; then
    echo "All tests passed."
else
    echo "Tests FAILED (exit code $EXIT_CODE)."
fi

exit $EXIT_CODE
