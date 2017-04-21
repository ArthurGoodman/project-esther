#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/object.h"

struct std_string;

struct Class {
    struct Object base;
    struct std_string *name;
    struct Class *superclass;
    struct std_string_map *methods;
};

typedef struct Class *PClass;

PClass Class_new(struct Esther *esther);
PClass Class_new_init(struct Esther *esther, const char *name, PClass superclass);

void Class_init(struct Esther *esther, PClass self, const char *name, PClass superclass);

#ifdef __cplusplus
}
#endif
