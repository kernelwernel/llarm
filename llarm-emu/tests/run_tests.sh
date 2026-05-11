#!/usr/bin/env bash
set -uo pipefail

EMULATOR=${1:?usage: run_tests.sh <path-to-llarm-emu>}
TESTS_DIR="$(cd "$(dirname "$0")" && pwd)"
TIMEOUT=10

PASS=0
FAIL=0

RED='\033[0;31m'
GRN='\033[0;32m'
RST='\033[0m'

run_test() {
    local name="$1"
    local dir="$TESTS_DIR/$2"
    local binary="$3"
    local expected="$4"

    printf "  %-52s" "$name"

    if ! make -C "$dir" --silent 2>/dev/null; then
        printf "${RED}FAIL${RST} (assembly error)\n"
        ((FAIL++))
        return
    fi

    local actual
    if ! actual=$(timeout "$TIMEOUT" "$EMULATOR" "$dir/$binary" 2>/dev/null); then
        local rc=$?
        if [ "$rc" -eq 124 ]; then
            printf "${RED}FAIL${RST} (timeout after ${TIMEOUT}s)\n"
        else
            printf "${RED}FAIL${RST} (emulator exited with code $rc)\n"
        fi
        ((FAIL++))
        return
    fi

    if [ "$actual" = "$expected" ]; then
        printf "${GRN}PASS${RST}\n"
        ((PASS++))
    else
        printf "${RED}FAIL${RST} (output mismatch)\n"
        printf "    expected: %s\n" "$expected"
        printf "    actual:   %s\n" "$actual"
        ((FAIL++))
    fi
}

echo "llarm-emu integration tests"
echo "==========================="

# peripherals
run_test "uart: basic TX output" \
    "peripherals/uart" \
    "uart_test.bin" \
    "If you can read this, the UART emulation worked."

run_test "timer: SP804 periodic IRQ" \
    "peripherals/timer" \
    "timer_test.bin" \
    "Timer IRQ fired."

echo ""
echo "Results: ${PASS} passed, ${FAIL} failed"
[ "$FAIL" -eq 0 ]
