#include "spi.h"

void init_spi() {
    byte sreg = SREG;
    cli();
    pinMode(22, PIN_OUTPUT);

    SPCR = (1 << SPE) | (1 << MSTR);
    pinMode(25, PIN_OUTPUT);
    pinMode(23, PIN_OUTPUT);
    SREG = sreg;
    sei();
}

char spi_transfer(char data) {
    SPDR = data;
    while (!(SPSR & (1 << SPIF)));
    return (SPDR);
}