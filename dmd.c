#include "dmd.h"

Point point(byte x, byte y) {
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

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
    for (int i = 0; i < DISPLAY_STORED_WIDTH; i++) {
        spi_transfer(d->matrix[ROW3 + offset][i]);
        spi_transfer(d->matrix[ROW2 + offset][i]);
        spi_transfer(d->matrix[ROW1 + offset][i]);
        spi_transfer(d->matrix[ROW0 + offset][i]);
    }
    flush_data(offset);
}

Display* create_display() {
    Display* d = malloc(sizeof(Display));
    d->matrix = malloc(sizeof(byte*) * DISPLAY_HEIGHT);
    for (int i = 0; i < DISPLAY_HEIGHT; i++) {
        d->matrix[i] = malloc(sizeof(byte) * DISPLAY_STORED_WIDTH);
        for (int j = 0; j < DISPLAY_STORED_WIDTH; j++) {
            d->matrix[i][j] = 255;
        }
    }
    return d;
}

void send_display(Display *d) {
    for (int i = 0; i < 4; i++) {
        send_row_group(d, i);
    }
}

void print_display(Display *d) {
    printf("DISPLAY:\n");
    for (int i = 0; i < DISPLAY_HEIGHT; i++) {
        for (int j = 0; j < DISPLAY_STORED_WIDTH; j++) {
            printf("%d ", d->matrix[i][j]);
        }
        printf("\n");
    }
}

void set_intensity(Display *d, Point p, byte val) {
    if (p.x < 0 || p.x >= DISPLAY_WIDTH || p.y < 0 || p.y >= DISPLAY_HEIGHT) {
        return;
    }
    int y = p.y;
    int xByte = p.x / 8;
    int xSub = p.x % 8;
    if (val) {
        d->matrix[y][xByte] |= (1 << xSub);
    } else {
        d->matrix[y][xByte] &= ~(1 << xSub);
    }
}

byte get_intensity(Display *d, Point p) {
    int y = p.y;
    int xByte = p.x / 8;
    int xSub = p.x % 8;
    return d->matrix[y][xByte] &= (1 << xSub);
}

void draw_line(Display *d, Point p1, Point p2) {
    float depth = 0.0;
    signed char dx = p2.x - p1.x;
    signed char dy = p2.y - p1.y;
    float pdx = dx;
    float pdy = dy;
    if (pdx < 0)
        pdx *= -1;
    if (pdy < 0)
        pdy *= -1;
    if (pdy > pdx) {
        depth = pdy;
    } else {
        depth = pdx;
    }
    float stepX = dx / depth;
    float stepY = dy / depth;
    float posX = p1.x;
    float posY = p1.y;
    set_intensity(d, point(posX, posY), DISPLAY_ON);
    for (int i = 0; i < depth; i++) {
        posX += stepX;
        posY += stepY;
        set_intensity(d, point(round(posX), round(posY)), DISPLAY_ON);
    }
}

void draw_point(Display *d, Point p, int radius) {
    for (int i = 0; i < 360; i++) {
        float rad = i * RAD_TO_PI;
        float x = cos(rad);
        float y = sin(rad);
        for (int i = 0; i < radius; i++) {
            float tempX = i * x + p.x;
            float tempY = i * y + p.y;
           set_intensity(d, point(round(tempX), round(tempY)), DISPLAY_ON);
        }
    }
}

void draw_circle(Display *d, Point p, int radius) {
    for (int i = 0; i < 360; i++) {
        float rad = i * RAD_TO_PI;
        float x = radius * cos(rad) + p.x;
        float y = radius * sin(rad) + p.y;
        set_intensity(d, point(round(x), round(y)), DISPLAY_ON);
    }
}

void draw_rect(Display *d, Point p1, Point p2) {
    draw_line(d, point(p1.x, p1.y), point(p2.x, p1.y));
    draw_line(d, point(p2.x, p1.y), point(p2.x, p2.y));
    draw_line(d, point(p2.x, p2.y), point(p1.x, p2.y));
    draw_line(d, point(p1.x, p2.y), point(p1.x, p1.y));
}

unsigned long get_letter(char c) {
    if (c == 'A' || c == 'a') {
        return LETTER_A;
    } else if (c == 'B' || c == 'b') {
        return LETTER_B;
    } else if (c == 'C' || c == 'c') {
        return LETTER_C;
    } else if (c == 'D' || c == 'd') {
        return LETTER_D;
    } else if (c == 'E' || c == 'e') {
        return LETTER_E;
    } else if (c == 'F' || c == 'f') {
        return LETTER_F;
    } else if (c == 'G' || c == 'g') {
        return LETTER_G;
    } else if (c == 'H' || c == 'h') {
        return LETTER_H;
    } else if (c == 'I' || c == 'i') {
        return LETTER_I;
    } else if (c == 'J' || c == 'j') {
        return LETTER_J;
    } else if (c == 'K' || c == 'k') {
        return LETTER_K;
    } else if (c == 'L' || c == 'l') {
        return LETTER_L;
    } else if (c == 'M' || c == 'm') {
        return LETTER_M;
    } else if (c == 'N' || c == 'n') {
        return LETTER_N;
    } else if (c == 'O' || c == 'o') {
        return LETTER_O;
    } else if (c == 'P' || c == 'p') {
        return LETTER_P;
    } else if (c == 'Q' || c == 'q') {
        return LETTER_Q;
    } else if (c == 'R' || c == 'r') {
        return LETTER_R;
    } else if (c == 'S' || c == 's') {
        return LETTER_S;
    } else if (c == 'T' || c == 't') {
        return LETTER_T;
    } else if (c == 'U' || c == 'u') {
        return LETTER_U;
    } else if (c == 'V' || c == 'v') {
        return LETTER_V;
    } else if (c == 'W' || c == 'w') {
        return LETTER_W;
    } else if (c == 'X' || c == 'x') {
        return LETTER_X;
    } else if (c == 'Y' || c == 'y') {
        return LETTER_Y;
    } else if (c == 'Z' || c == 'z') {
        return LETTER_Z;
    } else if (c == '1') {
        return LETTER_1;
    } else if (c == '2') {
        return LETTER_2;
    } else if (c == '3') {
        return LETTER_3;
    } else if (c == '4') {
        return LETTER_4;
    } else if (c == '5') {
        return LETTER_5;
    } else if (c == '6') {
        return LETTER_6;
    } else if (c == '7') {
        return LETTER_7;
    } else if (c == '8') {
        return LETTER_8;
    } else if (c == '9') {
        return LETTER_9;
    } else if (c == '0') {
        return LETTER_0;
    } else if (c == ' ') {
        return 0;
    } else {
        return 0;
    }
}

byte get_bit_position(int x, int y, unsigned long l) {
    int bitPos = y * 5 + x;
    return get_bit(l, 24 - bitPos);
}

void draw_char(Display *d, Point p, int height, char c) {
    if (height < 5)
        return;
    unsigned long l = get_letter(c);
    float scale = 5.0/height;
    float k = 24;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < height; j++) {
            byte bit = get_bit_position(floor(j * scale), floor(i * scale), l);
            set_intensity(d, point(j + p.x, i + p.y), !bit);
            k -= scale;
        }
    }
}

void draw_string(Display *d, Point p, int height, char *str) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        draw_char(d, point(height * i + p.x + 1, p.y), height, str[i]);
    }
}