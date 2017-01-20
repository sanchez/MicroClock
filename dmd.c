#include "dmd.h"

void timer2_func() {
    send_display(currentDisplay);
}

void set_current_display(Display *d) {
    currentDisplay = d;
}

unsigned long characterList[] = {
    0, // SPACE
    0, // !
    0, // "
    0, // #
    0, // $
    0, // %
    0, // &
    0, // '
    0, // (
    0, // )
    0, // *
    0, // +
    0, // ,
    0, // -
    0, // .
    LETTER_SLASH, // /
    LETTER_0, // 0
    LETTER_1, // 1
    LETTER_2,
    LETTER_3,
    LETTER_4,
    LETTER_5,
    LETTER_6,
    LETTER_7,
    LETTER_8,
    LETTER_9,
    LETTER_COLON, // :
    0, // ;
    0, // <
    0, // =
    0, // >
    0, // ?
    0, // @
    LETTER_A,
    LETTER_B,
    LETTER_C,
    LETTER_D,
    LETTER_E,
    LETTER_F,
    LETTER_G,
    LETTER_H,
    LETTER_I,
    LETTER_J,
    LETTER_K,
    LETTER_L,
    LETTER_M,
    LETTER_N,
    LETTER_O,
    LETTER_P,
    LETTER_Q,
    LETTER_R,
    LETTER_S,
    LETTER_T,
    LETTER_U,
    LETTER_V,
    LETTER_W,
    LETTER_X,
    LETTER_Y,
    LETTER_Z
};

byte characterWidth[] = {
    2, // SPACE
    3, // !
    3, // "
    3, // #
    3, // $
    3, // %
    3, // &
    3, // '
    3, // (
    3, // )
    3, // *
    3, // +
    3, // ,
    3, // -
    3, // .
    3, // /
    3, // 0
    3, // 1
    3, // 2
    3, // 3
    3, // 4
    3, // 5
    3, // 6
    3, // 7
    3, // 8
    3, // 9
    1, // :
    3, // ;
    3, // <
    3, // =
    3, // >
    3, // ?
    3, // @
    5, // A
    4, // B
    3, // C
    4, // D
    3, // E
    3, // F
    4, // G
    4, // H
    3, // I
    4, // J
    4, // K
    3, // L
    5, // M
    5, // N
    5, // O
    4, // P
    5, // Q
    4, // R
    5, // S
    5, // T
    5, // U
    5, // V
    5, // W
    5, // X
    5, // Y
    5  // Z
};

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

void draw_line(Display *d, Point p1, Point p2, byte val) {
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
    set_intensity(d, point(posX, posY), val);
    for (int i = 0; i < depth; i++) {
        posX += stepX;
        posY += stepY;
        set_intensity(d, point(round(posX), round(posY)), val);
    }
}

void draw_point(Display *d, Point p, int radius, byte val) {
    for (int i = 0; i < 360; i++) {
        float rad = i * RAD_TO_PI;
        float x = cos(rad);
        float y = sin(rad);
        for (int i = 0; i < radius; i++) {
            float tempX = i * x + p.x;
            float tempY = i * y + p.y;
           set_intensity(d, point(round(tempX), round(tempY)), val);
        }
    }
}

void draw_circle(Display *d, Point p, int radius, byte val) {
    for (int i = 0; i < 360; i++) {
        float rad = i * RAD_TO_PI;
        float x = radius * cos(rad) + p.x;
        float y = radius * sin(rad) + p.y;
        set_intensity(d, point(round(x), round(y)), val);
    }
}

void draw_rect(Display *d, Point p1, Point p2, byte val) {
    signed char stepX = p2.x - p1.x;
    signed char stepY = p2.y - p1.y;
    stepX = stepX / absolute(stepX);
    stepY = stepY / absolute(stepY);
    for (int i = p1.x; i != p2.x; i += stepX) {
        for (int j = p1.y; j != p2.y; j += stepY) {
            set_intensity(d, point(i, j), val);
        }
    }
}

void draw_box(Display *d, Point p1, Point p2, byte val) {
    draw_line(d, point(p1.x, p1.y), point(p2.x, p1.y), val);
    draw_line(d, point(p2.x, p1.y), point(p2.x, p2.y), val);
    draw_line(d, point(p2.x, p2.y), point(p1.x, p2.y), val);
    draw_line(d, point(p1.x, p2.y), point(p1.x, p1.y), val);
}

unsigned long get_letter(char c) {
    if (c >= 32 && c <= 90) {
        return characterList[c - 32];
    } else if (c >= 'a' && c <= 'z') {
        return get_letter(c - 32);
    } else {
        return 0;
    }
}

byte get_letter_width(char c) {
    if (c >= 32 && c <= 90) {
        return characterWidth[c - 32];
    } else if (c >= 'a' && c <= 'z') {
        return get_letter_width(c - 32);
    } else {
        return 3;
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
    int charWidth = ceil(get_letter_width(c) * height / 5.0);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < charWidth; j++) {
            byte bit = get_bit_position(floor(j * scale), floor(i * scale), l);
            set_intensity(d, point(j + p.x, i + p.y), !bit);
            k -= scale;
        }
    }
}

void draw_string(Display *d, Point p, int height, char *str) {
    int len = strlen(str);
    byte posX = p.x;
    for (int i = 0; i < len; i++) {
        draw_char(d, point(posX, p.y), height, str[i]);
        byte charWidth = get_letter_width(str[i]);
        posX += ceil(charWidth * height / 5.0);
        for (int j = 0; j < height; j++) {
            set_intensity(d, point(posX, j + p.y), DISPLAY_OFF);
        }
        posX += 1;
    }
}

void clear_display(Display *d, byte val) {
    for (int i = 0; i < DISPLAY_WIDTH; i++) {
        for (int j = 0; j < DISPLAY_HEIGHT; j++) {
            set_intensity(d, point(i, j), val);
        }
    }
}