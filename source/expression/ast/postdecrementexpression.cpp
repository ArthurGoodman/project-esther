#include "postdecrementexpression.h"

#include "iobject.h"

PostDecrementExpression::PostDecrementExpression(Expression *self)
    : self(self) {
}

IObject *PostDecrementExpression::exec(Context *context) {
    IObject *self = this->self->eval(context);
    IObject *clone = self->clone();
    self->call("--");
    return clone;
}
