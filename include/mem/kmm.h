#pragma once

#include <multiboot.h>

extern unsigned char __kernel_section_start;
extern unsigned char __kernel_section_end;
extern unsigned char __kernel_text_section_start;
extern unsigned char __kernel_text_section_end;
extern unsigned char __kernel_data_section_start;
extern unsigned char __kernel_data_section_end;
extern unsigned char __kernel_rodata_section_start;
extern unsigned char __kernel_rodata_section_end;
extern unsigned char __kernel_bss_section_start;
extern unsigned char __kernel_bss_section_end;

typedef struct {
    struct {
        unsigned int k_start_addr;
        unsigned int k_end_addr;
        unsigned int k_len;
        unsigned int text_start_addr;
        unsigned int text_end_addr;
        unsigned int text_len;
        unsigned int data_start_addr;
        unsigned int data_end_addr;
        unsigned int data_len;
        unsigned int rodata_start_addr;
        unsigned int rodata_end_addr;
        unsigned int rodata_len;
        unsigned int bss_start_addr;
        unsigned int bss_end_addr;
        unsigned int bss_len;
    } kernel;

    struct {
        unsigned int total_memory;
    } system;

    struct {
        unsigned int start_addr;
        unsigned int end_addr;
        unsigned int size;
    } available;
} KMM;

int init_kmm(KMM* kmap, multiboot_info_t* mboot_info);