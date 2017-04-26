#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/common.h"

struct std_map;

typedef struct Object Object;
typedef struct Class Class;
typedef struct Esther Esther;
typedef struct String String;
typedef struct Tuple Tuple;

typedef struct Object {
    Object *objectClass;
    struct std_map *attributes;

    Object *(*toString)(Esther *esther, Object *self);
    Object *(*inspect)(Esther *esther, Object *self);
    bool (*equals)(Esther *esther, Object *self, Object *obj);
    bool (*isTrue)();
} Object;

Object *Object_new(Esther *esther);
Object *Object_new_init(Esther *esther, Object *objectClass);

void Object_init(Esther *esther, Object *self, Object *objectClass);

Object *Object_getClass(Object *self);

bool Object_hasAttribute(Object *self, const char *name);
Object *Object_getAttribute(Object *self, const char *name);
void Object_setAttribute(Object *self, const char *name, Object *value);

bool Object_is(Object *self, Object *_class);

Object *Object_resolve(Object *self, const char *name);

Object *Object_call(Esther *esther, Object *self, const char *name, Object *args);
Object *Object_callIfFound(Esther *esther, Object *self, const char *name, Object *args);
Object *Object_call_function(Esther *esther, Object *self, Object *f, Object *args);

Object *Object_toString(Esther *esther, Object *self);
Object *Object_virtual_toString(Esther *esther, Object *self);

Object *Object_inspect(Esther *esther, Object *self);

bool Object_equals(Esther *esther, Object *self, Object *obj);
bool Object_virtual_equals(Esther *esther, Object *self, Object *obj);

bool Object_isTrue(Object *self);
bool Object_virtual_isTrue();

#ifdef __cplusplus
}
#endif
