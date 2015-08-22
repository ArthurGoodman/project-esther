#include "includeexpression.h"

#include "engine.h"
#include "io.h"

IncludeExpression::IncludeExpression(Expression *fileName)
    : fileName(fileName) {
}

IncludeExpression::~IncludeExpression() {
    delete fileName;
}

Object *IncludeExpression::eval(Context *context) {
    return Engine::instance()->run(IO::readFile(fileName->eval(context)->toString()), context);
}
