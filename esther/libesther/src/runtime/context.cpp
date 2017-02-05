#include "runtime/context.h"

#include "runtime/object.h"
#include "esther.h"
#include "runtime/class.h"

namespace es {

Context::Context(Esther *esther)
    : parent(nullptr)
    , self(esther->getMainObject())
    , here(self) {
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

bool Context::hasLocal(Esther *esther, const std::string &name) const {
    return getHere()->hasAttribute(esther, name);
}

Ptr<Object> Context::getLocal(Esther *esther, const std::string &name) const {
    return getHere()->getAttribute(esther, name);
}

void Context::setLocal(Esther *esther, const std::string &name, Ptr<Object> value) {
    getHere()->setAttribute(esther, name, value);
}

Ptr<Object> Context::get(Esther *esther, const std::string &name) const {
    Ptr<const Context> _this = this;

    if (_this->hasLocal(esther, name))
        return _this->getLocal(esther, name);

    if (_this->parent)
        return _this->parent->get(esther, name);

    if (esther->hasRootClass(name))
        return static_cast<Object *>(*esther->getRootClass(name));

    return nullptr;
}

bool Context::set(Esther *esther, const std::string &name, Ptr<Object> value) {
    Ptr<Context> _this = this;

    if (_this->hasLocal(esther, name)) {
        _this->setLocal(esther, name, value);
        return true;
    }

    if (_this->parent)
        return _this->parent->set(esther, name, value);

    return false;
}

Ptr<Context> Context::childContext(Ptr<Object> self, Ptr<Object> here) {
    return new Context(self, here, this);
}

void Context::mapOnReferences(void (*f)(ManagedObject *&)) {
    if (parent)
        f(reinterpret_cast<ManagedObject *&>(parent));

    f(reinterpret_cast<ManagedObject *&>(self));

    if (self != here)
        f(reinterpret_cast<ManagedObject *&>(here));
}

int Context::getSize() const {
    return sizeof *this;
}

Context::Context(Ptr<Object> self, Ptr<Object> here, Ptr<Context> parent)
    : parent(parent)
    , self(self)
    , here(here) {
}
}
