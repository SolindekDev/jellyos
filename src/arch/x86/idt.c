#include <arch/x86/idt.h>
#include <arch/x86/isr.h>
#include <arch/x86/pic8259.h>

#include <drivers/serial_port.h>

IDT g_idt[NO_IDT_DESCRIPTORS];
IDT_PTR g_idt_ptr;

void set_entry_idt(int index, unsigned int base, unsigned short seg_sel, unsigned char flags) {
    IDT *this = &g_idt[index];

    this->base_low = base & 0xFFFF;
    this->segment_selector = seg_sel;
    this->zero = 0;
    this->type = flags | 0x60;
    this->base_high = (base >> 16) & 0xFFFF;
}

void init_idt() {
    serial_printf("[\x1b[1;33mIDT\x1b[0;0m] Initializing interrupt descriptor table\n");

    g_idt_ptr.base_address = (unsigned int)g_idt;
    g_idt_ptr.limit = sizeof(g_idt) - 1;
    pic8259_init();

    set_entry_idt(0, (unsigned int)exception_0, 0x08, 0x8E);
    set_entry_idt(1, (unsigned int)exception_1, 0x08, 0x8E);
    set_entry_idt(2, (unsigned int)exception_2, 0x08, 0x8E);
    set_entry_idt(3, (unsigned int)exception_3, 0x08, 0x8E);
    set_entry_idt(4, (unsigned int)exception_4, 0x08, 0x8E);
    set_entry_idt(5, (unsigned int)exception_5, 0x08, 0x8E);
    set_entry_idt(6, (unsigned int)exception_6, 0x08, 0x8E);
    set_entry_idt(7, (unsigned int)exception_7, 0x08, 0x8E);
    set_entry_idt(8, (unsigned int)exception_8, 0x08, 0x8E);
    set_entry_idt(9, (unsigned int)exception_9, 0x08, 0x8E);
    set_entry_idt(10, (unsigned int)exception_10, 0x08, 0x8E);
    set_entry_idt(11, (unsigned int)exception_11, 0x08, 0x8E);
    set_entry_idt(12, (unsigned int)exception_12, 0x08, 0x8E);
    set_entry_idt(13, (unsigned int)exception_13, 0x08, 0x8E);
    set_entry_idt(14, (unsigned int)exception_14, 0x08, 0x8E);
    set_entry_idt(15, (unsigned int)exception_15, 0x08, 0x8E);
    set_entry_idt(16, (unsigned int)exception_16, 0x08, 0x8E);
    set_entry_idt(17, (unsigned int)exception_17, 0x08, 0x8E);
    set_entry_idt(18, (unsigned int)exception_18, 0x08, 0x8E);
    set_entry_idt(19, (unsigned int)exception_19, 0x08, 0x8E);
    set_entry_idt(20, (unsigned int)exception_20, 0x08, 0x8E);
    set_entry_idt(21, (unsigned int)exception_21, 0x08, 0x8E);
    set_entry_idt(22, (unsigned int)exception_22, 0x08, 0x8E);
    set_entry_idt(23, (unsigned int)exception_23, 0x08, 0x8E);
    set_entry_idt(24, (unsigned int)exception_24, 0x08, 0x8E);
    set_entry_idt(25, (unsigned int)exception_25, 0x08, 0x8E);
    set_entry_idt(26, (unsigned int)exception_26, 0x08, 0x8E);
    set_entry_idt(27, (unsigned int)exception_27, 0x08, 0x8E);
    set_entry_idt(28, (unsigned int)exception_28, 0x08, 0x8E);
    set_entry_idt(29, (unsigned int)exception_29, 0x08, 0x8E);
    set_entry_idt(30, (unsigned int)exception_30, 0x08, 0x8E);
    set_entry_idt(31, (unsigned int)exception_31, 0x08, 0x8E);
    set_entry_idt(32, (unsigned int)irq_0, 0x08, 0x8E);
    set_entry_idt(33, (unsigned int)irq_1, 0x08, 0x8E);
    set_entry_idt(34, (unsigned int)irq_2, 0x08, 0x8E);
    set_entry_idt(35, (unsigned int)irq_3, 0x08, 0x8E);
    set_entry_idt(36, (unsigned int)irq_4, 0x08, 0x8E);
    set_entry_idt(37, (unsigned int)irq_5, 0x08, 0x8E);
    set_entry_idt(38, (unsigned int)irq_6, 0x08, 0x8E);
    set_entry_idt(39, (unsigned int)irq_7, 0x08, 0x8E);
    set_entry_idt(40, (unsigned int)irq_8, 0x08, 0x8E);
    set_entry_idt(41, (unsigned int)irq_9, 0x08, 0x8E);
    set_entry_idt(42, (unsigned int)irq_10, 0x08, 0x8E);
    set_entry_idt(43, (unsigned int)irq_11, 0x08, 0x8E);
    set_entry_idt(44, (unsigned int)irq_12, 0x08, 0x8E);
    set_entry_idt(45, (unsigned int)irq_13, 0x08, 0x8E);
    set_entry_idt(46, (unsigned int)irq_14, 0x08, 0x8E);
    set_entry_idt(47, (unsigned int)irq_15, 0x08, 0x8E);
    set_entry_idt(128, (unsigned int)exception_128, 0x08, 0x8E);

    load_idt((unsigned int)&g_idt_ptr);
    asm volatile("sti");
}