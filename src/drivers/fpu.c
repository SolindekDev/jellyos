#include <drivers/fpu.h>

#include <drivers/serial_port.h>

void fpu_set_control_w(unsigned short cw) {
    serial_printf("[\x1b[1;33mFPU\x1b[0;0m] Setting control word 0x%x\n", cw);
    asm volatile("fldcw %0" :: "m"(cw));
}

void init_fpu() {
    serial_printf("[\x1b[1;33mFPU\x1b[0;0m] Initializing FPU\n");

    unsigned int cr4;
    asm volatile("mov %%cr4, %0" : "=r"(cr4));

    cr4 |= 0x200;
    asm volatile("mov %0, %%cr4" :: "r"(cr4));

    fpu_set_control_w(0x37F);
    fpu_set_control_w(0x37E);
    fpu_set_control_w(0x37A);
}