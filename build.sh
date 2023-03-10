# /usr/bin/sh

flags="-m32 -c -nostdlib -march=i386 -fno-pie -mno-red-zone"
objects=""

mkdir -p bin

function compile_c {
    # for files in src/**/*.c; do
    for files in src/*.c src/**/*.c src/**/**/*.c; do
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

function set_up_filesystem {
    dd if=/dev/zero of=./disk.ext2 bs=512 count=20480
    /sbin/mkfs.ext2 ./disk.ext2
}

compile_c
compile_asm
# echo $objects
link_files
create_iso
# set_up_filesystem

qemu-system-x86_64 -cdrom JellyOS.iso -m 3G -vga vmware -serial stdio  -drive file=disk.ext2,format=raw