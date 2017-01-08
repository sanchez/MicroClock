#include "test.h"

int numtests = 0;

void test_text() {
    reset_cursor();
    printf("Test %d ... ", numtests);
    numtests++;
}

void assert_int(int a, int b, char* fileName, int lineNum) {
    test_text();
    if (a == b) {
        test_true(fileName, lineNum);
    } else {
        test_false(fileName, lineNum);
    }
}

void assert_string(char* a, char* b, char* fileName, int lineNum) {
    test_text();
    if (strcmp(a, b) == 0) {
        test_true(fileName, lineNum);
    } else {
        test_false(fileName, lineNum);
    }
}

void assert_bool(int a, char* fileName, int lineNum) {
    test_text();
    if (a) {
        test_true(fileName, lineNum);
    } else {
        test_false(fileName, lineNum);
    }
}

void test_true(char* fileName, int lineNum) {
    set_color(GREEN_FOREGROUND);
    bold_cursor();
    printf("Passed\n");
    reset_cursor();
}

void test_false(char* fileName, int lineNum) {
    set_color(RED_FOREGROUND);
    bold_cursor();
    printf("Failed\n");
    reset_cursor();
    set_color(YELLOW_FOREGROUND);
    printf("Assert Failed: %s:%d\n", fileName, lineNum);
}