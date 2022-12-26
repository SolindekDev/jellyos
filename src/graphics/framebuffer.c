#include <graphics/framebuffer.h>

#include <utils/colors.h>
#include <utils/vec.h>

#include <multiboot.h>

#include <drivers/serial_port.h>

unsigned long global_addr;

void init_framebuffer(unsigned long addr) {
    serial_printf("[\x1b[1;33mFramebuffer\x1b[0;0m] Initializing framebuffer\n");
    global_addr = addr;
}

Framebuffer_t get_framebuffer_info() {
    multiboot_info_t* mbinfo = (multiboot_info_t*)global_addr;
    Framebuffer_t fb;
    fb.addr   = mbinfo->framebuffer_addr;
    fb.bpp    = mbinfo->framebuffer_bpp;
    fb.height = mbinfo->framebuffer_height;
    fb.width  = mbinfo->framebuffer_width;
    fb.pitch  = mbinfo->framebuffer_pitch;
    fb.type   = mbinfo->framebuffer_type;

    return fb;
}

unsigned framebuffer_calculate_offset(int x, int y) {
    return (x * 4) + (y * get_framebuffer_info().pitch);
}

int framebuffer_put_pixel(Vec2 vec, Color color) {
    multiboot_info_t* mbinfo = (multiboot_info_t*)global_addr;
    unsigned char* framebuffer = (unsigned char*)mbinfo->framebuffer_addr;
    unsigned offset = vec.x * 4 + vec.y * (int)mbinfo->framebuffer_pitch;

    framebuffer[offset    ] = color.b;
    framebuffer[offset + 1] = color.g;
    framebuffer[offset + 2] = color.r;
    return offset;    
}
