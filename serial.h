#ifndef SERIAL_H
#define SERIAL_H

#define F_CPU 8000000L

#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "util.h"
#include "print.h"

typedef struct LinkedBuffer {
    char c;
    struct LinkedBuffer *prev;
    struct LinkedBuffer *next;
} LinkedBuffer;
volatile LinkedBuffer *out_buffer;
volatile LinkedBuffer *in_buffer;

void init_uart(unsigned long baudrate);
void uart_putchar(char c, FILE *stream);
char uart_getchar(FILE *stream);
byte uart_available();
void uart_display();
void uart_display_init();

#endif