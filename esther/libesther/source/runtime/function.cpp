#include "function.h"

#include "context.h"
#include "esther.h"
#include "utility.h"

Function::~Function() {
    delete name;
}

std::string Function::getName() const {
    return *name;
}

void Function::setName(const std::string &name) {
    *this->name = name;
}

Pointer<Object> Function::invoke(Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) {
    Pointer<Function> _this = this;

    if (_this->arity >= 0 && _this->arity != (int)args.size())
        Esther::runtimeError("invalid number of arguments (" + Utility::toString(args.size()) + "/" + Utility::toString(_this->arity) + ")");

    return _this->execute(esther, self, args);
}

std::string Function::toString() const {
    Pointer<const Function> _this = this;

    return _this->getName().empty() ? "<anonymous function>" : "<function " + _this->getName() + ">";
}

Function::Function(Pointer<Class> objectClass, const std::string &name, int arity)
    : Object(objectClass)
    , name(new std::string(name))
    , arity(arity) {
}
