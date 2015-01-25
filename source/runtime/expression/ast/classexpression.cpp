#include "classexpression.h"

#include "esther.h"

namespace esther {

ClassExpression::ClassExpression(Expression *name, Expression *superclass, Expression *body)
    : name(name), superclass(superclass), body(body) {
}

Object *ClassExpression::eval(Context *context) {
    return Esther::getNull();
}
}
