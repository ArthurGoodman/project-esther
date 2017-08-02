#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esther/common.h"
#include "esther/id.h"
#include "esther/memory.h"

struct std_map;
struct string;

typedef struct Esther Esther;
typedef struct Object Object;
typedef struct Class Class;
typedef struct String String;
typedef struct Tuple Tuple;

typedef struct ObjectVTable {
    ManagedObjectVTable base;

    Object *(*toString)(Esther *es, Object *self);
    Object *(*inspect)(Esther *es, Object *self);
    bool (*equals)(Object *self, Object *obj);
    bool (*less)(Object *self, Object *obj);
    bool (*isTrue)(Object *self);
    Object *(*clone)(Esther *es, Object *self);
} ObjectVTable;

#define OBJECT_VTABLE(name)                   \
    static ObjectVTable vtable_for_##name = { \
        { { name##_virtual_mapOnRefs },       \
          name##_virtual_finalize },          \
        Object_virtual_toString,              \
        Object_virtual_toString,              \
        Object_virtual_equals,                \
        Object_virtual_less,                  \
        Object_virtual_isTrue,                \
        name##_virtual_clone                  \
    };

Object *Object_virtual_clone_unimplemented(Esther *es, Object *self);

typedef enum ObjectType {
    TArray,
    TClass,
    TException,
    TFunction,
    TMap,
    TObject,
    TString,
    TSymbol,
    TTuple,
    TValueObject
} ObjectType;

typedef struct Object {
    ManagedObject base;

    ObjectType type;
    Object *objectClass;
    struct std_map *attributes;
} Object;

#define as_Object(obj) ((Object *) (obj))

Object *Object_new(Esther *es);

void Object_init(Esther *es, Object *self, ObjectType type, Object *objectClass);

ObjectType Object_getType(Object *self);

Object *Object_getClass(Object *self);

bool Object_hasAttribute(Object *self, ID id);
Object *Object_getAttribute(Object *self, ID id);
void Object_setAttribute(Object *self, ID id, Object *value);

bool Object_is(Object *self, Object *_class);

Object *Object_resolve(Object *self, ID id);

Object *Object_call(Esther *es, Object *self, ID id, size_t n, ...);
Object *Object_call_args(Esther *es, Object *self, ID id, Object *args);
Object *Object_callFunction(Esther *es, Object *self, Object *f, Object *args);

Object *Object_toString(Esther *es, Object *self);
Object *Object_virtual_toString(Esther *es, Object *self);

Object *Object_inspect(Esther *es, Object *self);

bool Object_equals(Object *self, Object *obj);
bool Object_virtual_equals(Object *self, Object *obj);

bool Object_less(Object *self, Object *obj);
bool Object_virtual_less(Object *self, Object *obj);

bool Object_isTrue(Object *self);
bool Object_virtual_isTrue(Object *self);

void Object_copyAttributes(Object *self, Object *target);

Object *Object_clone(Esther *es, Object *self);
Object *Object_virtual_clone(Esther *es, Object *self);

void Object_virtual_mapOnRefs(Mapper *self, MapFunction f);
void Object_virtual_finalize(ManagedObject *self);

#ifdef __cplusplus
}
#endif
