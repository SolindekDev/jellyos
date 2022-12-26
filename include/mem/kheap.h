#pragma once

typedef struct _kheap_block {
    struct {
        unsigned int size;  
        unsigned char is_free; 
    } metadata;
    struct _kheap_block *next; 
    void *data;  
} __attribute__((packed)) KHEAP_BLOCK;

int init_kheap(void *start_addr, void *end_addr);

void *kbrk(int size);

void kheap_print_blocks();

void *kmalloc(int size);

void *kcalloc(int n, int size);

void *krealloc(void *ptr, int size);

void kfree(void *addr);
