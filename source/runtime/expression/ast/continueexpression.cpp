#include "continueexpression.h"

#include "esther.h"
#include "continueexception.h"

namespace esther {

Object *ContinueExpression::eval(Context *) {
    throw new ContinueException;
}
}
