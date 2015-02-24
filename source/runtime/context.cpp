#include "context.h"

#include "runtime.h"
#include "class.h"
#include "objectcontext.h"

Context::Context(Object *currentSelf, Class *currentClass, Context *parent)
    : Object("Context"), currentSelf(currentSelf), currentClass(currentClass), parent(parent) {
}

Context::Context(Object *currentSelf, Context *parent)
    : Object("Context"), currentSelf(currentSelf), currentClass(currentSelf->getClass()), parent(parent) {
}

Context::Context()
    : Object("Context"), currentSelf(Runtime::getMainObject()), currentClass(currentSelf->getClass()), parent(0) {
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

void Context::setLocal(string name, Object *value) {
    locals[name] = value;
}

bool Context::hasId(string name) {
    if (hasLocal(name))
        return true;

    if (parent)
        return parent->hasId(name);

    if (Runtime::hasRootClass(name))
        return true;

    return false;
}

Object *Context::getId(string name) {
    if (hasLocal(name))
        return getLocal(name);

    if (parent)
        return parent->getId(name);

    if (Runtime::hasRootClass(name))
        return (Object *)Runtime::getRootClass(name);

    return 0;
}

bool Context::setId(string name, Object *value) {
    if (hasLocal(name)) {
        setLocal(name, value);
        return true;
    }

    if (parent)
        return parent->Context::setId(name, value);

    return false;
}

Context *Context::childContext(Object *currentSelf, Class *currentClass) {
    return new Context(currentSelf, currentClass, this);
}

Context *Context::childContext(Object *currentSelf) {
    return new Context(currentSelf, currentSelf->getClass(), this);
}

Context *Context::childContext() {
    return new Context(currentSelf, currentClass, this);
}

Context *Context::objectChildContext(Object *currentSelf, Class *currentClass) {
    return new ObjectContext(currentSelf, currentClass, this);
}

Context *Context::objectChildContext(Object *currentSelf) {
    return new ObjectContext(currentSelf, currentSelf->getClass(), this);
}

Context *Context::objectChildContext() {
    return new ObjectContext(currentSelf, currentClass, this);
}

//Context *Context::childContext() {
//    return new Context(currentSelf, currentClass, this);
//}

//Context *Context::childContext(Object *self) {
//    return new Context(self, this);
//}

//Context *Context::childContext(Object *self, Class *_class) {
//    return new Context(self, _class, this);
//}

bool Context::hasParent() {
    return parent;
}

Context *Context::getParent() {
    return parent ? parent : 0;
}
