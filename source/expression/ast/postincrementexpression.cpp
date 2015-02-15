#include "postincrementexpression.h"

PostIncrementExpression::PostIncrementExpression(Expression *self)
    : self(self) {
}

Object *PostIncrementExpression::eval(Context *context) {
    Object *self = this->self->eval(context);
    //Object *clone = self->clone();
    self->call("++");
    return /*clone*/ self;
}
