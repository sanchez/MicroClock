#ifndef SENSORS_H
#define SENSORS_H

#include "io.h"
#include "i2c.h"
#include "serial.h"

#define TEMP_PIN A0
#define LIGHT_PIN A1

byte get_light();
byte get_temp();
int get_rtc_temp();

#endif