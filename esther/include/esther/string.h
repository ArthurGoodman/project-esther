#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/object.h"

struct std_string;

typedef struct String {
    Object base;

    struct std_string *value;
} String;

#define as_String(obj) ((String *)(obj))

Object *String_new(Esther *es, const char *value);
Object *String_new_len(Esther *es, const char *value, size_t length);
Object *String_new_std(Esther *es, struct std_string *value);

void String_init(Esther *es, Object *self, const char *value, size_t length);
void String_init_std(Esther *es, Object *self, struct std_string *value);

const char *String_c_str(Object *self);

Object *String_append(Object *self, Object *str);
Object *String_append_c_str(Object *self, const char *str);
Object *String_append_char(Object *self, char c);

size_t String_size(Object *self);

bool String_contains(Object *self, char c);

Object *String_virtual_toString(Esther *es, Object *self);
Object *String_virtual_inspect(Esther *es, Object *self);

bool String_virtual_equals(Object *self, Object *obj);

void String_virtual_finalize(ManagedObject *self);

#ifdef __cplusplus
}
#endif
