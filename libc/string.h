#ifndef __STRING__
#define __STRING__

int strlen(const char* str) {
    int i;
    while (str[i] != '\0')
        i++;
    return i;
}

#endif /* __STRING__ */