#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

struct string {
    size_t size, capacity;
    char *data;
};

struct string string_null();
struct string string_new_empty();
struct string string_new_c_str(const char *str);
struct string string_copy(struct string str);
struct string string_new(const char *data, size_t size);
struct string string_new_prealloc(size_t size);
struct string string_const(const char *data);

void string_free(struct string self);

struct string string_assign(struct string *self, struct string str);

void string_resize(struct string *self, size_t size);

void string_append(struct string *self, struct string str);
void string_append_char(struct string *self, char c);
void string_append_c_str(struct string *self, const char *str);
void string_append_buffer(struct string *self, const char *buffer, size_t size);

void string_insert(struct string *self, size_t pos, struct string str);
void string_insert_char(struct string *self, size_t pos, char c, size_t n);
void string_insert_c_str(struct string *self, size_t pos, const char *str);
void string_insert_buffer(struct string *self, size_t pos, const char *buffer, size_t size);

void string_replace(struct string *self, size_t pos, size_t len, struct string str);
void string_replace_char(struct string *self, size_t pos, size_t len, char c, size_t n);
void string_replace_c_str(struct string *self, size_t pos, size_t len, const char *str);
void string_replace_buffer(struct string *self, size_t pos, size_t len, const char *buffer, size_t size);

size_t string_find(struct string self, struct string str, size_t pos);
size_t string_find_char(struct string self, char c, size_t pos);
size_t string_find_c_str(struct string self, const char *str, size_t pos);
size_t string_find_buffer(struct string self, const char *buffer, size_t size, size_t pos);

size_t string_rfind(struct string self, struct string str, size_t pos);
size_t string_rfind_char(struct string self, char c, size_t pos);
size_t string_rfind_c_str(struct string self, const char *str, size_t pos);
size_t string_rfind_buffer(struct string self, const char *buffer, size_t size, size_t pos);

void string_erase(struct string *self, size_t pos, size_t len);

struct string string_substr(struct string self, size_t pos, size_t len);

bool string_equals(struct string self, struct string str);
int string_compare(struct string self, struct string str);

void string_clear(struct string *self);

struct string string_format(const char *fmt, ...);
struct string string_vformat(const char *fmt, va_list ap);

struct string string_escape(struct string self);
struct string string_escape_buffer(const char *buffer, size_t size);

struct string string_quote(struct string self, int offset, int column);

struct string string_expand_tabs(struct string self);
struct string string_expand_tabs_buffer(const char *buffer, size_t size);

#ifdef __cplusplus
}
#endif
