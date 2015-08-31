#include "preincrementexpression.h"

PreIncrementExpression::PreIncrementExpression(Expression *self)
    : self(self) {
}

Object *PreIncrementExpression::exec(Context *context) {
    Object *self = this->self->eval(context);
    self->call("++");
    return self;
}
