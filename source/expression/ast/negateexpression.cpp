#include "negateexpression.h"

#include "runtime.h"

namespace esther {

NegateExpression::NegateExpression(Expression *self)
    : self(self) {
}

NegateExpression::~NegateExpression() {
    delete self;
}

Object *NegateExpression::eval(Context *context) {
    return self->eval(context)->isTrue() ? Runtime::getFalse() : Runtime::getTrue();
}
}
