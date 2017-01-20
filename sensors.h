#ifndef SENSORS_H
#define SENSORS_H

#include "io.h"

#define TEMP_PIN A0
#define LIGHT_PIN A1
#define TEMP read_adc(TEMP_PIN)
#define LIGHT read_adc(LIGHT_PIN)

#endif