#ifndef IO_H
#define IO_H

#include "util.h"
#ifndef __linux__
#include <avr/io.h>
#else
#include "testIO.h"
#endif

#define PIN_OUTPUT 1
#define PIN_INPUT 0
#define PIN_HIGH 1
#define PIN_LOW 0

#define NOT_A_PORT 0

volatile byte *port_to_register[5];
volatile byte *direction_to_register[5];
volatile byte *pin_to_register[5];

void pinMode(byte pin, byte val);
void setPin(byte pin, byte val);
byte getPin(byte pin);

#define A0 0
#define A1 1
#define A2 2
#define A3 3
#define A4 4
#define A5 5
#define A6 6
#define A7 7

void init_adc();
unsigned int read_adc(byte addr);

#endif