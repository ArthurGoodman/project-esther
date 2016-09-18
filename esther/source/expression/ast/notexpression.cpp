#include "notexpression.h"

#include "runtime.h"

NotExpression::NotExpression(Expression *self)
    : self(self) {
}

NotExpression::~NotExpression() {
    delete self;
}

Object *NotExpression::exec(Context *context) {
    return Runtime::toBoolean(!self->eval(context)->isTrue());
}
