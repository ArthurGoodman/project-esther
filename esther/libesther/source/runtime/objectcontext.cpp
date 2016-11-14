#include "objectcontext.h"

//void ObjectContext::setSelf(Object *self) {
//    Context::setSelf(self);
//    setHere(self);
//}

//void ObjectContext::clear() {
//}

void ObjectContext::pushSelf(Object *self) {
    Context::pushSelf(self);
    pushHere(self);
}

void ObjectContext::popSelf() {
    Context::popSelf();
    popHere();
}

ObjectContext::ObjectContext(Object *self, Object *here, Context *parent)
    : Context(self, here, parent) {
}
