#ifndef DMD_H
#define DMD_H

#include "io.h"
#include "spi.h"
#include "stdlib.h"
#include "serial.h"
#include "util.h"

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

#define LETTER_0 0xE5294E
#define LETTER_1 0x46108E
#define LETTER_2 0xE8899F
#define LETTER_3 0xC1304C
#define LETTER_4 0xA53842
#define LETTER_5 0xE4304C
#define LETTER_6 0x64394E
#define LETTER_7 0xE10884
#define LETTER_8 0xE5394E
#define LETTER_9 0xE51842
#define LETTER_A 0x453A31
#define LETTER_B 0x1C9725C
#define LETTER_C 0x642106
#define LETTER_D 0xE4A52E
#define LETTER_E 0xE4390E
#define LETTER_F 0xE43908
#define LETTER_G 0x322127
#define LETTER_H 0xA5394A
#define LETTER_I 0xE2108E
#define LETTER_J 0xF1084C
#define LETTER_K 0x953149
#define LETTER_L 0x84210E
#define LETTER_M 0x11DEEB5
#define LETTER_N 0x11CD671
#define LETTER_O 0x476DC4
#define LETTER_P 0xE4B908
#define LETTER_Q 0x476DC5
#define LETTER_R 0xE4B949
#define LETTER_S 0xE8382E
#define LETTER_T 0x1F21084
#define LETTER_U 0x118C544
#define LETTER_V 0x118A944
#define LETTER_W 0x15AEF71
#define LETTER_X 0x1151151
#define LETTER_Y 0x1151084
#define LETTER_Z 0x1F1111F

unsigned long characterList[58];
byte characterWidth[58];

typedef struct {
    byte **matrix;
} Display;

typedef struct {
    byte x;
    byte y;
} Point;
Point point(byte x, byte y);

void flush_data(byte cycleNum);

void init_dmd();
Display* create_display();
void send_display(Display* d);
void print_display(Display *d);
void set_intensity(Display *d, Point p, byte val);
byte get_intensity(Display *d, Point p);
void draw_line(Display *d, Point p1, Point p2);
void draw_point(Display *d, Point p, int radius);
void draw_circle(Display *d, Point p, int radius);
void draw_rect(Display *d, Point p1, Point p2);
void draw_char(Display *d, Point p, int height, char c);

#endif