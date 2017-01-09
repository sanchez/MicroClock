#ifndef UTIL_H
#define UTIL_H

#ifndef F_CPU
#define F_CPU 8000000L
#endif
#ifndef __linux__
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#else
#include "testIO.h"
#endif

typedef unsigned char byte;

volatile unsigned long clock_ticks;

unsigned long millis();
void init_timers();

void delay(unsigned int period);

byte get_bit(unsigned long l, byte pos);

#endif