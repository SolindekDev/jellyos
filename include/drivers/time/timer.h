#pragma once

#define TIMER_INPUT_CLOCK_FREQUENCY    1193180
#define TIMER_CHANNEL_0_DATA_PORT    0x40
#define TIMER_CHANNEL_1_DATA_PORT    0x41
#define TIMER_CHANNEL_2_DATA_PORT    0x42
#define TIMER_COMMAND_PORT    0x43

typedef struct TimerFuncArgs_t {
    int timeout; 
    void *user;
} TimerFuncArgs_t;

typedef void (*TimerFunction) (TimerFuncArgs_t*);

#define MAXIMUM_TIMER_FUNCTIONS    32

typedef struct TimerFunctionManager_t {
    int current_index;
    TimerFunction functions[MAXIMUM_TIMER_FUNCTIONS];
    TimerFuncArgs_t func_args[MAXIMUM_TIMER_FUNCTIONS];
} TimerFunctionManager_t;

void init_timer();

void timer_register_function(TimerFunction function, TimerFuncArgs_t *args);

void add_timer_function(TimerFunction fn, int timeout);

int get_ticks();