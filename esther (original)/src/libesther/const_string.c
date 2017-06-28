#include "esther/const_string.h"

#include <stdlib.h>
#include <string.h>

struct const_string *const_string_new(const char *data) {
    return const_string_new_len(data, strlen(data));
}

struct const_string *const_string_new_len(const char *data, size_t length) {
    struct const_string *str = (struct const_string *)((size_t *)malloc(length + sizeof(size_t)) + 1);
    *((size_t *)str - 1) = length;
    memcpy(str, data, length);
    return str;
}

void const_string_delete(struct const_string *str) {
    free((size_t *)str - 1);
}

size_t const_string_size(struct const_string *str) {
    return *((size_t *)str - 1);
}

bool const_string_compare(struct const_string *a, struct const_string *b) {
    if (const_string_size(a) < const_string_size(b))
        return true;

    for (size_t i = 0; i < const_string_size(a); i++)
        if (((const char *)a)[i] < ((const char *)b)[i])
            return true;
        else if (((const char *)a)[i] > ((const char *)b)[i])
            return false;

    return false;
}
