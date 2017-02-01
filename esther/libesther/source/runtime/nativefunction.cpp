#include "nativefunction.h"

#include "esther.h"

NativeFunction::NativeFunction(Esther *esther, const std::string &name, int arity, const FunctionBody &body)
    : Function(esther->getRootClass("Function"), name, arity)
    , body(new FunctionBody(body)) {
}

NativeFunction::~NativeFunction() {
    delete body;
}

void NativeFunction::copy(ManagedObject *dst) {
    new (dst) NativeFunction(*this);
}

int NativeFunction::getSize() const {
    return sizeof *this;
}

Pointer<Object> NativeFunction::execute(Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) {
    Pointer<NativeFunction> _this = this;

    return (*_this->body)(esther, self, args);
}
