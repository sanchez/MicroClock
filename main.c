#include "io.h"
#include "serial.h"
#include "util.h"
#include "dmd.h"
#include "i2c.h"
#include "rtc.h"
#include "sensors.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    init_adc();
    init_timers();
    init_uart(19200);
    init_dmd();
    uart_display_init();
    i2c_init();

    printf("Hello World\n");

    Display* test = create_display();
    set_current_display(test);

    while (1) {
        uart_display();

        Time t = get_time();

        //clear_display(test, DISPLAY_OFF);

        char timeStr[20];
        sprintf(timeStr, "%2d%02d", t.hour, t.min);
        draw_string(test, point(0, 0), 10, timeStr);
        char dateUpper[3];
        sprintf(dateUpper, "%d", t.sec / 10);
        char dateLower[3];
        sprintf(dateLower, "%d", t.sec % 10);
        draw_string(test, point(29, 0), 5, dateUpper);
        draw_string(test, point(29, 5), 5, dateLower);

        char lightReading[20];
        sprintf(lightReading, "%2d", get_light());
        draw_string(test, point(25, 11), 5, lightReading);
        // printf("%d\n", read_adc(A0));
    }
}