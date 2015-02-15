#include "andexpression.h"

AndExpression::AndExpression(Expression *self, Expression *arg)
    : self(self), arg(arg) {
}

AndExpression::~AndExpression() {
    delete self;
    delete arg;
}

Object *AndExpression::eval(Context *context) {
    Object *self = this->self->eval(context);

    if (self->isTrue())
        return arg->eval(context);

    return self;
}
