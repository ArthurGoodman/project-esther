#include "notexpression.h"

#include "context.h"
#include "runtime.h"

NotExpression::NotExpression(Expression *self)
    : self(self) {
}

NotExpression::~NotExpression() {
    delete self;
}

Object *NotExpression::exec(Context *context) {
    return context->getRuntime()->toBoolean(!self->eval(context)->isTrue());
}
