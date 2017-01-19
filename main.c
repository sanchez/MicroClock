#include "io.h"
#include "serial.h"
#include "util.h"
#include "dmd.h"
#include "time.h"
#include "i2c.h"
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

    i2c_start(0x68 << 1);
    i2c_write(0x00);
    i2c_stop();

    printf("Here\n");

    i2c_start((0x68 << 1) + 1);
    byte value = fromBCD(i2c_read());
    i2c_stop();

    printf("Val: %d\n", value);

    while (1) {
        uart_display();

        i2c_start(0x68 << 1);
        i2c_write(0x00);
        i2c_stop();
        i2c_start((0x68 << 1) + 1);
        byte value = fromBCD(i2c_read());
        byte minute = fromBCD(i2c_read());
        byte hour = fromHourBCD(i2c_read());
        i2c_stop();

        char timeStr[80];
        sprintf(timeStr, "%02d:%02d  ", hour, minute);
        draw_string(test, point(1, 0), 10, timeStr);
    }
}