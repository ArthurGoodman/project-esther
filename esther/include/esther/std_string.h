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

size_t string_size(struct string *_this);
size_t string_capacity(struct string *_this);

void string_append(struct string *_this, struct string str);
void string_append_c_str(struct string *_this, const char *data);
void string_append_data(struct string *_this, const char *data, size_t size);

size_t string_find(struct string *_this, struct string str);
size_t string_find_char(struct string *_this, char c);
size_t string_find_c_str(struct string *_this, const char *str);
size_t string_find_data(struct string *_this, const char *data, size_t size);

struct string string_substr(struct string *_this, size_t i, size_t n);

void string_free(struct string *_this);

#ifdef __cplusplus
}
#endif
