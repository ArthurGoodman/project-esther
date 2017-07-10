#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

size_t ceil_to_power_of_2(size_t n);

struct string read_file(const char *fileName);

const char *full_path(const char *path);

struct string executable_dir();

#ifdef __cplusplus
}
#endif
