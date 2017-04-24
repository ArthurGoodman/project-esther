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

String *String_new(Esther *esther, const char *value);
String *String_new_std(Esther *esther, struct std_string *value);

void String_init(Esther *esther, String *self, const char *value);
void String_init_std(Esther *esther, String *self, struct std_string *value);

const char *String_c_str(String *self);

void String_append(String *self, String *str);
void String_append_c_str(String *self, const char *str);

String *String_virtual_toString(Esther *esther, Object *self);
String *String_virtual_inspect(Esther *esther, Object *self);

bool String_virtual_equals(Esther *esther, Object *self, Object *obj);

#ifdef __cplusplus
}
#endif
