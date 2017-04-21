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

String *String_new(Esther *esther);
String *String_new_init(Esther *esther, const char *value);

void String_init(Esther *esther, String *self, const char *value);

const char *String_c_str(String *self);

#ifdef __cplusplus
}
#endif
