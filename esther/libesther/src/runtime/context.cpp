#include "runtime/context.h"

#include "esther.h"
#include "runtime/object.h"
#include "runtime/class.h"

namespace es {

Context::Context(Esther *esther)
    : ManagedObject(sizeof *this)
    , parent(nullptr)
    , self(esther->getMainObject())
    , here(self) {
}

Object *Context::getSelf() const {
    return self;
}

void Context::setSelf(Object *self) {
    this->self = self;
}

Object *Context::getHere() const {
    return here;
}

void Context::setHere(Object *here) {
    this->here = here;
}

bool Context::hasLocal(const std::string &name) const {
    return getHere()->hasAttribute(name);
}

Object *Context::getLocal(const std::string &name) const {
    return getHere()->getAttribute(name);
}

void Context::setLocal(const std::string &name, Object *value) {
    getHere()->setAttribute(name, value);
}

Object *Context::get(Esther *esther, const std::string &name) const {
    if (hasLocal(name))
        return getLocal(name);

    if (parent)
        return parent->get(esther, name);

    if (esther->hasRootClass(name))
        return static_cast<Object *>(esther->getRootClass(name));

    return nullptr;
}

bool Context::set(const std::string &name, Object *value) {
    if (hasLocal(name)) {
        setLocal(name, value);
        return true;
    }

    if (parent)
        return parent->set(name, value);

    return false;
}

Context *Context::childContext(Object *self, Object *here) {
    return new Context(self, here, this);
}

Context::Context(Object *self, Object *here, Context *parent)
    : ManagedObject(sizeof *this)
    , parent(parent)
    , self(self)
    , here(here) {
}
}
