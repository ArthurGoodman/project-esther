#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <ctype.h>
#include <limits.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNUSED(var) var __attribute__((unused))

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

bool compare_str(void *a, void *b);
bool compare_id(void *a, void *b);

#ifdef __cplusplus
}
#endif
