#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

struct string;

struct string *string_new();
struct string *string_new_c_str(const char *str);

void string_delete(struct string *str);

struct string *string_append(struct string *self, struct string *str);
struct string *string_append_c_str(struct string *self, const char *str);

size_t string_size(struct string *self);

char string_at(struct string *self, size_t i);

const char *string_c_str(struct string *self);

#ifdef __cplusplus
}
#endif
