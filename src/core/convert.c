#include <core/convert.h>
#include <core/string.h>

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

int n_tu(int number, int count) {
    int result = 1;
    while(count-- > 0)
        result *= number;

    return result;
}
