#include <utils/mem.h>

void* memcopy(void* dst, const void* src, int nbytes) {
    char* ret = dst;
    char* p = dst;
    const char* q = src;
    while (nbytes--)
        *p++ = *q++;
    return ret;
}

void memset(unsigned char* dest, unsigned char val, unsigned int len) {
    unsigned char* temp = (unsigned char*)dest;
    for (; len != 0; len--) 
        *temp++ = val;
}