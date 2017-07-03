#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct string {
    char *data;
};

struct string string_new(const char *data, size_t size);
struct string string_new_c_str(const char *data);
struct string string_copy(struct string str);
struct string string_new_empty();

size_t string_size(struct string *self);
size_t string_capacity(struct string *self);

char string_at(struct string *self, size_t i);

void string_append(struct string *self, const char *data, size_t size);
void string_append_c_str(struct string *self, const char *data);
void string_append_str(struct string *self, struct string str);

void string_free(struct string *self);

#ifdef __cplusplus
}
#endif
