#include <drivers/time/sleep.h>

const int FREQUENCY = 1000000; // 1 MHz

unsigned long get_timer() {
    unsigned long timer;
    asm volatile("rdtsc" : "=A"(timer));
    return timer;
}

void sleep(unsigned int miliseconds) {
    unsigned long start = get_timer();
    unsigned long end = start + miliseconds * FREQUENCY / 1000;
    while (get_timer() < end)
        ;
}