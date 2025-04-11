all: comp

comp:
	arm-none-eabi-gcc -mthumb -march=armv4t -c -o fib.o fib.c
	arm-none-eabi-ld -Ttext=0x00000000 -o fib.elf fib.o
	arm-none-eabi-objcopy -O binary fib.elf fib.bin
	arm-none-eabi-objdump -D -b binary -marm -Mforce-thumb fib.bin > fib.asm
	make clear

clear:
	@rm -rf ./*.elf
	@rm -rf ./*.o