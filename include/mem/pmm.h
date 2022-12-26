#pragma once

typedef unsigned int PMM_PHYSICAL_ADDRESS;

#define PMM_BLOCK_SIZE    4096

typedef struct {
    unsigned int memory_size;
    unsigned int max_blocks;
    unsigned int *memory_map_array;
    unsigned int memory_map_end;
    unsigned int used_blocks;
} PMM_INFO;

unsigned int pmm_get_max_blocks();

unsigned int pmm_get_used_blocks();

int pmm_next_free_frame(int size);

void init_pmm(PMM_PHYSICAL_ADDRESS bitmap, unsigned int total_memory_size);

void init_region_pmm(PMM_PHYSICAL_ADDRESS base, unsigned int region_size);

void pmm_deinit_region(PMM_PHYSICAL_ADDRESS base, unsigned int region_size);

void* pmm_alloc_block();

void pmm_free_block(void* p);

void* pmm_alloc_blocks(unsigned int size);

void pmm_free_blocks(void* p, unsigned int size);