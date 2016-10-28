#include "context.h"

#include "object.h"
#include "runtime.h"

Context::Context(Runtime *runtime)
    : self(runtime->getMainObject()), here(new Object), runtime(runtime), parent(0) {
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
    return hasLocal(name) ? getLocal(name) : parent ? parent->get(name) : 0;
}

void Context::clear() {
    here->clear();
}

Context *Context::childContext(Object *self) {
    return new Context(self, this);
}

Context::Context(Object *self, Context *parent)
    : self(self), here(new Object), runtime(parent->runtime), parent(parent) {
}
