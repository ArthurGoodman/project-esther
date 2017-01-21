#include "context.h"

#include "object.h"
#include "runtime.h"

Context::Context(Runtime *runtime)
    : runtime(runtime), parent(nullptr), self(runtime->getMainObject()), here(runtime->getMainObject()) {
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

Runtime *Context::getRuntime() const {
    return runtime;
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

    Object *temp = nullptr;
    if ((temp = getSelf()->get(name)))
        return temp;

    if (parent)
        return parent->get(name);

    if (runtime->hasRootClass(name))
        return (Object *)runtime->getRootClass(name);

    return nullptr;
}

std::pair<Object *, Object *> Context::getWithSource(const std::string &name) const {
    if (hasLocal(name))
        return std::make_pair(getLocal(name), getSelf());

    Object *temp = nullptr;
    if ((temp = getSelf()->get(name)))
        return std::make_pair(temp, getSelf());

    if (parent)
        return parent->getWithSource(name);

    if (runtime->hasRootClass(name))
        return std::make_pair((Object *)runtime->getRootClass(name), runtime->getMainObject());

    return std::make_pair(nullptr, nullptr);
}

Context *Context::childContext() {
    children << new Context(getSelf(), getHere(), this);
    return children.back();
}

Context *Context::childContext(Object *self, Object *here) {
    Context *context = childContext();

    context->setSelf(self);
    context->setHere(here);

    return context;
}

Context::Context(Object *self, Object *here, Context *parent)
    : runtime(parent->runtime), parent(parent), self(self), here(here) {
}
