#include "continueexpression.h"

#include "esther.h"

namespace esther {

Object *ContinueExpression::eval(Context *context) {
    return Esther::getNull();
}
}
