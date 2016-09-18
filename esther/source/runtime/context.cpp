#include "context.h"

#include "runtime.h"

Context::Context()
    : self(Runtime::getMainObject()), parent(0) {
}

Context::Context(Object *self, Context *parent)
    : self(self), parent(parent) {
}

Object *Context::getSelf() const {
    return self;
}

void Context::setSelf(Object *self) {
    this->self = self;
}

bool Context::hasLocal(const std::string &name) const {
    return locals.find(name) != locals.end();
}

Object *Context::getLocal(const std::string &name) const {
    return locals.at(name);
}

void Context::setLocal(const std::string &name, Object *value) {
    locals[name] = value;
}

Object *Context::get(const std::string &name) const {
    return hasLocal(name) ? getLocal(name) : parent ? parent->get(name) : 0;
}

void Context::clear() {
    locals.clear();
}
