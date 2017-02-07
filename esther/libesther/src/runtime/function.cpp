#include "runtime/function.h"

#include "esther.h"
#include "runtime/context.h"
#include "common/utility.h"

namespace es {

std::string Function::getName() const {
    return name;
}

void Function::setName(const std::string &name) {
    this->name = name;
}

Object *Function::invoke(Esther *esther, Object *self, const std::vector<Object *> &args) {
    if (arity >= 0 && arity != static_cast<int>(args.size()))
        Esther::runtimeError("invalid number of arguments (%i/%i)", args.size(), arity);

    return execute(esther, self, args);
}

std::string Function::toString() const {
    return getName().empty() ? "<anonymous function>" : "<function " + getName() + ">";
}

Function::Function(Class *objectClass, const std::string &name, int arity)
    : Object(objectClass)
    , name(name)
    , arity(arity) {
    setSize(sizeof *this);
}
}
