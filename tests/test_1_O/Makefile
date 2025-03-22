all: comp

comp:
	arm-none-eabi-as -mthumb -march=armv4t -o reg.o reg.asm
	arm-none-eabi-ld -Ttext=0x00000000 -o reg.elf reg.o
	arm-none-eabi-objcopy -O binary reg.elf reg.bin