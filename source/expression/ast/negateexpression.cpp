#include "negateexpression.h"

#include "runtime.h"
#include "iobject.h"

NegateExpression::NegateExpression(Expression *self)
    : self(self) {
}

IObject *NegateExpression::exec(Context *context) {
    return self->eval(context)->isTrue() ? Runtime::getFalse() : Runtime::getTrue();
}
