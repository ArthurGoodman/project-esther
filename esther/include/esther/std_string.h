#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

struct std_string;

struct std_string *std_string_new();
struct std_string *std_string_new_init(const char *str);

void std_string_delete(struct std_string *self);

struct std_string *std_string_append(struct std_string *self, struct std_string *std_string);
struct std_string *std_string_append_c_str(struct std_string *self, const char *std_string);

size_t std_string_size(struct std_string *self);

bool std_string_isEmpty(struct std_string *self);

char std_string_at(struct std_string *self, size_t index);

bool std_string_equals(struct std_string *self, struct std_string *str);

const char *std_string_c_str(struct std_string *self);

struct std_string *std_string_format(const char *fmt, ...);

#ifdef __cplusplus
}
#endif
