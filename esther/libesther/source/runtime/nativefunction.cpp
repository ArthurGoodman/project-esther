#include "nativefunction.h"

NativeFunction::NativeFunction(const std::string &name, int arity, const std::function<Object *(Object *, const std::list<Object *> &)> &body)
    : Function(name, arity), body(body) {
}

Object *NativeFunction::execute(Object *self, const std::list<Object *> &args) {
    return body(self, args);
}
