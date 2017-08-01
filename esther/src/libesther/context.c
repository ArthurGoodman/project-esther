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

bool Context_hasLocal(Context *self, ID id) {
    return Object_hasAttribute(self->here, id);
}

Object *Context_getLocal(Context *self, ID id) {
    return Object_getAttribute(self->here, id);
}

void Context_setLocal(Context *self, ID id, Object *value) {
    Object_setAttribute(self->here, id, value);
}

Object *Context_resolve(Esther *es, Context *self, ID id) {
    if (Context_hasLocal(self, id))
        return Context_getLocal(self, id);

    if (self->parent)
        return Context_resolve(es, self->parent, id);

    if (Esther_hasRootObject(es, id))
        return Esther_getRootObject(es, id);

    return NULL;
}

bool Context_assign(Context *self, ID id, Object *value) {
    if (Context_hasLocal(self, id)) {
        Context_setLocal(self, id, value);
        return true;
    }

    if (self->parent)
        return Context_assign(self->parent, id, value);

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
