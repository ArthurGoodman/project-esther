#include "esther/std_string.h"

#include <memory.h>
#include <stdlib.h>

struct string string_new(const char *data, size_t length) {
    struct string str;
    string_init(&str, data, length);
    return str;
}

struct string string_new_c_str(const char *data) {
    struct string str;
    string_init_c_str(&str, data);
    return str;
}

struct string string_new_copy(struct string other) {
    struct string str;
    string_init_copy(&str, other);
    return str;
}

struct string string_new_empty() {
    struct string str;
    string_init_empty(&str);
    return str;
}

void string_init(struct string *str, const char *data, size_t length) {
    str->length = length;
    str->data = malloc(length + 1);
    memcpy(str->data, data, length);
    str->data[length] = '\0';
}

void string_init_c_str(struct string *str, const char *data) {
    str->length = strlen(data);
    str->data = strdup(data);
}

void string_init_copy(struct string *str, struct string other) {
    string_init(str, other.data, other.length);
}

void string_init_empty(struct string *str) {
    str->length = 0;
    str->data = strdup("");
}

void string_free(struct string str) {
    free(str.data);
}
