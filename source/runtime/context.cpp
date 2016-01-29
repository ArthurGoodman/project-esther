#include "context.h"

#include "runtime.h"
#include "class.h"
#include "objectcontext.h"
#include "runtimeerror.h"
#include "method.h"

Context::Context(IObject *currentSelf, Class *currentClass, Context *parent, int modifiers)
    : Object("Context"), currentSelf(currentSelf), currentClass(currentClass), parent(parent), modifiers(modifiers) {
}

Context::Context(IObject *currentSelf, Class *currentClass, Context *parent)
    : Object("Context"), currentSelf(currentSelf), currentClass(currentClass), parent(parent), modifiers(0) {
}

Context::Context(IObject *currentSelf, Context *parent)
    : Object("Context"), currentSelf(currentSelf), currentClass(currentSelf->getClass()), parent(parent), modifiers(0) {
}

Context::Context()
    : Object("Context"), currentSelf(Runtime::getMainObject()), currentClass(currentSelf->getClass()), parent(0), modifiers(0) {
}

IObject *Context::getCurrentSelf() {
    return currentSelf;
}

Class *Context::getCurrentClass() {
    return currentClass;
}

//bool Context::isObjectContext() {
//    return !parent || currentSelf != parent->currentSelf;
//}

bool Context::hasLocal(const std::string &name) {
    return locals.find(name) != locals.end();
}

IObject *Context::getLocal(const std::string &name) {
    return Context::hasLocal(name) ? locals.at(name) : 0;
}

void Context::setLocal(const std::string &name, IObject *value) {
    locals[name] = value;
}

bool Context::hasId(const std::string &name) {
    if (Context::hasLocal(name))
        return true;

    if (parent)
        return parent->hasId(name);

    if (Runtime::hasRootClass(name))
        return true;

    return false;
}

IObject *Context::getId(const std::string &name) {
    if (Context::hasLocal(name))
        return Context::getLocal(name);

    if (parent)
        return parent->getId(name);

    if (Runtime::hasRootClass(name))
        return (IObject *)Runtime::getRootClass(name);

    return 0;
}

bool Context::setId(const std::string &name, IObject *value) {
    if (Context::hasLocal(name)) {
        Context::setLocal(name, value);
        return true;
    }

    if (parent)
        return parent->setId(name, value);

    return false;
}

Context *Context::childContext(IObject *currentSelf, Class *currentClass) {
    return new Context(currentSelf, currentClass, this, modifiers);
}

Context *Context::childContext(IObject *currentSelf) {
    return new Context(currentSelf, currentSelf->getClass(), this, modifiers);
}

Context *Context::childContext() {
    return new Context(currentSelf, currentClass, this, modifiers);
}

Context *Context::objectChildContext(IObject *currentSelf, Class *currentClass) {
    return new ObjectContext(currentSelf, currentClass, this, modifiers);
}

Context *Context::objectChildContext(IObject *currentSelf) {
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

IObject *Context::getSelfForMethod(Method *method) {
    if (method->suitableFor(currentSelf))
        return currentSelf;

    if (parent)
        return parent->getSelfForMethod(method);

    ErrorException *e = new RuntimeError("can't find self for " + method->callToString());
    e->raise();

    return 0;
}

IObject *Context::clone() {
    Context *clone = new Context(currentSelf, currentClass, parent, modifiers);
    clone->locals = locals;
    return clone;
}
