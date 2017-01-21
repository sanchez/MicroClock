#ifndef DMD_H
#define DMD_H

#include "io.h"
#include "spi.h"
#include "stdlib.h"
#include "serial.h"
#include "util.h"
#include "print.h"
#include <string.h>

#define PI 3.14159265
#define RAD_TO_PI 0.017453229

#define DMD_nOE 21
#define DMD_B 46
#define DMD_A 47
#define DMD_CLK 25
#define DMD_SCLK 20
#define DMD_DATA 23

#define DISPLAY_WIDTH 32
#define DISPLAY_STORED_WIDTH 4
#define DISPLAY_HEIGHT 16
#define DISPLAY_OFF 1
#define DISPLAY_ON 0
#define ROW0 0
#define ROW1 4
#define ROW2 8
#define ROW3 12

#define LETTER_0 0x1ca529c
#define LETTER_1 0x8c211c
#define LETTER_2 0x8A111C
#define LETTER_3 0x1826098
#define LETTER_4 0x14a7084
#define LETTER_5 0x1c86098
#define LETTER_6 0xc8729c
#define LETTER_7 0x1c21108
#define LETTER_8 0x1ca729c
#define LETTER_9 0x1ca3084
#define LETTER_A 0x453A31
#define LETTER_B 0x1C9725C
#define LETTER_C 0xC8420C
#define LETTER_D 0x1C94A5C
#define LETTER_E 0x1C8721C
#define LETTER_F 0x1C87210
#define LETTER_G 0x64424E
#define LETTER_H 0x1297A52
#define LETTER_I 0x1C4211C
#define LETTER_J 0x1E21098
#define LETTER_K 0x12A6292
#define LETTER_L 0x108421C
#define LETTER_M 0x11DEEB5
#define LETTER_N 0x11CD671
#define LETTER_O 0xE8C62E
#define LETTER_P 0x1C97210
#define LETTER_Q 0x476DC5
#define LETTER_R 0x1C97292
#define LETTER_S 0xE8382E
#define LETTER_T 0x1F21084
#define LETTER_U 0x118C62E
#define LETTER_V 0x118A944
#define LETTER_W 0x15AEF71
#define LETTER_X 0x1151151
#define LETTER_Y 0x1151084
#define LETTER_Z 0x1F1111F
#define LETTER_COLON 0x80200
#define LETTER_SLASH 0x462310

#define ANIMATION_DEFAULT 0
#define ANIMATION_FADE 1

unsigned long characterList[60];
byte characterWidth[60];

typedef struct {
    byte **matrix;
} Display;
Display *currentDisplay;
Display *oldDisplay;
Display *transitionDisplay;
Display *newDisplay;
byte animationCode;

typedef struct {
    byte x;
    byte y;
} Point;
Point point(byte x, byte y);

void flush_data(byte cycleNum);

void init_dmd();
Display* create_display();
void delete_display(Display* d);
void copy_display(Display* d1, Display* d2);
void diff_display(Display* dOut, Display* d1, Display* d2);
void set_current_display(Display *d);
void send_display(Display* d);
void print_display(Display *d);
void set_intensity(Display *d, Point p, byte val);
byte get_intensity(Display *d, Point p);
void draw_line(Display *d, Point p1, Point p2, byte val);
void draw_point(Display *d, Point p, int radius, byte val);
void draw_circle(Display *d, Point p, int radius, byte val);
void draw_rect(Display *d, Point p1, Point p2, byte val);
void draw_box(Display *d, Point p1, Point p2, byte val);
void draw_char(Display *d, Point p, int height, char c);
void draw_string(Display *d, Point p, int height, char *str);
void clear_display(Display *d, byte val);

void set_display_animation(byte ani);

void set_display_intensity(byte val);

#endif