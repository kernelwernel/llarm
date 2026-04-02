# llarm CPU C Documentation

## Contents
- [`llarm_cpu_fetch_midr()`](#llarm_cpu_fetch_midr)
- [`llarm_cpu_fetch_bits()`](#llarm_cpu_fetch_bits)
- [`llarm_cpu_is_pre_arm7()`](#llarm_cpu_is_pre_arm7)
- [`llarm_cpu_is_arm7()`](#llarm_cpu_is_arm7)
- [`llarm_cpu_is_post_arm7()`](#llarm_cpu_is_post_arm7)
- [`llarm_cpu_fetch_revision()`](#llarm_cpu_fetch_revision)
- [`llarm_cpu_fetch_ppn()`](#llarm_cpu_fetch_ppn)
- [`llarm_cpu_fetch_variant()`](#llarm_cpu_fetch_variant)
- [`llarm_cpu_fetch_implementor()`](#llarm_cpu_fetch_implementor)
- [`llarm_cpu_fetch_implementor_string()`](#llarm_cpu_fetch_implementor_string)
- [`llarm_cpu_fetch_product()`](#llarm_cpu_fetch_product)
- [`llarm_cpu_fetch_product_string()`](#llarm_cpu_fetch_product_string)
- [`llarm_cpu_fetch_arch()`](#llarm_cpu_fetch_arch)
- [`llarm_cpu_fetch_arch_string()`](#llarm_cpu_fetch_arch_string)
- [Testing](#testing)
- [Enum tables](#enum-tables)
  - [Implementor table](#implementor-table)
  - [Product table](#product-table)
  - [Architecture table](#architecture-table)
- [Platform notes](#platform-notes)

<br>

## `llarm_cpu_fetch_midr()`

This is the core function of the library. It reads the Main ID Register (MIDR) directly from the CPU via the `mrc p15` coprocessor instruction and returns a `unsigned int`. All other fetch functions derive their data from this value.

```c
#include "llarm_cpu.h"

int main() {
    unsigned int midr = llarm_cpu_fetch_midr();
    printf("MIDR: 0x%08X\n", midr);
    return 0;
}
```

> [!NOTE]
> On x86 platforms, this function always returns `0`. All dependent functions return neutral/unknown values as a result.

<br>

## `llarm_cpu_is_pre_arm7()`, `llarm_cpu_is_arm7()`, and `llarm_cpu_is_post_arm7()`

Returns a `bool` indicating whether its release date relative to the ARM7 architecture.

```c
#include "llarm_cpu.h"

int main() {
    if (llarm_cpu_is_arm7()) {
        printf("This CPU is ARM7.\n");
    }

    if (llarm_cpu_is_post_arm7()) {
        printf("This CPU is newer than ARM7.\n");
    }


    if (llarm_cpu_is_pre_arm7()) {
        printf("This CPU is older than ARM7.\n");
    }
    return 0;
}
```

<br>

## `llarm_cpu_fetch_revision()`

Returns an `unsigned int` representing the revision field of the MIDR (bits 3:0). This is the minor stepping of the CPU, distinct from the variant.

```c
unsigned int rev = llarm_cpu_fetch_revision();
printf("CPU revision: r%u\n", rev);
```

<br>

## `llarm_cpu_fetch_ppn()`

Returns an `unsigned int` representing the Primary Part Number (PPN). This is the main identifier used to distinguish specific CPU products within a given implementor.

> [!NOTE]
> Returns `0` for pre-ARM7 CPUs, as the MIDR format is different for those parts.

<br>

## `llarm_cpu_fetch_variant()`

Returns an `unsigned int` for the variant field of the MIDR. This represents the major stepping of the CPU.

<br>

## `llarm_cpu_fetch_implementor()`

Returns an `enum implementor` identifying the company that manufactured the CPU.

```c
#include "llarm_cpu.h"

int main() {
    enum implementor impl = llarm_cpu_fetch_implementor();

    if (impl == IMPL_APPLE) {
        // Apple Silicon specific path
    } else if (impl == IMPL_QUALCOMM) {
        // Qualcomm Snapdragon specific path
    }

    return 0;
}
```

If the implementor byte does not match any known value, the function returns `IMPL_UNKNOWN`. See the [implementor table](#implementor-table) for all supported values.

<br>

## `llarm_cpu_fetch_implementor_string()`

Returns a `const char*` string name for the current CPU's implementor. This is a convenience wrapper around `llarm_cpu_fetch_implementor()`.

```c
printf("Implementor: %s\n", llarm_cpu_fetch_implementor_string());
// example output: "APPLE"
```

<br>

## `llarm_cpu_fetch_product()`

Returns an `enum product` identifying the specific CPU core. It combines the implementor, the generation check, and the PPN to produce a precise product match.

```c
#include "llarm_cpu.h"

int main() {
    enum product prod = llarm_cpu_fetch_product();

    switch (prod) {
        case PROD_CORTEX_A76:
            printf("Cortex-A76 detected\n");
            break;
        case PROD_APPLE_FIRESTORM:
            printf("Apple M1 performance core detected\n");
            break;
        case PROD_UNKNOWN:
        default:
            printf("Product not recognised\n");
            break;
    }

    return 0;
}
```

See the [product table](#product-table) for all supported products.

> [!IMPORTANT]
> A result of `PROD_UNKNOWN` does not mean the CPU is invalid. It means the specific part is not in the library's database. This is common for very old pre-ARM7 parts and newer unreleased silicon, but the lib will do its best to be as up-to-date as possible. 

<br>

## `llarm_cpu_fetch_product_string()`

Returns a `const char*` string for a given `enum product`. Unlike most other fetch functions, this one takes an explicit product argument rather than reading the MIDR itself.

```c
enum product prod = llarm_cpu_fetch_product();
const char* name = llarm_cpu_fetch_product_string(prod);
printf("Product: %s\n", name);
// example output: "CORTEX_A76"
```

<br>

## `llarm_cpu_fetch_arch()`

Returns an `enum arch` identifying the ARM architecture version of the current CPU.

```c
#include "llarm_cpu.h"

int main() {
    enum arch a = llarm_cpu_fetch_arch();

    if (a == ARCH_ARMv8_A) {
        printf("64-bit capable ARMv8-A CPU\n");
    }

    return 0;
}
```

See the [architecture table](#Architecture-table) for all supported archs

<br>

## `llarm_cpu_fetch_arch_string()`

Returns a `const char*` string for a given `enum arch`. Takes an explicit arch argument.

```c
enum arch a = llarm_cpu_fetch_arch();
printf("Architecture: %s\n", llarm_cpu_fetch_arch_string(a));
// example output: "ARMv8-A"
```

<br>

# Enum tables

## Implementor table

| Enum | Implementor | ID byte |
| ---- | ----------- | ------- |
| `IMPL_ARM` | ARM | `0x41` |
| `IMPL_BRCM` | Broadcom | `0x42` |
| `IMPL_DEC` | Digital Equipment Corporation | `0x44` |
| `IMPL_MOTOROLA` | Motorola | `0x4D` |
| `IMPL_QUALCOMM` | Qualcomm | `0x51` |
| `IMPL_MARVELL` | Marvell | `0x56` |
| `IMPL_INTEL` | Intel | `0x69` |
| `IMPL_CAVIUM` | Cavium | `0x43` |
| `IMPL_FUJITSU` | Fujitsu | `0x46` |
| `IMPL_INFINEON` | Infineon | `0x49` |
| `IMPL_NVIDIA` | NVIDIA | `0x4E` |
| `IMPL_APM` | Applied Micro Circuits Corporation | `0x50` |
| `IMPL_SAMSUNG` | Samsung | `0x53` |
| `IMPL_TI` | Texas Instruments | `0x54` |
| `IMPL_APPLE` | Apple | `0x61` |
| `IMPL_FARADAY` | Faraday | `0x66` |
| `IMPL_AMPERE` | Ampere | `0xC0` |
| `IMPL_HISI` | HiSilicon | `0x48` |
| `IMPL_MICROSOFT` | Microsoft | `0x6D` |
| `IMPL_LLARM` | LLARM (custom) | `0x4C` |
| `IMPL_UNKNOWN` | Unknown | — |

<br>

## Product table

### ARM Classic

| Enum | Product | PPN |
| ---- | ------- | --- |
| `PROD_ARM3` | ARM3 | — |
| `PROD_ARM600` | ARM600 | — |
| `PROD_ARM610` | ARM610 | — |
| `PROD_ARM620` | ARM620 | — |
| `PROD_ARM700` | ARM700 | — |
| `PROD_ARM710` | ARM710 | — |
| `PROD_ARM710A` | ARM710A | — |
| `PROD_ARM710T` | ARM710T | — |
| `PROD_ARM720T` | ARM720T | — |
| `PROD_ARM740T` | ARM740T | — |
| `PROD_ARM810` | ARM810 | `0x810` |
| `PROD_ARM920T` | ARM920T | `0x920` |
| `PROD_ARM922T` | ARM922T | `0x922` |
| `PROD_ARM926EJ_S` | ARM926EJ-S | `0x926` |
| `PROD_ARM940T` | ARM940T | `0x940` |
| `PROD_ARM946E_S` | ARM946E-S | `0x946` |
| `PROD_ARM966E_S` | ARM966E-S | `0x966` |
| `PROD_ARM1020E` | ARM1020E | `0xA20` |
| `PROD_ARM1022E` | ARM1022E | `0xA22` |
| `PROD_ARM1026EJ_S` | ARM1026EJ-S | `0xA26` |
| `PROD_ARM11MPCORE` | ARM11 MPCore | `0xB02` |
| `PROD_ARM1136JF_S` | ARM1136JF-S | `0xB36` |
| `PROD_ARM1156T2F_S` | ARM1156T2F-S | `0xB56` |
| `PROD_ARM1176JZF_S` | ARM1176JZF-S | `0xB76` |

### ARM Cortex-M

| Enum | Product | PPN |
| ---- | ------- | --- |
| `PROD_CORTEX_M0` | Cortex-M0 | `0xC20` |
| `PROD_CORTEX_M0_PLUS` | Cortex-M0+ | `0xC60` |
| `PROD_CORTEX_M1` | Cortex-M1 | `0xC21` |
| `PROD_CORTEX_M3` | Cortex-M3 | `0xC23` |
| `PROD_CORTEX_M4` | Cortex-M4 | `0xC24` |
| `PROD_CORTEX_M7` | Cortex-M7 | `0xC27` |
| `PROD_CORTEX_M23` | Cortex-M23 | `0xD20` |
| `PROD_CORTEX_M33` | Cortex-M33 | `0xD21` |
| `PROD_CORTEX_M35P` | Cortex-M35P | `0xD31` |
| `PROD_CORTEX_M55` | Cortex-M55 | `0xD50` |

### ARM Cortex-R

| Enum | Product | PPN |
| ---- | ------- | --- |
| `PROD_CORTEX_R4` | Cortex-R4 | `0xC14` |
| `PROD_CORTEX_R5` | Cortex-R5 | `0xC15` |
| `PROD_CORTEX_R7` | Cortex-R7 | `0xC17` |
| `PROD_CORTEX_R8` | Cortex-R8 | `0xC18` |
| `PROD_CORTEX_R52` | Cortex-R52 | `0xD13` |
| `PROD_CORTEX_R52_PLUS` | Cortex-R52+ | `0xD16` |
| `PROD_CORTEX_R82` | Cortex-R82 | `0xD15` |

### ARM Cortex-A (ARMv7)

| Enum | Product | PPN |
| ---- | ------- | --- |
| `PROD_CORTEX_A5` | Cortex-A5 | `0xC05` |
| `PROD_CORTEX_A7` | Cortex-A7 | `0xC07` |
| `PROD_CORTEX_A8` | Cortex-A8 | `0xC08` |
| `PROD_CORTEX_A9` | Cortex-A9 | `0xC09` |
| `PROD_CORTEX_A12` | Cortex-A12 | `0xC0D` |
| `PROD_CORTEX_A15` | Cortex-A15 | `0xC0F` |
| `PROD_CORTEX_A17` | Cortex-A17 | `0xC0E` |

### ARM Cortex-A (ARMv8+)

| Enum | Product | PPN |
| ---- | ------- | --- |
| `PROD_CORTEX_A32` | Cortex-A32 | `0xD01` |
| `PROD_CORTEX_A34` | Cortex-A34 | `0xD02` |
| `PROD_CORTEX_A35` | Cortex-A35 | `0xD04` |
| `PROD_CORTEX_A53` | Cortex-A53 | `0xD03` |
| `PROD_CORTEX_A55` | Cortex-A55 | `0xD05` |
| `PROD_CORTEX_A57` | Cortex-A57 | `0xD07` |
| `PROD_CORTEX_A65` | Cortex-A65 | `0xD06` |
| `PROD_CORTEX_A65AE` | Cortex-A65AE | `0xD43` |
| `PROD_CORTEX_A72` | Cortex-A72 | `0xD08` |
| `PROD_CORTEX_A73` | Cortex-A73 | `0xD09` |
| `PROD_CORTEX_A75` | Cortex-A75 | `0xD0A` |
| `PROD_CORTEX_A76` | Cortex-A76 | `0xD0B` |
| `PROD_CORTEX_A76AE` | Cortex-A76AE | `0xD0E` |
| `PROD_CORTEX_A77` | Cortex-A77 | `0xD0D` |
| `PROD_CORTEX_A78` | Cortex-A78 | `0xD41` |
| `PROD_CORTEX_A78AE` | Cortex-A78AE | `0xD42` |
| `PROD_CORTEX_A78C` | Cortex-A78C | `0xD4B` |
| `PROD_CORTEX_A510` | Cortex-A510 | `0xD46` |
| `PROD_CORTEX_A520` | Cortex-A520 | `0xD80` |
| `PROD_CORTEX_A710` | Cortex-A710 | `0xD47` |
| `PROD_CORTEX_A715` | Cortex-A715 | `0xD4D` |
| `PROD_CORTEX_A720` | Cortex-A720 | `0xD81` |
| `PROD_CORTEX_A725` | Cortex-A725 | `0xD87` |

### ARM Cortex-X

| Enum | Product | PPN |
| ---- | ------- | --- |
| `PROD_CORTEX_X1` | Cortex-X1 | `0xD44` |
| `PROD_CORTEX_X2` | Cortex-X2 | `0xD48` |
| `PROD_CORTEX_X3` | Cortex-X3 | `0xD4E` |
| `PROD_CORTEX_X4` | Cortex-X4 | `0xD82` |
| `PROD_CORTEX_X925` | Cortex-X925 | `0xD85` |

### ARM Neoverse

| Enum | Product | PPN |
| ---- | ------- | --- |
| `PROD_NEOVERSE_E1` | Neoverse E1 | `0xD4A` |
| `PROD_NEOVERSE_N1` | Neoverse N1 | `0xD0C` |
| `PROD_NEOVERSE_N2` | Neoverse N2 | `0xD49` |
| `PROD_NEOVERSE_N3` | Neoverse N3 | `0xD8E` |
| `PROD_NEOVERSE_V1` | Neoverse V1 | `0xD40` |
| `PROD_NEOVERSE_V2` | Neoverse V2 | `0xD4F` |
| `PROD_NEOVERSE_V3` | Neoverse V3 | `0xD84` |

### Qualcomm

| Enum | Product | PPN | Notes |
| ---- | ------- | --- | ----- |
| `PROD_QCOM_SCORPION` | Scorpion | `0x00F` | Snapdragon S1/S2 (ARMv7) |
| `PROD_QCOM_SCORPION_MP` | Scorpion MP | `0x02D` | Snapdragon S3/S4 multi-core (ARMv7) |
| `PROD_QCOM_KRAIT` | Krait | `0x04D` | Snapdragon 200/400 (ARMv7) |
| `PROD_QCOM_KRAIT_S4_PRO` | Krait S4 Pro | `0x06F` | Snapdragon 600/800 (ARMv7) |
| `PROD_QCOM_KRYO` | Kryo | `0x200` | Snapdragon 820/821 custom (ARMv8) |
| `PROD_QCOM_FALKOR_V1` | Falkor v1 | `0x800` | Centriq 2400 early silicon (server) |
| `PROD_QCOM_FALKOR` | Falkor | `0xC00` | Centriq 2400 (server) |
| `PROD_QCOM_KRYO_3XX_SILVER` | Kryo 3xx Silver | `0x803` | Snapdragon 845 little (semi-custom A55) |
| `PROD_QCOM_KRYO_4XX_GOLD` | Kryo 4xx Gold | `0x804` | Snapdragon 855/865 big (semi-custom A76) |
| `PROD_QCOM_KRYO_4XX_SILVER` | Kryo 4xx Silver | `0x805` | Snapdragon 855/865 little (semi-custom A55) |
| `PROD_QCOM_KRYO_5XX_GOLD` | Kryo 5xx Gold | `0x806` | Snapdragon 888 big (semi-custom A78) |
| `PROD_QCOM_KRYO_5XX_SILVER` | Kryo 5xx Silver | `0x807` | Snapdragon 888 little (semi-custom A55) |
| `PROD_QCOM_ORYON` | Oryon | `0x001` | Snapdragon X Elite (custom ARMv9) |

### Apple

| Enum | Product | PPN | Notes |
| ---- | ------- | --- | ----- |
| `PROD_APPLE_ICESTORM` | Icestorm | `0x022` | M1 efficiency core |
| `PROD_APPLE_FIRESTORM` | Firestorm | `0x023` | M1 performance core |
| `PROD_APPLE_ICESTORM_PRO` | Icestorm Pro | `0x024` | M1 Pro/Max efficiency core |
| `PROD_APPLE_FIRESTORM_PRO` | Firestorm Pro | `0x025` | M1 Pro/Max performance core |
| `PROD_APPLE_ICESTORM_MAX` | Icestorm Max | `0x028` | M1 Ultra efficiency core |
| `PROD_APPLE_FIRESTORM_MAX` | Firestorm Max | `0x029` | M1 Ultra performance core |
| `PROD_APPLE_BLIZZARD` | Blizzard | `0x032` | M2 efficiency core |
| `PROD_APPLE_AVALANCHE` | Avalanche | `0x033` | M2 performance core |

> [!NOTE]
> Apple A-series identifiers (A7 through A13) are derived from reverse engineering and Asahi Linux work. They are not in the table above and are not matched by the library. The PPNs listed for M1 and M2 are confirmed via mainline kernel sources.

### Samsung Mongoose

| Enum | Product | PPN | SoC |
| ---- | ------- | --- | --- |
| `PROD_SAMSUNG_M1` | Mongoose M1 | `0x001` | Exynos 8890 (2016) |
| `PROD_SAMSUNG_M2` | Mongoose M2 | `0x002` | Exynos 8895 (2017) |
| `PROD_SAMSUNG_M3` | Mongoose M3 | `0x003` | Exynos 9810 (2018) |
| `PROD_SAMSUNG_M4` | Mongoose M4 | `0x004` | Exynos 9820 (2019) |
| `PROD_SAMSUNG_M5` | Mongoose M5 | `0x005` | Exynos 990 (2020) |

### Other implementors

| Enum | Product | Implementor | PPN |
| ---- | ------- | ----------- | --- |
| `PROD_CAVIUM_THUNDERX` | ThunderX | Cavium | `0x0A1` |
| `PROD_CAVIUM_THUNDERX_81XX` | ThunderX CN81xx | Cavium | `0x0A2` |
| `PROD_CAVIUM_THUNDERX_83XX` | ThunderX CN83xx | Cavium | `0x0A3` |
| `PROD_CAVIUM_THUNDERX2` | ThunderX2 | Cavium | `0x0AF` |
| `PROD_NVIDIA_DENVER` | Denver 2 | NVIDIA | `0x003` |
| `PROD_NVIDIA_CARMEL` | Carmel | NVIDIA | `0x004` |
| `PROD_FUJITSU_A64FX` | A64FX | Fujitsu | `0x001` |
| `PROD_HISI_TSV110` | TSV110 / Kunpeng 920 | HiSilicon | `0xD01` |
| `PROD_APM_POTENZA` | X-Gene | APM | `0x000` |

<br>

## Architecture table

| Enum | String | Notes |
| ---- | ------ | ----- |
| `ARCH_UNKNOWN` | `UNKNOWN` | Default when the arch cannot be determined |
| `ARCH_ARMv1` | `ARMv1` | |
| `ARCH_ARMv2` | `ARMv2` | |
| `ARCH_ARMv2a` | `ARMv2a` | ARM3 |
| `ARCH_ARMv3` | `ARMv3` | ARM600 series and base ARM7 |
| `ARCH_ARMv3M` | `ARMv3M` | |
| `ARCH_ARMv4` | `ARMv4` | |
| `ARCH_ARMv4xM` | `ARMv4xM` | |
| `ARCH_ARMv4T` | `ARMv4T` | ARM7 with Thumb support |
| `ARCH_ARMv4TxM` | `ARMv4TxM` | |
| `ARCH_ARMv5` | `ARMv5` | |
| `ARCH_ARMv5xM` | `ARMv5xM` | |
| `ARCH_ARMv5T` | `ARMv5T` | |
| `ARCH_ARMv5TxM` | `ARMv5TxM` | |
| `ARCH_ARMv5TE` | `ARMv5TE` | |
| `ARCH_ARMv5TExP` | `ARMv5TExP` | |
| `ARCH_ARMv5TEJ` | `ARMv5TEJ` | |
| `ARCH_ARMv6` | `ARMv6` | |
| `ARCH_ARMv6T2` | `ARMv6T2` | |
| `ARCH_ARMv6Z` | `ARMv6Z` | |
| `ARCH_ARMv6K` | `ARMv6K` | |
| `ARCH_ARMv6_M` | `ARMv6-M` | |
| `ARCH_ARMv7_A` | `ARMv7-A` | |
| `ARCH_ARMv7_M` | `ARMv7-M` | |
| `ARCH_ARMv7_R` | `ARMv7-R` | |
| `ARCH_ARMv7E_M` | `ARMv7E-M` | |
| `ARCH_ARMv8_A` | `ARMv8-A` | |
| `ARCH_ARMv8_R` | `ARMv8-R` | |
| `ARCH_ARMv8_M_BASELINE` | `ARMv8-M Baseline` | |
| `ARCH_ARMv8_M_MAINLINE` | `ARMv8-M Mainline` | |
| `ARCH_ARMv8_1_M_MAINLINE` | `ARMv8.1-M Mainline` | |
| `ARCH_ARMv8_2_A` | `ARMv8.2-A` | |
| `ARCH_ARMv8_3_A` | `ARMv8.3-A` | |
| `ARCH_ARMv8_4_A` | `ARMv8.4-A` | |
| `ARCH_ARMv8_5_A` | `ARMv8.5-A` | |
| `ARCH_ARMv8_6_A` | `ARMv8.6-A` | |
| `ARCH_ARMv9_A` | `ARMv9-A` | |
| `ARCH_ARMv9_2_A` | `ARMv9.2-A` | |

<br>

# Platform notes

The library uses compile-time guards to handle cross-platform behavior cleanly.

- **x86/x86_64**: All fetch functions return `0`, `false`, `IMPL_UNKNOWN`, `PROD_UNKNOWN`, or `ARCH_UNKNOWN` as appropriate. `llarm_cpu_fetch_bits()` is not compiled at all. The library will not crash on x86, but it will not produce useful data either.
- **ARM (32-bit and 64-bit)**: Full functionality. The MIDR is read via the `mrc p15, 0, %0, c0, c0, 0` inline assembly instruction.
- **Other architectures**: Treated the same as x86. The `is_x86` guard defaults to not defined, so the ARM path compiles. This may cause build errors on architectures that do not support the `mrc` instruction. Guard your include accordingly if targeting non-ARM, non-x86 platforms.