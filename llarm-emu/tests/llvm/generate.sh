#!/bin/bash

required_tools=("llvm-stress" "clang" "ld.lld" "arm-none-eabi-gcc" "llvm-objcopy" "llvm-objdump")
for tool in "${required_tools[@]}"; do
    if ! command -v "$tool" >/dev/null 2>&1; then
        echo "Error: $tool is not installed or not in PATH, aborting"
        exit 1
    fi
done


mkdir -p generated
cd generated || exit 1


for i in {1..1}; do
    mkdir test_$i
    cd test_$i

    SEED=$(od -An -N4 -tu4 < /dev/urandom | tr -d ' ')

    llvm-stress --size=250 -seed=$SEED -o IR.ll 
    opt IR.ll -O3 -mtriple=armv4t-unknown-none-eabi -o IR.bc

    #ld.lld -Ttext=0x00000000 --entry=main \
    #    -L$(dirname $(arm-none-eabi-gcc -print-libgcc-file-name)) \
    #    -lgcc \
    #    bin.o -o bin.elf
    #llvm-objcopy -O bin bin.elf bin.bin
    #llvm-objdump -D -b bin -marm bin.bin > output.asm


    clang -c IR.bc \
        -target armv4t-unknown-none-eabi \
        -march=armv4t \
        -fomit-frame-pointer \
        -nostdlib \
        -ffreestanding \
        -fno-builtin \
        -fno-exceptions \
        -mfloat-abi=soft \
        -o bin.o

    GCC_LIB_PATH=$(dirname "$(arm-none-eabi-gcc -print-libgcc-file-name)")
    ARM_LIB_PATH="$GCC_LIB_PATH/../arm-none-eabi/lib"

    ld.lld -Ttext=0x00000000 \
        --entry=main \
        -nostdlib \
        --no-undefined \
        -L"$GCC_LIB_PATH" \
        -L"$ARM_LIB_PATH" \
        -lgcc \
        bin.o \
        -o bin.elf

    llvm-objcopy -O binary bin.elf bin.bin
    llvm-objdump -D --mattr=+armv4t bin.elf > output.asm




    cd ..
done