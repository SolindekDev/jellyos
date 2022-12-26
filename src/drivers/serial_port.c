#include <drivers/serial_port.h>

#include <arch/x86/ports.h>
#include <core/string.h>

#include <stdarg.h>

void serial_putchar(char c) {
    outb(0x3F8, c);
}

void serial_print(char* buf) {
    int i = 0;
    while (buf[i] != '\0')
        serial_putchar(buf[i]);
}

void serial_printf(char* buf, ...) {
    va_list arg;
    va_start(arg, buf);
    
    int format_int;
    float format_float;
    char format_char;
    char* format_str;
    char bufprint[1024];
    
    for (int i = 0; i < strlen(buf); i++) {
        char c = buf[i];
        
        if (c == '%') {
            i++;
            c = buf[i];
            
            switch (c) {
                case '%':
                    serial_putchar('%');
                    break;
                case 'd': case 'i': case 'D': case 'I': case 'o': case 'O': case 'x': case 'X': case 'h': case 'H':
                    format_int = va_arg(arg, int); 
                    if (format_int < 0) {
                        serial_putchar('-');
                        format_int *= -1;
                    }
                    
                    if (c == 'd' || c == 'i' || c == 'D' || c == 'I') // Decimal
                        itoa(format_int, bufprint, 10);
                    else if (c == 'o' || c == 'O') // Octals
                        itoa(format_int, bufprint, 8);
                    else if (c == 'x' || c == 'X' || c == 'h' || c == 'H') // Hexadecimal
                        itoa(format_int, bufprint, 16);
                    
                    for (int i = 0; bufprint[i] != '\0'; i++)
                        serial_putchar(bufprint[i]);
                    break;
                // case 'f': case 'F':
                //     format_float = va_arg(arg, double);
                //     dtoa(format_float, bufprint);
                //     for (int i2 = 0; i2 < strlen(bufprint); i2++)
                //         putchar(bufprint[i2]);
                case 'c': case 'C':
                    format_char = va_arg(arg, int);
                    serial_putchar((char)format_char);
                    break;
                case 's': case 'S':
                    format_str = va_arg(arg, char*);
                    for (int i2 = 0; i2 < strlen(format_str); i2++) 
                        serial_putchar(format_str[i2]);
                    break;
                default:
                    break;
            }
        }
        else 
            serial_putchar(c);
    }
    va_end(arg);
}
