#include "context.h"

#include "object.h"
#include "runtime.h"
#include "objectcontext.h"

Context::Context(Runtime *runtime)
    : runtime(runtime), parent(nullptr) {
    pushSelf(runtime->getMainObject());
    pushHere(runtime->getMainObject());
}

Context::~Context() {
    for (Context *child : children)
        delete child;
}

Object *Context::getSelf() const {
    return selves.back();
}

//void Context::setSelf(Object *self) {
//    this->self = self;
//}

Object *Context::getHere() const {
    return heres.back();
}

//void Context::setHere(Object *here) {
//    this->here = here;
//}

void Context::pushSelf(Object *self) {
    selves << self;
}

void Context::popSelf() {
    selves.pop_back();
}

void Context::pushHere(Object *here) {
    heres << here;
}

void Context::popHere() {
    heres.pop_back();
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

void Context::clear() {
    getHere()->clear();
}

Context *Context::childContext(Object *self, Object *here) {
    children << new Context(self, here, this);
    return children.back();
}

Context *Context::childContext(Object *here) {
    return childContext(getSelf(), here);
}

Context *Context::objectChildContext(Object *self, Object *here) {
    children << new ObjectContext(self, here, this);
    return children.back();
}

Context *Context::objectChildContext() {
    return objectChildContext(getSelf(), getHere());
}

Context::Context(Object *self, Object *here, Context *parent)
    : runtime(parent->runtime), parent(parent) {
    pushSelf(self);
    pushHere(here);
}
