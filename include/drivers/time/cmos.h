#pragma once

#define CMOS_ADDRESS 0x70
#define CMOS_DATA    0x71

#define RTC_REGISTER_SECOND  0x00
#define RTC_REGISTER_MINUTE   0x02
#define RTC_REGISTER_HOUR    0x04
#define RTC_REGISTER_DAY     0x07
#define RTC_REGISTER_MONTH   0x08
#define RTC_REGISTER_YEAR    0x09
#define RTC_REGISTER_CENTURY NULL

#define RTC_REGISTER_MEMORY_LOW  0x30
#define RTC_REGISTER_MEMORY_HIGH 0x31

#define RTC_REGISTER_B       0x0B

typedef struct Date_t {
    int second;
    int minute;
    int hour;
    int day;
    int month;
    int year;
    int century;
} Date_t;

int get_update_in_progress_flag();

unsigned char get_rtc_register(int reg);

char* get_date_pretty();

Date_t get_date_cmos();