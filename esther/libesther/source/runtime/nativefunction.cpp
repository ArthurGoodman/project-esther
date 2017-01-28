#include "nativefunction.h"

Object *NativeFunction::execute(Esther *esther, Object *self, const std::vector<Object *> &args) {
    return body(esther, self, args);
}

NativeFunction::NativeFunction(Class *objectClass, const std::string &name, int arity, const std::function<Object *(Esther *, Object *, const std::vector<Object *> &)> &body)
    : Function(objectClass, name, arity)
    , body(body) {
}
