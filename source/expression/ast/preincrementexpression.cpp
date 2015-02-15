#include "preincrementexpression.h"

PreIncrementExpression::PreIncrementExpression(Expression *self)
    : self(self) {
}

Object *PreIncrementExpression::eval(Context *context) {
    Object *self = this->self->eval(context);
    self->call("++");
    return self;
}
