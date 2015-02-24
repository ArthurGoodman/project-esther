#include "objectcontext.h"

#include "class.h"

ObjectContext::ObjectContext(Object *currentSelf, Class *currentClass, Context *parent, int modifiers)
    : Context(currentSelf, currentClass, parent, modifiers) {
}

ObjectContext::ObjectContext()
    : Context() {
}

void ObjectContext::setLocal(string name, Object *value) {
    currentSelf->setAttribute(name, value);
}

bool ObjectContext::hasId(string name) {
    if (currentSelf->hasAttribute(name))
        return true;

    if (currentClass->lookup(name))
        return true;

    return Context::hasId(name);
}

Object *ObjectContext::getId(string name) {
    if (currentSelf->hasAttribute(name))
        return currentSelf->getAttribute(name);

    if (currentClass->lookup(name))
        return (Object *)currentClass->lookup(name);

    return Context::getId(name);
}

bool ObjectContext::setId(string name, Object *value) {
    //    if (currentSelf->hasAttribute(name)) {
    currentSelf->setAttribute(name, value);
    return true;
    //    }

    //    return Context::setId(name, value);
}
