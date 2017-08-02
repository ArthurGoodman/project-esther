#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/object.h"
#include "esther/std_string.h"

typedef struct String {
    Object base;

    struct string value;
} String;

#define as_String(obj) ((String *) (obj))

Object *String_new(Esther *es, struct string value);
Object *String_new_move(Esther *es, struct string value);
Object *String_new_c_str(Esther *es, const char *value);

void String_init(Esther *es, Object *self, struct string value);
void String_init_move(Esther *es, Object *self, struct string value);
void String_init_c_str(Esther *es, Object *self, const char *value);

const char *String_c_str(Object *self);
struct string String_value(Object *self);

Object *String_append(Object *self, Object *str);
Object *String_append_c_str(Object *self, const char *str);
Object *String_append_char(Object *self, char c);
Object *String_append_std(Object *self, struct string str);

size_t String_size(Object *self);
size_t String_capacity(Object *self);

bool String_contains(Object *self, char c);

Object *String_virtual_toString(Esther *es, Object *self);
Object *String_virtual_inspect(Esther *es, Object *self);

bool String_virtual_equals(Object *self, Object *obj);

bool String_virtual_less(Object *self, Object *obj);

Object *String_virtual_clone(Esther *es, Object *self);

void String_virtual_finalize(ManagedObject *self);

#ifdef __cplusplus
}
#endif
