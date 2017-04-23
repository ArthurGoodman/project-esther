#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/object.h"

struct std_string;

typedef struct Class {
    Object base;

    const char *name;
    Class *superclass;
    struct std_string_map *methods;

    Object *(*newInstance)(Esther *esther, Class *self);
} Class;

Class *Class_new(Esther *esther);
Class *Class_new_init(Esther *esther, const char *name, Class *superclass);

void Class_init(Esther *esther, Class *self, const char *name, Class *superclass);

const char *Class_getName(Class *self);

Class *Class_getSuperclass(Class *self);

bool Class_hasMethod(Class *self, const char *name);
Object *Class_getMethod(Class *self, const char *name);
void Class_setMethod(Class *self, const char *name, Object *method);

bool Class_isChildOf(Class *self, Class *_class);

Object *Class_lookup(Class *self, const char *name);

String *Class_virtual_toString(Esther *esther, Object *self);

Object *Class_newInstance(Esther *esther, Class *self);
Object *Class_virtual_newInstance(Esther *esther, Class *self);

#ifdef __cplusplus
}
#endif
