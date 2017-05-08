#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

struct const_string;

struct const_string *const_string_new(const char *data);
struct const_string *const_string_new_len(const char *data, size_t length);

void const_string_delete(struct const_string *str);

size_t const_string_size(struct const_string *str);

bool const_string_compare(struct const_string *a, struct const_string *b);

#ifdef __cplusplus
}
#endif
