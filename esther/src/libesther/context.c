#include "esther/context.h"

#include "esther/common.h"
#include "esther/esther.h"

Context *Context_new(Esther *es) {
    Context *self = malloc(sizeof(Context));
    Context_init(self, NULL, es->mainObject, es->mainObject);
    return self;
}

void Context_init(Context *self, Context *parent, Object *selfObject, Object *hereObject) {
    ManagedObject_init(&self->base);

    self->parent = parent;
    self->self = selfObject;
    self->here = hereObject;

    self->base.base.mapOnReferences = (void (*)(Mapper *, MapFunction))Context_virtual_mapOnReferences;
    self->base.finalize = (void (*)(ManagedObject *))Context_virtual_finalize;
}

Context *Context_getParent(Context *self) {
    return self->parent;
}

Object *Context_getSelf(Context *self) {
    return self->self;
}

Object *Context_getHere(Context *self) {
    return self->here;
}

bool Context_hasLocal(Context *self, const char *name) {
    return Object_hasAttribute(self->here, name);
}

Object *Context_getLocal(Context *self, const char *name) {
    return Object_getAttribute(self->here, name);
}

void Context_setLocal(Context *self, const char *name, Object *value) {
    Object_setAttribute(self->here, name, value);
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
    Context_init(child, self, selfObject, hereObject);
    return child;
}

void Context_virtual_mapOnReferences(Context *self, void (*f)(ManagedObject **)) {
    f((ManagedObject **)&self->parent);
    f((ManagedObject **)&self->self);
    f((ManagedObject **)&self->here);
}

void Context_virtual_finalize(Context *UNUSED(self)) {
}
