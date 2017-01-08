#include "print.h"

void move_cursor(int x, int y) {
    printf("\033[%d;%dH", x, y);
}

void clear_screen() {
    printf("\033[2J");
}

void set_color(int sgr) {
    printf("\033[%dm", sgr);
}

void reset_cursor() {
    set_color(0);
}

void bold_cursor() {
    set_color(1);
}

void reverse_cursor() {
    set_color(7);
}