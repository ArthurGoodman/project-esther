#include "esther/context.h"

#include "esther/common.h"
#include "esther/esther.h"

Context *Context_new(Esther *es) {
    Context *self = malloc(sizeof(Context));

    self->parent = NULL;
    self->self = self->here = es->mainObject;

    return self;
}

Object *Context_getSelf(Context *self) {
    return self->self;
}

Object *Context_getHere(Context *self) {
    return self->here;
}

bool Context_hasLocal(Context *self, const char *name) {
    return Object_hasAttribute(self->self, name);
}

Object *Context_getLocal(Context *self, const char *name) {
    return Object_getAttribute(self->self, name);
}

void Context_setLocal(Context *self, const char *name, Object *value) {
    Object_setAttribute(self->self, name, value);
}

Object *Context_resolve(Esther *es, Context *self, const char *name) {
    if (Context_hasLocal(self, name))
        return Context_getLocal(self, name);

    if (self->parent)
        return Context_resolve(es, self->parent, name);

    if (Esther_hasRootObject(es, name))
        return Esther_getRootObject(es, name);

    return NULL;
}

bool Context_assign(Context *self, const char *name, Object *value) {
    if (Context_hasLocal(self, name)) {
        Context_setLocal(self, name, value);
        return true;
    }

    if (self->parent)
        return Context_assign(self->parent, name, value);

    return false;
}

Context *Context_childContext(Context *self, Object *selfObject, Object *hereObject) {
    Context *child = malloc(sizeof(Context));

    child->parent = self;
    child->self = selfObject;
    child->here = hereObject;

    return child;
}
