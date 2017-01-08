#include "io.h"
#include "serial.h"
#include "util.h"
#include "dmd.h"
#include "spi.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    init_timers();
    init_uart(19200);
    init_spi();

    init_dmd();
    // init_uart(19200);
    // init_timers();
    // printf("HELLO\n");
    // pinMode(25, PIN_OUTPUT);
    // setPin(25, PIN_HIGH);
    // delay(5000);
    // printf("LEGO\n");

    Display* test = create_display();
    // print_display(test);
    printf("Created\n");
    // send_display(test);

    while (1) {
        // delay(500);
        //printf("Looping\n");
        // send_display(test);
        for (int i = 0; i < 16; i++) {
            spi_transfer(0);
        }
        flush_data(0);
        for (int i = 0; i < 16; i++) {
            spi_transfer(0);
        }
        flush_data(1);
    }
}