#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct string {
    size_t length;
    char *data;
};

struct string *string_new(const char *data, size_t length);
struct string *string_new_c_str(const char *data);
struct string *string_new_empty();

void string_init(struct string *str, const char *data, size_t length);
void string_init_c_str(struct string *str, const char *data);
void string_init_empty(struct string *str);

size_t string_length(struct string *str);
const char *string_c_str(struct string *str);

struct string *string_copy(struct string *str);

#ifdef __cplusplus
}
#endif
