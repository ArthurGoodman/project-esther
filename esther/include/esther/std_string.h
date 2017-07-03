#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct string {
    char *data;
};

struct string string_new_empty();
struct string string_new_c_str(const char *data);
struct string string_copy(struct string str);
struct string string_new(const char *data, size_t size);

size_t string_size(struct string *self);
size_t string_capacity(struct string *self);

void string_append(struct string *self, struct string str);
void string_append_c_str(struct string *self, const char *data);
void string_append_data(struct string *self, const char *data, size_t size);

size_t string_find(struct string *self, struct string str);
size_t string_find_char(struct string *self, char c);
size_t string_find_c_str(struct string *self, const char *str);
size_t string_find_data(struct string *self, const char *data, size_t size);

struct string string_substr(struct string *self, size_t i, size_t n);

void string_free(struct string *self);

#ifdef __cplusplus
}
#endif
