#include "io.h"
#include "serial.h"
#include "util.h"
#include "dmd.h"
#include "i2c.h"
#include "rtc.h"
#include "sensors.h"
#include <stdio.h>
#include <stdlib.h>

#define LIGHT_CUTOFF 35

int main() {
    init_adc();
    init_timers();
    init_uart(19200);
    init_dmd();
    uart_display_init();
    i2c_init();
    init_sensors();

    printf("Hello World\n");

    Display* test = create_display();
    Display* blank = create_display();
    Display* hello = create_display();
    set_current_display(hello);
    draw_string(hello, point(0, 0), 5, "Hello");
    set_display_animation(ANIMATION_FADE);
    delay(1000);

    byte lightsOn = 0;

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

        char dateStr[20];
        sprintf(dateStr, "%2d/%2d", t.date, t.month);
        draw_string(test, point(0, 11), 5, dateStr);

        char tempStr[5];
        sprintf(tempStr, "%.0fC", get_temp());
        draw_string(test, point(21, 11), 5, tempStr);

        if ((get_light() >= LIGHT_CUTOFF) || get_pir()) {
            if (lightsOn == 0) {
                set_current_display(test);
                lightsOn = 1;
            }
        } else {
            if (lightsOn == 1) {
                set_current_display(blank);
                lightsOn = 0;
            }
        }
    }
}