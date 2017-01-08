#ifndef TEST_H
#define TEST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "print.h"

#define ASSERT_BOOL(a) assert_bool(a, __FILE__, __LINE__)
#define ASSERT_INT(a, b) assert_int(a, b, __FILE__, __LINE__)
#define ASSERT_STRING(a, b) assert_string(a, b, __FILE__, __LINE__)

void assert_int(int a, int b, char* fileName, int lineNum);
void assert_string(char* a, char* b, char* fileName, int lineNum);
void assert_bool(int a, char* fileName, int lineNum);
void test_true();
void test_false();

#endif