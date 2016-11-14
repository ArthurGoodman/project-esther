#include "objectcontext.h"

void ObjectContext::pushSelf(Object *self) {
    Context::pushSelf(self);
    Context::pushHere(self);
}

void ObjectContext::popSelf() {
    Context::popSelf();
    Context::popHere();
}

void ObjectContext::pushHere(Object *) {
}

void ObjectContext::popHere() {
}

ObjectContext::ObjectContext(Object *self, Object *here, Context *parent)
    : Context(self, here, parent) {
}
