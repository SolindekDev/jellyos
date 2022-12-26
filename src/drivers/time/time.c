#include <drivers/time/time.h>
#include <drivers/time/cmos.h>

const unsigned char month_days[12] = {
    31,
    28, 
    31, 
    30, 
    31, 
    30, 
    31, 
    31, 
    30, 
    31, 
    30, 
    31
};

int time(int* sec) {
    Date_t date = get_date_cmos();

    int unix_timestamp = 0;
    int unix_years = date.year - 1970;
    unix_timestamp += ((unix_years + 2) / 4) * 86400; 
    unix_timestamp += unix_years * 86400 * 365;

    if (((date.year % 100) || (((date.year % 400) == 0))) && ((date.year % 4) == 0) && (date.month < 3)) { 
        unix_timestamp -= 86400;
    }

    date.month--;
    while (date.month) {
        date.month--;
        unix_timestamp += month_days[date.month] * 86400;
    }

    unix_timestamp += (int)date.second;
    unix_timestamp += ((int)date.minute) * 60;
    unix_timestamp += ((int)date.hour) * 3600;
    unix_timestamp += ((int)date.day - 1) * 86400;

    if (sec != ((void*)0))
        sec = &unix_timestamp;

    return unix_timestamp;
}
