#include "context.h"

#include "esther.h"

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

Context::~Context() {
    foreach (i, locals)
        delete i->second;

    delete parent;
}

Object *Context::getCurrentSelf() {
    return currentSelf;
}

Class *Context::getCurrentClass() {
    return currentClass;
}

bool Context::hasLocal(string name) {
    return locals.find(name) != locals.end();
}

void Context::setLocal(string name, Object *value) {
    locals[name] = value;
}

bool Context::hasId(string name) {
    return false;
}

Object *Context::getId(string name) {
    return Esther::getNull();
}

void Context::setId(string name, Object *value) {
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
    return parent ? parent : (Context *)Esther::getNull();
}
}
