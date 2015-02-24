#include "forexpression.h"

#include "runtime.h"
#include "continueexception.h"
#include "breakexception.h"

ForExpression::ForExpression() {
}

Object *ForExpression::eval(Context *context) {
    return Runtime::getNull();
}
