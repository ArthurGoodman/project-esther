#include "function.h"

#include "runtime.h"
#include "utility.h"

Function::Function(const std::string &name, uint arity)
    : name(name), arity(arity) {
}

std::string Function::getName() const {
    return name;
}

void Function::setName(const std::string &name) {
    this->name = name;
}

Object *Function::invoke(Object *self, const std::list<Object *> &args) {
    if (args.size() != arity)
        Runtime::runtimeError("invalid number of arguments (" + Utility::toString(args.size()) + "/" + Utility::toString(arity) + ")");

    return execute(self, args);
}
