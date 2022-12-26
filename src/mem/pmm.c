#include <mem/pmm.h>
#include <mem/mem.h>

#include <drivers/serial_port.h>

#include <core/convert.h>
#include <arch/x86/isr.h>
 
static PMM_INFO g_pmm_info;

static inline void pmm_mmap_set(int bit) {
    g_pmm_info.memory_map_array[bit / 32] |= (1 << (bit % 32));
}

static inline void pmm_mmap_unset(int bit) {
    g_pmm_info.memory_map_array[bit / 32] &= ~(1 << (bit % 32));
}

static inline char pmm_mmap_test(int bit) {
    return g_pmm_info.memory_map_array[bit / 32] & (1 << (bit % 32));
}

unsigned int pmm_get_max_blocks() {
    return g_pmm_info.max_blocks;
}

unsigned int pmm_get_used_blocks() {
    return g_pmm_info.used_blocks;
}

int pmm_mmap_first_free() {
    unsigned int i, j;

    for (i = 0; i < g_pmm_info.max_blocks; i++) {
        if (g_pmm_info.memory_map_array[i] != 0xffffffff) {
            for (j = 0; j < 32; j++) {
                int bit = 1 << j;
                if (!(g_pmm_info.memory_map_array[i] & bit))
                    return i * 32 + j;
            }
        }
    }
    return -1;
}

int pmm_mmap_first_free_by_size(unsigned int size) {
    unsigned int i, j, k, free = 0;
    int bit;

    if (size == 0)
        return -1;

    if (size == 1)
        return pmm_mmap_first_free();

    for (i = 0; i < g_pmm_info.max_blocks; i++) {
        if (g_pmm_info.memory_map_array[i] != 0xffffffff) {
            // check each bit, if not set
            for (j = 0; j < 32; j++) {
                bit = 1 << j;
                if (!(g_pmm_info.memory_map_array[i] & bit)) {
                    // check no of bits(size) are free or not?
                    for (k = j; k < 32; k++) {
                        bit = 1 << k;
                        if (!(g_pmm_info.memory_map_array[i] & bit))
                            free++;
                        
                        if (free == size)
                            return i * 32 + j;
                    }
                }
            }
        }
    }
    return -1;
}

int pmm_next_free_frame(int size) {
    return pmm_mmap_first_free_by_size(size);
}

void init_pmm(PMM_PHYSICAL_ADDRESS bitmap, unsigned int total_memory_size) {
    serial_printf("[\x1b[1;33mPPM\x1b[0;0m] Initializing psychical memory managment\n");

    g_pmm_info.memory_size = total_memory_size;
    g_pmm_info.memory_map_array = (unsigned int *)bitmap;
    g_pmm_info.max_blocks = total_memory_size / PMM_BLOCK_SIZE;
    g_pmm_info.used_blocks = g_pmm_info.max_blocks;

    memset((unsigned char*)g_pmm_info.memory_map_array, 0xff, g_pmm_info.max_blocks * sizeof(unsigned int));
    g_pmm_info.memory_map_end = (unsigned int)&g_pmm_info.memory_map_array[g_pmm_info.max_blocks];
}

void init_region_pmm(PMM_PHYSICAL_ADDRESS base, unsigned int region_size) {
    int align = base / PMM_BLOCK_SIZE;
    int blocks = region_size / PMM_BLOCK_SIZE;

    while (blocks >= 0) {
        pmm_mmap_unset(align++);
        g_pmm_info.used_blocks--;
        blocks--;
    }
}

void pmm_deinit_region(PMM_PHYSICAL_ADDRESS base, unsigned int region_size) {
    int align = base / PMM_BLOCK_SIZE;
    int blocks = region_size / PMM_BLOCK_SIZE;

    while (blocks >= 0) {
        pmm_mmap_set(align++);
        g_pmm_info.used_blocks++;
        blocks--;
    }
}

void* pmm_alloc_block() {
    // out of memory
    if ((g_pmm_info.max_blocks - g_pmm_info.used_blocks) <= 0)
        return NULL;

    int frame = pmm_mmap_first_free();
    if (frame == -1)
        return NULL;

    pmm_mmap_set(frame);

    PMM_PHYSICAL_ADDRESS addr = (frame * PMM_BLOCK_SIZE) + g_pmm_info.memory_map_end;
    g_pmm_info.used_blocks++;

    return (void *)addr;
}

void pmm_free_block(void* p) {
    PMM_PHYSICAL_ADDRESS addr = (PMM_PHYSICAL_ADDRESS)p;
    addr -= g_pmm_info.memory_map_end;
    int frame = addr / PMM_BLOCK_SIZE;
    pmm_mmap_unset(frame);
    g_pmm_info.used_blocks--;
}

void* pmm_alloc_blocks(unsigned int size) {
    unsigned int i;

    if ((g_pmm_info.max_blocks - g_pmm_info.used_blocks) <= size)
        return NULL;

    int frame = pmm_mmap_first_free_by_size(size);
    if (frame == -1)
        return NULL;

    for (i = 0; i < size; i++)
        pmm_mmap_set(frame + i);

    PMM_PHYSICAL_ADDRESS addr = (frame * PMM_BLOCK_SIZE) + g_pmm_info.memory_map_end;
    g_pmm_info.used_blocks += size;

    return (void *)addr;
}

void pmm_free_blocks(void* p, unsigned int size) {
    unsigned int i;

    PMM_PHYSICAL_ADDRESS addr = (PMM_PHYSICAL_ADDRESS)p;
    addr -= g_pmm_info.memory_map_end;
    int frame = addr / PMM_BLOCK_SIZE;
    for (i = 0; i < size; i++)
        pmm_mmap_unset(frame + i);
    g_pmm_info.used_blocks -= size;
}