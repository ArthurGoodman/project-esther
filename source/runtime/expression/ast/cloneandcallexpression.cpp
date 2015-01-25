#include "cloneandcallexpression.h"

#include "esther.h"

namespace esther {

CloneAndCallExpression::CloneAndCallExpression(Expression *self, string name)
    : self(self), name(name) {
}

Object *CloneAndCallExpression::eval(Context *context) {
    return Esther::getNull();
}
}
