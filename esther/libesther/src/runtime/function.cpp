#include "runtime/function.h"

#include "runtime/context.h"
#include "runtime/esther.h"
#include "common/utility.h"

std::string Function::getName() const {
    return *name;
}

void Function::setName(const std::string &name) {
    *this->name = name;
}

Ptr<Object> Function::invoke(Esther *esther, Ptr<Object> self, const std::vector<Ptr<Object>> &args) {
    Ptr<Function> _this = this;

    if (_this->arity >= 0 && _this->arity != (int)args.size())
        Esther::runtimeError("invalid number of arguments (" + Utility::toString(args.size()) + "/" + Utility::toString(_this->arity) + ")");

    return _this->execute(esther, self, args);
}

std::string Function::toString() const {
    Ptr<const Function> _this = this;

    return _this->getName().empty() ? "<anonymous function>" : "<function " + _this->getName() + ">";
}

void Function::finalize() {
    Object::finalize();

    delete name;
}

Function::Function(Ptr<Class> objectClass, const std::string &name, int arity)
    : Object(objectClass)
    , name(new std::string(name))
    , arity(arity) {
}
