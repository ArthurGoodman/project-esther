#include "functionexpression.h"

FunctionExpression::FunctionExpression(InterpretedFunction *f, Expression *name)
    : f(f), name(name) {
}

Object *FunctionExpression::exec(Context *context) {
    f->setContext(context);
    f->setName(name->eval(context)->toString());
    context->setLocal(f->getName(), f);
    return f;
}
