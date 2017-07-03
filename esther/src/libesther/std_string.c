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

static bool enoughSpace(struct string *self, size_t size) {
    return string_size(self) + size <= string_capacity(self);
}

static char *freeSpace(struct string *self) {
    return self->data + string_size(self);
}

static void extend(struct string *self, size_t size) {
    size_t newCapacity = ceilToPowerOf2(string_size(self) + size);
    self->data = realloc(HEADER(self), TOTAL_SIZE(newCapacity)) + sizeof(struct string_header);
    HEADER(self)->capacity = newCapacity;
}

struct string string_new(const char *data, size_t size) {
    struct string_header header = { size, ceilToPowerOf2(size) };
    struct string str = { malloc(TOTAL_SIZE(header.capacity)) + sizeof(struct string_header) };

    *HEADER(&str) = header;

    memcpy(str.data, data, size);
    str.data[size] = '\0';

    return str;
}

struct string string_new_c_str(const char *data) {
    return string_new(data, strlen(data));
}

struct string string_copy(struct string str) {
    return string_new(str.data, string_size(&str));
}

struct string string_new_empty() {
    return string_new("", 0);
}

size_t string_size(struct string *self) {
    return HEADER(self)->size;
}

size_t string_capacity(struct string *self) {
    return HEADER(self)->capacity;
}

char string_at(struct string *self, size_t i) {
    return self->data[i];
}

void string_append(struct string *self, const char *data, size_t size) {
    if (!enoughSpace(self, size))
        extend(self, size);

    memcpy(freeSpace(self), data, size + 1);
    HEADER(self)->size += size;
}

void string_append_c_str(struct string *self, const char *data) {
    string_append(self, data, strlen(data));
}

void string_append_str(struct string *self, struct string str) {
    string_append(self, str.data, string_size(&str));
}

void string_free(struct string *self) {
    free(HEADER(self));
}
