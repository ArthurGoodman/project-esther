#include "context.h"

#include "object.h"
#include "runtime.h"

//Context::Context()
//    : self(Runtime::getMainObject()), here(new Object), parent(0) {
//}

Context::Context(Object *self, Context *parent)
    : self(self), here(new Object), parent(parent) {
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
