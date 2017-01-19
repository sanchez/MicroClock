#include "io.h"
#include "serial.h"
#include "util.h"
#include "dmd.h"
#include "i2c.h"
#include "rtc.h"
#include <stdio.h>
#include <stdlib.h>

byte fromBCD(byte val) {
    return (val >> 4) * 10 + (val & 0x0F);
}

byte fromHourBCD(byte val) {
    if ((val & 0x40) != 0) {
        byte result = ((val >> 4) & 1) * 10 + (val & 0x0F);
        if ((val & 0x20) != 0)
            return (result == 12) ? 12 : (result + 12);
        else
            return (result == 12) ? 0 : result;
    } else {
        return fromBCD(val);
    }
}

int main() {
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

        char timeStr[80];
        sprintf(timeStr, "%02d:%02d", t.hour, t.min);
        draw_string(test, point(1, 0), 10, timeStr);
        char dateStr[80];
        sprintf(dateStr, "%2d/%d", t.date, t.month);
        draw_string(test, point(16, 11), 5, dateStr);
    }
}