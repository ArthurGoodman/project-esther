#include "negateexpression.h"

#include "esther.h"

namespace esther {

NegateExpression::NegateExpression(Expression *self)
    : self(self) {
}

NegateExpression::~NegateExpression() {
    delete self;
}

Object *NegateExpression::eval(Context *context) {
    return self->eval(context)->isTrue() ? Esther::getFalse() : Esther::getTrue();
}
}
