#include "cloneandcallexpression.h"

#include "runtime.h"

namespace esther {

CloneAndCallExpression::CloneAndCallExpression(Expression *self, string name)
    : self(self), name(name) {
}

Object *CloneAndCallExpression::eval(Context *context) {
    return Runtime::getNull();
}
}
