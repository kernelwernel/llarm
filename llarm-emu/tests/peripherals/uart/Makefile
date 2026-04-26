all: comp

comp:
	arm-none-eabi-as -march=armv4t -o uart_test.o uart_test.s
	arm-none-eabi-ld -Ttext=0x00000000 -o uart_test.elf uart_test.o
	arm-none-eabi-objcopy -O binary uart_test.elf uart_test.bin
	make clear

clear:
	@rm -f uart_test.o uart_test.elf
