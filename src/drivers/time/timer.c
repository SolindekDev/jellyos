#include <drivers/time/timer.h>

#include <mem/mem.h>
#include <core/print.h>
#include <drivers/serial_port.h>

#include <arch/x86/isr.h>
#include <arch/x86/ports.h>

int ticks = 0;
unsigned int frequency = 0;
TimerFunctionManager_t timer_function_manager;

void timer_set_frequency(unsigned int f) {
    frequency = f;
    unsigned int divisor = TIMER_INPUT_CLOCK_FREQUENCY / f;
    outb(TIMER_COMMAND_PORT, 0b00110110);
    outb(TIMER_CHANNEL_0_DATA_PORT, divisor & 0xFF);
    outb(TIMER_CHANNEL_0_DATA_PORT, (divisor >> 8) & 0xFF);
}

int get_ticks() {
    return ticks;
}

void timer_handler(registers_t* r) {
    int i;
    TimerFuncArgs_t *args = NULL;
    ticks++;
    for (i = 0; i < MAXIMUM_TIMER_FUNCTIONS; i++) {
        args = &timer_function_manager.func_args[i];
        if (args->timeout == 0)
            continue;
        if ((ticks % args->timeout) == 0) {
            timer_function_manager.functions[i](args);
        }
    }
}

void add_timer_function(TimerFunction fn, int timeout) {
    TimerFuncArgs_t args = {0};
    args.timeout = timeout;
    timer_register_function(fn, &args);
}

void timer_register_function(TimerFunction function, TimerFuncArgs_t *args) {
    int index = 0;
    if (function == NULL || args == NULL) {
        printf("ERROR: failed to register timer function %x\n", function);
        return;
    }
    index = (++timer_function_manager.current_index) % MAXIMUM_TIMER_FUNCTIONS;
    timer_function_manager.current_index = index;
    timer_function_manager.functions[index] = function;
    memcpy(&timer_function_manager.func_args[index], args, sizeof(TimerFuncArgs_t));
}

void init_timer() {
    serial_printf("[\x1b[1;33mTimer\x1b[0;0m] Initializing timer\n");
    timer_set_frequency(60);
    isr_register_interrupt_handler(IRQ_BASE, timer_handler);
}