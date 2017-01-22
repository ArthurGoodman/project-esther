#include "nativefunction.h"

Object *NativeFunction::execute(Object *self, const std::vector<Object *> &args) {
    return body(self, args);
}

NativeFunction::NativeFunction(Class *objectClass, const std::string &name, int arity, const std::function<Object *(Object *, const std::vector<Object *> &)> &body)
    : Function(objectClass, name, arity)
    , body(body) {
}
