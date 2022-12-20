# /usr/bin/sh

flags="-m32 -c -nostdlib -march=i386 -fno-pie -mno-red-zone"
objects=""

mkdir -p bin

function compile_c {
    # for files in src/**/*.c; do
    for files in src/*.c src/**/*.c; do
        objects="${objects} ${files}.o"
        clang $flags $files -ffreestanding -O3 -I./include/ -o $files.o
    done
}

function compile_asm {
    for files in asm/*.asm; do
        objects="${objects} ${files}.o"
        nasm -felf32 $files -o $files.o
    done
}

function link_files {
    ld -m elf_i386 -T linker.ld $objects -o bin/kernel.bin -nostdlib
}

function create_iso {
    grub-file --is-x86-multiboot bin/kernel.bin
    mkdir -p isodir/boot/grub
    cp bin/kernel.bin isodir/boot/kernel.bin
    cp grub.cfg isodir/boot/grub/grub.cfg
    grub-mkrescue -o JellyOS.iso  isodir
}

compile_c
compile_asm
# echo $objects
link_files
create_iso

qemu-system-x86_64 -cdrom JellyOS.iso -m 2G -monitor stdio -vga vmware