#include "context.h"

#include "esther.h"
#include "class.h"

namespace esther {

Context::Context(Object *currentSelf, Class *currentClass, Context *parent)
    : Object("Context"), currentSelf(currentSelf), currentClass(currentClass), parent(parent) {
}

Context::Context(Object *currentSelf, Context *parent)
    : Object("Context"), currentSelf(currentSelf), currentClass(currentSelf->getClass()), parent(parent) {
}

Context::Context()
    : Object("Context"), currentSelf(Esther::getMainObject()), currentClass(currentSelf->getClass()), parent(0) {
}

//Context::~Context() {
//    foreach (i, locals)
//        delete i->second;

//    delete parent;
//}

Object *Context::getCurrentSelf() {
    return currentSelf;
}

Class *Context::getCurrentClass() {
    return currentClass;
}

bool Context::isObjectContext() {
    return !parent || currentSelf != parent->currentSelf;
}

bool Context::hasLocal(string name) {
    return locals.find(name) != locals.end();
}

Object *Context::getLocal(string name) {
    return hasLocal(name) ? locals.at(name) : 0;
}

void Context::setLocalOrAttribute(string name, Object *value) {
    if (isObjectContext())
        currentSelf->setAttribute(name, value);
    else
        locals[name] = value;
}

void Context::setLocal(string name, Object *value) {
    locals[name] = value;
}

bool Context::hasId(string name) {
    if (isObjectContext()) {
        if (currentSelf->hasAttribute(name))
            return true;

        if (currentClass->lookup(name))
            return true;
    }

    if (hasLocal(name))
        return true;

    if (parent)
        return parent->hasId(name);

    return false;
}

Object *Context::getId(string name) {
    if (isObjectContext()) {
        if (currentSelf->hasAttribute(name))
            return currentSelf->getAttribute(name);

        if (currentClass->lookup(name))
            return (Object *)currentClass->lookup(name);
    }

    if (hasLocal(name))
        return getLocal(name);

    if (parent)
        return parent->getId(name);

    return 0;
}

bool Context::setId(string name, Object *value) {
    if (isObjectContext() && currentSelf->hasAttribute(name)) {
        currentSelf->setAttribute(name, value);
        return true;
    }

    if (hasLocal(name)) {
        setLocal(name, value);
        return true;
    }

    if (parent)
        return parent->setId(name, value);

    return false;
}

Context *Context::childContext() {
    return new Context(currentSelf, currentClass, this);
}

Context *Context::childContext(Object *self) {
    return new Context(self, this);
}

Context *Context::childContext(Object *self, Class *_class) {
    return new Context(self, _class, this);
}

bool Context::hasParent() {
    return parent;
}

Context *Context::getParent() {
    return parent ? parent : 0;
}
}
