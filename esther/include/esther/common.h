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

#define UNUSED(x) ((void)(x))

bool string_compare(void *a, void *b);

#ifdef __cplusplus
}
#endif
