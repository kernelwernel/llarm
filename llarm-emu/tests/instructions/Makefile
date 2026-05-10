AS      := arm-none-eabi-as
LD      := arm-none-eabi-ld
OBJCOPY := arm-none-eabi-objcopy
LDSCRIPT := ../linker.ld

# Flags per instruction-set level
F_V4T  := -march=armv4t
F_V5T  := -march=armv5t
F_V5TE := -march=armv5te
F_VFP  := -march=armv5te -mfpu=vfp

BINS := \
    math/math_test.bin \
    logic/logic_test.bin \
    movement/movement_test.bin \
    multiply/multiply_test.bin \
    branching/branching_test.bin \
    load_store/load_store_test.bin \
    misc/misc_test.bin \
    dsp/dsp_test.bin \
    vfp/vfp_test.bin

.PHONY: all clean

all: $(BINS)

# Helper: assemble → link → strip to raw binary
define build
	$(AS) $(2) -o $(@:.bin=.o) $<
	$(LD) -T $(LDSCRIPT) -o $(@:.bin=.elf) $(@:.bin=.o)
	$(OBJCOPY) -O binary $(@:.bin=.elf) $@
	@rm -f $(@:.bin=.o) $(@:.bin=.elf)
endef

# ARMv4T
math/math_test.bin:       math/math_test.s       ; $(call build,$<,$(F_V4T))
movement/movement_test.bin: movement/movement_test.s ; $(call build,$<,$(F_V4T))
multiply/multiply_test.bin: multiply/multiply_test.s ; $(call build,$<,$(F_V4T))
branching/branching_test.bin: branching/branching_test.s ; $(call build,$<,$(F_V4T))
load_store/load_store_test.bin: load_store/load_store_test.s ; $(call build,$<,$(F_V4T))
misc/misc_test.bin:       misc/misc_test.s       ; $(call build,$<,$(F_V5T))

# ARMv5T (CLZ)
logic/logic_test.bin:     logic/logic_test.s     ; $(call build,$<,$(F_V5T))

# ARMv5TE (DSP extensions)
dsp/dsp_test.bin:         dsp/dsp_test.s         ; $(call build,$<,$(F_V5TE))

# ARMv5TE + VFP
vfp/vfp_test.bin:         vfp/vfp_test.s         ; $(call build,$<,$(F_VFP))

clean:
	find . -name "*.bin" -delete
	find . -name "*.o"   -delete
	find . -name "*.elf" -delete
