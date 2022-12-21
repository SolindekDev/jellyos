#pragma once

#define NO_IDT_DESCRIPTORS     256

#include <stdint.h>

typedef struct {
    unsigned short base_low;        
    unsigned short segment_selector; 
    unsigned char zero;               
    unsigned char type;               
    unsigned short base_high;         
} __attribute__((packed)) IDT;

typedef struct {
    unsigned short limit;       
    unsigned int base_address; 
} __attribute__((packed)) IDT_PTR;

extern void load_idt(unsigned int idt_ptr);

void set_entry_idt(int index, unsigned int base, unsigned short seg_sel, unsigned char flags);

void init_idt();