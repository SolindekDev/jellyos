#include <drivers/time/cmos.h>

#include <core/sprintf.h>
#include <utils/mem.h>

#include <arch/x86/ports.h>

int get_update_in_progress_flag() {
    outb(CMOS_ADDRESS, 0x0A);
    return inb(CMOS_DATA) & 0x80;
}

unsigned char get_rtc_register(int reg) {
    outb(CMOS_ADDRESS, reg);
    return inb(CMOS_DATA);
}

char* get_date_pretty() {
    Date_t date = get_date_cmos();
    static char buf[128];

    sprintf(buf, 
        "%s%d:%s%d:%s%d %d%d:%s%d:%s%d\n", 
        // Time
        date.hour <= 9 ? "0" : "", date.hour, 
        date.minut <= 9 ? "0" : "", date.minut, 
        date.second <= 9 ? "0" : "", date.second, 

        // Date
        date.century, 
        date.year, 
        date.month <= 9 ? "0" : "", date.month, 
        date.day <= 9 ? "0" : "", date.day);

    return (char*)buf;
}

Date_t get_date_cmos() {
    Date_t date;
    while (get_update_in_progress_flag());
    date.second  = get_rtc_register(RTC_REGISTER_SECOND);
    date.minut   = get_rtc_register(RTC_REGISTER_MINUT);
    date.hour    = get_rtc_register(RTC_REGISTER_HOUR);
    date.day     = get_rtc_register(RTC_REGISTER_DAY);
    date.month   = get_rtc_register(RTC_REGISTER_MONTH);
    date.year    = get_rtc_register(RTC_REGISTER_YEAR);
    date.century = 20;

    unsigned char register_b = get_rtc_register(RTC_REGISTER_B);
    if  (!(register_b & 0x04)) {
        date.second = (date.second & 0x0F) + ((date.second / 16) * 10);
        date.minut = (date.minut & 0x0F) + ((date.minut / 16) * 10);
        date.hour = ( (date.hour & 0x0F) + (((date.hour & 0x70) / 16) * 10) ) | (date.hour & 0x80);
        date.day = (date.day & 0x0F) + ((date.day / 16) * 10);
        date.month = (date.month & 0x0F) + ((date.month / 16) * 10);
        date.year = (date.year & 0x0F) + ((date.year / 16) * 10);
    }

    return date;
}