#include <core/convert.h>
#include <core/string.h>

#include <mem/mem.h>

void itoa(int num, char* str, int base) {
    int i = 0;
    int is_neg = 0;
    
    if (num == 0) { 
        str[i++] = '0';
        str[i] = '\0';
        return;
    } 
    if (num < 0 && base == 10) {
        is_neg = 1;
        num = -num;
    }
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }
    if (is_neg)
        str[i++] = '-';
    str[i] = '\0';
    reverse(str);
}

void dtoa(char* buf, double f) {
    unsigned int count = 1;
    const unsigned int DEFAULT_DECIMAL_COUNT = 8;
    char int_part_buf[16];
    char *p;

    memset((unsigned char*)int_part_buf, 0, sizeof(int_part_buf));
    // add integer part
    int x = (int)f;
    itoa(x, int_part_buf, 10);
    p = int_part_buf;
    while (*p != '\0') {
        *buf++ = *p++;
    }
    *buf++ = '.';

    float decimal = f - x;
    if (decimal == 0)
        *buf++ = '0';
    else 
        while (decimal > 0) {
            unsigned int y = decimal * 10;  
            *buf++ = y + '0';
            decimal = (decimal * 10) - y;  
            count++;
            if (count == DEFAULT_DECIMAL_COUNT)
                break;
        }
    *buf = '\0';
}

int n_tu(int number, int count) {
    int result = 1;
    while(count-- > 0)
        result *= number;

    return result;
}
