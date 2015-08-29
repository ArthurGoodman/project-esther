#include "includeexpression.h"

#include "engine.h"

IncludeExpression::IncludeExpression(Expression *fileName)
    : fileName(fileName) {
}

Object *IncludeExpression::eval(Context *context) {
    return Engine::instance()->runFile(fileName->eval(context)->toString(), context);
}
