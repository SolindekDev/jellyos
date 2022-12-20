#include <core/print.h>
#include <core/sprintf.h>
#include <core/string.h>

#include <graphics/draw.h>
#include <graphics/framebuffer.h>

#include <utils/colors.h>
#include <utils/vec.h>

Vec2 internal_print_vec;

Color internal_print_fg;
Color internal_print_bg;

void insert_tab() {
    for (int i = 0; i < 4; i++) putc(' ');
}

void insert_newline() {
    internal_print_vec.x = 0;
    internal_print_vec.y += 22;

    // If we are getting to far down the screen let's begin from top
    // but this should be fix
    // TODO: fix so it work better at scrolling
    if (internal_print_vec.y >= get_framebuffer_info().height) internal_print_vec.y = 0;
}

void putc(char c) {
    if (c == '\n' || c == '\r') insert_newline();
    else if (c == '\t') insert_tab();
    else {
        draw_character(
            c, 
            internal_print_vec.x, internal_print_vec.y, 
            internal_print_fg, internal_print_bg);
        internal_print_vec.x += 9;

        // If we are at the end of screen width then get to the newline!
        // get_framebuffer_info().width will return the width of screen
        // default is 1024 but i don't want to precode it let's be safe
        if (internal_print_vec.x >= get_framebuffer_info().width) insert_newline();
    }

}

void printf(char* format, ...) {
    // TODO: implement printf
}

void init_print() {
    internal_print_vec = vec2(5, 5);
    internal_print_bg  = color(0, 0, 0);
    internal_print_fg  = color(255, 255, 255);
}