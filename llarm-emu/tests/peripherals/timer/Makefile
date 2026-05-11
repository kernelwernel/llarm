all: comp

comp:
	arm-none-eabi-as -march=armv4t -o timer_test.o timer_test.s
	arm-none-eabi-ld -Ttext=0x00000000 -o timer_test.elf timer_test.o
	arm-none-eabi-objcopy -O binary timer_test.elf timer_test.bin
	make clear

clear:
	@rm -f timer_test.o timer_test.elf
