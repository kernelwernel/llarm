
# llarm::as Documentation

## Contents
- [Overview](#overview)
- [Types](#types)
- [Settings](#settings)
- [`llarm::as::identify_arm()`](#llarmAsidentify_arm)
- [`llarm::as::identify_arm_string()`](#llarmAsidentify_arm_string)
- [`llarm::as::identify_thumb()`](#llarmAsidentify_thumb)
- [`llarm::as::identify_thumb_string()`](#llarmAsidentify_thumb_string)
- [`llarm::as::identify_shifter()`](#llarmAsidentify_shifter)
- [`llarm::as::disassemble_arm()`](#llarmAsdisassemble_arm)
- [`llarm::as::disassemble_thumb()`](#llarmAsdisassemble_thumb)
- [`llarm::as::assemble_arm()`](#llarmAsassemble_arm)
- [`llarm::as::assemble_thumb()`](#llarmAsassemble_thumb)
- [`llarm::as::is_arm_instruction_valid()`](#llarmAsis_arm_instruction_valid)
- [`llarm::as::is_thumb_instruction_valid()`](#llarmAsis_thumb_instruction_valid)
- [`llarm::as::arm_id_to_string()`](#llarmAsarm_id_to_string)
- [`llarm::as::thumb_id_to_string()`](#llarmAsthumb_id_to_string)
- [`llarm::as::shifter_id_to_string()`](#llarmAsshifter_id_to_string)
- [`llarm::as::code_to_shifter_string()`](#llarmAscode_to_shifter_string)

<br>

## Overview

The `llarm::as` namespace provides ARM assembler and disassembler functionality. It handles both ARM and Thumb instruction sets, along with shifter operand identification.

Functions come in two forms where applicable: one that takes a raw binary instruction (`u32`) and one that takes a string mnemonic (`std::string`).

<br>

## Types

| Type | Description |
| ---- | ----------- |
| `arm_id` | Identifies a specific ARM instruction |
| `thumb_id` | Identifies a specific Thumb instruction |
| `shifter_id` | Identifies a specific shifter operand |
| `shifter_category` | Categorises the type of shifter operand |
| `settings` | Configuration for disassembly output |

<br>

## Settings

Disassembly functions accept an optional `settings` argument. If none is provided, `default_settings()` is used.

```cpp
#include "llarm-as.hpp"

int main() {
    // use default settings
    std::string result = llarm::as::disassemble_arm(0xE0821003);

    // use custom settings
    llarm::as::settings config = llarm::as::default_settings();
    std::string result2 = llarm::as::disassemble_arm(0xE0821003, 0, config);
}
```

You can also reassign `default_settings` to a custom function that returns your preferred configuration:

```cpp
llarm::as::settings my_settings() {
    llarm::as::settings s = llarm::as::default_settings();
    // modify s here
    return s;
}

llarm::as::default_settings = &my_settings;
```


| Field | Default | Description |
| ----- | ------- | ----------- |
| `hex` | `true` | Format immediate values and offsets greater than 9 in hexadecimal. When `false`, all immediates are printed in decimal. |
| `register_alias` | `true` | Use standard ARM register aliases (e.g. `SP`, `LR`, `PC`, `FP`, `IP`). When `false`, raw register numbers are used (`R13`, `R14`, `R15`, etc.). |
| `capitals` | `true` | Emit the entire disassembly in uppercase. When `false`, output is lowercased. |
| `simplify` | `false` | Omit redundant or implied suffixes. For example, `LDMIA` becomes `LDM` and default addressing mode indicators are dropped. |
| `remove_nulls` | `true` | Omit zero offsets from memory addressing modes. `[R0, #0]` is printed as `[R0]`. When `false`, zero offsets are shown explicitly. |
| `gcc_convention` | `false` | Use GCC-style dot-separated condition codes (e.g. `MOV.EQ`) instead of the traditional suffix form (e.g. `MOVEQ`). |
| `cond_always_suffix` | `true` | When an instruction sets flags (S suffix) and has a condition code, place S before the condition (e.g. `MLASEQ`). When `false`, the condition comes first (e.g. `MLAEQS`). |
| `explicit_operands` | `true` | Show all operands explicitly, including those that are implied by convention. For example, `LDRD` shows both destination registers even when the second is implicit. |
| `strict_compliance` | `true` | Return `UNDEFINED` for instructions that violate ARM architecture rules (e.g. `LDRD` with an odd-numbered destination register). When `false`, those instructions are disassembled anyway. |
| `equivalent_alias` | `true` | Substitute canonical instruction aliases where applicable (e.g. emit `LSL R0, R1, #2` rather than the equivalent `MOV` form with a shift operand). |
| `explicit_rotation` | `false` | Reserved for future use. Intended to control whether the rotation amount in rotated immediates is shown explicitly. Currently has no effect. |
| `extra_space` | `false` | Add spaces inside register list braces (e.g. `{ R0-R3 }` instead of `{R0-R3}`). |


<br>

# ARM

## `llarm::as::identify_arm()`

Identifies an ARM instruction and returns an `arm_id`. Accepts either a raw binary instruction or a string mnemonic.

```cpp
#include "llarm-as.hpp"

int main() {
    // from binary
    llarm::as::arm_id id = llarm::as::identify_arm(0xE0821003);

    // from string
    llarm::as::arm_id id2 = llarm::as::identify_arm("ADD R1, R2, R3");
}
```

<br>

## `llarm::as::identify_arm_string()`

Identifies an ARM instruction from a raw binary instruction and returns its mnemonic as a `std::string`. This is a convenience function that combines `identify_arm()` and `arm_id_to_string()`.

```cpp
std::string mnemonic = llarm::as::identify_arm_string(0xE0821003);
std::cout << mnemonic << "\n";
// example output: "ADD"
```

<br>

## `llarm::as::identify_shifter()`

Identifies a shifter operand and returns a `shifter_id`. Has three overloads.

```cpp
// from binary
llarm::as::shifter_id id = llarm::as::identify_shifter(0xE0821103);

// from string
llarm::as::shifter_id id2 = llarm::as::identify_shifter("R3, LSL #2");

// from binary with a known category, which can narrow the result
llarm::as::shifter_id id3 = llarm::as::identify_shifter(
    llarm::as::shifter_category::/* your category here */,
    0xE0821103
);
```

<br>

## `llarm::as::disassemble_arm()`

Disassembles a raw ARM binary instruction into a `std::string`. Accepts an optional program counter value and settings.

```cpp
#include "llarm-as.hpp"

int main() {
    // basic usage
    std::string result = llarm::as::disassemble_arm(0xE0821003);
    std::cout << result << "\n";
    // example output: "ADD R1, R2, R3"

    // with PC (used for PC-relative instructions like branches and LDR literals)
    std::string result2 = llarm::as::disassemble_arm(0xEA000005, 0x1000);
    std::cout << result2 << "\n";
    // example output: "B #0x101C"
}
```
<br>

## `llarm::as::assemble_arm()`

Assembles an ARM mnemonic string into a raw `u32` binary instruction. Accepts an optional program counter value for PC-relative instructions.

```cpp
#include "llarm-as.hpp"

int main() {
    u32 code = llarm::as::assemble_arm("ADD R1, R2, R3");
    std::cout << std::hex << code << "\n";
    // example output: "e0821003"

    // with PC for branch instructions
    u32 branch = llarm::as::assemble_arm("B #0x101C", 0x1000);
}
```

<br>

## `llarm::as::is_arm_instruction_valid()`

Returns a `bool` indicating whether the given ARM instruction is valid. Accepts either a raw binary instruction or a string mnemonic.

```cpp
// from binary
if (llarm::as::is_arm_instruction_valid(0xE0821003)) {
    std::cout << "Valid ARM instruction\n";
}

// from string
if (llarm::as::is_arm_instruction_valid("ADD R1, R2, R3")) {
    std::cout << "Valid ARM instruction\n";
}
```

<br>

## `llarm::as::arm_id_to_string()`

Returns a `std::string` mnemonic name for a given `arm_id`.

```cpp
llarm::as::arm_id id = llarm::as::identify_arm(0xE0821003);
std::cout << llarm::as::arm_id_to_string(id) << "\n";
// example output: "ADD"
```

<br>

## ARM shifters

## `llarm::as::shifter_id_to_string()`

Returns a `std::string` name for a given `shifter_id`.

```cpp
llarm::as::shifter_id id = llarm::as::identify_shifter(0xE0821103);
std::cout << llarm::as::shifter_id_to_string(id) << "\n";
// example output: "LSL"
```

<br>

## `llarm::as::code_to_shifter_string()`

Returns a `std::string` representing the full shifter operand for a given raw binary instruction, including the register and shift amount.

```cpp
std::string shifter = llarm::as::code_to_shifter_string(0xE0821103);
std::cout << shifter << "\n";
// example output: "R3, LSL #2"
```


<br>

# Thumb

## `llarm::as::identify_thumb()`

Identifies a Thumb instruction and returns a `thumb_id`. Accepts either a raw binary instruction or a string mnemonic.

```cpp
// from binary
llarm::as::thumb_id id = llarm::as::identify_thumb(0x1888);

// from string
llarm::as::thumb_id id2 = llarm::as::identify_thumb("ADD R0, R1, R2");
```


<br>

## `llarm::as::disassemble_thumb()`

Disassembles a raw Thumb binary instruction into a `std::string`. Accepts an optional program counter value and settings.

```cpp
#include "llarm-as.hpp"

int main() {
    // basic usage
    std::string result = llarm::as::disassemble_thumb(0x1888);
    std::cout << result << "\n";
    // example output: "ADD R0, R1, R2"

    // with PC
    std::string result2 = llarm::as::disassemble_thumb(0xE005, 0x1000);
}
```


<br>

## `llarm::as::assemble_thumb()`

Assembles a Thumb mnemonic string into a raw `u32` binary instruction. Accepts an optional program counter value for PC-relative instructions.

```cpp
u32 code = llarm::as::assemble_thumb("ADD R0, R1, R2");
std::cout << std::hex << code << "\n";
// example output: "1888"
```


<br>

## `llarm::as::is_thumb_instruction_valid()`

Returns a `bool` indicating whether the given Thumb instruction is valid. Accepts either a raw binary instruction or a string mnemonic.

```cpp
// from binary
if (llarm::as::is_thumb_instruction_valid(0x1888)) {
    std::cout << "Valid Thumb instruction\n";
}

// from string
if (llarm::as::is_thumb_instruction_valid("ADD R0, R1, R2")) {
    std::cout << "Valid Thumb instruction\n";
}
```

<br>

## `llarm::as::thumb_id_to_string()`

Returns a `std::string` mnemonic name for a given `thumb_id`.

```cpp
llarm::as::thumb_id id = llarm::as::identify_thumb(0x1888);
std::cout << llarm::as::thumb_id_to_string(id) << "\n";
// example output: "ADD"
```

<br>

## `llarm::as::identify_thumb_string()`

Identifies a Thumb instruction from a raw binary instruction and returns its mnemonic as a `std::string`. This is a convenience function that combines `identify_thumb()` and `thumb_id_to_string()`.

```cpp
std::string mnemonic = llarm::as::identify_thumb_string(0x1888);
std::cout << mnemonic << "\n";
// example output: "ADD"
```

# Tables

### `arm_id`

| | | | |
| - | - | - | - |
| `UNKNOWN` | `UNDEFINED` | `NOP` | `ADC` |
| `ADD` | `RSB` | `BIC` | `RSC` |
| `SBC` | `SUB` | `CMN` | `AND` |
| `CMP` | `EOR` | `ORR` | `TEQ` |
| `TST` | `MOV` | `MVN` | `B` |
| `BL` | `SWI` | `LDM1` | `LDM2` |
| `LDM3` | `LDR` | `LDRB` | `LDRBT` |
| `LDRT` | `STM1` | `STM2` | `STR` |
| `STRB` | `STRBT` | `STRT` | `CMNP` |
| `CMPP` | `TEQP` | `TSTP` | `CDP` |
| `LDC` | `MCR` | `MRC` | `STC` |
| `SWP` | `SWPB` | `MLA` | `MUL` |
| `SMLAL` | `SMULL` | `UMLAL` | `UMULL` |
| `MRS` | `MSR_IMM` | `MSR_REG` | `LDRH` |
| `LDRSB` | `LDRSH` | `STRH` | `BX` |
| `BKPT` | `BLX1` | `BLX2` | `CLZ` |
| `CDP2` | `LDC2` | `MCR2` | `MRC2` |
| `STC2` | `MCRR` | `MRRC` | `PLD` |
| `STRD` | `LDRD` | `QADD` | `QDADD` |
| `QDSUB` | `QSUB` | `SMLAXY` | `SMLALXY` |
| `SMLAWY` | `SMULXY` | `SMULWY` | |
| **VFP single-precision** | | | |
| `FABSS` | `FADDS` | `FCMPES` | `FCMPEZS` |
| `FCMPS` | `FCMPZS` | `FCPYS` | `FDIVS` |
| `FLDMS` | `FLDMX` | `FLDS` | `FMACS` |
| `FMRS` | `FMRX` | `FMSCS` | `FMSR` |
| `FMSTAT` | `FMULS` | `FMXR` | `FNEGS` |
| `FNMACS` | `FNMSCS` | `FNMULS` | `FSITOS` |
| `FSQRTS` | `FSTMS` | `FSTMX` | `FSTS` |
| `FSUBS` | `FTOSIS` | `FTOUIS` | `FUITOS` |
| **VFP double-precision** | | | |
| `FABSD` | `FADDD` | `FCMPD` | `FCMPED` |
| `FCMPEZD` | `FCMPZD` | `FCPYD` | `FCVTDS` |
| `FCVTSD` | `FDIVD` | `FLDD` | `FLDMD` |
| `FMACD` | `FMDHR` | `FMDLR` | `FMRDL` |
| `FMRDH` | `FMSCD` | `FMULD` | `FNEGD` |
| `FNMACD` | `FNMSCD` | `FNMULD` | `FSITOD` |
| `FSQRTD` | `FSTD` | `FSTMD` | `FSUBD` |
| `FTOSID` | `FTOUID` | `FUITOD` | |

<br>

### `thumb_id`

| | | | |
| - | - | - | - |
| `UNKNOWN` | `UNDEFINED` | `ADC` | `ADD1` |
| `ADD2` | `ADD3` | `ADD4` | `ADD5` |
| `ADD6` | `ADD7` | `SBC` | `SUB1` |
| `SUB2` | `SUB3` | `SUB4` | `MUL` |
| `AND` | `ASR1` | `ASR2` | `BIC` |
| `EOR` | `LSL1` | `LSL2` | `LSR1` |
| `LSR2` | `NEG` | `ORR` | `ROR` |
| `TST` | `CMN` | `CMP1` | `CMP2` |
| `CMP3` | `MOV1` | `MOV2` | `MOV3` |
| `MVN` | `B1` | `B2` | `BL` |
| `BLX1` | `BL_BLX1_PREFIX` | `BLX2` | `BX` |
| `NOP` | `BKPT` | `SWI` | `LDMIA` |
| `LDR1` | `LDR2` | `LDR3` | `LDR4` |
| `LDRB1` | `LDRB2` | `LDRH1` | `LDRH2` |
| `LDRSB` | `LDRSH` | `POP` | `PUSH` |
| `STMIA` | `STR1` | `STR2` | `STR3` |
| `STRB1` | `STRB2` | `STRH1` | `STRH2` |

<br>

### `shifter_id`

| Value | Description |
| ----- | ----------- |
| `UNKNOWN` | Unrecognised shifter |
| `NONE` | No shifter operand |
| **Data processing** | |
| `DATA_IMM` | Rotated immediate |
| `DATA_RRX` | Register with RRX shift |
| `DATA_REG` | Plain register |
| `DATA_IMM_LSL` | Register shifted left by immediate |
| `DATA_IMM_LSR` | Register shifted right (logical) by immediate |
| `DATA_IMM_ASR` | Register shifted right (arithmetic) by immediate |
| `DATA_IMM_ROR` | Register rotated right by immediate |
| `DATA_REG_LSL` | Register shifted left by register |
| `DATA_REG_LSR` | Register shifted right (logical) by register |
| `DATA_REG_ASR` | Register shifted right (arithmetic) by register |
| `DATA_REG_ROR` | Register rotated right by register |
| **Load/store** | |
| `LS_IMM` | Immediate offset |
| `LS_IMM_PRE` | Immediate offset, pre-indexed |
| `LS_IMM_POST` | Immediate offset, post-indexed |
| `LS_REG` | Register offset |
| `LS_REG_PRE` | Register offset, pre-indexed |
| `LS_REG_POST` | Register offset, post-indexed |
| `LS_SCALED_LSL` | Scaled register offset, LSL |
| `LS_SCALED_LSR` | Scaled register offset, LSR |
| `LS_SCALED_ASR` | Scaled register offset, ASR |
| `LS_SCALED_ROR` | Scaled register offset, ROR |
| `LS_SCALED_RRX` | Scaled register offset, RRX |
| `LS_SCALED_PRE_LSL` | Scaled register offset pre-indexed, LSL |
| `LS_SCALED_PRE_LSR` | Scaled register offset pre-indexed, LSR |
| `LS_SCALED_PRE_ASR` | Scaled register offset pre-indexed, ASR |
| `LS_SCALED_PRE_ROR` | Scaled register offset pre-indexed, ROR |
| `LS_SCALED_PRE_RRX` | Scaled register offset pre-indexed, RRX |
| `LS_SCALED_POST_LSL` | Scaled register offset post-indexed, LSL |
| `LS_SCALED_POST_LSR` | Scaled register offset post-indexed, LSR |
| `LS_SCALED_POST_ASR` | Scaled register offset post-indexed, ASR |
| `LS_SCALED_POST_ROR` | Scaled register offset post-indexed, ROR |
| `LS_SCALED_POST_RRX` | Scaled register offset post-indexed, RRX |
| **Load/store miscellaneous** | |
| `LS_MISC_IMM` | Miscellaneous immediate offset |
| `LS_MISC_IMM_PRE` | Miscellaneous immediate offset, pre-indexed |
| `LS_MISC_IMM_POST` | Miscellaneous immediate offset, post-indexed |
| `LS_MISC_REG` | Miscellaneous register offset |
| `LS_MISC_REG_PRE` | Miscellaneous register offset, pre-indexed |
| `LS_MISC_REG_POST` | Miscellaneous register offset, post-indexed |
| **Load/store multiple** | |
| `LS_MUL_INC_AFTER` | Increment after (IA) |
| `LS_MUL_INC_BEFORE` | Increment before (IB) |
| `LS_MUL_DEC_AFTER` | Decrement after (DA) |
| `LS_MUL_DEC_BEFORE` | Decrement before (DB) |
| **Coprocessor load/store** | |
| `LS_COPROC_IMM` | Coprocessor immediate offset |
| `LS_COPROC_IMM_PRE` | Coprocessor immediate offset, pre-indexed |
| `LS_COPROC_IMM_POST` | Coprocessor immediate offset, post-indexed |
| `LS_COPROC_UNINDEXED` | Coprocessor unindexed |
| **VFP single-precision** | |
| `VFP_SINGLE` | Single-precision dyadic |
| `VFP_SINGLE_SCALAR` | Single-precision scalar dyadic |
| `VFP_SINGLE_MIXED` | Single-precision mixed scalar/vector |
| `VFP_SINGLE_VECTOR` | Single-precision vector dyadic |
| `VFP_SINGLE_MONADIC` | Single-precision monadic |
| `VFP_SINGLE_MONADIC_SCALAR_TO_SCALAR` | Single-precision monadic, scalar → scalar |
| `VFP_SINGLE_MONADIC_SCALAR_TO_VECTOR` | Single-precision monadic, scalar → vector |
| `VFP_SINGLE_MONADIC_VECTOR_TO_VECTOR` | Single-precision monadic, vector → vector |
| **VFP double-precision** | |
| `VFP_DOUBLE` | Double-precision dyadic |
| `VFP_DOUBLE_SCALAR` | Double-precision scalar dyadic |
| `VFP_DOUBLE_MIXED` | Double-precision mixed scalar/vector |
| `VFP_DOUBLE_VECTOR` | Double-precision vector dyadic |
| `VFP_DOUBLE_MONADIC` | Double-precision monadic |
| `VFP_DOUBLE_MONADIC_SCALAR_TO_SCALAR` | Double-precision monadic, scalar → scalar |
| `VFP_DOUBLE_MONADIC_SCALAR_TO_VECTOR` | Double-precision monadic, scalar → vector |
| `VFP_DOUBLE_MONADIC_VECTOR_TO_VECTOR` | Double-precision monadic, vector → vector |
| **VFP load/store multiple** | |
| `VFP_LS_MUL` | VFP load/store multiple |
| `VFP_LS_MUL_UNINDEXED` | VFP load/store multiple, unindexed |
| `VFP_LS_MUL_INC` | VFP load/store multiple, increment |
| `VFP_LS_MUL_DEC` | VFP load/store multiple, decrement |
| `VFP_LS_MUL_SPECIAL` | VFP load/store multiple, special |

<br>

### `shifter_category`

| Value | Description |
| ----- | ----------- |
| `DATA` | Data processing shifter operand |
| `LS` | Load/store offset |
| `LS_MISC` | Miscellaneous load/store offset |
| `LS_MUL` | Load/store multiple addressing mode |
| `LS_COPROC` | Coprocessor load/store offset |
| `VFP_SINGLE` | VFP single-precision operand |
| `VFP_SINGLE_MONADIC` | VFP single-precision monadic operand |
| `VFP_DOUBLE` | VFP double-precision operand |
| `VFP_DOUBLE_MONADIC` | VFP double-precision monadic operand |
| `VFP_LS_MUL` | VFP load/store multiple addressing mode |

<br>
