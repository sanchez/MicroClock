#include "util.h"

unsigned long millis() {
    unsigned long rt;
    cli();
    rt = clock_ticks;
    sei();
    return rt;
}

void init_timers() {
    cli();
    clock_ticks = 0;
    OCR0A = 124;
    TCCR0A = (1 << WGM01);
    TCCR0B = (1 << CS01) | (1 << CS00);
    TIMSK0 = (1 << 1);
    TIFR0 &= (1 << 1);
    TCNT0 = 0;
    sei();
}

ISR(TIMER0_COMPA_vect) {
    clock_ticks++;
}

void delay(unsigned int period) {
    _delay_ms(period);
}

byte get_bit(unsigned long l, byte pos) {
    unsigned long bit = l >> pos;
    return bit & 1;
}