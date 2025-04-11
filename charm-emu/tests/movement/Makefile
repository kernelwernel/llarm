all: comp

comp:
	arm-none-eabi-as -mthumb -march=armv4t -o mov.o mov.asm
	arm-none-eabi-ld -Ttext=0x00000000 -o mov.elf mov.o
	arm-none-eabi-objcopy -O binary mov.elf mov.bin