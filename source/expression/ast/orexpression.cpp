#include "orexpression.h"

#include "iobject.h"

OrExpression::OrExpression(Expression *self, Expression *arg)
    : self(self), arg(arg) {
}

IObject *OrExpression::exec(Context *context) {
    IObject *self = this->self->eval(context);

    if (self->isTrue())
        return self;

    return arg->eval(context);
}
