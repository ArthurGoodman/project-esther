#include "forexpression.h"

#include "runtime.h"
#include "continueexception.h"
#include "breakexception.h"

ForExpression::ForExpression() {
}

Object *ForExpression::exec(Context */*context*/) {
    return Runtime::getNull();
}
