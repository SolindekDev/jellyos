#pragma once

#include <utils/colors.h>

void set_print_fg(Color new_color);

void set_print_bg(Color new_color);

void insert_tab();

void insert_newline();

void putc(char c);

void printf(char* format, ...);

void init_print();