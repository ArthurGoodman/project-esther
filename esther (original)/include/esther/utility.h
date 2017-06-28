#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

struct std_string;

struct std_string *read_file(const char *fileName);

const char *full_path(const char *path);

struct std_string *expand_tabs(const char *str, size_t length);

#ifdef __cplusplus
}
#endif
