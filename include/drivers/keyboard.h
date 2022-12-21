#pragma once

#include <arch/x86/isr.h>

char get_key_char();

char get_keycode();

char await_for_key_char();

char await_for_keycode();

char read_keyboard_char();

void keyboard_handler(registers_t* reg);

void init_keyboard_driver();
