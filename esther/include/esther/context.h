#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "esther/id.h"
#include "esther/memory.h"
#include "esther/std_string.h"

typedef struct Object Object;
typedef struct Context Context;
typedef struct Esther Esther;

typedef struct Context {
    ManagedObject base;

    Context *parent;
    Object *self;
    Object *here;
} Context;

#define as_Context(obj) ((Context *) (obj))

Context *Context_new(Esther *es);

void Context_init(Context *self, Context *parent, Object *selfObject, Object *hereObject);

Context *Context_getParent(Context *self);
Object *Context_getSelf(Context *self);
Object *Context_getHere(Context *self);

bool Context_hasLocal(Context *self, ID id);
Object *Context_getLocal(Context *self, ID id);
void Context_setLocal(Context *self, ID id, Object *value);

Object *Context_resolve(Esther *es, Context *self, ID id);
bool Context_assign(Context *self, ID id, Object *value);

Context *Context_childContext(Context *self, Object *selfObject, Object *hereObject);

void Context_virtual_mapOnRefs(Mapper *self, MapFunction f);

#ifdef __cplusplus
}
#endif
