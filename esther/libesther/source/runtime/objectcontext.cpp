#include "objectcontext.h"

void ObjectContext::setSelf(Object *self) {
    Context::setSelf(self);
    setHere(self);
}

void ObjectContext::clear() {
}

ObjectContext::ObjectContext(Object *self, Object *here, Context *parent)
    : Context(self, here, parent) {
}
