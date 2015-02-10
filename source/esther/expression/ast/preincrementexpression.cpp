#include "preincrementexpression.h"

namespace esther {

PreIncrementExpression::PreIncrementExpression(Expression *self)
    : self(self) {
}

PreIncrementExpression::~PreIncrementExpression() {
    delete self;
}

Object *PreIncrementExpression::eval(Context *context) {
    Object *self = this->self->eval(context);
    self->call("++");
    return self;
}
}
