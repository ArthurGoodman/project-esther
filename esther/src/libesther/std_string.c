#include "esther/std_string.h"

#include <memory.h>
#include <stdlib.h>
#include <string.h>

#include "esther/common.h"
#include "esther/utility.h"

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

static bool match(const char *a, const char *b, size_t n) {
    for (size_t i = 0; i < n; i++)
        if (a[i] != b[i])
            return false;

    return true;
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

void string_free(struct string *self) {
    free(HEADER(self));
}

size_t string_size(struct string *self) {
    return HEADER(self)->size;
}

size_t string_capacity(struct string *self) {
    return HEADER(self)->capacity;
}

bool string_isEmpty(struct string *self) {
    return HEADER(self)->size == 0;
}

void string_append(struct string *self, struct string str) {
    string_insert_buffer(self, HEADER(self)->size, str.data, HEADER(&str)->size);
}

void string_append_char(struct string *self, char c) {
    string_insert_buffer(self, HEADER(self)->size, &c, 1);
}

void string_append_c_str(struct string *self, const char *data) {
    string_insert_buffer(self, HEADER(self)->size, data, strlen(data));
}

void string_append_buffer(struct string *self, const char *data, size_t size) {
    string_insert_buffer(self, HEADER(self)->size, data, size);
}

void string_insert(struct string *self, size_t pos, struct string str) {
    string_insert_buffer(self, pos, str.data, HEADER(&str)->size);
}

void string_insert_char(struct string *self, size_t pos, char c, size_t n) {
    char buf[n];

    for (size_t i = 0; i < n; i++)
        buf[i] = c;

    string_insert_buffer(self, pos, buf, n);
}

void string_insert_c_str(struct string *self, size_t pos, const char *str) {
    string_insert_buffer(self, pos, str, strlen(str));
}

void string_insert_buffer(struct string *self, size_t pos, const char *data, size_t size) {
    if (!ENOUGH_SPACE(self, size))
        extend(self, size);

    memmove(self->data + pos + size, self->data + pos, HEADER(self)->size - pos + 1);
    memcpy(self->data + pos, data, size);
    HEADER(self)->size += size;
}

void string_replace(struct string *self, size_t pos, size_t len, struct string str) {
    string_replace_buffer(self, pos, len, str.data, HEADER(&str)->size);
}

void string_replace_char(struct string *self, size_t pos, size_t len, char c, size_t n) {
    char buf[n];

    for (size_t i = 0; i < n; i++)
        buf[i] = c;

    string_replace_buffer(self, pos, len, buf, n);
}

void string_replace_c_str(struct string *self, size_t pos, size_t len, const char *str) {
    string_replace_buffer(self, pos, len, str, strlen(str));
}

void string_replace_buffer(struct string *self, size_t pos, size_t len, const char *data, size_t size) {
    len = MIN(len, HEADER(self)->size - pos);

    if (size > len && !ENOUGH_SPACE(self, size - len))
        extend(self, size - len);

    memmove(self->data + pos + size, self->data + pos + len, HEADER(self)->size - pos - len + 1);
    memcpy(self->data + pos, data, size);
    HEADER(self)->size += size - len;
}

size_t string_find(struct string *self, struct string str) {
    return string_find_buffer(self, str.data, HEADER(&str)->size);
}

size_t string_find_char(struct string *self, char c) {
    return string_find_buffer(self, &c, 1);
}

size_t string_find_c_str(struct string *self, const char *str) {
    return string_find_buffer(self, str, strlen(str));
}

size_t string_find_buffer(struct string *self, const char *data, size_t size) {
    if (size == 0)
        return 0;

    for (size_t i = 0; i < HEADER(self)->size - size + 1; i++)
        if (match(self->data + i, data, size))
            return i;

    return -1;
}

size_t string_rfind(struct string *self, struct string str) {
    return string_rfind_buffer(self, str.data, HEADER(&str)->size);
}

size_t string_rfind_char(struct string *self, char c) {
    return string_rfind_buffer(self, &c, 1);
}

size_t string_rfind_c_str(struct string *self, const char *str) {
    return string_rfind_buffer(self, str, strlen(str));
}

size_t string_rfind_buffer(struct string *self, const char *data, size_t size) {
    if (size == 0)
        return 0;

    for (int i = HEADER(self)->size - size; i >= 0; i--)
        if (match(self->data + i, data, size))
            return i;

    return -1;
}

void string_erase(struct string *self, size_t pos, size_t len) {
    len = MIN(len, HEADER(self)->size - pos);

    memmove(self->data + pos, self->data + pos + len, HEADER(self)->size - pos - len + 1);
    HEADER(self)->size -= len;
}

struct string string_substr(struct string *self, size_t pos, size_t len) {
    return string_new(self->data + pos, MIN(len, HEADER(self)->size - pos));
}

bool string_equals(struct string *self, struct string str) {
    return string_compare(self, str) == 0;
}

int string_compare(struct string *self, struct string str) {
    if (HEADER(self)->size < HEADER(&str)->size)
        return -1;

    if (HEADER(self)->size > HEADER(&str)->size)
        return 1;

    for (size_t i = 0; i < HEADER(self)->size; i++)
        if (self->data[i] < str.data[i])
            return -1;
        else if (self->data[i] > str.data[i])
            return 1;

    return 0;
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
