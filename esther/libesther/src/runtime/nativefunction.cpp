#include "runtime/nativefunction.h"

#include "esther.h"

namespace es {

NativeFunction::NativeFunction(Esther *esther, const std::string &name, int arity, const FunctionBody &body)
    : Function(esther->getRootClass("Function"), name, arity)
    , body(body) {
    setSize(sizeof *this);
}

Object *NativeFunction::execute(Esther *esther, Object *self, const std::vector<Object *> &args) {
    return body(esther, self, args);
}
}
