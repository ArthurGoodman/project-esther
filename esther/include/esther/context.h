#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef struct Object Object;
typedef struct Context Context;
typedef struct Esther Esther;

typedef struct Context {
    Context *parent;
    Object *self;
    Object *here;
} Context;

Context *Context_new(Esther *es);

Object *Context_getSelf(Context *self);
Object *Context_getHere(Context *self);

bool Context_hasLocal(Context *self, const char *name);
Object *Context_getLocal(Context *self, const char *name);
void Context_setLocal(Context *self, const char *name, Object *value);

Object *Context_resolve(Esther *es, Context *self, const char *name);
bool Context_assign(Context *self, const char *name, Object *value);

Context *Context_childContext(Context *self, Object *selfObject, Object *hereObject);

#ifdef __cplusplus
}
#endif
