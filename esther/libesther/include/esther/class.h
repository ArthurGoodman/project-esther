#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/object.h"

struct string;

struct Class {
    struct Object base;
    struct string *name;
    struct Class *superclass;
    struct strmap *methods;
};

typedef struct Class *PClass;

PClass Class_new(struct Esther *esther);
PClass Class_new_init(struct Esther *esther, const char *name, PClass superclass);

void Class_init(struct Esther *esther, PClass self, const char *name, PClass superclass);

#ifdef __cplusplus
}
#endif
