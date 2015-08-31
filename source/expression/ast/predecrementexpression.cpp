#include "predecrementexpression.h"

PreDecrementExpression::PreDecrementExpression(Expression *self)
    : self(self) {
}

Object *PreDecrementExpression::exec(Context *context) {
    Object *self = this->self->eval(context);
    self->call("--");
    return self;
}
