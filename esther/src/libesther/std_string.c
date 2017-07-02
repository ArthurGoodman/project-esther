#include "esther/std_string.h"

#include <memory.h>
#include <stdlib.h>
#include <string.h>

struct string string_new(const char *data, size_t length) {
    struct string str = { length, malloc(length + 1) };
    memcpy(str.data, data, length);
    str.data[length] = '\0';
    return str;
}

struct string string_new_c_str(const char *data) {
    struct string str = { strlen(data), strdup(data) };
    return str;
}

struct string string_new_copy(struct string str) {
    return string_new(str.data, str.size);
}

struct string string_new_empty() {
    struct string str = { 0, strdup("") };
    return str;
}

char string_at(struct string *self, size_t i) {
    return self->data[i];
}

void string_append(struct string *self, struct string str) {
}

void string_free(struct string *self) {
    free(self->data);
}
