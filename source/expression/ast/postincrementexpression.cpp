#include "postincrementexpression.h"

#include "iobject.h"

PostIncrementExpression::PostIncrementExpression(Expression *self)
    : self(self) {
}

IObject *PostIncrementExpression::exec(Context *context) {
    IObject *self = this->self->eval(context);
    IObject *clone = self->clone();
    self->call("++");
    return clone;
}
