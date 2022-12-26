#include <mem/kheap.h>
#include <mem/mem.h>
#include <mem/kmm.h>
#include <mem/pmm.h>

#include <drivers/serial_port.h>
#include <arch/x86/isr.h>
#include <core/print.h>

#include <multiboot.h>

void *g_kheap_start_addr = NULL, *g_kheap_end_addr = NULL;
unsigned long g_total_size = 0;
unsigned long g_total_used_size = 0;

KHEAP_BLOCK *g_head = NULL;

int init_kheap(void *start_addr, void *end_addr) {
    if (start_addr > end_addr) {
        printf("failed to init kheap\n");
        return -1;
    }
    g_kheap_start_addr = start_addr;
    g_kheap_end_addr = end_addr;
    g_total_size = end_addr - start_addr;
    g_total_used_size = 0;
    return 0;
}

void *kbrk(int size) {
    void *addr = NULL;
    if (size <= 0)
        return NULL;
    if ((int)(g_total_size - g_total_used_size) <= size)
        return NULL;
    addr = g_kheap_start_addr + g_total_used_size + size + sizeof(void *);
    g_total_used_size += size + sizeof(void *);
    return addr;
}

void kheap_print_blocks() {
    KHEAP_BLOCK *temp = g_head;
    printf("Block Size: %d\n", sizeof(KHEAP_BLOCK));
    while (temp != NULL) {
        printf("size:%d, free:%d, data: 0x%x, curr: 0x%x, next: 0x%x\n",
               temp->metadata.size, temp->metadata.is_free, temp->data, temp, temp->next);
        temp = temp->next;
    }
}

int is_block_free(KHEAP_BLOCK *block) {
    if (!block)
        return 0;
    return (block->metadata.is_free == 1);
}

KHEAP_BLOCK *worst_fit(int size) {
    KHEAP_BLOCK *temp = g_head;
    while (temp != NULL) {
        if (is_block_free(temp)) {
            if ((int)temp->metadata.size >= size)
                return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

KHEAP_BLOCK *allocate_new_block(int size) {
    KHEAP_BLOCK *temp = g_head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    KHEAP_BLOCK *new_block = (KHEAP_BLOCK *)kbrk(sizeof(KHEAP_BLOCK));
    new_block->metadata.is_free = 0;
    new_block->metadata.size = size;
    new_block->data = kbrk(size);
    new_block->next = NULL;
    temp->next = new_block;
    return new_block;
}

void *kmalloc(int size) {
    serial_printf("[\x1b[1;33mKHeap\x1b[0;0m] Trying to allocate %d bytes of memory\n", size);

    if (size <= 0) {
        serial_printf("[\x1b[1;33mKHeap\x1b[0;0m] Something gone wrong while allocating %d bytes of memory\n", size);
        return NULL;
    }
    if (g_head == NULL) {
        g_head = (KHEAP_BLOCK *)kbrk(sizeof(KHEAP_BLOCK));
        g_head->metadata.is_free = 0;
        g_head->metadata.size = size;
        g_head->next = NULL;
        g_head->data = kbrk(size);
        serial_printf("[\x1b[1;33mKHeap\x1b[0;0m] Successfully allocated %d bytes of memory\n", size);
        return g_head->data;
    } else {
        KHEAP_BLOCK *worst = worst_fit(size);
        if (worst == NULL) {
            KHEAP_BLOCK *new_block = allocate_new_block(size);
            new_block->metadata.is_free = 0;
            new_block->metadata.size = size;
            new_block->data = kbrk(size);
            serial_printf("[\x1b[1;33mKHeap\x1b[0;0m] Successfully allocated %d bytes of memory\n", size);
            return new_block->data;
        } else {
            worst->metadata.is_free = 0;
            serial_printf("[\x1b[1;33mKHeap\x1b[0;0m] Successfully allocated %d bytes of memory\n", size);
            return worst->data;
        }
    }
    serial_printf("[\x1b[1;33mKHeap\x1b[0;0m] Trying to allocate %d bytes of memory\n", size);
    return NULL;
}

void *kcalloc(int n, int size) {
    if (n < 0 || size < 0)
        return NULL;
    void *mem = kmalloc(n * size);
    memset(mem, 0, n * size);
    return mem;
}

void *krealloc(void *ptr, int size) {
    KHEAP_BLOCK *temp = g_head;
    while (temp != NULL) {
        if (temp->data == ptr) {
            KHEAP_BLOCK *new_block = allocate_new_block(size);
            if ((int)temp->metadata.size > size)
                memcpy(new_block->data, ptr, size);
            else
                memcpy(new_block->data, ptr, temp->metadata.size);
            temp->metadata.is_free = 1;
            return new_block->data;
        }
        temp = temp->next;
    }
    return NULL;
}

void kfree(void *addr) {
    KHEAP_BLOCK *temp = g_head;
    while (temp != NULL) {
        if (temp->data == addr) {
            temp->metadata.is_free = 1;
            return;
        }
        temp = temp->next;
    }
}