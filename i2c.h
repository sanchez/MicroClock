#include <avr/io.h>
#include <util/twi.h>

#include "util.h"

#define F_SCL 100000UL
#define Prescaler 1
#define TWBR_val ((((F_CPU / F_SCL) / Prescaler) - 16 ) / 2)

#define I2C_WRITE 0
#define I2C_READ 1

void i2c_init();
byte i2c_start(byte address);
byte i2c_write(byte data);
byte i2c_read();
void i2c_stop();