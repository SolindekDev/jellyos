#include <core/string.h>

int strlen(const char* str) {
    int i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}

char to_uppercase(char c) {
    return (char)c - 0x20;
}

char to_lowercase(char c) {
    return (char)c + 0x20;
}

void reverse(char* str) {
    int c, i, j;
    for (i = 0, j = strlen(str)-1; i < j; i++, j--) {
        c = str[i];
        str[i] = str[j];
        str[j] = c;
    }
}

int strcmp(const char *s1, char *s2) {
    int i = 0;

    while ((s1[i] == s2[i])) {
        if (s2[i++] == 0)
            return 0;
    }
    return 1;
}

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

void pop_last_str(char* str) {
    int len = strlen(str);
    str[len-1] = '\0';
}

void append_str(char* str, char c) {
    int len = strlen(str);
    str[len] = c;
    str[len + 1] = '\0';
}