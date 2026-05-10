AS      := arm-none-eabi-as
LD      := arm-none-eabi-ld
OBJCOPY := arm-none-eabi-objcopy
ASFLAGS := -march=armv4t
LDSCRIPT := ../linker.ld

SRCS := $(shell find . -name "*.s")
BINS := $(SRCS:.s=.bin)

.PHONY: all clean

all: $(BINS)

%.bin: %.s
	$(AS) $(ASFLAGS) -o $(@:.bin=.o) $<
	$(LD) -T $(LDSCRIPT) -o $(@:.bin=.elf) $(@:.bin=.o)
	$(OBJCOPY) -O binary $(@:.bin=.elf) $@
	@rm -f $(@:.bin=.o) $(@:.bin=.elf)

clean:
	find . -name "*.bin" -delete
	find . -name "*.o" -delete
	find . -name "*.elf" -delete
