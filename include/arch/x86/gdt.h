#pragma once

#define NO_GDT_DESCRIPTORS 8

typedef struct {
   unsigned short segment_limit;
   unsigned short base_low;      
   unsigned char base_middle;    
   unsigned char access;          
   unsigned char granularity;     
   unsigned char base_high;      
} __attribute__((packed)) GDT;

typedef struct {
   unsigned short limit;       
   unsigned int base_address;  
} __attribute__((packed)) GDT_PTR;

void set_entry_gdt(int index, unsigned int base, unsigned int limit, unsigned char access, unsigned char gran);

void init_gdt();