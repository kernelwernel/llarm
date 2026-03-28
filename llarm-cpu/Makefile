ARM_CXX ?= arm-linux-gnueabi-g++
CXXFLAGS := -march=armv5te -mfloat-abi=soft -Wall -Wextra

.PHONY: all install test clean

all: install

install:
	@echo "Debian/Ubuntu: sudo apt install g++-arm-linux-gnueabi qemu-user"
	@echo "Arch Linux:    sudo pacman -S arm-none-eabi-newlib qemu-system-arm"

test:
	@bash tests/run_tests.sh

clean:
	rm -f tests/test_arm
