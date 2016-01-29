#include "predecrementexpression.h"

#include "iobject.h"

PreDecrementExpression::PreDecrementExpression(Expression *self)
    : self(self) {
}

IObject *PreDecrementExpression::exec(Context *context) {
    IObject *self = this->self->eval(context);
    self->call("--");
    return self;
}
