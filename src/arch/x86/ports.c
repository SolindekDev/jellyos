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

unsigned short inw(unsigned short port) {
    unsigned short ret;
    asm volatile ( "inw %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}

unsigned int inportl(unsigned short port) {
    unsigned int res;
    __asm__ __volatile__ ("inl %%dx, %%eax" : "=a" (res) : "dN" (port));
    return res;
}

void outportl(unsigned short port, unsigned int data) {
    __asm__ __volatile__ ("outl %%eax, %%dx" : : "dN" (port), "a" (data));
}

void insl (unsigned int addr, unsigned int buffer, unsigned int count) {
    __asm__ __volatile__ ("cld; rep; insl" :: "D" (buffer), "d" (addr), "c" (count));
}

void insw (unsigned int addr, unsigned int buffer, unsigned int count) {
    __asm__ __volatile__ ("cld; rep; insw" :: "D" (buffer), "d" (addr), "c" (count));
}

void insb (unsigned int addr, unsigned int buffer, unsigned int count) {
    __asm__ __volatile__ ("cld; rep; insb" :: "D" (buffer), "d" (addr), "c" (count));
}

void outsl (unsigned int addr, unsigned int buffer, unsigned int count) {
    __asm__ __volatile__ ("cld; rep; outsl" :: "D" (buffer), "d" (addr), "c" (count));
}

void outsw (unsigned int addr, unsigned int buffer, unsigned int count) {
    __asm__ __volatile__ ("cld; rep; outsw" :: "D" (buffer), "d" (addr), "c" (count));
}

void outsb (unsigned int addr, unsigned int buffer, unsigned int count) {
    __asm__ __volatile__ ("cld; rep; outsb" :: "D" (buffer), "d" (addr), "c" (count));
}