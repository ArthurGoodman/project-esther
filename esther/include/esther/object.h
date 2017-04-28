#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/common.h"

struct std_map;

typedef struct Esther Esther;
typedef struct Object Object;
typedef struct Class Class;
typedef struct String String;
typedef struct Tuple Tuple;

typedef enum ObjectType {
    TArray,
    TClass,
    TException,
    TFunction,
    TObject,
    TString,
    TSymbol,
    TTuple,
    TValueObject
} ObjectType;

typedef struct Object {
    ObjectType type;
    Object *objectClass;
    struct std_map *attributes;

    Object *(*toString)(Esther *es, Object *self);
    Object *(*inspect)(Esther *es, Object *self);
    bool (*equals)(Esther *es, Object *self, Object *obj);
    bool (*isTrue)();
} Object;

Object *Object_new(Esther *es);

void Object_init(Esther *es, Object *self, ObjectType type, Object *objectClass);

ObjectType Object_getType(Object *self);

Object *Object_getClass(Object *self);

bool Object_hasAttribute(Object *self, const char *name);
Object *Object_getAttribute(Object *self, const char *name);
void Object_setAttribute(Object *self, const char *name, Object *value);

bool Object_is(Object *self, Object *_class);

Object *Object_resolve(Object *self, const char *name);

Object *Object_call(Esther *es, Object *self, const char *name, Object *args);
Object *Object_callIfFound(Esther *es, Object *self, const char *name, Object *args);
Object *Object_call_function(Esther *es, Object *self, Object *f, Object *args);

Object *Object_toString(Esther *es, Object *self);
Object *Object_virtual_toString(Esther *es, Object *self);

Object *Object_inspect(Esther *es, Object *self);

bool Object_equals(Esther *es, Object *self, Object *obj);
bool Object_virtual_equals(Esther *es, Object *self, Object *obj);

bool Object_isTrue(Object *self);
bool Object_virtual_isTrue();

#ifdef __cplusplus
}
#endif
