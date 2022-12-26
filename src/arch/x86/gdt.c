#include <arch/x86/gdt.h>

#include <drivers/serial_port.h>

GDT g_gdt[NO_GDT_DESCRIPTORS];
GDT_PTR g_gdt_ptr;

extern void load_gdt(unsigned int gdt_ptr);

void set_entry_gdt(int index, unsigned int base, unsigned int limit, unsigned char access, unsigned char gran) {
    GDT *current_gdt = &g_gdt[index];

    current_gdt->segment_limit = limit & 0xFFFF;
    current_gdt->base_low = base & 0xFFFF;
    current_gdt->base_middle = (base >> 16) & 0xFF;
    current_gdt->access = access;

    current_gdt->granularity = (limit >> 16) & 0x0F;
    current_gdt->granularity = current_gdt->granularity | (gran & 0xF0);

    current_gdt->base_high = (base >> 24 & 0xFF);
}

void init_gdt() {
    serial_printf("[\x1b[1;33mGDT\x1b[0;0m] Initializing global descriptor table\n");
    
    g_gdt_ptr.limit = sizeof(g_gdt) - 1;
    g_gdt_ptr.base_address = (unsigned int)g_gdt;

    set_entry_gdt(0, 0, 0, 0, 0);
    set_entry_gdt(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    set_entry_gdt(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    set_entry_gdt(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    set_entry_gdt(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    load_gdt((unsigned int)&g_gdt_ptr);
}