#include <core/sprintf.h>
#include <core/string.h>
#include <core/convert.h>

#include <mem/mem.h>

#include <stdarg.h>

void sprintf(char* buf, char* format, ...) {
    va_list arg;
    va_start(arg, format);
    int format_int;
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
                    append_str(buf, '%');
                    break;
                case 'd': case 'i': case 'D': case 'I': case 'o': case 'O': case 'x': case 'X': case 'h': case 'H':
                    format_int = va_arg(arg, int); 
                    if (format_int < 0) {
                        append_str(buf, '-');
                        format_int *= -1;
                    }
                    
                    if (c == 'd' || c == 'i' || c == 'D' || c == 'I') // Decimal
                        itoa(format_int, bufprint, 10);
                    else if (c == 'o' || c == 'O') // Octals
                        itoa(format_int, bufprint, 8);
                    else if (c == 'x' || c == 'X' || c == 'h' || c == 'H') // Hexadecimal
                        itoa(format_int, bufprint, 16);
                    
                    for (int i = 0; bufprint[i] != '\0'; i++)
                        append_str(buf, bufprint[i]);
                    memset((unsigned char*)bufprint, 0, 1024);
                    break;
                // case 'f': case 'F':
                //     format_float = va_arg(list, double);
                //     dtoa(format_float, bufprint);
                //     for (int i2 = 0; i2 < strlen(bufprint); i2++)
                //         putchar(bufprint[i2]);
                case 'c': case 'C':
                    format_char = va_arg(arg, int);
                    append_str(buf, (char)format_char);
                    break;
                case 's': case 'S':
                    format_str = va_arg(arg, char*);
                    for (int i2 = 0; i2 < strlen(format_str); i2++) 
                        append_str(buf, format_str[i2]);
                    break;
                case 'f': case 'F':
                    format_float = va_arg(arg, double);
                    dtoa(bufprint, format_float);
                    for (int i2 = 0; i2 < strlen(format_str); i2++) 
                        append_str(buf, format_str[i2]);
                    break;
                default:
                    break;
            }
        }
        else 
            append_str(buf, c);
    }
    va_end(arg);
}

void sprintf_va(char* buf, va_list list) {
    // TODO: implemented sprintf_va function
}