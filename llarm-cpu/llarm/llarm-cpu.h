#include <stdint.h>

#if defined(__i386__) || defined(__x86_64__)
    #define is_x86 1
#endif

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
    PROD_NEOVERSE_V3,

    /* Qualcomm */
    PROD_QCOM_SCORPION,        // Snapdragon S1/S2 (ARMv7)
    PROD_QCOM_SCORPION_MP,     // Snapdragon S3/S4 multi-core (ARMv7)
    PROD_QCOM_KRAIT,           // Snapdragon 200/400 (ARMv7)
    PROD_QCOM_KRAIT_S4_PRO,    // Snapdragon 600/800 (ARMv7)
    PROD_QCOM_KRYO,            // Snapdragon 820/821 custom (ARMv8)
    PROD_QCOM_FALKOR_V1,       // Centriq 2400 early silicon (server)
    PROD_QCOM_FALKOR,          // Centriq 2400 (server)
    PROD_QCOM_KRYO_3XX_SILVER, // Snapdragon 845 little (semi-custom A55)
    PROD_QCOM_KRYO_4XX_GOLD,   // Snapdragon 855/865 big (semi-custom A76)
    PROD_QCOM_KRYO_4XX_SILVER, // Snapdragon 855/865 little (semi-custom A55)
    PROD_QCOM_KRYO_5XX_GOLD,   // Snapdragon 888 big (semi-custom A78)
    PROD_QCOM_KRYO_5XX_SILVER, // Snapdragon 888 little (semi-custom A55)
    PROD_QCOM_ORYON,           // Snapdragon X Elite (custom ARMv9)

    /* Apple M1+ (confirmed via Asahi Linux / mainline kernel) */
    PROD_APPLE_ICESTORM,       // M1 efficiency (0x022); A14 little may be 0x020
    PROD_APPLE_FIRESTORM,      // M1 performance (0x023); A14 big may be 0x021
    PROD_APPLE_ICESTORM_PRO,   // M1 Pro/Max efficiency
    PROD_APPLE_FIRESTORM_PRO,  // M1 Pro/Max performance
    PROD_APPLE_ICESTORM_MAX,   // M1 Ultra efficiency
    PROD_APPLE_FIRESTORM_MAX,  // M1 Ultra performance
    PROD_APPLE_BLIZZARD,       // M2 efficiency
    PROD_APPLE_AVALANCHE,      // M2 performance

    /* Samsung Mongoose */
    PROD_SAMSUNG_M1,           // Exynos 8890 (2016)
    PROD_SAMSUNG_M2,           // Exynos 8895 (2017)
    PROD_SAMSUNG_M3,           // Exynos 9810 (2018)
    PROD_SAMSUNG_M4,           // Exynos 9820 (2019)
    PROD_SAMSUNG_M5,           // Exynos 990 (2020)

    /* Cavium */
    PROD_CAVIUM_THUNDERX,      // ThunderX CN88xx
    PROD_CAVIUM_THUNDERX_81XX, // ThunderX CN81xx
    PROD_CAVIUM_THUNDERX_83XX, // ThunderX CN83xx
    PROD_CAVIUM_THUNDERX2,     // ThunderX2 CN99xx

    /* NVIDIA */
    PROD_NVIDIA_DENVER,        // Tegra X1 (Denver 2)
    PROD_NVIDIA_CARMEL,        // Tegra Xavier

    /* Fujitsu */
    PROD_FUJITSU_A64FX,        // Fugaku supercomputer

    /* HiSilicon */
    PROD_HISI_TSV110,          // Hi1620 / Kunpeng 920 (server)

    /* APM */
    PROD_APM_POTENZA           // X-Gene (first ARMv8 server processor)
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

#if !defined(is_x86)
static uint32_t llarm_cpu_fetch_bits(const uint32_t value, const uint8_t start, const uint8_t end) {
    return (value >> end) & ((1U << (start - end + 1)) - 1);
}
#endif

#ifdef LLARM_CPU_TEST_MIDR
static uint32_t _llarm_test_midr_val = 0;
static void llarm_cpu_set_test_midr(uint32_t midr) { _llarm_test_midr_val = midr; }
static uint32_t llarm_cpu_fetch_midr() { return _llarm_test_midr_val; }
#else
static uint32_t llarm_cpu_fetch_midr() {
#if defined(is_x86)
    return 0;
#else
    uint32_t midr; // main ID register
    __asm__ volatile("mrc p15, 0, %0, c0, c0, 0" : "=r"(midr));
    return midr;
#endif
}
#endif


static bool llarm_cpu_is_pre_arm7() {
#if defined(is_x86)
    return false;
#else
    const uint32_t upper_PPN = llarm_cpu_fetch_bits(llarm_cpu_fetch_midr(), 15, 12);
    return (upper_PPN == 0x0);
#endif
}


static bool llarm_cpu_is_arm7() {
#if defined(is_x86)
    return false;
#else
    const uint32_t upper_PPN = llarm_cpu_fetch_bits(llarm_cpu_fetch_midr(), 15, 12);
    return (upper_PPN == 0x7);
#endif
}


static bool llarm_cpu_is_post_arm7() {
#if defined(is_x86)
    return false;
#else
    const uint32_t upper_PPN = llarm_cpu_fetch_bits(llarm_cpu_fetch_midr(), 15, 12);
    return ((upper_PPN != 0x0) && (upper_PPN != 0x7));
#endif
}


static uint32_t llarm_cpu_fetch_revision() {
#if defined(is_x86)
    return 0;
#else
    return llarm_cpu_fetch_bits(llarm_cpu_fetch_midr(), 3, 0);
#endif
}


static uint32_t llarm_cpu_fetch_ppn() {
#if defined(is_x86)
    return 0;
#else
    if (llarm_cpu_is_pre_arm7()) {
        return 0;
    }

    return llarm_cpu_fetch_bits(llarm_cpu_fetch_midr(), 15, 4);
#endif
}


static uint32_t llarm_cpu_fetch_variant() {
#if defined(is_x86)
    return 0;
#else
    if (llarm_cpu_is_pre_arm7()) {
        return 0;
    }

    if (llarm_cpu_is_arm7()) {
        return llarm_cpu_fetch_bits(llarm_cpu_fetch_midr(), 22, 16);
    }

    return llarm_cpu_fetch_bits(llarm_cpu_fetch_midr(), 23, 20);
#endif
}


static enum implementor llarm_cpu_fetch_implementor() {
#if defined(is_x86)
    return IMPL_UNKNOWN;
#else
    if (llarm_cpu_is_pre_arm7()) {
        return IMPL_UNKNOWN;
    }

    const uint32_t implementor_bits = llarm_cpu_fetch_bits(llarm_cpu_fetch_midr(), 31, 24);

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

static const char* llarm_cpu_fetch_implementor_string() {
#if defined(is_x86)
    return "UNKNOWN";
#else
    switch (llarm_cpu_fetch_implementor()) {
        case IMPL_ARM: return "ARM"; 
        case IMPL_BRCM: return "BRCM"; 
        case IMPL_LLARM: return "LLARM"; 
        case IMPL_DEC: return "DEC"; 
        case IMPL_MOTOROLA: return "MOTOROLA"; 
        case IMPL_QUALCOMM: return "QUALCOMM"; 
        case IMPL_MARVELL: return "MARVELL"; 
        case IMPL_INTEL: return "INTEL"; 
        case IMPL_CAVIUM: return "CAVIUM"; 
        case IMPL_FUJITSU: return "FUJITSU"; 
        case IMPL_INFINEON: return "INFINEON"; 
        case IMPL_NVIDIA: return "NVIDIA"; 
        case IMPL_APM: return "APM"; 
        case IMPL_SAMSUNG: return "SAMSUNG"; 
        case IMPL_TI: return "TI"; 
        case IMPL_APPLE: return "APPLE"; 
        case IMPL_FARADAY: return "FARADAY"; 
        case IMPL_AMPERE: return "AMPERE"; 
        case IMPL_HISI: return "HISI"; 
        case IMPL_MICROSOFT: return "MICROSOFT"; 
        case IMPL_UNKNOWN: return "UNKNOWN";
    }

    return "UNKNOWN";
#endif
}


static enum product llarm_cpu_fetch_product() {
#if defined(is_x86)
    return PROD_UNKNOWN;
#else
    const uint32_t midr = llarm_cpu_fetch_midr();

    if (midr == 0) {
        return PROD_UNKNOWN;
    }

    const uint32_t product_code = midr & 0xFFFFFFF0;

    // see https://github.com/NetBSD/src/blob/cce745e5e7843c99aabeec982cea42f75700d5b0/sys/arch/arm/include/cputypes.h#L116

    if (llarm_cpu_is_pre_arm7()) {
        switch (product_code) {
            case 0x41560300: return PROD_ARM3;
            case 0x41560600: return PROD_ARM600;
            case 0x41560610: return PROD_ARM610;
            case 0x41560620: return PROD_ARM620;
            default:         return PROD_UNKNOWN;
        }
    }

    if (llarm_cpu_is_arm7()) {
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
    const uint32_t ppn  = llarm_cpu_fetch_ppn();
    const enum implementor impl = llarm_cpu_fetch_implementor();

    if (impl == IMPL_ARM) {
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
    }

    if (impl == IMPL_QUALCOMM) {
        switch (ppn) {
            case 0x00F: return PROD_QCOM_SCORPION;
            case 0x02D: return PROD_QCOM_SCORPION_MP;
            case 0x04D: return PROD_QCOM_KRAIT;
            case 0x06F: return PROD_QCOM_KRAIT_S4_PRO;
            case 0x200: return PROD_QCOM_KRYO;
            case 0x800: return PROD_QCOM_FALKOR_V1;
            case 0xC00: return PROD_QCOM_FALKOR;
            case 0x803: return PROD_QCOM_KRYO_3XX_SILVER;
            case 0x804: return PROD_QCOM_KRYO_4XX_GOLD;
            case 0x805: return PROD_QCOM_KRYO_4XX_SILVER;
            case 0x806: return PROD_QCOM_KRYO_5XX_GOLD;
            case 0x807: return PROD_QCOM_KRYO_5XX_SILVER;
            case 0x001: return PROD_QCOM_ORYON;
            default: return PROD_UNKNOWN;
        }
    }

    if (impl == IMPL_APPLE) {
        switch (ppn) {
            /* A-series (unconfirmed => reverse-engineered, not in mainline Linux):
            case 0x001: Cyclone  (A7)
            case 0x002: Typhoon  (A8/A8X)
            case 0x003: Twister  (A9/A9X)
            case 0x004: Hurricane (A10 Fusion big)
            case 0x005: Zephyr   (A10 Fusion little)
            case 0x008: Monsoon  (A11 Bionic big)
            case 0x009: Mistral  (A11 Bionic little)
            case 0x00B: Vortex   (A12 Bionic big)
            case 0x00C: Tempest  (A12 Bionic little)
            case 0x00E: Lightning (A13 Bionic big)
            case 0x00F: Thunder  (A13 Bionic little)
            case 0x020: Icestorm (A14 Bionic little)
            case 0x021: Firestorm (A14 Bionic big)
            */
            case 0x022: return PROD_APPLE_ICESTORM;
            case 0x023: return PROD_APPLE_FIRESTORM;
            case 0x024: return PROD_APPLE_ICESTORM_PRO;
            case 0x025: return PROD_APPLE_FIRESTORM_PRO;
            case 0x028: return PROD_APPLE_ICESTORM_MAX;
            case 0x029: return PROD_APPLE_FIRESTORM_MAX;
            case 0x032: return PROD_APPLE_BLIZZARD;
            case 0x033: return PROD_APPLE_AVALANCHE;
            default: return PROD_UNKNOWN;
        }
    }

    if (impl == IMPL_SAMSUNG) {
        switch (ppn) {
            case 0x001: return PROD_SAMSUNG_M1;
            case 0x002: return PROD_SAMSUNG_M2;
            case 0x003: return PROD_SAMSUNG_M3;
            case 0x004: return PROD_SAMSUNG_M4;
            case 0x005: return PROD_SAMSUNG_M5;
            default: return PROD_UNKNOWN;
        }
    }

    if (impl == IMPL_CAVIUM) {
        switch (ppn) {
            case 0x0A1: return PROD_CAVIUM_THUNDERX;
            case 0x0A2: return PROD_CAVIUM_THUNDERX_81XX;
            case 0x0A3: return PROD_CAVIUM_THUNDERX_83XX;
            case 0x0AF: return PROD_CAVIUM_THUNDERX2;
            default: return PROD_UNKNOWN;
        }
    }

    if (impl == IMPL_NVIDIA) {
        switch (ppn) {
            case 0x003: return PROD_NVIDIA_DENVER;
            case 0x004: return PROD_NVIDIA_CARMEL;
            default: return PROD_UNKNOWN;
        }
    }

    if (impl == IMPL_FUJITSU) {
        switch (ppn) {
            case 0x001: return PROD_FUJITSU_A64FX;
            default: return PROD_UNKNOWN;
        }
    }

    if (impl == IMPL_HISI) {
        switch (ppn) {
            case 0xD01: return PROD_HISI_TSV110;
            default: return PROD_UNKNOWN;
        }
    }

    if (impl == IMPL_APM) {
        switch (ppn) {
            case 0x000: return PROD_APM_POTENZA;
            default: return PROD_UNKNOWN;
        }
    }

    // IMPL_AMPERE: 0xAC3 reported for Altra but unconfirmed
    // IMPL_MARVELL PJ4B-MP: 0x581/0x584 reported but conflicting sources

    return PROD_UNKNOWN;
#endif
}


static const char* llarm_cpu_fetch_product_string(const enum product prod) {
    switch (prod) {
        case PROD_UNKNOWN: return "UNKNOWN";
        case PROD_ARM1: return "ARM1";
        case PROD_ARM2: return "ARM2";
        case PROD_ARM250: return "ARM250";
        case PROD_ARM3: return "ARM3";
        case PROD_ARM60: return "ARM60";
        case PROD_ARM600: return "ARM600";
        case PROD_ARM610: return "ARM610";
        case PROD_ARM620: return "ARM620";
        case PROD_ARM700: return "ARM700";
        case PROD_ARM710: return "ARM710";
        case PROD_ARM710A: return "ARM710A";
        case PROD_ARM7TDMI_S: return "ARM7TDMI_S";
        case PROD_ARM710T: return "ARM710T";
        case PROD_ARM720T: return "ARM720T";
        case PROD_ARM740T: return "ARM740T";
        case PROD_ARM7EJ_S: return "ARM7EJ_S";
        case PROD_ARM810: return "ARM810";
        case PROD_ARM9TDMI: return "ARM9TDMI";
        case PROD_ARM920T: return "ARM920T";
        case PROD_ARM922T: return "ARM922T";
        case PROD_ARM940T: return "ARM940T";
        case PROD_ARM946E_S: return "ARM946E_S";
        case PROD_ARM966E_S: return "ARM966E_S";
        case PROD_ARM968E_S: return "ARM968E_S";
        case PROD_ARM926EJ_S: return "ARM926EJ_S";
        case PROD_ARM996HS: return "ARM996HS";
        case PROD_ARM1020E: return "ARM1020E";
        case PROD_ARM1022E: return "ARM1022E";
        case PROD_ARM1026EJ_S: return "ARM1026EJ_S";
        case PROD_ARM1136JF_S: return "ARM1136JF_S";
        case PROD_ARM1156T2F_S: return "ARM1156T2F_S";
        case PROD_ARM1176JZF_S: return "ARM1176JZF_S";
        case PROD_ARM11MPCORE: return "ARM11MPCORE";
        case PROD_SC000: return "SC000";
        case PROD_SC100: return "SC100";
        case PROD_SC300: return "SC300";
        case PROD_CORTEX_M0: return "CORTEX_M0";
        case PROD_CORTEX_M0_PLUS: return "CORTEX_M0_PLUS";
        case PROD_CORTEX_M1: return "CORTEX_M1";
        case PROD_CORTEX_M3: return "CORTEX_M3";
        case PROD_CORTEX_M4: return "CORTEX_M4";
        case PROD_CORTEX_M7: return "CORTEX_M7";
        case PROD_CORTEX_M23: return "CORTEX_M23";
        case PROD_CORTEX_M33: return "CORTEX_M33";
        case PROD_CORTEX_M35P: return "CORTEX_M35P";
        case PROD_CORTEX_M52: return "CORTEX_M52";
        case PROD_CORTEX_M55: return "CORTEX_M55";
        case PROD_CORTEX_M85: return "CORTEX_M85";
        case PROD_CORTEX_R4: return "CORTEX_R4";
        case PROD_CORTEX_R5: return "CORTEX_R5";
        case PROD_CORTEX_R7: return "CORTEX_R7";
        case PROD_CORTEX_R8: return "CORTEX_R8";
        case PROD_CORTEX_R52: return "CORTEX_R52";
        case PROD_CORTEX_R52_PLUS: return "CORTEX_R52_PLUS";
        case PROD_CORTEX_R82: return "CORTEX_R82";
        case PROD_CORTEX_A5: return "CORTEX_A5";
        case PROD_CORTEX_A7: return "CORTEX_A7";
        case PROD_CORTEX_A8: return "CORTEX_A8";
        case PROD_CORTEX_A9: return "CORTEX_A9";
        case PROD_CORTEX_A12: return "CORTEX_A12";
        case PROD_CORTEX_A15: return "CORTEX_A15";
        case PROD_CORTEX_A17: return "CORTEX_A17";
        case PROD_CORTEX_A32: return "CORTEX_A32";
        case PROD_CORTEX_A34: return "CORTEX_A34";
        case PROD_CORTEX_A35: return "CORTEX_A35";
        case PROD_CORTEX_A53: return "CORTEX_A53";
        case PROD_CORTEX_A57: return "CORTEX_A57";
        case PROD_CORTEX_A72: return "CORTEX_A72";
        case PROD_CORTEX_A73: return "CORTEX_A73";
        case PROD_CORTEX_A55: return "CORTEX_A55";
        case PROD_CORTEX_A65: return "CORTEX_A65";
        case PROD_CORTEX_A65AE: return "CORTEX_A65AE";
        case PROD_CORTEX_A75: return "CORTEX_A75";
        case PROD_CORTEX_A76: return "CORTEX_A76";
        case PROD_CORTEX_A76AE: return "CORTEX_A76AE";
        case PROD_CORTEX_A77: return "CORTEX_A77";
        case PROD_CORTEX_A78: return "CORTEX_A78";
        case PROD_CORTEX_A78AE: return "CORTEX_A78AE";
        case PROD_CORTEX_A78C: return "CORTEX_A78C";
        case PROD_CORTEX_A510: return "CORTEX_A510";
        case PROD_CORTEX_A710: return "CORTEX_A710";
        case PROD_CORTEX_A715: return "CORTEX_A715";
        case PROD_CORTEX_A520: return "CORTEX_A520";
        case PROD_CORTEX_A720: return "CORTEX_A720";
        case PROD_CORTEX_A725: return "CORTEX_A725";
        case PROD_CORTEX_X1: return "CORTEX_X1";
        case PROD_CORTEX_X2: return "CORTEX_X2";
        case PROD_CORTEX_X3: return "CORTEX_X3";
        case PROD_CORTEX_X4: return "CORTEX_X4";
        case PROD_CORTEX_X925: return "CORTEX_X925";
        case PROD_NEOVERSE_N1: return "NEOVERSE_N1";
        case PROD_NEOVERSE_E1: return "NEOVERSE_E1";
        case PROD_NEOVERSE_V1: return "NEOVERSE_V1";
        case PROD_NEOVERSE_N2: return "NEOVERSE_N2";
        case PROD_NEOVERSE_V2: return "NEOVERSE_V2";
        case PROD_NEOVERSE_N3: return "NEOVERSE_N3";
        case PROD_NEOVERSE_V3: return "NEOVERSE_V3";
        case PROD_QCOM_SCORPION: return "QCOM_SCORPION";
        case PROD_QCOM_SCORPION_MP: return "QCOM_SCORPION_MP";
        case PROD_QCOM_KRAIT: return "QCOM_KRAIT";
        case PROD_QCOM_KRAIT_S4_PRO: return "QCOM_KRAIT_S4_PRO";
        case PROD_QCOM_KRYO: return "QCOM_KRYO";
        case PROD_QCOM_FALKOR_V1: return "QCOM_FALKOR_V1";
        case PROD_QCOM_FALKOR: return "QCOM_FALKOR";
        case PROD_QCOM_KRYO_3XX_SILVER: return "QCOM_KRYO_3XX_SILVER";
        case PROD_QCOM_KRYO_4XX_GOLD: return "QCOM_KRYO_4XX_GOLD";
        case PROD_QCOM_KRYO_4XX_SILVER: return "QCOM_KRYO_4XX_SILVER";
        case PROD_QCOM_KRYO_5XX_GOLD: return "QCOM_KRYO_5XX_GOLD";
        case PROD_QCOM_KRYO_5XX_SILVER: return "QCOM_KRYO_5XX_SILVER";
        case PROD_QCOM_ORYON: return "QCOM_ORYON";
        case PROD_APPLE_ICESTORM: return "APPLE_ICESTORM";
        case PROD_APPLE_FIRESTORM: return "APPLE_FIRESTORM";
        case PROD_APPLE_ICESTORM_PRO: return "APPLE_ICESTORM_PRO";
        case PROD_APPLE_FIRESTORM_PRO: return "APPLE_FIRESTORM_PRO";
        case PROD_APPLE_ICESTORM_MAX: return "APPLE_ICESTORM_MAX";
        case PROD_APPLE_FIRESTORM_MAX: return "APPLE_FIRESTORM_MAX";
        case PROD_APPLE_BLIZZARD: return "APPLE_BLIZZARD";
        case PROD_APPLE_AVALANCHE: return "APPLE_AVALANCHE";
        case PROD_SAMSUNG_M1: return "SAMSUNG_M1";
        case PROD_SAMSUNG_M2: return "SAMSUNG_M2";
        case PROD_SAMSUNG_M3: return "SAMSUNG_M3";
        case PROD_SAMSUNG_M4: return "SAMSUNG_M4";
        case PROD_SAMSUNG_M5: return "SAMSUNG_M5";
        case PROD_CAVIUM_THUNDERX: return "CAVIUM_THUNDERX";
        case PROD_CAVIUM_THUNDERX_81XX: return "CAVIUM_THUNDERX_81XX";
        case PROD_CAVIUM_THUNDERX_83XX: return "CAVIUM_THUNDERX_83XX";
        case PROD_CAVIUM_THUNDERX2: return "CAVIUM_THUNDERX2";
        case PROD_NVIDIA_DENVER: return "NVIDIA_DENVER";
        case PROD_NVIDIA_CARMEL: return "NVIDIA_CARMEL";
        case PROD_FUJITSU_A64FX: return "FUJITSU_A64FX";
        case PROD_HISI_TSV110: return "HISI_TSV110";
        case PROD_APM_POTENZA: return "APM_POTENZA";
    }

    return "UNKNOWN";
}

static enum arch llarm_cpu_fetch_arch() {
#if defined(is_x86)
    return ARCH_UNKNOWN;
#else
    if (llarm_cpu_is_pre_arm7()) {
        const enum product prod = llarm_cpu_fetch_product();

        switch (prod) {
            case PROD_ARM3: return ARCH_ARMv2a;
            case PROD_ARM60:
            case PROD_ARM600:
            case PROD_ARM610:
            case PROD_ARM620: return ARCH_ARMv3;
            default: return ARCH_UNKNOWN;
        }
    }

    const uint32_t midr = llarm_cpu_fetch_midr();

    // B2-8
    if (llarm_cpu_is_arm7()) {
        // this is literally called the A bit in the ARM docs
        const bool A = ((midr >> 23) & 1);

        if (A) {
            return ARCH_ARMv4T;
        }

        return ARCH_ARMv3;
    }

    // B2-7
    const uint32_t arch_bits = llarm_cpu_fetch_bits(midr, 19, 16);

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


static const char* llarm_cpu_fetch_arch_string(const enum arch arch) {
    switch (arch) {
        case ARCH_UNKNOWN: return "UNKNOWN";
        case ARCH_ARMv1: return "ARMv1";
        case ARCH_ARMv2: return "ARMv2";
        case ARCH_ARMv2a: return "ARMv2a";
        case ARCH_ARMv3: return "ARMv3";
        case ARCH_ARMv3M: return "ARMv3M";
        case ARCH_ARMv4: return "ARMv4";
        case ARCH_ARMv4xM: return "ARMv4xM";
        case ARCH_ARMv4T: return "ARMv4T";
        case ARCH_ARMv4TxM: return "ARMv4TxM";
        case ARCH_ARMv5: return "ARMv5";
        case ARCH_ARMv5xM: return "ARMv5xM";
        case ARCH_ARMv5T: return "ARMv5T";
        case ARCH_ARMv5TxM: return "ARMv5TxM";
        case ARCH_ARMv5TE: return "ARMv5TE";
        case ARCH_ARMv5TExP: return "ARMv5TExP";
        case ARCH_ARMv5TEJ: return "ARMv5TEJ";
        case ARCH_ARMv6: return "ARMv6";
        case ARCH_ARMv6T2: return "ARMv6T2";
        case ARCH_ARMv6Z: return "ARMv6Z";
        case ARCH_ARMv6K: return "ARMv6K";
        case ARCH_ARMv6_M: return "ARMv6-M";
        case ARCH_ARMv7_A: return "ARMv7-A";
        case ARCH_ARMv7_M: return "ARMv7-M";
        case ARCH_ARMv7_R: return "ARMv7-R";
        case ARCH_ARMv7E_M: return "ARMv7E-M";
        case ARCH_ARMv8_A: return "ARMv8-A";
        case ARCH_ARMv8_R: return "ARMv8-R";
        case ARCH_ARMv8_M_BASELINE: return "ARMv8-M Baseline";
        case ARCH_ARMv8_M_MAINLINE: return "ARMv8-M Mainline";
        case ARCH_ARMv8_1_M_MAINLINE: return "ARMv8.1-M Mainline";
        case ARCH_ARMv8_2_A: return "ARMv8.2-A";
        case ARCH_ARMv8_3_A: return "ARMv8.3-A";
        case ARCH_ARMv8_4_A: return "ARMv8.4-A";
        case ARCH_ARMv8_5_A: return "ARMv8.5-A";
        case ARCH_ARMv8_6_A: return "ARMv8.6-A";
        case ARCH_ARMv9_A: return "ARMv9-A";
        case ARCH_ARMv9_2_A: return "ARMv9.2-A";
    }
    return "UNKNOWN";
}