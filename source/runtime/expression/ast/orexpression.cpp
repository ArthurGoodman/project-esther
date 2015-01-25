#include "orexpression.h"

namespace esther {

OrExpression::OrExpression(Expression *self, Expression *arg)
    : self(self), arg(arg) {
}

Object *OrExpression::eval(Context *context) {
    Object *self = this->self->eval(context);

    if (self->isTrue())
        return self;

    return arg->eval(context);
}
}
