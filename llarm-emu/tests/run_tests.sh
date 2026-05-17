#!/usr/bin/env bash
set -uo pipefail

TESTS_DIR="$(cd "$(dirname "$0")" && pwd)"
EMULATOR="${1:-$TESTS_DIR/../build/llarm-emu}"

if [ ! -x "$EMULATOR" ]; then
    echo "error: emulator not found at $EMULATOR"
    echo "usage: run_tests.sh [path-to-llarm-emu]"
    exit 1
fi
TIMEOUT=10

PASS=0
FAIL=0

RED='\033[0;31m'
GREEN='\033[0;32m'
RESET='\033[0m'

# run_test <name> <build_dir_rel> <binary_rel> <expected_stdout>
# build_dir_rel: relative to TESTS_DIR, where `make` is run
# binary_rel: relative to TESTS_DIR, path to the binary
run_test() {
    local name="$1"
    local build_dir="$TESTS_DIR/$2"
    local binary="$TESTS_DIR/$3"
    local expected="$4"

    printf "  %-36s" "$name"

    if ! make -C "$build_dir" --silent 2>/dev/null; then
        printf "${RED}FAIL${RESET} (build error)\n"
        ((FAIL++))
        return
    fi

    local actual stderr_out rc tmp_stderr
    tmp_stderr=$(mktemp)
    actual=$(timeout "$TIMEOUT" "$EMULATOR" "$binary" 2>"$tmp_stderr")
    rc=$?
    stderr_out=$(cat "$tmp_stderr")
    rm -f "$tmp_stderr"

    if [ "$rc" -eq 124 ]; then
        printf "${RED}FAIL${RESET} (timeout after ${TIMEOUT}s)\n"
        [ -n "$actual" ]     && printf "    stdout: %s\n" "$actual"
        [ -n "$stderr_out" ] && printf "    stderr: %s\n" "$stderr_out"
        ((FAIL++))
        return
    elif [ "$rc" -ne 0 ]; then
        printf "${RED}FAIL${RESET} (exit code $rc)\n"
        [ -n "$actual" ]     && printf "    stdout: %s\n" "$actual"
        [ -n "$stderr_out" ] && printf "    stderr: %s\n" "$stderr_out"
        ((FAIL++))
        return
    fi

    if [ "$actual" = "$expected" ]; then
        printf "${GREEN}PASS${RESET}\n"
        ((PASS++))
    else
        printf "${RED}FAIL${RESET} (output mismatch)\n"
        printf "    expected: %s\n" "$expected"
        printf "    actual:   %s\n" "$actual"
        [ -n "$stderr_out" ] && printf "    stderr:   %s\n" "$stderr_out"
        ((FAIL++))
    fi
}

section() {
    printf "\n-- %s\n" "$1"
}

echo "llarm-emu integration tests"
echo "==========================="

section "peripherals"
run_test "uart: basic TX output" "peripherals/uart" "peripherals/uart/uart_test.bin" "If you can read this, the UART emulation worked."
run_test "timer: SP804 periodic IRQ" "peripherals/timer" "peripherals/timer/timer_test.bin" "Timer IRQ fired."

section "instructions"
run_test "instructions: math" "instructions" "instructions/math/math_test.bin" ""
run_test "instructions: logic" "instructions" "instructions/logic/logic_test.bin" ""
run_test "instructions: movement" "instructions" "instructions/movement/movement_test.bin" ""
run_test "instructions: multiply" "instructions" "instructions/multiply/multiply_test.bin" ""
run_test "instructions: branching" "instructions" "instructions/branching/branching_test.bin" ""
run_test "instructions: load/store" "instructions" "instructions/load_store/load_store_test.bin" ""
run_test "instructions: misc" "instructions" "instructions/misc/misc_test.bin" ""
run_test "instructions: DSP" "instructions" "instructions/dsp/dsp_test.bin" ""
run_test "instructions: VFP" "instructions" "instructions/vfp/vfp_test.bin" ""

section "algorithms"
run_test "algorithms: bubble sort" "algorithms" "algorithms/bubble_sort/bubble_sort.bin" ""
run_test "algorithms: factorial" "algorithms" "algorithms/factorial/factorial.bin" ""
run_test "algorithms: is prime" "algorithms" "algorithms/is_prime/is_prime.bin" ""
run_test "algorithms: sum array" "algorithms" "algorithms/sum_array/sum_array.bin" ""
run_test "algorithms: fibonacci (Thumb)" "algorithms" "algorithms/thumb/fibonacci/fib_thumb.bin" ""

echo ""
echo "Results: ${PASS} passed, ${FAIL} failed"
[ "$FAIL" -eq 0 ]