#include "includeexpression.h"

#include "iengine.h"

IncludeExpression::IncludeExpression(Expression *fileName)
    : fileName(fileName) {
}

Object *IncludeExpression::exec(Context *context) {
    return IEngine::instance()->runFile(fileName->eval(context)->callToString(), context);
}
