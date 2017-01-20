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

    // millis timer
    clock_ticks = 0;
    OCR0A = 249;
    TCCR0A = (1 << WGM01);
    TCCR0B = (1 << CS01) | (1 << CS00);
    TIMSK0 = (1 << 1);
    TIFR0 &= (1 << 1);
    TCNT0 = 0;

    // display timer
    TCCR2A = 0;
    TCCR2B = (1 << CS22) | (1 << CS22) | (1 << CS22);
    OCR2A = 12;
    TIMSK2 = (1 << 1);
    TCNT2 = 0;
    sei();
}

ISR(TIMER0_COMPA_vect) {
    clock_ticks++;
}

ISR(TIMER2_COMPA_vect) {
    timer2_func();
}

void delay(unsigned int period) {
    _delay_ms(period);
}

byte get_bit(unsigned long l, byte pos) {
    unsigned long bit = l >> pos;
    return bit & 1;
}

signed char absolute(signed char val) {
    if (val < 0)
        return val * -1;
    else
        return val;
}