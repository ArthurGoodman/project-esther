#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/object.h"

struct std_string;

typedef struct Function Function;

typedef struct Class {
    Object base;

    const char *name;
    Object *superclass;
    struct std_map *methods;

    Object *(*newInstance)(Esther *es, Object *self, Object *args);
} Class;

#define as_Class(obj) ((Class *) (obj))

Object *Class_new(Esther *es);
Object *Class_new_init(Esther *es, const char *name, Object *superclass);

void Class_init(Esther *es, Object *self, const char *name, Object *superclass);

const char *Class_getName(Object *self);

Object *Class_getSuperclass(Object *self);

bool Class_hasMethod(Object *self, const char *name);
Object *Class_getMethod(Object *self, const char *name);
void Class_setMethod(Object *self, const char *name, Object *method);
void Class_setMethod_func(Object *self, Object *f);

bool Class_isChildOf(Object *self, Object *_class);

Object *Class_lookup(Object *self, const char *name);

Object *Class_virtual_toString(Esther *es, Object *self);

Object *Class_newInstance(Esther *es, Object *self, Object *args);
Object *Class_virtual_newInstance(Esther *es, Object *self, Object *args);

void Class_virtual_mapOnReferences(Mapper *self, MapFunction f);
void Class_virtual_finalize(ManagedObject *self);

#ifdef __cplusplus
}
#endif
