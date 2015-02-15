#include "predecrementexpression.h"

PreDecrementExpression::PreDecrementExpression(Expression *self)
    : self(self) {
}

Object *PreDecrementExpression::eval(Context *context) {
    Object *self = this->self->eval(context);
    self->call("--");
    return self;
}
