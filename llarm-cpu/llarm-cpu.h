#include <stdint.h>

//#define is_x86 (defined(__i386__) || defined(__x86_64__))
// ^ TODO add this back during production builds 


enum arch {
    ARCH_UNKNOWN,
    ARCH_ARMv1,
    ARCH_ARMv2,
    ARCH_ARMv2a,
    ARCH_ARMv3,
    ARCH_ARMv3M,
    ARCH_ARMv4,
    ARCH_ARMv4xM,
    ARCH_ARMv4T,
    ARCH_ARMv4TxM,
    ARCH_ARMv5,
    ARCH_ARMv5xM,
    ARCH_ARMv5T,
    ARCH_ARMv5TxM,
    ARCH_ARMv5TE,
    ARCH_ARMv5TExP,
    ARCH_ARMv5TEJ,
    ARCH_ARMv6,
    ARCH_ARMv6T2,
    ARCH_ARMv6Z,
    ARCH_ARMv6K,
    ARCH_ARMv6_M,
    ARCH_ARMv7_A,
    ARCH_ARMv7_M,
    ARCH_ARMv7_R,
    ARCH_ARMv7E_M,
    ARCH_ARMv8_A,
    ARCH_ARMv8_R,
    ARCH_ARMv8_M_BASELINE,
    ARCH_ARMv8_M_MAINLINE,
    ARCH_ARMv8_1_M_MAINLINE,
    ARCH_ARMv8_2_A,
    ARCH_ARMv8_3_A,
    ARCH_ARMv8_4_A,
    ARCH_ARMv8_5_A,
    ARCH_ARMv8_6_A,
    ARCH_ARMv9_A,
    ARCH_ARMv9_2_A
};


enum product {
    PROD_UNKNOWN,
    PROD_ARM1,
    PROD_ARM2,
    PROD_ARM250,
    PROD_ARM3,
    PROD_ARM60,
    PROD_ARM600,
    PROD_ARM610,
    PROD_ARM620,
    PROD_ARM700,
    PROD_ARM710,
    PROD_ARM710A,
    PROD_ARM7TDMI_S,
    PROD_ARM710T,
    PROD_ARM720T,
    PROD_ARM740T,
    PROD_ARM7EJ_S,
    PROD_ARM810,
    PROD_ARM9TDMI,
    PROD_ARM920T,
    PROD_ARM922T,
    PROD_ARM940T,
    PROD_ARM946E_S,
    PROD_ARM966E_S,
    PROD_ARM968E_S,
    PROD_ARM926EJ_S,
    PROD_ARM996HS,
    PROD_ARM1020E,
    PROD_ARM1022E,
    PROD_ARM1026EJ_S,
    PROD_ARM1136JF_S,
    PROD_ARM1156T2F_S,
    PROD_ARM1176JZF_S,
    PROD_ARM11MPCORE,
    PROD_SC000,
    PROD_SC100,
    PROD_SC300,
    PROD_CORTEX_M0,
    PROD_CORTEX_M0_PLUS,
    PROD_CORTEX_M1,
    PROD_CORTEX_M3,
    PROD_CORTEX_M4,
    PROD_CORTEX_M7,
    PROD_CORTEX_M23,
    PROD_CORTEX_M33,
    PROD_CORTEX_M35P,
    PROD_CORTEX_M52,
    PROD_CORTEX_M55,
    PROD_CORTEX_M85,
    PROD_CORTEX_R4,
    PROD_CORTEX_R5,
    PROD_CORTEX_R7,
    PROD_CORTEX_R8,
    PROD_CORTEX_R52,
    PROD_CORTEX_R52_PLUS,
    PROD_CORTEX_R82,
    PROD_CORTEX_A5,
    PROD_CORTEX_A7,
    PROD_CORTEX_A8,
    PROD_CORTEX_A9,
    PROD_CORTEX_A12,
    PROD_CORTEX_A15,
    PROD_CORTEX_A17,
    PROD_CORTEX_A32,
    PROD_CORTEX_A34,
    PROD_CORTEX_A35,
    PROD_CORTEX_A53,
    PROD_CORTEX_A57,
    PROD_CORTEX_A72,
    PROD_CORTEX_A73,
    PROD_CORTEX_A55,
    PROD_CORTEX_A65,
    PROD_CORTEX_A65AE,
    PROD_CORTEX_A75,
    PROD_CORTEX_A76,
    PROD_CORTEX_A76AE,
    PROD_CORTEX_A77,
    PROD_CORTEX_A78,
    PROD_CORTEX_A78AE,
    PROD_CORTEX_A78C,
    PROD_CORTEX_A510,
    PROD_CORTEX_A710,
    PROD_CORTEX_A715,
    PROD_CORTEX_A520,
    PROD_CORTEX_A720,
    PROD_CORTEX_A725,
    PROD_CORTEX_X1,
    PROD_CORTEX_X2,
    PROD_CORTEX_X3,
    PROD_CORTEX_X4,
    PROD_CORTEX_X925,
    PROD_NEOVERSE_N1,
    PROD_NEOVERSE_E1,
    PROD_NEOVERSE_V1,
    PROD_NEOVERSE_N2,
    PROD_NEOVERSE_V2,
    PROD_NEOVERSE_N3,
    PROD_NEOVERSE_V3
};

enum implementor {
    IMPL_UNKNOWN,
    IMPL_ARM,
    IMPL_BRCM, // broadcom 
    IMPL_DEC, // digital equipment corporation
    IMPL_MOTOROLA,
    IMPL_QUALCOMM,
    IMPL_MARVELL,
    IMPL_INTEL,
    IMPL_CAVIUM,
    IMPL_FUJITSU,
    IMPL_INFINEON,
    IMPL_NVIDIA,
    IMPL_APM, // applied micro circuits corporation
    IMPL_SAMSUNG,
    IMPL_TI, // texas instruments (this is a guess)
    IMPL_APPLE,
    IMPL_FARADAY,
    IMPL_AMPERE,
    IMPL_HISI,
    IMPL_MICROSOFT,
    IMPL_LLARM // custom
};


static uint32_t fetch_bits(const uint32_t value, const uint8_t start, const uint8_t end) {
    return (value >> end) & ((1U << (start - end + 1)) - 1);
}


static uint32_t fetch_midr() {
#if defined(is_x86)
    return 0;
#else
    uint32_t midr; // main ID register
    __asm__ volatile("mrc p15, 0, %0, c0, c0, 0" : "=r"(midr));
    return midr;
#endif
}


static bool is_pre_ARM7() {
#if defined(is_x86)
    return false;
#else
    const uint32_t upper_PPN = fetch_bits(fetch_midr(), 15, 12);
    return (upper_PPN == 0x0);
#endif
}


static bool is_ARM7() {
#if defined(is_x86)
    return false;
#else
    const uint32_t upper_PPN = fetch_bits(fetch_midr(), 15, 12);
    return (upper_PPN == 0x7);
#endif
}


static bool is_post_ARM7() {
#if defined(is_x86)
    return false;
#else
    const uint32_t upper_PPN = fetch_bits(fetch_midr(), 15, 12);
    return ((upper_PPN != 0x0) && (upper_PPN != 0x7));
#endif
}


static uint32_t fetch_cpu_revision() {
#if defined(is_x86)
    return 0;
#else
    return fetch_bits(fetch_midr(), 3, 0);
#endif
}


static uint32_t fetch_cpu_ppn() {
#if defined(is_x86)
    return 0;
#else
    if (is_pre_ARM7()) {
        return 0;
    }

    return fetch_bits(fetch_midr(), 15, 4);
#endif
}


static uint32_t fetch_cpu_variant() {
#if defined(is_x86)
    return 0;
#else
    if (is_pre_ARM7()) {
        return 0;
    }

    if (is_ARM7()) {
        return fetch_bits(fetch_midr(), 22, 16);
    }

    return fetch_bits(fetch_midr(), 23, 20);
#endif
}


static enum implementor fetch_implementor() {
#if defined(is_x86)
    return IMPL_UNKNOWN;
#else
    if (is_pre_ARM7()) {
        return IMPL_UNKNOWN;
    }

    const uint32_t implementor_bits = fetch_bits(fetch_midr(), 31, 24);

    switch (implementor_bits) {
        case 0x41: return IMPL_ARM;
        case 0x42: return IMPL_BRCM;
        case 0x4C: return IMPL_LLARM;
        case 0x44: return IMPL_DEC;
        case 0x4D: return IMPL_MOTOROLA;
        case 0x51: return IMPL_QUALCOMM;
        case 0x56: return IMPL_MARVELL;
        case 0x69: return IMPL_INTEL;
        case 0x43: return IMPL_CAVIUM;
        case 0x46: return IMPL_FUJITSU;
        case 0x49: return IMPL_INFINEON;
        case 0x4e: return IMPL_NVIDIA;
        case 0x50: return IMPL_APM;
        case 0x53: return IMPL_SAMSUNG;
        case 0x54: return IMPL_TI;
        case 0x61: return IMPL_APPLE;
        case 0x66: return IMPL_FARADAY;
        case 0xc0: return IMPL_AMPERE;
        case 0x48: return IMPL_HISI;
        case 0x6D: return IMPL_MICROSOFT;
        default: return IMPL_UNKNOWN;
    }
#endif
}


static enum product fetch_cpu_product() {
#if defined(is_x86)
    return 0;
#else
    const uint32_t midr = fetch_midr();

    if (midr == 0) {
        return PROD_UNKNOWN;
    }

    const uint32_t product_code = midr & 0xFFFFFFF0;

    // see https://github.com/NetBSD/src/blob/cce745e5e7843c99aabeec982cea42f75700d5b0/sys/arch/arm/include/cputypes.h#L116

    if (is_pre_ARM7()) {
        switch (product_code) {
            case 0x41560300: return PROD_ARM3;
            case 0x41560600: return PROD_ARM600;
            case 0x41560610: return PROD_ARM610;
            case 0x41560620: return PROD_ARM620;
            default:         return PROD_UNKNOWN;
        }
    }

    if (is_ARM7()) {
        switch (product_code) {
            case 0x41007000: return PROD_ARM700;
            case 0x41007100: return PROD_ARM710;
            case 0x41067100: return PROD_ARM710A;
            case 0x41807100: return PROD_ARM710T;
            case 0x41807200: return PROD_ARM720T;
            case 0x41807400: return PROD_ARM740T;
            default:         return PROD_UNKNOWN;
        }
    }

    // post-ARM7
    const uint32_t ppn  = fetch_cpu_ppn();
    const enum implementor impl = fetch_implementor();

    // temporary, third-party processors will be added in the future
    if (impl != IMPL_ARM) {
        return PROD_UNKNOWN;
    }

    switch (ppn) {
        /* Classic ARM */
        case 0x810: return PROD_ARM810;
        case 0x920: return PROD_ARM920T;
        case 0x922: return PROD_ARM922T;
        case 0x926: return PROD_ARM926EJ_S;
        case 0x940: return PROD_ARM940T;
        case 0x946: return PROD_ARM946E_S;
        case 0x966: return PROD_ARM966E_S;
        case 0xa20: return PROD_ARM1020E;
        case 0xa22: return PROD_ARM1022E;
        case 0xa26: return PROD_ARM1026EJ_S;
        case 0xb02: return PROD_ARM11MPCORE;
        case 0xb36: return PROD_ARM1136JF_S;
        case 0xb56: return PROD_ARM1156T2F_S;
        case 0xb76: return PROD_ARM1176JZF_S;

        /* Cortex-M */
        case 0xc20: return PROD_CORTEX_M0;
        case 0xc60: return PROD_CORTEX_M0_PLUS;
        case 0xc21: return PROD_CORTEX_M1;
        case 0xc23: return PROD_CORTEX_M3;
        case 0xc24: return PROD_CORTEX_M4;
        case 0xc27: return PROD_CORTEX_M7;
        case 0xd20: return PROD_CORTEX_M23;
        case 0xd21: return PROD_CORTEX_M33;
        case 0xd31: return PROD_CORTEX_M35P;
        // case 0xd44: return PROD_CORTEX_M52; TODO resolve conflict
        case 0xd50: return PROD_CORTEX_M55;  /* also Cortex-M52 shares? verify */
        // case 0xd85: return PROD_CORTEX_M85; TODO resolve conflict

        /* Cortex-R */
        case 0xc14: return PROD_CORTEX_R4;
        case 0xc15: return PROD_CORTEX_R5;
        case 0xc17: return PROD_CORTEX_R7;
        case 0xc18: return PROD_CORTEX_R8;
        case 0xd13: return PROD_CORTEX_R52;
        case 0xd16: return PROD_CORTEX_R52_PLUS;
        case 0xd15: return PROD_CORTEX_R82;

        /* Cortex-A (ARMv7) */
        case 0xc05: return PROD_CORTEX_A5;
        case 0xc07: return PROD_CORTEX_A7;
        case 0xc08: return PROD_CORTEX_A8;
        case 0xc09: return PROD_CORTEX_A9;
        case 0xc0d: return PROD_CORTEX_A12;
        case 0xc0f: return PROD_CORTEX_A15;
        case 0xc0e: return PROD_CORTEX_A17;

        /* Cortex-A (ARMv8+) */
        case 0xd01: return PROD_CORTEX_A32;
        case 0xd02: return PROD_CORTEX_A34; /* AArch64 only, verify */
        case 0xd04: return PROD_CORTEX_A35;
        case 0xd03: return PROD_CORTEX_A53;
        case 0xd07: return PROD_CORTEX_A57;
        case 0xd08: return PROD_CORTEX_A72;
        case 0xd09: return PROD_CORTEX_A73;
        case 0xd05: return PROD_CORTEX_A55;
        case 0xd06: return PROD_CORTEX_A65;
        case 0xd43: return PROD_CORTEX_A65AE;
        case 0xd0a: return PROD_CORTEX_A75;
        case 0xd0b: return PROD_CORTEX_A76;
        case 0xd0e: return PROD_CORTEX_A76AE;
        case 0xd0d: return PROD_CORTEX_A77;
        case 0xd41: return PROD_CORTEX_A78;
        case 0xd42: return PROD_CORTEX_A78AE;
        case 0xd4b: return PROD_CORTEX_A78C;
        case 0xd46: return PROD_CORTEX_A510;
        case 0xd47: return PROD_CORTEX_A710;
        case 0xd4d: return PROD_CORTEX_A715;
        case 0xd80: return PROD_CORTEX_A520;
        case 0xd81: return PROD_CORTEX_A720;
        case 0xd87: return PROD_CORTEX_A725;

        /* Cortex-X */
        case 0xd44: return PROD_CORTEX_X1;
        case 0xd48: return PROD_CORTEX_X2;
        case 0xd4e: return PROD_CORTEX_X3;
        case 0xd82: return PROD_CORTEX_X4;
        case 0xd85: return PROD_CORTEX_X925;

        /* Neoverse */
        case 0xd0c: return PROD_NEOVERSE_N1;
        case 0xd4a: return PROD_NEOVERSE_E1;
        case 0xd40: return PROD_NEOVERSE_V1;
        case 0xd49: return PROD_NEOVERSE_N2;
        case 0xd4f: return PROD_NEOVERSE_V2;
        case 0xd8e: return PROD_NEOVERSE_N3;
        case 0xd84: return PROD_NEOVERSE_V3;

        default: return PROD_UNKNOWN;
    }
#endif
}


static const char* fetch_cpu_product_string(const enum product prod) {
    switch (prod) {
        case PROD_UNKNOWN: return "PROD_UNKNOWN";
        case PROD_ARM1: return "PROD_ARM1";
        case PROD_ARM2: return "PROD_ARM2";
        case PROD_ARM250: return "PROD_ARM250";
        case PROD_ARM3: return "PROD_ARM3";
        case PROD_ARM60: return "PROD_ARM60";
        case PROD_ARM600: return "PROD_ARM600";
        case PROD_ARM610: return "PROD_ARM610";
        case PROD_ARM620: return "PROD_ARM620";
        case PROD_ARM700: return "PROD_ARM700";
        case PROD_ARM710: return "PROD_ARM710";
        case PROD_ARM710A: return "PROD_ARM710A";
        case PROD_ARM7TDMI_S: return "PROD_ARM7TDMI_S";
        case PROD_ARM710T: return "PROD_ARM710T";
        case PROD_ARM720T: return "PROD_ARM720T";
        case PROD_ARM740T: return "PROD_ARM740T";
        case PROD_ARM7EJ_S: return "PROD_ARM7EJ_S";
        case PROD_ARM810: return "PROD_ARM810";
        case PROD_ARM9TDMI: return "PROD_ARM9TDMI";
        case PROD_ARM920T: return "PROD_ARM920T";
        case PROD_ARM922T: return "PROD_ARM922T";
        case PROD_ARM940T: return "PROD_ARM940T";
        case PROD_ARM946E_S: return "PROD_ARM946E_S";
        case PROD_ARM966E_S: return "PROD_ARM966E_S";
        case PROD_ARM968E_S: return "PROD_ARM968E_S";
        case PROD_ARM926EJ_S: return "PROD_ARM926EJ_S";
        case PROD_ARM996HS: return "PROD_ARM996HS";
        case PROD_ARM1020E: return "PROD_ARM1020E";
        case PROD_ARM1022E: return "PROD_ARM1022E";
        case PROD_ARM1026EJ_S: return "PROD_ARM1026EJ_S";
        case PROD_ARM1136JF_S: return "PROD_ARM1136JF_S";
        case PROD_ARM1156T2F_S: return "PROD_ARM1156T2F_S";
        case PROD_ARM1176JZF_S: return "PROD_ARM1176JZF_S";
        case PROD_ARM11MPCORE: return "PROD_ARM11MPCORE";
        case PROD_SC000: return "PROD_SC000";
        case PROD_SC100: return "PROD_SC100";
        case PROD_SC300: return "PROD_SC300";
        case PROD_CORTEX_M0: return "PROD_CORTEX_M0";
        case PROD_CORTEX_M0_PLUS: return "PROD_CORTEX_M0_PLUS";
        case PROD_CORTEX_M1: return "PROD_CORTEX_M1";
        case PROD_CORTEX_M3: return "PROD_CORTEX_M3";
        case PROD_CORTEX_M4: return "PROD_CORTEX_M4";
        case PROD_CORTEX_M7: return "PROD_CORTEX_M7";
        case PROD_CORTEX_M23: return "PROD_CORTEX_M23";
        case PROD_CORTEX_M33: return "PROD_CORTEX_M33";
        case PROD_CORTEX_M35P: return "PROD_CORTEX_M35P";
        case PROD_CORTEX_M52: return "PROD_CORTEX_M52";
        case PROD_CORTEX_M55: return "PROD_CORTEX_M55";
        case PROD_CORTEX_M85: return "PROD_CORTEX_M85";
        case PROD_CORTEX_R4: return "PROD_CORTEX_R4";
        case PROD_CORTEX_R5: return "PROD_CORTEX_R5";
        case PROD_CORTEX_R7: return "PROD_CORTEX_R7";
        case PROD_CORTEX_R8: return "PROD_CORTEX_R8";
        case PROD_CORTEX_R52: return "PROD_CORTEX_R52";
        case PROD_CORTEX_R52_PLUS: return "PROD_CORTEX_R52_PLUS";
        case PROD_CORTEX_R82: return "PROD_CORTEX_R82";
        case PROD_CORTEX_A5: return "PROD_CORTEX_A5";
        case PROD_CORTEX_A7: return "PROD_CORTEX_A7";
        case PROD_CORTEX_A8: return "PROD_CORTEX_A8";
        case PROD_CORTEX_A9: return "PROD_CORTEX_A9";
        case PROD_CORTEX_A12: return "PROD_CORTEX_A12";
        case PROD_CORTEX_A15: return "PROD_CORTEX_A15";
        case PROD_CORTEX_A17: return "PROD_CORTEX_A17";
        case PROD_CORTEX_A32: return "PROD_CORTEX_A32";
        case PROD_CORTEX_A34: return "PROD_CORTEX_A34";
        case PROD_CORTEX_A35: return "PROD_CORTEX_A35";
        case PROD_CORTEX_A53: return "PROD_CORTEX_A53";
        case PROD_CORTEX_A57: return "PROD_CORTEX_A57";
        case PROD_CORTEX_A72: return "PROD_CORTEX_A72";
        case PROD_CORTEX_A73: return "PROD_CORTEX_A73";
        case PROD_CORTEX_A55: return "PROD_CORTEX_A55";
        case PROD_CORTEX_A65: return "PROD_CORTEX_A65";
        case PROD_CORTEX_A65AE: return "PROD_CORTEX_A65AE";
        case PROD_CORTEX_A75: return "PROD_CORTEX_A75";
        case PROD_CORTEX_A76: return "PROD_CORTEX_A76";
        case PROD_CORTEX_A76AE: return "PROD_CORTEX_A76AE";
        case PROD_CORTEX_A77: return "PROD_CORTEX_A77";
        case PROD_CORTEX_A78: return "PROD_CORTEX_A78";
        case PROD_CORTEX_A78AE: return "PROD_CORTEX_A78AE";
        case PROD_CORTEX_A78C: return "PROD_CORTEX_A78C";
        case PROD_CORTEX_A510: return "PROD_CORTEX_A510";
        case PROD_CORTEX_A710: return "PROD_CORTEX_A710";
        case PROD_CORTEX_A715: return "PROD_CORTEX_A715";
        case PROD_CORTEX_A520: return "PROD_CORTEX_A520";
        case PROD_CORTEX_A720: return "PROD_CORTEX_A720";
        case PROD_CORTEX_A725: return "PROD_CORTEX_A725";
        case PROD_CORTEX_X1: return "PROD_CORTEX_X1";
        case PROD_CORTEX_X2: return "PROD_CORTEX_X2";
        case PROD_CORTEX_X3: return "PROD_CORTEX_X3";
        case PROD_CORTEX_X4: return "PROD_CORTEX_X4";
        case PROD_CORTEX_X925: return "PROD_CORTEX_X925";
        case PROD_NEOVERSE_N1: return "PROD_NEOVERSE_N1";
        case PROD_NEOVERSE_E1: return "PROD_NEOVERSE_E1";
        case PROD_NEOVERSE_V1: return "PROD_NEOVERSE_V1";
        case PROD_NEOVERSE_N2: return "PROD_NEOVERSE_N2";
        case PROD_NEOVERSE_V2: return "PROD_NEOVERSE_V2";
        case PROD_NEOVERSE_N3: return "PROD_NEOVERSE_N3";
        case PROD_NEOVERSE_V3: return "PROD_NEOVERSE_V3";
    }
}

static enum arch fetch_cpu_arch() {
#if defined(is_x86)
    return 0;
#else
    if (is_pre_ARM7()) {
        const enum product prod = fetch_cpu_product();

        switch (prod) {
            case PROD_ARM3: return ARCH_ARMv2a;
            case PROD_ARM60:
            case PROD_ARM600:
            case PROD_ARM610:
            case PROD_ARM620: return ARCH_ARMv3;
            default: return ARCH_UNKNOWN;
        }
    }

    const uint32_t midr = fetch_midr();

    // B2-8
    if (is_ARM7()) {
        // this is literally called the A bit in the ARM docs
        const bool A = ((midr >> 23) & 1);

        if (A) {
            return ARCH_ARMv4T;
        }

        return ARCH_ARMv3;
    }

    // B2-7
    const uint32_t arch_bits = fetch_bits(midr, 19, 16);

    switch (arch_bits) {
        case 0x1: return ARCH_ARMv4;
        case 0x2: return ARCH_ARMv4T;
        case 0x3: return ARCH_ARMv5;
        case 0x4: return ARCH_ARMv5T;
        case 0x5: return ARCH_ARMv5TE;
        case 0x6: return ARCH_ARMv5TEJ;
        case 0x7: return ARCH_ARMv6;
        default: return ARCH_UNKNOWN;
    }
#endif
}

//struct info {
//
//};