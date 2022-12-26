#include <mem/kmm.h>
#include <mem/mem.h>

#include <arch/x86/isr.h>

#include <multiboot.h>

int init_kmm(KMM* kmap, multiboot_info_t* mboot_info) {
    unsigned int i;

    if (kmap == NULL) return -1;
    kmap->kernel.k_start_addr = (unsigned int)&__kernel_section_start;
    kmap->kernel.k_end_addr = (unsigned int)&__kernel_section_end;
    kmap->kernel.k_len = ((unsigned int)&__kernel_section_end - (unsigned int)&__kernel_section_start);

    kmap->kernel.text_start_addr = (unsigned int)&__kernel_text_section_start;
    kmap->kernel.text_end_addr = (unsigned int)&__kernel_text_section_end;
    kmap->kernel.text_len = ((unsigned int)&__kernel_text_section_end - (unsigned int)&__kernel_text_section_start);

    kmap->kernel.data_start_addr = (unsigned int)&__kernel_data_section_start;
    kmap->kernel.data_end_addr = (unsigned int)&__kernel_data_section_end;
    kmap->kernel.data_len = ((unsigned int)&__kernel_data_section_end - (unsigned int)&__kernel_data_section_start);

    kmap->kernel.rodata_start_addr = (unsigned int)&__kernel_rodata_section_start;
    kmap->kernel.rodata_end_addr = (unsigned int)&__kernel_rodata_section_end;
    kmap->kernel.rodata_len = ((unsigned int)&__kernel_rodata_section_end - (unsigned int)&__kernel_rodata_section_start);

    kmap->kernel.bss_start_addr = (unsigned int)&__kernel_bss_section_start;
    kmap->kernel.bss_end_addr = (unsigned int)&__kernel_bss_section_end;
    kmap->kernel.bss_len = ((unsigned int)&__kernel_bss_section_end - (unsigned int)&__kernel_bss_section_start);

    kmap->system.total_memory = mboot_info->mem_lower + mboot_info->mem_upper;

    for (i = 0; i < mboot_info->mmap_length; i += sizeof(multiboot_memory_map)) {
        multiboot_memory_map* mmap = (multiboot_memory_map*)(mboot_info->mmap_addr + i);
        if (mmap->type != MULTIBOOT_MEMORY_AVAILABLE) continue;
        // make sure kernel is loaded at 0x100000 by bootloader(see linker.ld)
        if (mmap->addr_low == kmap->kernel.text_start_addr) {
            // set available memory starting from end of our kernel, leaving 1MB size for functions exceution
            kmap->available.start_addr = kmap->kernel.k_end_addr + 1024 * 1024;
            kmap->available.end_addr = mmap->addr_low + mmap->len_low;
            // get availabel memory in bytes
            kmap->available.size = kmap->available.end_addr - kmap->available.start_addr;
            return 0;
        }
    }

    return -1;
}