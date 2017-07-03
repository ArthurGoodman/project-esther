#include "esther/std_string.h"

#include <memory.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "esther/common.h"

struct string_header {
    size_t size, capacity;
};

#define HEADER(str) ((struct string_header *) (str)->data - 1)
#define TOTAL_SIZE(capacity) (sizeof(struct string_header) + (capacity) + 1)
#define ENOUGH_SPACE(str, size) (HEADER(str)->size + (size) <= HEADER(str)->capacity)
#define FREE_SPACE(str) ((str)->data + HEADER(str)->size)

static void extend(struct string *self, size_t size) {
    size_t newCapacity = ceilToPowerOf2(string_size(self) + size);
    self->data = realloc(HEADER(self), TOTAL_SIZE(newCapacity)) + sizeof(struct string_header);
    HEADER(self)->capacity = newCapacity;
}

struct string string_new_empty() {
    return string_new("", 0);
}

struct string string_new_c_str(const char *data) {
    return string_new(data, strlen(data));
}

struct string string_copy(struct string str) {
    return string_new(str.data, string_size(&str));
}

struct string string_new(const char *data, size_t size) {
    struct string_header header = { size, ceilToPowerOf2(size) };
    struct string str = { malloc(TOTAL_SIZE(header.capacity)) + sizeof(struct string_header) };

    *HEADER(&str) = header;

    memcpy(str.data, data, size);
    str.data[size] = '\0';

    return str;
}

size_t string_size(struct string *self) {
    return HEADER(self)->size;
}

size_t string_capacity(struct string *self) {
    return HEADER(self)->capacity;
}

void string_append(struct string *self, struct string str) {
    string_append_data(self, str.data, string_size(&str));
}

void string_append_c_str(struct string *self, const char *data) {
    string_append_data(self, data, strlen(data));
}

void string_append_data(struct string *self, const char *data, size_t size) {
    if (!ENOUGH_SPACE(self, size))
        extend(self, size);

    memcpy(FREE_SPACE(self), data, size + 1);
    HEADER(self)->size += size;
}

size_t string_find(struct string *self, struct string str) {
    return string_find_data(self, str.data, string_size(&str));
}

size_t string_find_char(struct string *self, char c) {
    return string_find_data(self, &c, 1);
}

size_t string_find_c_str(struct string *self, const char *str) {
    return string_find_data(self, str, strlen(str));
}

size_t string_find_data(struct string *self, const char *data, size_t size) {
    if (size == 0)
        return 0;

    for (size_t i = 0; i < string_size(self) - (size - 1); i++) {
        size_t j = 0;
        for (; j < size; j++)
            if (self->data[i + j] != data[j])
                break;

        if (j == size)
            return i;
    }

    return -1;
}

struct string string_substr(struct string *self, size_t i, size_t n) {
    return string_new(self->data + i, min(n, string_size(self) - i));
}

void string_free(struct string *self) {
    free(HEADER(self));
}
