# llarm::cpu C++ Wrapper Documentation

## Contents
- [Overview](#overview)
- [`llarm::cpu::fetch_midr()`](#llarmcpufetch_midr)
- [`llarm::cpu::is_pre_arm7()`, `llarm::cpu::is_arm7()`, and `llarm::cpu::is_post_arm7()`](#llarmcpuis_pre_arm7-llarmcpuis_arm7-and-llarmcpuis_post_arm7)
- [`llarm::cpu::fetch_revision()`](#llarmcpufetch_revision)
- [`llarm::cpu::fetch_ppn()`](#llarmcpufetch_ppn)
- [`llarm::cpu::fetch_variant()`](#llarmcpufetch_variant)
- [`llarm::cpu::fetch_implementor()`](#llarmcpufetch_implementor)
- [`llarm::cpu::fetch_implementor_string()`](#llarmcpufetch_implementor_string)
- [`llarm::cpu::fetch_product()`](#llarmcpufetch_product)
- [`llarm::cpu::fetch_product_string()`](#llarmcpufetch_product_string)
- [`llarm::cpu::fetch_arch()`](#llarmcpufetch_arch)
- [`llarm::cpu::fetch_arch_string()`](#llarmcpufetch_arch_string)

<br>

## Overview

The `llarm::cpu` namespace is a thin C++ wrapper around the `llarm-cpu.h` C API. Every function in this namespace is `inline` and delegates directly to its C counterpart with no added logic or overhead.

The wrapper exists to let C++ code use the library without the `llarm_cpu_` prefix and without polluting the global namespace.

```cpp
int main() {
    // C++ style
    const char* impl = llarm::cpu::fetch_implementor_string();

    // Equivalent C style
    const char* impl2 = llarm_cpu_fetch_implementor_string();
}
```

For documentation on the enum types (`implementor`, `product`, `arch`) and platform behavior, refer to the [C API documentation](llarm_cpu_docs.md). The enums are defined in `llarm-cpu.h` and are shared between both interfaces.

<br>

## `llarm::cpu::fetch_midr()`

Returns an `unsigned int` containing the raw MIDR value read from the CPU. Wraps `llarm_cpu_fetch_midr()`.

```cpp
#include "llarm-cpu.hpp"

int main() {
    unsigned int midr = llarm::cpu::fetch_midr();
    std::cout << "MIDR: " << std::hex << midr << "\n";
}
```

> [!NOTE]
> On x86 platforms, this function always returns `0`. All dependent functions return neutral/unknown values as a result.

<br>

## `llarm::cpu::is_pre_arm7()`, `llarm::cpu::is_arm7()`, and `llarm::cpu::is_post_arm7()`

Returns a `bool` indicating whether its release date relative to the ARM7 architecture.

```cpp
#include "llarm-cpu.hpp"

int main() {
    if (llarm::cpu::is_arm7()) {
        std::cout << "This CPU is ARM7.\n";
    }

    if (llarm::cpu::is_post_arm7()) {
        std::cout << "This CPU is newer than ARM7.\n";
    }

    if (llarm::cpu::is_pre_arm7()) {
        std::cout << "This CPU is older than ARM7.\n";
    }
}
```

<br>

## `llarm::cpu::fetch_revision()`

Returns an `unsigned int` representing the revision field of the MIDR (bits 3:0). This is the minor stepping of the CPU, distinct from the variant.

## `llarm::cpu::fetch_ppn()`

Returns an `unsigned int` representing the Primary Part Number (PPN). This is the main identifier used to distinguish specific CPU products within a given implementor.

<br>

## `llarm::cpu::fetch_variant()`

Returns an `unsigned int` for the variant field of the MIDR. This represents the major stepping of the CPU.

<br>

## `llarm::cpu::fetch_implementor()`

Returns an `enum implementor` identifying the company that manufactured the CPU. Wraps `llarm_cpu_fetch_implementor()`.

```cpp
#include "llarm-cpu.hpp"

int main() {
    enum implementor impl = llarm::cpu::fetch_implementor();

    if (impl == IMPL_APPLE) {
        // Apple Silicon path
    } else if (impl == IMPL_QUALCOMM) {
        // Qualcomm Snapdragon path
    }
}
```

If the implementor byte does not match any known value, the function returns `IMPL_UNKNOWN`. See the [implementor table](c_documentation.md#implementor-table) for all supported values.

<br>

## `llarm::cpu::fetch_implementor_string()`

Returns a `const char*` name for the current CPU's implementor.

```cpp
std::cout << "Implementor: " << llarm::cpu::fetch_implementor_string() << "\n";
// example output: "APPLE"
```

<br>

## `llarm::cpu::fetch_product()`

Returns an `enum product` identifying the specific CPU core. Wraps `llarm_cpu_fetch_product()`.

```cpp
#include "llarm-cpu.hpp"

int main() {
    enum product prod = llarm::cpu::fetch_product();

    switch (prod) {
        case PROD_CORTEX_A76:
            std::cout << "Cortex-A76 detected\n";
            break;
        case PROD_APPLE_FIRESTORM:
            std::cout << "Apple M1 performance core detected\n";
            break;
        case PROD_UNKNOWN:
        default:
            std::cout << "Product not recognised\n";
            break;
    }
}
```

See the [product table](c_documentation.md#product-table) for all supported products.

> [!IMPORTANT]
> A result of `PROD_UNKNOWN` does not mean the CPU is invalid. It means the specific part is not in the library's database. This is common for very old pre-ARM7 parts and newer unreleased silicon, but the lib will do its best to be as up-to-date as possible.

<br>

## `llarm::cpu::fetch_product_string()`

Returns a `const char*` string for a given `enum product`. Takes an explicit product argument. Overloads are available:

```cpp
const char* fetch_product_string();
const char* fetch_product_string(const enum product);
```

```cpp
enum product prod = llarm::cpu::fetch_product();
const char* name  = llarm::cpu::fetch_product_string(prod);
// or just use llarm::cpu::fetch_product_string()

std::cout << "Product: " << name << "\n";
// example output: "CORTEX_A76"
```

<br>

## `llarm::cpu::fetch_arch()`

Returns an `enum arch` identifying the ARM architecture version of the current CPU.
```cpp
#include "llarm-cpu.hpp"

int main() {
    enum arch a = llarm::cpu::fetch_arch();

    if (a == ARCH_ARMv8_A) {
        std::cout << "64-bit capable ARMv8-A CPU\n";
    }
}
```

See the [architecture table](c_documentation.md#architecture-table) for all supported archs.

<br>

## `llarm::cpu::fetch_arch_string()`

Returns a `const char*` string for a given `enum arch`. Takes an explicit arch argument, overloads are available:

```cpp
const char* fetch_arch_string();
const char* fetch_arch_string(const enum arch); 
```

```cpp
enum arch a = llarm::cpu::fetch_arch();
std::cout << "Architecture: " << llarm::cpu::fetch_arch_string(a) << "\n";
// or just use llarm::cpu::fetch_arch_string()

// example output: "ARMv8-A"
```