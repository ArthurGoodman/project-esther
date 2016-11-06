#include "context.h"

#include "object.h"
#include "runtime.h"

Context::Context(Runtime *runtime)
    : self(runtime->getMainObject()), here(runtime->getMainObject()), runtime(runtime), parent(nullptr) {
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

Runtime *Context::getRuntime() const {
    return runtime;
}

bool Context::hasLocal(const std::string &name) const {
    return here->hasAttribute(name);
}

Object *Context::getLocal(const std::string &name) const {
    return here->getAttribute(name);
}

void Context::setLocal(const std::string &name, Object *value) {
    here->setAttribute(name, value);
}

Object *Context::get(const std::string &name) const {
    if (hasLocal(name))
        return getLocal(name);

    Object *temp = nullptr;
    if ((temp = self->get(name)))
        return temp;

    if (parent)
        return parent->get(name);

    if (runtime->hasRootClass(name))
        return (Object *)runtime->getRootClass(name);

    return nullptr;
}

std::pair<Object *, Object *> Context::getWithSource(const std::string &name) const {
    if (hasLocal(name))
        return std::make_pair(getLocal(name), self);

    Object *temp = nullptr;
    if ((temp = self->get(name)))
        return std::make_pair(temp, self);

    if (parent)
        return parent->getWithSource(name);

    if (runtime->hasRootClass(name))
        return std::make_pair((Object *)runtime->getRootClass(name), runtime->getMainObject());

    return std::make_pair(nullptr, nullptr);
}

void Context::clear() {
    here->clear();
}

Context *Context::childContext(Object *self, Object *here) {
    return new Context(self, here, this);
}

Context::Context(Object *self, Object *here, Context *parent)
    : self(self), here(here), runtime(parent->runtime), parent(parent) {
}
