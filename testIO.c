#include "testIO.h"

unsigned char PORTB = 0;
unsigned char PORTC = 0;
unsigned char PORTD = 0;
unsigned char DDRB = 0;
unsigned char DDRC = 0;
unsigned char DDRD = 0;
unsigned char PINB = 0;
unsigned char PINC = 0;
unsigned char PIND = 0;
unsigned char OCR0A = 0;
unsigned char TCCR0A = 0;
unsigned char TCCR0B = 0;
unsigned char TIMSK0 = 0;
unsigned char TIFR0 = 0;
unsigned char TCNT0 = 0;
unsigned char ADCSRA = 0;
unsigned char ADMUX = 0;
unsigned char ADC = 0;

void cli() {

}

void sei() {

}

unsigned char get_bit(unsigned char val, unsigned char pos) {
    unsigned char result = val & (1 << pos);
    if (result) {
        return 1;
    } else {
        return 0;
    }
}

void print_output_pins() {
    printf("Current Output Registers\n");

    printf("      /-----------------\\\n");
    printf("DDRB  | %d %d %d %d %d %d %d %d |\n", get_bit(DDRB, 7), get_bit(DDRB, 6), get_bit(DDRB, 5), get_bit(DDRB, 4), get_bit(DDRB, 3), get_bit(DDRB, 2), get_bit(DDRB, 1), get_bit(DDRB, 0));
    printf("PORTB | %d %d %d %d %d %d %d %d |\n", get_bit(PORTB, 7), get_bit(PORTB, 6), get_bit(PORTB, 5), get_bit(PORTB, 4), get_bit(PORTB, 3), get_bit(PORTB, 2), get_bit(PORTB, 1), get_bit(PORTB, 0));
    printf("      |-----------------|\n");
    printf("DDRC  | %d %d %d %d %d %d %d %d |\n", get_bit(DDRC, 7), get_bit(DDRC, 6), get_bit(DDRC, 5), get_bit(DDRC, 4), get_bit(DDRC, 3), get_bit(DDRC, 2), get_bit(DDRC, 1), get_bit(DDRC, 0));
    printf("PORTC | %d %d %d %d %d %d %d %d |\n", get_bit(PORTC, 7), get_bit(PORTC, 6), get_bit(PORTC, 5), get_bit(PORTC, 4), get_bit(PORTC, 3), get_bit(PORTC, 2), get_bit(PORTC, 1), get_bit(PORTC, 0));
    printf("      |-----------------|\n");
    printf("DDRD  | %d %d %d %d %d %d %d %d |\n", get_bit(DDRD, 7), get_bit(DDRD, 6), get_bit(DDRD, 5), get_bit(DDRD, 4), get_bit(DDRD, 3), get_bit(DDRD, 2), get_bit(DDRD, 1), get_bit(DDRD, 0));
    printf("PORTD | %d %d %d %d %d %d %d %d |\n", get_bit(PORTD, 7), get_bit(PORTD, 6), get_bit(PORTD, 5), get_bit(PORTD, 4), get_bit(PORTD, 3), get_bit(PORTD, 2), get_bit(PORTD, 1), get_bit(PORTD, 0));
    printf("      \\-----------------/\n");
}