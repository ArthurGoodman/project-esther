#include "postincrementexpression.h"

namespace esther {

PostIncrementExpression::PostIncrementExpression(Expression *self)
    : self(self) {
}

PostIncrementExpression::~PostIncrementExpression() {
    delete self;
}

Object *PostIncrementExpression::eval(Context *context) {
    Object *self = this->self->eval(context);
    //Object *clone = self->clone();
    self->call("++");
    return /*clone*/ self;
}
}
