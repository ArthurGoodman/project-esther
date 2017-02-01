#include "context.h"

#include "object.h"
#include "esther.h"

Context::Context(Esther *esther)
    : parent(nullptr)
    , self(esther->getMainObject())
    , here(self) {
}

Context::~Context() {
}

Pointer<Object> Context::getSelf() const {
    return self;
}

void Context::setSelf(Pointer<Object> self) {
    this->self = self;
}

Pointer<Object> Context::getHere() const {
    return here;
}

void Context::setHere(Pointer<Object> here) {
    this->here = here;
}

bool Context::hasLocal(const std::string &name) const {
    return getHere()->hasAttribute(name);
}

Pointer<Object> Context::getLocal(const std::string &name) const {
    return getHere()->getAttribute(name);
}

void Context::setLocal(const std::string &name, Pointer<Object> value) {
    getHere()->setAttribute(name, value);
}

Pointer<Object> Context::get(Esther *esther, const std::string &name) const {
    if (hasLocal(name))
        return getLocal(name);

    if (parent)
        return parent->get(esther, name);

    if (esther->hasRootClass(name))
        return (Object *)*esther->getRootClass(name);

    return nullptr;
}

bool Context::set(const std::string &name, Pointer<Object> value) {
    if (hasLocal(name)) {
        setLocal(name, value);
        return true;
    }

    if (parent)
        return parent->set(name, value);

    return false;
}

Pointer<Context> Context::childContext(Pointer<Object> self, Pointer<Object> here) {
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

Context::Context(Pointer<Object> self, Pointer<Object> here, Pointer<Context> parent)
    : parent(parent)
    , self(self)
    , here(here) {
}
