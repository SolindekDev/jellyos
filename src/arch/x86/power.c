#include <arch/x86/power.h>
#include <arch/x86/ports.h>

#include <core/print.h>

void shutdown() {
    // outw(0xB004, 0x2000); // Older versions than QEMU 2.0  
    // outw(0x604, 0x2000);  // Newer versions of QEMU
    // outw(0x4004, 0x3400); // VirtualBox

    // TODO: ACPI Driver
    printf("Can't shutdown the system because of unimplemented ACPI driver\n\tIf you are on real hardware try to power off the machine otherwise if you are on unsupported\n\tshutdown x86 emulator try to close the window.");
}

void reboot() {
    unsigned char good = 0x02;
    while (good & 0x02)
        good = inb(0x64);
    outb(0x64, 0xFE);
    asm("hlt");
}