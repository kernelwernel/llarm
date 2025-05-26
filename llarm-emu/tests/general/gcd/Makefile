all: comp

comp:
	arm-none-eabi-gcc -fomit-frame-pointer -march=armv4t -c -o gcd.o gcd.c
	arm-none-eabi-ld -Ttext=0x00000000 -o gcd.elf gcd.o
	arm-none-eabi-objcopy -O binary gcd.elf gcd.bin
	arm-none-eabi-objdump -D -b binary -marm gcd.bin > gcd.asm
	make clear

clear:
	@rm -rf ./*.elf
	@rm -rf ./*.o