#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/object.h"

struct str;

struct Class {
    struct Object base;
    struct string *name;
    struct Class *superclass;
    struct strmap *methods;
};

struct Class *Class_new(struct Esther *esther, const char *name, struct Class *volatile superclass);
void Class_init(struct Esther *esther, struct Class *volatile self, const char *name, struct Class *volatile superclass);

#ifdef __cplusplus
}
#endif
