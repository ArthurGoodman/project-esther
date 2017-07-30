#include "esther/context.h"

#include "esther/common.h"
#include "esther/esther.h"

Context *Context_new(Esther *es) {
    Context *self = gc_alloc(sizeof(Context));
    Context_init(self, NULL, es->mainObject, es->mainObject);
    return self;
}

static ManagedObjectVTable vtable_for_Context = {
    .base = {
        .mapOnRefs = Context_virtual_mapOnRefs },
    .finalize = ManagedObject_virtual_finalize
};

void Context_init(Context *self, Context *parent, Object *selfObject, Object *hereObject) {
    ManagedObject_init(&self->base);

    self->parent = parent;
    self->self = selfObject;
    self->here = hereObject;

    *(void **) self = &vtable_for_Context;
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

bool Context_hasLocal(Context *self, struct string name) {
    return Object_hasAttribute(self->here, name);
}

Object *Context_getLocal(Context *self, struct string name) {
    return Object_getAttribute(self->here, name);
}

void Context_setLocal(Context *self, struct string name, Object *value) {
    Object_setAttribute(self->here, name, value);
}

Object *Context_resolve(Esther *es, Context *self, struct string name) {
    if (Context_hasLocal(self, name))
        return Context_getLocal(self, name);

    if (self->parent)
        return Context_resolve(es, self->parent, name);

    if (Esther_hasRootObject(es, str_to_id(name)))
        return Esther_getRootObject(es, str_to_id(name));

    return NULL;
}

bool Context_assign(Context *self, struct string name, Object *value) {
    if (Context_hasLocal(self, name)) {
        Context_setLocal(self, name, value);
        return true;
    }

    if (self->parent)
        return Context_assign(self->parent, name, value);

    return false;
}

Context *Context_childContext(Context *self, Object *selfObject, Object *hereObject) {
    Context *child = gc_alloc(sizeof(Context));
    Context_init(child, self, selfObject, hereObject);
    return child;
}

void Context_virtual_mapOnRefs(Mapper *self, MapFunction f) {
    f(as_Context(self)->parent);
    f(as_Context(self)->self);

    if (as_Context(self)->self != as_Context(self)->here)
        f(as_Context(self)->here);
}
