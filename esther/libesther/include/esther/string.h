#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/object.h"

struct std_string;

struct String {
    struct Object base;
    struct std_string *value;
};

typedef struct String *PString;

PString String_new(struct Esther *esther);
PString String_new_init(struct Esther *esther, const char *value);

void String_init(struct Esther *esther, PString self, const char *value);

const char *String_c_str(PString self);

#ifdef __cplusplus
}
#endif
