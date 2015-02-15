#include "negateexpression.h"

#include "runtime.h"

NegateExpression::NegateExpression(Expression *self)
    : self(self) {
}

Object *NegateExpression::eval(Context *context) {
    return self->eval(context)->isTrue() ? Runtime::getFalse() : Runtime::getTrue();
}
