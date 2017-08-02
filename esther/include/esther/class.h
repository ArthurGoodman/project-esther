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

#define CLASS_VTABLE(name)                          \
    static ClassVTable vtable_for_##name##Class = { \
        { { { Class_virtual_mapOnRefs },            \
            Class_virtual_finalize },               \
          Class_virtual_toString,                   \
          Class_virtual_toString,                   \
          Object_virtual_equals,                    \
          Object_virtual_less,                      \
          Object_virtual_isTrue,                    \
          Object_virtual_clone_unimplemented },     \
        name##Class_virtual_newInstance             \
    };

Object *Class_virtual_unimplemented_newInstance(Esther *es, Object *self, Object *args);

typedef struct Class {
    Object base;

    struct string name;
    Object *superclass;
    struct std_map *methods;
} Class;

#define as_Class(obj) ((Class *) (obj))

Object *Class_new(Esther *es, struct string name, Object *superclass);
Object *Class_new_anonymous(Esther *es);

void Class_init(Esther *es, Object *self, struct string name, Object *superclass);

struct string Class_getName(Object *self);

Object *Class_getSuperclass(Object *self);

bool Class_hasMethod(Object *self, ID id);
Object *Class_getMethod(Object *self, ID id);
void Class_setMethod(Object *self, ID id, Object *method);
void Class_setMethod_func(Object *self, Object *f);

bool Class_isChildOf(Object *self, Object *_class);

Object *Class_lookup(Object *self, ID id);

Object *Class_virtual_toString(Esther *es, Object *self);

Object *Class_newInstance(Esther *es, Object *self, Object *args);
Object *Class_virtual_newInstance(Esther *es, Object *self, Object *args);

void Class_virtual_mapOnRefs(Mapper *self, MapFunction f);
void Class_virtual_finalize(ManagedObject *self);

#ifdef __cplusplus
}
#endif
