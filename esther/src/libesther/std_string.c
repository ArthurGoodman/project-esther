#include "esther/std_string.h"

#include <memory.h>

struct string *string_new(const char *data, size_t length) {
    struct string *str = malloc(sizeof(struct string));
    string_init(str, data, length);
    return str;
}

struct string *string_new_c_str(const char *data) {
    struct string *str = malloc(sizeof(struct string));
    string_init_c_str(str, data);
    return str;
}

struct string *string_new_empty() {
    struct string *str = malloc(sizeof(struct string));
    string_init_empty(str);
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

void string_init_empty(struct string *str) {
    str->length = 0;
    str->data = strdup("");
}

size_t string_length(struct string *str) {
    return str->length;
}

const char *string_c_str(struct string *str) {
    return str->data;
}

struct string *string_copy(struct string *str) {
    return string_new(str->data, str->length);
}
