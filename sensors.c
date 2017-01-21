#include "sensors.h"

byte get_light() {
    return (read_adc(LIGHT_PIN) / 10);
}

double get_temp() {
    double temp;
    temp = log(((10240000 / read_adc(TEMP_PIN)) - 10000));
    temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temp * temp)) * temp);
    return (temp - 273.15);
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

void init_sensors() {
    pinMode(PIR_PIN, PIN_INPUT);
}

byte get_pir() {
    // setPin(PIR_PIN, PIN_HIGH);
    // return 0;
    return getPin(PIR_PIN);
}