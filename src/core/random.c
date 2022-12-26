#include <core/random.h>

#include <drivers/time/time.h>
#include <arch/x86/isr.h>

static unsigned long int next = 1;

int rand() {
    next = next * 1103515245 + 12345;
    return (unsigned int)(next / 65536) % 32768;
}

void srand(unsigned int seed) {
    next = seed;
}

void auto_srand() {
    next = time(NULL);
}