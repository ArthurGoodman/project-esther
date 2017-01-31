#include "function.h"

#include "context.h"
#include "esther.h"
#include "utility.h"

std::string Function::getName() const {
    return name;
}

void Function::setName(const std::string &name) {
    this->name = name;
}

Pointer<Object> Function::invoke(Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) {
    if (arity >= 0 && arity != (int)args.size())
        Esther::runtimeError("invalid number of arguments (" + Utility::toString(args.size()) + "/" + Utility::toString(arity) + ")");

    return execute(esther, self, args);
}

std::string Function::toString() const {
    return getName().empty() ? "<anonymous function>" : "<function " + getName() + ">";
}

int Function::getSize() const {
    return sizeof *this;
}

Function::Function(Pointer<Class> objectClass, const std::string &name, int arity)
    : Object(objectClass)
    , name(name)
    , arity(arity) {
}
