#include <arch/x86/gdt.h>
#include <arch/x86/idt.h>

#include <graphics/framebuffer.h>
#include <graphics/draw.h>

#include <drivers/keyboard.h>

#include <drivers/time/cmos.h>

#include <core/convert.h>
#include <core/print.h>

#include <multiboot.h>

void main(unsigned long magic, unsigned long addr) {
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
        return;

    // Initialize some graphical things
    init_framebuffer(addr);
    init_print();

    // Initialize interrupts and other
    init_gdt();
    init_idt();

    // Initialize drivers
    init_keyboard_driver();

    printf("%s", get_date_pretty());
    
}