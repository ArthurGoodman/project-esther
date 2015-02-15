#include "postdecrementexpression.h"

PostDecrementExpression::PostDecrementExpression(Expression *self)
    : self(self) {
}

Object *PostDecrementExpression::eval(Context *context) {
    Object *self = this->self->eval(context);
    //Object *clone = self->clone();
    self->call("--");
    return /*clone*/ self;
}
