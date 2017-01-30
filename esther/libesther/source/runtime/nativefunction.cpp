#include "nativefunction.h"

Pointer<Object> NativeFunction::execute(Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) {
    return body(esther, self, args);
}

NativeFunction::NativeFunction(Pointer<Class> objectClass, const std::string &name, int arity, const std::function<Pointer<Object>(Esther *, Pointer<Object>, const std::vector<Pointer<Object>> &)> &body)
    : Function(objectClass, name, arity)
    , body(body) {
}
