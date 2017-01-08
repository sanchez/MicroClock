#ifndef SPI_H
#define SPI_H

#include <avr/io.h>
#include "io.h"
#include "util.h"
#include "stdio.h"

void init_spi();
char spi_transfer(char data);

#endif