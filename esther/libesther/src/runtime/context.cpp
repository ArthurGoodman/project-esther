#include "runtime/context.h"

#include "runtime/object.h"
#include "runtime/esther.h"

Context::Context(Esther *esther)
    : parent(nullptr)
    , self(esther->getMainObject())
    , here(self) {
}

Context::~Context() {
}

Ptr<Object> Context::getSelf() const {
    return self;
}

void Context::setSelf(Ptr<Object> self) {
    this->self = self;
}

Ptr<Object> Context::getHere() const {
    return here;
}

void Context::setHere(Ptr<Object> here) {
    this->here = here;
}

bool Context::hasLocal(const std::string &name) const {
    return getHere()->hasAttribute(name);
}

Ptr<Object> Context::getLocal(const std::string &name) const {
    return getHere()->getAttribute(name);
}

void Context::setLocal(const std::string &name, Ptr<Object> value) {
    getHere()->setAttribute(name, value);
}

Ptr<Object> Context::get(Esther *esther, const std::string &name) const {
    if (hasLocal(name))
        return getLocal(name);

    if (parent)
        return parent->get(esther, name);

    if (esther->hasRootClass(name))
        return (Object *)*esther->getRootClass(name);

    return nullptr;
}

bool Context::set(const std::string &name, Ptr<Object> value) {
    if (hasLocal(name)) {
        setLocal(name, value);
        return true;
    }

    if (parent)
        return parent->set(name, value);

    return false;
}

Ptr<Context> Context::childContext(Ptr<Object> self, Ptr<Object> here) {
    return new Context(self, here, this);
}

void Context::mapOnReferences(const std::function<void(ManagedObject *&)> &f) {
    if (parent)
        f((ManagedObject *&)parent);

    f((ManagedObject *&)self);
    f((ManagedObject *&)here);
}

int Context::getSize() const {
    return sizeof *this;
}

Context::Context(Ptr<Object> self, Ptr<Object> here, Ptr<Context> parent)
    : parent(parent)
    , self(self)
    , here(here) {
}
