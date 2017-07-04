#include "esther/std_string.h"

#include <memory.h>
#include <stdlib.h>
#include <string.h>

#include "esther/common.h"

void string_iterator_next(string_iterator *self) {
    (*self)++;
}

void string_iterator_rnext(string_iterator *self) {
    (*self)--;
}

size_t string_iterator_distance(string_iterator start, string_iterator end) {
    return abs(end - start);
}

struct string_header {
    size_t size, capacity;
};

#define HEADER(str) ((struct string_header *) (str)->data - 1)
#define TOTAL_SIZE(capacity) (sizeof(struct string_header) + (capacity) + 1)
#define ENOUGH_SPACE(str, size) (HEADER(str)->size + (size) <= HEADER(str)->capacity)
#define FREE_SPACE(str) ((str)->data + HEADER(str)->size)

static void extend(struct string *self, size_t size) {
    size_t newCapacity = ceilToPowerOf2(HEADER(self)->size + size);
    self->data = (char *) realloc(HEADER(self), TOTAL_SIZE(newCapacity)) + sizeof(struct string_header);
    HEADER(self)->capacity = newCapacity;
}

struct string string_new_empty() {
    return string_new("", 0);
}

struct string string_new_c_str(const char *data) {
    return string_new(data, strlen(data));
}

struct string string_copy(struct string str) {
    return string_new(str.data, HEADER(&str)->size);
}

struct string string_new(const char *data, size_t size) {
    struct string_header header = { size, ceilToPowerOf2(size) };
    struct string str = { (char *) malloc(TOTAL_SIZE(header.capacity)) + sizeof(struct string_header) };

    *HEADER(&str) = header;

    memcpy(str.data, data, size);
    *FREE_SPACE(&str) = '\0';

    return str;
}

string_iterator string_begin(struct string *self) {
    return self->data;
}

string_iterator string_end(struct string *self) {
    return FREE_SPACE(self);
}

string_iterator string_rbegin(struct string *self) {
    return FREE_SPACE(self) - 1;
}

string_iterator string_rend(struct string *self) {
    return self->data - 1;
}

size_t string_size(struct string *self) {
    return HEADER(self)->size;
}

size_t string_capacity(struct string *self) {
    return HEADER(self)->capacity;
}

void string_append(struct string *self, struct string str) {
    string_append_data(self, str.data, HEADER(&str)->size);
}

void string_append_char(struct string *self, char c) {
    string_append_data(self, &c, 1);
}

void string_append_c_str(struct string *self, const char *data) {
    string_append_data(self, data, strlen(data));
}

void string_append_data(struct string *self, const char *data, size_t size) {
    if (!ENOUGH_SPACE(self, size))
        extend(self, size);

    memcpy(FREE_SPACE(self), data, size);
    HEADER(self)->size += size;
    *FREE_SPACE(self) = '\0';
}

void string_insert(struct string *self, size_t pos, struct string str) {
}

void string_insert_char(struct string *self, size_t pos, char c, size_t n) {
}

void string_insert_c_str(struct string *self, size_t pos, const char *str) {
}

void string_insert_data(struct string *self, size_t pos, const char *data, size_t size) {
}

void string_replace(struct string *self, size_t pos, size_t len, struct string str) {
}

void string_replace_char(struct string *self, size_t pos, size_t len, char c, size_t n) {
}

void string_replace_c_str(struct string *self, size_t pos, size_t len, const char *str) {
}

void string_replace_data(struct string *self, size_t pos, size_t len, const char *data, size_t size) {
}

bool string_isEmpty(struct string *self) {
    return HEADER(self)->size == 0;
}

size_t string_find(struct string *self, struct string str) {
    return string_find_data(self, str.data, HEADER(&str)->size);
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

size_t string_rfind(struct string *self, struct string str) {
    return string_rfind_data(self, str.data, HEADER(&str)->size);
}

size_t string_rfind_char(struct string *self, char c) {
    return string_rfind_data(self, &c, 1);
}

size_t string_rfind_c_str(struct string *self, const char *str) {
    return string_rfind_data(self, str, strlen(str));
}

size_t string_rfind_data(struct string *self, const char *data, size_t size) {
    if (size == 0)
        return 0;

    for (int i = string_size(self) - (size - 1) - 1; i >= 0; i--) {
        size_t j = 0;
        for (; j < size; j++)
            if (self->data[i + j] != data[j])
                break;

        if (j == size)
            return i;
    }

    return -1;
}

bool string_equals(struct string *self, struct string str) {
}

int string_compare(struct string *self, struct string str) {
}

void string_erase(struct string *self, size_t pos, size_t len) {
}

struct string string_substr(struct string *self, size_t pos, size_t len) {
    return string_new(self->data + pos, MIN(len, HEADER(self)->size - pos));
}

void string_clear(struct string *self) {
    HEADER(self)->size = 0;
    *FREE_SPACE(self) = '\0';
}

struct string string_format(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    struct string str = vformat(fmt, ap);
    va_end(ap);
    return str;
}

struct string string_format_va(const char *fmt, va_list ap) {
    return vformat(fmt, ap);
}

void string_free(struct string *self) {
    free(HEADER(self));
}
