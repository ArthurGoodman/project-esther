#include "postdecrementexpression.h"

PostDecrementExpression::PostDecrementExpression(Expression *self)
    : self(self) {
}

Object *PostDecrementExpression::exec(Context *context) {
    Object *self = this->self->eval(context);
    Object *clone = self->clone();
    self->call("--");
    return clone;
}
