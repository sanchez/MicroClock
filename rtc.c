#include "rtc.h"

byte convert_sec(byte val) {
    return ((val >> 4) * 10) + (val & 0x0F);
}

byte convert_min(byte val) {
    return convert_sec(val);
}

byte convert_hour(byte val) {
    if ((val & 0x40) != 0) {
        byte result = ((val >> 4) & 1) * 10 + (val & 0x0F);
        if ((val & 0x20) != 0)
            return (result == 12) ? 12 : (result + 12);
        else
            return (result == 12) ? 0 : result;
    } else {
        return convert_sec(val);
    }
}

byte convert_day(byte val) {
    return val;
}

byte convert_date(byte val) {
    return ((val >> 4) * 10) + (val & 0x0F);
}

byte convert_month(byte val) {
    return (((val >> 4) & 1) * 10) + (val & 0x0F);
}

byte convert_year(byte val) {
    return ((val >> 4) * 10) + (val & 0x0F);
}

byte i2c_request(byte reg) {
    i2c_start(0xD0);
    i2c_write(reg);
    i2c_stop();

    i2c_start(0xD1);
    byte val = i2c_read();
    i2c_stop();
}

Time get_time() {
    Time t;

    i2c_start((0x68 << 1));
    i2c_write(0x00);
    i2c_stop();

    i2c_start((0x68 << 1) + 1);

    t.sec = convert_sec(i2c_read());
    t.min = convert_min(i2c_read());
    t.hour = convert_hour(i2c_read());
    t.day = convert_day(i2c_read());
    t.date = convert_date(i2c_read());
    t.month = convert_month(i2c_read());
    t.year = convert_year(i2c_read());

    return t;
}