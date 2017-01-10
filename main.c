#include "io.h"
#include "serial.h"
#include "util.h"
#include "dmd.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    init_timers();
    init_uart(19200);
    init_dmd();
    printf("Hello World\n");

    Display* test = create_display();
    set_current_display(test);

    while (1) {
        char timeStr[80];
        sprintf(timeStr, "%02d:%02d  ", getHours(), getMinutes());
        draw_string(test, point(1, 0), 10, timeStr);
    }
}