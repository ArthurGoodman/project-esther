#include "esther/std_string.h"

#include "esther/common.h"
#include "utility.h"

#define ENOUGH_SPACE(str, n) ((str)->size + (n) <= (str)->capacity)
#define FREE_SPACE(str) ((str)->data + (str)->size)

static void extend(struct string *self, size_t size) {
    size_t newCapacity = ceil_to_power_of_2(self->size + size);
    self->data = realloc(self->data, newCapacity + 1);
    memset(self->data + self->capacity, 0, newCapacity - self->capacity);
    self->capacity = newCapacity;
}

static bool match(const char *a, const char *b, size_t size) {
    for (size_t i = 0; i < size; i++)
        if (a[i] != b[i])
            return false;

    return true;
}

static bool buffer_contains_char(const char *buffer, size_t size, char c) {
    for (size_t i = 0; i < size; i++)
        if (buffer[i] == c)
            return true;

    return false;
}

struct string string_null() {
    struct string str = {.size = 0, .capacity = 0, .data = NULL };
    return str;
}

struct string string_new_empty() {
    return string_new("", 0);
}

struct string string_new_cstr(const char *str) {
    return string_new(str, strlen(str));
}

struct string string_copy(struct string str) {
    return string_new(str.data, str.size);
}

struct string string_new(const char *data, size_t size) {
    struct string str = string_new_prealloc(size);

    memcpy(str.data, data, size);
    str.size = size;
    *FREE_SPACE(&str) = '\0';

    return str;
}

struct string string_new_prealloc(size_t size) {
    size_t capacity = ceil_to_power_of_2(size);
    struct string str = { 0, capacity, calloc(capacity + 1, 1) };

    *FREE_SPACE(&str) = '\0';

    return str;
}

struct string string_const(const char *data) {
    struct string str;
    str.size = str.capacity = strlen(data);
    str.data = (char *) data;
    return str;
}

void string_free(struct string self) {
    free(self.data);
}

struct string string_assign(struct string *self, struct string str) {
    string_free(*self);
    *self = str;
    return *self;
}

void string_resize(struct string *self, size_t size) {
    if (size > self->size && !ENOUGH_SPACE(self, size - self->size))
        extend(self, size - self->size);

    self->size = size;
    *FREE_SPACE(self) = '\0';
}

void string_append(struct string *self, struct string str) {
    string_insert_buffer(self, self->size, str.data, str.size);
}

void string_append_char(struct string *self, char c) {
    string_insert_buffer(self, self->size, &c, 1);
}

void string_append_cstr(struct string *self, const char *str) {
    string_insert_buffer(self, self->size, str, strlen(str));
}

void string_append_buffer(struct string *self, const char *buffer, size_t size) {
    string_insert_buffer(self, self->size, buffer, size);
}

void string_insert(struct string *self, size_t pos, struct string str) {
    string_insert_buffer(self, pos, str.data, str.size);
}

void string_insert_char(struct string *self, size_t pos, char c, size_t n) {
    char buf[n];

    for (size_t i = 0; i < n; i++)
        buf[i] = c;

    string_insert_buffer(self, pos, buf, n);
}

void string_insert_cstr(struct string *self, size_t pos, const char *str) {
    string_insert_buffer(self, pos, str, strlen(str));
}

void string_insert_buffer(struct string *self, size_t pos, const char *buffer, size_t size) {
    if (!ENOUGH_SPACE(self, size))
        extend(self, size);

    memmove(self->data + pos + size, self->data + pos, self->size - pos + 1);
    memcpy(self->data + pos, buffer, size);
    self->size += size;
}

void string_replace(struct string *self, size_t pos, size_t len, struct string str) {
    string_replace_buffer(self, pos, len, str.data, str.size);
}

void string_replace_char(struct string *self, size_t pos, size_t len, char c, size_t n) {
    char buf[n];

    for (size_t i = 0; i < n; i++)
        buf[i] = c;

    string_replace_buffer(self, pos, len, buf, n);
}

void string_replace_cstr(struct string *self, size_t pos, size_t len, const char *str) {
    string_replace_buffer(self, pos, len, str, strlen(str));
}

void string_replace_buffer(struct string *self, size_t pos, size_t len, const char *buffer, size_t size) {
    len = MIN(len, self->size - pos);

    if (size > len && !ENOUGH_SPACE(self, size - len))
        extend(self, size - len);

    memmove(self->data + pos + size, self->data + pos + len, self->size - pos - len + 1);
    memcpy(self->data + pos, buffer, size);
    self->size += size - len;
}

size_t string_find(struct string self, struct string str, size_t pos) {
    return string_find_buffer(self, str.data, str.size, pos);
}

size_t string_find_char(struct string self, char c, size_t pos) {
    return string_find_buffer(self, &c, 1, pos);
}

size_t string_find_cstr(struct string self, const char *str, size_t pos) {
    return string_find_buffer(self, str, strlen(str), pos);
}

size_t string_find_buffer(struct string self, const char *buffer, size_t size, size_t pos) {
    if (size == 0)
        return 0;

    if (self.size == 0)
        return -1;

    for (size_t i = MIN(pos, self.size - 1); i <= self.size - size; i++)
        if (match(self.data + i, buffer, size))
            return i;

    return -1;
}

size_t string_rfind(struct string self, struct string str, size_t pos) {
    return string_rfind_buffer(self, str.data, str.size, pos);
}

size_t string_rfind_char(struct string self, char c, size_t pos) {
    return string_rfind_buffer(self, &c, 1, pos);
}

size_t string_rfind_cstr(struct string self, const char *str, size_t pos) {
    return string_rfind_buffer(self, str, strlen(str), pos);
}

size_t string_rfind_buffer(struct string self, const char *buffer, size_t size, size_t pos) {
    if (size == 0)
        return 0;

    if (self.size == 0)
        return -1;

    for (int i = MIN(pos, self.size - 1) - size + 1; i >= 0; i--)
        if (match(self.data + i, buffer, size))
            return i;

    return -1;
}

//@Fix: Boilerplate?.. Questionmark...
size_t string_find_one_of(struct string self, struct string str, size_t pos) {
    return string_find_one_of_buffer(self, str.data, str.size, pos);
}

size_t string_find_one_of_cstr(struct string self, const char *str, size_t pos) {
    return string_find_one_of_buffer(self, str, strlen(str), pos);
}

size_t string_find_one_of_buffer(struct string self, const char *buffer, size_t size, size_t pos) {
    if (size == 0 || self.size == 0)
        return -1;

    for (size_t i = MIN(pos, self.size - 1); i <= self.size - size; i++)
        if (buffer_contains_char(buffer, size, self.data[i]))
            return i;

    return -1;
}

size_t string_rfind_one_of(struct string self, struct string str, size_t pos) {
    return string_rfind_one_of_buffer(self, str.data, str.size, pos);
}

size_t string_rfind_one_of_cstr(struct string self, const char *str, size_t pos) {
    return string_rfind_one_of_buffer(self, str, strlen(str), pos);
}

size_t string_rfind_one_of_buffer(struct string self, const char *buffer, size_t size, size_t pos) {
    if (size == 0 || self.size == 0)
        return -1;

    for (int i = MIN(pos, self.size - 1) - size + 1; i >= 0; i--)
        if (buffer_contains_char(buffer, size, self.data[i]))
            return i;

    return -1;
}

void string_erase(struct string *self, size_t pos, size_t len) {
    len = MIN(len, self->size - pos);

    memmove(self->data + pos, self->data + pos + len, self->size - pos - len + 1);
    self->size -= len;
}

struct string string_substr(struct string self, size_t pos, size_t len) {
    return string_new(self.data + pos, MIN(len, self.size - pos));
}

bool string_equals(struct string self, struct string str) {
    return string_compare(self, str) == 0;
}

int string_compare(struct string self, struct string str) {
    if (self.size < str.size)
        return -1;

    if (self.size > str.size)
        return 1;

    for (size_t i = 0; i < self.size; i++)
        if (self.data[i] < str.data[i])
            return -1;
        else if (self.data[i] > str.data[i])
            return 1;

    return 0;
}

void string_clear(struct string *self) {
    self->size = 0;
    *FREE_SPACE(self) = '\0';
}

struct string string_format(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    struct string str = string_vformat(fmt, ap);
    va_end(ap);
    return str;
}

struct string string_vformat(const char *fmt, va_list ap) {
    struct string str = string_new_prealloc(strlen(fmt));

    while (true) {
        va_list ap_copy;
        va_copy(ap_copy, ap);
        int needed = vsnprintf(str.data, str.capacity + 1, fmt, ap_copy);
        va_end(ap_copy);

        if (needed <= (int) str.capacity && needed >= 0) {
            str.size = needed;
            return str;
        }

        string_resize(&str, needed > 0 ? needed : (int) str.capacity * 2);
    }
}

struct string string_escape(struct string self) {
    return string_escape_buffer(self.data, self.size);
}

struct string string_escape_buffer(const char *buffer, size_t size) {
    static const char *hex = "0123456789abcdef";

    struct string str = string_new_prealloc(size);

    for (size_t i = 0; i < size; i++) {
        unsigned char c = *buffer++;

        if (isprint(c) && c != '\'' && c != '"' && c != '\\')
            string_append_char(&str, c);
        else {
            string_append_char(&str, '\\');

            switch (c) {
            case '\'':
                string_append_char(&str, '\'');
                break;
            case '"':
                string_append_char(&str, '"');
                break;
            case '\\':
                string_append_char(&str, '\\');
                break;
            case '\a':
                string_append_char(&str, 'a');
                break;
            case '\b':
                string_append_char(&str, 'b');
                break;
            case '\f':
                string_append_char(&str, 'f');
                break;
            case '\n':
                string_append_char(&str, 'n');
                break;
            case '\r':
                string_append_char(&str, 'r');
                break;
            case '\t':
                string_append_char(&str, 't');
                break;
            case '\v':
                string_append_char(&str, 'v');
                break;
            case '\0':
                string_append_char(&str, '0');
                break;

            default:
                string_append_char(&str, 'x');
                string_append_char(&str, hex[c >> 4]);
                string_append_char(&str, hex[c & 0xf]);
            }
        }
    }

    *FREE_SPACE(&str) = '\0';

    return str;
}

//@Investigate: quote cutting under small constraints and at the end of file
struct string string_quote(struct string self, int offset, int column) {
    //@Temp fix
    if (self.data[offset] == '\n') {
        offset--;
        column--;
    }

    static const int max_quote_length = 150;

    int start = string_rfind_char(self, '\n', offset) + 1;
    int end = string_find_char(self, '\n', offset);

    struct string quote = string_substr(self, start, end - start);

    int size = quote.size;

    string_assign(&quote, string_substr(quote, MAX(0, column - max_quote_length / 2), max_quote_length));

    struct string prefix = string_new_cstr(column > max_quote_length / 2 ? "... " : "");
    struct string suffix = string_new_cstr(size - column > max_quote_length / 2 ? " ..." : "");

    int pos = column > max_quote_length / 2 ? max_quote_length / 2 : column;

    struct string pointer = string_new_empty();
    string_insert_char(&pointer, 0, ' ', pos + prefix.size - 1);
    string_append_char(&pointer, '^');

    string_append(&prefix, quote);
    string_assign(&quote, prefix);
    string_append(&quote, suffix);
    string_append_char(&quote, '\n');
    string_append(&quote, pointer);

    string_free(suffix);
    string_free(pointer);

    return quote;
}

struct string string_expand_tabs(struct string self) {
    return string_expand_tabs_buffer(self.data, self.size);
}

struct string string_expand_tabs_buffer(const char *buffer, size_t size) {
    static const size_t tab_size = 4;

    struct string str = string_new_empty();

    for (size_t i = 0, c = 0; i < size; i++)
        if (buffer[i] == '\t') {
            size_t delta = c % tab_size ? c % tab_size : tab_size;
            c += delta;
            string_insert_char(&str, str.size, ' ', delta);
        } else {
            string_append_char(&str, buffer[i]);

            if (buffer[i] == '\n')
                c = 0;
            else
                c++;
        }

    return str;
}
