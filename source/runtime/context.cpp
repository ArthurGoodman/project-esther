#include "context.h"

#include "runtime.h"
#include "class.h"
#include "objectcontext.h"

Context::Context(Object *currentSelf, Class *currentClass, Context *parent, int modifiers)
    : Object("Context"), currentSelf(currentSelf), currentClass(currentClass), parent(parent), modifiers(modifiers) {
}

Context::Context(Object *currentSelf, Class *currentClass, Context *parent)
    : Object("Context"), currentSelf(currentSelf), currentClass(currentClass), parent(parent), modifiers(0) {
}

Context::Context(Object *currentSelf, Context *parent)
    : Object("Context"), currentSelf(currentSelf), currentClass(currentSelf->getClass()), parent(parent), modifiers(0) {
}

Context::Context()
    : Object("Context"), currentSelf(Runtime::getMainObject()), currentClass(currentSelf->getClass()), parent(0), modifiers(0) {
}

Object *Context::getCurrentSelf() {
    return currentSelf;
}

Class *Context::getCurrentClass() {
    return currentClass;
}

//bool Context::isObjectContext() {
//    return !parent || currentSelf != parent->currentSelf;
//}

bool Context::hasLocal(string name) {
    return locals.find(name) != locals.end();
}

Object *Context::getLocal(string name) {
    return Context::hasLocal(name) ? locals.at(name) : 0;
}

void Context::setLocal(string name, Object *value) {
    locals[name] = value;
}

bool Context::hasId(string name) {
    if (Context::hasLocal(name))
        return true;

    if (parent)
        return parent->hasId(name);

    if (Runtime::hasRootClass(name))
        return true;

    return false;
}

Object *Context::getId(string name) {
    if (Context::hasLocal(name))
        return Context::getLocal(name);

    if (parent)
        return parent->getId(name);

    if (Runtime::hasRootClass(name))
        return (Object *)Runtime::getRootClass(name);

    return 0;
}

bool Context::setId(string name, Object *value) {
    if (Context::hasLocal(name)) {
        Context::setLocal(name, value);
        return true;
    }

    if (parent)
        return parent->setId(name, value);

    return false;
}

Context *Context::childContext(Object *currentSelf, Class *currentClass) {
    return new Context(currentSelf, currentClass, this, modifiers);
}

Context *Context::childContext(Object *currentSelf) {
    return new Context(currentSelf, currentSelf->getClass(), this, modifiers);
}

Context *Context::childContext() {
    return new Context(currentSelf, currentClass, this, modifiers);
}

Context *Context::objectChildContext(Object *currentSelf, Class *currentClass) {
    return new ObjectContext(currentSelf, currentClass, this, modifiers);
}

Context *Context::objectChildContext(Object *currentSelf) {
    return new ObjectContext(currentSelf, currentSelf->getClass(), this, modifiers);
}

Context *Context::objectChildContext() {
    return new ObjectContext(currentSelf, currentClass, this, modifiers);
}

bool Context::hasParent() {
    return parent;
}

Context *Context::getParent() {
    return parent ? parent : (Context *)Runtime::getNull();
}

void Context::setModifier(int modifier, bool state) {
    if (state)
        modifiers |= modifier;
    else
        modifiers &= ~modifier;
}

int Context::getModifier(int modifier) {
    return modifiers & modifier;
}
