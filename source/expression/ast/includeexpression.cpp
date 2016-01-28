#include "includeexpression.h"

#include "iengine.h"
#include "iobject.h"

IncludeExpression::IncludeExpression(Expression *fileName)
    : fileName(fileName) {
}

IObject *IncludeExpression::exec(Context *context) {
    return IEngine::instance()->runFile(fileName->eval(context)->callToString(), context);
}
