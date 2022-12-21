#include <arch/x86/ports.h>

unsigned char inb(unsigned short port) {
    unsigned char res;
    __asm__("in %%dx, %%al" : "=a" (res) : "d" (port));
    return res;
}

void outb(unsigned short port, unsigned char data) {
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

void outw(unsigned short port, unsigned short data) {
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}

unsigned int inportl(unsigned short port) {
    unsigned int res;
    asm volatile ("inl %%dx, %%eax" : "=a" (res) : "dN" (port));
    return res;
}

void outportl(unsigned short port, unsigned int data) {
    asm volatile ("outl %%eax, %%dx" : : "dN" (port), "a" (data));
}