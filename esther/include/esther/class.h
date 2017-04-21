#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/object.h"

struct std_string;

typedef struct Class {
    Object base;
    struct std_string *name;
    Class *superclass;
    struct std_string_map *methods;
} Class;

Class *Class_new(Esther *esther);
Class *Class_new_init(Esther *esther, const char *name, Class *superclass);

void Class_init(Esther *esther, Class *self, const char *name, Class *superclass);

void Class_add_method(Class *self, const char *name, Object *method);

#ifdef __cplusplus
}
#endif
