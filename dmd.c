#include "dmd.h"

void init_dmd() {
    init_spi();
    pinMode(DMD_nOE, PIN_OUTPUT);
    pinMode(DMD_A, PIN_OUTPUT);
    pinMode(DMD_B, PIN_OUTPUT);
    pinMode(DMD_SCLK, PIN_OUTPUT);
}

void flush_data(byte cycleNum) {
    setPin(DMD_nOE, PIN_LOW);
    setPin(DMD_SCLK, PIN_HIGH);
    setPin(DMD_SCLK, PIN_LOW);
    setPin(DMD_A, cycleNum & 1);
    setPin(DMD_B, cycleNum & 2);
    setPin(DMD_nOE, PIN_HIGH);
}

void send_row_group(Display *d, byte offset) {
    printf("Sending\n");
    printf("Accessesing Rows: %d %d %d %d\n", ROW3 + offset, ROW2 + offset, ROW1 + offset, ROW0 + offset);
    // for (int i = 0; i < DISPLAY_STORED_WIDTH; i++) {
    //     // printf("Iteration %d\n", i);
    //     // spi_transfer(d->matrix[ROW3 + offset][i]);
    //     // printf("First transfer\n");
    //     // printf("Trying %d\n", d->matrix[ROW2 + offset][i]);
    //     // spi_transfer(d->matrix[ROW2 + offset][i]);
    //     // printf("Second transfer\n");
    //     // spi_transfer(d->matrix[ROW1 + offset][i]);
    //     // spi_transfer(d->matrix[ROW0 + offset][i]);
    //     for (int j = 0; j < 4; j ++) {
    //         spi_transfer(0);
    //     }
    // }
    for (int i = 0; i < 16; i++) {
        spi_transfer(0);
    }
    flush_data(offset);
}

Display* create_display() {
    Display* d = malloc(sizeof(Display));
    d->matrix = malloc(sizeof(byte*) * DISPLAY_HEIGHT);
    for (int i = 0; i < DISPLAY_HEIGHT; i++) {
        d->matrix[i] = malloc(sizeof(byte) * DISPLAY_STORED_WIDTH);
        for (int j = 0; j < DISPLAY_STORED_WIDTH; j++) {
            d->matrix[i][j] = 0;
        }
    }
    return d;
}

void send_display(Display* d) {
    for (int i = 0; i < 4; i++) {
        send_row_group(d, 0);
    }
}

void print_display(Display* d) {
    printf("DISPLAY:\n");
    for (int i = 0; i < DISPLAY_HEIGHT; i++) {
        for (int j = 0; j < DISPLAY_STORED_WIDTH; j++) {
            printf("%d ", d->matrix[i][j]);
        }
        printf("\n");
    }
}