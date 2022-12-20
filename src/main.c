#include <graphics/framebuffer.h>

#include <core/print.h>

#include <multiboot.h>

void main(unsigned long magic, unsigned long addr) {
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
        return;

    init_framebuffer(addr);
    init_print();

    putc('S');
    putc('o');
    putc('l');
    putc('i');
    putc('n');
    putc('d');
    putc('e');
    putc('k');
}