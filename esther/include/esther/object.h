#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/common.h"

struct std_string_map;

typedef struct Class Class;
typedef struct Object Object;
typedef struct Esther Esther;
typedef struct String String;
typedef struct Tuple Tuple;

typedef struct Object {
    Class *objectClass;
    struct std_string_map *attributes;

    String *(*toString)(Esther *esther, Object *self);
} Object;

Object *Object_new(Esther *esther);
Object *Object_new_init(Esther *esther, Class *objectClass);

void Object_init(Esther *esther, Object *self, Class *objectClass);

bool Object_hasAttribute(Object *self, const char *name);
Object *Object_getAttribute(Object *self, const char *name);
void Object_setAttribute(Object *self, const char *name, Object *value);

bool Object_is(Object *self, Class *_class);

Object *Object_resolve(Object *self, const char *name);

String *Object_toString(Esther *esther, Object *self);
String *Object_virtual_toString(Esther *esther, Object *self);

#ifdef __cplusplus
}
#endif
