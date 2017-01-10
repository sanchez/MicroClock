#include "time.h"

byte getHours() {
    return (millis() / 3600000) % 24;
}

byte getMinutes() {
    return (millis() / 60000) % 60;
}

byte getSeconds() {
    return (millis() / 1000) % 60;
}