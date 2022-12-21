#include <drivers/keyboard.h>

#include <core/print.h>

#include <arch/x86/ports.h>
#include <arch/x86/isr.h>

char keyboard_map_us[128] = {
    0,   27,  '1', '2', '3', '4', '5', '6', '7', '8', '9',  '0', '-',  '=',  '\b', '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[',  ']', '\n', 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z',  'x',  'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0,
    ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

char keyboard_map_us_shift[128] = {
    0,   27,  '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_',  '+', '\b', '\t',                                                 
    'Q', 'W', 'E', 'R', 'T', 'Z', 'U', 'I', 'O', 'P', '{', '}', '\n', 0,                                                                  
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '?', 0,   0,    '|', 'Z',  'X',  'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, '*', 0, 
    ' ', 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'-', 0,                                                                                                                               0,   0,                                                                                                                            '+', 0, 0, 0, 0,0,0,   0,   0,   0, 0,0, 
};

char key_char;
char keycode;

int shift;
int capslock;

char get_key_char() { 
    char copy_key_char = key_char;
    key_char = 0;
    return copy_key_char; 
}

char get_keycode() { 
    char copy_keycode = keycode;
    keycode = 0;
    return copy_keycode; 
}

// TODO: create an independent thread for function await_for_key_char() and await_for_keycode()

char await_for_key_char() {
    while (key_char == 0) {}

    return key_char;
}

char await_for_keycode() {
    while (keycode == 0) {}

    return keycode;
}

char read_keyboard_char() {
    char _keycode = inb(0x60);

    if (_keycode == 0x2A || _keycode == 0x36) {
        if (shift) 
            shift = 0;
        else   
            shift = 1;
        return -2;
    } else if (_keycode == 0x3a) {
        if (capslock == 1)
            capslock = 0;
        else   
            capslock = 1;
        return -3;
    } else if (_keycode > 0) {
        if ((shift == 0 && capslock == 0))
            return keyboard_map_us[(unsigned char)_keycode];
        else
            return keyboard_map_us_shift[(unsigned char)_keycode];
    } 
    
    return -1;
}

void keyboard_handler(registers_t* reg) {
    char key = read_keyboard_char();

    if (key > 0 || key == -2 || key == -3) {
        key_char = key;
        keycode = inb(0x60);
    } else return;
}

void init_keyboard_driver() {
    key_char = 0;
    keycode = 0;
    shift = 0;
    capslock = 0;

    isr_register_interrupt_handler(33, keyboard_handler);
}
