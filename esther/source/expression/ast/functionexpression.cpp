#include "functionexpression.h"

FunctionExpression::FunctionExpression(::Function *f)
    : f(f) {
}

Object *FunctionExpression::exec(Context *context) {
    f->setContext(context);
    return f;
}
