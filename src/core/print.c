#include <core/print.h>
#include <core/convert.h>
#include <core/sprintf.h>
#include <core/string.h>

#include <mem/mem.h>
#include <drivers/serial_port.h>

#include <graphics/draw.h>
#include <graphics/framebuffer.h>

#include <utils/colors.h>
#include <utils/vec.h>

Vec2 internal_print_vec;

Color internal_print_fg;
Color internal_print_bg;

void set_print_fg(Color new_color) {
    internal_print_fg = new_color;
}

void set_print_bg(Color new_color) {
    internal_print_bg = new_color;
}


void insert_tab() {
    for (int i = 0; i < 4; i++) putc(' ');
}

void insert_newline() {
    internal_print_vec.x = 5;
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
    va_list arg;
    va_start(arg, format);
    int format_int;
    double format_double;
    float format_float;
    char format_char;
    char* format_str;
    char bufprint[1024];
    
    for (int i = 0; i < strlen(format); i++) {
        char c = format[i];
        
        if (c == '%') {
            i++;
            c = format[i];
            
            switch (c) {
                case '%':
                    putc('%');
                    break;
                case 'd': case 'i': case 'D': case 'I': case 'o': case 'O': case 'x': case 'X': case 'h': case 'H':
                    format_int = va_arg(arg, int); 
                    if (format_int < 0) {
                        putc('-');
                        format_int *= -1;
                    }
                    
                    if (c == 'd' || c == 'i' || c == 'D' || c == 'I') // Decimal
                        itoa(format_int, bufprint, 10);
                    else if (c == 'o' || c == 'O') // Octals
                        itoa(format_int, bufprint, 8);
                    else if (c == 'x' || c == 'X' || c == 'h' || c == 'H') // Hexadecimal
                        itoa(format_int, bufprint, 16);
                    
                    for (int i = 0; bufprint[i] != '\0'; i++)
                        putc(bufprint[i]);
                    memset((unsigned char*)bufprint, 0, 1024);
                    break;
                case 'c': case 'C':
                    format_char = va_arg(arg, int);
                    putc((char)format_char);
                    break;
                case 's': case 'S':
                    format_str = va_arg(arg, char*);
                    for (int i2 = 0; i2 < strlen(format_str); i2++) 
                        putc(format_str[i2]);
                    break;
                case 'f': case 'F':
                    format_double = va_arg(arg, double);
                    dtoa(bufprint, format_double);
                    for (int i2 = 0; i2 < strlen(format_str); i2++) 
                        putc(format_str[i2]);
                    break;
                default:
                    break;
            }
        }
        else 
            putc(c);
    }
    va_end(arg);
}

void init_print() {
    serial_printf("[\x1b[1;33mPrint\x1b[0;0m] Initializing printing on screen\n");
    internal_print_vec = vec2(5, 5);
    internal_print_bg  = color(0, 0, 0);
    internal_print_fg  = color(255, 255, 255);
}