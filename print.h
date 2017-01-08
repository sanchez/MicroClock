#ifndef PRINT_H
#define PRINT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BLACK_FOREGROUND 30
#define RED_FOREGROUND 31
#define GREEN_FOREGROUND 32
#define YELLOW_FOREGROUND 33
#define BLUE_FOREGROUND 34
#define PURPLE_FOREGROUND 35
#define TEAL_FOREGROUND 36
#define WHITE_FOREGROUND 37
#define BLACK_BACKGROUND 40
#define RED_BACKGROUND 41
#define GREEN_BACKGROUND 42
#define YELLOW_BACKGROUND 43
#define BLUE_BACKGROUND 44
#define PURPLE_BACKGROUND 45
#define TEAL_BACKGROUND 46
#define WHITE_BACKGROUND 47

void move_cursor(int x, int y);
void clear_screen();
void set_color(int sgr);
void reset_cursor();
void bold_cursor();
void reverse_cursor();

#endif