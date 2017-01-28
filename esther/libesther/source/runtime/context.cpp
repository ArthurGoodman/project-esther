#include "context.h"

#include "object.h"
#include "esther.h"

Context::Context(Esther *esther)
    : esther(esther)
    , parent(nullptr)
    , self(esther->getMainObject())
    , here(self) {
}

Context::~Context() {
    for (Context *child : children)
        delete child;
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

Object *Context::get(const std::string &name) const {
    if (hasLocal(name))
        return getLocal(name);

    if (parent)
        return parent->get(name);

    if (esther->hasRootClass(name))
        return (Object *)esther->getRootClass(name);

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

Context *Context::childContext() {
    children << new Context(getSelf(), getHere(), this);
    return children.back();
}

Context *Context::childContext(Object *self, Object *here) {
    children << new Context(self, here, this);
    return children.back();
}

Context::Context(Object *self, Object *here, Context *parent)
    : esther(parent->esther)
    , parent(parent)
    , self(self)
    , here(here) {
}
