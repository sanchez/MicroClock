#ifndef SENSORS_H
#define SENSORS_H

#include "io.h"
#include "i2c.h"
#include "serial.h"
#include <math.h>

#define TEMP_PIN A0
#define LIGHT_PIN A1
#define PIR_PIN 42

void init_sensors();

byte get_light();
double get_temp();
int get_rtc_temp();
byte get_pir();

#endif