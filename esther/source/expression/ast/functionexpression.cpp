#include "functionexpression.h"

FunctionExpression::FunctionExpression(InterpretedFunction *f)
    : f(f) {
}

Object *FunctionExpression::exec(Context *context) {
    f->setContext(context);
    context->setLocal(f->getName(), f);
    return f;
}
