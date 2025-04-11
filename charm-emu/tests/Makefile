

all: test

test:
	gcc -ffreestanding -nostdlib -T linker.ld -o output.bin test_1_O/test.c

disassemble:
	arm-none-eabi-objdump -D -b binary -marm -Mforce-thumb main.bin