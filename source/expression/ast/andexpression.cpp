#include "andexpression.h"

#include "iobject.h"

AndExpression::AndExpression(Expression *self, Expression *arg)
    : self(self), arg(arg) {
}

IObject *AndExpression::exec(Context *context) {
    IObject *self = this->self->eval(context);

    if (self->isTrue())
        return arg->eval(context);

    return self;
}
