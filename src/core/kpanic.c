#include <core/kpanic.h>

#include <core/print.h>

#include <utils/colors.h>
#include <drivers/serial_port.h>

void kpanic(char* msg) {
    set_print_fg(color(255, 0, 0));
    printf("KERNEL PANIC: %s\n", msg);
    printf("HALTING THE SYSTEM");

    serial_printf("\x1b[1;31mKERNEL PANIC: %s\n", msg);
    serial_printf("\x1b[1;31mHALTING THE SYSTEM");
    
    while (1)
        asm("hlt");
}