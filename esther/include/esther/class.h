#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/object.h"
#include "esther/std_string.h"

typedef struct Function Function;

typedef struct ClassVTable {
    ObjectVTable base;

    Object *(*newInstance)(Esther *es, Object *self, Object *args);
} ClassVTable;

typedef struct Class {
    Object base;

    struct string name;
    Object *superclass;
    struct std_map *methods;
} Class;

#define as_Class(obj) ((Class *) (obj))

Object *Class_new(Esther *es);
Object *Class_new_init(Esther *es, struct string name, Object *superclass);

void Class_init(Esther *es, Object *self, struct string name, Object *superclass);

struct string Class_getName(Object *self);

Object *Class_getSuperclass(Object *self);

bool Class_hasMethod(Object *self, struct string name);
Object *Class_getMethod(Object *self, struct string name);
void Class_setMethod(Object *self, struct string name, Object *method);
void Class_setMethod_func(Object *self, Object *f);

bool Class_isChildOf(Object *self, Object *_class);

Object *Class_lookup(Object *self, struct string name);

Object *Class_virtual_toString(Esther *es, Object *self);

Object *Class_newInstance(Esther *es, Object *self, Object *args);
Object *Class_virtual_newInstance(Esther *es, Object *self, Object *args);

void Class_virtual_mapOnRefs(Mapper *self, MapFunction f);
void Class_virtual_finalize(ManagedObject *self);

#ifdef __cplusplus
}
#endif
