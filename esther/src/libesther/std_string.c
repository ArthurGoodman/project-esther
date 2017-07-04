#include "esther/std_string.h"

#include <memory.h>
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

static void extend(struct string *this, size_t size) {
    size_t newCapacity = ceilToPowerOf2(string_size(this) + size);
    this->data = (char *) realloc(HEADER(this), TOTAL_SIZE(newCapacity)) + sizeof(struct string_header);
    HEADER(this)->capacity = newCapacity;
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
    struct string str = { (char *) malloc(TOTAL_SIZE(header.capacity)) + sizeof(struct string_header) };

    *HEADER(&str) = header;

    memcpy(str.data, data, size);
    *FREE_SPACE(&str) = '\0';

    return str;
}

size_t string_size(struct string *this) {
    return HEADER(this)->size;
}

size_t string_capacity(struct string *this) {
    return HEADER(this)->capacity;
}

void string_append(struct string *this, struct string str) {
    string_append_data(this, str.data, string_size(&str));
}

void string_append_c_str(struct string *this, const char *data) {
    string_append_data(this, data, strlen(data));
}

void string_append_data(struct string *this, const char *data, size_t size) {
    if (!ENOUGH_SPACE(this, size))
        extend(this, size);

    memcpy(FREE_SPACE(this), data, size);
    HEADER(this)->size += size;
    *FREE_SPACE(this) = '\0';
}

size_t string_find(struct string *this, struct string str) {
    return string_find_data(this, str.data, string_size(&str));
}

size_t string_find_char(struct string *this, char c) {
    return string_find_data(this, &c, 1);
}

size_t string_find_c_str(struct string *this, const char *str) {
    return string_find_data(this, str, strlen(str));
}

size_t string_find_data(struct string *this, const char *data, size_t size) {
    if (size == 0)
        return 0;

    for (size_t i = 0; i < string_size(this) - (size - 1); i++) {
        size_t j = 0;
        for (; j < size; j++)
            if (this->data[i + j] != data[j])
                break;

        if (j == size)
            return i;
    }

    return -1;
}

struct string string_substr(struct string *this, size_t i, size_t n) {
    return string_new(this->data + i, MIN(n, string_size(this) - i));
}

void string_free(struct string *this) {
    free(HEADER(this));
}
