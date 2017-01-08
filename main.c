#include "io.h"
#include "serial.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    pinMode(25, PIN_OUTPUT);
    setPin(25, PIN_LOW);
    init_uart(19200);
    uart_putchar('H', NULL);
    uart_putchar('\n', NULL);
    init_timers();
    printf("HELLO");

    while (1) {
        setPin(25, PIN_HIGH);
    }
}