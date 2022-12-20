#pragma once

#include <multiboot.h>
#include <utils/colors.h>
#include <utils/vec.h>

typedef struct Framebuffer_t {
    unsigned char pitch;
    unsigned char type;
    int height;
    int width;
    long addr;
    int bpp;
} Framebuffer_t;

void init_framebuffer(unsigned long addr);

Framebuffer_t get_framebuffer_info();

int framebuffer_put_pixel(Vec2 vec, Color color);

unsigned framebuffer_calculate_offset(int x, int y);