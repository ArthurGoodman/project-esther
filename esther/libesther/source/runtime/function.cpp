#include "function.h"

#include "context.h"
#include "runtime.h"
#include "utility.h"

std::string Function::getName() const {
    return name;
}

void Function::setName(const std::string &name) {
    this->name = name;
}

Object *Function::invoke(Object *self, const std::vector<Object *> &args) {
    if (arity >= 0 && arity != (int)args.size())
        Runtime::runtimeError("invalid number of arguments (" + Utility::toString(args.size()) + "/" + Utility::toString(arity) + ")");

    return execute(self, args);
}

std::string Function::toString() const {
    return getName().empty() ? "<anonymous function>" : "<function " + getName() + ">";
}

Function::Function(Class *objectClass, const std::string &name, int arity)
    : Object(objectClass), name(name), arity(arity) {
}
