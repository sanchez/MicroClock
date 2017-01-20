#include "sensors.h"

byte get_light() {
    return (read_adc(LIGHT_PIN) / 10);
}

byte get_temp() {
    return (read_adc(TEMP_PIN) / 10);
}

int get_rtc_temp() {

    i2c_start(0x68 << 1);
    i2c_write(0x11);
    i2c_stop();

    i2c_start((0x68 << 1) + 1);
    byte temp = i2c_read();
    i2c_stop();

    return temp;
}