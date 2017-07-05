#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

bool isControlCharacter(char c);

size_t ceilToPowerOf2(size_t n);

struct string vformat(const char *fmt, va_list ap);

struct string read_file(const char *fileName);

const char *full_path(const char *path);

struct string expand_tabs(const char *str, size_t length);

#ifdef __cplusplus
}
#endif
