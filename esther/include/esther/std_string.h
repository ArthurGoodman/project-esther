#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct string {
    size_t size;
    char *data;
};

struct string string_new(const char *data, size_t length);
struct string string_new_c_str(const char *data);
struct string string_new_copy(struct string str);
struct string string_new_empty();

char string_at(struct string *self, size_t i);

void string_append(struct string *self, struct string str);

void string_free(struct string *self);

#ifdef __cplusplus
}
#endif
