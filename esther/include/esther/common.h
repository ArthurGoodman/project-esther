#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define UNUSED(var) var __attribute__((unused))

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

bool string_compare(void *a, void *b);
bool uint32_compare(void *a, void *b);

#ifdef __cplusplus
}
#endif
