#include <core/string.h>

#include <drivers/serial_port.h>
#include <arch/x86/isr.h>

#include <mem/kheap.h>
#include <mem/mem.h>

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

void pop_last_str(char* str) {
    int len = strlen(str);
    str[len-1] = '\0';
}

void append_str(char* str, char c) {
    int len = strlen(str);
    str[len] = c;
    str[len + 1] = '\0';
}

char* strcpy(char* dest, const char* src) {
    int i;
    for (i = 0; src[i] != '\0'; i++) 
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}

char* strtok(char* str, const char* delim) {
    static char* last;
    if (str != NULL) 
        last = str;
    if (last == NULL)
        return NULL;
    
    char* delim_pos = strpbrk(last, delim);
    if (delim_pos == NULL) {
        char* ret = last;
        last = NULL;
        return ret;
    }

    *delim_pos = '\0';
    char* ret = last;
    last = delim_pos + 1;
    return ret;
}

char* strpbrk(const char* str, const char* accept) {
    for (int i = 0; str[i] != '\0'; i++) {
        for (int j = 0; accept[j] != '\0'; j++) {
            if (str[i] == accept[j])
                return ((char*)(str + i));
        }
    }
    return NULL;
}

char* strdup(const char* str) {
    char* copy = (char*)kmalloc(strlen(str) + 1);
    if (copy == NULL) {
        serial_printf("[\x1b[1;33mStringLib\x1b[0;0m] Unsuccessfully allocated memory\n");
        return NULL;
    }

    return memcpy((void*)copy, (const void*)str, strlen(str) + 1);
}

char* strrchr(const char* str, int c) {
    for (int i = strlen(str) - 1; i > 0; i--) {
        if (str[i] == c)
            return ((char*)(str + 1));
    }
    return NULL;
}