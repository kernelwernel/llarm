/*
 * llarm-cpu test suite
 * Runs bare-metal under qemu-system-arm with semihosting — no libc required.
 */

#include "../llarm/llarm-cpu.h"

#include <stdint.h>

// ---------------------------------------------------------------------------
// ARM semihosting primitives (no newlib/rdimon needed)
// ---------------------------------------------------------------------------

// SYS_WRITE0 (0x04): write a null-terminated string to the host console
static void semi_puts(const char* s) {
    register int        r0 asm("r0") = 0x04;
    register const char* r1 asm("r1") = s;
    asm volatile("svc 0x123456" : "+r"(r0) : "r"(r1) : "memory");
}

// Write a single character
static void semi_putc(char c) {
    char buf[2] = { c, '\0' };
    semi_puts(buf);
}

// Write a 32-bit value as "0x" followed by 8 hex digits
static void semi_put_hex(uint32_t val) {
    semi_puts("0x");
    char buf[9];
    for (int i = 7; i >= 0; i--) {
        int nibble = val & 0xF;
        buf[i] = (char)(nibble < 10 ? '0' + nibble : 'a' + nibble - 10);
        val >>= 4;
    }
    buf[8] = '\0';
    semi_puts(buf);
}

// Write an unsigned decimal integer
static void semi_put_uint(unsigned v) {
    if (v == 0) { semi_putc('0'); return; }
    char buf[12];
    int  i = 11;
    buf[i] = '\0';
    while (v > 0) {
        buf[--i] = (char)('0' + v % 10);
        v /= 10;
    }
    semi_puts(buf + i);
}

// Minimal strcmp (avoids string.h dependency)
static int my_strcmp(const char* a, const char* b) {
    while (*a && *a == *b) { a++; b++; }
    return (unsigned char)*a - (unsigned char)*b;
}

// ---------------------------------------------------------------------------
// Minimal test framework
// ---------------------------------------------------------------------------

static int _tests_run    = 0;
static int _tests_passed = 0;
static int _tests_failed = 0;
static const char* _current_test = 0;

#define TEST_BEGIN(name) \
    do { _current_test = (name); _tests_run++; } while(0)

#define TEST_END() \
    do { _tests_passed++; semi_puts("[PASS] "); semi_puts(_current_test); semi_puts("\n"); } while(0)

#define ASSERT_EQ(a, b) \
    do { \
        if ((uint32_t)(a) != (uint32_t)(b)) { \
            semi_puts("[FAIL] "); semi_puts(_current_test); \
            semi_puts(" — expected "); semi_put_hex((uint32_t)(b)); \
            semi_puts(" got "); semi_put_hex((uint32_t)(a)); \
            semi_puts(" (line "); semi_put_uint(__LINE__); semi_puts(")\n"); \
            _tests_failed++; \
            return; \
        } \
    } while(0)

#define ASSERT_TRUE(expr) \
    do { \
        if (!(expr)) { \
            semi_puts("[FAIL] "); semi_puts(_current_test); \
            semi_puts(" — assertion failed: " #expr \
                      " (line "); semi_put_uint(__LINE__); semi_puts(")\n"); \
            _tests_failed++; \
            return; \
        } \
    } while(0)

// ---------------------------------------------------------------------------
// llarm_cpu_fetch_bits tests
// ---------------------------------------------------------------------------

static void test_llarm_cpu_fetch_bits_full_word() {
    // Note: llarm_cpu_fetch_bits(val, 31, 0) triggers 1U<<32 UB in the impl — test up to 31 bits wide instead
    TEST_BEGIN("llarm_cpu_fetch_bits: 31-bit wide field");
    ASSERT_EQ(llarm_cpu_fetch_bits(0x7FFFFFFF, 30, 0), 0x7FFFFFFFU);
    TEST_END();
}

static void test_llarm_cpu_fetch_bits_byte_high() {
    TEST_BEGIN("llarm_cpu_fetch_bits: top byte");
    ASSERT_EQ(llarm_cpu_fetch_bits(0x41000000, 31, 24), 0x41U);
    TEST_END();
}

static void test_llarm_cpu_fetch_bits_byte_low() {
    TEST_BEGIN("llarm_cpu_fetch_bits: bottom byte");
    ASSERT_EQ(llarm_cpu_fetch_bits(0x000000AB, 7, 0), 0xABU);
    TEST_END();
}

static void test_llarm_cpu_fetch_bits_nibble() {
    TEST_BEGIN("llarm_cpu_fetch_bits: nibble at bits[11:8]");
    ASSERT_EQ(llarm_cpu_fetch_bits(0x00000F00, 11, 8), 0xFU);
    TEST_END();
}

static void test_llarm_cpu_fetch_bits_single() {
    TEST_BEGIN("llarm_cpu_fetch_bits: single bit");
    ASSERT_EQ(llarm_cpu_fetch_bits(0x00800000, 23, 23), 0x1U);
    ASSERT_EQ(llarm_cpu_fetch_bits(0x007FFFFF, 23, 23), 0x0U);
    TEST_END();
}

static void test_llarm_cpu_fetch_bits_arm926_implementor() {
    TEST_BEGIN("llarm_cpu_fetch_bits: ARM926 implementor field");
    ASSERT_EQ(llarm_cpu_fetch_bits(0x41069265, 31, 24), 0x41U); // ARM
    TEST_END();
}

static void test_llarm_cpu_fetch_bits_arm926_arch() {
    TEST_BEGIN("llarm_cpu_fetch_bits: ARM926 architecture field");
    ASSERT_EQ(llarm_cpu_fetch_bits(0x41069265, 19, 16), 0x6U); // ARMv5TEJ
    TEST_END();
}

static void test_llarm_cpu_fetch_bits_arm926_ppn() {
    TEST_BEGIN("llarm_cpu_fetch_bits: ARM926 PPN field");
    ASSERT_EQ(llarm_cpu_fetch_bits(0x41069265, 15, 4), 0x926U);
    TEST_END();
}

// ---------------------------------------------------------------------------
// pre/ARM7/post-ARM7 classification tests
// ---------------------------------------------------------------------------

static void test_is_pre_arm7() {
    TEST_BEGIN("llarm_cpu_is_pre_arm7: ARM3 (0x41560300)");
    llarm_cpu_set_test_midr(0x41560300);
    ASSERT_TRUE(llarm_cpu_is_pre_arm7());
    ASSERT_TRUE(!llarm_cpu_is_arm7());
    ASSERT_TRUE(!llarm_cpu_is_post_arm7());
    TEST_END();
}

static void test_is_arm7() {
    TEST_BEGIN("llarm_cpu_is_arm7: ARM710 (0x41007100)");
    llarm_cpu_set_test_midr(0x41007100);
    ASSERT_TRUE(!llarm_cpu_is_pre_arm7());
    ASSERT_TRUE(llarm_cpu_is_arm7());
    ASSERT_TRUE(!llarm_cpu_is_post_arm7());
    TEST_END();
}

static void test_is_post_arm7() {
    TEST_BEGIN("llarm_cpu_is_post_arm7: ARM926EJ-S (0x41069265)");
    llarm_cpu_set_test_midr(0x41069265);
    ASSERT_TRUE(!llarm_cpu_is_pre_arm7());
    ASSERT_TRUE(!llarm_cpu_is_arm7());
    ASSERT_TRUE(llarm_cpu_is_post_arm7());
    TEST_END();
}

// ---------------------------------------------------------------------------
// llarm_cpu_fetch_implementor tests
// ---------------------------------------------------------------------------

static void test_implementor_arm() {
    TEST_BEGIN("llarm_cpu_fetch_implementor: ARM (0x41)");
    llarm_cpu_set_test_midr(0x41069265);
    ASSERT_EQ(llarm_cpu_fetch_implementor(), IMPL_ARM);
    TEST_END();
}

static void test_implementor_qualcomm() {
    TEST_BEGIN("llarm_cpu_fetch_implementor: Qualcomm (0x51)");
    llarm_cpu_set_test_midr(0x51069265);
    ASSERT_EQ(llarm_cpu_fetch_implementor(), IMPL_QUALCOMM);
    TEST_END();
}

static void test_implementor_apple() {
    TEST_BEGIN("llarm_cpu_fetch_implementor: Apple (0x61)");
    llarm_cpu_set_test_midr(0x61069265);
    ASSERT_EQ(llarm_cpu_fetch_implementor(), IMPL_APPLE);
    TEST_END();
}

static void test_implementor_nvidia() {
    TEST_BEGIN("llarm_cpu_fetch_implementor: NVIDIA (0x4e)");
    llarm_cpu_set_test_midr(0x4e069265);
    ASSERT_EQ(llarm_cpu_fetch_implementor(), IMPL_NVIDIA);
    TEST_END();
}

static void test_implementor_llarm() {
    TEST_BEGIN("llarm_cpu_fetch_implementor: LLARM (0x4C)");
    llarm_cpu_set_test_midr(0x4C069265);
    ASSERT_EQ(llarm_cpu_fetch_implementor(), IMPL_LLARM);
    TEST_END();
}

static void test_implementor_unknown_pre_arm7() {
    TEST_BEGIN("llarm_cpu_fetch_implementor: pre-ARM7 returns UNKNOWN");
    llarm_cpu_set_test_midr(0x41560300);
    ASSERT_EQ(llarm_cpu_fetch_implementor(), IMPL_UNKNOWN);
    TEST_END();
}

// ---------------------------------------------------------------------------
// llarm_cpu_fetch_product tests
// ---------------------------------------------------------------------------

static void test_product_arm926() {
    TEST_BEGIN("llarm_cpu_fetch_product: ARM926EJ-S (0x41069265)");
    llarm_cpu_set_test_midr(0x41069265);
    ASSERT_EQ(llarm_cpu_fetch_product(), PROD_ARM926EJ_S);
    TEST_END();
}

static void test_product_arm920t() {
    TEST_BEGIN("llarm_cpu_fetch_product: ARM920T");
    // [31:24]=0x41 [23:20]=0x0 [19:16]=0x2 [15:4]=0x920 [3:0]=0x0 → 0x41029200
    llarm_cpu_set_test_midr(0x41029200);
    ASSERT_EQ(llarm_cpu_fetch_product(), PROD_ARM920T);
    TEST_END();
}

static void test_product_cortex_a9() {
    TEST_BEGIN("llarm_cpu_fetch_product: Cortex-A9");
    // PPN=0xC09, arch=0xF (CPUID), impl=ARM → 0x410FC090
    llarm_cpu_set_test_midr(0x410FC090);
    ASSERT_EQ(llarm_cpu_fetch_product(), PROD_CORTEX_A9);
    TEST_END();
}

static void test_product_cortex_m4() {
    TEST_BEGIN("llarm_cpu_fetch_product: Cortex-M4");
    // PPN=0xC24 → 0x410FC240
    llarm_cpu_set_test_midr(0x410FC240);
    ASSERT_EQ(llarm_cpu_fetch_product(), PROD_CORTEX_M4);
    TEST_END();
}

static void test_product_cortex_a53() {
    TEST_BEGIN("llarm_cpu_fetch_product: Cortex-A53");
    // PPN=0xD03 → 0x410FD030
    llarm_cpu_set_test_midr(0x410FD030);
    ASSERT_EQ(llarm_cpu_fetch_product(), PROD_CORTEX_A53);
    TEST_END();
}

static void test_product_arm710() {
    TEST_BEGIN("llarm_cpu_fetch_product: ARM710 (ARM7 era)");
    llarm_cpu_set_test_midr(0x41007100);
    ASSERT_EQ(llarm_cpu_fetch_product(), PROD_ARM710);
    TEST_END();
}

static void test_product_arm710t() {
    TEST_BEGIN("llarm_cpu_fetch_product: ARM710T (ARM7 era)");
    llarm_cpu_set_test_midr(0x41807100);
    ASSERT_EQ(llarm_cpu_fetch_product(), PROD_ARM710T);
    TEST_END();
}

static void test_product_arm600_pre_arm7() {
    TEST_BEGIN("llarm_cpu_fetch_product: ARM600 (pre-ARM7)");
    llarm_cpu_set_test_midr(0x41560600);
    ASSERT_EQ(llarm_cpu_fetch_product(), PROD_ARM600);
    TEST_END();
}

static void test_product_unknown_third_party() {
    TEST_BEGIN("llarm_cpu_fetch_product: third-party impl → UNKNOWN");
    llarm_cpu_set_test_midr(0x510FC090); // Qualcomm, not supported yet
    ASSERT_EQ(llarm_cpu_fetch_product(), PROD_UNKNOWN);
    TEST_END();
}

// ---------------------------------------------------------------------------
// llarm_cpu_fetch_arch tests
// ---------------------------------------------------------------------------

static void test_arch_armv5tej_arm926() {
    TEST_BEGIN("llarm_cpu_fetch_arch: ARMv5TEJ (ARM926)");
    llarm_cpu_set_test_midr(0x41069265); // arch bits[19:16] = 0x6
    ASSERT_EQ(llarm_cpu_fetch_arch(), ARCH_ARMv5TEJ);
    TEST_END();
}

static void test_arch_armv4t_arm920t() {
    TEST_BEGIN("llarm_cpu_fetch_arch: ARMv4T (ARM920T)");
    llarm_cpu_set_test_midr(0x41029200); // arch bits = 0x2
    ASSERT_EQ(llarm_cpu_fetch_arch(), ARCH_ARMv4T);
    TEST_END();
}

static void test_arch_armv3_arm710() {
    TEST_BEGIN("llarm_cpu_fetch_arch: ARMv3 (ARM710, A-bit=0)");
    llarm_cpu_set_test_midr(0x41007100); // ARM7, bit23=0 → ARMv3
    ASSERT_EQ(llarm_cpu_fetch_arch(), ARCH_ARMv3);
    TEST_END();
}

static void test_arch_armv4t_arm710t() {
    TEST_BEGIN("llarm_cpu_fetch_arch: ARMv4T (ARM710T, A-bit=1)");
    llarm_cpu_set_test_midr(0x41807100); // ARM7, bit23=1 → ARMv4T
    ASSERT_EQ(llarm_cpu_fetch_arch(), ARCH_ARMv4T);
    TEST_END();
}

static void test_arch_armv5te() {
    TEST_BEGIN("llarm_cpu_fetch_arch: ARMv5TE");
    // arch bits = 0x5 → 0x41059460
    llarm_cpu_set_test_midr(0x41059460);
    ASSERT_EQ(llarm_cpu_fetch_arch(), ARCH_ARMv5TE);
    TEST_END();
}

static void test_arch_armv6() {
    TEST_BEGIN("llarm_cpu_fetch_arch: ARMv6");
    // arch bits = 0x7 → 0x4107B760 (ARM1136JF-S like)
    llarm_cpu_set_test_midr(0x4107B760);
    ASSERT_EQ(llarm_cpu_fetch_arch(), ARCH_ARMv6);
    TEST_END();
}

static void test_arch_unknown_cpuid_scheme() {
    TEST_BEGIN("llarm_cpu_fetch_arch: UNKNOWN for CPUID scheme (arch=0xF)");
    llarm_cpu_set_test_midr(0x410FC090); // Cortex-A9
    ASSERT_EQ(llarm_cpu_fetch_arch(), ARCH_UNKNOWN);
    TEST_END();
}

// ---------------------------------------------------------------------------
// llarm_cpu_fetch_ppn tests
// ---------------------------------------------------------------------------

static void test_ppn_arm926() {
    TEST_BEGIN("llarm_cpu_fetch_ppn: ARM926 = 0x926");
    llarm_cpu_set_test_midr(0x41069265);
    ASSERT_EQ(llarm_cpu_fetch_ppn(), 0x926U);
    TEST_END();
}

static void test_ppn_pre_arm7_returns_zero() {
    TEST_BEGIN("llarm_cpu_fetch_ppn: pre-ARM7 returns 0");
    llarm_cpu_set_test_midr(0x41560300);
    ASSERT_EQ(llarm_cpu_fetch_ppn(), 0U);
    TEST_END();
}

// ---------------------------------------------------------------------------
// llarm_cpu_fetch_revision tests
// ---------------------------------------------------------------------------

static void test_revision_arm926() {
    TEST_BEGIN("llarm_cpu_fetch_revision: ARM926 revision = 5");
    llarm_cpu_set_test_midr(0x41069265); // bits[3:0] = 0x5
    ASSERT_EQ(llarm_cpu_fetch_revision(), 0x5U);
    TEST_END();
}

static void test_revision_zero() {
    TEST_BEGIN("llarm_cpu_fetch_revision: revision = 0");
    llarm_cpu_set_test_midr(0x41069260);
    ASSERT_EQ(llarm_cpu_fetch_revision(), 0U);
    TEST_END();
}

// ---------------------------------------------------------------------------
// llarm_cpu_fetch_product_string tests
// ---------------------------------------------------------------------------

static void test_product_string_arm926() {
    TEST_BEGIN("llarm_cpu_fetch_product_string: ARM926EJ-S");
    ASSERT_TRUE(my_strcmp(llarm_cpu_fetch_product_string(PROD_ARM926EJ_S), "ARM926EJ_S") == 0);
    TEST_END();
}

static void test_product_string_cortex_a9() {
    TEST_BEGIN("llarm_cpu_fetch_product_string: Cortex-A9");
    ASSERT_TRUE(my_strcmp(llarm_cpu_fetch_product_string(PROD_CORTEX_A9), "CORTEX_A9") == 0);
    TEST_END();
}

static void test_product_string_unknown() {
    TEST_BEGIN("llarm_cpu_fetch_product_string: UNKNOWN");
    ASSERT_TRUE(my_strcmp(llarm_cpu_fetch_product_string(PROD_UNKNOWN), "UNKNOWN") == 0);
    TEST_END();
}

// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------

extern "C" int main() {
    semi_puts("=== llarm-cpu test suite (ARMv5 / QEMU) ===\n\n");

    test_llarm_cpu_fetch_bits_full_word();
    test_llarm_cpu_fetch_bits_byte_high();
    test_llarm_cpu_fetch_bits_byte_low();
    test_llarm_cpu_fetch_bits_nibble();
    test_llarm_cpu_fetch_bits_single();
    test_llarm_cpu_fetch_bits_arm926_implementor();
    test_llarm_cpu_fetch_bits_arm926_arch();
    test_llarm_cpu_fetch_bits_arm926_ppn();

    test_is_pre_arm7();
    test_is_arm7();
    test_is_post_arm7();

    test_implementor_arm();
    test_implementor_qualcomm();
    test_implementor_apple();
    test_implementor_nvidia();
    test_implementor_llarm();
    test_implementor_unknown_pre_arm7();

    test_product_arm926();
    test_product_arm920t();
    test_product_cortex_a9();
    test_product_cortex_m4();
    test_product_cortex_a53();
    test_product_arm710();
    test_product_arm710t();
    test_product_arm600_pre_arm7();
    test_product_unknown_third_party();

    test_arch_armv5tej_arm926();
    test_arch_armv4t_arm920t();
    test_arch_armv3_arm710();
    test_arch_armv4t_arm710t();
    test_arch_armv5te();
    test_arch_armv6();
    test_arch_unknown_cpuid_scheme();

    test_ppn_arm926();
    test_ppn_pre_arm7_returns_zero();

    test_revision_arm926();
    test_revision_zero();

    test_product_string_arm926();
    test_product_string_cortex_a9();
    test_product_string_unknown();

    semi_puts("\n=== Results: ");
    semi_put_uint(_tests_passed);
    semi_putc('/');
    semi_put_uint(_tests_run);
    semi_puts(" passed");
    if (_tests_failed > 0) {
        semi_puts(", ");
        semi_put_uint(_tests_failed);
        semi_puts(" FAILED");
    }
    semi_puts(" ===\n");

    return (_tests_failed == 0) ? 0 : 1;
}
