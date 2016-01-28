#include "preincrementexpression.h"

#include "iobject.h"

PreIncrementExpression::PreIncrementExpression(Expression *self)
    : self(self) {
}

IObject *PreIncrementExpression::exec(Context *context) {
    IObject *self = this->self->eval(context);
    self->call("++");
    return self;
}
