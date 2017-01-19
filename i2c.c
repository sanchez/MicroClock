#include "i2c.h"

void i2c_init() {
    TWBR = (byte) TWBR_val;
}

byte i2c_start(byte address) {
    TWCR = 0;
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    while (!(TWCR & (1 << TWINT)));

    if ((TWSR & 0xF8) != TW_START) {
        return 1;
    }

    TWDR = address;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));

    byte twst = TW_STATUS & 0xF8;
    if ((twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK)) {
        return 1;
    }

    return 0;
}

byte i2c_write(byte data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));

    if ((TWSR & 0xF8) != TW_MT_DATA_ACK) {
        return 1;
    }

    return 0;
}

byte i2c_read() {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}

void i2c_stop() {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}