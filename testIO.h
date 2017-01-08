#ifndef TESTIO_H
#define TESTIO_H

#include <stdio.h>
#include "util.h"

extern unsigned char PORTB;
extern unsigned char PORTC;
extern unsigned char PORTD;
extern unsigned char DDRB;
extern unsigned char DDRC;
extern unsigned char DDRD;
extern unsigned char PINB;
extern unsigned char PINC;
extern unsigned char PIND;

#define WGM01 0
#define CS01 0
#define CS00 0
extern unsigned char OCR0A;
extern unsigned char TCCR0A;
extern unsigned char TCCR0B;
extern unsigned char TIMSK0;
extern unsigned char TIFR0;
extern unsigned char TCNT0;

#define ADEN 0
#define ADPS1 0
#define ADPS2 0
#define ADSC 0
extern unsigned char ADCSRA;
extern unsigned char ADMUX;
extern unsigned char ADC;

void cli();
void sei();

void print_output_pins();

#endif