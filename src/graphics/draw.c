#include <graphics/draw.h>
#include <graphics/framebuffer.h>
#include <graphics/font.h>

#include <utils/colors.h>
#include <utils/vec.h>

void draw_rect(Vec2 pos, Vec2 size, Color color) {
    for (int x = 0; x < size.x; x++)
        for (int y = 0; y < size.y; y++)
            framebuffer_put_pixel(vec2(x + pos.x, y + pos.y), color);
}

void draw_circle(Vec2 center, int radius, Color color) {
    int x = 0, y = radius;
    int d = 3 - 2 * radius;

    framebuffer_put_pixel(vec2(center.x+x, center.y+y), color);
    framebuffer_put_pixel(vec2(center.x-x, center.y+y), color);
    framebuffer_put_pixel(vec2(center.x+x, center.y-y), color);
    framebuffer_put_pixel(vec2(center.x-x, center.y-y), color);
    framebuffer_put_pixel(vec2(center.x+y, center.y+x), color);
    framebuffer_put_pixel(vec2(center.x-y, center.y+x), color);
    framebuffer_put_pixel(vec2(center.x+y, center.y-x), color);
    framebuffer_put_pixel(vec2(center.x-y, center.y-x), color);

    while (y >= x) {
        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else
            d = d + 4 * x + 6;

        framebuffer_put_pixel(vec2(center.x+x, center.y+y), color);
        framebuffer_put_pixel(vec2(center.x-x, center.y+y), color);
        framebuffer_put_pixel(vec2(center.x+x, center.y-y), color);
        framebuffer_put_pixel(vec2(center.x-x, center.y-y), color);
        framebuffer_put_pixel(vec2(center.x+y, center.y+x), color);
        framebuffer_put_pixel(vec2(center.x-y, center.y+x), color);
        framebuffer_put_pixel(vec2(center.x+y, center.y-x), color);
        framebuffer_put_pixel(vec2(center.x-y, center.y-x), color);
    }
}

void draw_line(Vec2 start, Vec2 end, Color color) {
    int dx = end.x - start.x;
    int dy = end.y - start.y;
    int d = 2 * dy - dx;
    int y = start.y;

    for (int x = start.x; x <= end.x; x++) {
        framebuffer_put_pixel(vec2(x, y), color);
        if (d > 0) {
            y = y + 1;
            d = d - 2 * dx;
        }
        d = d + 2 * dy;
    }
}

void draw_character(char c, int x, int y, Color fg, Color bg) {
    // int* font_char = &get_font()[c * 16];

    // for (int i = 0; i < 16; ++i){
    //     for (int j = 0; j < 8; ++j){
    //         if (font_char[i] & (1 << (8 - j))){
    //             framebuffer_put_pixel(vec2(x+j, y+i), fg);
    //         } else {
    //             framebuffer_put_pixel(vec2(x+j, y+i), bg);
    //         }
    //     }
    // }
    unsigned char* font_char = &get_font()[c * 16];

    for(int i = 0; i < 16; ++i){
        for(int j = 0; j < 8; ++j){
            if(font_char[i] & (1 << (8 - j))){
                framebuffer_put_pixel(vec2(x+j, y+i), fg);
            } else {
                framebuffer_put_pixel(vec2(x+j, y+i), bg);
            }
        }
    }
}
