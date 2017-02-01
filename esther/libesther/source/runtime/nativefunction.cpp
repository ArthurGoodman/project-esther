#include "nativefunction.h"

#include "esther.h"

NativeFunction::NativeFunction(Esther *esther, const std::string &name, int arity, const std::function<Pointer<Object>(Esther *, Pointer<Object>, const std::vector<Pointer<Object>> &)> &body)
    : Function(esther->getRootClass("Function"), name, arity)
    , body(body) {
}

void NativeFunction::copy(ManagedObject *dst) {
    new (dst) NativeFunction(*this);
}

int NativeFunction::getSize() const {
    return sizeof *this;
}

Pointer<Object> NativeFunction::execute(Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) {
    return body(esther, self, args);
}
