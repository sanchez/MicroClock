#ifndef RTC_H
#define RTC_H

#include "util.h"
#include "i2c.h"

typedef struct {
    byte sec;
    byte min;
    byte hour;
    byte day;
    byte date;
    byte month;
    byte year;
} Time;

Time get_time();

#endif