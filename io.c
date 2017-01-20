#include "io.h"

volatile byte *port_to_register[] = {
    NOT_A_PORT,
    NOT_A_PORT,
    &PORTB,
    &PORTC,
    &PORTD
};

volatile byte *direction_to_register[] = {
    NOT_A_PORT,
    NOT_A_PORT,
    &DDRB,
    &DDRC,
    &DDRD
};

volatile byte *pin_to_register[] = {
    NOT_A_PORT,
    NOT_A_PORT,
    &PINB,
    &PINC,
    &PIND
};

void pinMode(byte pin, byte val) {
    byte bit = pin % 10;
    byte regNum = pin / 10;
    volatile byte *out = direction_to_register[regNum];
    if (val) {
        (*out) |= (1 << bit);
    } else {
        (*out) &= ~(1 << bit);
    }
}

void setPin(byte pin, byte val) {
    byte bit = pin % 10;
    byte regNum = pin / 10;
    volatile byte *out = port_to_register[regNum];
    if (val) {
        (*out) |= (1 << bit);
    } else {
        (*out) &= ~(1 << bit);
    }
}

byte getPin(byte pin) {
    byte bit = pin % 10;
    byte regNum = pin / 10;
    byte result = 0;
    volatile byte *out = pin_to_register[regNum];
    result = (*out) & (1 << bit);
    if (result) {
        return 1;
    } else {
        return 0;
    }
}

void init_adc() {
    ADMUX |= (1 << REFS0);
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN);
}

unsigned int read_adc(byte addr) {
    ADMUX = (ADMUX & 0xF0) | (addr & 0x0F);
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    return ADC;
}