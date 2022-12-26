#include <arch/x86/ports.h>
#include <arch/x86/gdt.h>
#include <arch/x86/idt.h>

#include <graphics/framebuffer.h>
#include <graphics/draw.h>

#include <drivers/keyboard.h>
#include <drivers/serial_port.h>
#include <drivers/time/cmos.h>
#include <drivers/time/timer.h>
#include <drivers/time/sleep.h>
#include <drivers/fpu.h>

#include <mem/kheap.h>
#include <mem/mem.h>
#include <mem/kmm.h>
#include <mem/pmm.h>

#include <utils/complex_arrays.h>
#include <syscall/syscall.h>

#include <elf/apps/hello.h>
#include <elf/elf.h>

#include <fs/ata.h>
#include <fs/vfs.h>

#include <core/convert.h>
#include <core/random.h>
#include <core/print.h>

#include <multiboot.h>

void main(unsigned long magic, unsigned long addr) {
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        serial_printf("[\x1b[1;33mMultiboot\x1b[0;0m] magic don't equals 0x%x\n", magic);
        return;
    } else
        serial_printf("[\x1b[1;33mMultiboot\x1b[0;0m] magic equals 0x%x\n", magic);

    // Initialize some graphical things
    init_framebuffer(addr);
    init_print();

    // Initialize interrupts
    init_gdt();
    init_idt();
    init_fpu();

    // Initialize Memory allocation
    KMM kmm;

    init_kmm(&kmm, (multiboot_info_t*)addr);
    init_pmm(kmm.available.start_addr, kmm.available.size);
    init_region_pmm(kmm.available.start_addr, PMM_BLOCK_SIZE * 256);

    void* start = pmm_alloc_blocks(20);
    void* end   = start + (pmm_next_free_frame(1) * PMM_BLOCK_SIZE);
    init_kheap(start, end);

    // Initialize drivers
    init_keyboard_driver();
    init_timer();
    init_syscalls();
    init_ata();
    init_vfs();

    File_t* file = create_file("hello", get_bin_dir());
    fwrite(get_hello_app_array(), strlen(get_hello_app_array()) + 1, 1, file);

    load_elf(file);
}