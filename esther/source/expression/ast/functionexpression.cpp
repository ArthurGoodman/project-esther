#include "functionexpression.h"

FunctionExpression::FunctionExpression(InterpretedFunction *f)
    : f(f) {
}

Object *FunctionExpression::exec(Context *context) {
    f->setContext(context);
    return f;
}
