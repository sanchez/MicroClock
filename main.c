#include "io.h"
#include "serial.h"
#include "util.h"
#include "dmd.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    init_timers();
    init_uart(19200);
    init_dmd();
    printf("Hello World\n");

    Display* test = create_display();
    // print_display(test);
    printf("Created\n");
    send_display(test);
    draw_string(test, point(0, 0), 5, "1:2 3:4");
    // set_intensity(test, point(0, 0), DISPLAY_ON);

    while (1) {
        // delay(500);
        //printf("Looping\n");
        send_display(test);
    }
}