#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "testIO.h"
#include "print.h"
#include "test.h"
#include "io.h"

void test_io() {
    ASSERT_BOOL(DDRB == 0);
    ASSERT_BOOL(PORTB == 0);
    pinMode(25, PIN_OUTPUT);
    ASSERT_BOOL(DDRB);
    ASSERT_BOOL(PORTB == 0);
    setPin(25, PIN_HIGH);
    ASSERT_BOOL(DDRB);
    ASSERT_BOOL(PORTB);
}

int main(int argc, char** argv) {
    clear_screen();
    move_cursor(1, 20);
    bold_cursor();
    printf("Running Tests\n");
    reset_cursor();

    test_io();

    printf("\n");
    print_output_pins();
}