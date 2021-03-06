#include "serial.h"

FILE uartOutput = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uartInput = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);

void init_uart(unsigned long baudrate) {
    // unsigned int baudPrescale = (((F_CPU/(baudrate * 8UL))) - 1);
    unsigned int baudPrescale = (F_CPU / (8UL * baudrate)) - 1;

    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
    UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
    UBRR0H = (baudPrescale >> 8);
    UBRR0L = baudPrescale;

    out_buffer = NULL;
    in_buffer = NULL;

    stdout = &uartOutput;
    stdin = &uartInput;
    stderr = &uartOutput;
    // stdout = &uartStream;
    // stdin = &uartStream;
}

void uart_putchar(char c, FILE *stream) {
    if (c == '\n') {
        uart_putchar('\r', NULL);
    }
    while ((UCSR0A & (1 << UDRE0)) == 0);
    UDR0 = c;
}

char uart_getchar(FILE *stream) {
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

byte uart_available() {
    if (UCSR0A & (1 << RXC0)) {
        return 0;
    } else {
        return 1;
    }
}

void uart_display() {
    if (uart_available()) {
        // do uart stuff
    }
}

void uart_display_init() {
    clear_screen();
    move_cursor(0, 10);
    set_color(YELLOW_FOREGROUND);
    printf("Clock");
}