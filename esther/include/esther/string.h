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

#define as_string(obj) ((String *)(obj))

Object *String_new(Esther *esther, const char *value);
Object *String_new_std(Esther *esther, struct std_string *value);

void String_init(Esther *esther, Object *self, const char *value);
void String_init_std(Esther *esther, Object *self, struct std_string *value);

const char *String_c_str(Object *self);

void String_append(Object *self, Object *str);
void String_append_c_str(Object *self, const char *str);

Object *String_virtual_toString(Esther *esther, Object *self);
Object *String_virtual_inspect(Esther *esther, Object *self);

bool String_virtual_equals(Esther *esther, Object *self, Object *obj);

#ifdef __cplusplus
}
#endif
